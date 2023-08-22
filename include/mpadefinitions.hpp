#ifndef __MPDADEFINITIONS_HPP__
#define __MPDADEFINITIONS_HPP__

#ifdef MPAH_STATIC
#define DLLMPAH
#elif MPAH_DLL
#ifdef __linux__
#define DLLMPAH __attribute__((visibility("default")))
#else
#define DLLMPAH __declspec(dllexport)
#endif
#else
#ifdef __linux__
#define DLLMPAH
#else
#define DLLMPAH __declspec(dllimport)
#endif
#endif

#endif
