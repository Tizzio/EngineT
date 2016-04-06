
#include "material.h" 
#include "shader.h"
#include "texture.h"
#include "cubemap.h"

namespace EngineT
{ 
    Material::Material(Shader * shader, Texture * a, Texture * s, Texture * n, Texture * e, Texture * o)
    {
        this->shader = shader;
        albedo = a;
        specular = s;
        normalmap = n;
        emission = e;
        occlusion = o;
    }

    void Material::Enable()
    {
        if(shader == nullptr)
        {
            Engine.TrowError("ERROR in Material -> shader does not exits", __LINE__, __FILE__);
            return;
        }


        shader->Enable(this);

        // Bind textures

        if(albedo) 
            albedo->Bind(GL_TEXTURE0); 

        if(specular)
            specular->Bind(GL_TEXTURE1);

        if(normalmap)
            normalmap->Bind(GL_TEXTURE2);
        
        if(occlusion)
            occlusion->Bind(GL_TEXTURE3);

        if(emission)
            emission->Bind(GL_TEXTURE4);

        if(cubemap)
            cubemap->Bind();

        // Settings

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