
#include "fps_controller.h" 
#include "inputs.h"
#include "camera.h"
#include "renderer.h" 
#include "engine_t.h" 
#include "physics.h" 
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace EngineT
{
    FpsController::FpsController(Camera* cam, bool lock, bool hideCursor)
    {
        camera = cam;
        cam->LookAt(transform.position + vec3(0, 1, 0));
        inputs = Engine.inputs;
        setmouse = false;
        speed = 0;
        maxSpeed = 100.0f;
        acceleration = 50.0f;
        if(hideCursor)
            SDL_ShowCursor(false);
        mouseLock = lock;

        rayLambda[0] = 1.0f;
        rayLambda[1] = 1.0f;
        halfHeight = 1.0f;
        turnAngle = 0.0f;
        maxLinearVelocity = 10.0f;
        walkVelocity = 8.0f; // meters/sec
        turnVelocity = 1.0f; // radians/sec
        shape = NULL;
        rigidBody = NULL;
    }

    void FpsController::Setup(btScalar height, btScalar width, btScalar stepHeight)
    {
        btVector3 spherePositions[2];
        btScalar sphereRadii[2];

        sphereRadii[0] = width;
        sphereRadii[1] = width;
        spherePositions[0] = btVector3(0.0, (height / btScalar(2.0) - width), 0.0);
        spherePositions[1] = btVector3(0.0, (-height / btScalar(2.0) + width), 0.0);

        halfHeight = height / btScalar(2.0);

        shape = new btMultiSphereShape(&spherePositions[0], &sphereRadii[0], 2);

        btTransform startTransform(btQuaternion(0, 0, 0, 1), btVector3(0.0, 12.0, 0.0));
        //TODO: DELETE motionState
        btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
        /*shape->calculateLocalInertia(1.0f, std::move(btVector3(0, 0, 0)));*/
        btRigidBody::btRigidBodyConstructionInfo constructionInfo(1.0f, motionState, shape);
        rigidBody = new btRigidBody(constructionInfo);

        rigidBody->setSleepingThresholds(0.0, 0.0);
        rigidBody->setAngularFactor(0.0);
        rigidBody->setFriction(15.0f);
        Engine.physics->world->addRigidBody(rigidBody);
    }

    void FpsController::SetMouseLock(bool locked, bool hideCursor, float mouseSensitivity)
    {
        mouseLock = locked;
        this->mouseSensitivity = mouseSensitivity;
        SDL_ShowCursor(!hideCursor);

    }

    void FpsController::SetPosition(vec3 position)
    {
        transform.position = position;
        camera->LookAt(camera->target + (position - lastPosition));
        camera->SetPosition(position);
        lastPosition = transform.position;

    }

    void FpsController::PreUpdate()
    {

        btTransform xform = rigidBody->getWorldTransform();
        btVector3 down = -xform.getBasis()[1];
        btVector3 forward = xform.getBasis()[2];
        down.normalize();
        forward.normalize();

        raySource[0] = xform.getOrigin();
        raySource[1] = xform.getOrigin();

        rayTarget[0] = raySource[0] + down * halfHeight * btScalar(1.1);
        rayTarget[1] = raySource[1] + forward * halfHeight * btScalar(1.1);

        class ClosestNotMe : public btCollisionWorld::ClosestRayResultCallback
        {
        public:
            ClosestNotMe(btRigidBody* me) : btCollisionWorld::ClosestRayResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0))
            {
                m_me = me;
            }

            virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
            {
                if(rayResult.m_collisionObject == m_me)
                    return 1.0;

                return ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
            }
        protected:
            btRigidBody* m_me;
        };

        ClosestNotMe rayCallback(rigidBody);

        int i = 0;
        for(i = 0; i < 2; i++)
        {
            rayCallback.m_closestHitFraction = 1.0;
            Engine.physics->world->rayTest(raySource[i], rayTarget[i], rayCallback);
            if(rayCallback.hasHit())
            {
                rayLambda[i] = rayCallback.m_closestHitFraction;
            }
            else
            {
                rayLambda[i] = 1.0;
            }
        }
    }

    void FpsController::Update()
    {
        PreUpdate();
        float dt = Engine.time->delta;
        bool moved = false;

        if(mouseLock)
        {
            if(setmouse && !inputs->GetKey(Keycode::LSHIFT))
            {
                inputs->SetMouse((int) Engine.windowWidth / 2, (int) Engine.windowHeight / 2);
            }
            setmouse = !setmouse;
        }


        btVector3 linearVelocity = rigidBody->getLinearVelocity();
        btScalar speed = linearVelocity.length();

        btTransform xform = rigidBody->getWorldTransform();

        btScalar walkSpeed = walkVelocity;// *dt;

        bool forward = inputs->GetKey(Keycode::W);
        bool backward = inputs->GetKey(Keycode::S);
        bool left = inputs->GetKey(Keycode::A);
        bool right = inputs->GetKey(Keycode::D);

        vec3 forBack;
        if(forward)
            forBack = camera->forward;
        else if(backward)
            forBack = -camera->forward;

        vec3 leftRight;
        if(left)
            leftRight = -camera->right;
        else if(right)
            leftRight = camera->right;


        //debug onground
        bool onGround = rayLambda[0] < 1.0f;

        vec3 dirVector = forBack + leftRight;
        if(length(dirVector) > 0)
        {
            moved = true;

            btVector3 walkDirection = btVector3(dirVector.x, 0, dirVector.z).normalize();
            btVector3 velocity = walkDirection * walkSpeed*30.0f;
            rigidBody->applyCentralForce(velocity);

            velocity = rigidBody->getLinearVelocity();

        }

        if(onGround)
        {
            if(inputs->GetKeyPress(Keycode::SPACE))
            {
                btVector3 up = xform.getBasis()[1].normalize();
                btScalar magnitude = (btScalar(1.0) / rigidBody->getInvMass()) * btScalar(8.0);
                rigidBody->applyCentralImpulse(up * magnitude);
            }
        }

        //rigidBody->setCenterOfMassTransform(xform);
        //xform = rigidBody->getWorldTransform();
        if(speed > maxLinearVelocity)
        {
            rigidBody->applyCentralForce(linearVelocity.normalize() * maxLinearVelocity);
        }
        /*btQuaternion rot = xform.getRotation();
        transform.rotation = quat(rot.getW(), rot.getX(), rot.getY(), rot.getZ());*/

        btVector3 pos = xform.getOrigin();

        transform.position = vec3(pos.getX(), pos.getY(), pos.getZ());

        if(moved || lastPosition != transform.position)
        {
            camera->SetPosition(transform.position);
        }

        lastPosition = transform.position;


        //mouseLook

        if(mouseLock)
        {
            if(inputs->mouseMoved)
            {
                accumX += inputs->mouseDeltaX * mouseSensitivity;
                accumY += inputs->mouseDeltaY * mouseSensitivity;
            }

            if(accumX == 0 && accumY == 0)
                return;

            float deltaX = 0, deltaY = 0;

            deltaX = accumX * smoothMouseLook;

            deltaY = accumY * smoothMouseLook;

            accumX -= deltaX;
            accumY -= deltaY;


            camera->MouseLook(deltaX, deltaY);
        }
    }
}
