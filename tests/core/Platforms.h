#ifdef _WIN32
	#ifdef _WIN64
		#define _PLATFORM_WINDOWS_
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#ifdef TARGET_OS_MAC == 1
		#define _PLATFORM_MACOS_
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__linux__)
	#define _PLATFORM_LINUX_
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif