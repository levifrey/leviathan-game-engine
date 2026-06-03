#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

layout (binding = 3) uniform sampler2D bufferTex; 

void main() {   
    FragColor = texture(bufferTex, TexCoords);
}
