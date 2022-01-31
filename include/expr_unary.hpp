#if !defined(MASH_UNARY_EXPRESSIONS)
#define MASH_UNARY_EXPRESSIONS
#include "expr_basic.hpp"
#include "expr_binary.hpp"

namespace mash {
	class unary_function : public expression {
	public:
		unary_function(exprptr content);
		void print(std::ostream& stream) const override;

	protected:
		virtual const char * name() const = 0;
		exprptr contents;
	};

	class negative : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class sine : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class cosine : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class tangent : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class cotangent : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class secant : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class cosecant : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class logn : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class square_root final : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class cubic_root final : public unary_function {
	public:
		using unary_function::unary_function;
		const char * name() const override;
		double evaluate(double x) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};
}

#endif
