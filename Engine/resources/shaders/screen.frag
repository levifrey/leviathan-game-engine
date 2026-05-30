#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D buffer1;
};
uniform Material material;
const float off = 1.0 / 200.0; 

void main() {
    
    FragColor = texture(material.buffer1, TexCoords);
    
    vec2 offsets[9] = vec2[](
        vec2(-off, off),
        vec2(0.0, off),
        vec2(off, off),
        vec2(-off, 0.0),
        vec2(0.0, 0.0),
        vec2(off, 0.0),
        vec2(-off, -off),
        vec2(0.0, -off),
        vec2(off, -off)

    );

    float kernel[9] = float[](
         1.0 / 16, 2.0 / 16, 1.0 / 16,
         2.0 / 16, 4.0 / 16, 2.0 / 16,
         1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    vec3 color = vec3(0.0);
    for (int i = 0; i < 9; i++) {
        color += kernel[i] * vec3(texture(material.buffer1, TexCoords + offsets[i]));
    }

    FragColor = vec4(color, 1);
    
}
