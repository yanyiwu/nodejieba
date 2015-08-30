#ifndef LIMONP_COLOR_PRINT_HPP
#define LIMONP_COLOR_PRINT_HPP

#include <string>
#include <stdarg.h>

namespace limonp {
using std::string;

enum COLOR {
  BLACK = 30,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  PURPLE
};

static void ColorPrintln(enum COLOR color, const char * fmt, ...) {
  va_list ap;
  printf("\033[0;%dm", color);
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  printf("\033[0m\n"); // if not \n , in some situation , the next lines will be set the same color unexpectedly
}

#if 0
static void ColorPrint(const string& str, enum COLOR color = GREEN) {
  printf("\033[0;%dm%s\033[0m", color, str.c_str());
}
#endif

} // namespace limonp

#endif
