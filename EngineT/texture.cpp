

#include "texture.h"
#include "lodepng.h" 

namespace EngineT
{
	Texture::Texture(const string& fileName, int mipmaps)
	{
		textureTarget = GL_TEXTURE_2D;
		this->Load(fileName, mipmaps);
	}

	Texture::Texture(GLenum textureTarget)
	{
		this->textureTarget = textureTarget;
	}

	void Texture::SetFilter(TextureFilter filter)
	{

		glBindTexture(textureTarget, textureObj);
		switch(filter){
		case TextureFilter::Point:
			glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case TextureFilter::Bilinear:
			glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case TextureFilter::BilinearMipmap:
			glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		case TextureFilter::PointMipmap:
			glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			break;
		}
		glBindTexture(textureTarget, 0);
	}

	bool Texture::Load(const std::string& fileName, int mipmaps)
	{
		this->fileName = fileName;

		//load and decode
		std::vector<unsigned char> png;
		std::vector<unsigned char> image; //the raw pixels
		unsigned _width, _height;
		lodepng::State state; //optionally customize this one

		lodepng::load_file(png, fileName); //load the image file with given filename
		unsigned error = lodepng::decode(image, _width, _height, state, png);

		//if there's an error, display it
		if(error){
			std::cout << "error loading image " << endl << error << ": " << lodepng_error_text(error) << std::endl;
			return false;
		}
		else{
			cout << "success loading image" << endl;;

			this->width = (float) _width;
			this->height = (float) _height;

			glGenTextures(1, &textureObj);
			glBindTexture(textureTarget, textureObj);

			if(mipmaps > 0)
			{
				glTexStorage2D(textureTarget, mipmaps, GL_RGBA, _width, _height);
				glTexImage2D(textureTarget, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) &image[0]);
				glGenerateMipmap(textureTarget);
				glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else
			{
				glTexImage2D(textureTarget, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) &image[0]);
				glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
		}
		return true;
	}

	void Texture::Bind(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(textureTarget, textureObj);
	}
}