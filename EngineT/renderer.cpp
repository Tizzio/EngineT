
#include "renderer.h"
#include "effect_light.h"
#include "effect_sprite.h"
#include "effect_text.h"
#include "gameobject.h"
#include "scene.h"
#include "camera.h"
#include "mesh.h"
#include "sprite.h"
#include "ui_text.h"

namespace EngineT
{
	void Renderer::Render(Scene* scene)
	{

		if(scene == nullptr) return;
		if(scene->cameras.size() == 0) return;

		effect = Engine.lightEffect;
		effect->Enable();

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glDisable(GL_BLEND);

		//render all 3D objects
		for(auto cam : scene->cameras){

			curCamera = cam;
			vec3 pos = cam->position;

			//get all object of the camera layer 
			//TODO: add more layers to one camera
			int layer = cam->layer;
			for(auto go : scene->obj3DLayers[layer]){
				curObj = go;
				effect->UpdateUniforms();

				Mesh* mesh = go->GetMesh();
				if(mesh != NULL){
					mesh->Draw();
				}
			}
		}

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		/*
		effect = Engine.effectSprite;
		effect->Enable();

		//render all 2D objects
		for (auto cam : scene->cameras){

			curCamera = cam;
			vec3 pos = cam->position;

			//get all object of the camera layer
			//TODO: add more layers to one camera
			int layer = cam->layer;
			for (auto go : scene->obj2DLayers[layer]){
				curObj = go;
				effect->UpdateUniforms();

				go->Draw();

			}
		}

		//Render 2D Text
		effect = Engine.effectText;
		effect->Enable();

		for (auto cam : scene->cameras)
		{

			curCamera = cam;
			vec3 pos = cam->position;

			//get all object of the camera layer
			//TODO: add more layers to one camera
			int layer = cam->layer;
			for (auto go : scene->textLayers[layer])
			{
				curObj = go;
				effect->UpdateUniforms();

				go->Draw();

			}
		}

		 */


	}
}