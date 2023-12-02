//===----------------------------------------------------------------------===//
//
// Part of KatieUmbra's Solution for Advent Of Code 2023, under the MIT license
// See https://github.com/KatieUmbra/AoC2023/blob/main/LICENSE
// SPDX-License-Identifier: MIT
//
//===----------------------------------------------------------------------===//

#pragma once

#include <array>
#include <string>
#include <unordered_map>
namespace advent
{
enum class message_type : short
{
	DAY = 0,
	PUZZLE = 1,
	RESULT = 2
};
inline const char* prefix_code{"\033"};
inline const char* reset_code{"\033[0m"};
inline constexpr std::array<const char*, 3> prefix_map{"[DAY]", "[PUZZLE]", "[RESULT]"};
inline constexpr std::array<const char*, 3> prefix_color{"[38;5;197m", "[38;5;222m", "[38;5;14m"};
void log(const char* message, message_type type);
} // namespace advent
