#pragma once

#include <list>
#include <queue>
#include <unordered_map>

template <typename T, typename F, typename KeyT = int>
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
    std::unordered_map<KeyT, QueueTIt> in_htable;

    // A1-out
    std::queue<KeyT> out;
    std::size_t      out_maxsize;

    using QueueKeyTIt = typename std::queue<KeyT>::iterator;
    std::unordered_map<KeyT, QueueKeyTIt> out_htable;

    public:

    bool lookup_update(KeyT key, F slow_get_page) {
        auto hit = htable.find(key);
        if (hit != htable.end()) { // found in Am
            auto elem_it = hit->second;
            if (elem_it != cache_.begin()) {
                // move elem to head
                cache_.splice(cache_.begin(), cache_, elem_it, std::next(elem_it));
            }

            return true;
        }

        auto out_it = out_htable.find(key);
        if (out_it != out.end()) { // found in A1-out
            reclaim_for(key);

            // add in Am and in htable
            cache_.push_front(slow_get_page(key));
            htable.add(cache_.front());

            return true;
        }

        auto in_it = in_htable.find(key);
        if (in_it != in.end()) { // found in A1-in
            // skip
            return true;
        }

        reclaim_for(key);

        // add in A1-in & in in_htable
        in.push(slow_get_page(key));
        in_htable.add(in.back());

        return false;
    }

    void reclaim_for(KeyT key) {
        // to be continued.
        return;
    }

    cache_t(std::size_t size): size_(size) { }
};
