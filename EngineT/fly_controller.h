
#pragma once

 
#include "gameobject.h"

namespace EngineT
{
	class FlyController : public GameObject
	{
	public:
		FlyController(Camera* cam, bool lockMouse = true, bool hideCursor = true);
		void Update();
		Camera* camera;
		void SetPosition(vec3 position);
		void SetMouseLock(bool locked, bool hideCursor, float mouseSensitivity = 0.3f);
		float smoothMouseLook = 0.6f;
	private:
		Inputs* inputs;
		float speed;
		float acceleration;
		float maxSpeed;
		bool setmouse;
		vec3 lastPosition;
		float accumX;
		float accumY;
		bool mouseLock;
		float mouseSensitivity = 0.2f;

	};
}