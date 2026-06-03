#version 460 core
#define AREA 0
#define POINT 1
#define DIRECTIONAL 2
#define SPOT 3

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

struct Material {
    float shininess;
};

layout (binding = 0) uniform sampler2D diffuseTex;
layout (binding = 1) uniform sampler2D specularTex;

struct LightData {
    vec4 position_type; // (x,y,z,type)
    vec4 ambient; // (r,g,b)
    vec4 diffuse; // (r,g,b)
    vec4 specular; // (r,g,b)
    vec4 direction; // (x,y,z)
    vec4 attenuation; // (const, lin, quad)
    vec4 spotlight; // (innerCutOff, outerCutOff)
};

#define MAX_LIGHTS 128
layout(std140, binding = 0) uniform LightBlock {
    LightData lights[MAX_LIGHTS];
    vec4 lightCount;
};

uniform Material material;
uniform mat4 model;
uniform vec3 viewPos;

vec3 CalcDirLight(LightData light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(-vec3(light.direction));

    // diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(diffuseTex, TexCoord));
    vec3 specular = vec3(light.specular) * spec * vec3(texture(specularTex, TexCoord));
    return (diffuse + specular);
}

vec3 CalcPointLight(LightData light, vec3 norm, vec3 viewDir) {
    float dist = length(vec3(light.position_type) - FragPos);
    float attenuation = 1.0 / (light.attenuation[0] + dist * light.attenuation[1] + dist * dist * light.attenuation[2]);
    vec3 lightDir = normalize(vec3(light.position_type) - FragPos);
    float lightAngle = max(dot(norm, lightDir), 0.0);

    // diffuse shading
    vec3 diffuse = vec3(light.diffuse) * lightAngle * vec3(texture(diffuseTex, TexCoord));

    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float light_above_face = max(dot(lightDir, norm), 0.0);
    reflectDir = normalize(light_above_face * reflectDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(light.specular) * spec * vec3(texture(specularTex, TexCoord));
    return attenuation * (specular + diffuse);
}

vec3 CalcAreaLight(LightData light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(light.position_type.xyz - FragPos);
    float lightAngle = max(dot(norm, lightDir), 0.0);

    // diffuse shading
    vec3 diffuse = vec3(light.diffuse) * lightAngle * vec3(texture(diffuseTex, TexCoord));

    // specular shading
    vec3 specTex = texture(specularTex, TexCoord).rgb;
    float specMask = max(max(specTex.r, specTex.g), specTex.b);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(light.specular) * spec * specTex * specMask;
    /*
    vec3 reflectDir = reflect(-lightDir, norm);
    float light_above_face = max(dot(lightDir, norm), 0.0);
    reflectDir = normalize(light_above_face * reflectDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(light.specular) * spec * vec3(texture(specularTex, TexCoord));
    */
    return specular + diffuse;
}

vec3 CalcSpotLight(LightData light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(vec3(light.position_type) - FragPos);
    float theta = dot(normalize(lightDir), normalize(-vec3(light.direction)));
    float innerOuterDiff = light.spotlight[0] - light.spotlight[1];
    float intensity = clamp((theta - light.spotlight[1]) / innerOuterDiff, 0.0f, 1.0f);
    
    // diffuse shading
    float lightAngle = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(light.diffuse) * lightAngle * vec3(texture(diffuseTex, TexCoord));

    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float light_above_face = max(dot(lightDir, norm), 0.0);
    reflectDir = normalize(light_above_face * reflectDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(light.specular) * spec * vec3(texture(specularTex, TexCoord));

    return intensity * (diffuse + specular);
}


void main()
{
    vec4 texColor = texture(diffuseTex, TexCoord);
    if (texColor.a < 0.1) {
        discard;
    }
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < lightCount[0]; i++) {
        if (lights[i].position_type[3] == AREA) {
            result += CalcAreaLight(lights[i], norm, viewDir);
        } else if (lights[i].position_type[3] == POINT) {
            result += CalcPointLight(lights[i], norm, viewDir);
        } else if (lights[i].position_type[3] == DIRECTIONAL) {
            result += CalcDirLight(lights[i], norm, viewDir);
        } else if  (lights[i].position_type[3] == SPOT) {
            result += CalcSpotLight(lights[i], norm, viewDir);
        }
    }
    FragColor = vec4(result, 1.0);
}
