#pragma once

#include "engine_t.h"

namespace EngineT {
	class Style
	{
	public:
		int xoffset = 0;
		int yoffset = 0;
		int spacing = 3;
		int spaceWidth = 8;
		int lineHeight = 2;
		vec4 color;

		Font* font;
		Style(Font* font);


	};
}