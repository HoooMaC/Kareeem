#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;

out vec4 v_color;
out vec2 v_texCoord;
out float v_texIndex;

uniform mat4 projectionView;
uniform mat4 model;
// uniform sampler2D u_Texture;

void main()
{
    gl_Position = projectionView * model * vec4(position, 1.0);

    // int texIndexInt = int(texIndex);
	v_texIndex = texIndex;
	v_texCoord = texCoord;
	v_color = color;
}
