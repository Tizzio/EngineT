
#include "inputs.h"

namespace EngineT
{
    Inputs::Inputs()
    {

        for(int i = 0; i < 512; i++){
            key[i] = false;
            keyPress[i] = false;
            keyRelease[i] = false;
        }
    }

    void Inputs::SetMouse(int x, int y)
    {
        mousePrevX = x;
        mousePrevY = y;
        mouseX = x;
        mouseY = y;
        mouseDeltaX = 0;
        mouseDeltaY = 0;

        if(hasFocus)
            SDL_WarpMouseInWindow(Engine.context.window, x, y);
    }

    void Inputs::_CallbackMouseMove(int x, int y)
    {
        mouseMoved = true;


        mouseDeltaX = x - mouseX;
        mouseDeltaY = y - mouseY;


        mousePrevX = mouseX;
        mousePrevY = mouseY;
        mouseX = x;
        mouseY = y;
    }


    void Inputs::_CallbackMouse(int button, int state, int x, int y)
    {
        switch(button){
        case SDL_BUTTON_LEFT:
            if(state == SDL_PRESSED){
                mouseLeft = true;
                mouseLeftPress = true;
            }
            else{
                mouseLeft = false;
                mouseLeftRel = true;
            }
            break;
        case SDL_BUTTON_MIDDLE:
            if(state == SDL_PRESSED){
                mouseMiddle = true;
                mouseMiddlePress = true;
            }
            else{
                mouseMiddle = false;
                mouseMiddleRel = true;
            }
            break;
        case SDL_BUTTON_RIGHT:
            if(state == SDL_PRESSED){
                mouseRight = true;
                mouseRightPress = true;
            }
            else{
                mouseRight = false;
                mouseRightRel = true;
            }
            break;
        }
    }

    void Inputs::_CallbackKeyDown(int keycode)
    {
        key[keycode] = true;
        keyPress[keycode] = true;

        //cout << keycode << "Down" << endl;
    }


    void Inputs::_CallbackKeyUp(int keycode)
    {
        key[keycode] = false;
        keyRelease[keycode] = true;
        //cout << keycode << "Up" << endl;
    }




    void Inputs::Clear()
    {

        mouseDeltaX = 0;
        mouseDeltaY = 0;

        mouseLeftPress = false;
        mouseLeftRel = false;

        mouseMiddlePress = false;
        mouseMiddleRel = false;

        mouseRightPress = false;
        mouseRightRel = false;
        mouseMoved = false;

        for(int i = 0; i < 512; i++){
            keyPress[i] = false;
            keyRelease[i] = false;
        }
    }


    bool Inputs::GetMouse(int button)
    {
        switch(button){
        case SDL_BUTTON_LEFT:
            return mouseLeft;
            break;
        case SDL_BUTTON_MIDDLE:
            return mouseMiddle;
            break;
        case SDL_BUTTON_RIGHT:
            return mouseRight;
            break;
        }
        return false;
    }

    bool Inputs::GetMousePress(int button)
    {
        switch(button){
        case SDL_BUTTON_LEFT:
            return mouseLeftPress;
            break;
        case SDL_BUTTON_MIDDLE:
            return mouseMiddlePress;
            break;
        case SDL_BUTTON_RIGHT:
            return mouseRightPress;
            break;
        }
        return false;
    }

    bool Inputs::GetMouseRelease(int button)
    {
        switch(button){
        case SDL_BUTTON_LEFT:
            return mouseLeftRel;
            break;
        case SDL_BUTTON_MIDDLE:
            return mouseMiddleRel;
            break;
        case SDL_BUTTON_RIGHT:
            return mouseRightRel;
            break;
        }
        return false;
    }


    bool Inputs::GetKey(int keycode)
    {
        return key[keycode] == true;
    }

    bool Inputs::GetKeyPress(int keycode)
    {
        return keyPress[keycode] == true;
    }
    bool Inputs::GetKeyRelease(int keycode)
    {
        return keyRelease[keycode] == true;
    }
}