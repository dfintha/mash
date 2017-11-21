#include "expressions/basic.hpp"
#include <iostream>

mash_e::constant::constant(double x) : value(x) { }

double mash_e::constant::evaluate(double) const {
	return value;
}

void mash_e::constant::print(std::ostream& stream) const {
	stream << value;
}

mash_e::exprptr mash_e::constant::derive() const {
	return std::make_shared<mash_e::constant>(0);
}

mash_e::exprptr mash_e::constant::clone() const {
	return std::make_shared<mash_e::constant>(*this);
}

mash_e::exprptr mash_e::constant::simplify() const {
	return clone();
}

double mash_e::variable::evaluate(double x) const {
	return x;
}

void mash_e::variable::print(std::ostream& stream) const {
	stream << 'x';
}

mash_e::exprptr mash_e::variable::derive() const {
	return std::make_shared<mash_e::constant>(1);
}

mash_e::exprptr mash_e::variable::clone() const {
	return std::make_shared<mash_e::variable>(*this);
}

mash_e::exprptr mash_e::variable::simplify() const {
	return clone();
}
