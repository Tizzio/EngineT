
#pragma once

#include "gameobject.h"

namespace EngineT {
	class FpsController : public GameObject
	{
	public:

		float speed;
		float acceleration;
		float maxSpeed;
		float mouseSensitivity = 0.2f;

		FpsController(Camera* cam, bool lockMouse = true, bool hideCursor = true);
		void Setup(btScalar height = 2.0f, btScalar width = 0.25f, btScalar stepHeight = 0.25f);
		void Update();
		Camera* camera;
		void SetPosition(vec3 position);
		void SetMouseLock(bool locked, bool hideCursor, float mouseSensitivity = 0.3f);
		float smoothMouseLook = 0.6f;
	
	private:

		void PreUpdate();

		btScalar halfHeight;
		btCollisionShape* shape;
		btRigidBody* rigidBody;

		btVector3 raySource[2];
		btVector3 rayTarget[2];
		btScalar rayLambda[2];
		btVector3 rayNormal[2];

		btScalar turnAngle;

		btScalar maxLinearVelocity;
		btScalar walkVelocity;
		btScalar turnVelocity;

		Inputs* inputs;
		bool setmouse;
		vec3 lastPosition;
		float accumX;
		float accumY;
		bool mouseLock;

	};

}