#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out VS_OUT {
    vec2 TexCoord;
} vs_out;

layout(std140, binding = 1) uniform CameraData {
    mat4 view;
    mat4 projection;
    mat4 viewPos;
};

uniform mat4 model;

void main() {
    vs_out.TexCoord = aTexCoord;
    gl_Position = model * vec4(aPos, 1.0);
}
