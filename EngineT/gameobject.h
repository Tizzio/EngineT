
#pragma once


#include "engine_t.h"
#include "transform.h"
#include "component.h"

namespace EngineT
{

    class GameObject
    {
        friend class Renderer;
        friend class Scene;
    public:
        Transform transform;
        int layer = 0;
        string name;

        
        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... mArgs)
        {
            T* component(new T(std::forward < TArgs(mArgs)...));

            component->gameObject = this;

            components.emplace_back(component);

            return *component;
        };
        
 

        template<typename T>
        T* GetComponent()
        {
            cout << "GetComponent" << endl;
            const string cName = typeid(T).name();
            for(Component* c : components)
            {
                cout << c->GetType() << " < -- > " << cName << endl;
                if(c->GetType() == cName)
                    return reinterpret_cast<T*>(c);
            }
            return nullptr;
        }

    protected:
        virtual void Update() = 0;
        vector<Component*> components;
    };


    class GameObject3D : public GameObject
    {
    public:
        TransformRenderable transform;
        void SetMesh(Mesh* mesh);
        Mesh* GetMesh();
    private:
        Mesh* mesh = NULL;
        void Draw();
    };

    class GameObject2D : public GameObject
    {
        friend class Renderer;
        friend class Scene;
    public:
        float imageIndex;
        float imageSpeed;
        TransformRenderable transform;
        void SetSprite(Sprite* sprite);
        Sprite* GetSprite();
    private:
        Sprite* sprite = NULL;
        void Draw();
    };
}
