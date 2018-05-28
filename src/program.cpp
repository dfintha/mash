#include "parser/parser.hpp"
#include "utilities.hpp"
#include "messages.hpp"
#include "commands.hpp"

bool prompt(std::string& input, bool success);
bool interpret(std::string command, bool noisy);
void cache_msg(const char *store, std::string *load);

int main() {
    mash_s::init();
    std::cout << info_version << nl;
    std::cout << msg_intro_help << nl << nl;

    bool success = true;
    std::string command;
    while (prompt(command, success)) {
        success = interpret(command, true);
        if (!success) {
            std::string errmsg;
            cache_msg(nullptr, &errmsg);
            mash_s::color(mash_s::termcolor::red);
            std::cout << "! " << errmsg << nl;
        }
    }

    mash_s::color(mash_s::termcolor::teal);
    std::cout << nl << "Goodbye!" << nl;
    mash_s::close();
    return 0;
}

bool prompt(std::string& input, bool success) {
    mash_s::color(success ? mash_s::termcolor::green : mash_s::termcolor::red);
    std::cout << "% ";
    mash_s::color(mash_s::termcolor::normal);
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

    if (name == "deriv")
        return deriv(rest, noisy);

    if (name == "asderiv")
        return asderiv(rest, noisy);

    if (name == "eval")
        return eval(rest, noisy);

    if (name == "riemann")
        return riemann(rest, noisy);

    if (name == "unlink")
        return unlink(rest);

    if (name == "print")
        return print(rest);

    if (name == "run")
        return run(rest, noisy);

    if (name == "plot")
        return plot(rest);

    if (name == "help")
        return help();

    if (name == "builtins")
        return builtins();

    if (name == "exit" || name == "quit") {
        mash_s::color(mash_s::termcolor::teal);
        std::cout << "Goodbye!" << nl;
        mash_s::close();
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
