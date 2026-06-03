#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 TexCoords;

layout(std140, binding=1) uniform CameraData {
    mat4 view;
    mat4 projection;
    vec4 viewPos;
};


void main() {
    TexCoords = aPos;
    vec4 pos =  projection * mat4(mat3(view)) * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}
