//===----------------------------------------------------------------------===//
//
// Part of KatieUmbra's Solution for Advent Of Code 2023, under the MIT license
// See https://github.com/KatieUmbra/AoC2023/blob/main/LICENSE
// SPDX-License-Identifier: MIT
//
//===----------------------------------------------------------------------===//

#include <algorithm>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <ranges>
#include <span>
#include <string_view>
#include <system_error>

#include "advent_days.hpp"
#include "advent_functions.hpp"

void advent::register_functions()
{
	advent::advent_functions[0] = advent::day_1;
	advent::advent_functions[1] = advent::day_2;
	advent::advent_functions[2] = advent::day_3;
}

auto main(int argc, char const* argv[]) -> int
{
	auto arguments = std::span(argv, argc) | std::views::transform([](char const* it) { return std::string_view{it}; });
	auto first_argument = arguments[1];
	bool is_number = !first_argument.empty() &&
					 std::find_if(first_argument.begin(), first_argument.end(),
								  [](unsigned char it) { return std::isdigit(it); }) != first_argument.end();
	if (!is_number)
	{
		std::cerr << "The first argument must be a positive integer!" << '\n';
		std::terminate();
	};
	std::uint32_t result;
	auto status = std::from_chars(first_argument.data(), first_argument.data() + first_argument.size(), result);
	if (status.ec == std::errc::invalid_argument)
	{
		std::cerr << "Error parsing argument" << '\n';
		std::terminate();
	}
	if (result > 31)
	{
		std::cerr << "Index out of bounds [0, 30]" << '\n';
		std::terminate();
	}
	if (result > std::to_integer<std::uint32_t>(advent::day))
	{
		std::cerr << "Day " << result << " has not ocurred yet, stay tuned for updates!" << '\n';
		std::terminate();
	}
	std::cout << "-->     Katherine's AoC2023 Solution!     <--" << '\n';
	std::cout << "--> https://github.com/KatieUmbra/AoC2023 <--" << '\n';
	advent::register_functions();
	advent::advent_functions[result - 1]();
}
