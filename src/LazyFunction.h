//
// Created by matt on 12/09/2019.
//

#ifndef NOVELRT_LAZYFUNCTION_H
#define NOVELRT_LAZYFUNCTION_H
#include <functional>
#include <memory>

namespace NovelRT {
template<typename T>
class LazyFunction {
public:
  LazyFunction(std::function<T()> delegate);
  LazyFunction(T eagerStartValue, std::function<T()> delegate);
  T getActual();
  void reset();
private:
  std::function<T()> _delegate;
  std::unique_ptr<T> _actual = nullptr;
};

template<typename T>
LazyFunction<T>::LazyFunction(std::function<T()> delegate) : _delegate(delegate) {}

template <typename T>
LazyFunction<T>::LazyFunction(T eagerStartValue, std::function<T()> delegate) : _delegate(delegate), _actual(std::make_unique<T>(eagerStartValue)) {}

template <typename T>
T LazyFunction<T>::getActual() {
  if(_actual == nullptr) _actual = std::make_unique<T>(_delegate());

  return *_actual;
}

template <typename T>
void LazyFunction<T>::reset() {
  _actual.reset();
}

}

#endif //NOVELRT_LAZYFUNCTION_H
