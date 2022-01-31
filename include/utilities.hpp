#if !defined(MASH_COMMON_UTILITIES)
#define MASH_COMMON_UTILITIES
#include "container.hpp"
#include "expr_basic.hpp"
#include <cfloat>
#include <cmath>
#include <iostream>

inline std::ostream& operator<<(std::ostream& stream, const mash::container& expr) {
	expr->print(stream);
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const mash::expression& expr) {
	expr.print(stream);
	return stream;
}

inline bool near(double a, double b) {
	return std::abs(a - b) < DBL_EPSILON;
}

inline double riemann(const mash::container& f, double a, double b, double dx = 0.0001) {
	if (!f.is_valid() || near(a, b)) return 0.0;
	if (a > b) std::swap(a, b);
	mash::container fn = f->simplify();

	double sum = 0.0;
	for (double x = a; x <= b; x += dx) {
		sum += fn.evaluate(x) * dx;
	}
	return sum;
}

inline void strtrim(std::string& str) {
	static constexpr const char whitespaces[] = " \t\n";
    if (str == "")
        return;

    const auto beg = str.find_first_not_of(whitespaces);
    const auto end = str.find_last_not_of(whitespaces);
    str = str.substr(beg, end - beg + 1);
}

inline void cmtstrip(std::string& str) {
	static constexpr const char comment[] = "::";
	const auto pos = str.find(comment);
	if (pos != std::string::npos)
		str = str.substr(0, pos);
}

#endif
