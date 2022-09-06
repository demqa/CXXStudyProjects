#pragma once

#include <list>
#include <queue>
#include <unordered_map>

template <typename T, typename KeyT, typename GetKeyT>
struct cache_t {
    private:

    // Am. It is default LRU.
    std::list<T> cache_;
    std::size_t  size_;

    using ListTIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListTIt> htable;

    // A1-in
    std::deque<T>    in;
    std::size_t      in_maxsize;

    using DequeTIt = typename std::deque<T>::iterator;
    std::unordered_map<KeyT, DequeTIt> in_htable;

    // A1-out
    std::deque<KeyT> out;
    std::size_t      out_maxsize;

    using DequeKeyTIt = typename std::deque<KeyT>::iterator;
    std::unordered_map<KeyT, DequeKeyTIt> out_htable;

    T    (&slow_get_page)(KeyT  key);
    KeyT (&     get_key) (T    page);

    public:

    bool lookup_update(KeyT key) {
        auto hit = htable.find(key);
        if (hit != htable.end()) { // found in Am
            auto elem_it = hit->second;
            if (elem_it != cache_.begin()) {
                // move elem to head
                cache_.splice(cache_.begin(), cache_, elem_it, std::next(elem_it));
            }

            return true;
        }

        auto out_hit = out_htable.find(key);
        if (out_hit != out_htable.end()) { // found in A1-out
            assert(out_hit->second != out.end());

            reclaim_for();

            // add in Am and in htable
            T page = slow_get_page(key);
            cache_.push_front(page);
            htable[get_key(page)] = cache_.begin();

            return true;
        }

        auto in_hit = in_htable.find(key);
        if (in_hit != in_htable.end()) { // found in A1-in
            assert(in_hit->second != in.end());

            // skip
            return true;
        }

        reclaim_for();

        // add in A1-in & in in_htable
        T page = slow_get_page(key);
        in.push_front(page);
        in_htable[get_key(page)] = in.begin();

        return false;
    }

    void reclaim_for() {
        if (in.size() >= in_maxsize) {
            T coldest_in_page = in.pop();

            if (out.size() >= out_maxsize) {
                KeyT extra_page_key = out.pop();
                out_htable.erase(extra_page_key);
            }

            KeyT key = get_key(coldest_in_page);
            out.push_front(key);
            out_htable[key] = out.begin();
        }

        if (cache_.size() >= size_) {
            T coldest_cache_page = cache_.pop();
            htable.erase(get_key(coldest_cache_page));
        }
    }

    cache_t(std::size_t size, GetKeyT get_key,  T (&slow_get_page)(KeyT)):
                 size_(size), get_key(get_key), slow_get_page(slow_get_page) {
        // change it to optimal values
        out_maxsize = size;
        in_maxsize  = size;
    }
};
