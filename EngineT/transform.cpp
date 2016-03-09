
#include "transform.h"
 
#include <iostream>


namespace EngineT
{

	vec3 Transform::GetForward() const
	{
		return vec3(2.0f * (rotation.x * rotation.z + rotation.w * rotation.y),
			2.0f * (rotation.y * rotation.x - rotation.w * rotation.x),
			1.0f - 2.0f * (rotation.x * rotation.x + rotation.y * rotation.y));
	};

	vec3 Transform::GetUp() const
	{
		return vec3(2.0f * (rotation.x * rotation.y - rotation.w * rotation.z),
			1.0f - 2.0f * (rotation.x * rotation.x + rotation.z * rotation.z),
			2.0f * (rotation.y * rotation.z + rotation.w * rotation.x));
	};

	vec3 Transform::GetRight() const
	{
		return vec3(1.0f - 2.0f * (rotation.y * rotation.y + rotation.z * rotation.z),
			2.0f * (rotation.x * rotation.y + rotation.w * rotation.z),
			2.0f * (rotation.x * rotation.z - rotation.w * rotation.y));
	};


	void Transform::SetPosition(vec3& position)
	{
		this->position = position;
	}


	void Transform::AddPosition(vec3& delta)
	{
		position += delta;
	}


	void Transform::SetScaling(vec3& scaling)
	{
		this->scaling = scaling;
	}

	void Transform::AddScaling(vec3& delta)
	{
		scaling += delta;
	}

	void Transform::SetRotation(quat& rotation)
	{
		this->rotation = rotation;
	}

	void Transform::AddRotation(float angle, vec3& axis)
	{
		rotation = rotate(rotation, angle, axis);
	}


	///////////////////////////////////////////////
	// TRANSFORM RENDERABLE (with matrices)
	///////////////////////////////////////////////

	TransformRenderable::TransformRenderable()
	{
		matTranslate = translate(identity, position);
		matRotate = toMat4(rotation);
		matScale = scale(identity, vec3(1.0f, 1.0f, 1.0f));

	}


	mat4 TransformRenderable::GetWorldMatrix()
	{
		if(matUpdate){
			matWorld = matTranslate * matRotate * matScale;
			matUpdate = false;
		}
		return matWorld;
	}


	void TransformRenderable::SetPosition(vec3& position)
	{
		this->position = position;
		matTranslate = translate(identity, position);
		matUpdate = true;
	}


	void TransformRenderable::AddPosition(vec3& delta)
	{
		position += delta;
		matTranslate = translate(identity, position);
		matUpdate = true;
	}

	void TransformRenderable::SetScaling(vec3& scaling)
	{
		this->scaling = scaling;
		matScale = scale(identity, scaling);
		matUpdate = true;
	}
	void TransformRenderable::AddScaling(vec3& delta)
	{
		scaling += delta;
		matScale = scale(identity, scaling);
		matUpdate = true;
	}

	void TransformRenderable::SetRotation(quat& rotation)
	{
		this->rotation = rotation;
		matRotate = toMat4(rotation);
		matUpdate = true;
	}

	void TransformRenderable::AddRotation(float angle, vec3& axis)
	{
		rotation = rotate(rotation, angle, axis);
		matRotate = toMat4(rotation);
		matUpdate = true;
	}
}