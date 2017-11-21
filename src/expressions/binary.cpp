#include "expressions/binary.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

mash_e::binary_function::binary_function(exprptr lhs, exprptr rhs) :
	left(lhs),
	right(rhs)
{ }

double mash_e::binary_function::evaluate(double x) const {
	return evaluate(left->evaluate(x), right->evaluate(x));
}

void mash_e::binary_function::print(std::ostream& stream) const {
	stream << '(';
	left->print(stream);
	stream << ' ' << sign() << ' ';
	right->print(stream);
	stream << ')';
}

char mash_e::addition::sign() const {
	return '+';
}

double mash_e::addition::evaluate(double lhs, double rhs) const {
	return lhs + rhs;
}

mash_e::exprptr mash_e::addition::derive() const {
	return std::make_shared<mash_e::addition>(left->derive(), right->derive());
}

mash_e::exprptr mash_e::addition::clone() const {
	return std::make_shared<mash_e::addition>(left, right);
}

mash_e::exprptr mash_e::addition::simplify() const {
	mash_e::exprptr simpleL = left->simplify();
	mash_e::exprptr simpleR = right->simplify();
	mash_e::constant *constL = dynamic_cast<mash_e::constant *>(simpleL.get());
	mash_e::constant *constR = dynamic_cast<mash_e::constant *>(simpleR.get());

	if (constL != nullptr && constL->evaluate(0) == 0)
		return simpleR;

	if (constR != nullptr && constR->evaluate(0) == 0)
		return simpleL;

	if (constL != nullptr && constR != nullptr) {
		const double val = constL->evaluate(0) + constR->evaluate(0);
		return std::make_shared<mash_e::constant>(val);
	}

	return std::make_shared<mash_e::addition>(simpleL, simpleR);
}

char mash_e::subtraction::sign() const {
	return '-';
}

double mash_e::subtraction::evaluate(double lhs, double rhs) const {
	return lhs - rhs;
}

mash_e::exprptr mash_e::subtraction::derive() const {
	return std::make_shared<mash_e::subtraction>(left->derive(), right->derive());
}

mash_e::exprptr mash_e::subtraction::clone() const {
	return std::make_shared<mash_e::subtraction>(left, right);
}

mash_e::exprptr mash_e::subtraction::simplify() const {
	mash_e::exprptr simpleL = left->simplify();
	mash_e::exprptr simpleR = right->simplify();
	mash_e::constant *constL = dynamic_cast<mash_e::constant *>(simpleL.get());
	mash_e::constant *constR = dynamic_cast<mash_e::constant *>(simpleR.get());

	if (constL != nullptr && constL->evaluate(0) == 0)
		return simpleR;

	if (constR != nullptr && constR->evaluate(0) == 0)
		return simpleL;

	if (constL != nullptr && constR != nullptr) {
		const double val = constL->evaluate(0) + constR->evaluate(0);
		return std::make_shared<mash_e::constant>(val);
	}

	return std::make_shared<mash_e::subtraction>(simpleL, simpleR);
}

char mash_e::multiplication::sign() const {
	return '*';
}

double mash_e::multiplication::evaluate(double lhs, double rhs) const {
	return lhs * rhs;
}

mash_e::exprptr mash_e::multiplication::derive() const {
	return std::make_shared<mash_e::addition>(
			std::make_shared<mash_e::multiplication>(left->derive(), right),
			std::make_shared<mash_e::multiplication>(left, right->derive())
		);
}

mash_e::exprptr mash_e::multiplication::clone() const {
	return std::make_shared<mash_e::multiplication>(left, right);
}

