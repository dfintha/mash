#include "expressions/container.hpp"
#include "expressions/binary.hpp"
#include "expressions/unary.hpp"
#include "parser/parser.hpp"
#include "parser/tokens.hpp"
#include "utilities.hpp"

using unaryptr = std::shared_ptr<mash_e::unary_function>;
using binaryptr = std::shared_ptr<mash_e::binary_function>;
using mash_e::exprptr;

#include <iostream>
namespace {
	static unaryptr make_unary(const std::string& name, exprptr expr) {
		#define map(fun, type) \
			if (name == #fun) return std::make_shared<type>(expr);
		map(-, mash_e::negative);
		map(sin, mash_e::sine);
		map(cos, mash_e::cosine);
		map(tan, mash_e::tangent);
		map(tg, mash_e::tangent);
		map(ctg, mash_e::cotangent);
		map(sec, mash_e::secant);
		map(csc, mash_e::cosecant);
		map(ln, mash_e::logn);
		map(sqrt, mash_e::square_root);
		map(cbrt, mash_e::cubic_root);
		#undef map
		throw std::logic_error("invalid function name");
	}

	static binaryptr make_binary(const std::string& name, exprptr lhs, exprptr rhs) {
		#define map(fun, type) \
			if (name == #fun) return std::make_shared<type>(lhs, rhs)
		map(+, mash_e::addition);
		map(-, mash_e::subtraction);
		map(*, mash_e::multiplication);
		map(/, mash_e::division);
		map(^, mash_e::power);
		#undef map
		throw std::logic_error("invalid function name");
	}

	static double strnum(const std::string& str) {
		std::stringstream stream(str);
		double result;
		stream >> result;
		return result;
	}

	static mash_p::token create_token(std::stringstream& stream) {
		mash_p::token result;
		result.read(stream);
		return result;
	}

	static mash_p::token create_token(const std::string& tok) {
		std::stringstream stream(tok);
		return create_token(stream);
	}

	static mash_e::exprptr parse_tree(const mash_p::token& tok) {
		switch (tok.argcount()) {
			case 0:
				if (tok.name() == "x")
					return std::make_shared<mash_e::variable>();
				if (tok.name() == "e")
					return std::make_shared<mash_e::constant>(mash_e::const_e);
				if (tok.name() == "pi")
					return std::make_shared<mash_e::constant>(mash_e::const_pi);
				return std::make_shared<mash_e::constant>(strnum(tok.name()));
			case 1:
				return make_unary(tok.name(), parse_tree(tok.arg(0)));
			case 2:
				return make_binary(tok.name(), parse_tree(tok.arg(0)), parse_tree(tok.arg(1)));
			default:
				throw std::logic_error("incorrect syntax");
		}
	}
}

namespace mash_p {
	mash_e::container parse_expression(const std::string& str) {
		return parse_tree(create_token(str));
	}
}
