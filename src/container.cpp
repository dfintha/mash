#include "container.hpp"

mash::container::container() : contents(nullptr) { }

mash::container::container(mash::exprptr rhs) : contents(rhs) { }

mash::container::container(const mash::container& rhs) : contents(rhs.contents) { }

mash::container& mash::container::operator=(const mash::container& rhs) {
	contents = rhs.contents;
	return *this;
}

mash::container::~container() noexcept { }

mash::expression * mash::container::operator->() {
	return contents.get();
}

const mash::expression * mash::container::operator->() const {
	return contents.get();
}

bool mash::container::is_valid() const {
	return contents != nullptr;
}

double mash::container::evaluate(double x) const {
	return contents->evaluate(x);
}
