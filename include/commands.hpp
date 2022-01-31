#if !defined(MASH_COMMON_COMMANDS)
#define MASH_COMMON_COMMANDS
#include "messages.hpp"
#include <iostream>
#include <string>

bool interpret(std::string command, bool noisy);
void cache_msg(const char *store, std::string *load);

bool assign(const std::string& params, bool noisy);
bool derive(const std::string& params, bool noisy);
bool assign_derived(const std::string& params, bool noisy);
bool evaluate(const std::string& params, bool noisy);
bool riemann(const std::string& params, bool noisy);
bool unlink(const std::string& params);
bool print(std::string params);
bool run(const std::string& params, bool noisy);
bool plot(const std::string& params);

inline bool help() {
	mash::color(mash::termcolor::yellow);
	std::cout << msg_extended_help << nl;
	return true;
}

inline bool builtins() {
	mash::color(mash::termcolor::yellow);
	std::cout << msg_builtins_help << nl;
	return true;
}

#endif
