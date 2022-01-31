#include "system.hpp"
#if defined(MASH_SYSTEM_POSIX)
#include <iostream>

namespace mash {
	void init() {
		std::cout << "\x1b]2;mash\x07";
		color(termcolor::normal);
	}

	void color(termcolor fg) {
		const char *specific;
		switch (fg) {
			case termcolor::red:
				specific = "\x1B[31m";
				break;
			case termcolor::teal:
				specific = "\x1B[36m";
				break;
			case termcolor::green:
				specific = "\x1B[32m";
				break;
			case termcolor::yellow:
				specific = "\x1B[33m";
				break;
			case termcolor::normal:
			default:
				specific = "\x1B[37m";
				break;
		}
		std::cout << specific;
	}

	void close() {
		std::cout << "\x1B[0m";
	}
}

#endif
