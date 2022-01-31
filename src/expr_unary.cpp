#include "expr_unary.hpp"
#include <cmath>
#include <iostream>

mash::unary_function::unary_function(mash::exprptr content) :
	contents(content)
{ }

void mash::unary_function::print(std::ostream& stream) const {
	stream << name();
	stream << '(';
	contents->print(stream);
	stream << ')';
}

const char * mash::negative::name() const {
	return "-";
}

double mash::negative::evaluate(double x) const {
	return -1 * contents->evaluate(x);
}

mash::exprptr mash::negative::derive() const {
	return std::make_shared<mash::negative>(contents->derive());
}

mash::exprptr mash::negative::clone() const {
	return std::make_shared<mash::negative>(*this);
}

mash::exprptr mash::negative::simplify() const {
	return std::make_shared<mash::negative>(contents->simplify());
}

const char * mash::sine::name() const {
	return "sin";
}

double mash::sine::evaluate(double x) const {
	return std::sin(contents->evaluate(x));
}

mash::exprptr mash::sine::derive() const {
	return std::make_shared<mash::multiplication>(
		std::make_shared<mash::cosine>(contents),
		contents->derive()
	);
}

mash::exprptr mash::sine::clone() const {
	return std::make_shared<mash::sine>(contents);
}

mash::exprptr mash::sine::simplify() const {
	return std::make_shared<mash::sine>(contents->simplify());
}

const char * mash::cosine::name() const {
	return "cos";
}

double mash::cosine::evaluate(double x) const {
	return std::cos(contents->evaluate(x));
}

mash::exprptr mash::cosine::derive() const {
	return std::make_shared<mash::negative>(
		std::make_shared<mash::multiplication>(
			std::make_shared<mash::sine>(contents),
			contents->derive()
		)
	);
}

mash::exprptr mash::cosine::clone() const {
	return std::make_shared<mash::cosine>(contents);
}

mash::exprptr mash::cosine::simplify() const {
	return std::make_shared<mash::cosine>(contents->simplify());
}

const char * mash::tangent::name() const {
	return "tan";
}

double mash::tangent::evaluate(double x) const {
	return std::tan(contents->evaluate(x));
}

mash::exprptr mash::tangent::derive() const {
	return std::make_shared<mash::multiplication>(
		std::make_shared<mash::division>(
			std::make_shared<mash::constant>(1),
			std::make_shared<mash::power>(
				std::make_shared<mash::cosine>(contents),
				std::make_shared<mash::constant>(2)
			)
		),
		contents->derive()
	);
}

mash::exprptr mash::tangent::clone() const {
	return std::make_shared<mash::tangent>(contents);
}

mash::exprptr mash::tangent::simplify() const {
	return std::make_shared<mash::tangent>(contents->simplify());
}

const char * mash::cotangent::name() const {
	return "ctg";
}

double mash::cotangent::evaluate(double x) const {
	return 1 / std::tan(contents->evaluate(x));
}

mash::exprptr mash::cotangent::derive() const {
	return std::make_shared<mash::negative>(
		std::make_shared<mash::multiplication>(
			std::make_shared<mash::division>(
				std::make_shared<mash::constant>(1),
				std::make_shared<mash::power>(
					std::make_shared<mash::sine>(contents),
					std::make_shared<mash::constant>(2)
				)
			),
			contents->derive()
		)
	);
}

mash::exprptr mash::cotangent::clone() const {
	return std::make_shared<mash::cotangent>(contents);
}

mash::exprptr mash::cotangent::simplify() const {
	return std::make_shared<mash::cotangent>(contents->simplify());
}

const char * mash::secant::name() const {
	return "sec";
}

double mash::secant::evaluate(double x) const {
	return 1 / std::cos(contents->evaluate(x));
}

mash::exprptr mash::secant::derive() const {
	return std::make_shared<mash::multiplication>(
		std::make_shared<mash::multiplication>(
			std::make_shared<mash::tangent>(contents),
			std::make_shared<mash::secant>(contents)
		),
		contents->derive()
	);
}

mash::exprptr mash::secant::clone() const {
	return std::make_shared<mash::secant>(contents);
}

mash::exprptr mash::secant::simplify() const {
	return std::make_shared<mash::secant>(contents->simplify());
}

const char * mash::cosecant::name() const {
	return "csc";
}

double mash::cosecant::evaluate(double x) const {
	return 1 / std::sin(contents->evaluate(x));
}

mash::exprptr mash::cosecant::derive() const {
	return std::make_shared<mash::multiplication>(
		std::make_shared<mash::multiplication>(
			std::make_shared<mash::negative>(
				std::make_shared<mash::cotangent>(contents)
			),
			std::make_shared<mash::cosecant>(contents)
		),
		contents->derive()
	);
}

mash::exprptr mash::cosecant::clone() const {
	return std::make_shared<mash::cosecant>(contents);
}

mash::exprptr mash::cosecant::simplify() const {
	return std::make_shared<mash::cosecant>(contents->simplify());
}

const char * mash::logn::name() const {
	return "ln";
}

double mash::logn::evaluate(double x) const {
	return std::log(contents->evaluate(x));
}

mash::exprptr mash::logn::derive() const {
	return std::make_shared<mash::multiplication>(
		std::make_shared<mash::division>(
			std::make_shared<mash::constant>(1),
			contents
		),
		contents->derive()
	);
}

mash::exprptr mash::logn::clone() const {
	return std::make_shared<mash::logn>(contents);
}

mash::exprptr mash::logn::simplify() const {
	return std::make_shared<mash::logn>(contents->simplify());
}

const char * mash::square_root::name() const {
	return "sqrt";
}

double mash::square_root::evaluate(double x) const {
	return std::sqrt(contents->evaluate(x));
}

mash::exprptr mash::square_root::derive() const {
	return std::make_shared<mash::multiplication>(
		std::make_shared<mash::division>(
			std::make_shared<mash::constant>(1),
			std::make_shared<mash::multiplication>(
				std::make_shared<mash::constant>(2),
				std::make_shared<mash::square_root>(contents)
			)
		),
		contents->derive()
	);
}

mash::exprptr mash::square_root::clone() const {
	return std::make_shared<mash::square_root>(contents);
}

mash::exprptr mash::square_root::simplify() const {
	return std::make_shared<mash::square_root>(contents->simplify());
}

const char * mash::cubic_root::name() const {
	return "cbrt";
}

double mash::cubic_root::evaluate(double x) const {
	return std::cbrt(contents->evaluate(x));
}

mash::exprptr mash::cubic_root::derive() const {
	return std::make_shared<mash::multiplication>(
		std::make_shared<mash::division>(
			std::make_shared<mash::constant>(1),
			std::make_shared<mash::multiplication>(
				std::make_shared<mash::constant>(3),
				std::make_shared<mash::power>(
					contents,
					std::make_shared<mash::division>(
						std::make_shared<mash::constant>(2),
						std::make_shared<mash::constant>(3)
					)
				)
			)
		),
		contents->derive()
	);
}

mash::exprptr mash::cubic_root::clone() const {
	return std::make_shared<mash::cubic_root>(contents);
}

mash::exprptr mash::cubic_root::simplify() const {
	return std::make_shared<mash::cubic_root>(contents->simplify());
}
