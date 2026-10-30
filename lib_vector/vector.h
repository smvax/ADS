// Copyright 2024 Marina Usova

#ifndef LIB_VECTOR_VECTOR_H_
#define LIB_VECTOR_VECTOR_H_

#include <cstdlib>
#include <iostream>

#include "memdata.h"

template <typename T>
class TVector {
  TMemData<T> _mem;  // хранилище данных + размер  + вместимость
  size_t _front;              // индекс первого элемента
  size_t _back;               // индекс последнего элемента

 public:
  // конструкторы
  TVector(size_t size = 0);  // конструктор по размеру + по умолчанию
  TVector(std::initializer_list<T>);  // конструктор по списку
                                               // инициализации
  TVector(const T*, size_t);          // конструктор инициализации
  TVector(const TVector<T>&);          // конструктор копирования
  TVector(TVector<T>&&) noexcept;      // конструктор с move-семантикой
                                               // деструктор
  ~TVector() = default;                         // напишется компилятором

  // публичные методы проверок
  inline bool is_empty() const noexcept;  // на пустоту
  inline bool is_full() const noexcept;   // на переполнение

  // геттеры
  inline size_t get_size() const noexcept;      // размера
  inline size_t get_capacity() const noexcept;  // вместимости
  inline T get_front() const;  // первого элемента (возвр. копию)
  inline size_t get_front_idx() const;  // первого элемента (возвр. индекс) ДЛЯ GTESTS
  inline T get_back() const;  // последнего элемента (возвр. копию)
  inline size_t get_back_idx() const;  // последнего элемента (возвр. индес) ДЛЯ GTESTS
  inline TMemData<T> get_mem_copy()
      const noexcept;  // копии мемдаты (для тестов)
  inline const TMemData<T>& get_mem_original()
      const noexcept;  // оригинала мемдаты (для тестов на move)

  // сеттеры
  inline T& front_ref();  // первого элемента (возвр. ссылку)
  inline T& back_ref();   // последнего элемента (возвр. ссылку)

  // публичные методы вставок
  void push_front(T) noexcept;                // 1 элемента в начало
  void push_front_many(T*, size_t) noexcept;  // нескольких в начало
  void push_back(T) noexcept;                 // 1 элемента в конец
  void push_back_many(T*, size_t) noexcept;   // нескольких в конец
  void insert(T, size_t);                     // 1 элемента по позиции
  void insert_many(T*, size_t, size_t);       // нескольких по позиции

  // удалений
  void pop_front();                 // 1 элемента из начала
  void pop_front_many(size_t);      // нескольких из начала
  void pop_back();                  // 1 элемента из конца
  void pop_back_many(size_t);       // нескольких из конца
  void erase(size_t);               // 1 элемента по позиции
  void erase_many(size_t, size_t);  // нескольких по позиции
  void shrink_to_fit();             // неиспользуемой памяти

  // перегрузки операторов
  TVector<T>& operator=(
      const TVector<T>&) noexcept;  // присваивания
  TVector<T>& operator=(
      TVector<T>&&) noexcept;  // присваивания с move-семантикой
  T operator[](
      size_t) const noexcept;  // обращения по индексу (не изм., возвр. копию)
  T& operator[](
      size_t) noexcept;  // обращения по индексу (изм., возвр. ссылку)

  // дружественные функции
  // перегрузки ввода-вывода
  template <typename T>
  friend std::ostream& operator<<(std::ostream&,
                                  const TVector<T>&);  // вывода
  template <typename T>
  friend std::istream& operator>>(std::istream&,
                                  TVector<T>&);  // ввода
  // сортировки и перемешивания
  template <typename T>
  friend void quick_sort(TVector<T>&);  // сортировки (Хоара)
  template <typename T>
  friend void shuffle(TVector<T>&);  // перемешивания (Фишер-Йетса)

  // ИТЕРАТОР

  template <typename Type>
  class Iterator {
    Type* _p_start;       // Указатель на начало физического массива (_mem._data)
    Type* _p_cur;         // Текущий указатель на элемент
    size_t _capacity;     // Вместимость массива
    size_t _front_idx;    // Физический индекс начала вектора
    size_t _logical_pos;  // Логическая позиция (от 0 до size)

