#version 460 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

struct Material {
    sampler2D diffuse1;
};

uniform Material material;

void main()
{
    //FragColor = vec4(TexCoord, 0.0, 1.0);
    vec4 texColor = texture(material.diffuse1, TexCoord);
    if (texColor.a < 0.1) {
        discard;
    }
    FragColor = texture(material.diffuse1,TexCoord);
}

