#pragma once  

#include "engine_t.h"  

namespace EngineT
{
	class Rect
	{
	public:

		Rect(float x, float y, float width, float height);

		bool GetPointInside(float x, float y);
		bool GetIntersection(Rect rect);
		vec2 GetSize();
		vec2 GetPosition();

		void SetPosition(float x, float y);
		void SetSize(float width, float height);

	private:
		float x1, y1, x2, y2, width, height;
	};
}