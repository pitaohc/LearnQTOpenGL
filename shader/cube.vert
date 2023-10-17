#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCord;
out vec3 objectColor;
out vec3 objectNorm;//世界坐标下的法线方向
out vec2 outTexCord;
out vec3 FragPos;//世界坐标下的片段颜色
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
//    objectNorm = vec3(model * vec4(aNorm, 1.0)); //model的scale和pos会影响法线，但是我们只需要rotation
    objectNorm = mat3(transpose(inverse(model))) * aNorm;
    //transpose和inverse可以解决不均匀缩放和位置的影响
    objectColor = aColor;
    outTexCord = aTexCord;
}