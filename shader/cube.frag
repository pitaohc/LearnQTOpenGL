#version 330 core                            
out vec4 FragColor;
in vec3 objectColor;
in vec3 objectNorm; 
in vec3 FragPos;
in vec2 outTexCord;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;
struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

vec3 getAmbient()
{
	//ambient
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * light.ambient;
	return ambient;
}
vec3 getDiffuse()
{
	//diffuse
	vec3 norm = normalize(objectNorm); //归一化法向
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * light.diffuse;
	return diffuse;
}
vec3 getSpecular()
{
	//specular
	float specularStrength = 0.5;
	vec3 norm = normalize(objectNorm); //归一化法向
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = specularStrength * spec * light.specular;
	return specular;
}
void main()                                  
{
	vec3 ambient, diffuse, specular;
	ambient = vec3(0,0,0);
	diffuse = vec3(0,0,0);
	specular = vec3(0,0,0);
	ambient = getAmbient();
	diffuse = getDiffuse();
	specular = getSpecular();
	vec3 result = ambient  * material.ambient + 
			      diffuse  * material.diffuse +
				  specular * material.specular;
	FragColor = vec4(result ,1.0f);
} 