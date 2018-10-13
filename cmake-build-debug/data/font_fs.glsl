#version 330

in vec2 v_texcoord;

uniform sampler2D sampler;

out vec4 o_color;

void main(){
    o_color = texture(sampler, v_texcoord);
}
