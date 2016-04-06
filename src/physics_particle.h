#pragma once
#include "engine_t.h"
class PhysicsParticle
{

public:
   
    //physics properties
    float k = 0.001f;
    float sx;
    float sy;
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 newSpeed;
    float radius;
    float mass;
    float charge;

    PhysicsParticle();
    ~PhysicsParticle();

    void Solve(PhysicsParticle* other);
};

