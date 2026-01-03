#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

typedef long long ll;

std::string GetInputFilename(std::string path_string);

std::string GetOutputFilename(std::string path_string);

// TODO(vmpeels): Make this templated?
void pv(std::vector<ll> &v);
void pv(std::vector<std::string> &v);

// C++11 onwards actually has move-semantics for std::vector, so we can return
// this by "value". In fact, there might actually be elision! (Whatever that
// means).
// Source:
// https://stackoverflow.com/questions/15704565/efficient-way-to-return-a-stdvector-in-c
std::vector<std::string> split(const std::string &s,
                               const std::string &delimiter);

// Reads the input from the Advent of Code sample or actual file and returns it
// as a vector of strings where each line represents an entry in the vector.
// IMPORTANT: For this to work, main MUST be defined with the argc and argv
// parameters, and it is up to the user (i.e. ... ME ...) to do error checking
// on the arguments to ensure correctness.
std::vector<std::string> GetInput(int argc, char *const *const argv);
#endif