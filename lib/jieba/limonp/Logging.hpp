#ifndef LIMONP_LOGGING_HPP
#define LIMONP_LOGGING_HPP

#include <sstream>
#include <iostream>
#include <cassert>
#include <cstdlib>

#ifdef LOG
#error "LOG has been defined already"
#endif // LOG
#ifdef CHECK
#error "CHECK has been defined already"
#endif // CHECK

#define LOG(level) limonp::Logger(limonp::level, __FILE__, __LINE__).Stream() 
#define CHECK(exp) if(!(exp)) LOG(FATAL) << "exp: ["#exp << "] false. "

namespace limonp {

enum {
  DEBUG = 0, 
  INFO = 1, 
  WARNING = 2, 
  ERROR = 3, 
  FATAL = 4,
}; // enum

static const char * LOG_LEVEL_ARRAY[] = {"DEBUG","INFO","WARN","ERROR","FATAL"};
static const char * LOG_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";

class Logger {
 public:
  Logger(size_t level, const char* filename, int lineno)
   : level_(level) {
#ifdef LOGGING_LEVEL
     if (level_ < LOGGING_LEVEL) {
       return;
     }
#endif
    assert(level_ <= sizeof(LOG_LEVEL_ARRAY)/sizeof(*LOG_LEVEL_ARRAY));
    char buf[32];
    time_t now;
    time(&now);
    strftime(buf, sizeof(buf), LOG_TIME_FORMAT, localtime(&now));
    stream_ << buf 
      << " " << filename 
      << ":" << lineno 
      << " " << LOG_LEVEL_ARRAY[level_] 
      << " ";
  }
  ~Logger() {
#ifdef LOGGING_LEVEL
     if (level_ < LOGGING_LEVEL) {
       return;
     }
#endif
    std::cerr << stream_.str() << std::endl;
    if (level_ == FATAL) {
      abort();
    }
  }

  std::ostream& Stream() {
    return stream_;
  }

 private:
  std::ostringstream stream_;
  size_t level_;
}; // class Logger

} // namespace limonp

#endif // LIMONP_LOGGING_HPP
