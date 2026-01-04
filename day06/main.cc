#include "common/common.h"
#include <algorithm>
#include <iostream>

constexpr char ADD_SYMBOL = '+';
constexpr char MULTIPLY_SYMBOL = '*';

void Part1(const std::vector<std::string> input) {
  ll ans = 0;

  std::vector<std::vector<ll>> numbers;
  std::vector<char> operators;
  for (int i = 0; i < input.size(); ++i) {
    std::vector<std::string> splitline = split(input[i], " ");
    if (i == input.size() - 1) {
      for (std::string s : splitline) {
        operators.push_back(s[0]);
      }
      continue;
    }
    std::vector<ll> n;
    std::for_each(splitline.begin(), splitline.end(),
                  [&n](const std::string &s) { n.push_back(std::stoll(s)); });
    numbers.push_back(n);
  }
  for (int j = 0; j < numbers[0].size(); ++j) {
    char op = operators[j];
    ll sum = (op == ADD_SYMBOL) ? 0 : 1;
    for (int i = 0; i < numbers.size(); ++i) {
      switch (op) {
      case ADD_SYMBOL:
        sum += numbers[i][j];
        break;
      case MULTIPLY_SYMBOL:
        sum *= numbers[i][j];
        break;
      }
    }
    ans += sum;
  }

  std::cout << "Part 1: " << ans << std::endl;
  return;
}

void Part2(const std::vector<std::string> input) {
  ll ans = 0;

  // Instead of splitting the numbers by space, we have to actually read the
  // numbers from right-to-left.

  // We'll need to separate by empty column, and we can compute the sum in
  // place.
  ll linelen = input[0].size() - 1;
  std::vector<ll> numbers;
  char op = ' ';
  int col = linelen;
  while (col >= 0) {
    ll num = 0;
    bool found_op = false;
    // std::cout << "-----" << std::endl;
    // std::cout << "cur column: " << col << std::endl;
    for (int row = 0; row < input.size() - 1; ++row) {
      if (input[row][col] != ' ') {
        ll digit = input[row][col] - '0';
        num = num * 10 + digit;
      }
    }
    // The last row only contains operators or empty spaces. If we find an
    // operator, then we need to record it and use it when we compute the sum.
    // We should expect the input to be normal and follow that there will only
    // be 1 operator for every set of numbers.
    if (input[input.size() - 1][col] != ' ') {
      op = input[input.size() - 1][col];
      // std::cout << "found op " << op << "at: " << input.size() - 1 << ", "
      //           << col << std::endl;

      found_op = true;
    } else {
      // std::cout << "char at " << input.size() - 1 << ", " << col << " is
      // empty"
      // << std::endl;
    }
    if (found_op) {
      numbers.push_back(num);
      // Now we can compute the sum and add to our answer, and then reset the
      // vector to process the next group of numbers.
      ll sum = 0;
      // std::cout << "op: " << op << std::endl;
      switch (op) {
      case ADD_SYMBOL:
        sum = 0;
        break;
      case MULTIPLY_SYMBOL:
        sum = 1;
        break;
      }

      for (const auto num : numbers) {
        // std::cout << "num: " << num << std::endl;
        switch (op) {
        case ADD_SYMBOL:
          sum += num;
          break;
        case MULTIPLY_SYMBOL:
          sum *= num;
          break;
        }
      }

      // std::cout << "sum: " << sum << std::endl;

      ans += sum;

      // Reset our numbers and our op.
      numbers.clear();
      op = ' ';
      // Skip the next column since it's guaranteed to be empty.
      --col;
    } else {
      numbers.push_back(num);
    }
    --col;
  }

  std::cout << "Part 2: " << ans << std::endl;
  return;
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