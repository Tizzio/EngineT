
#pragma once

#include "engine_t.h"

namespace EngineT
{
    class RenderManager
    {
    public:
        void Render(Scene* scene);

        void Add(GameObjectRenderable* object);

        void Remove(GameObjectRenderable * object);

        Shader* shader;

        Camera* curCamera;
        GameObject* curObj;
        unsigned int textureUnit;

        vector<Light*> lights;

        struct Batch
        {
            Material* material;
            vector<GameObjectRenderable*> gameObjects;
        };

        vector<Batch> renderQueue;
    private: 
        void Add(GameObjectRenderable* object, Material* material);
    };
}