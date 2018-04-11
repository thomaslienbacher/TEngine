#version 330

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec2 i_texcoord;
layout(location = 2) in vec3 i_normal;

//only used when instancing
layout(location = 3) in vec4 i_modelCol1;
layout(location = 4) in vec4 i_modelCol2;
layout(location = 5) in vec4 i_modelCol3;
layout(location = 6) in vec4 i_modelCol4;

const int c_numLights = 4;

uniform float u_instanced = 0;
uniform mat4 u_model;
uniform mat4 u_projview;
uniform vec3 u_lightpositions[c_numLights];

out vec2 v_texcoord;
out vec3 v_normal;
out vec3 v_tolight[c_numLights];

void main() {
    vec4 worldPos;

    //is instanced
    if(u_instanced > 0.5){
        mat4 i_model = mat4(i_modelCol1, i_modelCol2, i_modelCol3, i_modelCol4);
        worldPos = i_model * vec4(i_vertex, 1);
        v_normal = normalize((i_model * vec4(i_normal, 0.0)).xyz);
    }
    //not instanced
    else {
        worldPos = u_model * vec4(i_vertex, 1);
        v_normal = normalize((u_model * vec4(i_normal, 0.0)).xyz);
    }

    gl_Position = u_projview * worldPos;
    v_texcoord = i_texcoord;


    for(int i = 0; i < c_numLights; i++){
        v_tolight[i] = u_lightpositions[i] - worldPos.xyz;
    }
}