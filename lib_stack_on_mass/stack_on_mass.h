// Copyright 2024 Marina Usova

#include <stdexcept>

template <class T>
class TStackOnMass {
  T* _data;
  size_t _size;
  int _top;

 public:
  TStackOnMass(size_t);
  TStackOnMass(const TStackOnMass&);
  ~TStackOnMass();

  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;
  inline size_t size() const noexcept;
  inline T& top();
  inline void push(const T&);
  inline T pop();
};

template <class T>
TStackOnMass<T>::TStackOnMass(size_t size) {
  if (size == 0) {
    throw std::invalid_argument("ERROR: Stack size can't be 0!");
  }
  _data = new T[size];
  _size = size;
  _top = -1;
}
template <class T>
TStackOnMass<T>::TStackOnMass(const TStackOnMass& other)
    : _size(other._size), _top(other._top) {
  _data = new T[_size];
  for (size_t i = 0; i <= _top; ++i) {
    _data[i] = other._data[i]; // Would not go if _top == -1
  }
}
template <class T>
TStackOnMass<T>::~TStackOnMass() {
  delete[] _data;
}

template <class T>
inline bool TStackOnMass<T>::is_empty() const noexcept {
  return _top == -1;
}
template <class T>
inline bool TStackOnMass<T>::is_full() const noexcept {
  return _top == _size - 1;
}
template <class T>
inline size_t TStackOnMass<T>::size() const noexcept {
  return _size;
}
template <class T>
inline T& TStackOnMass<T>::top() {
  if (is_empty()) {
    throw std::underflow_error("ERROR: Stack underflow, can't get top!");
  }
  return _data[_top];
}
template <class T>
inline void TStackOnMass<T>::push(const T& val) {
  if (is_full()) {
    throw std::overflow_error("ERROR: Stack overflow, can't push!");
  }
  _data[++_top] = val;
}
template <class T>
inline T TStackOnMass<T>::pop() {
  if (is_empty()) {
    throw std::underflow_error("ERROR: Stack underflow, can't pop!");
  }
  return _data[_top--];
}