
#include "engine_t.h"
#include "shader_manager.h" 
#include "engine_setup.h" 
#include "inputs.h"
#include "gameobject.h"
#include "scene.h"
#include "render_manager.h" 
#include "physics.h" 
#include "engine_setup.h" 
#include <glm/gtc/type_ptr.hpp>

namespace EngineT
{
    EngineT& EngineT::Inst()
    {
        static EngineT instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    bool EngineT::Init(EngineSetup setup, int argc, char** argv)
    {
        if(init)
            return false; //already initialized

        init = true;


        windowWidth = setup.windowWidth;
        windowHeight = setup.windowHeight;
        if(!context.Init((int) setup.windowWidth, (int) setup.windowHeight, setup.fullscreen, setup.windowTitle))
        {
            return false;
        } 
        glClearColor(0, 116.0f / 255.0f, 161.0f/255.0f, 0.0f);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        physics = new Physics();

        time = new TimeManager();

        inputs = new Inputs();

        shaderManager = new ShaderManager();
        shaderManager->PrintErrors();
         
        renderManager = new RenderManager();

        return true;
    }

    int EngineT::Run()
    {
        context.Run();
        return 0;
    }


    bool EngineT::TrowError(string error, int line, string filename)
    {
        cout << "\n-------ERROR>-------\n" << "Line " << line << " of \"" << filename << "\"" << endl << error << "\n-------<ERROR-------\n" << endl;
        assert(false);
        this->error = true;
        return false;
    }


    bool EngineT::HasError()
    {
        return error;
    }

    void EngineT::Update()
    {
        //update physics world
        time->startFrameTime = SDL_GetTicks();


        physics->world->stepSimulation(1.0f / 60.0f);

        for(Rigidbody* rigidbody : physics->bodies)
        {
            float rawMat4[16];
            rigidbody->body->getWorldTransform().getOpenGLMatrix(rawMat4);
            rigidbody->gameObject->transform.matWorld = glm::make_mat4(rawMat4);

            //btVector3 pos = rigidbody->body->getWorldTransform().getOrigin();
            //rigidbody->gameObject->transform.SetPosition(vec3(pos.getX(), pos.getY(), pos.getZ()));

            //btQuaternion rot = rigidbody->body->getWorldTransform().getRotation();
            //rigidbody->gameObject->transform.SetRotation(quat(rot.getW(), rot.getX(), rot.getY(), rot.getZ()));

        }
        //update scene
        scene->Update();
    }

    void EngineT::Render()
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderManager->Render(scene);

        inputs->Clear();

        Uint32 curTime = SDL_GetTicks();

        //frame duration in seconds
        float delta = (curTime - time->prevFrameTime) / 1000.0f;
        time->accumulator += delta;

        if(time->accumulator >= 1.0f){
            float diff = time->accumulator - 1.0f;
            if(diff < 1.0f)
                time->accumulator = diff;
            else
                time->accumulator = 0;

            time->fps = time->ticks;
            time->ticks = 0;
            cout << "d: " << delta << " | " << time->fps << "fps \r";
        }

        if(delta > 0 && delta < 1.0f){
            time->delta = delta;
        }

        time->prevFrameTime = curTime;
        time->ticks++;

        float delay = (1000.0f / time->frameRate) - (curTime - time->startFrameTime);
        if(delay > 0 && delay < 1000.0f)
            SDL_Delay((Uint32) delay);

    }

    void EngineT::SetScene(Scene* scene)
    {
        this->scene = scene;
    }

    Scene * EngineT::GetScene()
    {
        return scene;
    }
}