# mash

## Short Description

Mash is a basic command-line expression evaluator, which can derive simple
mathematical expressions, evaluate them, and perform definite integrals. 
Function definitions are in Lisp syntax.

Please note, that the basic structure of the expression tree is heavily based on
an example given during a "C11 and C++11 Programming" course at the Budapest
University of Technology and Economics.

## Usage

### Expression Format

In mash, expressions are described in a Lisp-like prefix syntax. So, the
expression `ln(sin(x) * x)` will look like `(ln (* (sin x) x))`.
Every expression shall begin and end with parentheses, even a simple `x`.
Double opening parentheses are not allowed, as this prefix syntax can not be 
ambigous without them.

### Commands

After issuing the __mash__ command we get a shell.
Line comments are denoted by double colons (`::`).
The following commands apply there:

#### assign
```assign [name] [expression/name]```

Assigns the given name to the given expression, as if saying _name_ = 
_expression/name_ in functional programming languages. Assignments can be 
overwritten with consecutive assign commands with the same name. The names of 
assignments must comply to the following constraints:

* They contain letters, numbers, and underscore characters only.
* They start with a letter.
* "x" is reserved for variables in functions.

#### derive
```derive [name/expression]```

Calculates the derivative of the given function.

#### assign_derived
```assign_derived [target name] [name/expression]```

Calculates the derivative of its second argument, and assigns the result to 
the given name. Essentially a combination of the __assign__ and __derive__
functions.

#### evaluate
```evaluate [n] [name/expression]```

Evaluates the given function, when _x = n_.

#### riemann
```riemann [a] [b] [name/expression]```

Integrates by summing small areas under the function curve between _a_ and _b_.

#### unlink
```unlink [name]```

Deletes the assignment of the given name.

#### print
```print [name/expression/string]```

Prints the representation of a given function, or a given string. Strings are
indicated by beginning and ending with an apostrophe. If no parameters are
given, `print` will output an empty line.

#### run
```run [file]```

Interprets the contents of a given file line-by-line, as if the lines were
entered during the session.

#### plot
```plot [name/expression]```

Shows a plot of the given function in an SDL window.

#### help
```help```

Prints an extended help about the functionality of the shell. The contents of
the help are similar to the descriptions of the commands in this document.

#### builtins
```builtins```

Displays a list of builtin functions.

#### exit, quit
```exit```
```quit```

Closes the mash session. The same functionality can be achieved by sending an
EOF to the standard input (^D).
