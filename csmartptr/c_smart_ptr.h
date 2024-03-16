/* copied from envoy project */

#include <memory>

template <class T, void (*deleter)(T *)>
class CSmartPtr : public std::unique_ptr<T, void (*)(T *)> {
public:
  CSmartPtr() : std::unique_ptr<T, void (*)(T *)>(nullptr, deleter) {}
  CSmartPtr(T *object) : std::unique_ptr<T, void (*)(T *)>(object, deleter) {}
};
