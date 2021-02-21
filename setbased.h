#ifndef SETBASED
#define SETBASED

#include <vector>
#include <unordered_set>

int find_missing_number(const std::vector<int>& numbers) {
  std::unordered_set<int> candidates;
  candidates.reserve(numbers.size() + 1);
  for (int i = 1; i <= (numbers.size() + 1); i++) {
    candidates.insert(i);
  }

  for (const auto& number : numbers) {
    candidates.erase(number);
  }
  return *(candidates.begin());
}

#endif //SETBASED
