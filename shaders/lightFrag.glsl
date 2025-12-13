#version 460 core

// in vec2 v_TexCoord;

// uniform sampler2D u_Texture;
uniform vec3 u_LightColor;

out vec4 FragColor;

void main()
{
    // vec4 texColor = texture(u_Texture, v_TexCoord);

    FragColor = vec4(u_LightColor, 1.0)/* * texColor*/;
}