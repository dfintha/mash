#if !defined(MASH_COMMON_COMMANDS)
#define MASH_COMMON_COMMANDS
#include "messages.hpp"
#include <iostream>
#include <string>

bool interpret(std::string command, bool noisy);
void cache_msg(const char *store, std::string *load);

bool assign(const std::string& params, bool noisy);
bool deriv(const std::string& params, bool noisy);
bool asderiv(const std::string& params, bool noisy);
bool eval(const std::string& params, bool noisy);
bool riemann(const std::string& params, bool noisy);
bool unlink(const std::string& params);
bool print(std::string params);
bool run(const std::string& params, bool noisy);

inline bool help() {
	mash_s::color(mash_s::termcolor::yellow);
	std::cout << msg_extended_help << nl;
	return true;
}

inline bool builtins() {
	mash_s::color(mash_s::termcolor::yellow);
	std::cout << msg_builtins_help << nl;
	return true;
}

#endif
