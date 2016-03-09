
#pragma once


namespace EngineT
{
    class EngineSetup
    {
    public:
        float windowWidth;
        float windowHeight;
        bool fullscreen;
        string windowTitle;

        EngineSetup(float width = 800.0f, float height = 500.0f, bool fullScreen = false, string title = "EngineT")
        {
            windowWidth = width;
            windowHeight = height;
            fullscreen = fullScreen;
            windowTitle = title.c_str();

        }
    };
}