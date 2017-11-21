#include "db/database.hpp"

mash_d::database& mash_d::database::instance() {
	static mash_d::database i;
	return i;
}

void mash_d::database::assign(const std::string& name, const mash_e::container& func) {
	contents[name] = func;
}

void mash_d::database::unlink(const std::string& name) {
	auto where = contents.find(name);
	if (where != contents.end()) {
		contents.erase(where);
	}
}

mash_e::container * mash_d::database::lookup(const std::string& name) {
	auto where = contents.find(name);
	if (where != contents.end()) {
		return &where->second;
	}
	return nullptr;
}
