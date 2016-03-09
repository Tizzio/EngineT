#include "rect.h"

namespace EngineT {

	Rect::Rect(float x, float y, float width, float height)
	{
		this->x1 = x;
		this->y1 = y;
		this->x2 = x + width;
		this->y2 = y + height;
		this->width = width;
		this->height = height;
	}

	bool Rect::GetPointInside(float x, float y)
	{
		return (x >= x1 && y >= y1 && x <= x2 && y <= y2);
	}

	bool Rect::GetIntersection(Rect rect)
	{
		return !(x2 <= rect.x1 || rect.x2 <= x1 || y2 <= rect.y1 || rect.y2 <= y1);
	}

	void Rect::SetPosition(float x, float y)
	{
		this->x1 = x;
		this->y1 = y;
		this->x2 = x + width;
		this->y2 = y + height;
	}

	void Rect::SetSize(float width, float height)
	{
		this->width = width;
		this->height = width;
		this->x2 = x1 + width;
		this->y2 = y1 + height;
	}

}