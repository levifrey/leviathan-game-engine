#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D buffer1;
};
uniform Material material;

void main() {   
    FragColor = texture(material.buffer1, TexCoords);
}
