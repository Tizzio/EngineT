#include "physics_particle.h"

PhysicsParticle::PhysicsParticle()
{
    radius = 8.0f;
    mass = 3.14159 * radius * radius * radius;

    charge = 1;
    speed = vec3(1.0f);
    newSpeed = speed;
}


PhysicsParticle::~PhysicsParticle()
{
}

void PhysicsParticle::Solve(PhysicsParticle * other)
{ 
    vec3 d = position - other->position;

    float r = glm::length(d);
    float r2 = r * r;
    if(r == 0)
        return;

    float p = radius - other->radius;

    vec3 n = d / r;

    if(p > 0)
    {
        //fix position
        float ratio = other->mass / (other->mass + mass);
        position += n * p * ratio;

        //calculate collision							
        float dot = glm::dot(speed - other->speed, d);
        float f = 2 * other->mass / (mass + other->mass) * dot / r2;
        newSpeed = speed - d * f * 0.8f;
    }
    else
    {
        float chargeSign = charge * (-other->charge);
        newSpeed -= n * k * other->mass * chargeSign / r2;
    } 
}
