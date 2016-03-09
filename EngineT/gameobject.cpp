
#include "gameobject.h"
#include "mesh.h"
#include "sprite.h"

#include "transform.h"

namespace EngineT
{
	void GameObject3D::SetMesh(Mesh* mesh)
	{
		this->mesh = mesh;
	}

	Mesh* GameObject3D::GetMesh()
	{
		return mesh;
	}

	void GameObject3D::Draw()
	{
		mesh->Draw();
	}

	void GameObject2D::SetSprite(Sprite* sprite)
	{
		this->sprite = sprite;
	}

	Sprite* GameObject2D::GetSprite()
	{
		return sprite;
	}

	void GameObject2D::Draw()
	{
		uint index = (uint) imageIndex;
		sprite->Draw(index);
		imageIndex = fmodf(imageIndex + imageSpeed, (float) sprite->frames.size());
	}
}