#if !defined(MASH_DB_DATABASE)
#define MASH_DB_DATABASE
#include "container.hpp"
#include <map>
#include <string>

namespace mash {
	class database final {
	public:
		static database& instance();

		void assign(const std::string& name, const mash::container& func);
		void unlink(const std::string& name);
		mash::container * lookup(const std::string& name);

		database(const database&) = delete;
		database(database&&) = delete;
		database& operator=(const database&) = delete;
		database& operator=(database&&) = delete;
	private:
		database() = default;
		std::map<std::string, mash::container> contents;
	};
}

#endif
