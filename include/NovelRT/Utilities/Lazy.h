// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_UTILITIES_LAZY_H
#define NOVELRT_UTILITIES_LAZY_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Utilities {
  template<typename T, typename Deleter = std::default_delete<T>>
  class Lazy {
  private:
    std::function<T()> _delegate;
    std::unique_ptr<T, Deleter> _actual;

  public:
    Lazy(std::function<T()> delegate) : _delegate(delegate), _actual(nullptr) {}
    Lazy(T eagerStartValue, std::function<T()> delegate) : _delegate(delegate), _actual(std::unique_ptr<T, Deleter>(new T(eagerStartValue))) {}

    T& getActual() {
      if (!isCreated()) {
        _actual = std::unique_ptr<T, Deleter>(new T(_delegate()));
      }

      return *_actual;
    }

    void reset() {
      _actual.reset();
    }

    bool isCreated() const {
      return _actual != nullptr;
    }
  };
}
#endif //NOVELRT_UTILITIES_LAZY_H