mash_e::exprptr mash_e::multiplication::simplify() const {
	mash_e::exprptr simpleL = left->simplify();
	mash_e::exprptr simpleR = right->simplify();
	mash_e::constant *constL = dynamic_cast<mash_e::constant *>(simpleL.get());
	mash_e::constant *constR = dynamic_cast<mash_e::constant *>(simpleR.get());

	if (constL != nullptr) {
		if (constL->evaluate(0) == 0)
			return std::make_shared<mash_e::constant>(0);
		if (constL->evaluate(0) == 1)
			return simpleR;
	}

	if (constR != nullptr) {
		if (constR->evaluate(0) == 0)
			return std::make_shared<mash_e::constant>(0);
		if (constR->evaluate(0) == 1)
			return simpleL;
	}

	if (constL != nullptr && constR != nullptr) {
		const double val = constL->evaluate(0) * constR->evaluate(0);
		return std::make_shared<mash_e::constant>(val);
	}

	return std::make_shared<mash_e::multiplication>(simpleL, simpleR);
}

char mash_e::division::sign() const {
	return '/';
}

double mash_e::division::evaluate(double lhs, double rhs) const {
	return lhs / rhs;
}

mash_e::exprptr mash_e::division::derive() const {
	return std::make_shared<mash_e::division>(
		std::make_shared<mash_e::subtraction>(
			std::make_shared<mash_e::multiplication>(left->derive(), right),
			std::make_shared<mash_e::multiplication>(left, right->derive())
		),
		std::make_shared<mash_e::power>(right, std::make_shared<mash_e::constant>(2))		
	);
}

mash_e::exprptr mash_e::division::clone() const {
	return std::make_shared<division>(left->clone(), right->clone());
}

mash_e::exprptr mash_e::division::simplify() const {
	mash_e::exprptr simpleL = left->simplify();
	mash_e::exprptr simpleR = right->simplify();
	mash_e::constant *constL = dynamic_cast<mash_e::constant *>(simpleL.get());
	mash_e::constant *constR = dynamic_cast<mash_e::constant *>(simpleR.get());

	if (constL != nullptr) {
		if (constL->evaluate(0) == 0)
			return std::make_shared<mash_e::constant>(0);
	}

	if (constR != nullptr) {
		if (constR->evaluate(0) == 0)
			throw std::runtime_error("Division by Zero!");
		if (constR->evaluate(0) == 1)
			return simpleL;
	}

	if (constL != nullptr && constR != nullptr) {
		const double val = constL->evaluate(0) / constR->evaluate(0);
		return std::make_shared<mash_e::constant>(val);
	}

	return std::make_shared<mash_e::division>(simpleL, simpleR);
}

char mash_e::power::sign() const {
	return '^';
}

double mash_e::power::evaluate(double lhs, double rhs) const {
	return pow(lhs, rhs);
}

mash_e::exprptr mash_e::power::derive() const {
	return std::make_shared<mash_e::multiplication>(
		std::make_shared<mash_e::multiplication>(
			right,
			std::make_shared<mash_e::power>(
				left,
				std::make_shared<mash_e::subtraction>(
					right,
					std::make_shared<mash_e::constant>(1)
				)
			)
		),
		left->derive()
	);
}

mash_e::exprptr mash_e::power::clone() const {
	return std::make_shared<power>(left, right);
}

mash_e::exprptr mash_e::power::simplify() const {
	mash_e::exprptr simpleL = left->simplify();
	mash_e::exprptr simpleR = right->simplify();
	mash_e::constant *constL = dynamic_cast<mash_e::constant *>(simpleL.get());
	mash_e::constant *constR = dynamic_cast<mash_e::constant *>(simpleR.get());

	if (constL != nullptr && constL->evaluate(0) == 0)
		return std::make_shared<mash_e::constant>(0);

	if (constR != nullptr) {
		if (constR->evaluate(0) == 0)
			return std::make_shared<mash_e::constant>(1);
		if (constR->evaluate(0) == 1)
			return simpleL;
	}

	if (constL != nullptr && constR != nullptr) {
		const double val = pow(constL->evaluate(0), constR->evaluate(0));
		return std::make_shared<mash_e::constant>(val);
	}

	return std::make_shared<mash_e::power>(simpleL, simpleR);
}
