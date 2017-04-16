#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class Robot {
 public:
  explicit Robot()
      : foot_(1) {}
  void StepLeft() {
    std::unique_lock<std::mutex> lock(mtx_);
    while(foot_ != 1) {
      cv_foot_.wait(lock, [this]{return foot_ == 1;});
    }
    std::cout << "left\n";
    foot_ = 1 - foot_;
    cv_foot_.notify_one();
    
  }
  void StepRight() {
    std::unique_lock<std::mutex> lock(mtx_);
    while(foot_ != 0) {
      cv_foot_.wait(lock, [this]{return foot_ == 0;});
    }
    std::cout << "right\n";
    foot_ = 1 - foot_;
    cv_foot_.notify_one();
    
  }

 private:
  char foot_;
  std::condition_variable cv_foot_;
  std::mutex mtx_;
};

int main() {   
  const size_t steps = 3;   
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
