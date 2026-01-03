#include "common/common.h"
#include <iostream>
#include <vector>

int main(int argc, char **argv) {

  std::vector<std::string> input = GetInput(argc, argv);
  pv(input);
  return 0;
}