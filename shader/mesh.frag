#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
/* 数据结构声明区 */
struct Material //材质
{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_specular1;
	float shininess;
};
uniform Material material;

void main()
{   
	vec4 tex1 = texture(material.texture_diffuse1, TexCoords);
	vec4 tex2 = texture(material.texture_diffuse2, TexCoords);

    FragColor = mix(tex1,tex2,0.5);
}