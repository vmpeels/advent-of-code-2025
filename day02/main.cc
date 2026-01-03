#include "absl/container/flat_hash_set.h"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

typedef long long ll;

std::string GetInputFilename(std::string path_string) {
  std::filesystem::path path(path_string);
  return path.parent_path().filename().generic_string() + "/" +
         path.filename().generic_string() + ".txt";
}

std::string GetOutputFilename(std::string path_string) {
  std::filesystem::path path(path_string);
  return path.parent_path().filename().generic_string() + "/output.txt";
}

void pv(std::vector<ll> &v) {
  for (ll e : v) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

// C++11 onwards actually has move-semantics for std::vector, so we can return
// this by "value". In fact, there might actually be elision! (Whatever that
// means).
// Source:
// https://stackoverflow.com/questions/15704565/efficient-way-to-return-a-stdvector-in-c
std::vector<std::string> split(const std::string &s,
                               const std::string &delimiter) {
  // Custom parsing because C++ doesn't make splitting a string easy...
  // Ripped from StackOverflow:
  // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c#comment44856986_14266139
  // Essentially, we just string find the first instance of a delimiter starting
  // from a given position. I've change this code to increment by the
  // delimiter's length rather than just 1.
  size_t last = 0;
  size_t next = 0;
  // Computes the next index of the delimiter.
  std::vector<std::string> tokens;
  while ((next = s.find(delimiter, last)) != std::string::npos) {
    // Get the next n characters, starting from position last.
    tokens.emplace_back(s.substr(last, next - last));
    last = next + delimiter.size();
  }

  // The above code won't handle the last token if there is no delimiter
  // following it, as string.find() will return n pos. EX: "a,b,c" with a comma
  // delimiter -- there is no "," following 'c', so string.find() will return
  // npos after finding the second comma. Last will hold the starting index of
  // the last token, so we just take the substring from last to the end.
  tokens.emplace_back(s.substr(last));
  return tokens;
}

std::vector<ll> GenerateInvalidNumbers(int num_digits) {
  // There are no invalid numbers that have an odd number of digits.
  if (num_digits % 2 != 0) {
    return {};
  }
  ll low = std::pow(10, (num_digits / 2) - 1);
  ll hi = std::pow(10, (num_digits / 2));
  // std::cout << "low: " << low << ", hi: " << hi << std::endl;
  std::vector<ll> invalid_nums;
  for (int i = low; i < hi; ++i) {
    invalid_nums.push_back(i * std::pow(10, (num_digits / 2)) + i);
  }
  return invalid_nums;
}

ll GetInvalidNumberSum(const std::string &lower, const std::string &upper) {
  ll lower_ll = std::stoll(lower);
  ll upper_ll = std::stoll(upper);
  ll sum = 0;
  for (int i = lower.size(); i <= upper.size(); ++i) {
    std::vector<ll> invalid_nums = GenerateInvalidNumbers(i);
    for (ll invalid_num : invalid_nums) {
      if (lower_ll <= invalid_num && invalid_num <= upper_ll) {
        sum += invalid_num;
      }
    }
  }
  return sum;
}

std::vector<ll> GenerateInvalidNumbers(int num_digits,
                                       int num_times_to_repeat) {
  ll low = std::pow(10, (num_digits)-1);
  ll hi = std::pow(10, (num_digits));
  std::vector<ll> invalid_nums;
  for (int i = low; i < hi; ++i) {
    // std::cout << "cur i: " << i << std::endl;
    ll sum = 0;
    // std::cout << "sum: " << sum << " ";
    for (int j = 0; j < num_times_to_repeat; ++j) {
      sum = sum * std::pow(10, (num_digits)) + i;
      // std::cout << sum << " ";
    }
    // std::cout << std::endl;
    // std::cout << "final sum: " << std::endl;
    invalid_nums.push_back(sum);
  }
  return invalid_nums;
}

ll GetInvalidNumberSumPart2(const std::string &lower,
                            const std::string &upper) {
  ll lower_ll = std::stoll(lower);
  ll upper_ll = std::stoll(upper);
  // std::cout << "Lower: " << lower << ", upper: " << upper << '\n';
  absl::flat_hash_set<ll> invalid_nums_set;
  ll sum = 0;
  for (int i = lower.size(); i <= upper.size(); ++i) {
    // std::cout << "finding factors for length: " << i << '\n';
    for (int factor = 1; factor < i; ++factor) {
      if (i % factor != 0) {
        continue;
      }
      // std::cout << "factor: " << factor << '\n';
      std::vector<ll> invalid_nums = GenerateInvalidNumbers(factor, i / factor);
      for (ll invalid_num : invalid_nums) {
        // std::cout << "invalid num: " << invalid_num << "\n";
        if (lower_ll <= invalid_num && invalid_num <= upper_ll) {
          // std::cout << "adding invalid num: " << invalid_num << '\n';
          invalid_nums_set.insert(invalid_num);
          // sum += invalid_num;
        }
      }
    }
  }
  for (ll e : invalid_nums_set) {
    sum += e;
  }
  return sum;
}

/*
Given a lower and upper bound
Let the length of lower and upper bound string be represented as len(lower),
len(upper) For i in  [len(lower), len(upper)]: Get all the factors of i. For
each factor of i except i itself, generate every number n with length i
concatenate n to itself until its length is i
if that number is between lower and upper, add it to the invalid nums list

We can retrofit the part 1 solution by adding a factors list and only using 2 in
the factors list.
*/

int main(int argc, char **argv) {
  if (argc != 1) {
    std::cerr << "ERROR: argc != 1. argc = " << argc << std::endl;
    return 1;
  }
  std::string path_string = argv[0];
  std::cout << "input file name: " << GetInputFilename(path_string)
            << std::endl;
  std::ifstream input(GetInputFilename(path_string));

  // Input is just one big line.
  std::string line;
  getline(input, line);
  ll sum_part1 = 0;
  ll sum_part2 = 0;
  std::vector<std::string> ranges = split(line, ",");
  for (const auto &range : ranges) {
    std::vector<std::string> bounds = split(range, "-");
    std::string lower = bounds[0];
    std::string upper = bounds[1];
    ll range_sum = GetInvalidNumberSum(lower, upper);
    sum_part1 += range_sum;
    sum_part2 += GetInvalidNumberSumPart2(lower, upper);
  }
  std::cout << "Part 1: " << sum_part1 << std::endl;
  std::cout << "Part 2: " << sum_part2 << std::endl;
  input.close();
  return 0;
}