   public:
    Iterator()
        : _p_start(nullptr),
          _p_cur(nullptr),
          _capacity(0),
          _front_idx(0),
          _logical_pos(0) {}
    Iterator(Type* start, size_t capacity, size_t front_idx, size_t logical_pos)
        : _p_start(start),
          _capacity(capacity),
          _front_idx(front_idx),
          _logical_pos(logical_pos) {
      update_ptr();
    }
    template <typename OtherType>
    Iterator(const Iterator<OtherType>& other)
        : _p_start(other.get_start_pointer()),
          _capacity(other.get_capacity()),
          _front_idx(other.get_front_idx()),
          _logical_pos(other.get_logical_pos()) {
      update_ptr();
    }

    inline Type* get_start_pointer() const noexcept { return _p_start; }
    inline size_t get_capacity() const noexcept { return _capacity; }
    inline size_t get_front_idx() const noexcept { return _front_idx; }
    inline size_t get_logical_pos() const noexcept { return _logical_pos; }

    inline bool operator==(const Iterator& other) const noexcept {
      return _p_start == other._p_start && _logical_pos == other._logical_pos;
    }
    inline bool operator!=(const Iterator& other) const noexcept {
      return !(*this == other);
    }

    inline Type& operator*() const noexcept { return *_p_cur; }
    Iterator& operator++() noexcept {
      _logical_pos++;
      update_ptr();
      return *this;
    }
    Iterator operator++(int) {
      Iterator temp = *this;
      _logical_pos++;
      update_ptr();
      return temp;
    }
    Iterator& operator--() {
      _logical_pos--;
      update_ptr();
      return *this;
    }
    Iterator operator--(int) {
      Iterator temp = *this;
      _logical_pos--;
      update_ptr();
      return temp;
    }
    Iterator& operator=(const Iterator& other) {
      if (this != &other) {
        _p_start = other._p_start;
        _capacity = other._capacity;
        _front_idx = other._front_idx;
        _logical_pos = other._logical_pos;
        _p_cur = other._p_cur;
      }
      return *this;
    }
    Iterator& operator+=(int n) {
      _logical_pos += n;
      update_ptr();
      return *this;
    }
    Iterator& operator-=(int n) {
      _logical_pos -= n;
      update_ptr();
      return *this;
    }
    Iterator operator+(int n) const {
      Iterator temp = *this;
      return temp += n;
    }
    Iterator operator-(int n) const {
      Iterator temp = *this;
      return temp -= n;
    }

    private:
    // Вспомогательный метод для обновления p_cur на основе логической позиции
    void update_ptr() {
      if (_capacity == 0) {
        _p_cur = nullptr;
      } else {
        size_t phys_idx = (_front_idx + _logical_pos) % _capacity;
        _p_cur = _p_start + phys_idx;
      }
    }
  };

  typedef Iterator<T> iterator;
  typedef Iterator<const T> const_iterator;

  inline iterator begin() noexcept {
    return iterator(_mem.get_data_changeable(), _mem.get_capacity(), _front, 0);
  }
  inline iterator end() noexcept {
    return iterator(_mem.get_data_changeable(), _mem.get_capacity(), _front,
                    _mem.get_size());
  }
  inline const_iterator begin() const noexcept {
    return const_iterator(_mem.get_data_const(), _mem.get_capacity(), _front, 0);
  }
  inline const_iterator end() const noexcept {
    return const_iterator(_mem.get_data_const(), _mem.get_capacity(), _front,
                          _mem.get_size());
  }
  inline const_iterator cbegin() const noexcept {
    return const_iterator(_mem.get_data_const(), _mem.get_capacity(), _front, 0);
  }
  inline const_iterator cend() const noexcept {
    return const_iterator(_mem.get_data_const(), _mem.get_capacity(), _front,
                          _mem.get_size());
  }

 private:
  // служебный метод получения (геттер) физического индекса по относительному
  inline size_t get_mem_index(size_t i) const;
};

