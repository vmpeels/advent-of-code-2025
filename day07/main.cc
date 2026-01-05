#include "common/common.h"
#include <iostream>
#include <queue>
#include <vector>

constexpr char SPLITTER = '^';

void Part1(const std::vector<std::string> input) {
  ll ans = 0;

  // Unnecessary copy, but let's convert the input in the puzzle's abstraction.
  // Also allows us to modify the input if necessary.
  std::vector<std::string> manifold(input);

  // We'll simulate the beam splitting and then count how many splitters were
  // hit.

  struct rc {
    ll row = -1;
    ll col = -1;
  };

  // First, find the coordinate of the starting point.
  int row = 0;
  int col = 0;
  for (int j = 0; j < input[0].size(); ++j) {
    if (input[0][j] == 'S') {
      col = j;
      break;
    }
  }

  ll max_row = manifold.size();
  ll max_col = manifold[0].size();
  auto inb = [max_row, max_col](rc rc) -> bool {
    return 0 <= rc.row && rc.row < max_row && 0 <= rc.col && rc.col < max_col;
  };

  rc start{.row = row, .col = col};
  ll count = 0;
  std::queue<rc> q;
  q.push(start);
  std::vector<std::vector<bool>> visited(
      input.size(), std::vector<bool>(input[0].size(), false));
  visited[start.row][start.col] = true;

  while (!q.empty()) {
    // We can assume cur is always inbounds.
    rc cur = q.front();
    char c = input[cur.row][cur.col];

    // Check if we hit a splitter. If so, append two to the left and the right
    // if inb. Otherwise, we just go downwards.
    if (c == SPLITTER) {
      count++;
      rc left{.row = cur.row, .col = cur.col - 1};
      if (inb(left) && !visited[left.row][left.col]) {
        q.push(left);
        visited[left.row][left.col] = true;
      }
      rc right{.row = cur.row, .col = cur.col + 1};
      if (inb(right) && !visited[right.row][right.col]) {
        q.push(right);
        visited[right.row][right.col] = true;
      }
    } else {
      rc down{.row = cur.row + 1, .col = cur.col};
      if (inb(down) && !visited[down.row][down.col]) {
        q.push(down);
        visited[down.row][down.col] = true;
      }
    }
    q.pop();
  }
  ans = count;
  std::cout << "Part1: " << ans << std::endl;
  return;
}

void Part2(const std::vector<std::string> input) {
  ll ans = 0;

  // Unnecessary copy, but let's convert the input in the puzzle's abstraction.
  // Also allows us to modify the input if necessary.
  std::vector<std::string> manifold(input);
  ll max_row = manifold.size();
  ll max_col = manifold[0].size();
  auto inb = [max_row, max_col](int row, int col) -> bool {
    return 0 <= row && row < max_row && 0 <= col && col < max_col;
  };

  // We'll implement this as a bottom up DP. timelines[i][j] tells us the number
  // of timelines that exist if a beam is going downwards at locations (i, j)
  std::vector<std::vector<ll>> timelines(max_row, std::vector<ll>(max_col, -1));

  // Bottom row is the base case. There is one timeline if we reach the bottom
  // row.
  for (int col = 0; col < max_col; ++col) {
    timelines[max_row - 1][col] = 1;
  }

  for (int row = (max_row - 1) - 1; row >= 0; --row) {
    // We can do this in 1 pass but the 2 pass approach is a little cleaner.
    // First find the values for all non-splitter values.
    for (int col = 0; col < max_col; ++col) {
      char c = input[row][col];
      if (c != SPLITTER) {
        timelines[row][col] = timelines[row + 1][col];
      }
    }

    // Now calculate the values for all the splitters.
    for (int col = 0; col < max_col; ++col) {
      char c = input[row][col];
      if (c == SPLITTER) {
        int left = col - 1;
        int right = col + 1;
        ll val = 0;
        if (inb(row, left)) {
          val += timelines[row][left];
        }
        if (inb(row, right)) {
          val += timelines[row][right];
        }
        timelines[row][col] = val;
      }
    }
  }

  // Finally, find the value of the start point.
  for (int j = 0; j < manifold[0].size(); ++j) {
    if (manifold[0][j] == 'S') {
      ans = timelines[0][j];
      break;
    }
  }

  std::cout << "Part2: " << ans << std::endl;
  return;
}

int main(int argc, char **argv) {
  if (argc != 1) {
    std::cerr << "argc != 1" << std::endl;
    return 1;
  }
  Part1(GetInput(argc, argv));
  Part2(GetInput(argc, argv));
  return 0;
}