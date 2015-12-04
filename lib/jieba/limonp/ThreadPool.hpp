#ifndef LIMONP_THREAD_POOL_HPP
#define LIMONP_THREAD_POOL_HPP

#include "Thread.hpp"
#include "BlockingQueue.hpp"

namespace limonp {
class ITask {
 public:
  virtual void run() = 0;
  virtual ~ITask() {}
};

template <class TaskType>
ITask* CreateTask() {
  return new TaskType();
}
template <class TaskType, class ArgType>
ITask* CreateTask(ArgType arg) {
  return new TaskType(arg);
}
template <class TaskType, class ArgType0, class ArgType1>
ITask* CreateTask(ArgType0 arg0, ArgType1 arg1) {
  return new TaskType(arg0, arg1);
}
template <class TaskType, class ArgType0, class ArgType1, class ArgType2>
ITask* CreateTask(ArgType0 arg0, ArgType1 arg1, ArgType2 arg2) {
  return new TaskType(arg0, arg1, arg2);
}

//class ThreadPool;
class ThreadPool: NonCopyable {
 private:
  class Worker: public IThread {
   private:
    ThreadPool * ptThreadPool_;
   public:
    Worker(ThreadPool* pool): ptThreadPool_(pool) {
      assert(ptThreadPool_);
    }
    virtual ~Worker() {
    }
   public:
    virtual void run() {
      while(true) {
        ITask * task = ptThreadPool_->queue_.pop();
        if(task == NULL) {
          break;
        }
        try {
          task->run();
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
  };
 private:
  friend class Worker;
 private:
  vector<IThread*> threads_;
  BoundedBlockingQueue<ITask*> queue_;
  //mutable MutexLock mutex_;
  //Condition isEmpty__;
 public:
  ThreadPool(size_t threadNum, size_t queueMaxSize): threads_(threadNum), queue_(queueMaxSize) { //, mutex_(), isEmpty__(mutex_)
    assert(threadNum);
    assert(queueMaxSize);
    for(size_t i = 0; i < threads_.size(); i ++) {
      threads_[i] = new Worker(this);
    }
  }
  ~ThreadPool() {
    for(size_t i = 0; i < threads_.size(); i ++) {
      queue_.push(NULL);
    }
    for(size_t i = 0; i < threads_.size(); i ++) {
      threads_[i]->join();
      delete threads_[i];
    }
  }

 public:
  void start() {
    for(size_t i = 0; i < threads_.size(); i++) {
      threads_[i]->start();
    }
  }

  void add(ITask* task) {
    assert(task);
    queue_.push(task);
  }
};
}

#endif
