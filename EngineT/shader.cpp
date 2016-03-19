
#include "shader.h"
#include "renderer.h"
#include "shader_manager.h"

namespace EngineT
{
    Shader::Shader()
    {
        shaderManager = Engine.shaderManager;
        renderer = Engine.renderer;
    }

    GLuint Shader::CreateProgram(string vertex, string fragment, string geometry)
    {
        GLuint program = shaderManager->CreateProgram(vertex, fragment, geometry);
        if(program == 0)
        {
            cout << "Impossible to create shader program:" << endl;
            shaderManager->PrintErrors();
        }
        else{
            shaderProgram = program; 
            uLoc = shaderManager->GetAllUniforms(program);
            LoadUniforms();
        }

        return program;
    }

    GLint Shader::Loc(const string& uniformName)
    {
        if(uLoc.find(uniformName) == uLoc.end())
        {
            cout << "undefined uniform: " << uniformName << endl;
            return -1;
        }
        else
            return uLoc[uniformName];
    }

    GLint Shader::GetUniformLoc(const char* uniformName)
    {
        GLint location = shaderManager->GetUniformLoc(shaderProgram, uniformName);
        if(location == 0xFFFFFFFF)
            shaderManager->PrintErrors();
        return location;
    }

    GLint Shader::GetUniformLoc(const string& uniformName)
    {
        GLint location = shaderManager->GetUniformLoc(shaderProgram, uniformName.c_str());
        if(location == 0xFFFFFFFF)
            shaderManager->PrintErrors();
        return location;
    }
}