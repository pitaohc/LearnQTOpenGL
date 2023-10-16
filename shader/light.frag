#version 330 core                            
out vec4 FragColor;
in vec3 ourColor;
in vec2 outTexCord;
uniform vec3 lightColor;
void main()                                  
{                   
	FragColor = vec4(lightColor,1.0f);
} 