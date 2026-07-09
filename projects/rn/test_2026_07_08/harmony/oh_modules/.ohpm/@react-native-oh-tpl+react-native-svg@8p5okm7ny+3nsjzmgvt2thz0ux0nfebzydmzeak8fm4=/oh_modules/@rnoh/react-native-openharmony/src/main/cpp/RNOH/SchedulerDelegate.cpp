/**
 * Copyright (c) 2024 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "SchedulerDelegate.h"
#include <cxxreact/TraceSection.h>
#include "MountingManager.h"
#include "RNOH/Performance/RNOHMarker.h"

namespace rnoh {

struct CreateBuckets {
  facebook::react::ShadowViewMutationList movableCreates;
  facebook::react::ShadowViewMutationList deferredTail;
  size_t deferredCreateCount{0};
};

static facebook::react::Tag getTargetTagImpl(
    const facebook::react::ShadowViewMutation& m) {
  using M = facebook::react::ShadowViewMutation;
  switch (m.type) {
    case M::Create:
    case M::Insert:
    case M::Update:
      return m.newChildShadowView.tag;
    case M::Remove:
    case M::Delete:
      return m.oldChildShadowView.tag;
    default:
      return (m.oldChildShadowView.tag != 0) ? m.oldChildShadowView.tag
                                             : m.newChildShadowView.tag;
  }
}

static inline facebook::react::Tag getTargetTag(
    const facebook::react::ShadowViewMutation& m) {
  return getTargetTagImpl(m);
}

static CreateBuckets bucketizeCreateMutations(
    const facebook::react::ShadowViewMutationList& all) {
  using M = facebook::react::ShadowViewMutation;

  CreateBuckets out;
  out.movableCreates.reserve(all.size());
  out.deferredTail.reserve(all.size());

  // If a non-create mutation for a tag appears before its Create in the same
  // transaction, that Create must not be moved ahead.
  std::unordered_set<facebook::react::Tag> seenNonCreateTags;
  seenNonCreateTags.reserve(all.size());

  for (const auto& m : all) {
    const auto tag = getTargetTag(m);
    if (m.type == M::Create) {
      if (seenNonCreateTags.find(tag) != seenNonCreateTags.end()) {
        out.deferredTail.push_back(m);
        ++out.deferredCreateCount;
      } else {
        out.movableCreates.push_back(m);
      }
      continue;
    }

    out.deferredTail.push_back(m);
    seenNonCreateTags.insert(tag);
  }

  return out;
}

SchedulerDelegate::~SchedulerDelegate() {
  DLOG(INFO) << "~SchedulerDelegate";
}

void SchedulerDelegate::schedulerDidFinishTransaction(
    const std::shared_ptr<const MountingCoordinator>& /*mountingCoordinator*/) {
  // no-op, we will flush the transaction from schedulerShouldRenderTransactions
}

void SchedulerDelegate::schedulerDidUpdateShadowTree(
    const std::unordered_map<facebook::react::Tag, folly::dynamic>&
        tagToProps) {
  // no-op
  // We will investigate if this method should be implemented
}

void logTransactionTelemetryMarkers(MountingTransaction const& transaction) {
  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_FINISH_TRANSACTION_END);
  const auto& telemetry = transaction.getTelemetry();
  auto commitStartTime =
      telemetryTimePointToMilliseconds(telemetry.getCommitStartTime());
  auto commitEndTime =
      telemetryTimePointToMilliseconds(telemetry.getCommitEndTime());
  auto diffStartTime =
      telemetryTimePointToMilliseconds(telemetry.getDiffStartTime());
  auto diffEndTime =
      telemetryTimePointToMilliseconds(telemetry.getDiffEndTime());
  auto layoutStartTime =
      telemetryTimePointToMilliseconds(telemetry.getLayoutStartTime());
  auto layoutEndTime =
      telemetryTimePointToMilliseconds(telemetry.getLayoutEndTime());

  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_COMMIT_START, "", commitStartTime);
  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_COMMIT_END, "", commitEndTime);
  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_DIFF_START, "", diffStartTime);
  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_DIFF_END, "", diffEndTime);
  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_LAYOUT_START, "", layoutStartTime);
  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_LAYOUT_END, "", layoutEndTime);
}

void SchedulerDelegate::reportMount(
    const facebook::react::ShadowViewMutationList& mutations) {
  m_taskExecutor->runTask(
      TaskThread::MAIN, [scheduler = m_scheduler, mutations] {
        const auto& schedulerShared = scheduler.lock();
        if (!schedulerShared) {
          return;
        }
        std::unordered_set<SurfaceId> mountedSurfaceIds;
        for (const auto& mutation : mutations) {
          mountedSurfaceIds.insert(mutation.newChildShadowView.surfaceId);
        }
        if (!mountedSurfaceIds.empty()) {
          for (SurfaceId surfaceId : mountedSurfaceIds) {
            schedulerShared->reportMount(surfaceId);
          }
        }
      });
}

void SchedulerDelegate::schedulerDidRequestPreliminaryViewAllocation(
    const ShadowNode& shadowNode) {
  facebook::react::TraceSection s(
      "#RNOH::SchedulerDelegate::schedulerDidRequestPreliminaryViewAllocation");
  auto preallocationRequestQueue = m_weakPreallocationRequestQueue.lock();
  if (preallocationRequestQueue == nullptr) {
    return;
  }
  preallocationRequestQueue->push({
      shadowNode.getTag(),
      shadowNode.getComponentHandle(),
      shadowNode.getComponentName(),
  });
}

