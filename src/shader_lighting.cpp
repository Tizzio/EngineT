
#include "shader_lighting.h"
#include "render_manager.h"
#include "gameobject.h"
#include "camera.h"
#include "light.h"
#include "transform.h"

namespace EngineT
{
#define PI glm::atan(1.0f) * 4.0f
#define toRad PI/180.0f
#define toDeg 180.0f/PI

    ShaderLighting::ShaderLighting() 
    {
        renderManager = Engine.renderManager;
    }

    void ShaderLighting::LoadUniforms()
    {

        uWVP = Loc("uWVP");
        uWorld = Loc("uWorld");
        //uniforms
        
        if(hasSpecular) 
            uEyeWorldPos = Loc("uEyeWorldPos"); 

        uNumPointLights = Loc("uNumPointLights");
        uNumSpotLights = Loc("uNumSpotLights");
        uAmbientIntensity = Loc("uAmbientIntensity");

        if(hasSpecular)
        {
            uSpecularIntensity = Loc("uSpecularIntensity");
            uSpecularPower = Loc("uSpecularPower");
        }

        //directional light uniforms
        DirLight light;
        light.color = Loc("uDirLight.color");
        light.diffuseIntensity = Loc("uDirLight.diffuseIntensity");
        light.direction = Loc("uDirLight.direction");
        uDirLights.push_back(light);

        //point light uniforms
        for(int i = 0; i < MAX_POINT_LIGHTS; i++){

            PointLight light;
            string name = "uPointLights[" + to_string(i) + "].";
            light.color = Loc(name + "color");
            light.diffuseIntensity = Loc(name + "diffuseIntensity");
            light.attenConstant = Loc(name + "attenConstant");
            light.attenLinear = Loc(name + "attenLinear");
            light.attenExp = Loc(name + "attenExp");
            light.position = Loc(name + "position");

            uPointLights.push_back(light);
        }

        //spot light uniforms
        for(int i = 0; i < MAX_POINT_LIGHTS; i++){

            SpotLight light;
            string name = "uSpotLights[" + to_string(i) + "].";
            light.color = Loc(name + "color");
            light.diffuseIntensity = Loc(name + "diffuseIntensity");
            light.attenConstant = Loc(name + "attenConstant");
            light.attenLinear = Loc(name + "attenLinear");
            light.attenExp = Loc(name + "attenExp");
            light.position = Loc(name + "position");

            light.direction = Loc(name + "direction");
            light.cutoff = Loc(name + "cutoff");

            uSpotLights.push_back(light);
        }
         
    }

    void ShaderLighting::Enable()
    {
        renderManager = Engine.renderManager;
        glUseProgram(shaderProgram);
        int pointLightCount = 0;
        int spotLightCount = 0;
        for(auto light : renderManager->lights)
        {
            if(light->type == LightType::Directional)
            {
                glUniform3f(uDirLights[0].color, light->color.x, light->color.y, light->color.z);
                vec3 direction = light->transform.GetForward();
                glUniform3f(uDirLights[0].direction, direction.x, direction.y, direction.z);
                glUniform1f(uDirLights[0].diffuseIntensity, light->diffuseIntensity);
            }
            else if(light->type == LightType::Point)
            {

                int i = pointLightCount;

                glUniform3f(uPointLights[i].color, light->color.x, light->color.y, light->color.z);
                glUniform1f(uPointLights[i].diffuseIntensity, light->diffuseIntensity);
                glUniform1f(uPointLights[i].attenConstant, light->attenuationConstant);
                glUniform1f(uPointLights[i].attenLinear, light->attenuationLinear);
                glUniform1f(uPointLights[i].attenExp, light->attenuationExp);
                glUniform3f(uPointLights[i].position, light->transform.position.x, light->transform.position.y, light->transform.position.z);

                pointLightCount++;
            }
            else if(light->type == LightType::Spot)
            {

                int i = spotLightCount;

                glUniform3f(uSpotLights[i].color, light->color.x, light->color.y, light->color.z);
                glUniform1f(uSpotLights[i].diffuseIntensity, light->diffuseIntensity);
                glUniform1f(uSpotLights[i].attenConstant, light->attenuationConstant);
                glUniform1f(uSpotLights[i].attenLinear, light->attenuationLinear);
                glUniform1f(uSpotLights[i].attenExp, light->attenuationExp);
                glUniform3f(uSpotLights[i].position, light->transform.position.x, light->transform.position.y, light->transform.position.z);

                vec3 direction = light->transform.GetForward();
                glUniform3f(uSpotLights[i].direction, direction.x, direction.y, direction.z);
                glUniform1f(uSpotLights[i].cutoff, cosf(light->cutoff) * toRad);
                spotLightCount++;
            }

        }

        glUniform1i(uNumPointLights, pointLightCount);
        glUniform1i(uNumSpotLights, spotLightCount);

        glUniform1f(uAmbientIntensity, 0.01f);

        if(hasSpecular)
        { 
            glUniform1f(uSpecularIntensity, 0.75f);
            glUniform1f(uSpecularPower, 16.0f);
        }
    }

    void ShaderLighting::UpdateUniforms()
    {
        mat4 worldMatrix = ((GameObject3D*) (renderManager->curObj))->transform.GetWorldMatrix();
        mat4 WVP = renderManager->curCamera->GetViewProjMatrix() * worldMatrix;

        glUniformMatrix4fv(uWVP, 1, GL_FALSE, &WVP[0][0]);

        glUniformMatrix4fv(uWorld, 1, GL_FALSE, &worldMatrix[0][0]);

        glUniform1i(GetUniformLoc("uSampler"), 0); //texture unit 0

        if(hasNnormalmap)
            glUniform1i(GetUniformLoc("uNormalMap"), 1); //texture unit 1

        vec3 eye = renderManager->curCamera->position;
        glUniform3f(uEyeWorldPos, eye.x, eye.y, eye.z);
    }
}
