#pragma once


#include "engine_t.h"

namespace EngineT
{

	class Font
	{
	public:

		int maxHeight = 0;
		Font(Texture* texture, const string& filename);
		~Font();
		void Load(Texture* texture, const string& filename);

		class Char
		{
		public:
			float uvX1, uvY1, uvX2, uvY2, width, height, xoffset, yoffset, xadvance;
			Char::Char(float uvX1, float uvY1, float uvX2, float uvY2, float width, float height, float xoffset, float yoffset, float xadvance)
			{
				this->uvX1 = uvX1;
				this->uvY1 = uvY1;
				this->uvX2 = uvX2;
				this->uvY2 = uvY2;
				this->width = width;
				this->height = height;
				this->xoffset = xoffset;
				this->yoffset = yoffset;
				this->xadvance = xadvance;
			}
		};

		vector<Char*> chars;

		Texture* texture;

	};


}