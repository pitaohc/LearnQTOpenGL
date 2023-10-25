#version 330 core
/* 输入输出声明区 */
out vec4 FragColor;
in vec3 objectNorm; 
in vec3 FragPos;
in vec2 TexCord;
/* END 输入输出声明区 */

/* 数据结构声明区 */
struct Material //材质
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct SpotLight //聚光灯
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

struct ParallelLight //平行光
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight //点光源
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
};
/* END 数据结构声明区 */

/* 函数声明区*/

/* 聚光灯区 */
vec3 getSpotAmbient(SpotLight light);
vec3 getSpotDiffuse(SpotLight light,vec3 normal,vec3 lightDir);
vec3 getSpotSpecular(SpotLight light,vec3 normal,vec3 viewPos);
vec3 getSpotLight(SpotLight light,vec3 normal,vec3 viewDir);
/* END 聚光灯区 */

/* 平行光区 */
vec3 getParallelAmbient(ParallelLight light);
vec3 getParallelDiffuse(ParallelLight light,vec3 normal);
vec3 getParallelSpecular(ParallelLight light,vec3 normal,vec3 viewDir);
vec3 getParallelLight(ParallelLight light,vec3 normal,vec3 viewDir);
/* END 平行光区 */

/* 点光源区 */
float getPointAttenuation(PointLight light);
vec3 getPointAmbient(PointLight light);
vec3 getPointDiffuse(PointLight light,vec3 normal);
vec3 getPointSpecular(PointLight light,vec3 normal,vec3 viewDir);
vec3 getPointLight(PointLight light,vec3 normal,vec3 viewDir);
/* END 点光源区 */
/* END 函数声明区*/

/* uniform变量声明区 */
uniform vec3 viewPos;
uniform Material material;
uniform SpotLight spotlight0;
uniform ParallelLight parallellight0;
uniform PointLight pointlight0;
/* END uniform变量声明区 */

void main()
{
	vec3 norm = normalize(objectNorm);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 spotLightResult = getSpotLight(spotlight0,norm,viewDir); //聚光灯光照
	vec3 parallelLightResult = getParallelLight(parallellight0,norm,viewDir); //平行光光照
	vec3 pointLightResult = getPointLight(pointlight0,norm,viewDir); //点光源光照
	FragColor = vec4((spotLightResult + parallelLightResult + pointLightResult)/3,1.0f);
}

/*
* 计算聚光灯环境光
*/
vec3 getSpotAmbient(SpotLight light)
{
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * light.ambient;
	return ambient * vec3(texture(material.diffuse,TexCord));
}

/*
* 计算聚光灯漫反射
*/
vec3 getSpotDiffuse(SpotLight light,vec3 normal,vec3 lightDir)
{
	vec3 norm = normalize(normal); //归一化法向
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * light.diffuse;
	return diffuse * vec3(texture(material.diffuse,TexCord));
}

/*
* 计算聚光灯镜面反射
*/
vec3 getSpotSpecular(SpotLight light,vec3 normal,vec3 viewDir,vec3 lightDir)
{
	float specularStrength = 0.5;
	vec3 norm = normalize(normal); //归一化法向
	vec3 reflectDir = reflect(lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = specularStrength * spec * light.specular;
	return specular * vec3(texture(material.specular,TexCord)); //为了体现平行光而修改的
}

/*
* 计算聚光灯衰减
*/
float getSpotAttenuation(SpotLight light,vec3 lightDir)
{
	float theta = dot(-lightDir,normalize(light.direction));
	float epsilon = light.cutoff - light.outCutoff;
	float intensity = clamp((theta - light.outCutoff) / epsilon,0.0,1.0); //平滑过渡
	return intensity;
}

/*
* 计算聚光灯光照
*/
vec3 getSpotLight(SpotLight light,vec3 normal,vec3 viewDir){
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 ambient, diffuse, specular;
	ambient = getSpotAmbient(light); //环境光
	diffuse = getSpotDiffuse(light,normal,lightDir); //漫反射
	specular = getSpotSpecular(light,normal,viewDir,lightDir); //镜面反射
	vec3 result = ambient + getSpotAttenuation(light,lightDir) * (diffuse + specular);
	return result;
}

/*
* 计算平行光环境光
*/
vec3 getParallelAmbient(ParallelLight light)
{
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * light.ambient;
	return ambient * vec3(texture(material.diffuse,TexCord));
}

/*
* 计算平行光漫反射
*/
vec3 getParallelDiffuse(ParallelLight light,vec3 normal)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal,lightDir),0.0);
	vec3 diffuse = diff * light.diffuse;
	return diffuse * vec3(texture(material.diffuse,TexCord));
}

/*
* 计算平行光镜面反射
*/
vec3 getParallelSpecular(ParallelLight light,vec3 normal,vec3 viewDir)
{
	float specularStrength = 0.5;
	vec3 lightDir = normalize(-light.direction); //TODO 去除负号
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = specularStrength * spec * light.specular;
	return specular * vec3(texture(material.specular,TexCord)); //为了体现平行光而修改的
}

/*
* 计算平行光光照
*/
vec3 getParallelLight(ParallelLight light,vec3 normal,vec3 viewDir)
{
	vec3 ambient, diffuse, specular;
	ambient = getParallelAmbient(light); //环境光
	diffuse = getParallelDiffuse(light,normal); //漫反射
	specular = getParallelSpecular(light,normal,viewDir); //镜面反射
	vec3 result = ambient + diffuse + specular;
	return result;
}

/*
* 计算点光源衰减
*/
float getPointAttenuation(PointLight light)
{
	float dist = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	return attenuation;
}

/*
* 计算点光源环境光
*/
vec3 getPointAmbient(PointLight light)
{
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * light.ambient;
	return ambient * vec3(texture(material.diffuse,TexCord));
}

/*
* 计算点光源漫反射
*/
vec3 getPointDiffuse(PointLight light,vec3 normal)
{	
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(normal,lightDir),0.0);
	vec3 diffuse = diff * light.diffuse;
	return diffuse * vec3(texture(material.diffuse,TexCord));
}

/*
* 计算点光源镜面反射
*/
vec3 getPointSpecular(PointLight light,vec3 normal,vec3 viewDir)
{
	float specularStrength = 0.5;
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = specularStrength * spec * light.specular;
	return specular * vec3(texture(material.specular,TexCord));
}

/*
* 计算点光源光照
*/
vec3 getPointLight(PointLight light,vec3 normal,vec3 viewDir)
{
	vec3 ambient, diffuse, specular;
	ambient = getPointAmbient(light);
	diffuse = getPointDiffuse(light,normal);
	specular = getPointSpecular(light,normal,viewDir);
	vec3 result = ambient + getPointAttenuation(light) * (diffuse + specular);
	return result;
}