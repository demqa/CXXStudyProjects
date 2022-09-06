#include <iostream>
#include "cache/cache.h"

typedef int page_t;
typedef int key_t;

key_t get_key(page_t page) {
    return page;
}

page_t slow_get_page(key_t key) {
    return key;
}

int main() {
    // cache_t<int, int (*)(int), int, int (*)(int)> cache(5, get_key);
    //
    // cache.lookup_update(14, slow_get_page);

    std::unordered_map<int, int> base;

    std::vector<int> example;

    example.push_back(1);
    example.push_back(2);
    example.push_back(3);
    example.push_back(4);

    std::cout << example.front() << "\n";

    base[5] = 6;

    std::cout << base.find(5)->first << " " << base.find(5)->second << "\n";
    return 0;
}
