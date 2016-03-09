#pragma once

#include "effect.h"


namespace EngineT
{
    class LightEffect : public Effect
    {
    public:

        static const unsigned int MAX_POINT_LIGHTS = 2;
        static const unsigned int MAX_SPOT_LIGHTS = 2;

        LightEffect();

        virtual void Enable();
        virtual void UpdateUniforms();

        //uniforms
        GLint gWVP;
        GLint gWorld;
        GLint gSampler;
        GLint gEyeWorldPos;
        GLint gSpecularIntensity;
        GLint gSpecularPower;

        struct gDirLight
        {
            GLint color;
            GLint direction;
            GLint diffuseIntensity;
        };

        struct gPointLight
        {
            GLint color;
            GLint diffuseIntensity;
            GLint attenConstant;
            GLint attenLinear;
            GLint attenExp;
            GLint position;
        };

        struct gSpotLight
        {
            GLint color;
            GLint diffuseIntensity;
            GLint attenConstant;
            GLint attenLinear;
            GLint attenExp;
            GLint position;
            GLint direction;
            GLint cutoff;
        };

        vector<gDirLight> gDirLights;
        vector<gPointLight> gPointLights;
        vector<gSpotLight> gSpotLights;

        GLint gNumPointLights;
        GLint gNumSpotLights;
        GLint gAmbientIntensity;

    };

}