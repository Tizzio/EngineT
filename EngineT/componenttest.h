#pragma once

#include "engine_t.h"
#include "component.h"
namespace EngineT
{
    class ComponentTest : public Component
    {
    public:

        GameObject* gameObject;

        ComponentTest()
        {
            cout << GetType() << " constructor" << endl;
        }

        ~ComponentTest()
        {
            cout << GetType() << " destructor" << endl;
        }

        void Update() override
        {
            
        }

        string GetType() override
        {
            return typeid(ComponentTest).name();
        }
    };
}
