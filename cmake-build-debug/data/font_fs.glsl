#version 330

in vec2 v_texcoord;

uniform sampler2D sampler;

out vec4 o_color;

void main(){
    o_color = texture(sampler, v_texcoord);
    float a = (o_color.x + o_color.y + o_color.z) / 3.0;
    o_color = vec4(o_color.xyz, a);
}
