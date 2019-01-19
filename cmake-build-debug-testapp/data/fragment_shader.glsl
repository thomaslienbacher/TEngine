#version 330

const int c_numLights = 4;
const float c_ambient = 0.6;

in vec2 v_texcoord;
in vec3 v_normal;
in vec3 v_tolight[c_numLights];

uniform sampler2D sampler;
uniform vec3 u_lightcolors[c_numLights];
uniform float u_lightstrengths[c_numLights];

out vec4 o_color;

void main(){
    vec4 diffuse = vec4(0);

    for(int i = 0; i < c_numLights; i++){
        if(u_lightstrengths[i] == 0) continue;
        float dis = length(v_tolight[i]);
        float attenuation = u_lightstrengths[i] + (u_lightstrengths[i] / 100) * dis + (u_lightstrengths[i] / 500) * dis * dis;

        float b = max(dot(v_normal, normalize(v_tolight[i])), 0);
        diffuse += vec4(normalize(u_lightcolors[i]) * b / attenuation, 1);
    }

    diffuse = max(diffuse, c_ambient);
    diffuse.a = 1;
    o_color = diffuse * texture(sampler, v_texcoord);
}
