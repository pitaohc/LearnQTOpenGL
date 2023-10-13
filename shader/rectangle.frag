#version 330 core                            
out vec4 FragColor;
in vec3 objectColor;
in vec3 objectTexCord;
uniform vec3 lightColor;
void main()                                  
{                   
	FragColor = vec4(lightColor * objectColor, 1.0f);
	//0代表全为第一个输入，1代表全为第二个输入
} 