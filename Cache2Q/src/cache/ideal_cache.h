#pragma once

#include <cstddef>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <cassert>

#include <vector>

#include <cstdio>

template <typename T, typename KeyT>
struct ideal_cache_t {
private:
    // there I choose list to remove exactly that element
    std::list<T> cache_;
    std::size_t  size_;

    using ListTIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListTIt> htable_;

    // helping functions
    T    (&slow_get_page)(KeyT  key);
    KeyT (&     get_key) (T    page);

    std::vector<T> &array_;

public:
    ideal_cache_t(std::size_t size, KeyT (&get_key)(T page),  T (&slow_get_page)(KeyT key), std::vector<T> &array):
                 size_(size), get_key(get_key), slow_get_page(slow_get_page), array_(array) {
        // cache...
    }

    std::size_t count_hits() {
        std::size_t hits = 0;

        for (std::size_t index = 0; index < array_.size(); ++index) {
            T page = array_[index];
            KeyT key = get_key(page);

            auto hit = htable_.find(key);
            if (hit != htable_.end()) {
                assert(hit->second != cache_.end());

                ++hits;
                continue;
            }

            if (!full()) {
                cache_.push_front(page);
                htable_[key] = cache_.begin();
                continue;
            }

            typename std::list<T>::iterator element_to_remove = cache_.begin();

            for (auto candidate = cache_.begin(); candidate != cache_.end(); ++candidate) {
                KeyT candidate_key = get_key(*candidate);

                for (std::size_t find_index = index; find_index < array_.size(); ++find_index) {
                    if (candidate_key == get_key(array_[find_index])) {
                        element_to_remove = candidate;
                    }
                }
            }

            cache_.erase(element_to_remove);
            htable_.erase(get_key(*element_to_remove));

            // slow get page
            cache_.push_front(slow_get_page(key));
            htable_[key] = cache_.begin();
        }

        return hits;
    }

    bool full() {
        return cache_.size() == size_;
    }

    void dump() {
        fprintf(stderr, "\n-----CACHE DUMP-----\n\n");

        fprintf(stderr, "-----CACHE DUMP END-----\n");
    }
};
