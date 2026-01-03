#include <fstream>
#include <iostream>

constexpr int NUM_DIALS = 100;

int numClicksAtZero(char direction, int amount, int cur_pos) {
  if (direction == 'R') {
    return ((cur_pos + amount) / NUM_DIALS);
  }
  return (amount / NUM_DIALS) +
         ((cur_pos - (amount % NUM_DIALS)) <= 0 && cur_pos > 0);
}

int adjustDial(char direction, int amount, int cur_pos) {
  if (direction == 'R') {
    cur_pos = (cur_pos + amount) % NUM_DIALS;
  } else if (direction == 'L') {
    cur_pos = (cur_pos + (NUM_DIALS + ((amount * -1) % NUM_DIALS))) % NUM_DIALS;
  }
  return cur_pos;
}

int main() {
  std::ifstream infile("day01/input.txt");
  int ans = 0;
  int cur_pos = 50;
  std::string line;
  while (std::getline(infile, line)) {
    char direction = line[0];
    int amount = std::stoi(line.substr(1));
    // std::cout << "curpos: " << cur_pos << " dir: " << direction
    //           << ", amt: " << amount << std::endl;
    int num_clicks_at_zero = numClicksAtZero(direction, amount, cur_pos);
    // std::cout << "numzero: " << num_clicks_at_zero << std::endl;
    ans += num_clicks_at_zero;
    cur_pos = adjustDial(direction, amount, cur_pos);
  }
  std::ofstream output;
  output.open("day01/output2.txt");
  output << ans;
  output.close();
  infile.close();
  return 0;
}