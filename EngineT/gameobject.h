
#pragma once


#include "engine_t.h"
#include "transform.h"

#include "bullet\btBulletCollisionCommon.h"
#include "bullet\btBulletDynamicsCommon.h"

namespace EngineT{

	class GameObject{ 
		friend class Renderer;
		friend class Scene;
	public:
		Transform transform;
		int layer = 0;
		string name;
		//btCollisionShape* collider;

	protected:
		virtual void Update() = 0;
		//btDefaultMotionState* motionState;
	};


	class GameObject3D : public GameObject{
	public:
		TransformRenderable transform;
		void SetMesh(Mesh* mesh);
		Mesh* GetMesh();
	private:
		Mesh* mesh = NULL;
		void Draw();
	};

	class GameObject2D : public GameObject
	{
		friend class Renderer;
		friend class Scene;
	public:
		float imageIndex;
		float imageSpeed;
		TransformRenderable transform;
		void SetSprite(Sprite* sprite);
		Sprite* GetSprite();
	private:
		Sprite* sprite = NULL;
		void Draw();
	};
}