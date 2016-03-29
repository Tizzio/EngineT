
#pragma once


#include "engine_t.h"

#include <unordered_set>

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
         
        GLuint CreateShader(GLenum shaderType, const string& shaderText);

        GLint GetUniformLoc(GLuint shaderProg, const char* uniformName);

        unordered_map<string, GLint> GetAllUniforms(GLuint shaderProg);

        void PrintErrors();
        Shader* Load(const string filename);
    private:

        vector<string> header;
        unordered_map<string, string> headerMap;
        vector<string> vertex;
        vector<string> geometry;
        vector<string> fragment;
        std::unordered_set<string> defines;

        string ShaderTypeString(GLuint shaderType);
        string ReadShaderFile(const char* filename);
       
        void ParseShader(vector<string>& input, vector<string>& output, const string filename);
        bool SaveToFile(const string filename, vector<string>& lines);
        
        inline bool HeaderExits(string key)
        {
            return headerMap.find(key) != headerMap.end();
        }

        inline bool HeaderEnabled(string key)
        {
            return headerMap.find(key) != headerMap.end() && headerMap[key] == "On";
        }

    };
}

