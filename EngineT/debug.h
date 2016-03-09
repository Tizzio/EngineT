
#pragma once
 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stdarg.h"
#include <ctime>


#ifdef NDEBUG
#define Check(_Expression)     ((void)0)
#else
#ifdef WIN32
#define __CURFILE__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __CURFILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define Check(_Expression, error) (void)( (!!(_Expression)) || (Engine.TrowError(error, __LINE__, __CURFILE__)) )
#endif


namespace EngineT{

	class Debug
	{
	public:
		void LogS(int n){
			std::ofstream log("log.txt", std::ios_base::app | std::ios_base::out);
			log << n << '\n';
		}
		void LogS(const char* szString)
		{
			std::ofstream log("log.txt", std::ios_base::app | std::ios_base::out);
			log << szString << '\n';
		}

		void LogM(const char* szString, ...)
		{
			va_list args;
			va_start(args, szString);
			for (const char* arg = szString; arg != NULL; arg = va_arg(args, const char*)) {
				std::ofstream log("log.txt", std::ios_base::app | std::ios_base::out);
				log << arg << '\n';
			}

			va_end(args);

		}

		void LogDate(){
			time_t rawtime;
			time(&rawtime);
			char out[100];
			ctime_s(out, 100, &rawtime);
			LogM("--------------------------------------", out, "--------------------------------------", NULL);
		}

		 
	};


}