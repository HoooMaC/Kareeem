#version 450 core

layout (location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;


out vec2 v_texCoord;
out float v_texIndex;
out vec4 v_color;

uniform vec4 u_Color;
uniform mat4 pv;

uniform float arrray[3];
out float v_arrray[3];

void main()
{
	gl_Position = pv * vec4(position, 1.0);
	v_texCoord = texCoord;
	v_texIndex = texIndex;

	v_color = vec4(0.5 * (sin(position.x) + 1.0), 0.5 * (sin(position.y) + 1.0), 0.5 * (sin(position.z) + 1.0), 1.0);
	v_color = u_Color;

	v_arrray[0] = arrray[0];
	v_arrray[1] = arrray[1];
	v_arrray[2] = arrray[2]; 
}