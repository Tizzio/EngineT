
#include "effect_light.h"
#include "renderer.h"
#include "gameobject.h"
#include "camera.h"
#include "light.h"
#include "transform.h"

namespace EngineT
{
#define PI glm::atan(1.0f) * 4.0f
#define toRad PI/180.0f
#define toDeg 180.0f/PI


    LightEffect::LightEffect()
    {

        GLuint prog = CreateProgram("data/shaders/light_diffuse_specular.vs", "data/shaders/light_diffuse_specular.fs", "");


        //uniforms
        gWVP = Loc("gWVP");
        gWorld = Loc("gWorld");
        gSampler = Loc("gSampler");
        gEyeWorldPos = Loc("gEyeWorldPos");
        gSpecularIntensity = Loc("gSpecularIntensity");
        gSpecularPower = Loc("gSpecularPower");


        gNumPointLights = Loc("gNumPointLights");;
        gNumSpotLights = Loc("gNumSpotLights");;
        gAmbientIntensity = Loc("gAmbientIntensity");;


        //directional light uniforms
        gDirLight light;
        light.color = Loc("gDirLight.color");
        light.diffuseIntensity = Loc("gDirLight.diffuseIntensity");
        light.direction = Loc("gDirLight.direction");
        gDirLights.push_back(light);

        //point light uniforms
        for(int i = 0; i < MAX_POINT_LIGHTS; i++){

            gPointLight light;
            string name = "gPointLights[" + to_string(i) + "].";
            light.color = Loc(name + "color");
            light.diffuseIntensity = Loc(name + "diffuseIntensity");
            light.attenConstant = Loc(name + "attenConstant");
            light.attenLinear = Loc(name + "attenLinear");
            light.attenExp = Loc(name + "attenExp");
            light.position = Loc(name + "position");

            gPointLights.push_back(light);
        }

        //spot light uniforms
        for(int i = 0; i < MAX_POINT_LIGHTS; i++){

            gSpotLight light;
            string name = "gSpotLights[" + to_string(i) + "].";
            light.color = Loc(name + "color");
            light.diffuseIntensity = Loc(name + "diffuseIntensity");
            light.attenConstant = Loc(name + "attenConstant");
            light.attenLinear = Loc(name + "attenLinear");
            light.attenExp = Loc(name + "attenExp");
            light.position = Loc(name + "position");

            light.direction = Loc(name + "direction");
            light.cutoff = Loc(name + "cutoff");

            gSpotLights.push_back(light);
        }

    }


    void LightEffect::Enable()
    {

        glUseProgram(shaderProgram);
        int pointLightCount = 0;
        int spotLightCount = 0;
        for(auto light : renderer->lights){
            if(light->type == LightType::Directional)
            {

                glUniform3f(gDirLights[0].color, light->color.x, light->color.y, light->color.z);
                vec3 direction = light->transform.GetForward();
                glUniform3f(gDirLights[0].direction, direction.x, direction.y, direction.z);
                glUniform1f(gDirLights[0].diffuseIntensity, light->diffuseIntensity);
            }
            else if(light->type == LightType::Point)
            {

                int i = pointLightCount;

                glUniform3f(gPointLights[i].color, light->color.x, light->color.y, light->color.z);
                glUniform1f(gPointLights[i].diffuseIntensity, light->diffuseIntensity);
                glUniform1f(gPointLights[i].attenConstant, light->attenuationConstant);
                glUniform1f(gPointLights[i].attenLinear, light->attenuationLinear);
                glUniform1f(gPointLights[i].attenExp, light->attenuationExp);
                glUniform3f(gPointLights[i].position, light->transform.position.x, light->transform.position.y, light->transform.position.z);

                pointLightCount++;
            }
            else if(light->type == LightType::Spot)
            {

                int i = spotLightCount;

                glUniform3f(gSpotLights[i].color, light->color.x, light->color.y, light->color.z);
                glUniform1f(gSpotLights[i].diffuseIntensity, light->diffuseIntensity);
                glUniform1f(gSpotLights[i].attenConstant, light->attenuationConstant);
                glUniform1f(gSpotLights[i].attenLinear, light->attenuationLinear);
                glUniform1f(gSpotLights[i].attenExp, light->attenuationExp);
                glUniform3f(gSpotLights[i].position, light->transform.position.x, light->transform.position.y, light->transform.position.z);

                vec3 direction = light->transform.GetForward();
                glUniform3f(gSpotLights[i].direction, direction.x, direction.y, direction.z);
                glUniform1f(gSpotLights[i].cutoff, cosf(light->cutoff) * toRad);
                spotLightCount++;
            }

        }

        glUniform1i(gNumPointLights, pointLightCount);
        glUniform1i(gNumSpotLights, spotLightCount);

        glUniform1f(gAmbientIntensity, 1.0f);

    }



    void LightEffect::UpdateUniforms()
    {

        mat4 worldMatrix = ((GameObject3D*) (renderer->curObj))->transform.GetWorldMatrix();//translate(mat4(), transform.position);
        mat4  WVP = renderer->curCamera->GetViewProjMatrix() * worldMatrix;

        glUniformMatrix4fv(gWVP, 1, GL_FALSE, &WVP[0][0]); //set WVP

        glUniformMatrix4fv(gWorld, 1, GL_FALSE, &worldMatrix[0][0]); //set world matrix


        glUniform1i(gSampler, 0); //set texture unit 
        vec3 eye = renderer->curCamera->position;
        glUniform3f(gEyeWorldPos, eye.x, eye.y, eye.z);
        glUniform1f(gSpecularIntensity, 3.0f);
        glUniform1f(gSpecularPower, 8.0f);

    }
}
