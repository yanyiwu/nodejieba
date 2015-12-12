#ifndef LIMONP_THREAD_POOL_HPP
#define LIMONP_THREAD_POOL_HPP

#include "Thread.hpp"
#include "BlockingQueue.hpp"
#include "BoundedBlockingQueue.hpp"
#include "Closure.hpp"

namespace limonp {

using namespace std;

//class ThreadPool;
class ThreadPool: NonCopyable {
 public:
  class Worker: public IThread {
   public:
    Worker(ThreadPool* pool): ptThreadPool_(pool) {
      assert(ptThreadPool_);
    }
    virtual ~Worker() {
    }

    virtual void Run() {
      while(true) {
        ITask * task = ptThreadPool_->queue_.Pop();
        if(task == NULL) {
          break;
        }
        try {
          task->Run();
        } catch(std::exception& e) {
          cerr << "file:" << __FILE__ 
               << ", line:" << __LINE__ 
               << ", " << e.what() << endl;
        } catch(...) {
          cerr << "file:" << __FILE__ 
               << ", line:" << __LINE__ 
               << ", unknown exception." << endl;
        }
        delete task;
      }
    }
   private:
    ThreadPool * ptThreadPool_;
  }; // class Worker

  ThreadPool(size_t threadNum, size_t queueMaxSize)
    : threads_(threadNum), 
      queue_(queueMaxSize) {
    assert(threadNum);
    assert(queueMaxSize);
    for(size_t i = 0; i < threads_.size(); i ++) {
      threads_[i] = new Worker(this);
    }
  }
  ~ThreadPool() {
    for(size_t i = 0; i < threads_.size(); i ++) {
      queue_.Push(NULL);
    }
    for(size_t i = 0; i < threads_.size(); i ++) {
      threads_[i]->Join();
      delete threads_[i];
    }
  }

  void Start() {
    for(size_t i = 0; i < threads_.size(); i++) {
      threads_[i]->Start();
    }
  }

  void Add(ITask* task) {
    assert(task);
    queue_.Push(task);
  }

 private:
  friend class Worker;

  vector<IThread*> threads_;
  BoundedBlockingQueue<ITask*> queue_;
}; // class ThreadPool

} // namespace limonp

#endif // LIMONP_THREAD_POOL_HPP
