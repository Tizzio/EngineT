
#pragma once

#include "engine_t.h" 
#include "transform.h" 


namespace EngineT
{
    enum class LightType { Directional, Point, Spot };

    class Light
    {
    public:
        Transform transform;

        Light(LightType type);
        ~Light();

        vec3 color;

        LightType type;
        float diffuseIntensity;

        float attenuationConstant;
        float attenuationLinear;
        float attenuationExp;

        float cutoff;



    };
}


