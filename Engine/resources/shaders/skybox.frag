#version 460 core

out vec4 FragColor;
in vec3 TexCoords;

layout (binding = 2) uniform samplerCube cubemap;

void main() {
    FragColor = texture(cubemap, TexCoords);
}
