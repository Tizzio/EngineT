#include "engine_t.h"
namespace EngineT
{
    class Utils
    {
    public:
        static vector<int> StringToIntArray(string str)
        {
            vector<int> data;
            string buf;
            stringstream stream(str);
            while(stream >> buf){
                data.push_back(stoi(buf));
            }
            return data;

        }

        static vector<string> StringToStringArray(string str)
        {
            vector<string> data;
            string buf;
            stringstream stream(str);
            while(stream >> buf)
            {
                data.push_back(buf);
            }
            return data;
        }

        static string GetStringAfter(string str, char separator)
        {
            int skip = str.find_first_of(separator) + 1;
            return str.substr(skip, str.length() - skip);
        }

        static int GetIntAfter(string str, char separator)
        {
            int skip = str.find_first_of(separator) + 1;
            return stoi(str.substr(skip, str.length() - skip));
        }

        static vec4 HexColorToVec4(string color)
        {
            float c1 = strtol(color.substr(1, 2).c_str(), nullptr, 16) / 255.0f;
            float c2 = strtol(color.substr(3, 2).c_str(), nullptr, 16) / 255.0f;
            float c3 = strtol(color.substr(5, 2).c_str(), nullptr, 16) / 255.0f;
            return vec4(c1, c2, c3, 1.0f);
        }
    };
}