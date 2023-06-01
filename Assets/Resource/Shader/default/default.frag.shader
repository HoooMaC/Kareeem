#version 450 core

out vec4 color;

in vec4 v_color;
in vec2 v_texCoord;
in float v_texIndex;

uniform sampler2D uTexture[32];


void main()
{
	int index = int(v_texIndex);
	//if (index == 0)
		color = v_color;
	//else
	//{
		//color = 
		//color = texture(uTexture[index], v_texCoord);
	//}
}