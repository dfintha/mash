#include "system.hpp"
#if defined(MASH_SYSTEM_WINDOWS)
#include <Windows.h>

namespace mash {
	static WORD stored = 0x0;

	void init() {
		SetConsoleTitle("mash");
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		stored = info.wAttributes;
		color(termcolor::normal);
	}

	void color(termcolor fg) {
		int specific;
		switch (fg) {
			case termcolor::red:
				specific = FOREGROUND_RED | FOREGROUND_INTENSITY;
				break;
			case termcolor::teal:
				specific = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				break;
			case termcolor::green:
				specific = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
				break;
			case termcolor::yellow:
				specific = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
				break;
			case termcolor::normal:
				[[fallthrough]];
			default:
				specific = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), specific);
	}

	void close() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), stored);
	}
}

#endif
