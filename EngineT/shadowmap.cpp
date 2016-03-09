
#include "shadowmap.h"

namespace EngineT
{
	Shadowmap::Shadowmap()
	{
		fbo = 0;
		shadowMap = 0;
	}



	Shadowmap::~Shadowmap()
	{
		if(fbo != 0) {
			glDeleteFramebuffers(1, &fbo);
		}

		if(shadowMap != 0) {
			glDeleteTextures(1, &shadowMap);
		}
	}



	bool Shadowmap::Init(unsigned int WindowWidth, unsigned int WindowHeight)
	{
		// Create the FBO
		glGenFramebuffers(1, &fbo);

		// Create the depth buffer
		glGenTextures(1, &shadowMap);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

		// Disable writes to the color buffer
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if(Status != GL_FRAMEBUFFER_COMPLETE) {
			cout << "FrameBuffer error, status: 0x" << Status << endl;
			return false;
		}

		return true;
	}


	void Shadowmap::BindForWriting()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	}


	void Shadowmap::BindForReading(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
	}
}