#include <cmath>
inline bool is_square_num(int value)
{
  int root = static_cast<int>(std::sqrt(value));
  return (root * root == value);
}
