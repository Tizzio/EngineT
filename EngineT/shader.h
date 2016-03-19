#pragma once

#include "engine_t.h"
 
namespace EngineT
{
    class Shader
    {
    public:
        Shader();

        GLuint CreateProgram(string vertexFname, string fragmentFname, string geometryFname);
        GLint GetUniformLoc(const char* uniformName);
        GLint GetUniformLoc(const string& uniformName);

        GLint Loc(const string& uniformName);
        virtual void Enable() = 0;
        virtual void UpdateUniforms() = 0;
    protected:

        virtual void LoadUniforms() = 0;
        ShaderManager* shaderManager;
        Renderer* renderer;
        GLuint shaderProgram;
        unordered_map<string, GLint> uLoc;//uniform location
    };
}