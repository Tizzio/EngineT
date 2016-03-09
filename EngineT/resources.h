#pragma once 

#include "engine_t.h"  

namespace EngineT
{

	class Resources
	{
	public:

		static vector <Texture*> textures;
		static vector <Sprite*> sprites;
		static vector <Mesh*> meshes;
		static vector <Font*> fonts;
		static vector <Style*> styles;
		static vector <Text*> texts;
		static vector <Scene*> scenes;
		static vector <Camera*> cameras;

	};

}