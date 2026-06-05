#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

layout (std140, binding = 1) uniform CameraData {
    mat4 view;
    mat4 projection;
    vec4 viewPos;
};

uniform mat4 model;

out VS_OUT {
    vec3 normal;
} vs_out;

void main() {
    gl_Position = view * model * vec4(aPos, 1.0);
    mat3 normalMat = mat3(transpose(inverse(view * model)));
    vs_out.normal = normalize(normalMat * aNormal);
};
