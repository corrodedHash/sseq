template <typename T>
HamiltonPathFinder<T>::HamiltonPathFinder(const T& graph_) : graph(graph_) {
  visited.reserve(boost::num_vertices(graph));
  iterator_stack.reserve(boost::num_vertices(graph));
  auto it_pair = boost::vertices(graph);
  root_it = it_pair.first;
  root_end = it_pair.second;
}

template <typename T>
std::optional<std::vector<typename boost::graph_traits<T>::vertex_descriptor>>
HamiltonPathFinder<T>::next() {
  while (root_it != root_end) {
    visited.push_back(*root_it);
    iterator_stack.push_back(boost::adjacent_vertices(visited.back(), graph));
    while (!iterator_stack.empty()) {
      while (iterator_stack.back().first != iterator_stack.back().second) {
        if (std::find(std::begin(visited), std::end(visited),
                      *iterator_stack.back().first) == std::end(visited)) {
          visited.push_back(*iterator_stack.back().first);
          ++iterator_stack.back().first;
          iterator_stack.push_back(
              boost::adjacent_vertices(visited.back(), graph));

          break;
        }
        ++iterator_stack.back().first;
      }
      if (iterator_stack.back().first == iterator_stack.back().second) {
        visited.pop_back();
        iterator_stack.pop_back();
      } else if (visited.size() == boost::num_vertices(graph)) {
        return visited;
      }
    }
    ++root_it;
  }
  return std::nullopt;
}
template <typename T>
typename HamiltonPathFinder<T>::iterator HamiltonPathFinder<T>::begin() {
  return HamiltonPathFinder<T>::iterator(
      *this, HamiltonPathFinder<T>::iterator::CompletionStatus::running);
}
template <typename T>
typename HamiltonPathFinder<T>::iterator HamiltonPathFinder<T>::end() {
  return HamiltonPathFinder<T>::iterator(
      *this, HamiltonPathFinder<T>::iterator::CompletionStatus::finished);
}
