#pragma once
#ifndef ROCKET_API_INCLUDED
#define ROCKET_API_INCLUDED

#if defined(_WIN32)
	#if defined(ROCKET_LIB_EXPORT)
		#define ROCKET_API __declspec(dllexport)
	#else
		#define ROCKET_API __declspec(dllimport)
	#endif
#else
	#define ROCKET_API
#endif

#endif