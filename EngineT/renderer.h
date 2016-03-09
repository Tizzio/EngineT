
#pragma once

#include "engine_t.h"

namespace EngineT{
	class Renderer{
	public:
		void Render(Scene* scene);

		Effect* effect;

		Camera* curCamera;
		GameObject* curObj;
		unsigned int textureUnit;

		vector<Light*> lights;
	};

}