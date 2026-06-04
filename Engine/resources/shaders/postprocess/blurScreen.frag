#version 460 core
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoord;
} fs_in;

layout (binding = 3) uniform sampler2D bufferTex;
const float off = 1.0 / 200.0; 

void main() { 
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
        color += kernel[i] * vec3(texture(bufferTex, fs_in.TexCoord + offsets[i]));
    }

    FragColor = vec4(color, 1);
    
}
