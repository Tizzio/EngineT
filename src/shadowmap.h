#pragma once

#include "engine_t.h"

namespace EngineT
{
    class Shadowmap
    {
    public:
        Shadowmap();
        ~Shadowmap();

        bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

        void BindForWriting();

        void BindForReading(GLenum TextureUnit);


    private:
        GLuint fbo;
        GLuint shadowMap;

    };
}
