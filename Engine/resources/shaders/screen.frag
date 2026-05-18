#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main() {
    //FragColor = texture(screenTexture, TexCoords);
    FragColor = vec4(vec3(1.0f - texture(screenTexture, TexCoords)), 1.0);
}
