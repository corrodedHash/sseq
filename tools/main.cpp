#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

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
struct graphnode {
  std::vector<int> neighbors;
};

struct graph {
  std::vector<graphnode> nodes;
  std::optional<setvec> has_path();
  void add_bi_edge(int i, int j)
  {
    nodes[static_cast<setvec::size_type>(i)].neighbors.push_back(j);
    nodes[static_cast<setvec::size_type>(j)].neighbors.push_back(i);
  }
};

std::optional<setvec> graph::has_path()
{
  setvec visited;
  visited.push(0);
  while (visited.size() < nodes.size()) {
    auto& choices = nodes[static_cast<setvec::size_type>(visited.back())].neighbors;
    auto next_id_it = std::find_if(std::begin(choices), std::end(choices), [&](int x) { return !visited.contains(x); });
    if (next_id_it != std::end(choices)) {
      visited.push(*next_id_it);
    }
    while (next_id_it == std::end(choices)) {
      auto faulty_id = visited.pop();

      if (visited.empty()) {
        if (static_cast<setvec::size_type>(faulty_id) >= nodes.size()) {
          return std::nullopt;
        }
        visited.push(faulty_id + 1);
      } else {
        choices = nodes[static_cast<setvec::size_type>(visited.back())].neighbors;
        next_id_it = std::find_if(std::begin(choices), std::end(choices), [&](int x) { return (!visited.contains(x)) && (x > faulty_id); });
        if (next_id_it != std::end(choices)) {
          visited.push(*next_id_it);
        }
      }
    }
  }
  return visited;
}

int main(int argc, char** args)
{
  (void)argc;
  (void)args;
  graph test;
  for (int i = 0; i < 22; ++i) {
    test.nodes.emplace_back();
    for (int j = 0; j < i; ++j) {
      int cur = i + 1 + j + 1;
      int root = static_cast<int>(std::sqrt(cur));
      if (root * root == cur) {
        test.add_bi_edge(i, j);
        std::cout << "h: " << i + 1 << " " << j + 1 << "\n";
      }
    }
    if (auto x = test.has_path(); x) {
      std::cout << i + 1 << "\n";
      for (auto j : x->_vec) {
        std::cout << j + 1 << " ";
      }
      std::cout << "\n";
    }
  }
  for (decltype(test.nodes.size()) j = 0; j < test.nodes.size() ; ++j) {
    std::cout << j + 1 << "\n\t";
    for (int i : test.nodes[j].neighbors) {
      std::cout << i + 1 << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
