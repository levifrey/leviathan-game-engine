#version 460 core

in VS_OUT {
    vec3 Normal;
    vec3 Position;
} fs_in;

layout(std140, binding = 1) uniform CameraData {
    mat4 view;
    mat4 projection;
    vec4 viewPos;
};

layout (binding = 2) uniform samplerCube skybox;

out vec4 FragColor;

void main() {
    vec3 I = normalize(fs_in.Position-vec3(viewPos));
    vec3 R = reflect(I, normalize(fs_in.Normal));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}
