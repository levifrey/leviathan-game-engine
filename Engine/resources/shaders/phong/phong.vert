#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out VS_OUT {
    vec2 TexCoord;
    vec3 Normal;
    vec3 FragPos;
} vs_out;

layout(std140, binding = 1) uniform CameraData {
    mat4 view;
    mat4 projection;
    vec4 viewPos;
};

uniform mat4 model;


void main() 
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.TexCoord = aTexCoord;
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
