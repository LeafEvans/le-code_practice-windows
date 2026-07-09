/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <cstdio>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unordered_set>
#include <filesystem>
#include <glog/logging.h>
#include "RemoteCommunicationKit/rcp.h"
#include "ImageSourceResolver.h"
#include "utils/StringUtils.h"

namespace fs = std::filesystem;
namespace rnoh {
namespace svg {
class HttpTaskProcessor {
public:
    HttpTaskProcessor() { taskList_.push_back(this); }

    ~HttpTaskProcessor() {
        if (request_ != nullptr) {
            // 释放请求资源
            HMS_Rcp_DestroyRequest(request_);
            request_ = nullptr;
        }
    }

    static void clearTaskList() { taskList_.clear(); }

    void createParentPath(const fs::path &filePath);

    size_t saveImage(const char *buffer, uint32_t length);

    void markStart();

    void markEnd();

    bool keep() { return !finished_; }

    void echoSpendTime() {
        DLOG(INFO) << "[SVGImage] HttpTaskProcessor Spend Time(ns): " << endTime_.count() - startTime_.count();
    }

    bool initializeRequestAndSession(const char *uri, const std::map<std::string, std::string> *headers = nullptr);
    void setResponseCallback();

    void launchHttpRequest(const char *uri);
    void launchHttpRequestWithHeaders(const char *uri, const std::map<std::string, std::string> &headers);


    void pushThreadID(std::string id);

    static void waitAllTask();
    static void destroyAllTask();
    static void echoThreadIds();

    std::shared_ptr<ImageSourceResolver> instance_;

    std::string uri_;
    std::string filePath_;

private:
    static std::vector<HttpTaskProcessor *> taskList_;
    static std::unordered_set<std::string> threadIds_;

    FILE *fp_ = nullptr;

    std::chrono::nanoseconds startTime_;
    std::chrono::nanoseconds endTime_;

    bool finished_ = false;

    Rcp_Request *request_ = nullptr;
    Rcp_Session *session_ = nullptr;

    Rcp_ResponseCallbackObject responseCallback_;
};

} // namespace svg
} // namespace rnoh
