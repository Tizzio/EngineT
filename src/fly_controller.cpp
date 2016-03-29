
#include "fly_controller.h" 
#include "inputs.h"
#include "camera.h"
#include "light.h" 
#include "render_manager.h" 
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace EngineT
{
	FlyController::FlyController(Camera* cam, bool lock, bool hideCursor)
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
	}


	void FlyController::SetMouseLock(bool locked, bool hideCursor, float mouseSensitivity)
	{
		mouseLock = locked;
		this->mouseSensitivity = mouseSensitivity;
		SDL_ShowCursor(!hideCursor);

	}

	void FlyController::SetPosition(vec3 position)
	{
		transform.position = position;
		camera->LookAt(camera->target + (position - lastPosition));
		camera->SetPosition(position);
		lastPosition = transform.position;

	}

	void FlyController::Update()
	{
		if(mouseLock){
			if(setmouse && !inputs->GetKey(Keycode::LSHIFT)){
				inputs->SetMouse((int) Engine.windowWidth / 2, (int) Engine.windowHeight / 2);
			}
			setmouse = !setmouse;
		}

        if(light)
            light->transform.position = transform.position;
		float dt = Engine.time->delta;
		bool moved = false;
		if(inputs->GetKey(Keycode::W))
		{
			if(speed < maxSpeed)
				speed += acceleration  * dt;
			transform.AddPosition(camera->forward * (speed * dt));
			moved = true;
		}
		else if(inputs->GetKey(Keycode::S))
		{
			if(speed < maxSpeed)
				speed += acceleration * dt;
			transform.AddPosition(-camera->forward*(speed * dt));
			moved = true;
		}

		if(inputs->GetKey(Keycode::A))
		{
			if(speed < maxSpeed)
				speed += acceleration * dt;
			transform.AddPosition(-camera->right*(speed * dt));
			moved = true;
		}
		else if(inputs->GetKey(Keycode::D))
		{
			if(speed < maxSpeed)
				speed += acceleration * dt;
			transform.AddPosition(camera->right*(speed * dt));
			moved = true;
		}

		if(inputs->GetKey(Keycode::UP)){
			Engine.time->frameRate += 1.0f;
		}
		else if(inputs->GetKey(Keycode::DOWN)){
			Engine.time->frameRate -= 1.0f;
		}

		if(inputs->GetKey(Keycode::T))
		{
			cout << "Delta: " << Engine.time->delta << "  " << 1000 / std::fmax(Engine.time->delta, 0.001f) << endl;
		}

		if(inputs->GetKey(Keycode::I)){
			camera->SetOrtho(0.0f, 0.0f, Engine.windowWidth, Engine.windowHeight, 0.001f, 1000.0f);
		}
		if(inputs->GetKey(Keycode::O)){
			camera->SetPerspective(50, Engine.windowWidth, Engine.windowHeight, 0.1f, 1000.0f);
		}


		if(moved || lastPosition != transform.position){
			camera->SetPosition(transform.position);
		}
		else
			speed = 0;

		lastPosition = transform.position;


		//mouseLook

		if(mouseLock){
			if(inputs->mouseMoved){
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