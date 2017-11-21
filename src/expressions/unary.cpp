#include "expressions/unary.hpp"
#include <cmath>
#include <iostream>

mash_e::unary_function::unary_function(mash_e::exprptr content) : 
	contents(content)
{ }

void mash_e::unary_function::print(std::ostream& stream) const {
	stream << name();
	stream << '(';
	contents->print(stream);
	stream << ')';
}

const char * mash_e::negative::name() const {
	return "-";
}

double mash_e::negative::evaluate(double x) const { 
	return -1 * contents->evaluate(x);
}

mash_e::exprptr mash_e::negative::derive() const {
	return std::make_shared<mash_e::negative>(contents->derive());
}

mash_e::exprptr mash_e::negative::clone() const {
	return std::make_shared<mash_e::negative>(*this);
}

mash_e::exprptr mash_e::negative::simplify() const {
	return std::make_shared<mash_e::negative>(contents->simplify());
}

const char * mash_e::sine::name() const {
	return "sin";
}

double mash_e::sine::evaluate(double x) const {
	return std::sin(contents->evaluate(x));
}

mash_e::exprptr mash_e::sine::derive() const {
	return std::make_shared<mash_e::multiplication>(
		std::make_shared<mash_e::cosine>(contents),
		contents->derive()
	);
}

mash_e::exprptr mash_e::sine::clone() const {
	return std::make_shared<mash_e::sine>(contents);
}

mash_e::exprptr mash_e::sine::simplify() const {
	return std::make_shared<mash_e::sine>(contents->simplify());
}

const char * mash_e::cosine::name() const {
	return "cos";
}

double mash_e::cosine::evaluate(double x) const {
	return std::cos(contents->evaluate(x));
}

mash_e::exprptr mash_e::cosine::derive() const {
	return std::make_shared<mash_e::negative>(
		std::make_shared<mash_e::multiplication>(
			std::make_shared<mash_e::sine>(contents),
			contents->derive()
		)
	);
}

mash_e::exprptr mash_e::cosine::clone() const {
	return std::make_shared<mash_e::cosine>(contents);
}

mash_e::exprptr mash_e::cosine::simplify() const {
	return std::make_shared<mash_e::cosine>(contents->simplify());
}

const char * mash_e::tangent::name() const {
	return "tan";
}

double mash_e::tangent::evaluate(double x) const {
	return std::tan(contents->evaluate(x));
}

mash_e::exprptr mash_e::tangent::derive() const {
	return std::make_shared<mash_e::multiplication>(
		std::make_shared<mash_e::division>(
			std::make_shared<mash_e::constant>(1),
			std::make_shared<mash_e::power>(
				std::make_shared<mash_e::cosine>(contents),
				std::make_shared<mash_e::constant>(2)
			)
		),
		contents->derive()
	);
}

mash_e::exprptr mash_e::tangent::clone() const {
	return std::make_shared<mash_e::tangent>(contents);
}

mash_e::exprptr mash_e::tangent::simplify() const {
	return std::make_shared<mash_e::tangent>(contents->simplify());
}

const char * mash_e::cotangent::name() const {
	return "ctg";
}

double mash_e::cotangent::evaluate(double x) const {
	return 1 / std::tan(contents->evaluate(x));
}

mash_e::exprptr mash_e::cotangent::derive() const {
	return std::make_shared<mash_e::negative>(
		std::make_shared<mash_e::multiplication>(
			std::make_shared<mash_e::division>(
				std::make_shared<mash_e::constant>(1),
				std::make_shared<mash_e::power>(
					std::make_shared<mash_e::sine>(contents),
					std::make_shared<mash_e::constant>(2)
				)
			),
			contents->derive()
		)
	);
}

mash_e::exprptr mash_e::cotangent::clone() const {
	return std::make_shared<mash_e::cotangent>(contents);
}

mash_e::exprptr mash_e::cotangent::simplify() const {
	return std::make_shared<mash_e::cotangent>(contents->simplify());
}

const char * mash_e::secant::name() const {
	return "sec";
}

