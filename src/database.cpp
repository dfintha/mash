#include "database.hpp"

mash::database& mash::database::instance() {
	static mash::database i;
	return i;
}

void mash::database::assign(const std::string& name, const mash::container& func) {
	contents[name] = func;
}

void mash::database::unlink(const std::string& name) {
	auto where = contents.find(name);
	if (where != contents.end()) {
		contents.erase(where);
	}
}

mash::container * mash::database::lookup(const std::string& name) {
	auto where = contents.find(name);
	if (where != contents.end()) {
		return &where->second;
	}
	return nullptr;
}
