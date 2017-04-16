#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

template <class ConditionVariable = std::condition_variable>  
class CyclicBarrier {
 private:
  const size_t max_threads_;
  size_t curr_threads_;
  char end_;
  ConditionVariable cv_full_;
  std::mutex mtx_;
  int curr_eval_;
 public:
  CyclicBarrier(const CyclicBarrier&) = delete;
  CyclicBarrier& operator=(const CyclicBarrier&) = delete;
  explicit CyclicBarrier(size_t max_threads)
      : max_threads_(max_threads),
        curr_threads_(0),
        curr_eval_(0) {}
  void Pass() {
    // Захват мьютекса для безопасного изменения curr_threads.
    std::unique_lock<std::mutex> lock(mtx_);
    curr_threads_++;
    // Пора разблокировать потоки?
    if(curr_threads_ % max_threads_ == 0) { 
      curr_eval_++;
      cv_full_.notify_all();
    } else {
      // Уход потока в ожидание и освобождение мьютекса.
      int curr_eval = curr_eval_;
      cv_full_.wait(lock, [this, curr_eval]{return curr_eval < curr_eval_;});
    }
  }
  // Тут освобождается мьютекс после последнего потока.
};

CyclicBarrier<> bar(3);

void test(size_t i) {
  std::cout << i;
  bar.Pass();
  std::cout << " все дошли ";
}

main() {
  std::thread t1(test, 1);
  std::thread t2(test, 2);
  t1.join();
  t2.join();
}
