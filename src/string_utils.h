#pragma once

#include "engine_t.h"

namespace EngineT
{
    class StringUtils
    {
    public:
        static vector<int> ToIntArray(string str);

        static vector<string> ToStringArray(string str);

        static string GetStringAfter(string str, char separator);

        static int GetIntAfter(string str, char separator);

        static string Trim(string str);

        static inline bool OnlySpaces(string str);
    };
}