

#pragma once


#include "engine_t.h" 
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace EngineT
{
    class Transform
    {
    public:
        vec3 position;
        vec3 scaling;
        quat rotation;

        vec3 GetForward() const;
        vec3 GetUp() const;
        vec3 GetRight() const;

        void SetPosition(vec3& position);
        void SetScaling(vec3& scaling);
        void SetRotation(quat& rotation);
        void AddRotation(float angle, vec3& axis);
        void AddPosition(vec3& delta);
        void AddScaling(vec3& delta);
    };

    class TransformRenderable : public Transform
    {
    public:

        mat4 matTranslate;
        mat4 matScale;
        mat4 matRotate;
        mat4 matWorld;

        mat4 GetWorldMatrix();

        void SetPosition(vec3& position);
        void SetScaling(vec3& scaling);
        void SetRotation(quat& rotation);
        void AddRotation(float angle, vec3& axis);
        void AddPosition(vec3& delta);
        void AddScaling(vec3& delta);

        TransformRenderable();

    private:
        const mat4 identity;
        bool matUpdate = false;
    };
}
