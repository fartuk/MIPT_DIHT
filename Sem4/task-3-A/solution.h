#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <deque>

template<class T, class Container = std::deque<T>>
class BlockingQueue {
 public:
  BlockingQueue(const BlockingQueue&) = delete;
  BlockingQueue& operator=(const BlockingQueue&) = delete;
  explicit BlockingQueue(const size_t& max_size)
      : max_size_(max_size),
        is_turn_(1) {}

  void Put(T&& item) {
        // Захват мьютекса для безопасного изменения curr_threads.
    std::unique_lock<std::mutex> lock(mtx_);
    if (!is_turn_) {
      throw std::runtime_error("s");
    } else {
        // Ожидание возможности положить в очередь или выключения очереди.
      cv_full_.wait(lock, [this]{return (queue_.size() < max_size_) || !is_turn_;});
      if (is_turn_) {
        queue_.push_back(std::move(item));
        cv_empty_.notify_one();
      }
    }
  }
  char Get(T& item) {
    std::unique_lock<std::mutex> lock(mtx_);
    if (!is_turn_) {
      return 0;
    } else {
      cv_empty_.wait(lock, [this]{return queue_.size() > 0 || !is_turn_;});
      if (is_turn_) {
        item = std::move(queue_.front());
        queue_.pop_front();
        if (queue_.size() == max_size_ - 1) {
          cv_full_.notify_all();
        } 
      }
      return 1;
    }
  }
  void Shutdown() {
    std::unique_lock<std::mutex> lock(mtx_);
    is_turn_ = 0;
    cv_full_.notify_all();
    cv_empty_.notify_all();
  }

 private:
  const size_t max_size_;
  char is_turn_;
  Container queue_;
  std::condition_variable cv_empty_;
  std::condition_variable cv_full_;
  std::mutex mtx_;
};
