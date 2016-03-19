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

vec4 CalcLightInternal(vec3 lightColor, float lightIntensity, vec3 lightDirection, vec3 normal) 
{ 
	
	vec4 final_color = vec4(lightColor, 1.0f) * gAmbientIntensity; 
							
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDirection);
	
	float lambertTerm = dot(N,L);
	
	//if(lambertTerm > 0.0)
	//{
		final_color += vec4(lightColor, 1.0f)  * lambertTerm;	
		/*
		vec3 vertexToEye = normalize(gEyeWorldPos - WorldPos0); 
		vec3 E = normalize(vertexToEye);
		vec3 R = reflect(-L, N);
		
		
		float asd_FrontMaterial_shininess = 1.0;
		float asd_LightSource_specular = 1.0;
		
		float specular = pow( max(dot(R, E), 0.0), asd_FrontMaterial_shininess );
		final_color += asd_LightSource_specular * specular;	
		*/
		return final_color;
	//}
	/*
	vec4 ambientColor = vec4(lightColor, 1.0f) * gAmbientIntensity; 
	float diffuseFactor = dot(normal, -lightDirection); 

	vec4 diffuseColor = vec4(0, 0, 0, 0);
	vec4 specularColor = vec4(0, 0, 0, 0);

	if (diffuseFactor > 0) {
		diffuseColor = vec4(lightColor, 1.0f) * lightIntensity * diffuseFactor;
	}
	
	vec3 vertexToEye = normalize(gEyeWorldPos - WorldPos0); 
	vec3 lightReflect = normalize(reflect(lightDirection, normal)); 
	float specularFactor = dot(vertexToEye, lightReflect);
	specularFactor = pow(specularFactor, gSpecularPower); 
	if (specularFactor > 0) { 
		specularColor = vec4(lightColor, 1.0f) * 
		gSpecularIntensity * specularFactor; 
	} 
	return (ambientColor + diffuseColor + specularColor); 
	*/
} 

vec4 CalcDirectionalLight(vec3 normal)
{ 
	return CalcLightInternal(gDirLight.color, gDirLight.diffuseIntensity, gDirLight.direction, normal);
} 

vec4 CalcPointLight(PointLight l, vec3 normal)
{ 
	vec3 lightDirection = WorldPos0 - l.position; 
	float distance = length(lightDirection);
	lightDirection = normalize(lightDirection); 

	vec4 color = CalcLightInternal(l.color, l.diffuseIntensity, lightDirection, normal); 
	float attenuation = l.attenConstant + 
	 l.attenLinear * distance +
	 l.attenExp * distance * distance; 

	return color / attenuation; 
} 

vec4 CalcSpotLight(SpotLight l, vec3 normal)
{ 
	
	vec3 lightDirection = WorldPos0 - l.position; 
	float distance = length(lightDirection);
	lightDirection = normalize(lightDirection);  
	float spotFactor = dot(lightDirection, l.direction);

	if (spotFactor > l.cutoff) {
		vec4 color = CalcLightInternal(l.color, l.diffuseIntensity, lightDirection, normal); 
		float attenuation = l.attenConstant + 
		  l.attenLinear * distance +
		  l.attenExp * distance * distance; 
 
		return (color / attenuation) * (1.0 - (1.0 - spotFactor) * 1.0/(1.0 - l.cutoff)); 
	} 
	else {
		return vec4(0,0,0,0); 
	} 
} 

void main() 
{ 
	vec3 normal = normalize(Normal0); 
	vec4 totalLight = CalcDirectionalLight(normal); 
	
	for (int i = 0 ; i < gNumPointLights ; i++) { 
		totalLight += CalcPointLight(gPointLights[i], normal);
	} 

	for (int i = 0 ; i < gNumSpotLights ; i++) {
		totalLight += CalcSpotLight(gSpotLights[i], normal);
	} 
	
	//vec3 gamma = vec3(1.0 / 2.2);
	FragColor = /*texture2D(gSampler, TexCoord0.xy) **/ totalLight; 
    //FragColor.rgb = pow(FragColor.rgb, gamma);
}
