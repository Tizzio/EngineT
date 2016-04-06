
#pragma once


#include "engine_t.h"

namespace EngineT
{

    class Scene
    {
        friend class RenderManager;
    private: 
        vector<GameObject*>  gameObjects;

    public:
        vector<Camera*> cameras;
        vector<Light*> lights;
        Scene();
        ~Scene();
         
        void Add(GameObject* gameObject);
        void Add(GameObjectRenderable * gameObject); 

        void Remove(GameObject* gameObject);
        void Remove(GameObjectRenderable * gameObject);

        void Add(Light* light);
        void Remove(Light* light);

        void Add(Camera* camera);
        void Remove(Camera* camera);

        void Update();


    };
}

