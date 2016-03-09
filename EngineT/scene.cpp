
#include "scene.h"
#include "gameobject.h"
#include "ui_text.h"
#include "camera.h" 


namespace EngineT
{


    Scene::Scene()
    {
    }

    Scene::~Scene()
    {

    }

    Layer Scene::CreateLayer()
    {
        objLayers[currentLayerId] = vector<GameObject*>();
        obj2DLayers[currentLayerId] = vector<GameObject2D*>();
        obj3DLayers[currentLayerId] = vector<GameObject3D*>();
        textLayers[currentLayerId] = vector<Text*>();
        layerList.push_back(currentLayerId);
        return currentLayerId++;
    }

    void Scene::DeleteLayer(Layer layer)
    {
        //TODO: implement
    }

    void Scene::Add(GameObject* gameObject, Layer layer)
    {
        gameObject->layer = layer;
        auto gameObjects = &objLayers[layer];
        gameObjects->push_back(gameObject);
    }
    void Scene::Add(GameObject2D* gameObject, Layer layer)
    {
        gameObject->layer = layer;
        auto gameObjects = &obj2DLayers[layer];
        gameObjects->push_back(gameObject);
    }
    void Scene::Add(Text* text, Layer layer)
    {
        text->layer = layer;
        auto texts = &textLayers[layer];
        texts->push_back(text);
    }
    void Scene::Add(GameObject3D* gameObject, Layer layer)
    {
        gameObject->layer = layer;
        auto gameObjects = &obj3DLayers[layer];
        gameObjects->push_back(gameObject);
    }

    void Scene::Remove(GameObject* gameObject)
    {

        auto gameObjects = &objLayers[gameObject->layer];
        for(auto go = gameObjects->begin(); go < gameObjects->end(); go++){
            if((*go) == gameObject){
                gameObjects->erase(go);
                break;
            }
        }
    }
    void Scene::Remove(GameObject2D* gameObject)
    {

        auto gameObjects = &obj2DLayers[gameObject->layer];
        for(auto go = gameObjects->begin(); go < gameObjects->end(); go++){
            if((*go) == gameObject){
                gameObjects->erase(go);
                break;
            }
        }
    }
    void Scene::Remove(GameObject3D* gameObject)
    {

        auto gameObjects = &obj3DLayers[gameObject->layer];
        for(auto go = gameObjects->begin(); go < gameObjects->end(); go++){
            if((*go) == gameObject){
                gameObjects->erase(go);
                break;
            }
        }
    }

    //TODO: Important, add method remove text


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

    void Scene::Add(Camera* camera, Layer layer)
    {
        camera->layer = layer;
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
        for(Layer layer : layerList)
        {
            for(auto go : objLayers[layer])
            {
                go->Update();
            }

            for(auto go : obj2DLayers[layer])
            {
                go->Update();
            }

            for(auto go : obj3DLayers[layer])
            {
                go->Update();
            }

        }
    }
}