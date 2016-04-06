
#pragma once

#include "root_declar.h"
#include "engine_setup.h"
#include "time_manager.h"
#include "context.h"

//#include <GL/freeglut.h> 

namespace EngineT
{

    static const float toRad = 0.01745329251f;

    class EngineT
    {
        friend class Inputs;

    public:
        static EngineT& Inst();


        bool Init(EngineSetup setup, int argc, char** argv);
        int Run();

        void SetScene(Scene* scene);
        Scene* GetScene();

        void Update();
        void Render();
        bool TrowError(string error, int line, string filename);
        bool HasError();

        Inputs* inputs;
        ShaderManager* shaderManager;
        RenderManager* renderManager;
        TimeManager* time;

        Physics* physics;
        string dataPath = "data/";
        float windowWidth;
        float windowHeight;

    private:

        bool error = false;
        Context context;

        Scene* scene;
        bool init = false;

        EngineT() {};// Private so that it can  not be called
        EngineT(EngineT const&) {};// copy constructor is private
        void operator=(EngineT const&); // assignment operator is private

    };

    static EngineT& Engine = EngineT::Inst();

}
