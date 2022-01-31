#include "parser.hpp"
#include "utilities.hpp"
#include "messages.hpp"
#include "commands.hpp"

bool prompt(std::string& input, bool success);
bool interpret(std::string command, bool noisy);
void cache_msg(const char *store, std::string *load);

int main() {
    mash::init();
    std::cout << info_version << nl;
    std::cout << msg_intro_help << nl << nl;

    bool success = true;
    std::string command;
    while (prompt(command, success)) {
        success = interpret(command, true);
        if (!success) {
            std::string errmsg;
            cache_msg(nullptr, &errmsg);
            mash::color(mash::termcolor::red);
            std::cout << "! " << errmsg << nl;
        }
    }

    mash::color(mash::termcolor::teal);
    std::cout << nl << "Goodbye!" << nl;
    mash::close();
    return 0;
}

bool prompt(std::string& input, bool success) {
    mash::color(success ? mash::termcolor::green : mash::termcolor::red);
    std::cout << "% ";
    mash::color(mash::termcolor::normal);
    return bool(std::getline(std::cin, input));
}

bool interpret(std::string command, bool noisy) {
    cmtstrip(command);
    strtrim(command);
    
    if (command == "")
        return true;

    std::string name = command.substr(0, command.find(" "));
    std::string rest = command.substr(name.length());

    strtrim(rest);

    if (name == "assign")
        return assign(rest, noisy);

    if (name == "derive")
        return derive(rest, noisy);

    if (name == "assign_derived")
        return assign_derived(rest, noisy);

    if (name == "evaluate")
        return evaluate(rest, noisy);

    if (name == "riemann")
        return riemann(rest, noisy);

    if (name == "unlink")
        return unlink(rest);

    if (name == "print")
        return print(rest);

    if (name == "run")
        return run(rest, noisy);
#if defined(MASH_PLOT_FEATURE)
    if (name == "plot")
        return plot(rest);
#endif

    if (name == "help")
        return help();

    if (name == "builtins")
        return builtins();

    if (name == "exit" || name == "quit") {
        mash::color(mash::termcolor::teal);
        std::cout << "Goodbye!" << nl;
        mash::close();
        std::exit(0);
    }

    cache_msg(err_invalid_command, nullptr);
    return false;
}

void cache_msg(const char *store, std::string *load) {
    static std::string contents;

    if (store != nullptr) {
        contents = store;
        return;
    }

    if (load != nullptr) {
        *load = contents;
        return;
    }
}
