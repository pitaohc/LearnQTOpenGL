#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCord;
out vec3 objectColor;
out vec3 objectNorm;//���������µķ��߷���
out vec2 outTexCord;
out vec3 FragPos;//���������µ�Ƭ����ɫ
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
//    objectNorm = vec3(model * vec4(aNorm, 1.0)); //model��scale��pos��Ӱ�취�ߣ���������ֻ��Ҫrotation
    objectNorm = mat3(transpose(inverse(model))) * aNorm;
    //transpose��inverse���Խ�����������ź�λ�õ�Ӱ��
    objectColor = aColor;
    outTexCord = aTexCord;
}