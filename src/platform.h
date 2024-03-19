#ifndef PLATFORM_H_
#define PLATFORM_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PLATFORM_WIN32 1
#elif defined(__linux__) || defined(__gnu_linux__)
#define PLATFORM_LINUX 1
#else
#error "UNKNOWN PLATFORM! NoLog supports only on Windows and Linux."
#endif

#endif // PLATFORM_H_
