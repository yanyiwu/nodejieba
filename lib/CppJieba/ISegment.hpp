#ifndef CPPJIEBA_ISEGMENT_H
#define CPPJIEBA_ISEGMENT_H

namespace CppJieba {

class ISegment {
 public:
  virtual ~ISegment() {
  }
  virtual bool cut(const string& str, vector<string>& res) const = 0;
};

} // namespace CppJieba

#endif // CPPJIEBA_ISEGMENT_H
