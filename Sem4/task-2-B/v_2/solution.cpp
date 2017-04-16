#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class Semaphor {
 public:
  Semaphor& operator=(const Semaphor&) = delete;
  Semaphor(const Semaphor&) = delete;
  explicit Semaphor(int count)
      : count_(count) {}
  void wait() {
    std::unique_lock<std::mutex> lock(mtx_);
    while(count_ == 0) {
      cv_count_.wait(lock);
    }
    count_--;
  }
  void notify() {
    std::unique_lock<std::mutex> lock(mtx_);
    count_++;
    cv_count_.notify_one();
  }

 private:
  int count_;
  std::mutex mtx_;
  std::condition_variable cv_count_;
};


class Robot {
 public:
  explicit Robot()
      : left_sem_(1),
        right_sem_(0) {}
  void StepLeft() {
    left_sem_.wait();
    std::cout << "left\n";
    right_sem_.notify();
  }
  void StepRight() {
    right_sem_.wait();
    std::cout << "right\n";
    left_sem_.notify();
  }

 private:
  Semaphor left_sem_;
  Semaphor right_sem_;
};

int main() {   
  const size_t steps = 10;   
  Robot robot;   
  std::thread left_thread([&robot] {   
  for (size_t i = 0; i < steps; ++i)   
    robot.StepLeft();   
  });   
  std::thread right_thread([&robot] {   
  for (size_t i = 0; i < steps; ++i)   
    robot.StepRight();   
  });   
  left_thread.join();   
  right_thread.join();   
}
