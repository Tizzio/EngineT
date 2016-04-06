#include "string_utils.h"

namespace EngineT
{
    vector<int> StringUtils::ToIntArray(string str)
    {
        vector<int> data;
        string buf;
        stringstream stream(str);
        while(stream >> buf)
            data.push_back(stoi(buf));
        return data;
    }

    vector<string> StringUtils::ToStringArray(string str)
    {
        vector<string> data;
        string buf;
        stringstream stream(str);
        while(stream >> buf)
            data.push_back(buf);
        return data;
    }

    string StringUtils::GetStringAfter(string str, char separator)
    {
        int skip = str.find_first_of(separator) + 1;
        return str.substr(skip, str.length() - skip);
    }

    int StringUtils::GetIntAfter(string str, char separator)
    {
        int skip = str.find_first_of(separator) + 1;
        return stoi(str.substr(skip, str.length() - skip));
    }

    string StringUtils::Trim(string str)
    {
        int before = str.find_first_not_of(" \t");
        if(before < 0)
            before = 0;
        
        int after = str.find_last_not_of(" \t");
        if(after < 0)
            after = str.length();

        return str.substr(before, str.length() - (before - after));
    }

    inline bool StringUtils::OnlySpaces(string str)
    {
        return str.find_first_not_of(' ') < 0;
    }
}