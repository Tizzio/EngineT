#pragma once

#include "shader_mesh.h"


namespace EngineT
{
    class ShaderLighting : public ShaderMesh
    {
    public:

        static const unsigned int MAX_POINT_LIGHTS = 2;
        static const unsigned int MAX_SPOT_LIGHTS = 2;

        ShaderLighting();

        virtual void Enable();
        virtual void UpdateUniforms();

        bool hasSpecular;
        bool hasNnormalmap;
    
    private:

        virtual void LoadUniforms();

        //specular
        GLint uWVP;
        GLint uWorld;
        GLint uEyeWorldPos; 
         
        GLint uNumPointLights;
        GLint uNumSpotLights;
        GLint uAmbientIntensity;

        struct DirLight
        {
            GLint color;
            GLint direction;
            GLint diffuseIntensity;
        };

        struct PointLight
        {
            GLint color;
            GLint diffuseIntensity;
            GLint attenConstant;
            GLint attenLinear;
            GLint attenExp;
            GLint position;
        };

        struct SpotLight
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

        vector<DirLight> uDirLights;
        vector<PointLight> uPointLights;
        vector<SpotLight> uSpotLights;

        GLint uSpecularIntensity;
        GLint uSpecularPower;

    };

}