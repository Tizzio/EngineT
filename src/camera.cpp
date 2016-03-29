
#include "engine_t.h"
#include <stdio.h>
#include "camera.h"
 

namespace EngineT
{
    Camera::Camera(float width, float height, const vec3 position, const vec3 target, const vec3 up)
    {
        this->width = width;
        this->height = height;
        this->position = position;
        this->up = normalize(up);
        forward = vec3(0.0f, 0.0f, 1.0f);
        right = vec3(1.0f, 0.0f, 0.0f);
        this->target = target;
        horizontalAngle = 0.0f;
        verticalAngle = 0.0f;
        yaw = 0.0f;
        pitch = 0.0f;
        SetPerspective(toRad*60.0f, (float) width, (float) height, 0.1f, 1000);
        matView = lookAt(position, target, up);
    }

    Camera::Camera(float width, float height)
    {
        this->width = width;
        this->height = height;
        this->position = vec3(0.0f, 0.0f, 5.0f);
        this->up = vec3(0.0f, 1.0f, 0.0f);
        this->target = vec3(0.0f, 0.0f, 1.0f);
        forward = vec3(0.0f, 0.0f, 1.0f);
        right = vec3(1.0f, 0.0f, 0.0f);
        horizontalAngle = 0.0f;
        verticalAngle = 0.0f;
        yaw = 0.0f;
        pitch = 0.0f;

        SetPerspective(toRad*60.0f, (float) width, (float) height, 0.1f, 1000);
        matView = lookAt(position, target, up);
    }
    /*
    void GetForward()
    {
    cos(yaw*toRad)*cos(pitch*toRad) * 4
    sin(pitch*pi / 180) * 4
    sin(yaw*toRad)*cos(pitch*toRad) * 4
    }*/

    void Camera::MouseLook(float deltaX, float deltaY)
    {

        //method 1

        yaw += deltaX;
        while(yaw < 0){ yaw += 360.0f; }
        pitch -= deltaY;
        while(pitch < 0){ pitch += 360.0f; }

        forward = vec3(
            cos(yaw*toRad)*cos(pitch*toRad),
            sin(pitch*toRad),
            sin(yaw*toRad)*cos(pitch*toRad)
            );

        up = normalize(vec3(0.0f, cos(pitch*toRad), 0.0f));

        right = normalize(cross(forward, up));

        //method 2
        /*
        horizontalAngle -= deltaX * toRad;
        if (horizontalAngle < 0.0f) horizontalAngle = 3.1416f;

        verticalAngle += deltaY * toRad;
        if (verticalAngle > 3.1415f) verticalAngle = 0.0f;

        forward = vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
        );

        // Right vector
        right = vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
        );

        // Up vector : perpendicular to both direction and right
        up = cross(right, forward);
        */

        target = position + forward;

        updateMatView = true;
    }

    void Camera::LookAt(vec3 target)
    {
        this->target = target;
        updateMatView = true;
    }
    void Camera::LookAt(vec3 target, vec3 up)
    {
        this->target = target;
        this->up = up;
        updateMatView = true;
    }

    void Camera::SetPerspective(float FOV, float width, float height, float zNear, float zFar)
    {
        this->FOV = FOV;
        this->width = width;
        this->height = height;
        this->aspect = width / height;
        this->zNear = zNear;
        this->zFar = zFar;
        this->projectionType = ProjectionType::Perspective;
        updateMatProjection = true;
    }

    void Camera::SetOrtho(float x, float y, float width, float height, float zNear, float zFar)
    {
        this->width = width;
        this->height = height;
        this->zNear = zNear;
        this->zFar = zFar;
        this->orthoX = x;
        this->orthoY = y;
        this->projectionType = ProjectionType::Ortho;
        updateMatProjection = true;
    }

    mat4 Camera::GetViewMatrix()
    {
        if(updateMatView){
            matView = lookAt(position, target, up);
            updateMatView = false;
        }
        return matView;
    }

    mat4 Camera::GetProjectionMatrix()
    {
        if(updateMatProjection){

            if(projectionType == ProjectionType::Perspective)
                matProjection = perspective(FOV, aspect, zNear, zFar);
            else
                matProjection = ortho(orthoX, orthoX + width, orthoY + height, orthoY, zNear, zFar);

            updateMatProjection = false;
        }
        return matProjection;
    }

    mat4 Camera::GetViewProjMatrix()
    {
        if(updateMatView){
            matView = lookAt(position, target, up);
            updateMatView = false;
        }

        if(updateMatProjection){
            if(projectionType == ProjectionType::Perspective)
                matProjection = perspective(FOV, aspect, zNear, zFar);
            else
                matProjection = ortho(orthoX, orthoX + width, orthoY + height, orthoY, zNear, zFar);

            updateMatProjection = false;
        }
        return  matProjection * matView;

    }

    void Camera::SetPosition(vec3 position)
    {
        this->position = position;
        updateMatView = true;
    }
    void Camera::AddPosition(vec3 delta)
    {
        position += delta;
        updateMatView = true;
    }


    /*
    bool Camera::OnKeyboard(int Key)
    {
    bool Ret = false;

    switch (Key) {

    case GLUT_KEY_UP:
    {
    position += (target * STEP_SCALE);
    Ret = true;
    }
    break;

    case GLUT_KEY_DOWN:
    {
    position -= (target * STEP_SCALE);
    Ret = true;
    }
    break;

    case GLUT_KEY_LEFT:
    {
    vec3 Left = cross(target,up);
    Left = normalize(Left);
    Left *= STEP_SCALE;
    position += Left;
    Ret = true;
    }
    break;

    case GLUT_KEY_RIGHT:
    {
    vec3 Right = cross(up,target);

    Right = normalize(Right);
    Right *= STEP_SCALE;
    position += Right;
    Ret = true;
    }
    break;
    }

    return Ret;
    }



    void Camera::OnMouse(int x, int y)
    {
    const int DeltaX = x - mousePos.x;
    const int DeltaY = y - mousePos.y;

    mousePos.x = x;
    mousePos.y = y;

    angleH += (float)DeltaX / 20.0f;
    angleV += (float)DeltaY / 20.0f;

    if (DeltaX == 0) {
    if (x <= MARGIN) {
    //    angleH -= 1.0f;
    OnLeftEdge = true;
    }
    else if (x >= (windowWidth - MARGIN)) {
    //    angleH += 1.0f;
    OnRightEdge = true;
    }
    }
    else {
    OnLeftEdge = false;
    OnRightEdge = false;
    }

    if (DeltaY == 0) {
    if (y <= MARGIN) {
    OnUpperEdge = true;
    }
    else if (y >= (windowHeight - MARGIN)) {
    OnLowerEdge = true;
    }
    }
    else {
    OnUpperEdge = false;
    OnLowerEdge = false;
    }

    Update();
    }



    replace with Camera::LookAt(position)
    void Camera::Render()
    {
    const vec3 vAxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    vec3 view(1.0f, 0.0f, 0.0f);
    view = normalize(rotateY(view, angleH));

    // Rotate the view vector by the vertical angle around the horizontal axis
    vec3 hAxis = normalize(cross(vAxis, view));

    View = rotate(view, angleV, haxis);

    target = normalize(view);

    up = normalize( cross(target, Haxis) );
    }
    */
}
