#version 460 core

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform sampler2D u_Texture;
uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

out vec4 FragColor;

void main()
{
    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * u_LightColor;

    // diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir =  normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor;

    vec3 lightingResult = u_ObjectColor * (ambient + diffuse + specular);
    vec4 texColor = texture(u_Texture, v_TexCoord);

    FragColor = vec4(lightingResult, 1.0) * texColor;
}