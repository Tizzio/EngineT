

#include "cubemap.h"
#include "lodepng.h" 

namespace EngineT
{

    Cubemap::Cubemap(const string right, const string left, const string top, const string bottom, const string front, const string back)
    {
        Load(vector<string> {right, left, top, bottom, front, back});
    }

    void Cubemap::Load(vector<string> fileNames)
    {
        glGenTextures(1, &textureID);

        bool error = false;
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        //load and decode
        std::vector<unsigned char> png;
        std::vector<unsigned char> image; // raw pixels

        for(GLuint i = 0; i < fileNames.size(); i++)
        {
            unsigned _width, _height;
            lodepng::State state; // optionally customize this one

            lodepng::load_file(png, fileNames[i]); // load the image file with given filename
            unsigned errorCode = lodepng::decode(image, _width, _height, state, png);

            if(errorCode)
            {
                std::cout << "error loading image " << std::endl
                    << fileNames[i] << std::endl
                    << errorCode << ": " << lodepng_error_text(errorCode) << std::endl;
                error = true;
                break;
            }
            else
            {
                cout << "success loading image " << fileNames[i] << std::endl;
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) &image[0]);
            }
            png.clear();
            image.clear();
        }

        if(!error)
        {
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
   

    void Cubemap::Bind()
    {
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    }
     
}