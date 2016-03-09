#include "ui_canvas.h"
#include "sprite.h"

namespace EngineT
{

    UICanvas::~UICanvas() {}

    void UICanvas::Destroy() {}


    void UICanvas::SetPosition(int x, int y)
    {

    }

    vec2 UICanvas::GetPosition()
    {

        return vec2(0, 0);
    }


    void UICanvas::SetSize(int width, int height)
    {

    }

    vec2 UICanvas::GetSize()
    {
        return vec2(0, 0);
    }

    void UICanvas::SetParent(UIElement* element)
    {

    }

    UIElement* UICanvas::GetParent()
    {
        return nullptr;
    }

    void UICanvas::AddChild(UIElement* element)
    {

    }

    void UICanvas::RemoveChild(UIElement* element)
    {

    }

    void UICanvas::Draw()
    {
        sprite->Draw(0);
        //render all childs with glScissor
    }
}