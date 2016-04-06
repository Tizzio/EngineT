
#include "light.h" 

namespace EngineT
{
    Light::Light(LightType type)
    {

        this->type = type;

        color = vec3(0.5f, 0.5f, 0.5f);
        diffuseIntensity = 0.5f;

        attenuationConstant = 0.1f;
        attenuationLinear = 0.1f;
        attenuationExp = 0.15f;
        cutoff = 0.3f;
    }

    Light::~Light()
    {
    }
}