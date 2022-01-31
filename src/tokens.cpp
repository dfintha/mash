#include <cassert>
#include <cctype>
#include <climits>
#include <iostream>
#include "tokens.hpp"
#include "utilities.hpp"

namespace {
	static void skipws(std::istream& stream) {
		char c;
		while (isspace(stream.peek())) {
			stream >> std::noskipws >> c;
		}
	}

	static bool not_separator(int c) {
		return c != ')' && !isspace(c);
	}
}

const std::string& mash::token::name() const {
	return id;
}

const mash::token& mash::token::arg(unsigned i) const {
	return arguments.at(i);
}

size_t mash::token::argcount() const {
	return arguments.size();
}

void mash::token::read(std::istream& stream) {
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
		int next = stream.peek();
		if (next < CHAR_MIN || next > CHAR_MAX)
			throw std::runtime_error("invalid character received");
		chrbuf = char(next);

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
