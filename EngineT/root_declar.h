
#pragma once 
#define GLEW_STATIC

#include <GL/glew.h>
#include <sdl/SDL.h> 
#include <glm/glm.hpp>

#include <iostream>
#include <vector> 
#include <unordered_map>
#include <ctime>
#include <stdio.h>
#include <string>
#include <sstream>
#include <thread>
#include <fstream> 
#include <memory> 


using namespace glm; 

//common used from std
using std::vector;
using std::unordered_map;
using std::pair;
using std::wstring; 
using std::string; 
using std::cout;
using std::cin;
using std::stringstream;
using std::to_string;
using std::fstream;
using std::ifstream;
using std::endl;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;

namespace EngineT
{


	class EngineT;
	class EngineSetup;

	//core
	class Renderer;
	class TextRenderer;
	class Scene;
	class Transform;
	class TransformRenderable;
	class GameObject;
	class GameObject2D;
	class GameObject3D;
	class Camera;
	class Inputs;
	class TimeManager;
	class MeshGenerator;

	//Resources
	class Mesh;
	class Vertex;
	class Texture;
	class Sprite;
	class Font;
	class Text;
	class Style;


	//Physics 
	class Physics;
	class Rigidbody;
	class Rect;

	//UI
	class UIManager;
	//UI Interface classes
	class UIElement;
	//UI Elements
	class UIWindow;



	//graphics
	class ShaderManager;
	class Light;
	class Effect;
	class Renderable;

	//effects
	class LightEffect;
	class EffectSprite;
	class EffectText;

}
