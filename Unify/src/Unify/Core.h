#pragma once

#ifdef UN_PLATFORM_WINDOWS
#ifdef UN_BUILD_DLL
#define UNIFY_API __declspec(dllexport)
#else 
#define UNIFY_API __declspec(dllimport)
#endif // UN_BUILD_DLL
#else
#error Unify currently only supports Windows!
#endif