#include "particles_manager.h"


ParticlesManager::ParticlesManager()
{
    for(int i = 0; i < 1000; i++)
    {
        particles.push_back(new PhysicsParticle());
    }
}

void ParticlesManager::Update()
{ 
    for(PhysicsParticle* p : particles)
    {
        for(PhysicsParticle* p2 : particles)
        {
            p->Solve(p2);
        }
    }
}


ParticlesManager::~ParticlesManager()
{
}
