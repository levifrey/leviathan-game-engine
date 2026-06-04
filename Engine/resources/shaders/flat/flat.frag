#version 460 core

in VS_OUT {
    vec2 TexCoord;
} fs_in;

out vec4 FragColor;

layout (binding = 0) uniform sampler2D diffuseTex;

void main()
{
    vec4 texColor = texture(diffuseTex, fs_in.TexCoord);
    if (texColor.a < 0.1) {
        discard;
    }
    FragColor = texColor;
}

