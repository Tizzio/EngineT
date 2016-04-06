#pragma once

#include "engine_t.h"

namespace EngineT
{
    class Component
    {
    public:
        GameObject* gameObject;

        Component();

        ~Component();

        virtual void Update() = 0;

        virtual string GetType()
        {
            return typeid(Component).name();
        }
    };
}
