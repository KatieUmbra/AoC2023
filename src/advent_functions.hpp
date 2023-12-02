//===----------------------------------------------------------------------===//
//
// Part of KatieUmbra's Solution for Advent Of Code 2023, under the MIT license
// See https://github.com/KatieUmbra/AoC2023/blob/main/LICENSE
// SPDX-License-Identifier: MIT
//
//===----------------------------------------------------------------------===//

#pragma once

#include <array>
#include <cstddef>

namespace advent
{
inline std::byte day{1};
inline std::array<void (*)(), 31> advent_functions{};
void register_functions();
} // namespace advent
