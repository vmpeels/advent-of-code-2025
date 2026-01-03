#include "common.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

void pv(std::vector<std::string> &v) {
  for (const auto &e : v) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

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

std::vector<std::string> GetInput(int argc, char *const *const argv) {
  std::string path_string = argv[0];
  std::cout << "input file name: " << GetInputFilename(path_string)
            << std::endl;
  std::ifstream input(GetInputFilename(path_string));
  std::string line;
  std::vector<std::string> output;
  while (getline(input, line)) {
    output.push_back(line);
  }
  return output;
}