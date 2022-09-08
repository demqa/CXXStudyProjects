#pragma once

#include <list>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <cassert>

#include <cstdio>

template <typename T, typename KeyT>
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

    // helping functions
    T    (&slow_get_page)(KeyT  key);
    KeyT (&     get_key) (T    page);


    template <typename U>
    void add_item(U &container, std::unordered_map<KeyT, typename U::iterator> &htable, T &page) {
        container.push_front(page);
        htable[get_key(page)] = container.begin();
    }

    template <typename U>
    void remove_item(U &container, std::unordered_map<KeyT, typename U::iterator> &htable, KeyT &key) {
        container.pop_back();
        htable.erase(key);
    }


    void reclaim_for_cache() {
        if (cache_.size() >= size_) {
            remove_item(cache_, htable, get_key(cache_.back()));
        }
    }

    void reclaim_for_in() {
        if (in.size() >= in_maxsize) {
            T    coldest_page = in.back();
            KeyT coldest_key  = get_key(coldest_page);
            remove_item(in, in_htable, coldest_key);

            if (out.size() >= out_maxsize) {
                remove_item(out, out_htable, out.back());
            }

            add_item(out, out_htable, coldest_key);
        }
    }


public:
    cache_t(std::size_t size, KeyT (&get_key)(T page),  T (&slow_get_page)(KeyT key)):
                 size_(size), get_key(get_key), slow_get_page(slow_get_page) {
        // these 2Q cache parameters are optimal as Algorithm authors
        // discovered via number of experiments.

         in_maxsize = std::max(size / 4, 1LU);
        out_maxsize = std::max(size / 2, 1LU);
    }

    bool lookup_update(KeyT key) {
        auto hit = htable.find(key);
        if (hit != htable.end()) { // found in Am
            auto elem_it = hit->second;
            if (elem_it != cache_.begin()) { // move elem to head
                cache_.splice(cache_.begin(), cache_, elem_it, std::next(elem_it));
            }

            return true;
        }

        auto in_hit = in_htable.find(key);
        if (in_hit != in_htable.end()) { // found in A1-in
            assert(in_hit->second != in.end());

            return true;
        }

        auto out_hit = out_htable.find(key);
        if (out_hit != out_htable.end()) { // found in A1-out
            assert(out_hit->second != out.end());

            reclaim_for_cache();

            // add in Am
            T page = slow_get_page(key);
            add_item(cache_, htable, page);

            return false;
        }

        reclaim_for_in();

        // add in A1-in
        T page = slow_get_page(key);
        add_item(in, in_htable, page);

        return false;
    }

    bool full() {
        return cache_.size() == size_;
    }

    void dump() {
        fprintf(stderr, "\n-----CACHE DUMP-----\n\n");

        fprintf(stderr, "Am cache %lu/%lu:\n", cache_.size(), size_);
        for (auto elem: cache_)
            fprintf(stderr, "%d ", elem);
        fprintf(stderr, "\n\n");

        fprintf(stderr, "A1-in %lu/%lu:\n", in.size(), in_maxsize);
        for (auto elem: in)
            fprintf(stderr, "%d ", elem);
        fprintf(stderr, "\n\n");

        fprintf(stderr, "A1-out %lu/%lu:\n", out.size(), out_maxsize);
        for (auto elem: out)
            fprintf(stderr, "%d ", elem);
        fprintf(stderr, "\n\n");

        fprintf(stderr, "-----CACHE DUMP END-----\n");
    }
};
