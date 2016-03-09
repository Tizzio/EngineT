
#include "light.h" 

namespace EngineT
{
	Light::Light(LightType type)
	{

		this->type = type;

		color = vec3(0.5f, 0.5f, 0.5f);
		diffuseIntensity = 0.5f;

		attenuationConstant = 0.05f;
		attenuationLinear = 0.05f;
		attenuationExp = 0.005f;
		cutoff = 0.3f;
	}

	Light::~Light()
	{
	}
}