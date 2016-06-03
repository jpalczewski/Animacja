#version 330 core
in vec3 position;
in vec3 color;
in vec3 normal;

out vec3 ourColor;
out vec3 Normal;
out vec3 FragPos;

uniform mat3 modelNormal; 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    ourColor = color;
	FragPos = vec3(model * vec4(position, 1.0f));
	Normal = modelNormal * normal;

} 
