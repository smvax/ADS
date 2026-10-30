// Copyright 2026 smvax

#include <iostream>
#include <iomanip>

// #define EASY_EXAMPLE
#define ITERATOR
#ifdef EASY_EXAMPLE

#include "../lib_algorithms/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE

#ifdef ITERATOR

#include "../lib_vector/vector.h"

int main() {
  TVector<int> my_vec(8);
  int val = 1;

  for (int val = 1; val <= 8; ++val) {
    my_vec.push_back(val);
  }

  for (TVector<int>::const_iterator it = my_vec.begin(); it != my_vec.end();
       ++it) {
    std::cout << *it << " ";
  }

  std::cout << std::endl;

  return 0;
}

#endif  // ITERATOR
