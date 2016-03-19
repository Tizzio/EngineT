#version 330

const int MAX_POINT_LIGHTS = 2; 
const int MAX_SPOT_LIGHTS = 2;

in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;

out vec4 FragColor; 

struct DirectionalLight 
{ 
	vec3 color;
	float diffuseIntensity;
	vec3 direction; 
};

struct PointLight 
{ 
	vec3 color;
	float diffuseIntensity; 
	float attenConstant; 
	float attenLinear; 
	float attenExp;
	vec3 position;
};

struct SpotLight
{ 
	vec3 color;
	float diffuseIntensity; 
	float attenConstant; 
	float attenLinear; 
	float attenExp;
	vec3 position;
	vec3 direction; 
	float cutoff; 
};

uniform int gNumPointLights;
uniform int gNumSpotLights; 
uniform DirectionalLight gDirLight;  
uniform PointLight gPointLights[MAX_POINT_LIGHTS];
uniform SpotLight gSpotLights[MAX_SPOT_LIGHTS]; 
uniform sampler2D gSampler; 
uniform vec3 gEyeWorldPos;
uniform float gAmbientIntensity;
uniform float gSpecularIntensity;
uniform float gSpecularPower; 

const int lightingModel = 0; //0 : lambert   1: oren-nayar
vec3 eyeDirection;
vec3 normal;

float Specular(vec3 lightDirection, float power)
{ 
	vec3 reflected = reflect(-lightDirection, normal); 
	return pow( max(dot(reflected, -eyeDirection), 0.0), power);
}

float Lambert(vec3 lightDirection) 
{ 
	return dot(normal, lightDirection);
} 

vec3 CalcDirectionalLight()
{ 
	vec3 lightDirection = normalize(gDirLight.direction);
	return  gDirLight.color * (gDirLight.diffuseIntensity * Lambert(lightDirection) + gSpecularIntensity * Specular(lightDirection, gSpecularPower));
} 

vec3 CalcPointLight(PointLight l)
{ 
	vec3 lightVector = l.position- WorldPos0 ; 
	float distance = length(lightVector);
	vec3 lightDirection = normalize(lightVector); 

	vec3 color = l.color * (l.diffuseIntensity *  Lambert(lightDirection)  + gSpecularIntensity * Specular(lightDirection, gSpecularPower)); 
	float attenuation = l.attenConstant + l.attenLinear * distance +  l.attenExp * distance * distance; 

	return color  / attenuation ; 
}

vec3 CalcSpotLight(SpotLight l)
{
		vec3 lightVector = l.position- WorldPos0 ; 
	float distance = length(lightVector);
	vec3 lightDirection = normalize(lightVector);
	float spotFactor = dot(lightDirection, l.direction);

	if (spotFactor > l.cutoff)
	{
		vec3 color = l.color * (l.diffuseIntensity * Lambert(lightDirection) + gSpecularIntensity * Specular(lightDirection, gSpecularPower)); 
		float attenuation = l.attenConstant + l.attenLinear * distance +  l.attenExp * distance * distance;
		return (color / attenuation) * (1.0 - (1.0 - spotFactor)/(1.0 - l.cutoff)); 
	} 
	
	return vec3(0,0,0); 
} 

void main() 
{ 
	eyeDirection = normalize(WorldPos0 - gEyeWorldPos);
	 
	normal = normalize(Normal0); 
	vec3 totalLight = CalcDirectionalLight(); 
	
	for (int i = 0 ; i < gNumPointLights ; i++)  
		totalLight += CalcPointLight(gPointLights[i]);
	

	for (int i = 0 ; i < gNumSpotLights ; i++)
		totalLight += CalcSpotLight(gSpotLights[i]);
	 
	
	const vec3 gamma = vec3(1.0 / 2.2);
	FragColor.rgb = pow( texture2D(gSampler, TexCoord0.xy).rgb * totalLight, gamma); 
}


