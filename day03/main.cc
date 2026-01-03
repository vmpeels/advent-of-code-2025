#include "common/common.h"
#include <iostream>
#include <vector>

int GetMaxJoltage(const std::string &bank) {
  // First, we find the largest number that is not the last digit.
  int largest_first_num = bank[0] - '0';
  int first_num_index = 0;

  // It's important that we iterate from left to right here. Imagine the case
  // where there are two numbers in a bank that are both the max. We would want
  // to choose the "leftmost" index of the number as it is the more flexible of
  // the two.
  for (int i = 1; i < bank.size() - 1; ++i) {
    int num = bank[i] - '0';
    if (num > largest_first_num) {
      largest_first_num = num;
      first_num_index = i;
    }
  }

  int second_num = -1;
  for (int i = first_num_index + 1; i < bank.size(); ++i) {
    int num = bank[i] - '0';
    second_num = std::max(num, second_num);
  }

  return largest_first_num * 10 + second_num;
}

void Part1(const std::vector<std::string> &input) {

  // Unnecessary but let's put convert the input into the problem's abstraction.
  std::vector<std::string> banks(input);
  int sum = 0;
  for (const auto &bank : banks) {
    sum += GetMaxJoltage(bank);
  }
  std::cout << "Part 1: " << sum << std::endl;
}

/*
Part 2 is very similar to Part 1. Instead, of looking for 2 numbers, we're
looking for 12.

We'll have two ints, `start` and `end`, that represent the indices we need to
search through. Also keep track of the numbers left to concatenate (starts at
12).

Iterate through `start` and `end`, looking for the max number between those
indices. The key part is to ensure that `end` is sufficiently far away enough
from the end of the bank to ensure we have enough numbers left over to make 12.
*/
ll GetMaxJoltage2(const std::string &bank) {
  std::vector<ll> joltages;
  int start = 0;
  int batteries_remaining = 12;
  int end = bank.size() - batteries_remaining;
  while (batteries_remaining > 0) {
    end = bank.size() - batteries_remaining;
    int max_joltage = bank[start] - '0';
    int max_joltage_index = start;
    for (int i = start; i <= end; ++i) {
      int joltage = bank[i] - '0';
      if (joltage > max_joltage) {
        max_joltage = joltage;
        max_joltage_index = i;
      }
    }
    joltages.push_back(max_joltage);
    start = max_joltage_index + 1;
    batteries_remaining--;
  }
  ll sum = 0;
  for (ll joltage : joltages) {
    sum = sum * 10 + joltage;
  }
  return sum;
}

void Part2(const std::vector<std::string> &input) {
  std::vector<std::string> banks(input);
  ll sum = 0;
  for (const auto &bank : banks) {
    sum += GetMaxJoltage2(bank);
  }
  std::cout << "Part 2: " << sum << std::endl;
}

int main(int argc, char **argv) {
  if (argc != 1) {
    std::cerr << "ERROR: argc != 1. argc = " << argc << std::endl;
    return 1;
  }
  std::vector<std::string> input = GetInput(argc, argv);
  Part1(input);
  Part2(input);
  return 0;
}