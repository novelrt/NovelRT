// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_UTILITIES_LAZY_H
#define NOVELRT_UTILITIES_LAZY_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Utilities {
  template<typename T>
  class Lazy {
  private:
    std::function<T()> _delegate;
    T _actual;
    bool _isCreated;

  public:
    Lazy(std::function<T()> delegate) : _delegate(delegate), _actual(), _isCreated(false) {}
    Lazy(T eagerStartValue, std::function<T()> delegate) : _delegate(delegate), _actual(eagerStartValue), _isCreated(true) {}

    T& getActual()
    {
      if (!isCreated()) {
        _actual = _delegate();
        _isCreated = true;
      }

      return _actual;
    }

    void reset() {
      _isCreated = false;
    }

    bool isCreated() const {
      return _isCreated;
    }
  };

  template<typename T>
  class Lazy<std::unique_ptr<T>> {
  private:
    std::function<T*()> _delegate;
    std::unique_ptr<T> _actual;

  public:
    Lazy(std::function<T*()> delegate) : _delegate(delegate), _actual(std::unique_ptr<T>(nullptr)) {}

    T* getActual()
    {
      if (!isCreated()) {
        _actual = std::unique_ptr<T>(_delegate());
      }

      return _actual.get();
    }

    void reset() {
      _actual = nullptr;
    }

    bool isCreated() const {
      return _actual != nullptr;
    }
  };

  template<typename T, typename Deleter>
  class Lazy<std::unique_ptr<T, Deleter>> {
  private:
    std::function<T*()> _delegate;
    std::unique_ptr<T, Deleter> _actual;

  public:
    Lazy(std::function<T*()> delegate, Deleter deleter) : _delegate(delegate), _actual(std::unique_ptr<T, Deleter>(nullptr, deleter)) {}

    T* getActual()
    {
      if (!isCreated()) {
        _actual = std::unique_ptr<T, Deleter>(_delegate(), _actual.get_deleter());
      }

      return _actual.get();
    }

    void reset() {
      _actual = nullptr;
    }

    bool isCreated() const {
      return _actual != nullptr;
    }
  };
}
#endif //NOVELRT_UTILITIES_LAZY_H