double mash_e::secant::evaluate(double x) const {
	return 1 / std::cos(contents->evaluate(x));
}

mash_e::exprptr mash_e::secant::derive() const {
	return std::make_shared<mash_e::multiplication>(
		std::make_shared<mash_e::multiplication>(
			std::make_shared<mash_e::tangent>(contents),
			std::make_shared<mash_e::secant>(contents)
		),
		contents->derive()
	);
}

mash_e::exprptr mash_e::secant::clone() const {
	return std::make_shared<mash_e::secant>(contents);
}

mash_e::exprptr mash_e::secant::simplify() const {
	return std::make_shared<mash_e::secant>(contents->simplify());
}

const char * mash_e::cosecant::name() const {
	return "csc";
}

double mash_e::cosecant::evaluate(double x) const {
	return 1 / std::sin(contents->evaluate(x));
}

mash_e::exprptr mash_e::cosecant::derive() const {
	return std::make_shared<mash_e::multiplication>(
		std::make_shared<mash_e::multiplication>(
			std::make_shared<mash_e::negative>(
				std::make_shared<mash_e::cotangent>(contents)
			),
			std::make_shared<mash_e::cosecant>(contents)
		),
		contents->derive()
	);
}

mash_e::exprptr mash_e::cosecant::clone() const {
	return std::make_shared<mash_e::cosecant>(contents);
}

mash_e::exprptr mash_e::cosecant::simplify() const {
	return std::make_shared<mash_e::cosecant>(contents->simplify());
}

const char * mash_e::logn::name() const {
	return "ln";
}

double mash_e::logn::evaluate(double x) const {
	return std::log(contents->evaluate(x));
}

mash_e::exprptr mash_e::logn::derive() const {
	return std::make_shared<mash_e::multiplication>(
		std::make_shared<mash_e::division>(
			std::make_shared<mash_e::constant>(1),
			contents
		),
		contents->derive()
	);
}

mash_e::exprptr mash_e::logn::clone() const {
	return std::make_shared<mash_e::logn>(contents);
}

mash_e::exprptr mash_e::logn::simplify() const {
	return std::make_shared<mash_e::logn>(contents->simplify());
}

const char * mash_e::square_root::name() const {
	return "sqrt";
}

double mash_e::square_root::evaluate(double x) const {
	return std::sqrt(contents->evaluate(x));
}

mash_e::exprptr mash_e::square_root::derive() const {
	return std::make_shared<mash_e::multiplication>(
		std::make_shared<mash_e::division>(
			std::make_shared<mash_e::constant>(1),
			std::make_shared<mash_e::multiplication>(
				std::make_shared<mash_e::constant>(2),
				std::make_shared<mash_e::square_root>(contents)
			)
		),
		contents->derive()
	);
}

mash_e::exprptr mash_e::square_root::clone() const {
	return std::make_shared<mash_e::square_root>(contents);
}

mash_e::exprptr mash_e::square_root::simplify() const {
	return std::make_shared<mash_e::square_root>(contents->simplify());
}

const char * mash_e::cubic_root::name() const {
	return "cbrt";
}

double mash_e::cubic_root::evaluate(double x) const {
	return std::cbrt(contents->evaluate(x));
}

mash_e::exprptr mash_e::cubic_root::derive() const {
	return std::make_shared<mash_e::multiplication>(
		std::make_shared<mash_e::division>(
			std::make_shared<mash_e::constant>(1),
			std::make_shared<mash_e::multiplication>(
				std::make_shared<mash_e::constant>(3),
				std::make_shared<mash_e::power>(
					contents,
					std::make_shared<mash_e::division>(
						std::make_shared<mash_e::constant>(2),
						std::make_shared<mash_e::constant>(3)
					)
				)
			)
		),
		contents->derive()
	);
}

mash_e::exprptr mash_e::cubic_root::clone() const {
	return std::make_shared<mash_e::cubic_root>(contents);
}

mash_e::exprptr mash_e::cubic_root::simplify() const {
	return std::make_shared<mash_e::cubic_root>(contents->simplify());
}
