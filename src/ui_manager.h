#pragma once  

#include "engine_t.h"  

namespace EngineT
{
    class UIManager
    {
        friend class EngineT;
        friend class RenderManager;

    public:
        UIWindow* CreateWindow(float x, float y, float width, float height);
        void DestroyWindow(UIWindow* window);

        UIWindow* GetWindow(float x, float y);

    private:
        vector<UIWindow*> windows;
        void Update();
        void Render();


    };
}