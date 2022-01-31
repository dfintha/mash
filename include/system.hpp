#if !defined(MASH_SYSTEM_GENERAL)
#define MASH_SYSTEM_GENERAL

#define MASH_MAJOR 0
#define MASH_MINOR 1
#define MASH_VERSION "v0.1"
#define MASH_STATE "alpha"
#define MASH_BUILD "2022-01-31"

#if defined(_WIN64) || defined (__x86_64__)
#define MASH_ARCH "64"
#else
#define MASH_ARCH "32"
#endif

#if defined(__clang__)
#define MASH_COMPILER "clang"
#elif defined(__GNUC__)
#define MASH_COMPILER "gcc"
#elif defined(_MSC_VER)
#define MASH_COMPILER "msvc"
#else
#define MASH_COMPILER "unknown"
#endif

#if defined(_WIN32) || defined(_WIN64)
#define MASH_SYSTEM_WINDOWS
#define MASH_OS "windows"
#elif defined(__unix__) || defined(__unix) || defined(unix) || defined(__POSIX_VERSION)
#define MASH_SYSTEM_POSIX
#define MASH_OS "posix"
#else
#define MASH_SYSTEM_UNKNOWN
#define MASH_OS "unknown"
#endif

namespace mash {
	enum termcolor {
		normal, red, teal, green, yellow
	};

	void init();
	void color(termcolor fg);
	void close();
}

#endif
