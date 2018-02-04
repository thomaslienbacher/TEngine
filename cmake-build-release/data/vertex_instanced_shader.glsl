#version 330

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec2 i_texcoord;
layout(location = 2) in vec3 i_normal;

layout(location = 3) in vec4 i_modelCol1;
layout(location = 4) in vec4 i_modelCol2;
layout(location = 5) in vec4 i_modelCol3;
layout(location = 6) in vec4 i_modelCol4;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_texcoord;

void main() {
    mat4 i_model = mat4(i_modelCol1, i_modelCol2, i_modelCol3, i_modelCol4);
    gl_Position = u_projection * u_view * i_model * vec4(i_vertex, 1);
    float d =  gl_InstanceID * 0.7;
    //gl_Position = u_projection * u_view * vec4(i_vertex.x, i_vertex.y + d, i_vertex.z, 1);
    v_texcoord = i_texcoord;
}