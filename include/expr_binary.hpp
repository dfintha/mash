#if !defined(MASH_BINARY_EXPRESSIONS)
#define MASH_BINARY_EXPRESSIONS
#include "expr_basic.hpp"

namespace mash {
	class binary_function : public expression {
	public:
		binary_function(exprptr lhs, exprptr rhs);
		double evaluate(double x) const override;
		void print(std::ostream& stream) const override;

	protected:
		virtual char sign() const = 0;
		virtual double evaluate(double lhs, double rhs) const = 0;
		exprptr left, right;
	};

	class addition final : public binary_function {
	public:
		using binary_function::binary_function;
		char sign() const override;
		double evaluate(double lhs, double rhs) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class subtraction final : public binary_function {
	public:
		using binary_function::binary_function;
		char sign() const override;
		double evaluate(double lhs, double rhs) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class multiplication final : public binary_function {
	public:
		using binary_function::binary_function;
		char sign() const override;
		double evaluate(double lhs, double rhs) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class division final : public binary_function {
	public:
		using binary_function::binary_function;
		char sign() const override;
		double evaluate(double lhs, double rhs) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

	class power final : public binary_function {
	public:
		using binary_function::binary_function;
		char sign() const override;
		double evaluate(double lhs, double rhs) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};

}

#endif
