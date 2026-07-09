/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <unordered_map>
#include <list>
#include <mutex>

namespace rnoh {
namespace svg {
template <typename KeyType, typename ValueType, int defaultCapacity = 10> class LRUCache {
private:
    std::unordered_map<KeyType, std::pair<ValueType, typename std::list<KeyType>::iterator>> m_cache;
    std::list<KeyType> m_lruList;
    std::mutex m_mtx; // 用于同步的互斥锁
    std::function<bool(KeyType, ValueType)> m_deleteCallback;
    int m_cacheCapacity; // 成员变量的容量

public:
    // 构造函数，允许设置自定义容量和删除回调函数
    LRUCache(int customCapacity = defaultCapacity, std::function<bool(KeyType, ValueType)> callback = nullptr)
        : m_cacheCapacity(customCapacity), m_deleteCallback(callback) {}

    ValueType get(const KeyType &key) {
        std::lock_guard<std::mutex> lock(m_mtx);
        if (m_cache.find(key) != m_cache.end()) {
            m_lruList.erase(m_cache[key].second);
            m_lruList.push_front(key);
            m_cache[key].second = m_lruList.begin();
            return m_cache[key].first;
        }
        return ValueType(); // 如果没找到，返回默认构造的值
    }

    void put(const KeyType &key, const ValueType &value) {
        std::lock_guard<std::mutex> lock(m_mtx);
        if (m_cache.find(key) != m_cache.end()) {
            m_cache[key].first = value;
            m_lruList.erase(m_cache[key].second);
            m_lruList.push_front(key);
            m_cache[key].second = m_lruList.begin();
        } else {
            if (m_cache.size() >= m_cacheCapacity) {
                KeyType lruKey = m_lruList.back();

                // 调用删除回调函数
                if (m_deleteCallback) {
                    m_deleteCallback(lruKey, m_cache[lruKey].first);
                }

                m_cache.erase(lruKey);
                m_lruList.pop_back();
            }
            m_lruList.push_front(key);
            m_cache[key] = std::make_pair(value, m_lruList.begin());
        }
    }

    bool remove(const KeyType &key) {
        std::lock_guard<std::mutex> lock(m_mtx);
        bool status = false;
        if (m_cache.find(key) != m_cache.end()) {
            ValueType value = m_cache[key].first;
            m_lruList.erase(m_cache[key].second);
            if (m_deleteCallback) {
                status = m_deleteCallback(key, value);
            }

            m_cache.erase(key);
        }
        return status;
    }
    bool clearAll() {
        std::lock_guard<std::mutex> lock(m_mtx);
        // 从后向前遍历 lruList
        for (auto it = m_lruList.end(); it != m_lruList.begin();) {
            --it;              // 先向前移动迭代器
            KeyType key = *it; // 获取当前键
            if (m_deleteCallback) {
                // 调用删除回调并检查返回值
                if (!m_deleteCallback(key, m_cache[key].first)) {
                    return false; // 如果删除失败，返回 false
                }
            }
            m_cache.erase(key);       // 从 cache 中删除该键
            it = m_lruList.erase(it); // 删除当前节点并更新迭代器
        }
        return true; // 成功删除所有元素，返回 true
    }
    size_t size() { return m_cache.size(); }
};

} // namespace svg
} // namespace rnoh