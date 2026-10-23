// Copyright 2024 Marina Usova

#include <stdexcept>

template <class T>
class TQueueOnMass {
  T* _data;
  size_t _size;
  size_t _front;
  size_t _back;
  bool _is_empty;

 public:
  TQueueOnMass(size_t);
  TQueueOnMass(const TQueueOnMass&);
  ~TQueueOnMass();

  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;
  inline size_t size() const noexcept;
  inline T& front();
  inline void push(const T&);
  inline T pop();
};

template <class T>
TQueueOnMass<T>::TQueueOnMass(size_t size) {
  if (size == 0) {
    throw std::invalid_argument("ERROR: Queue size can't be 0!");
  }
  _size = size;
  _data = new T[size];
  _front = 0;
  _back = 0;
  _is_empty = true;
}
template <class T>
TQueueOnMass<T>::TQueueOnMass(const TQueueOnMass& other)
    : _size(other._size), _front(other._front),
    _back(other._back), _is_empty(other._is_empty) {
  _data = new T[_size];
  for (size_t i = 0; i < _size; ++i) {
    _data[i] = other._data[i];
  }
}
template <class T>
TQueueOnMass<T>::~TQueueOnMass() {
  delete[] _data;
}

template <class T>
inline bool TQueueOnMass<T>::is_empty() const noexcept {
  return _is_empty;
}
template <class T>
inline bool TQueueOnMass<T>::is_full() const noexcept {
  return !_is_empty && (_front == _back);
}
template <class T>
inline size_t TQueueOnMass<T>::size() const noexcept {
  return _size;
}
template <class T>
inline T& TQueueOnMass<T>::front() {
  if (is_empty()) {
    throw std::underflow_error("ERROR: Queue underflow, can't get front!");
  }
  return _data[_front];
}
template <class T>
inline void TQueueOnMass<T>::push(const T& val) {
  if (is_full()) {
    throw std::overflow_error("ERROR: Queue overflow, can't push!");
  }
  _data[_back] = val;
  _back = (_back + 1) % _size;
  _is_empty = false;
}
template <class T>
inline T TQueueOnMass<T>::pop() {
  if (is_empty()) {
    throw std::underflow_error("ERROR: Queue underflow, can't pop!");
  }
  T val = _data[_front];
  _front = (_front + 1) % _size;
  if (_front == _back) {
    _is_empty = true;
  }
  return val;
}