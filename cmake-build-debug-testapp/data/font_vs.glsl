#version 330

layout(location = 0) in vec2 i_vertex;
layout(location = 1) in vec2 i_texcoord;

uniform mat4 u_transform;

out vec2 v_texcoord;

void main() {
    gl_Position = u_transform * vec4(i_vertex, 0, 1);
    v_texcoord = i_texcoord;
}
