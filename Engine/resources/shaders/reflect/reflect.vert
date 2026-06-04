#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT {
    vec3 Normal;
    vec3 Position;
} vs_out;

layout(std140, binding = 1) uniform CameraData {
    mat4 view;
    mat4 projection;
    vec4 viewPos;
};

uniform mat4 model;

void main() 
{
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vec3 position = vec3(model * vec4(aPos, 1.0));
    vs_out.Position = position;
    gl_Position = projection * view * vec4(position, 1.0);
}
