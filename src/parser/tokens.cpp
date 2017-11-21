#include <cassert>
#include <cctype>
#include <iostream>
#include "parser/tokens.hpp"
#include "utilities.hpp"

namespace {
	static void skipws(std::istream& stream) {
		char c;
		while (isspace(stream.peek())) {
			stream >> std::noskipws >> c;
		}
	}

	static bool not_separator(char c) {
		return c != ')' && !isspace(c);
	}
}

const std::string& mash_p::token::name() const {
	return id;
}

const mash_p::token& mash_p::token::arg(unsigned i) const {
	return arguments.at(i);
}

size_t mash_p::token::argcount() const {
	return arguments.size();
}

void mash_p::token::read(std::istream& stream) {
	skipws(stream);
	char chrbuf;
	stream >> chrbuf;
	assert(chrbuf == '(');

	while (not_separator(stream.peek())) {
		stream >> chrbuf;
		id += chrbuf;
	}

	bool processing = true;
	do {
		skipws(stream);
		chrbuf = stream.peek();

		if (chrbuf == '(') {
			token temp;
			temp.read(stream);
			arguments.push_back(temp);
			continue;
		}

		if (chrbuf == ')') {
			stream >> chrbuf;
			processing = false;
			continue;
		}
	
		token temp;
		while (not_separator(stream.peek())) {
			stream >> chrbuf;
			temp.id += chrbuf;
		}
		strtrim(temp.id);
		arguments.push_back(temp);
	} while (processing);
}
