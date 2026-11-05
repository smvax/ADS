// Copyright 2026 smvax

#ifndef LIB_MULTISTACK_ON_MASS_MULTISTACK_ON_MASS_H_
#define LIB_MULTISTACK_ON_MASS_MULTISTACK_ON_MASS_H_

#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <iostream>

template <class T>
class TMultiStackOnMass {
  T* _data;
  size_t _capacity;  // Physical capacity (how many may be in)
  size_t _parts_num;
  size_t _size;  // How many elements are in
  size_t* _lefts;
  size_t* _rights;
  int* _tops;

 public:
  TMultiStackOnMass(size_t, size_t);
  TMultiStackOnMass(const TMultiStackOnMass&);
  ~TMultiStackOnMass();

  bool is_empty_part(size_t) const;
  bool is_full_part(size_t) const;
  bool is_empty() const noexcept;
  bool is_full() const noexcept;
  size_t get_left(size_t) const;
  size_t get_right(size_t) const;
  int get_top(size_t) const;

  void push(size_t, const T&);
  T pop(size_t);
  T& top(size_t);

 private:
  void repack(size_t, const T&);
};

template <class T>
TMultiStackOnMass<T>::TMultiStackOnMass(size_t parts_num, size_t capacity) {
  if (parts_num == 0 || capacity < parts_num) {
    throw std::invalid_argument("ERROR: Invalid size or parts count!");
  }
  _capacity = capacity;
  _parts_num = parts_num;
  _size = 0;
  _data = new T[_capacity]();
  _lefts = new size_t[_parts_num];
  _rights = new size_t[_parts_num];
  _tops = new int[_parts_num];
  size_t base_count = _capacity / _parts_num;
  size_t remainder = _capacity % _parts_num;
  size_t current_left = 0;
  for (size_t i = 0; i < _parts_num; ++i) {
    size_t current_size = base_count + (i < remainder ? 1 : 0);
    _lefts[i] = current_left;
    _rights[i] = current_left + current_size - 1;
    _tops[i] = static_cast<int>(current_left) - 1;
    current_left += current_size;
  }
}
template <class T>
TMultiStackOnMass<T>::TMultiStackOnMass(const TMultiStackOnMass& other) {
  _capacity = other._capacity;
  _parts_num = other._parts_num;
  _size = other._size;
  _data = new T[_capacity]();
  _lefts = new size_t[_parts_num];
  _rights = new size_t[_parts_num];
  _tops = new int[_parts_num];
  std::copy(other._data, other._data + _capacity, _data);
  std::copy(other._lefts, other._lefts + _parts_num, _lefts);
  std::copy(other._rights, other._rights + _parts_num, _rights);
  std::copy(other._tops, other._tops + _parts_num, _tops);
}
template <class T>
TMultiStackOnMass<T>::~TMultiStackOnMass() {
  delete[] _data;
  delete[] _lefts;
  delete[] _rights;
  delete[] _tops;
}

template <class T>
inline bool TMultiStackOnMass<T>::is_empty_part(size_t part) const {
  if (part >= _parts_num) {
    throw std::out_of_range("ERROR: Wrong part number!");
  }
  return _tops[part] < static_cast<int>(_lefts[part]);
}
template <class T>
inline bool TMultiStackOnMass<T>::is_full_part(size_t part) const {
  if (part >= _parts_num) {
    throw std::out_of_range("ERROR: Wrong part number!");
  }
  return _tops[part] == static_cast<int>(_rights[part]);
}
template <class T>
inline bool TMultiStackOnMass<T>::is_empty() const noexcept {
  return _size == 0;
}
template <class T>
inline bool TMultiStackOnMass<T>::is_full() const noexcept {
  return _size == _capacity;
}
template <class T>
inline size_t TMultiStackOnMass<T>::get_left(size_t part) const {
  if (part >= _parts_num) {
    throw std::out_of_range("ERROR: Wrong part number!");
  }
  return _lefts[part];
}

template <class T>
inline size_t TMultiStackOnMass<T>::get_right(size_t part) const {
  if (part >= _parts_num) {
    throw std::out_of_range("ERROR: Wrong part number!");
  }
  return _rights[part];
}

template <class T>
inline int TMultiStackOnMass<T>::get_top(size_t part) const {
  if (part >= _parts_num) {
    throw std::out_of_range("ERROR: Wrong part number!");
  }
  return _tops[part];
}


