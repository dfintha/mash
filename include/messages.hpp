#if !defined(MASH_COMMON_MESSAGES)
#define MASH_COMMON_MESSAGES
#include "system.hpp"

static constexpr const char nl = '\n';

static constexpr const char info_version[] =
	"mash " MASH_STATE 
	" [" MASH_OS "-" MASH_ARCH "-" MASH_COMPILER "] " 
	MASH_VERSION 
	" (" MASH_BUILD ")";

static constexpr const char err_invalid_command[] = 
	"The given command could not be interpreted.";

static constexpr const char err_invalid_name_letter[] = 
	"Names must begin with a letter.";

static constexpr const char err_invalid_name_x[] = 
	"The name 'x' is reserved for variables.";

static constexpr const char err_invalid_name_chars[] = 
	"Names can consist of alphanumeric characters, and underscores only.";

static constexpr const char err_invalid_string[] =
	"Invalid character string: no closing apostrophe found.";

static constexpr const char err_name_not_found[] = 
	"The given name was not found.";

static constexpr const char err_invalid_expression[] =
	"The given name or expression is not valid.";

static constexpr const char err_invalid_parens[] =
	"Expressions require an equal amount of opening and closing parentheses.";

static constexpr const char err_invalid_double_parens[] =
	"Double opening parentheses are forbidden.";

static constexpr const char err_file_not_found[] =
	"The specified file could not be found or opened.";

static constexpr const char err_window_open[] =
	"An SDL window could not be opened.";

static constexpr const char msg_intro_help[] =
	"Use the 'help' command for help or the 'exit' command to quit.";

static constexpr const char msg_extended_help[] =
	"The following commands are valid:\n"
	"  assign [name] [expression/name]    stores a function\n"
	"  deriv [name/expression]            derives a function\n"
	"  asderiv [name] [name/expression]   stores the derivative of a function\n"
	"  eval [x] [name/expression]         evaluates a function with given x\n"
	"  riemann [a] [b] [name/expression]  integrates a function from a to b\n"
	"  unlink [name]                      deletes a stored function\n"
	"  print [name/expression/string]     prints a function or a string\n"
	"  run [file]                         runs an external file\n"
	"  plot [expression/name]             displays the plot of a function\n"
	"  help                               shows this help message\n"
	"  builtins                           shows a list of builtin functions\n"
	"  exit, quit                         terminates the program\n"
	"Expressions are given in lisp syntax, without double opening\n"
	"parentheses. Names must contain alphanumeric characters and underscores\n"
	"only and must start with a letter. The same name can be reassigned to\n"
	"a different function.";

static constexpr const char msg_builtins_help[] =
	"Built-in unary functions:\n"
	"  - sin cos tan (tg) ctg sec csc ln sqrt cbrt\n"
	"Built-in binary functions:\n"
	"  + - * / ^\n"
	"Built-in constants:\n"
	"  pi e";

#endif
