#pragma once

#include "root_declar.h"

namespace EngineT
{

	class Context
	{
		friend class Inputs;
	private:


		SDL_Window* window = NULL;
		SDL_GLContext glContext = NULL;

		bool running = true;

		void OnEvent(SDL_Event* Event);
		void Cleanup();

	public:
		bool Init(const uint width, const uint height, const bool fullcreen, const string title);
		int Run();
		void Stop();

	};
}
