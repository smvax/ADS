// Copyright 2024 Marina Usova

#include <stdexcept>
#include <cstring>
#include "../lib_algorithms/easy_example.h"
#include "../lib_stack_on_mass/stack_on_mass.h"

float division(int a, int b) {
  if (b == 0) {
     throw std::invalid_argument("Input Error: can't divide by zero!");
  }
  return static_cast<float>(a) / b;
}

bool check_brackets(std::string expression) {
  TStackOnMass<char> tmp_stack(expression.size());
  for (char c : expression) {
    if (c == '(' || c == '[' || c == '{') {
      tmp_stack.push(c);  
    }
    if (c == ')') {
      if (tmp_stack.is_empty()) {
        return false;
      }
      if (tmp_stack.pop() != '(') {
        return false;
      }
    }
    else if (c == ']') {
      if (tmp_stack.is_empty()) {
        return false;
      }
      if (tmp_stack.pop() != '[') {
        return false;
      }
    }
    else if (c == '}') {
      if (tmp_stack.is_empty()) {
        return false;
      }
      if (tmp_stack.pop() != '{') {
        return false;
      }
    }
  }
  return tmp_stack.is_empty();
};