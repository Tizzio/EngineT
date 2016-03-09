#pragma once
#include "engine_t.h"
#include "bullet\btBulletCollisionCommon.h"
#include "bullet\btBulletDynamicsCommon.h"

namespace EngineT
{

    class Physics
    {
    public:
        Physics();
        ~Physics();
        void Add(Rigidbody* body);
        btDiscreteDynamicsWorld* world;
        vector<Rigidbody*> bodies;

    private:

        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;


    };

    enum class RigidbodyPrimitive
    {
        Box, Sphere, Capsule, Plane
    };

    class Rigidbody
    {
    public:
        GameObject3D* gameObject;
        btCollisionShape* shape;
        btDefaultMotionState* motionState;
        btRigidBody* body;
        Rigidbody(GameObject3D* obj3D);
        ~Rigidbody();
        void Instantiate(btCollisionShape* shape, btScalar mass, btVector3& inertia);
    };
}