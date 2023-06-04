#version 450 core

out vec4 color;

in vec4 v_color;
in vec2 v_texCoord;
in float v_texIndex;

in float v_arrray[3];

void main()
{
	color = vec4(v_color.x, v_color.y, v_arrray[0], v_arrray[1]);
}