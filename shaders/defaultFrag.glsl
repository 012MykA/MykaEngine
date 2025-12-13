#version 460 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material u_Material;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform sampler2D u_Texture;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

out vec4 FragColor;

void main()
{
    // ambient
    vec3 ambient = u_LightColor * u_Material.ambient;

    // diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_LightColor * (diff * u_Material.diffuse);

    // specular
    vec3 viewDir =  normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 specular = u_LightColor * (spec * u_Material.specular);

    vec3 lightingResult = ambient + diffuse + specular;
    vec4 texColor = texture(u_Texture, v_TexCoord);

    FragColor = vec4(lightingResult, 1.0);
}