
#include "effect_text.h"
#include "renderer.h"
#include "ui_text.h"
#include "camera.h"
#include "light.h"
#include "transform.h"


namespace EngineT
{

	EffectText::EffectText()
	{

		GLuint prog = CreateProgram("data/shaders/text_default.vs", "data/shaders/text_default.fs", "");

		//uniforms
		gWVP = Loc("gWVP");
		gSampler = Loc("gSampler");

	}

	void EffectText::Enable()
	{
		glUseProgram(shaderProgram);
	}

	void EffectText::UpdateUniforms()
	{
		mat4 worldMatrix = ((Text*) (renderer->curObj))->transform.GetWorldMatrix();
		mat4  WVP = renderer->curCamera->GetViewProjMatrix() * worldMatrix;
		glUniformMatrix4fv(gWVP, 1, GL_FALSE, &WVP[0][0]); //set WVP 
		glUniform1i(gSampler, 0); //set texture unit 
	}
}