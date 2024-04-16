# Advent of code year 2023
By Katherine, [AOC23](https://adventofcode.com/2023)

## THIS PROJECT COULD NOT BE COMPLETED DUE TO TECHNICAL ISSUES.

## How to run

### Requirements

I'm doing this project on Artix 6.6.2 but it should work on any other OS
- CMake
- Make/Ninja/Visual Studio 17 2022
- A C++20 compliant compiler (MSVC, clang, gcc)

### Setup

- Create a folder in the project root called inputs `mkdir inputs` and add day inputs the following way

    ```
    // inputs/day1
    1abc2
    pqr3stu8vwx
    a1b2c3d4e5f
    treb7uchet
    ...
    ```

### Building

- Run `cmake -B build`, `Make` generator works, but `Ninja` is preferred `cmake -B build -G Ninja`, alternatively use Visual Studio if you're on windows (should work with mingw aswell) `cmake -B build -G "Visual Studio 17 2022"`
- Run `cmake --build build` to compile the exectuable
- Run a puzzle by running `./build/aoc {NUMBER OF THE DAY}`

Example

```sh
cmake -B build -G Ninja
cmake --build build
./build/aoc 1
#Output:
"
Advent Of Code, Day 1
Puzzle 1:
The sum of all calibration values is: XXXXX
Puzzle 2:
...
"
```

### Current state

- 1 **
- 2 **
- 3 *
- 4
- 5
- 6
- 7
