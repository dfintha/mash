#include "expressions/container.hpp"

mash_e::container::container() : contents(nullptr) { }

mash_e::container::container(mash_e::exprptr rhs) : contents(rhs) { }

mash_e::container::container(const mash_e::container& rhs) : contents(rhs.contents) { }

mash_e::container& mash_e::container::operator=(const mash_e::container& rhs) {
	contents = rhs.contents;
	return *this;
}

mash_e::container::~container() noexcept { }

mash_e::expression * mash_e::container::operator->() {
	return contents.get();
}

const mash_e::expression * mash_e::container::operator->() const {
	return contents.get();
}

bool mash_e::container::is_valid() const {
	return contents != nullptr;
}

double mash_e::container::evaluate(double x) const {
	return contents->evaluate(x);
}
