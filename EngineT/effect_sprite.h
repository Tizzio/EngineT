#pragma once

#include "effect.h"


namespace EngineT
{
    class EffectSprite : public Effect
    {
    public:
        EffectSprite();
        void Enable();
        void UpdateUniforms();

        //uniforms
        GLint gWVP;
        GLint gSampler;

    };
}