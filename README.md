# Advent of Code 2025

These are my solutions to Advent of Code 2025. Unlike last year, I'll write all my solutions in C++ as an exercise for myself.

## Quick info
- Solutions are written in C++
- I'm not aiming for any leaderboard placements
- No guarantee on the optimality of the solutions either
- Bazel build system
- Each solution is organized into its own folder with an input file

## Commands + Quick development tips

To run a solution for a particular day, run the following command:

`bazel run //<day folder>:main`

To create another solution:
- Easiest way to do this is to copy an existing solution folder and edit it.

To view output files:
- This part is stupid. Bazel doesn't allow you to write to the workspace directory. So right now, the best way to find the output files is to navigate to `bazel-bin/<dayx>/main.runfiles/_main/<dayx>/` and find the output file there.
- I will find a workaround for this eventually.# advent-of-code-2025
C++ Solutions to Advent of Code 2025
