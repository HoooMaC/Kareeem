#version 450 core

out vec4 color;

in vec4 v_color;
in vec2 v_texCoord;
in float v_texIndex;

void main()
{
	color = v_color;
}