#version 330 core

in vec2 vs_TexCoord;
in vec3 vs_Normal;
in vec3 vs_WorldPos;

uniform sampler2D u_Texture;
uniform vec3 u_ViewPos;    

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light u_Light;

struct Material {
    vec3 color;
    float shininess;
};
uniform Material u_Material;


out vec4 FragColor;

void main()
{
    vec3 norm = normalize(vs_Normal);
    vec3 lightDir = normalize(u_Light.position - vs_WorldPos);
    vec3 viewDir = normalize(u_ViewPos - vs_WorldPos);
    vec4 texColor = texture(u_Texture, vs_TexCoord);
    vec3 ambient = u_Light.ambient * u_Material.color;
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.diffuse * diff * u_Material.color;
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 specular = u_Light.specular * spec; 

    vec3 lightingResult = ambient + diffuse + specular;
    FragColor = texColor * vec4(lightingResult, 1.0);
}