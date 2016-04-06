#pragma once



#include "engine_t.h"


namespace EngineT
{
     
    class Cubemap
    {
    public:
        Cubemap(const string  right, const string  left, const string  top, const string  bottom, const string  front, const string  back);
        void Load(vector<string> fileNames);
        void Bind();
        
    private: 
        GLuint textureID;
    };
}