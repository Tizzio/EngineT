
#include "shader_mesh.h"
#include "renderer.h"
#include "gameobject.h"
#include "camera.h"
#include "light.h"
#include "transform.h"

namespace EngineT
{ 
    ShaderMesh::ShaderMesh()
    { 
    }

    void ShaderMesh::LoadUniforms()
    {
        uWVP = Loc("uWVP"); 
    }

    void ShaderMesh::Enable()
    {
        glUseProgram(shaderProgram);
    }

    void ShaderMesh::UpdateUniforms()
    {
        renderer = Engine.renderer;
       
        mat4 worldMatrix = ((GameObject3D*) (renderer->curObj))->transform.GetWorldMatrix();//translate(mat4(), transform.position);
        mat4  WVP = renderer->curCamera->GetViewProjMatrix() * worldMatrix;

        glUniformMatrix4fv(uWVP, 1, GL_FALSE, &WVP[0][0]); //set WVP

        //glUniform1i(GetUniformLoc("uSampler"), 0); //set texture unit 
    }
}
