#if !defined(MASH_EXPRESSIONS_CONTAINER)
#define MASH_EXPRESSIONS_CONTAINER
#include "expr_basic.hpp"

namespace mash {
	class container final {
	public:
		container();
		container(exprptr rhs);
		container(const container& rhs);
		container& operator=(const container& rhs);
		~container() noexcept;

		expression * operator->();
		const expression * operator->() const;

		bool is_valid() const;
		double evaluate(double x) const;
		
	private:
		exprptr contents;
	};
}

#endif
