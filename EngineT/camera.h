
#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

namespace EngineT
{
    class Camera
    {
    public:

        enum ProjectionType { Ortho, Perspective };

        vec3 position;
        vec3 target;
        vec3 up;
        vec3 forward;
        vec3 right;

        float yaw;
        float pitch;
        float horizontalAngle;
        float verticalAngle;
        mat4 matProjection;
        mat4 matView;

        Camera(float width, float height);

        Camera(float width, float height, const vec3& position, const vec3& target, const vec3& up);

        //void Rotate(float angle, vec3& axis);
        void MouseLook(float deltaX, float deltaY);

        void SetPerspective(float FOV, float width, float height, float zNear, float zFar);
        void SetOrtho(float x, float y, float width, float height, float zNear, float zFar);

        void SetPosition(vec3& position);
        void AddPosition(vec3& position);


        void LookAt(vec3& target);
        void LookAt(vec3& target, vec3& up);

        mat4 GetViewProjMatrix();
        mat4 GetViewMatrix();
        mat4 GetProjectionMatrix();

        int layer = 0;

    private:
        bool updateMatView;
        bool updateMatProjection;

        ProjectionType projectionType;

        float FOV;
        float orthoX;
        float orthoY;
        float width;
        float height;
        float zNear;
        float zFar;
        float aspect;
    };
}