#ifndef LIMONP_CLOSURE_HPP
#define LIMONP_CLOSURE_HPP

namespace limonp {

class ITask {
 public:
  virtual ~ITask() {
  }
  virtual void Run() = 0;
}; // class ITask

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

} // namespace limonp

#endif // LIMONP_CLOSURE_HPP
