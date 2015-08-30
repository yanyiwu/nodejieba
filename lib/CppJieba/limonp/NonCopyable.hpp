/************************************
 ************************************/
#ifndef LIMONP_NONCOPYABLE_H
#define LIMONP_NONCOPYABLE_H

#include <iostream>
#include <string>

namespace limonp {
class NonCopyable {
 protected:
  NonCopyable() {};
  ~NonCopyable() {};
 private:
  NonCopyable(const NonCopyable& );
  const NonCopyable& operator=(const NonCopyable& );
};
}

#endif
