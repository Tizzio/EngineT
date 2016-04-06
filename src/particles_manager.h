#pragma once

#include "engine_t.h"
#include "gameobject.h"
#include "physics_particle.h"

using namespace EngineT;
class ParticlesManager : public GameObject2D
{

public:

    vector<PhysicsParticle*> particles;

    ParticlesManager();
    ~ParticlesManager();

    void Update();
};
