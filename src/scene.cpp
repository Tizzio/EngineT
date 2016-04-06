
#include "scene.h"
#include "render_manager.h" 
#include "gameobject.h"
#include "camera.h" 


namespace EngineT
{

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    } 

    void Scene::Add(GameObject* gameObject)
    {
        gameObjects.push_back(gameObject);
        gameObject->isInScene = true;
    }

    void Scene::Add(GameObjectRenderable* gameObject)
    {
        gameObjects.push_back(gameObject);

        //if it's not in render queue and it has a material
        //assign a default material
        if(gameObject->material != nullptr)
        {
            gameObject->isInScene = true;
            Engine.renderManager->Add(gameObject);
        }
        //else
            //Engine.TrowError("Missing material NOT IMPLEMENTED DEFAULT MATERIAL", __LINE__, __FILE__); 

    } 

    void Scene::Remove(GameObject* gameObject)
    {
        for(auto go = gameObjects.begin(); go < gameObjects.end(); go++)
        {
            if((*go) == gameObject)
            {
                gameObjects.erase(go);
                gameObject->isInScene = false;
                break;
            }
        }
    }


    void Scene::Remove(GameObjectRenderable* gameObject)
    {
        for(auto go = gameObjects.begin(); go < gameObjects.end(); go++)
        {
            if((*go) == gameObject)
            {
                gameObjects.erase(go);
                gameObject->isInScene = false;
                Engine.renderManager->Remove(gameObject);
                break;
            }
        }
    }
     
    void Scene::Add(Light* light)
    {
        lights.push_back(light);
    }

    void Scene::Remove(Light* light)
    {
        for(auto it = lights.begin(); it < lights.end(); it++){
            if((*it) == light){
                lights.erase(it);
                break;
            }
        }
    }

    void Scene::Add(Camera* camera)
    {
        cameras.push_back(camera);
    }

    void Scene::Remove(Camera* camera)
    {
        for(auto it = cameras.begin(); it < cameras.end(); it++){
            if((*it) == camera){
                cameras.erase(it);
                break;
            }
        }
    }

    void Scene::Update()
    { 
        for(auto go : gameObjects)
        {
            go->Update();
        }
    }
}