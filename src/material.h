#pragma once

#include "engine_t.h"

namespace EngineT
{
    class Material
    {
    public:
        Material(Shader* shader, Texture* albedo, Texture* specular = nullptr, Texture* normalmap = nullptr, Texture* emission = nullptr, Texture* occlusion = nullptr);
        void Enable();
        void Update();
        Shader* shader = nullptr;
        Texture* albedo = nullptr;
        Texture* specular = nullptr;
        Texture* normalmap = nullptr;
        Texture* occlusion = nullptr;
        Texture* emission = nullptr;
        Cubemap* cubemap = nullptr;

        float specularIntensity = 1.75f;
        float specularPower = 32.0f; //power of 2 for performance
        bool backfaceCulling = true;
        bool depthTest = true;
        bool blending = false;
        int blendFuncSource = GL_SRC_ALPHA;
        int blendFuncDest = GL_ONE_MINUS_SRC_ALPHA;
    };
}
