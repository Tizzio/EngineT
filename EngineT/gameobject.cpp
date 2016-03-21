
#include "gameobject.h"
#include "mesh.h"
#include "sprite.h"
#include "transform.h"
#include "render_manager.h"

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

    void GameObjectRenderable::SetMaterial(Material * mat)
    {
        if(material == mat)
            return;

        material = mat;      
    }

    Material * GameObjectRenderable::GetMaterial()
    {
        return material;
    }

	void GameObject3D::Draw()
	{
        if(mesh == nullptr)
            cout << "ERROR: GameObject3D::Draw()" << endl;
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
        if(sprite == nullptr)
            cout << "ERROR: GameObject2D::Draw()" << endl;

		uint index = (uint) imageIndex;
		sprite->Draw(index);
		imageIndex = fmodf(imageIndex + imageSpeed, (float) sprite->frames.size());
	}
}