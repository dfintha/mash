#if !defined(MASH_BASIC_EXPRESSIONS)
#define MASH_BASIC_EXPRESSIONS
#include <iosfwd>
#include <memory>

namespace mash {
	constexpr const double const_e = 2.718281828;
	constexpr const double const_pi = 3.141592654;

	class expression;
	using exprptr = std::shared_ptr<expression>;

	class constant;
	using constptr = std::shared_ptr<constant>;

	class expression {
	public:
		virtual double evaluate(double x) const = 0;
		virtual void print(std::ostream& stream) const = 0;
		virtual exprptr derive() const = 0;
		virtual exprptr clone() const = 0;
		virtual exprptr simplify() const = 0;
		virtual ~expression() noexcept { }
	};

	class constant final : public expression {
	public:
		constant(double x);
		double evaluate(double x) const override;
		void print(std::ostream& stream) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	private:
		double value;
	};

	class variable final : public expression {
	public:
		double evaluate(double x) const override;
		void print(std::ostream& stream) const override;
		exprptr derive() const override;
		exprptr clone() const override;
		exprptr simplify() const override;
	};
}

#endif
