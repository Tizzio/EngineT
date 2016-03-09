
#include "obj_3d.h"

void Obj3D::Update()
{
    /*
    float dt = Engine.time->delta;
    transform.AddRotation(speed * dt, vec3(0.0f, 1.0f, 0.0f));
    */
}

Obj3D::Obj3D()
{
    float r = (float) rand() / (float) RAND_MAX;
    speed = r * 10.0f;
}
