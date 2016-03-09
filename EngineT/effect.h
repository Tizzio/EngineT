#pragma once


#include "engine_t.h"

#include <glm/gtc/matrix_transform.hpp>


namespace EngineT
{

    class Effect
    {
    public:
        Effect();

        GLuint CreateProgram(const char* vertexFname, const char* fragmentFname, const char* geometryFname);
        GLint GetUniformLoc(const char* uniformName);
        GLint GetUniformLoc(const string& uniformName);

        GLint Loc(const string& uniformName);
        virtual void Enable() = 0;
        virtual void UpdateUniforms() = 0;


    protected:
        ShaderManager* shaderManager;
        Renderer* renderer;
        GLuint shaderProgram;
        unordered_map<string, GLint> uLoc;//uniform location


    };
}