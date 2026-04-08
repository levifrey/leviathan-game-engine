#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform mat4 model;
uniform vec3 viewPos;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float lightAngle = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * lightAngle * vec3(texture(material.diffuse, TexCoord));

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float light_above_face = max(dot(lightDir, norm), 0.0);
    reflectDir = normalize(light_above_face * reflectDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}

