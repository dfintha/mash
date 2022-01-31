#if !defined(MASH_PARSER_PARSER)
#define MASH_PARSER_PARSER
#include "container.hpp"
#include <sstream>
#include <stdexcept>

namespace mash {
	mash::container parse_expression(const std::string& str);
}

#endif
