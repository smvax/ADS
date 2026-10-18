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
  inline void push(const T&);
  inline T pop();
  const T& top() const;
};

template <class T>
TStackOnMass<T>::TStackOnMass(size_t size) {
  _data = new T[size];
  _size = size;
  _top = -1;
}
template <class T>
TStackOnMass<T>::TStackOnMass(const TStackOnMass& other) {
  _data = new T[other._size];
  _size = other._size;
  _top = other._top;
  if (_top != -1) {
    for (size_t i = 0; i <= _top; ++i) {
      _data[i] = other._data[i];
    }
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
inline void TStackOnMass<T>::push(const T& val) {
  if (is_full()) {
    throw std::out_of_range("ERROR: Stack overflow, can't push!");
  }
  _data[++_top] = val;
}
template <class T>
inline T TStackOnMass<T>::pop() {
  if (is_empty()) {
    throw std::out_of_range("ERROR: Stack is empty, can't pop!");
  }
  return _data[_top--];
}
template <class T>
const T& TStackOnMass<T>::top() const {
  if (is_empty()) {
    throw std::out_of_range("ERROR: Stack is empty! Can't get top!");
  }
  return _data[_top];
}