#include "common/common.h"
#include <algorithm>
#include <iostream>

struct range {
  ll lower = -1;
  ll upper = -1;
};

std::string tostring(range r) {
  return "(" + std::to_string(r.lower) + "," + std::to_string(r.upper) + ")";
}

void Part1(const std::vector<std::string> input) {
  ll ans = 0;

  std::vector<range> fresh_ingredient_ranges;
  std::vector<ll> ingredients;
  bool read_ingredients = false;
  for (const auto &line : input) {
    if (line.empty()) {
      read_ingredients = true;
      continue;
    }
    if (!read_ingredients) {
      std::vector<std::string> range = split(line, "-");
      fresh_ingredient_ranges.push_back(
          {.lower = std::stoll(range[0]), .upper = std::stoll(range[1])});
    } else {
      ingredients.push_back(std::stoll(line));
    }
  }

  // Just loop through each range and check if the ingredient is in the range.
  // While we certainly can be more efficient, this algorithm is fast enough to
  // find the answer. There are 185 ranges and 1000 ingredients, meaning this
  // will only take 185k lookups in the worst case.

  for (ll ingredient : ingredients) {
    bool is_fresh = false;
    for (range r : fresh_ingredient_ranges) {
      if (r.lower <= ingredient && ingredient <= r.upper) {
        is_fresh = true;
        break;
      }
    }
    ans += is_fresh;
  }
  std::cout << "Part 1: " << ans << std::endl;
  return;
}

void Part2(const std::vector<std::string> input) {
  ll ans = 0;

  struct bound {
    ll val;
    bool is_lower_bound;
  };

  std::vector<bound> bounds;
  for (const auto &line : input) {
    if (line.empty()) {
      // We don't need the ingredients for part 2.
      break;
    }
    std::vector<std::string> range = split(line, "-");
    bounds.push_back({.val = std::stoll(range[0]), .is_lower_bound = true});
    bounds.push_back({.val = std::stoll(range[1]), .is_lower_bound = false});
  }

  // Simply merge the ranges. This is a classical algorithm.
  sort(bounds.begin(), bounds.end(), [](bound a, bound b) {
    if (a.val == b.val) {
      return a.is_lower_bound;
    }
    return a.val < b.val;
  });

  ll bound_delta = 0;
  ll cur_lower = 0;
  for (bound b : bounds) {
    if (b.is_lower_bound) {
      if (bound_delta == 0) {
        cur_lower = b.val;
      }
      bound_delta++;
    } else {
      bound_delta--;
      if (bound_delta == 0) {
        ans += b.val - cur_lower + 1;
        cur_lower = 0;
      }
    }
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