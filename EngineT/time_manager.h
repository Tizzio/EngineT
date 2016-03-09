
#include "engine_t.h"


namespace EngineT
{
    class TimeManager
    {
        friend class EngineT;
    public:
        float delta = 0;
        int fps;
        float frameRate = 60.0f;
    private:
        Uint32 prevFrameTime = 0;
        Uint32 startFrameTime = 0;
        int ticks = 0;
        float accumulator = 0;

    };
}