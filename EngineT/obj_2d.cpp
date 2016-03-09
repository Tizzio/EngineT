#include "obj_2d.h"

void Obj2D::Update()
{
    //float dt = Engine.time->delta;
    //transform.AddRotation(speed * dt, vec3(0, 0, 1.0f));
}

Obj2D::Obj2D()
{
    float r = (float) rand() / (float) RAND_MAX;
    speed = -75.0f + r * 150.0f;

}
