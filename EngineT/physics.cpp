
#include "physics.h"
#include "gameobject.h"
#include "engine_t.h"

namespace EngineT
{

    Physics::~Physics()
    {
        for(Rigidbody* body : bodies)
        {
            delete body;
        }

        delete solver;
        delete collisionConfiguration;
        delete dispatcher;
        delete broadphase;
        delete world;
    }

    Physics::Physics()
    {
        //setup
        broadphase = new btDbvtBroadphase();
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        solver = new btSequentialImpulseConstraintSolver;

        //create new world
        world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

        //set default gravity
        world->setGravity(btVector3(0, -10, 0));

    }

    void Physics::Add(Rigidbody* rigidbody)
    {
        Engine.physics->world->addRigidBody(rigidbody->body);
        bodies.push_back(rigidbody);
    }


    Rigidbody::Rigidbody(GameObject3D* obj3D)
    {
        assert(obj3D != nullptr);
        gameObject = obj3D;
    }

    Rigidbody::~Rigidbody()
    {
        Engine.physics->world->removeRigidBody(body);
        delete body;
        delete shape;
        delete motionState;
    }

    void Rigidbody::Instantiate(btCollisionShape* shape, btScalar mass, btVector3 inertia)
    {
        assert(shape != nullptr);
        this->shape = shape;


        vec3 pos = gameObject->transform.position;
        //leaving the rotation to btQuaternion(0, 0, 0, 1) for debug purposes
        motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));

        //calculate local intertia
        if(mass > 0)
        {
            shape->calculateLocalInertia(mass, inertia);
        }

        btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, shape, inertia);

        body = new btRigidBody(constructionInfo);
        body->setFriction(1.0f);
        Engine.physics->Add(this);

    }


    void test()
    {

        auto broadphase = new btDbvtBroadphase();
        auto collisionConfiguration = new btDefaultCollisionConfiguration();
        auto dispatcher = new btCollisionDispatcher(collisionConfiguration);
        auto solver = new btSequentialImpulseConstraintSolver;

        //create new world
        auto world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

        //set default gravity
        world->setGravity(btVector3(0, -10, 0));
        btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);


        btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
        btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
        btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
        world->addRigidBody(groundRigidBody);

        btCollisionShape* fallShape = new btSphereShape(1);

        btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
        btScalar mass = 1;
        btVector3 fallInertia(0, 0, 0);
        fallShape->calculateLocalInertia(mass, fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
        btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
        world->addRigidBody(fallRigidBody);


        for(int i = 0; i < 300; i++)
        {
            world->stepSimulation(1 / 60.f, 10);
            btTransform trans;
            fallRigidBody->getMotionState()->getWorldTransform(trans);
            std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
        }

        world->removeRigidBody(fallRigidBody);
        delete fallRigidBody->getMotionState();
        delete fallRigidBody;

        world->removeRigidBody(groundRigidBody);
        delete groundRigidBody->getMotionState();
        delete groundRigidBody;


        delete fallShape;

        delete groundShape;

    }
}
