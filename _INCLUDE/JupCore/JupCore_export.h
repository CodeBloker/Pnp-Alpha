#pragma once
#ifndef _JUPCORE_EXPORT_
#define _JUPCORE_EXPORT_

#ifndef BUILD_STATIC
# if defined(JUPCORE_LIB)
#  define JUPCORE_EXPORT __declspec(dllexport)
# else
#  define JUPCORE_EXPORT __declspec(dllimport)
# endif
#else
# define JUPCORE_EXPORT
#endif

#pragma warning (disable: 4251)

#endif /*_JUPCORE_EXPORT_*/