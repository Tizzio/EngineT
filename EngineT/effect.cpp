
#include "effect.h"
#include "renderer.h"
#include "shader_manager.h"

namespace EngineT
{
    Effect::Effect()
    {
        shaderManager = Engine.shaderManager;
        renderer = Engine.renderer;
    }

    GLuint Effect::CreateProgram(const char* vertexFname, const char* fragmentFname, const char* geometryFname)
    {
        GLuint program = shaderManager->CreateProgram(vertexFname, fragmentFname, geometryFname);
        if(program == 0){
            cout << "Error creating shader program" << endl;
            shaderManager->PrintErrors();
        }
        else{
            shaderProgram = program;
            //add uniform locations 
            uLoc = shaderManager->GetAllUniforms(program);

        }

        return program;
    }



    GLint Effect::Loc(const string& uniformName)
    {
        if(uLoc.find(uniformName) == uLoc.end()) {
            cout << "undefined uniform: " << uniformName << endl;
            return -1;
        }
        else {
            return uLoc[uniformName];
        }
    }

    GLint Effect::GetUniformLoc(const char* uniformName)
    {
        GLint location = shaderManager->GetUniformLoc(shaderProgram, uniformName);
        if(location == 0xFFFFFFFF){
            shaderManager->PrintErrors();
        }
        return location;
    }
    GLint Effect::GetUniformLoc(const string& uniformName)
    {
        GLint location = shaderManager->GetUniformLoc(shaderProgram, uniformName.c_str());
        if(location == 0xFFFFFFFF){
            shaderManager->PrintErrors();
        }
        return location;
    }
}