#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <random>

#include "xorbased.h"


std::vector<int> generate_numbers(int n) {
  std::vector<int> values;
  values.reserve(n);
  for (int i = 1; i <= n; i++) {
    values.push_back(i);
  }
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(values), std::end(values), rng);
  values.pop_back();
  return values;
}

bool check_answer(const std::vector<int>& numbers, int answer) {
  for (const auto& number : numbers) {
    if (number == answer) return false;
  }
  return true;
}

double compute_mean(const std::vector<long long>& vals) {
  double res = 0.0;
  for ( const auto& val : vals) {
    res += val;
  }
  return res / vals.size();
}

double compute_std(const std::vector<long long>& vals, double mean) {
  double res = 0.0;
  for ( const auto& val : vals) {
    res += pow((val - mean), 2.0);
  }
  return pow(res / vals.size(), 0.5);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./missing_number NUMBER_OF_ELEMENTS" << std::endl;
  }
  int num_of_elements = std::stoi(argv[1]);
  const std::vector<int> numbers = generate_numbers(num_of_elements);
  std::vector<long long> running_time;
  for (int i = 0; i < 100; i++) {
    auto t1 = std::chrono::high_resolution_clock::now();
    int answer = find_missing_number(numbers);
    auto t2 = std::chrono::high_resolution_clock::now();

    running_time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count());

    // Actually use answer, so compiler does not discard it.
    if (!check_answer(numbers, answer)) {
      std::cout << "Wrong answer!" << std::endl;
    }
  }

  double mean_rt = compute_mean(running_time);
  double std_rt = compute_std(running_time, mean_rt);
  std::cout << "Running time over 100 runs: " << mean_rt  << " ± " << std_rt << std::endl;
  return 0;
}