void SchedulerDelegate::schedulerDidDispatchCommand(
    const ShadowView& shadowView,
    std::string const& commandName,
    folly::dynamic const& args) {
  facebook::react::TraceSection s(
      "#RNOH::SchedulerDelegate::schedulerDidDispatchCommand");
  performOnMainThread([shadowView, commandName, args](
                          MountingManager::Shared const& mountingManager) {
    mountingManager->dispatchCommand(shadowView, commandName, args);
  });
}

void SchedulerDelegate::schedulerDidSendAccessibilityEvent(
    const ShadowView& shadowView,
    std::string const& eventType) {
  performOnMainThread([shadowView, eventType](
                          MountingManager::Shared const& mountingManager) {
    mountingManager->schedulerDidSendAccessibilityEvent(shadowView, eventType);
  });
}

void SchedulerDelegate::schedulerDidSetIsJSResponder(
    ShadowView const& shadowView,
    bool isJSResponder,
    bool blockNativeResponder) {
  facebook::react::TraceSection s(
      "#RNOH::SchedulerDelegate::schedulerDidSetIsJSResponder");
  performOnMainThread([shadowView, isJSResponder, blockNativeResponder](
                          MountingManager::Shared const& mountingManager) {
    mountingManager->setIsJsResponder(
        shadowView, isJSResponder, blockNativeResponder);
  });
}

void SchedulerDelegate::performTransaction(
    const std::shared_ptr<const MountingCoordinator>& mountingCoordinator) {
  facebook::react::TraceSection s(
      "#RNOH::SchedulerDelegate::performTransaction");
  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_FINISH_TRANSACTION_START);
  mountingCoordinator->getTelemetryController().pullTransaction(
      [](auto const& transaction, auto const& /*surfaceTelemetry*/) {},
      [this](auto const& transaction, auto const& surfaceTelemetry) {
        performOnMainThread(
            [transaction](MountingManager::Shared const& mountingManager) {
              mountingManager->doMount(transaction.getMutations());
            });
      },
      [this](auto const& transaction, auto const& surfaceTelemetry) {
        int taskId = random();
        std::string taskTrace =
            "#RNOH::TaskExecutor::runningTask t" + std::to_string(taskId);
        auto createBuckets =
            bucketizeCreateMutations(transaction.getMutations());
        auto& sliceableMutations = createBuckets.movableCreates;
        auto& otherMutations = createBuckets.deferredTail;
        // The reason for using 70 here is that the average time for each
        // mutation creation is about 60 microseconds,and the time for 70 is 4.2
        // milliseconds which corresponds to the length of half a frame
        size_t maxSliceSize = 70;
        std::vector<facebook::react::ShadowViewMutationList> slicesOfMutations;
        size_t sliceableMutationsSize = sliceableMutations.size();
        if (sliceableMutationsSize > 0) {
          slicesOfMutations.reserve(
              (sliceableMutationsSize + maxSliceSize - 1) / maxSliceSize);
          for (size_t i = 0; i < sliceableMutationsSize; i += maxSliceSize) {
            slicesOfMutations.emplace_back(
                sliceableMutations.begin() + i,
                sliceableMutations.begin() +
                    std::min(sliceableMutationsSize, i + maxSliceSize));
          }
          for (const auto& mutations : slicesOfMutations) {
            performOnMainThread(
                [mutations, this, taskTrace](
                    MountingManager::Shared const& mountingManager) {
                  facebook::react::TraceSection s(taskTrace.c_str());
                  mountingManager->didMount(mutations);
                  this->reportMount(mutations);
                });
          }
        }
        performOnMainThread(
            [otherMutations, this, taskTrace](
                MountingManager::Shared const& mountingManager) {
              facebook::react::TraceSection s(taskTrace.c_str());
              mountingManager->didMount(otherMutations);
              this->reportMount(otherMutations);
              mountingManager->clearPreallocatedViews();
            });
        logTransactionTelemetryMarkers(transaction);
        facebook::react::TraceSection s(
            ("#RNOH::TaskExecutor::runTask t" + std::to_string(taskId))
                .c_str());
      });
}

void SchedulerDelegate::schedulerShouldRenderTransactions(
    const std::shared_ptr<const MountingCoordinator>& mountingCoordinator) {
  facebook::react::TraceSection s(
      "#RNOH::SchedulerDelegate::schedulerShouldRenderTransactions");
  if (m_transactionState->transactionInFlight) {
    m_transactionState->followUpTransactionRequired = true;
    return;
  }

  do {
    m_transactionState->followUpTransactionRequired = false;
    m_transactionState->transactionInFlight = true;
    performTransaction(mountingCoordinator);
    m_transactionState->transactionInFlight = false;
  } while (m_transactionState->followUpTransactionRequired);
}

void SchedulerDelegate::setScheduler(
    std::shared_ptr<facebook::react::Scheduler> const& scheduler) {
  m_scheduler = scheduler;
}

void SchedulerDelegate::schedulerShouldSynchronouslyUpdateViewOnUIThread(
    facebook::react::Tag tag,
    const folly::dynamic& props) {
  // We will investigate if this method should be implemented
  // Now, it is similar to iOS implementation in RCTScheduler.mm:71-75
}

} // namespace rnoh
