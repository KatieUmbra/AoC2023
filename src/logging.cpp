#include "advent_logging.hpp"
#include <iostream>
#include <sstream>

void advent::log(const char* message, message_type type)
{
	std::ostringstream ss{};
	short type_s = static_cast<short>(type);
	ss << prefix_code << prefix_color[type_s] << prefix_map[type_s] << ": " << prefix_code << "[38;5;7m" << message
	   << reset_code;
	std::cout << ss.str() << '\n';
}
