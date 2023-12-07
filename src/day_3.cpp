//===----------------------------------------------------------------------===//
//
// Part of KatieUmbra's Solution for Advent Of Code 2023, under the MIT license
// See https://github.com/KatieUmbra/AoC2023/blob/main/LICENSE
// SPDX-License-Identifier: MIT
//
//===----------------------------------------------------------------------===//

#include "advent_days.hpp"
#include "advent_logging.hpp"
#include <__ranges/transform_view.h>
#include <array>
#include <cctype>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

namespace advent
{
struct engine_part
{
	std::size_t x, y;
	std::size_t number;
	std::size_t size;
};
static std::array<std::array<char, 140>, 140> engine_schema;
static void load_input()
{
	std::ifstream ifs{PROJECT_FOLDER "/inputs/day3"};
	auto i = 0;
	for (std::string line; std::getline(ifs, line);)
	{
		std::strncpy(reinterpret_cast<char*>(&engine_schema[i]), line.data(), 140);
		i++;
	}
}

static bool find_symbol(const engine_part& part)
{
	bool result = false;
	std::array<std::string_view, 3> svs;
	for (int i = -1; i < 2; i++)
	{
		if (result)
			break;
		if (part.y + i < 0 || part.y + i > 139)
			continue;
		auto start = engine_schema[part.y + i].begin();
		auto end = engine_schema[part.y + i].begin();
		if (part.x > 1)
			std::advance(start, part.x - 2);
		if (part.x + part.size > 139)
			end = engine_schema[part.y + i].end();
		else
			std::advance(end, part.x + part.size);
		std::string_view slice{start, end};
		svs[i + 1] = slice;
		auto filtered = std::views::filter(slice, [](char it) { return !(std::isdigit(it) || it == '.'); });
		result = !filtered.empty();
	}
	return result;
}
static void lexer(std::vector<char>& char_buffer, std::vector<engine_part>& number_buffer, std::size_t& x,
				  const std::size_t& y)
{
	for (; x < 140; x++)
	{
		char c = engine_schema[y][x];
		if (!std::isdigit(c))
		{
			if (char_buffer.empty())
			{
				continue;
			}
			std::string_view number{char_buffer.begin(), char_buffer.end()};
			std::uint16_t res;
			std::from_chars(number.data(), number.data() + number.size(), res);
			number_buffer.emplace_back(engine_part{x - number.size() + 1, y, res, number.size()});
			char_buffer.clear();
		}
		else
		{
			char_buffer.emplace_back(c);
		}
	}
}
static void puzzle_1()
{
	std::vector<engine_part> number_buffer{};
	std::vector<char> char_buffer{};
	std::uint64_t sum = 0;
	for (std::size_t y = 0; y < 140; y++)
	{
		std::size_t x = 0;
		lexer(char_buffer, number_buffer, x, y);
		if (!char_buffer.empty())
		{
			std::string_view number{char_buffer.begin(), char_buffer.end()};
			std::uint16_t res;
			std::from_chars(number.data(), number.data() + number.size(), res);
			number_buffer.emplace_back(engine_part{x - number.size() + 1, y, res, number.size()});
			char_buffer.clear();
		}
	}
	for (const auto& part : number_buffer)
	{
		if (find_symbol(part))
		{
			sum += part.number;
		}
	}
	std::string output{std::string("The sum of all parts adjacent to a symbol is: ") + std::to_string(sum)};
	advent::log(output.c_str(), message_type::RESULT);
}
struct engine_part_star
{
	std::size_t x, y;
	std::size_t star_x, star_y;
	std::size_t number;
	std::size_t size;
	engine_part_star(const engine_part& copy) : x{copy.x}, y{copy.y}, number{copy.number}, size{copy.size}
	{
	}
};
static void puzzle_2()
{
	std::vector<engine_part> number_buffer{};
	std::vector<char> char_buffer{};
	std::uint64_t sum = 0;
	for (std::size_t y = 0; y < 140; y++)
	{
		std::size_t x = 0;
		lexer(char_buffer, number_buffer, x, y);
		if (!char_buffer.empty())
		{
			std::string_view number{char_buffer.begin(), char_buffer.end()};
			std::uint16_t res;
			std::from_chars(number.data(), number.data() + number.size(), res);
			number_buffer.emplace_back(engine_part{x - number.size() + 1, y, res, number.size()});
			char_buffer.clear();
		}
	}
	std::vector<engine_part_star> star_buffer;
	auto transformed = number_buffer | std::views::transform([](const auto& it) { return engine_part_star(it); });
	for (auto&& a : transformed)
		star_buffer.emplace_back(a);
}
void day_3()
{
	advent::log("Advent Of Code, Day 3", message_type::DAY);
	load_input();
	advent::log("Puzzle 1", message_type::PUZZLE);
	puzzle_1();
	advent::log("Puzzle 2", message_type::PUZZLE);
	puzzle_2();
}
} // namespace advent
