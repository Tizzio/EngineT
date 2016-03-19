#pragma once

#include "shader.h"


namespace EngineT
{
    class ShaderMesh : public Shader
    {
    public:
         
        ShaderMesh();

        virtual void Enable();
        virtual void UpdateUniforms(); 
    
    private:

        virtual void LoadUniforms();

        //projection
        GLint uWVP; 
    };

}