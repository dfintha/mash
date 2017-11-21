#if !defined(MASH_PARSER_PARSER)
#define MASH_PARSER_PARSER
#include "expressions/container.hpp"
#include <sstream>
#include <stdexcept>

namespace mash_p {
	mash_e::container parse_expression(const std::string& str);
}

#endif
