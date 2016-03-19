
#pragma once

#include "engine_t.h"

namespace EngineT
{
    class Renderer
    {
    public:
        void Render(Scene* scene);

        Shader* shader;

        Camera* curCamera;
        GameObject* curObj;
        unsigned int textureUnit;

        vector<Light*> lights;
        unordered_map<Material*, vector<GameObject*>> renderQueueOpaque;
        
    };
}