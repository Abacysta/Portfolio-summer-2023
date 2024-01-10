#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <condition_variable>

class SimpleThreadPool {
public:
    SimpleThreadPool(const SimpleThreadPool & ) = delete;
    SimpleThreadPool &  operator = (const SimpleThreadPool &  ) = delete;
    explicit SimpleThreadPool(std::size_t threadCount) : m_threadCount(threadCount), stop(false) {
        for (size_t i = 0; i < threadCount; ++i) {
            threads.emplace_back(
                [this] {
                    while (true) {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->mut);
                            this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                            if (this->stop && this->tasks.empty()) return;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }

                        task();
                    }
                }
            );
        }
    }

    ~SimpleThreadPool() {
        Destroy();
    }

    template<typename Fnc_T>
    auto Post(Fnc_T task) -> std::future<decltype(task())> {
        using ReturnType = decltype(task());
        auto wrapper = std::make_shared<std::packaged_task<ReturnType()>>(std::move(task));
        std::future<ReturnType> res = wrapper->get_future();

        {
            std::unique_lock<std::mutex> lock(mut);
            tasks.emplace([wrapper]() { (*wrapper)(); });
        }

        condition.notify_one();
        return res;
    }

    void Destroy() {
        {
            std::unique_lock<std::mutex> lock(mut);
            stop = true;
        }

        condition.notify_all();
        for (std::thread& worker : threads) {
            worker.join();
        }
    }

private:
    size_t m_threadCount;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::condition_variable condition;
    std::mutex mut;
    bool stop;
};

int main() {
    SimpleThreadPool pool(5);

    auto future1 = pool.Post([]() {
        std::cout << "Task 1 running on thread: " << std::this_thread::get_id() << std::endl;
        return 1;
        });

    auto future2 = pool.Post([]() {
        std::cout << "Task 2 running on thread: " << std::this_thread::get_id() << std::endl;
        return 2;
        });

    std::cout << "Task 1 result: " << future1.get() << std::endl;
    std::cout << "Task 2 result: " << future2.get() << std::endl;

    return 0;
}
