#pragma once  

#include "engine_t.h"  
#include "rect.h"  
#include "transform.h"  

namespace EngineT
{
	class UIElement
	{
	public:
		virtual void Destroy() = 0;

		virtual void SetParent(UIElement* element) = 0;
		virtual UIElement* GetParent() = 0;

	protected:
		virtual void Draw() = 0;
		TransformRenderable transform;

	};
}