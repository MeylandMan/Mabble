#version 410 core
out vec4 fragColor;

struct Material {
	sampler2D diffuse1;
	sampler2D specular1;
	sampler2D normal1;
	sampler2D height1;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 5
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct SpotLight {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

uniform SpotLight spotLight;

in vec3 FragPos;
in vec3 v_Normal;
in vec2 v_TexCoords;
uniform bool u_NegativeTexCoord;

uniform vec3 u_ViewPosition;

uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec2 texcoords);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 texcoords);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 texcoords);

void main()
{
     /* just using the uniforms so that openGL doesn't PISS ME OF */
    vec4 t_temp = texture(material.diffuse1, v_TexCoords) * texture(material.specular1, v_TexCoords) * texture(material.normal1, v_TexCoords);
	vec2 texcoords = v_TexCoords;

	if(!u_NegativeTexCoord)
        texcoords = v_TexCoords;
    else
       texcoords = vec2(v_TexCoords.x, -v_TexCoords.y);

	// properties
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPosition - FragPos);
	vec3 result = vec3(1.);

	// phase 1: Directional lighting
	result = CalcDirLight(dirLight, norm, viewDir, texcoords);
	// phase 2: Point lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, texcoords);
	// phase 3: Spot lights
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir, texcoords);

	fragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec2 texcoords) {

	vec3 lightDir = normalize(-light.direction);

	// diffuse
	float NDotL = max(dot(normal, lightDir), 0.0);

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// combine
	vec3 ambient = light.ambient * texture(material.diffuse1, texcoords).rgb;
	vec3 diffuse = light.diffuse * NDotL * texture(material.diffuse1, texcoords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular1, texcoords).rgb;
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 texcoords) {

	vec3 lightDir = normalize(light.position - fragPos);

	// diffuse
	float NDotL = max(dot(normal, lightDir), 0.0);

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// attenuation
	float distance = length(light.position - fragPos);
	float att = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// combine
	vec3 ambient = light.ambient * texture(material.diffuse1, texcoords).rgb;
	vec3 diffuse = light.diffuse * NDotL * texture(material.diffuse1, texcoords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular1, texcoords).rgb;

	ambient *= att;
	diffuse *= att;
	specular *= att;
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 texcoords) {
	
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse
	float NdotL = max(dot(normalize(normal), lightDir), 0.0);

	// Specular
	vec3 reflectDir = reflect(-lightDir, normalize(normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// CutOff (Smoother)
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// Attenuation
	float distance = length(light.position - fragPos);
	float att = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// combine
	vec3 ambient =  light.ambient * texture(material.diffuse1, texcoords).rgb;
	vec3 diffuse = light.diffuse * NdotL *  texture(material.diffuse1, texcoords).rgb;
	vec3 specular = light.specular * texture(material.specular1, texcoords).rgb * spec;

	ambient *= att;
	diffuse *= att;
	specular *= att;

	diffuse *= intensity;
	specular *= intensity;
	return (ambient + diffuse + specular);
}