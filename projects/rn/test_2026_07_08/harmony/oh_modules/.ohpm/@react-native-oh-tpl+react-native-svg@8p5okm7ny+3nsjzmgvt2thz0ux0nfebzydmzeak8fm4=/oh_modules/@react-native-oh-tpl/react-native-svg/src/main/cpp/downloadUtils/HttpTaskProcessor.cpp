/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include <unistd.h>
#include <sstream>
#include "HttpTaskProcessor.h"

namespace rnoh {
namespace svg {
std::vector<HttpTaskProcessor *> HttpTaskProcessor::taskList_;
std::unordered_set<std::string> HttpTaskProcessor::threadIds_;

void ResponseCallback(void *usrCtx, Rcp_Response *response, uint32_t errCode) {
    HttpTaskProcessor *processor = static_cast<HttpTaskProcessor *>(usrCtx);

    // 记录当前线程的ID
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    processor->pushThreadID(oss.str());

    if (response != NULL) {
        if (response->statusCode == RCP_OK) {
            size_t status = processor->saveImage(response->body.buffer, response->body.length);
            if (processor->instance_ && status != 0) {
                processor->instance_->imageDownloadComplete(processor->uri_, processor->filePath_);
            } else if (processor->instance_) {
                LOG(WARNING) << "[SVGImage] ResponseCallback imageDownloadFail, status: " << status;
                processor->instance_->imageDownloadFail(processor->uri_);
            }
        }

        response->destroyResponse(response);
    } else {
        LOG(ERROR) << "[SVGImage] Callback Response is NULL, errCode: " << errCode;
        if (processor->instance_) {
            processor->instance_->imageDownloadFail(processor->uri_);
        }
    }

    processor->markEnd();
}

void HttpTaskProcessor::createParentPath(const fs::path &filePath) {
    fs::path parentPath = filePath.parent_path();
    if (!parentPath.empty() && !fs::exists(parentPath)) {
        fs::create_directories(parentPath);
    }
}

size_t HttpTaskProcessor::saveImage(const char *buffer, uint32_t length) {
    size_t status = 0;
    if (filePath_ == "")
        return status;
    createParentPath(filePath_);
    fp_ = fopen(filePath_.c_str(), "w");
    if (fp_) {
        status = fwrite(buffer, sizeof(char), length, fp_);
        fclose(fp_);
    } else {
        LOG(ERROR) << "[SVGImage] write to file failed: " << filePath_;
    }
    return status;
}

void HttpTaskProcessor::markStart() {
    finished_ = false;
    auto now = std::chrono::high_resolution_clock::now();
    startTime_ = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch();
}

void HttpTaskProcessor::markEnd() {
    // 记录时间戳，标记任务结束使得keep() 返回false
    auto now = std::chrono::high_resolution_clock::now();
    endTime_ = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch();
    finished_ = true;
}

bool HttpTaskProcessor::initializeRequestAndSession(const char *uri,
                                                    const std::map<std::string, std::string> *headers) {
    // 创建http request 对象
    request_ = HMS_Rcp_CreateRequest(uri);
    if (request_ == nullptr) {
        LOG(ERROR) << "[SVGImage] Failed to create HTTP request!";
        return false;
    }

    // 如果有 headers 参数，初始化 headers
    if (headers) {
        Rcp_Headers *header = HMS_Rcp_CreateHeaders();
        for (const auto &it : *headers) {
            if (auto errorCode = HMS_Rcp_SetHeaderValue(header, it.first.c_str(), it.second.c_str())) {
                LOG(ERROR) << "[SVGImage] launchHttpRequestWithHeaders create headers error: " << errorCode;
                return false;
            }
        }
        request_->headers = header;
    }

    // 创建http 会话对象
    uint32_t errorCode = 0;
    session_ = HMS_Rcp_CreateSession(nullptr, &errorCode);
    if (errorCode) {
        LOG(ERROR) << "[SVGImage] Failed to create HTTP session, error code: " << errorCode;
        return false;
    }

    return true;
}

void HttpTaskProcessor::setResponseCallback() {
    // 设置响应数据处理的回调函数
    responseCallback_.callback = ResponseCallback;
    responseCallback_.usrCtx = this;
}

void HttpTaskProcessor::launchHttpRequest(const char *uri) {
    markStart();
    this->uri_ = uri;
    if (!initializeRequestAndSession(uri)) {
        if (instance_) {
            instance_->imageDownloadFail(uri);
        }
        markEnd();
        return;
    }

    // 设置响应数据处理的回调函数
    setResponseCallback();

    // API异步发起请求
    if (auto errCode = HMS_Rcp_Fetch(session_, request_, &responseCallback_)) {
        LOG(ERROR) << "[SVGImage] launchHttpRequest HMS_Rcp_Fetch error: " << errCode;
        if (instance_) {
            instance_->imageDownloadFail(uri);
        }
        markEnd();
    }
}

void HttpTaskProcessor::launchHttpRequestWithHeaders(const char *uri,
                                                     const std::map<std::string, std::string> &headers) {
    markStart();
    this->uri_ = uri;
    if (!initializeRequestAndSession(uri, &headers)) {
        if (instance_) {
            instance_->imageDownloadFail(uri);
        }
        markEnd();
        return;
    }

    // 设置响应数据处理的回调函数
    setResponseCallback();

    // API异步发起请求
    if (auto errCode = HMS_Rcp_Fetch(session_, request_, &responseCallback_)) {
        LOG(ERROR) << "[SVGImage] launchHttpRequest HMS_Rcp_Fetch error: " << errCode;
        if (instance_) {
            instance_->imageDownloadFail(uri);
        }
        markEnd();
    }
}

// static
void HttpTaskProcessor::waitAllTask() {
    bool wait = true;
    while (wait) {
        wait = false;
        for (auto *processor : taskList_) {
            if (processor->keep())
                wait = true;
        }
        if (wait) {
            usleep(1000 * 1000);
            echoThreadIds();
        }
    }
}

// static
void HttpTaskProcessor::destroyAllTask() {
    for (auto *processor : taskList_) {
        processor->echoSpendTime();
        delete processor;
    }

    taskList_.clear();
    threadIds_.clear();
}

// static
void HttpTaskProcessor::echoThreadIds() {
    for (auto id : threadIds_) {
        DLOG(INFO) << "[SVGImage] NetDownload Task Thread ID: " << id.c_str();
    }

    DLOG(INFO) << "[SVGImage] NetDownload Number Of Thread : " << threadIds_.size();
}

void HttpTaskProcessor::pushThreadID(std::string id) { threadIds_.insert(id); }

} // namespace svg
} // namespace rnoh