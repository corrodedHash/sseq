#pragma once
#include <vector>
#include <set>

struct setvec {
  using T = int;
  std::vector<T> _vec;
  std::set<T> _set;

  using size_type = std::vector<T>::size_type;
  void push(T value)
  {
    _vec.push_back(value);
    _set.insert(value);
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
    _set.erase(x);
    return x;
  }
  T back()
  {
    return _vec.back();
  }
  bool contains(T value)
  {
    return _set.find(value) != _set.end();
  }
};
