#version 460 core

out vec4 FragColor;
in vec3 TexCoords;

struct Material {
    samplerCube cubemap;
};
uniform Material material;

void main() {
    //FragColor = vec4(1.0, 0.0, 0.0, 0.0);
    FragColor = texture(material.cubemap, TexCoords);
}
