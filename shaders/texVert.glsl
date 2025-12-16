#version 460 core

layout (location = 0) in vec3 position; 
layout (location = 1) in vec2 texCoord; 
layout (location = 2) in vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    v_TexCoord = texCoord;
    v_Normal = mat3(transpose(inverse(u_Model))) * normal;
    v_FragPos = vec3(u_Model * vec4(position, 1.0));
}