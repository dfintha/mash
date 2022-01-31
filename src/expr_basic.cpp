#include "expr_basic.hpp"
#include <iostream>

mash::constant::constant(double x) : value(x) { }

double mash::constant::evaluate(double) const {
	return value;
}

void mash::constant::print(std::ostream& stream) const {
	stream << value;
}

mash::exprptr mash::constant::derive() const {
	return std::make_shared<mash::constant>(0);
}

mash::exprptr mash::constant::clone() const {
	return std::make_shared<mash::constant>(*this);
}

mash::exprptr mash::constant::simplify() const {
	return clone();
}

double mash::variable::evaluate(double x) const {
	return x;
}

void mash::variable::print(std::ostream& stream) const {
	stream << 'x';
}

mash::exprptr mash::variable::derive() const {
	return std::make_shared<mash::constant>(1);
}

mash::exprptr mash::variable::clone() const {
	return std::make_shared<mash::variable>(*this);
}

mash::exprptr mash::variable::simplify() const {
	return clone();
}
