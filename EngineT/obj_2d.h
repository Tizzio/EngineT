
#include "engine_t.h"
#include "gameobject.h"

using namespace EngineT;
class Obj2D : public GameObject2D
{
public:
    float speed;
    void Update();

    Obj2D();

};