// реализация инлайновых методов в хедере, но вне класса
template <typename T>
inline bool TVector<T>::is_empty() const noexcept {
  return _mem.is_empty();
}
template <typename T>
inline bool TVector<T>::is_full() const noexcept {
  return _mem.is_full();
}
template <typename T>
inline size_t TVector<T>::get_size() const noexcept {
  return _mem._size;
}
template <typename T>
inline size_t TVector<T>::get_capacity() const noexcept {
  return _mem._capacity;
}
template <typename T>
inline T TVector<T>::get_front() const {
  if (_mem._size != 0) {
    return (_mem._data)[_front];
  } else {
    throw std::logic_error("ERROR: Vector is empty! Can't get front");
  }
}
template <typename T>
inline size_t TVector<T>::get_front_idx() const {
  if (_mem._size != 0) {
    return _front;
  } else {
    throw std::logic_error("ERROR: Vector is empty! Can't get front");
  }
}
template <typename T>
inline T TVector<T>::get_back() const {
  if (_mem._size != 0) {
    return (_mem._data)[_back];
  } else {
    throw std::logic_error("ERROR: Vector is empty! Can't get back");
  }
}
template <typename T>
inline size_t TVector<T>::get_back_idx() const {
  if (_mem._size != 0) {
    return _back;
  } else {
    throw std::logic_error("ERROR: Vector is empty! Can't get back");
  }
}
template <typename T>
inline TMemData<T> TVector<T>::get_mem_copy() const noexcept {
  return _mem;
}
template <typename T>
inline const TMemData<T>& TVector<T>::get_mem_original()
    const noexcept {
  return _mem;
}
template <typename T>
inline T& TVector<T>::front_ref() {
  if (_mem._size != 0) {
    return (_mem._data)[_front];
  } else {
    throw std::logic_error("ERROR: Vector is empty! Can't set front");
  }
}
template <typename T>
inline T& TVector<T>::back_ref() {
  if (_mem._size != 0) {
    return (_mem._data)[_back];
  } else {
    throw std::logic_error("ERROR: Vector is empty! Can't set back");
  }
}
template <typename T>
inline size_t TVector<T>::get_mem_index(size_t i) const {
  return ((i + _front) % _mem._capacity);
}

//========РЕАЛИЗАЦИЯ МЕТОДОВ ВЕКТОРА=======

// конструкторы
template <typename T>
TVector<T>::TVector(size_t size) {
  TMemData<T> temp(size);
  _mem = (std::move(temp));
  _front = 0;
  _back = 0;
}
template <typename T>
TVector<T>::TVector(std::initializer_list<T> list) {
  TMemData<T> temp(list);
  _mem = (std::move(temp));
  _front = 0;
  if (_mem._size > 0) {
    _back = _mem._size - 1;
  } else {
    _back = 0;
  }
}
template <typename T>
TVector<T>::TVector(const T* array, size_t size) {
  TMemData<T> temp(array, size);
  _mem = (std::move(temp));
  _front = 0;
  if (_mem._size > 0) {
    _back = _mem._size - 1;
  } else {
    _back = 0;
  }
}
template <typename T>
TVector<T>::TVector(const TVector<T>& other) {
  _mem = other._mem;
  _front = other._front;
  _back = other._back;
}
template <typename T>
TVector<T>::TVector(TVector<T>&& other) noexcept {
  _mem = std::move(other._mem);
  _front = other._front;
  other._front = 0;
  _back = other._back;
  other._back = 0;
}

