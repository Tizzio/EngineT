#pragma once

#include "engine_t.h"

namespace EngineT
{
    class Material
    {
    public:
        Material(Shader* shader, Texture* texture, Texture* normalmap = nullptr);
        void Enable();
        void Update();
        Shader* shader = nullptr;
        Texture* texture = nullptr;
        Texture* normalmap = nullptr;

        bool backfaceCulling = true;
        bool depthTest = true;
        bool blending = false;
        int blendFuncSource = GL_SRC_ALPHA;
        int blendFuncDest = GL_ONE_MINUS_SRC_ALPHA;
    };
}
