#pragma once  

#include "engine_t.h"
#include "ui_element.h"  

namespace EngineT {
	class UICanvas : UIElement
	{
	public:

		UICanvas(Sprite* sprite);
		~UICanvas();
		void Destroy();
		 
		void SetPosition(int x, int y);
		vec2 GetPosition();

		void SetSize(int width, int height);
		vec2 GetSize();

		void SetParent(UIElement* element);
		UIElement* GetParent();

		void AddChild(UIElement* element);
		void RemoveChild(UIElement* element);

	private:
		Sprite* sprite;
		vector<UIElement> childs;
		Rect rect;

		void Draw();
		
	};
}