// публичные методы
// вставок
template <typename T>
void TVector<T>::push_front(T element) noexcept {
  _mem._size++;
  if (_mem._size > 1) {
    _front = (_front + _mem._capacity - 1) % _mem._capacity;
  }
  _mem._data[_front] = element;
  if (is_full()) {
    _mem.reset_memory(_mem._size, _front);
    _front = 0;
    _back = _mem._size - 1;
  }
}
template <typename T>
void TVector<T>::push_front_many(T* elements,
                                          size_t size) noexcept {
  for (int i = size - 1; i >= 0; i--) {  // идем с конца тк кладем в начало
    push_front(elements[i]);
  }
}
template <typename T>
void TVector<T>::push_back(T element) noexcept {
  _mem._size++;
  if (_mem._size > 1) {
    _back = (_back + 1) % _mem._capacity;
  }
  _mem._data[_back] = element;
  if (is_full()) {
    _mem.reset_memory(_mem._size, _front);
    _front = 0;
    _back = _mem._size - 1;
  }
}
template <typename T>
void TVector<T>::push_back_many(T* elements,
                                         size_t size) noexcept {
  for (int i = 0; i < size; i++) {  // идем с начала тк кладем в конец
    push_back(elements[i]);
  }
}
template <typename T>
void TVector<T>::insert(T element, size_t i) {
  if (i > _mem._size) {
    throw std::out_of_range("ERROR: Insert index out of range!");
  } else {
    if (i == 0) {
      push_front(element);
    } else if (i == _mem._size) {
      push_back(element);
    } else {
      _mem._size++;
      _back = (_back + 1) % _mem._capacity;
      for (int j = _mem._size - 1; j > i; j--) {
        (*this)[j] = (*this)[j - 1];
      }
      (*this)[i] = element;
      if (is_full()) {
        _mem.reset_memory(_mem._size, _front);
        _front = 0;
        _back = _mem._size - 1;
      }
    }
  }
}
template <typename T>
void TVector<T>::insert_many(T* elements, size_t size,
                                      size_t i) {
  if (i > _mem._size) {
    throw std::out_of_range("ERROR: Insert (many) index out of range!");
  } else {
    for (int j = 0; j < size; j++) {
      insert(elements[j], i + j);
    }
  }
}

// удалений
template <typename T>
void TVector<T>::pop_front() {
  if (_mem._size == 0) {
    throw std::logic_error("ERROR: Empty vector! Can't pop front");
  } else {
    _mem._size--;
    if (_mem._size != 0) {
      _front = (_front + 1) % _mem._capacity;
    } else {
      _front = 0;
      _back = 0;
    }
    if (_mem._capacity - _mem._size > MEM_STEP) {
      _mem.reset_memory(_mem._size, _front);
      _front = 0;
      if (_mem._size != 0) {
        _back = _mem._size - 1;
      }
    }
  }
}
template <typename T>
void TVector<T>::pop_front_many(size_t count) {
  if (_mem._size < count) {
    throw std::logic_error("ERROR: Popping (front) too many elements!");
  } else {
    _mem._size -= count;
    if (_mem._size != 0) {
      _front = (_front + count) % _mem._capacity;
    } else {
      _front = 0;
      _back = 0;
    }
    if (_mem._capacity - _mem._size > MEM_STEP) {
      _mem.reset_memory(_mem._size, _front);
      _front = 0;
      if (_mem._size != 0) {
        _back = _mem._size - 1;
      }
    }
  }
}
template <typename T>
void TVector<T>::pop_back() {
  if (_mem._size == 0) {
    throw std::logic_error("ERROR: Empty vector! Can't pop back");
  } else {
    _mem._size--;
    if (_mem._size != 0) {
      _back = (_back + _mem._capacity - 1) % _mem._capacity;
    } else {
      _front = 0;
      _back = 0;
    }
    if (_mem._capacity - _mem._size > MEM_STEP) {
      _mem.reset_memory(_mem._size, _front);
      _front = 0;
      if (_mem._size != 0) {
        _back = _mem._size - 1;
      }
    }
  }
}
template <typename T>
void TVector<T>::pop_back_many(size_t count) {
  if (_mem._size < count) {
    throw std::logic_error("ERROR: Popping (back) too many elements!");
  } else {
    _mem._size -= count;
    if (_mem._size != 0) {
      _back = (_back + _mem._capacity - count) % _mem._capacity;
    } else {
      _front = 0;
      _back = 0;
    }
    if (_mem._capacity - _mem._size > MEM_STEP) {
      _mem.reset_memory(_mem._size, _front);
      _front = 0;
      if (_mem._size != 0) {
        _back = _mem._size - 1;
      }
    }
  }
}
template <typename T>
void TVector<T>::erase(size_t i) {
  if (i >= _mem._size) {
    throw std::out_of_range("ERROR: Erase index out of range!");
  } else {
    if (i == 0) {
      pop_front();
    } else if (i == _mem._size - 1) {
      pop_back();
    } else {
      _back = (_back - 1 + _mem._capacity) % _mem._capacity;
      for (int j = i; j < _mem._size - 1; j++) {
        (*this)[j] = (*this)[j + 1];
      }
      _mem._size--;
      if (_mem._size == 0) {
        _front = 0;
        _back = 0;
      }
      if (_mem._capacity - _mem._size > MEM_STEP) {
        _mem.reset_memory(_mem._size, _front);
        _front = 0;
        _back = _mem._size == 0 ? 0 : _mem._size - 1;
      }
    }
  }
}
template <typename T>
void TVector<T>::erase_many(size_t i, size_t count) {
  if (i + count > _mem._size) {
    throw std::logic_error("ERROR: Erasing too many elements!");
  }
  for (int j = 0; j < count; j++) {
    erase(i);
  }
}
template <typename T>
void TVector<T>::shrink_to_fit() {
  if (is_empty() || is_full()) {
    return;
  }
  T* temp = new T[_mem._size];
  for (size_t i = 0; i < _mem._size; i++) {
    temp[i] = _mem._data[(_front + i) % _mem._capacity];
  }
  if (_mem._data) {
    delete[] _mem._data;
  }
  _mem._data = temp;
  _front = 0;
  _back = _mem._size - 1;
  _mem._capacity = _mem._size;
}