template <class T>
void TMultiStackOnMass<T>::push(size_t part, const T& elem) {
  if (is_full()) {
    throw std::overflow_error("ERROR: MultiStack overflow!");
  }
  if (is_full_part(part)) {
    repack(part, elem);
    return;
  }
  _tops[part]++;
  _data[_tops[part]] = elem;
  _size++;
}
template <class T>
T TMultiStackOnMass<T>::pop(size_t part) {
  if (is_empty_part(part)) {
    throw std::underflow_error("ERROR: Stack underflow!");
  }
  T elem = _data[_tops[part]];
  _tops[part]--;
  _size--;
  return elem;
}
template <class T>
inline T& TMultiStackOnMass<T>::top(size_t part) {
  if (is_empty_part(part)) {
    throw std::underflow_error("ERROR: Stack is empty!");
  }
  return _data[_tops[part]];
}

template <class T>
void TMultiStackOnMass<T>::repack(size_t overflow_part, const T& new_elem) {
  size_t* counts = new size_t[_parts_num];
  size_t total_elements = 0;
  for (size_t i = 0; i < _parts_num; ++i) {
    if (is_empty_part(i)) {
      counts[i] = 0;
    } else {
      counts[i] = _tops[i] - static_cast<int>(_lefts[i]) + 1;
    }
    if (i == overflow_part) {
      counts[i]++;
    }
    total_elements += counts[i];
  }
  size_t free_space = _capacity - total_elements;
  size_t* weights = new size_t[_parts_num];
  size_t total_weight = 0;
  for (size_t i = 0; i < _parts_num; ++i) {
    weights[i] = counts[i] + 1;
    total_weight += weights[i];
  }
  size_t* free_allocated = new size_t[_parts_num];
  size_t* remainders = new size_t[_parts_num];
  size_t free_allocated_sum = 0;
  for (size_t i = 0; i < _parts_num; ++i) {
    free_allocated[i] = (free_space * weights[i]) / total_weight;
    remainders[i] = (free_space * weights[i]) % total_weight;
    free_allocated_sum += free_allocated[i];
  }
  size_t leftover_free = free_space - free_allocated_sum;
  while (leftover_free > 0) {
    size_t max_idx = 0;
    size_t max_rem = 0;
    bool found = false;
    for (size_t i = 0; i < _parts_num; ++i) {
      if (remainders[i] > max_rem) {
        max_rem = remainders[i];
        max_idx = i;
        found = true;
      }
    }
    if (!found) {
      max_idx = 0;
    }
    free_allocated[max_idx]++;
    remainders[max_idx] = 0;
    leftover_free--;
  }
  size_t* new_caps = new size_t[_parts_num];
  for (size_t i = 0; i < _parts_num; ++i) {
    new_caps[i] = counts[i] + free_allocated[i];
  }
  T* new_data = new T[_capacity]();
  size_t current_left = 0;
  size_t* new_lefts = new size_t[_parts_num];
  size_t* new_rights = new size_t[_parts_num];
  int* new_tops = new int[_parts_num];
  for (size_t i = 0; i < _parts_num; ++i) {
    new_lefts[i] = current_left;
    new_rights[i] = current_left + new_caps[i] - 1;
    size_t existing_count = 0;
    if (!is_empty_part(i)) {
      existing_count = _tops[i] - static_cast<int>(_lefts[i]) + 1;
    }
    for (size_t j = 0; j < existing_count; ++j) {
      new_data[current_left + j] = _data[_lefts[i] + j];
    }
    new_tops[i] =
        static_cast<int>(current_left) + static_cast<int>(existing_count) - 1;
    if (i == overflow_part) {
      new_tops[i]++;
      new_data[new_tops[i]] = new_elem;
    }
    current_left += new_caps[i];
  }
  delete[] _data;
  delete[] _lefts;
  delete[] _rights;
  delete[] _tops;
  _data = new_data;
  _lefts = new_lefts;
  _rights = new_rights;
  _tops = new_tops;
  _size++;
  delete[] counts;
  delete[] weights;
  delete[] free_allocated;
  delete[] remainders;
  delete[] new_caps;
}

#endif  // LIB_MULTISTACK_ON_MASS_MULTISTACK_ON_MASS_H_
