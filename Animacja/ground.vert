#version 330 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
 
uniform mat3 modelNormal; 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{


    gl_Position = projection * view * model * vec4(position, 1.0f);
    
	//Normal = mat3(model) * normal;
	Normal = modelNormal * normal;

	TexCoord = texCoord;
	FragPos =   vec3(model * vec4(position, 1.0f));
	
} 