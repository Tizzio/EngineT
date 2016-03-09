
#include "effect_sprite.h"
#include "renderer.h"
#include "gameobject.h"
#include "camera.h"
#include "light.h"
#include "transform.h"


namespace EngineT
{

    EffectSprite::EffectSprite()
    {

        GLuint prog = CreateProgram("data/shaders/sprite_default.vs", "data/shaders/sprite_default.fs", "");

        //uniforms
        gWVP = Loc("gWVP");
        gSampler = Loc("gSampler");


    }

    void EffectSprite::Enable()
    {
        glUseProgram(shaderProgram);
    }

    void EffectSprite::UpdateUniforms()
    {
        mat4 worldMatrix = ((GameObject2D*) (renderer->curObj))->transform.GetWorldMatrix();
        mat4  WVP = renderer->curCamera->GetViewProjMatrix() * worldMatrix;
        glUniformMatrix4fv(gWVP, 1, GL_FALSE, &WVP[0][0]); //set WVP 
        glUniform1i(gSampler, 0); //set texture unit 
    }

}