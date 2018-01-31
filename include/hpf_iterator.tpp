template <typename T>
HamiltonPathFinder<T>::iterator::iterator(HamiltonPathFinder& hpf_, CompletionStatus finished_)
    : hpf(hpf_)
    , finished(finished_ == CompletionStatus::finished)
{
  if (!finished) {
    ++(*this);
  }
}

template <typename T>
typename HamiltonPathFinder<T>::iterator HamiltonPathFinder<T>::iterator::operator++()
{
  if (!hpf.next()) {
    finished = true;
  }
  return *this;
}

template <typename T>
typename HamiltonPathFinder<T>::iterator HamiltonPathFinder<T>::iterator::operator++(int)
{
  auto i = *this;
  ++(*this);
  return i;
}

template <typename T>
const std::vector<typename boost::graph_traits<T>::vertex_descriptor>& HamiltonPathFinder<T>::iterator::operator*()
{
  return hpf.visited;
}

template <typename T>
const std::vector<typename boost::graph_traits<T>::vertex_descriptor>* HamiltonPathFinder<T>::iterator::operator->()
{
  return &hpf.visited;
}

template <typename T>
bool HamiltonPathFinder<T>::iterator::operator==(const iterator& rhs) { return (finished && rhs.finished) || (!finished && !rhs.finished && (hpf.visited == rhs.hpf.visited)); }

template <typename T>
bool HamiltonPathFinder<T>::iterator::operator!=(const iterator& rhs) { return !(*this == rhs); }
