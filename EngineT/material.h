#pragma once

#include "engine_t.h"

namespace EngineT
{
    class Material
    {
    public:
        Material(Shader* shader, Texture* texture);
        void Enable();
        void Update();
        Shader* shader = nullptr;
        Texture* texture = nullptr;

        bool backfaceCulling;
        bool depthTest = true;
        bool blending = false;
        int blendFuncSource = GL_SRC_ALPHA;
        int blendFuncDest = GL_ONE_MINUS_SRC_ALPHA;
    };
}
