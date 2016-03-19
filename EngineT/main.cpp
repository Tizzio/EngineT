
#include "engine_t.h"
#include "Game.h"


using namespace EngineT;
int main(int argc, char** argv)
{
    EngineSetup setup(900, 500, false, "EngineT");

    if(!Engine.Init(setup, argc, argv))
    {
        return 0;
    }

    Game game;

    return Engine.Run();
}