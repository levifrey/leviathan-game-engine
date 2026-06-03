#version 460 core
uniform vec3 viewPos;
in vec3 Position;
in vec3 Normal;

layout (binding = 2) uniform samplerCube skybox;

out vec4 FragColor;


void main() {
    vec3 I = normalize(Position-viewPos);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}
