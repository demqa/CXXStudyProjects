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
    size_t cache_size = 0, number_of_elements = 0;
    std::cin >> cache_size >> number_of_elements;

    cache_t<int, int> cache(cache_size, get_key, slow_get_page);

    size_t number_of_hits = 0;
    for (size_t index = 0; index < number_of_elements; ++index) {
        int current_elem = 0;
        std::cin >> current_elem;

        bool hit = cache.lookup_update(current_elem);
        if (hit) number_of_hits++;

        // std::cout << "step №" << index << " " << (hit ? "hit" : "miss") << "\n";
        // cache.dump();
        // std::cout << "\n\n";
    }

    std::cout << number_of_hits << "\n";

    return 0;
}
