
#include "material.h" 
#include "shader.h"
#include "texture.h"

namespace EngineT
{
    Material::Material(Shader* s, Texture* t)
    {
        shader = s;
        texture = t;
    }

    void Material::Enable()
    {
        if(shader == nullptr)
        {
            cout << "ERROR in Material -> shader does not exits" << endl;
            return;
        }

        if(texture == nullptr)
        {
            cout << "ERROR in Material -> texture does not exits" << endl;
            return;
        }

        shader->Enable();

        texture->Bind(GL_TEXTURE0);

        if(backfaceCulling)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);

        if(depthTest)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);

        if(blending)
        {
            glEnable(GL_BLEND);
            glBlendFunc(blendFuncSource, blendFuncDest);
        }
        else 
            glDisable(GL_BLEND);
    }

    void Material::Update()
    {
        shader->UpdateUniforms();
    }
}