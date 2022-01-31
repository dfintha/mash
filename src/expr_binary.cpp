#include "expr_binary.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

mash::binary_function::binary_function(exprptr lhs, exprptr rhs) :
	left(lhs),
	right(rhs)
{ }

double mash::binary_function::evaluate(double x) const {
	return evaluate(left->evaluate(x), right->evaluate(x));
}

void mash::binary_function::print(std::ostream& stream) const {
	stream << '(';
	left->print(stream);
	stream << ' ' << sign() << ' ';
	right->print(stream);
	stream << ')';
}

char mash::addition::sign() const {
	return '+';
}

double mash::addition::evaluate(double lhs, double rhs) const {
	return lhs + rhs;
}

mash::exprptr mash::addition::derive() const {
	return std::make_shared<mash::addition>(left->derive(), right->derive());
}

mash::exprptr mash::addition::clone() const {
	return std::make_shared<mash::addition>(left, right);
}

mash::exprptr mash::addition::simplify() const {
	mash::exprptr simpleL = left->simplify();
	mash::exprptr simpleR = right->simplify();
	mash::constant *constL = dynamic_cast<mash::constant *>(simpleL.get());
	mash::constant *constR = dynamic_cast<mash::constant *>(simpleR.get());

	if (constL != nullptr && constL->evaluate(0) == 0)
		return simpleR;

	if (constR != nullptr && constR->evaluate(0) == 0)
		return simpleL;

	if (constL != nullptr && constR != nullptr) {
		const double val = constL->evaluate(0) + constR->evaluate(0);
		return std::make_shared<mash::constant>(val);
	}

	return std::make_shared<mash::addition>(simpleL, simpleR);
}

char mash::subtraction::sign() const {
	return '-';
}

double mash::subtraction::evaluate(double lhs, double rhs) const {
	return lhs - rhs;
}

mash::exprptr mash::subtraction::derive() const {
	return std::make_shared<mash::subtraction>(left->derive(), right->derive());
}

mash::exprptr mash::subtraction::clone() const {
	return std::make_shared<mash::subtraction>(left, right);
}

mash::exprptr mash::subtraction::simplify() const {
	mash::exprptr simpleL = left->simplify();
	mash::exprptr simpleR = right->simplify();
	mash::constant *constL = dynamic_cast<mash::constant *>(simpleL.get());
	mash::constant *constR = dynamic_cast<mash::constant *>(simpleR.get());

	if (constL != nullptr && constL->evaluate(0) == 0)
		return simpleR;

	if (constR != nullptr && constR->evaluate(0) == 0)
		return simpleL;

	if (constL != nullptr && constR != nullptr) {
		const double val = constL->evaluate(0) + constR->evaluate(0);
		return std::make_shared<mash::constant>(val);
	}

	return std::make_shared<mash::subtraction>(simpleL, simpleR);
}

char mash::multiplication::sign() const {
	return '*';
}

double mash::multiplication::evaluate(double lhs, double rhs) const {
	return lhs * rhs;
}

mash::exprptr mash::multiplication::derive() const {
	return std::make_shared<mash::addition>(
			std::make_shared<mash::multiplication>(left->derive(), right),
			std::make_shared<mash::multiplication>(left, right->derive())
		);
}

mash::exprptr mash::multiplication::clone() const {
	return std::make_shared<mash::multiplication>(left, right);
}

mash::exprptr mash::multiplication::simplify() const {
	mash::exprptr simpleL = left->simplify();
	mash::exprptr simpleR = right->simplify();
	mash::constant *constL = dynamic_cast<mash::constant *>(simpleL.get());
	mash::constant *constR = dynamic_cast<mash::constant *>(simpleR.get());

	if (constL != nullptr) {
		if (constL->evaluate(0) == 0)
			return std::make_shared<mash::constant>(0);
		if (constL->evaluate(0) == 1)
			return simpleR;
	}

	if (constR != nullptr) {
		if (constR->evaluate(0) == 0)
			return std::make_shared<mash::constant>(0);
		if (constR->evaluate(0) == 1)
			return simpleL;
	}

	if (constL != nullptr && constR != nullptr) {
		const double val = constL->evaluate(0) * constR->evaluate(0);
		return std::make_shared<mash::constant>(val);
	}

	return std::make_shared<mash::multiplication>(simpleL, simpleR);
}

char mash::division::sign() const {
	return '/';
}

double mash::division::evaluate(double lhs, double rhs) const {
	return lhs / rhs;
}

mash::exprptr mash::division::derive() const {
	return std::make_shared<mash::division>(
		std::make_shared<mash::subtraction>(
			std::make_shared<mash::multiplication>(left->derive(), right),
			std::make_shared<mash::multiplication>(left, right->derive())
		),
		std::make_shared<mash::power>(right, std::make_shared<mash::constant>(2))
	);
}

mash::exprptr mash::division::clone() const {
	return std::make_shared<division>(left->clone(), right->clone());
}

mash::exprptr mash::division::simplify() const {
	mash::exprptr simpleL = left->simplify();
	mash::exprptr simpleR = right->simplify();
	mash::constant *constL = dynamic_cast<mash::constant *>(simpleL.get());
	mash::constant *constR = dynamic_cast<mash::constant *>(simpleR.get());

	if (constL != nullptr) {
		if (constL->evaluate(0) == 0)
			return std::make_shared<mash::constant>(0);
	}

	if (constR != nullptr) {
		if (constR->evaluate(0) == 0)
			throw std::runtime_error("division by zero");
		if (constR->evaluate(0) == 1)
			return simpleL;
	}

	if (constL != nullptr && constR != nullptr) {
		const double val = constL->evaluate(0) / constR->evaluate(0);
		return std::make_shared<mash::constant>(val);
	}

	return std::make_shared<mash::division>(simpleL, simpleR);
}

char mash::power::sign() const {
	return '^';
}

double mash::power::evaluate(double lhs, double rhs) const {
	return pow(lhs, rhs);
}

mash::exprptr mash::power::derive() const {
	return std::make_shared<mash::multiplication>(
		std::make_shared<mash::multiplication>(
			right,
			std::make_shared<mash::power>(
				left,
				std::make_shared<mash::subtraction>(
					right,
					std::make_shared<mash::constant>(1)
				)
			)
		),
		left->derive()
	);
}

mash::exprptr mash::power::clone() const {
	return std::make_shared<power>(left, right);
}

mash::exprptr mash::power::simplify() const {
	mash::exprptr simpleL = left->simplify();
	mash::exprptr simpleR = right->simplify();
	mash::constant *constL = dynamic_cast<mash::constant *>(simpleL.get());
	mash::constant *constR = dynamic_cast<mash::constant *>(simpleR.get());

	if (constL != nullptr && constL->evaluate(0) == 0)
		return std::make_shared<mash::constant>(0);

	if (constR != nullptr) {
		if (constR->evaluate(0) == 0)
			return std::make_shared<mash::constant>(1);
		if (constR->evaluate(0) == 1)
			return simpleL;
	}

	if (constL != nullptr && constR != nullptr) {
		const double val = pow(constL->evaluate(0), constR->evaluate(0));
		return std::make_shared<mash::constant>(val);
	}

	return std::make_shared<mash::power>(simpleL, simpleR);
}
