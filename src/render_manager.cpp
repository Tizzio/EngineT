
#include "render_manager.h" 
#include "gameobject.h"
#include "scene.h"
#include "camera.h"
#include "mesh.h"
#include "sprite.h"
#include "ui_text.h"
#include "shader.h"
#include "material.h"

namespace EngineT
{
    void RenderManager::Render(Scene* scene)
    {
        if(scene == nullptr) return;
        if(scene->cameras.size() == 0) return;
      
        lights = scene->lights;

        for(auto cam : scene->cameras)
        {
            curCamera = cam;
            vec3 pos = cam->position;

            for(Batch batch : renderQueue)
            {
                batch.material->Enable();

                for(GameObjectRenderable* go : batch.gameObjects)
                {
                    curObj = go;
                    batch.material->Update();
                    go->Draw();
                }
            }
        }  
    }

    /*
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_BLEND);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    */
     

    void RenderManager::Add(GameObjectRenderable * object)
    {   
        Add(object, object->material);
    }

    void RenderManager::Remove(GameObjectRenderable * object)
    {
        for(Batch b : renderQueue)
        {
            if(b.material == object->material)
            {
                for(auto go = b.gameObjects.begin(); go < b.gameObjects.end(); go++)
                {
                    if((*go) == object)
                    {
                        b.gameObjects.erase(go);
                        return;
                    }
                }
            }
        }
    }

    void RenderManager::Add(GameObjectRenderable* object, Material* material)
    {
        //the material exists
        bool found = false;
        for(Batch& b : renderQueue)
        {
            if(b.material == material)
            { 
                b.gameObjects.push_back(object); 
                found = true;
                break;
            }
        }

        //add new batch if the material does not exists
        if(!found)
        { 
            Batch batch;
            batch.material = material;
            batch.gameObjects.push_back(object);
            renderQueue.push_back(std::move(batch));
        } 
    }
}