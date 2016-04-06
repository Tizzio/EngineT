#pragma once



#include "engine_t.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


namespace EngineT
{

    enum class TextureFilter { Point, Bilinear, BilinearMipmap, PointMipmap };

    class Texture
    {
    public:
        Texture(const string& fileName, int mipmaps = 0);
        Texture(GLenum textureTarget = GL_TEXTURE_2D);

        bool Load(const string& fileName, int mipmaps = 3);
        void SetFilter(TextureFilter filter);
        void Bind(GLenum textureUnit);

        float width;
        float height;
    private:
        string fileName;
        GLenum textureTarget;
        GLuint textureObj;
    };
}