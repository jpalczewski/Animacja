#version 330 core
in vec3 position;
in vec3 color;
in vec2 texture;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;

uniform mat4 projectionMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * transform * vec4(position, 1.0f);
    ourColor = color;
    TexCoord = texture;
}
