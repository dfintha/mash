#if !defined(MASH_DB_DATABASE)
#define MASH_DB_DATABASE
#include "expressions/container.hpp"
#include <map>
#include <string>

namespace mash_d {
	class database final {
	public:
		static database& instance();

		void assign(const std::string& name, const mash_e::container& func);
		void unlink(const std::string& name);
		mash_e::container * lookup(const std::string& name);

		database(const database&) = delete;
		database(database&&) = delete;
		database& operator=(const database&) = delete;
		database& operator=(database&&) = delete;
	private:
		database() = default;
		std::map<std::string, mash_e::container> contents;
	};
}

#endif
