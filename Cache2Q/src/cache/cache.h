#pragma once

#include <list>
#include <queue>
#include <unordered_map>

template <typename T, typename KeyT = int>
struct cache_t {
    private:

    // Am. It is default LRU.
    std::list<T> cache_;
    std::size_t  size_;

    using ListTIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListTIt> htable;

    // A1-in
    std::queue<T>    in;
    std::size_t      in_maxsize;

    using QueueTIt = typename std::queue<T>::iterator;
    std::unordered_map<KeyT, QueueTIt> in_hash;

    // A1-out
    std::queue<KeyT> out;
    std::size_t      out_maxsize;

    using QueueKeyTIt = typename std::queue<KeyT>::iterator;
    std::unordered_map<KeyT, QueueKeyTIt> out_hash;

    public:

    bool lookup_update(T page) {
        // proceed page
        return false;
    }

    void reclaim_for(T page) {
        // proceed page
        return;
    }

    cache_t(std::size_t size): size_(size) { }
};
