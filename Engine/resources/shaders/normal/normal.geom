#version 460 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.4;

layout(std140, binding = 1) uniform  CameraData {
    mat4 view;
    mat4 projection;
    vec4 viewPos;
};

void generateLine(int index) {
    gl_Position = projection * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position + vec4(gs_in[index].normal * MAGNITUDE, 0.0));
    EmitVertex();
    EndPrimitive();
}

void main() {
    generateLine(0);
    generateLine(1);
    generateLine(2);
}
