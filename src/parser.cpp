#include "container.hpp"
#include "expr_binary.hpp"
#include "expr_unary.hpp"
#include "parser.hpp"
#include "tokens.hpp"
#include "utilities.hpp"

using unaryptr = std::shared_ptr<mash::unary_function>;
using binaryptr = std::shared_ptr<mash::binary_function>;
using mash::exprptr;

#include <iostream>
namespace {
	static unaryptr make_unary(const std::string& name, exprptr expr) {
		#define map(fun, type) \
			if (name == #fun) return std::make_shared<type>(expr);
		map(-, mash::negative);
		map(sin, mash::sine);
		map(cos, mash::cosine);
		map(tan, mash::tangent);
		map(tg, mash::tangent);
		map(ctg, mash::cotangent);
		map(sec, mash::secant);
		map(csc, mash::cosecant);
		map(ln, mash::logn);
		map(sqrt, mash::square_root);
		map(cbrt, mash::cubic_root);
		#undef map
		throw std::logic_error("invalid function name");
	}

	static binaryptr make_binary(const std::string& name, exprptr lhs, exprptr rhs) {
		#define map(fun, type) \
			if (name == #fun) return std::make_shared<type>(lhs, rhs)
		map(+, mash::addition);
		map(-, mash::subtraction);
		map(*, mash::multiplication);
		map(/, mash::division);
		map(^, mash::power);
		#undef map
		throw std::logic_error("invalid function name");
	}

	static double strnum(const std::string& str) {
		std::stringstream stream(str);
		double result;
		stream >> result;
		return result;
	}

	static mash::token create_token(std::stringstream& stream) {
		mash::token result;
		result.read(stream);
		return result;
	}

	static mash::token create_token(const std::string& tok) {
		std::stringstream stream(tok);
		return create_token(stream);
	}

	static mash::exprptr parse_tree(const mash::token& tok) {
		switch (tok.argcount()) {
			case 0:
				if (tok.name() == "x")
					return std::make_shared<mash::variable>();
				if (tok.name() == "e")
					return std::make_shared<mash::constant>(mash::const_e);
				if (tok.name() == "pi")
					return std::make_shared<mash::constant>(mash::const_pi);
				return std::make_shared<mash::constant>(strnum(tok.name()));
			case 1:
				return make_unary(tok.name(), parse_tree(tok.arg(0)));
			case 2:
				return make_binary(tok.name(), parse_tree(tok.arg(0)), parse_tree(tok.arg(1)));
			default:
				throw std::logic_error("incorrect syntax");
		}
	}
}

namespace mash {
	mash::container parse_expression(const std::string& str) {
		return parse_tree(create_token(str));
	}
}
