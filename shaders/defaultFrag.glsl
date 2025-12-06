#version 460 core

out vec4 FragColor;
in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor * u_Color;
}