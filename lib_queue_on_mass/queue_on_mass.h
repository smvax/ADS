// Copyright 2024 Marina Usova

#include <stdexcept>

template <class T>
class TQueueOnMass {
  T* _data;
  size_t _size;
  size_t _front;
  size_t _back;

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