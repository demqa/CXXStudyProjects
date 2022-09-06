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

    // std::size_t n = 0;
    // std::cin >> n;

    cache_t<int, int> cache(3, get_key, slow_get_page);

    std::cout << cache.lookup_update(14) << "\n";
    std::cout << cache.lookup_update(15) << "\n";
    std::cout << cache.lookup_update(16) << "\n";
    std::cout << cache.lookup_update(16) << "\n";
    std::cout << cache.lookup_update(16) << "\n";
    std::cout << cache.lookup_update(14) << "\n";
    std::cout << cache.lookup_update(15) << "\n";

    return 0;
}
