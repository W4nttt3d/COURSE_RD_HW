#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <mutex>
#include <chrono>

std::mutex result_mutex;

void partial_sum(const std::vector<int>& vec, size_t start, size_t end, int& result)
{
    int local_sum = std::accumulate(vec.begin() + start, vec.begin() + end, 0);

    std::lock_guard<std::mutex> guard(result_mutex);
    result += local_sum;
}

int sum_single_thread(const std::vector<int>& vec) 
{
    return std::accumulate(vec.begin(), vec.end(), 0);
}

int sum_multiple_threads(const std::vector<int>& vec, unsigned int num_threads) 
{
    int result = 0; 
    std::vector<std::thread> threads;
    size_t chunk = vec.size() / num_threads;

    for (unsigned int i = 0; i < num_threads; ++i) 
    {
        size_t start = i * chunk;
        size_t end = (i == num_threads - 1) ? vec.size() : start + chunk;
        threads.emplace_back(partial_sum, std::ref(vec), start, end, std::ref(result));
    }

    for (auto& t : threads) 
    {
        t.join();
    }

    return result;
}

int main() 
{
    std::vector<int> sizes = { 10000, 100000, 1000000, 10000000, 100000000 };
    std::vector<unsigned int> thread_counts = { 2, std::thread::hardware_concurrency(), 2 * std::thread::hardware_concurrency() };

    for (auto size : sizes) {
        std::vector<int> vec(size, 1);

        std::cout << "Testing vector size: " << size << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        int sum = sum_single_thread(vec);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Single thread sum: " << sum << ", Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mcs\n";

        for (auto num_threads : thread_counts) 
        {
            start = std::chrono::high_resolution_clock::now();
            sum = sum_multiple_threads(vec, num_threads);
            end = std::chrono::high_resolution_clock::now();
            std::cout << num_threads << " threads sum: " << sum << ", Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mcs\n";
        }

        std::cout << std::endl;
    }
}
