#pragma once

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define PLATFORM_DLL_IMPORT __declspec(dllimport)
  #define PLATFORM_DLL_EXPORT __declspec(dllexport)
  #define PLATFORM_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define PLATFORM_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define PLATFORM_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define PLATFORM_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define PLATFORM_DLL_IMPORT
    #define PLATFORM_DLL_EXPORT
    #define PLATFORM_DLL_LOCAL
  #endif
#endif
