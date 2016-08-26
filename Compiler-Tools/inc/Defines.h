#pragma once
#include <stdint.h>

//export definitions
#if defined(WIN32)||defined(_WIN32)||defined(__WIN32__)||defined(_WIN64)||defined(WIN64)||defined(__MINGW32__)||defined(__MINGW64__)
    #define OS_WINDOWS
#elif defined(__linux__) || defined(__unix__)
    #define OS_LINUX
#endif

#ifdef OS_WINDOWS
#ifdef COMPILE_LIB
    #define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif
#endif

#ifdef OS_LINUX
    #define API
#endif


namespace CT{
	//type definitions
	using ubyte = unsigned char;
	using byte = char;

	using s8 = int8_t;
	using s16 = int16_t;
	using s32 = int32_t;
	using s64 = int64_t;

	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	using real32 = float;
	using real64 = double;
}