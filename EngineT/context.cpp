
#include "engine_t.h"
#include "context.h"
#include "inputs.h"

namespace EngineT{
	  
	bool Context::Init(const uint width, const uint height, const bool fullcreen, const string title)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			cout << "Unable to Init SDL" << SDL_GetError() << endl;
			return false;
		}
		 

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); 
		SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1); 
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

		Uint32 flags = SDL_WINDOW_OPENGL;
		if (fullcreen){
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		else{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, flags);
	

		if (window == NULL)
		{
			cout << "Unable to create SDL Window" << SDL_GetError() << endl;
			return false;
		}
		if (fullcreen){
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		}
		glContext = SDL_GL_CreateContext(window);
		SDL_GL_SetSwapInterval(0);

		if (glContext == NULL)
		{
			cout << "There was an error creating the OpenGL context!\n";
			return false;
		}

		SDL_GL_MakeCurrent(window, glContext);

		glewExperimental = GL_TRUE;
		GLenum res = glewInit();
		if (res != GLEW_OK)
		{
			cout << string("Error in glew: ") + ((char*)glewGetErrorString(res)) << endl;
			return false;
		}
		if (!glewIsSupported("GL_VERSION_3_3"))
		{
			cout << "OpenGL 3.3 required!" << endl;
			return false;
		}
		glGetError();
		glGetString(GL_VERSION);
		cout << string("Opengl Version: ") + ((char*)glGetString(GL_VERSION)) << endl;
		//init here

		return true;
	}

	void Context::OnEvent(SDL_Event* Event)
	{
		if (Event->type == SDL_QUIT)  {
			running = false;
		}
	}
	 

	void Context::Cleanup()
	{
		 

		int error = glGetError();
		switch (error)
		{
		case GL_NO_ERROR:						cout << "GL ERROR: GL_NO_ERROR" << endl; break;
		case GL_INVALID_ENUM:					cout << "GL ERROR: GL_INVALID_ENUM" << endl; break;
		case GL_INVALID_VALUE:					cout << "GL ERROR: GL_INVALID_VALUE" << endl; break;
		case GL_INVALID_OPERATION:				cout << "GL ERROR: GL_INVALID_OPERATION" << endl; break;
		case GL_STACK_OVERFLOW:					cout << "GL ERROR: GL_STACK_OVERFLOW" << endl; break;
		case GL_STACK_UNDERFLOW:				cout << "GL ERROR: GL_STACK_UNDERFLOW" << endl; break;
		case GL_OUT_OF_MEMORY:					cout << "GL ERROR: GL_OUT_OF_MEMORY" << endl; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:	cout << "GL ERROR: GL_INVALID_FRAMEBUFFER_OPERATION" << endl; break;
		case GL_TABLE_TOO_LARGE:				cout << "GL ERROR: GL_TABLE_TOO_LARGE" << endl; break;
		}
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);

		SDL_Quit();
	}

	int Context::Run()
	{  
		SDL_Event event;

		while (running)
		{
			
			while (SDL_PollEvent(&event) != 0)
			{
				OnEvent(&event);
				if (event.type == SDL_QUIT) running = false;

				else if (event.type == SDL_KEYDOWN){ 
					if(!event.key.repeat)
						Engine.inputs->_CallbackKeyDown(event.key.keysym.scancode);
				}
				else if (event.type == SDL_KEYUP){ 
					if (!event.key.repeat)
						Engine.inputs->_CallbackKeyUp(event.key.keysym.scancode);
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP){
					Engine.inputs->_CallbackMouse(event.button.button, event.button.state, event.button.x, event.button.y);
				}
				else if (event.type == SDL_MOUSEMOTION){
					Engine.inputs->_CallbackMouseMove(event.button.x, event.button.y);
				} 


				if (event.type == SDL_WINDOWEVENT) {
					switch (event.window.event) {  
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						Engine.inputs->hasFocus = true;
						break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
						Engine.inputs->hasFocus = false;
						break;
					}
				}

			}
			if (Engine.HasError())
				break;
			
			Engine.Update();
			Engine.Render();

			SDL_GL_SwapWindow(window);
			 
		}

		Cleanup();

		getchar();
		return 1;
	}

	void Context::Stop()
	{
		running = false;
	}
}