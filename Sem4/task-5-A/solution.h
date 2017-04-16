#pragma once

#include "spinlock_pause.h"

#include <iostream>
#include <atomic>
#include <thread>

//////////////////////////////////////////////////////////////////////

/* scalable and fair MCS (Mellor-Crummy, Scott) spinlock implementation
 *
 * usage:
 * {
 *   MCSSpinLock::Guard guard(spinlock); // spinlock acquired
 *   ... // in critical section
 * } // spinlock released
 */

template <template <typename T> class Atomic = std::atomic>
class MCSSpinLock {
 public:
  class Guard {
   public:
    explicit Guard(MCSSpinLock& spinlock)
        : spinlock_(spinlock) {
          Acquire();
        }

    ~Guard() {
      Release();
    }

   private:
    void Acquire() {
      Guard* prev_tail = this->spinlock_.wait_queue_tail_.exchange(this);
      if (prev_tail != nullptr) {
        prev_tail->next_.store(this);
      } else {
        this->is_owner_.store(true);
      }
      while(!this->is_owner_.load()) {
          // Ждём пока передадут владение.
      }
    }

    void Release() {
      if (this->next_.load() == nullptr) {
        Guard* tmp = this;
        if(spinlock_.wait_queue_tail_.compare_exchange_strong(tmp, nullptr)) {
          return ;
        }
        while(this->next_.load() == nullptr) {
          // Ждём линковку
        }
      }
      this->next_.load()->is_owner_.store(true);
    }

   private:
    MCSSpinLock& spinlock_;
    Atomic<bool> is_owner_{false};
    Atomic<Guard*> next_{nullptr};
  };

 private:
  Atomic<Guard*> wait_queue_tail_{nullptr};
};


/////////////////////////////////////////////////////////////////////

// alias for checker
template <template <typename T> class Atomic = std::atomic>
using SpinLock = MCSSpinLock<Atomic>;

/////////////////////////////////////////////////////////////////////



//main() {
  
  //MCSSpinLock<> spinlock;
//  {
 //   MCSSpinLock::Guard guard(spinlock); // spinlock acquired
  
 // } // spinlock released
//}
