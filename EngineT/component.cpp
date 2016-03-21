#pragma once

#include "component.h"

namespace EngineT
{
    Component::Component()
    {
        cout << GetType() << " constructor" << endl;
    }

    Component::~Component()
    {
        cout << GetType() << " destructor" << endl; 
    }
     
}