
#pragma once


#include "engine_t.h"


#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF


namespace EngineT
{
    class ShaderManager
    {
    public:

        ShaderManager();

        ~ShaderManager();

        vector<string> errors;

        GLuint CreateProgram(const string& vertexShader, const string& fragmentShader, const string& geometryShader);
        GLuint CreateProgram(const char* vertexFname, const char* fragmentFname, const char* geometryFname);



        GLuint CreateShader(GLenum shaderType, const string& shaderText);

        GLint GetUniformLoc(GLuint shaderProg, const char* uniformName);

        unordered_map<string, GLint> GetAllUniforms(GLuint shaderProg);

        void PrintErrors();
    private:
        string ShaderTypeString(GLuint shaderType);

        string ReadShaderFile(const char* filename);
    };
}

