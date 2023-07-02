#version 450 core

out vec4 color;

in vec4 v_color;
in vec2 v_texCoord;
in float v_texIndex;

int texIndexInt = int(v_texIndex);

uniform sampler2D u_Texture;

void main()
{
	if(texIndexInt == 0)
		color = v_color;
	else
		color = texture(u_Texture, v_texCoord);
}