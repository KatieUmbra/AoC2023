//===----------------------------------------------------------------------===//
//
// Part of KatieUmbra's Solution for Advent Of Code 2023, under the MIT license
// See https://github.com/KatieUmbra/AoC2023/blob/main/LICENSE
// SPDX-License-Identifier: MIT
//
//===----------------------------------------------------------------------===//

#include <cstdint>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "advent_days.hpp"

using cstr_t = const char*;

namespace advent
{
static std::unordered_map<std::string_view, std::string_view> replacements{
	{"one", "1"}, {"two", "2"},	  {"three", "3"}, {"four", "4"}, {"five", "5"},
	{"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};
static std::array<std::string_view, 9> numbers{"1", "2", "3", "4", "5", "6", "7", "8", "9"};
static void puzzle_1()
{
	std::ifstream input_file{PROJECT_FOLDER "/inputs/day1"};
	std::uint32_t sum = 0;
	for (std::string line; std::getline(input_file, line);)
	{
		auto numeric_chars = line | std::ranges::views::filter([](char it) { return it > 47 && it < 58; });
		std::string number{numeric_chars.front(), numeric_chars.back()};
		sum += std::stoi(number);
	}
	std::cout << "The sum of all calibration values is: " << sum << '\n';
}
static void find_all(const std::string& str, std::vector<std::pair<std::string_view, std::size_t>>& strings,
					 const std::string_view& find, std::optional<std::string_view> replace = std::nullopt)
{
	std::size_t pos = str.find(find, 0);
	while (pos != std::string::npos)
	{
		if (replace.has_value())
		{
			strings.emplace_back(std::pair{replace.value(), pos});
		}
		else
		{
			strings.emplace_back(std::pair{find, pos});
		}
		pos = str.find(find, pos + 1);
	}
}
static void puzzle_2()
{
	std::ifstream input_file{PROJECT_FOLDER "/inputs/day1"};
	std::uint32_t sum = 0;
	for (std::string line; std::getline(input_file, line);)
	{
		using qpair_t = std::pair<std::string_view, std::size_t>;
		std::vector<qpair_t> line_chars;
		for (auto& [k, v] : replacements)
		{
			find_all(line, line_chars, k, std::optional{v});
		}
		for (auto& num : numbers)
		{
			find_all(line, line_chars, num);
		}
		std::ranges::sort(line_chars.begin(), line_chars.end(),
						  [](const qpair_t& a, const qpair_t& b) { return a.second > b.second; });
		std::string front_num{line_chars.front().first};
		std::string back_num{line_chars.back().first};
		std::string number{back_num + front_num};
		sum += std::stoi(number);
	}
	std::cout << "The sum of all calibration values, including typed values, is: " << sum << '\n';
}
void day_1()
{
	std::cout << "Advent Of Code, Day 1" << '\n';
	std::cout << "Puzzle 1:" << '\n';
	puzzle_1();
	std::cout << "Puzzle 2:" << '\n';
	puzzle_2();
}
} // namespace advent
