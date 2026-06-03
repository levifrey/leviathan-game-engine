#version 460 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

layout (binding = 0) uniform sampler2D diffuseTex;

void main()
{
    //FragColor = vec4(TexCoord, 0.0, 1.0);
    vec4 texColor = texture(diffuseTex, TexCoord);
    if (texColor.a < 0.1) {
        discard;
    }
    FragColor = texColor;
}

