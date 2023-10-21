#version 330 core                            
out vec4 FragColor;
in vec3 objectNorm; 
in vec3 FragPos;
in vec2 TexCord;
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
struct Spotlight
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float cutoff;
	float outCutoff;
	float constant;
	float linear;
	float quadratic;
};
uniform vec3 viewPos;
uniform Material material;
uniform Spotlight light;
float getAttenuation()
{
	float dist = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	return attenuation;
}
/*
* 计算环境光
*/
vec3 getAmbient()
{
	//ambient
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * light.ambient;
	return ambient * vec3(texture(material.diffuse,TexCord));
}
/*
* 计算漫反射
*/
vec3 getDiffuse()
{
	//diffuse
	vec3 norm = normalize(objectNorm); //归一化法向
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * light.diffuse;
	return diffuse * vec3(texture(material.diffuse,TexCord));
}
/*
* 计算镜面反射
*/
vec3 getSpecular()
{
	//specular
	float specularStrength = 0.5;
	vec3 norm = normalize(objectNorm); //归一化法向
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = specularStrength * spec * light.specular;
	return specular * vec3(texture(material.specular,TexCord)); //为了体现平行光而修改的
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

	vec3 lightDir = normalize(FragPos - light.position);
	float theta = dot(lightDir,normalize(light.direction));
	float epsilon = light.cutoff - light.outCutoff;
	float intensity = clamp((theta - light.outCutoff) / epsilon,0.0,1.0); //平滑过渡
	vec3 result = ambient;
	result += (diffuse + specular) * intensity;
	result *= getAttenuation();
	FragColor = vec4(result ,1.0f);

} 