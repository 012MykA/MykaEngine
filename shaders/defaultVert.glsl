#version 330 core

layout (location = 0) in vec3 a_Position; 
layout (location = 1) in vec2 a_TexCoord; 
layout (location = 2) in vec3 a_Normal; 

uniform mat4 u_MVP;            
uniform mat4 u_Model;      
uniform mat4 u_NormalMatrix;

out vec2 vs_TexCoord;
out vec3 vs_Normal;
out vec3 vs_WorldPos;

void main()
{
    gl_Position = u_MVP * vec4(a_Position, 1.0);

    vs_WorldPos = vec3(u_Model * vec4(a_Position, 1.0));
    vs_Normal = vec3(u_NormalMatrix * vec4(a_Normal, 0.0));
    vs_TexCoord = a_TexCoord;
}