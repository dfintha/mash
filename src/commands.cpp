#include "db/database.hpp"
#include "expressions/container.hpp"
#include "parser/parser.hpp"
#include "system/system.hpp"
#include "commands.hpp"
#include "messages.hpp"
#include "plot.hpp"
#include "utilities.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

namespace {
	static bool valid_name(const std::string& name) {
		if (!std::isalpha(name[0])) {
			cache_msg(err_invalid_name_letter, nullptr);
			return false;
		}

		if (name == "x") {
			cache_msg(err_invalid_name_x, nullptr);
			return false;
		}

		for (const auto c : name) {
			if (!std::isalnum(c) && c != '_') {
				cache_msg(err_invalid_name_chars, nullptr);
				return false;
			}
		}

		return true;
	}

	static bool valid_expr(const std::string& expr) {
		const bool equal = std::count(expr.begin(), expr.end(), '(') ==
			   			   std::count(expr.begin(), expr.end(), ')');
		if (!equal) {
			cache_msg(err_invalid_parens, nullptr);
			return false;
		}

		const bool nodouble = expr.find("((") == std::string::npos;
		if (!nodouble) {
			cache_msg(err_invalid_double_parens, nullptr);
			return false;
		}

		return true;
	}

	static bool print_string(const std::string& exprstr) {
		size_t where = 1;
		while (exprstr[where] != '\'' && where < exprstr.length()) {
			std::cout << exprstr[where++];
			if (where == exprstr.length()) {
				std::cout << nl;
				cache_msg(err_invalid_string, nullptr);
				return false;
			}
		}
		std::cout << nl;
		return true;
	}

	static bool print_expr(const std::string& exprstr) {
		if (!valid_expr(exprstr))
			return false;
		std::cout << mash_p::parse_expression(exprstr) << nl;
		return true;
	}

	static bool print_named(const std::string& exprstr) {
		mash_e::container *where = mash_d::database::instance().lookup(exprstr);
		if (where != nullptr) {
			std::cout << exprstr << "(x) = " << *where << nl;
			return true;
		} else {
			cache_msg(err_name_not_found, nullptr);
			return false;
		}
	}
}

bool assign(const std::string& params, bool noisy) {
	std::stringstream stream(params);
	std::string name;
	stream >> name;

	if (!valid_name(name))
		return false;

	std::string exprstr = params.substr(name.length() + 1);
	strtrim(exprstr);

	mash_e::container func;
	if (exprstr[0] == '(') {
		if (!valid_expr(exprstr))
			return false;
		func = mash_p::parse_expression(exprstr);
		mash_d::database::instance().assign(name, func);
	} else {
		mash_e::container *where = mash_d::database::instance().lookup(exprstr);
		if (where != nullptr) {
			func = *where;
			mash_d::database::instance().assign(name, func);
		} else {
			cache_msg(err_name_not_found, nullptr);
			return false;
		}
	}

	if (noisy) {
		mash_s::color(mash_s::termcolor::teal);
		std::cout << name << "(x) = " << func << nl;
	}
	return true;
}

bool deriv(const std::string& params, bool noisy) {
	mash_e::container func;
	mash_e::container derived;
	bool named;

	if (params[0] == '(') {
		if (!valid_expr(params))
			return false;
		named = false;
		func = mash_p::parse_expression(params);
		derived = func->simplify()->derive()->simplify();
	} else {
		named = true;
		mash_e::container *where = mash_d::database::instance().lookup(params);
		if (where != nullptr) {
			func = *where;
			derived = func->simplify()->derive()->simplify();
		} else {
			cache_msg(err_name_not_found, nullptr);
			return false;
		}
	}

	if (noisy) {
		mash_s::color(mash_s::termcolor::teal);
		if (named) {
			std::cout << params << "'(x) = " << derived << nl;
		} else {
			std::cout << "(" << func << ")' = " << derived << nl;
		}
	}
	return true;
}

