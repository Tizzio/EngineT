#pragma once

#include "effect.h"


namespace EngineT {
	class EffectText : public Effect
	{
	public:
		EffectText();
		void Enable();
		void UpdateUniforms();

		//uniforms
		GLint gWVP;
		GLint gSampler;


	};
}