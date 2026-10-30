// Copyright 2026 smvax

#ifndef LIB_VECTOR_MEMDATA_H_
#define LIB_VECTOR_MEMDATA_H_

#include <cstdlib>  // дл€ рандома
#include <ctime>
#include <initializer_list>
#include <iostream>
#include <sstream>  // дл€ std::istringstream
#include <string>  // дл€ std::getline
#include <random>

#define MEM_STEP 15  // шаг: сколько выдел€етс€ €чеек пам€ти минимум при добавлении эл-тов

template <typename T>
class TVector;

template <typename T>
class TMemData {
  T* _data;  // хранилище данных
  size_t _size;        // размер заполненной части хранилища
  size_t _capacity;    // вместимость хранилища

 public:
  // конструкторы
  TMemData(size_t size = 0);                     // по размеру + по умолчанию
  TMemData(std::initializer_list<T>);  // по списку инициализации
  TMemData(const T*, size_t);          // инициализации
  TMemData(const TMemData&);                      // копировани€
  TMemData(TMemData&&) noexcept;                  // с move-семантикой
  // деструктор
  ~TMemData();

  // публичные методы проверок
  inline bool is_empty() const noexcept;  // на пустоту

  // геттеры
  inline size_t get_size() const noexcept;      // размера
  inline size_t get_capacity() const noexcept;  // вместимости
  inline const T* const get_data_const()
      const noexcept;  // хранилища (возвр указ-ль по которому Ќ≈Ћ№«я мен€ть)
  inline T* const
  get_data_changeable() noexcept;  // хранилища (возвр указ-ль по которому ћќ∆Ќќ мен€ть)

  // сеттеры пам€ти и размера заполненной части
  void set_memory(size_t) noexcept;  // установка пам€ти без сохранени€ данных
  void reset_memory(
      size_t size,
      size_t start_index = 0);   // перевыделение пам€ти с сохранением данных
  void clear_memory() noexcept;  // очистка пам€ти
  inline void set_size(size_t size);  // установка размера заполненной части

  // операторы
  TMemData& operator=(const TMemData&) noexcept;  // присваивани€
  TMemData& operator=(TMemData&&) noexcept;  // присваивани€ с move-семантикой
  bool operator==(const TMemData&) const noexcept;  // сравнени€

  // друзь€шки:
  // -функции
  template <typename T>  // <----иначе не компилируетс€
  friend void quick_sort(TMemData<T>& md);  // сортировки
  template <typename T>
  friend void shuffle(TMemData<T>&);  // перемешивани€

  // -классы
  friend class TVector<T>;

 private:
  // служебные методы
  inline bool is_full() const noexcept;  // проверка на переполнение
};

// реализаци€ инлайновых методов в хедере, но вне класса
template <typename T>
inline bool TMemData<T>::is_empty() const noexcept {
  return (_size == 0);
}
template <typename T>
inline size_t TMemData<T>::get_size() const noexcept {
  return _size;
}
template <typename T>
inline size_t TMemData<T>::get_capacity() const noexcept {
  return _capacity;
}
template <typename T>
inline const T* const TMemData<T>::get_data_const()
    const noexcept {
  return _data;
}
template <typename T>
inline T* const TMemData<T>::get_data_changeable() noexcept {
  return _data;
}
template <typename T>
inline void TMemData<T>::set_size(size_t size) {
  if (size > _capacity) {
    throw std::invalid_argument("ERROR: Size is bigger than capacity!");
  } else {
    _size = size;
  }
}
template <typename T>
inline bool TMemData<T>::is_full() const noexcept {
  return (_size >= _capacity);
}

// функции вне класса
inline int calculate_capacity(
    size_t);  // какую вместимость выставить при заданном кол-ве эл-тов
template <typename T>
void quick_sort_recursive(T* data, int left, int right);
template <typename T>
int partition(T* data, int left, int right);

//========–≈јЋ»«ј÷»я=========

// функции вне класса
inline int calculate_capacity(size_t size) {
  size_t new_capacity = size / MEM_STEP;
  return (new_capacity + 1) * MEM_STEP;
}

// конструкторы
template <typename T>
TMemData<T>::TMemData(size_t size) {  // по размеру + по умолчанию
  _data = nullptr;
  set_memory(size);
  _size = 0;
}
template <typename T>
TMemData<T>::TMemData(
    std::initializer_list<T> list) {  // по списку инициализации
  _data = nullptr;
  set_memory(list.size());
  for (size_t i = 0; i < _size; i++) {
    _data[i] = *(list.begin() + i);
  }
}
template <typename T>
TMemData<T>::TMemData(const T* array,
                              size_t size) {  // инициализации
  // if (array == nullptr) {
  //	throw std::invalid_argument("ERROR: Array pointer is a nullptr!");
  // }
  _size = size;
  _data = nullptr;
  set_memory(_size);
  for (size_t i = 0; i < _size; i++) {
    _data[i] = array[i];
  }
}
template <typename T>
TMemData<T>::TMemData(const TMemData& other) {  // копировани€
  _size = other._size;
  _data = nullptr;
  set_memory(_size);
  for (size_t i = 0; i < _size; i++) {
    _data[i] = other._data[i];
  }
}
template <typename T>
TMemData<T>::TMemData(TMemData&& other) noexcept {  // с move-семантикой
  _size = other._size;
  _capacity = other._capacity;
  _data = other._data;
  other._size = 0;
  other._capacity = 0;
  other._data = nullptr;
}