bool asderiv(const std::string& params, bool noisy) {
	std::stringstream stream(params);
	std::string name;
	stream >> name;

	if (!valid_name(name))
		return false;

	std::string exprstr = params.substr(name.length() + 1);
	strtrim(exprstr);

	mash_e::container derived;
	bool named;
	if (exprstr[0] == '(') {
		if (!valid_expr(exprstr))
			return false;
		named = false;
		mash_e::container parsed = mash_p::parse_expression(exprstr);
		derived = parsed->simplify()->derive()->simplify();
		mash_d::database::instance().assign(name, derived);
	} else {
		named = true;
		mash_e::container *where = mash_d::database::instance().lookup(exprstr);
		if (where != nullptr) {
			derived = (*where)->simplify()->derive()->simplify();
			mash_d::database::instance().assign(name, derived);
		} else {
			cache_msg(err_name_not_found, nullptr);
			return false;
		}
	}

	if (noisy) {
		mash_s::color(mash_s::termcolor::teal);
		if (named) {
			std::cout << name << "(x) = " << exprstr << "'(x)" << nl;
		} else {
			std::cout << name << "(x) = " << derived << nl;
		}
	}

	return true;
}

bool eval(const std::string& params, bool noisy) {
	std::stringstream stream(params);
	double x;
	std::string exprstr;
	stream >> x;
	std::getline(stream, exprstr);

	strtrim(exprstr);
	if (exprstr == "") {
		cache_msg(err_invalid_expression, nullptr);
		return false;
	}

	mash_e::container func;
	if (exprstr[0] == '(') {
		if (!valid_expr(exprstr))
			return false;
		func = mash_p::parse_expression(exprstr);
	} else {
		mash_e::container *where = mash_d::database::instance().lookup(exprstr);
		if (where != nullptr) {
			func = *where;
		} else {
			cache_msg(err_name_not_found, nullptr);
			return false;
		}
	}

	if (noisy) {
		mash_s::color(mash_s::termcolor::teal);
		std::cout << func->evaluate(x) << nl;
	}
	return true;
}

bool riemann(const std::string& params, bool noisy) {
	std::stringstream stream(params);
	double a, b;
	std::string exprstr;
	stream >> a >> b;
	std::getline(stream, exprstr);

	strtrim(exprstr);
	if (exprstr == "") {
		cache_msg(err_invalid_expression, nullptr);
		return false;
	}

	mash_e::container func;
	if (exprstr[0] == '(') {
		if (!valid_expr(exprstr))
			return false;
		func = mash_p::parse_expression(exprstr);
	} else {
		mash_e::container *where = mash_d::database::instance().lookup(exprstr);
		if (where != nullptr) {
			func = *where;
		} else {
			cache_msg(err_name_not_found, nullptr);
			return false;
		}
	}

	if (noisy) {
		mash_s::color(mash_s::termcolor::teal);
		std::cout << riemann(func, a, b) << nl;
	}
	return true;
}

bool unlink(const std::string& params) {
	if (mash_d::database::instance().lookup(params) == nullptr) {
		cache_msg(err_name_not_found, nullptr);
		return false;
	}

	mash_d::database::instance().unlink(params);
	return true;
}

bool print(std::string params) {
	strtrim(params);

	if (params == "") {
		std::cout << nl;
		return true;
	}

	mash_s::color(mash_s::termcolor::teal);
	switch (params[0]) {
		case '\'':
			return print_string(params);
		case '(':
			return print_expr(params);
		default:
			return print_named(params);
	}
}

bool run(const std::string& params, bool) {
	std::ifstream stream(params);
	if (!stream.good()) {
		cache_msg(err_file_not_found, nullptr);
		return false;
	}

	bool success = true;
	std::string line;

	while (std::getline(stream, line)) {
		strtrim(line);
		if (line == "") {
			continue;
        }
	
		success = interpret(line, false);
		if (!success) {
			std::string errmsg;
			cache_msg(nullptr, &errmsg);
			mash_s::color(mash_s::termcolor::red);
			std::cout << "| " << errmsg << nl;
			return false;
		}
	}

	return true;
}

bool plot(const std::string& params) {
	std::string exprstr = params;
    strtrim(exprstr);

	mash_e::container func;
	if (exprstr[0] == '(') {
		if (!valid_expr(exprstr))
			return false;
		func = mash_p::parse_expression(exprstr);
        return plot_function(func);
	} else {
		mash_e::container *where = mash_d::database::instance().lookup(exprstr);
		if (where != nullptr) {
            return plot_function(*where);
		} else {
			cache_msg(err_name_not_found, nullptr);
			return false;
		}
	}
}

