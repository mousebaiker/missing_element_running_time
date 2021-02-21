#ifndef XORBASED
#define XORBASED

#include <vector>
int find_missing_number(const std::vector<int>& numbers) {
  int result = 0;
  for (int i = 1; i <= (numbers.size() + 1); i++) {
    result ^= i;
  }

  for (const auto& number : numbers) {
    result ^= number;
  }
  return result;
}

#endif //XORBASED
