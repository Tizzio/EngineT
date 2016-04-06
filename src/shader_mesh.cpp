
#include "shader_mesh.h"
#include "render_manager.h"
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

    void ShaderMesh::Enable(Material* material)
    {
        glUseProgram(shaderProgram);
    }

    void ShaderMesh::UpdateUniforms()
    {
        renderManager = Engine.renderManager;
       
        mat4 worldMatrix = ((GameObject3D*) (renderManager->curObj))->transform.GetWorldMatrix();//translate(mat4(), transform.position);
        mat4  WVP = renderManager->curCamera->GetViewProjMatrix() * worldMatrix;

        glUniformMatrix4fv(uWVP, 1, GL_FALSE, &WVP[0][0]); //set WVP

        //glUniform1i(GetUniformLoc("uSampler"), 0); //set texture unit 
    }
}
