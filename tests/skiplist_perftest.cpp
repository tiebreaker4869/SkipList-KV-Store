#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <cstdint>
#include <thread>

#include "skiplist.hpp"

int main(int argc, char** argv) {
    using Key = uint64_t;
    using Value = uint64_t;
    
    constexpr int N = 500000;
    
    constexpr int kThreadCount = 8;

    SkipList<Key, Value> skip_list{};

    auto random_rw_func = [&]() {
        for (int i = 0; i < N; i ++) {
            uint64_t random_number = rand();
            int op = random_number % 3;
            Key key = random_number;
            Value value = random_number;
            switch (op)
            {
            case 0: // Insert
                skip_list.Insert(key, value);
                break;
            case 1: // Delete
                skip_list.Delete(key);
                break;
            case 2: // Get
                skip_list.Get(key);
            default:
                break;
            }
        }
    };

    std::vector<std::thread> threads{};

    std::cout << "Perf Test for SkipList start...>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < kThreadCount; i ++) {
        threads.emplace_back(random_rw_func);
    }

    for (int i = 0; i < kThreadCount; i ++) {
        threads[i].join();
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Total Execution Time: " << duration_ms.count() << " ms.\n";

    std::cout << "Total Operations: " << kThreadCount * N << "\n";

    std::cout << "QPS: " << kThreadCount * N / (duration_ms.count() / 1000) << "\n";
    
    return 0;
}