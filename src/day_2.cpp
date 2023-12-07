//===----------------------------------------------------------------------===//
//
// Part of KatieUmbra's Solution for Advent Of Code 2023, under the MIT license
// See https://github.com/KatieUmbra/AoC2023/blob/main/LICENSE
// SPDX-License-Identifier: MIT
//
//===----------------------------------------------------------------------===//

#include "advent_logging.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace advent
{
enum class cube_color
{
	RED,
	GREEN,
	BLUE
};
static std::unordered_map<std::string_view, cube_color> color_map{
	{"red", cube_color::RED}, {"green", cube_color::GREEN}, {"blue", cube_color::BLUE}};
struct cube
{
	std::uint16_t amount;
	cube_color color;
};
static auto split_ss(const std::string_view& str, char delim)
{
	return std::views::split(str, delim) | std::views::transform([](auto&& it) {
			   return std::string_view{it.begin(), std::ranges::size(it)};
		   });
}
std::vector<cube> cubes_from_line(std::string&& line)
{
	std::string_view line_view{line.begin() + (line.find(':') + 1), line.end()};
	std::vector<cube> vec;
	auto sets = split_ss(line_view, ';');
	for (const auto& set : sets)
	{
		auto cubes = split_ss(set, ',');
		for (const auto& cube : cubes)
		{
			auto cube_range = split_ss(cube, ' ');
			std::string back{};
			std::string_view front{};
			for (const auto& it : cube_range)
			{
				if (it.empty())
					continue;
				if (back.empty())
				{
					back = std::string{it};
					continue;
				}
				front = it;
			}
			std::uint16_t number = std::stoi(back);
			cube_color last = color_map[front];
			struct cube cbe
			{
				number, last
			};
			vec.emplace_back(cbe);
		}
	}
	return vec;
}
static void puzzle_1()
{
	std::ifstream input_file{PROJECT_FOLDER "/inputs/day2"};
	std::uint32_t sum = 0;
	for (std::string line; std::getline(input_file, line);)
	{
		auto vec = cubes_from_line(std::move(line));
		std::array<std::uint16_t, 3> cube_count{0, 0, 0};
		constexpr std::array<std::uint16_t, 3> target{12, 13, 14};
		for (const auto& cb : vec)
		{
			switch (cb.color)
			{
			case cube_color::RED:
				cube_count[0] = std::max(cube_count[0], cb.amount);
			case cube_color::GREEN:
				cube_count[1] = std::max(cube_count[1], cb.amount);
			case cube_color::BLUE:
				cube_count[2] = std::max(cube_count[2], cb.amount);
			}
		}
		if (cube_count[0] <= 12 && cube_count[1] <= 13 && cube_count[2] <= 14)
		{
			auto out = std::string{std::string_view{line.begin() + line.find(' ') + 1, line.begin() + line.find(':')}};
			sum += std::stoi(out);
		}
	}
	std::string output{std::string("The sum of all ids in which the game is possible is: ") + std::to_string(sum)};
	advent::log(output.c_str(), message_type::RESULT);
}
static std::uint32_t lowest(const std::vector<cube>& vec, cube_color color)
{
	auto collection = vec | std::views::filter([=](const cube& it) { return it.color == color; });
	std::uint32_t lowest = 0;
	for (const cube& element : collection)
	{
		if (element.amount > lowest)
			lowest = element.amount;
	}
	return lowest;
}
static void puzzle_2()
{
	std::ifstream input_file{PROJECT_FOLDER "/inputs/day2"};
	std::uint32_t sum = 0;
	for (std::string line; std::getline(input_file, line);)
	{
		auto vec = cubes_from_line(std::move(line));
		auto lowest_red = lowest(vec, cube_color::RED);
		auto lowest_green = lowest(vec, cube_color::GREEN);
		auto lowest_blue = lowest(vec, cube_color::BLUE);
		sum += lowest_red * lowest_green * lowest_blue;
	}
	std::string output{std::string("The sum of all powers of all sets of cubes: ") + std::to_string(sum)};
	advent::log(output.c_str(), message_type::RESULT);
}
void day_2()
{
	advent::log("Advent Of Code, Day 2", message_type::DAY);
	advent::log("Puzzle 1", message_type::PUZZLE);
	puzzle_1();
	advent::log("Puzzle 2", message_type::PUZZLE);
	puzzle_2();
}
} // namespace advent
