#if !defined(MASH_PARSER_TOKENS)
#define MASH_PARSER_TOKENS
#include <iosfwd>
#include <string>
#include <vector>

namespace mash {
	class token {
	public:
		const std::string& name() const;
		const token& arg(unsigned i) const;
		size_t argcount() const;
		void read(std::istream& stream);

	private:
		std::string id;
		std::vector<token> arguments;
	};
}

#endif
