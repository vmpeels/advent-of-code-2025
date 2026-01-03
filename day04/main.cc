#include "common/common.h"
#include <iostream>
#include <vector>

constexpr char PAPER_SYMBOL = '@';
constexpr char REMOVED_PAPER_SYMBOL = 'x';

void Part1(const std::vector<std::string> &input) {
  int ans = 0;

  // Unnecessary but let's put convert the input into the problem's abstraction.
  std::vector<std::string> grid(input);
  int max_row = grid.size();
  int max_col = grid[0].size();
  auto inb = [max_row, max_col](int i, int j) -> bool {
    return 0 <= i && i < max_row && 0 <= j && j < max_col;
  };
  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      char cur = grid[i][j];
      if (cur != PAPER_SYMBOL)
        continue;
      int num_rolls_surrounding = 0;
      for (int di : {-1, 0, 1}) {
        for (int dj : {-1, 0, 1}) {
          if (di == 0 && dj == 0)
            continue;
          num_rolls_surrounding +=
              (inb(i + di, j + dj) && grid[i + di][j + dj] == PAPER_SYMBOL);
        }
      }
      ans += (num_rolls_surrounding < 4);
    }
  }

  std::cout << "Part 1: " << ans << std::endl;
  return;
}

void Part2(const std::vector<std::string> &input) {
  int ans = 0;

  // Unnecessary but let's put convert the input into the problem's abstraction.
  std::vector<std::string> grid(input);
  int max_row = grid.size();
  int max_col = grid[0].size();
  auto inb = [max_row, max_col](int i, int j) -> bool {
    return 0 <= i && i < max_row && 0 <= j && j < max_col;
  };
  auto accessible_by_forklift = [&grid, &inb](int i, int j) -> bool {
    int num_rolls_surrounding = 0;
    for (int di : {-1, 0, 1}) {
      for (int dj : {-1, 0, 1}) {
        if (di == 0 && dj == 0)
          continue;
        num_rolls_surrounding +=
            (inb(i + di, j + dj) && grid[i + di][j + dj] == PAPER_SYMBOL);
      }
    }
    return num_rolls_surrounding < 4;
  };
  bool can_remove_rolls = true;
  std::vector<std::string> grid_buffer(grid);
  while (can_remove_rolls) {
    can_remove_rolls = false;
    for (int i = 0; i < max_row; ++i) {
      for (int j = 0; j < max_col; ++j) {
        char cur = grid[i][j];
        if (cur != PAPER_SYMBOL)
          continue;
        if (accessible_by_forklift(i, j)) {
          ans++;
          grid_buffer[i][j] = REMOVED_PAPER_SYMBOL;
          can_remove_rolls = true;
        }
      }
    }
    grid = grid_buffer;
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