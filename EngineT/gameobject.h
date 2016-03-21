
#pragma once


#include "engine_t.h"
#include "transform.h"
#include "component.h"

namespace EngineT
{

    class GameObject
    {
        friend class RenderManager;
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

        virtual void Update() = 0;
    protected:
        vector<Component*> components;
        bool isInScene;
    };


    class GameObjectRenderable : public GameObject
    {
        friend class RenderManager;
        friend class Scene;
    public:
        
        TransformRenderable transform;
        void SetMaterial(Material* material);
        Material* GetMaterial();
    protected:
        virtual void Draw() = 0;
        Material* material = nullptr;
    };

    class GameObject3D : public GameObjectRenderable
    {
        friend class RenderManager;
        friend class Scene;
    public: 
        void SetMesh(Mesh* mesh);
        Mesh* GetMesh();

    private:
        Mesh* mesh = nullptr;
        void Draw() override;
    };

    class GameObject2D : public GameObjectRenderable
    {
        friend class RenderManager;
        friend class Scene;
    public:
        float imageIndex;
        float imageSpeed;
        void SetSprite(Sprite* sprite);
        Sprite* GetSprite();
    private:
        Sprite* sprite = nullptr;
        void Draw() override;
    };
}