// перегрузки операторов
template <typename T>
TVector<T>& TVector<T>::operator=(
    const TVector<T>& other) noexcept {
  if (this != &other) {
    _mem = other._mem;
    _front = other._front;
    _back = other._back;
  }
  return (*this);
}
template <typename T>
TVector<T>& TVector<T>::operator=(
    TVector<T>&& other) noexcept {
  if (this != &other) {
    _mem = std::move(other._mem);
    _front = other._front;
    other._front = 0;
    _back = other._back;
    other._back = 0;
  }
  return (*this);
}
template <typename T>
T TVector<T>::operator[](size_t i) const noexcept {
  return _mem._data[(*this).get_mem_index(i)];
}
template <typename T>
T& TVector<T>::operator[](size_t i) noexcept {
  return _mem._data[(*this).get_mem_index(i)];
}

// дружественные функции
// сортировки и перемешивания
template <typename T>
void quick_sort(TVector<T>& vector) {
  if (vector._mem.get_size() <= 1) {
    return;
  }
  vector._mem.reset_memory(vector._mem.get_size(), vector._front);
  vector._front = 0;
  vector._back = vector._mem.get_size() - 1;
  quick_sort(vector._mem);
}
template <typename T>
void shuffle(TVector<T>& vector) {
  if (vector._mem.get_size() <= 1) {
    return;
  }
  vector._mem.reset_memory(vector._mem.get_size(), vector._front);
  vector._front = 0;
  vector._back = vector._mem.get_size() - 1;
  shuffle(vector._mem);
}
// перегрузки ввода-вывода
template <typename T>
std::ostream& operator<<(std::ostream& out,
                         const TVector<T>& vector) {  // вывода
  out << "{ ";
  size_t size = vector.get_size();
  if (size != 0) {
    out << vector._mem.get_data_const()[vector._front];
  }
  for (size_t i = 1; i < size; i++) {
    out << ", " << vector._mem.get_data_const()[vector.get_mem_index(i)];
  }
  out << " }";
  return out;
}
template <typename T>
std::istream& operator>>(std::istream& in,
                         TVector<T>& vector) {  // ввода
  TVector<T> temp;
  T element;
  in >> element;
  while (in >> element) {
    temp.push_back(element);
  }
  vector = std::move(temp);
  return in;
}

#endif  // LIB_VECTOR_VECTOR_H
