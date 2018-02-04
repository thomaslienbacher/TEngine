#version 330

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec2 i_texcoord;
layout(location = 2) in vec3 i_normal;

const int c_numLights = 16;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_lightpositions[c_numLights];

out vec2 v_texcoord;
out vec3 v_normal;
out vec3 v_tolight[c_numLights];

void main() {
    vec4 worldPos = u_model * vec4(i_vertex, 1);

    gl_Position = u_projection * u_view * worldPos;
    v_texcoord = i_texcoord;
    v_normal = normalize((u_model * vec4(i_normal, 0.0)).xyz);

    for(int i = 0; i < c_numLights; i++){
        v_tolight[i] = u_lightpositions[i] - worldPos.xyz;
    }
}