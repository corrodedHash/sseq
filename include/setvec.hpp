#pragma once
#include <unordered_set>
#include <vector>
#include <algorithm>

struct setvec {
  using T = int;
  std::vector<T> _vec;

  using size_type = std::vector<T>::size_type;
  void push(T value)
  {
    _vec.push_back(value);
  }
  auto size()
  {
    return _vec.size();
  }

  bool empty()
  {
    return _vec.empty();
  }

  T pop()
  {
    T x = _vec.back();
    _vec.pop_back();
    return x;
  }
  T back()
  {
    return _vec.back();
  }
  bool contains(T value)
  {
    return std::find(std::begin(_vec), std::end(_vec), value) != std::end(_vec);
  }
};
