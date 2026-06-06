#version 460 core
out vec4 FragColor;
in vec3 localPos;
uniform sampler2D equirectTexture;
const float PI = 3.14159265358979323846;

vec2 dirToEquirectUV(vec3 dir) {
    float theta = atan(dir.z, dir.x);
    float u = theta / (2.0 * PI) + 0.5;
    u = fract(u);
    float phi = asin(dir.y);
    float v = 0.5 -  phi / PI;
    return vec2(u, v);
}

void main() {
    vec3 dir = normalize(localPos);
    vec2 uv = dirToEquirectUV(dir);
    vec3 color = vec3(texture(equirectTexture, uv));
    //FragColor = vec4(0.0, uv.x, uv.y, 1.0);
    FragColor = vec4(color, 1.0);
};