// деструктор
template <typename T>
TMemData<T>::~TMemData() {
  if (_data) {
    delete[] _data;
  }
}

// сеттеры пам€ти
template <typename T>
void TMemData<T>::set_memory(
    size_t size) noexcept {  // установка без сохр
  _size = size;
  _capacity = calculate_capacity(size);
  if (_data) {
    delete[] _data;
  }
  _data = new T[_capacity];
}
template <typename T>
void TMemData<T>::reset_memory(
    size_t size, size_t start_index) {  // перевыделение с сохранением данных
  if (start_index >= size) {
    throw std::invalid_argument(
        "ERROR: Can't reset memory! start_index >= size");
  }
  size_t new_capacity = calculate_capacity(size);
  size_t old_capacity = _capacity;
  size_t copy_size = _size;
  _size = size;
  if (old_capacity == new_capacity) {
    if (start_index == 0) {
      return;
    }
    T* temp = new T[start_index];
    for (size_t i = 0; i < start_index; i++) {
      temp[i] = _data[i];
    }
    for (size_t i = 0; i < copy_size; i++) {
      if (i + start_index < old_capacity) {
        _data[i] = _data[(i + start_index)];
      } else {
        _data[i] = temp[(i + start_index) % old_capacity];
      }
    }
    return;
  }
  _capacity = new_capacity;
  T* temp = new T[_capacity];
  for (size_t i = 0; i < copy_size; i++) {
    if (i >= _size) {
      break;
    }
    temp[i] = _data[(i + start_index) % old_capacity];
  }
  delete[] _data;
  _data = temp;
}
template <typename T>
void TMemData<T>::clear_memory() noexcept {  // очистка пам€ти
  set_memory(0);
}

// операторы
template <typename T>
TMemData<T>& TMemData<T>::operator=(
    const TMemData& other) noexcept {  // присваивани€
  if (this != &other) {
    _size = other._size;
    _capacity = other._capacity;
    if (_data) {
      delete[] _data;
    }
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
      _data[i] = other._data[i];
    }
  }
  return *this;
}
template <typename T>
TMemData<T>& TMemData<T>::operator=(
    TMemData&& other) noexcept {  // присваивани€ с move-семантикой
  if (this != &other) {
    _size = other._size;
    _capacity = other._capacity;
    delete[] _data;
    _data = other._data;
  }
  other._size = 0;
  other._capacity = 0;
  other._data = nullptr;
  return *this;
}
template <typename T>
bool TMemData<T>::operator==(
    const TMemData& other) const noexcept {  // сравнени€
  if (_size != other._size) {
    return false;
  } else if (_data == other._data) {
    return true;
  } else if (_size == 0) {
    return true;
  } else {
    for (size_t i = 0; i < _size; i++) {
      if (_data[i] != other._data[i]) {
        return false;
      }
    }
    return true;
  }
}

// дружественные функции
template <typename T>
void quick_sort(TMemData<T>& md) {  // метод сортировки ’оара
  if (md._size <= 1) {
    return;
  }
  quick_sort_recursive(md._data, 0, md._size - 1);
}
template <typename T>
void shuffle(TMemData<T>& md) {  // перемешивание ‘ишер-…етса
  if (md._size <= 1) {
    return;
  }
  static std::random_device rd;
  static std::mt19937 gen(rd());
  for (size_t i = md._size - 1; i > 0; i--) {
    std::uniform_int_distribution<size_t> dist(0, i);
    size_t j = dist(gen);
    std::swap(md._data[i], md._data[j]);
  }
}

// функции вне класса
template <typename T>
int partition(T* data, int left, int right) {  // разбиение по ’оару
  T pivot = data[(left + right) / 2];  // опорный эл-т
  int i = left;
  int j = right;
  while (i <= j) {
    while (data[i] < pivot) i++;
    while (data[j] > pivot) j--;
    if (i <= j) {
      std::swap(data[i], data[j]);
      i++;
      j--;
    }
  }
  return i;
}
template <typename T>
void quick_sort_recursive(T* data, int left, int right) {
  if (left < right) {
    int pivot_index = partition(data, left, right);
    quick_sort_recursive(data, left, pivot_index - 1);
    quick_sort_recursive(data, pivot_index, right);
  }
}

#endif  // LIB_VECTOR_MEMDATA_H_
