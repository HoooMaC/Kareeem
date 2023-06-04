#pragma once

#include "glm.hpp"

#define BIT(x) (1 << x)

#define ASSERT(x) if(!(x)) __debugbreak();

#define OFFSETOF(type, member) (size_t) &(((type*)0)->member)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef _DEBUG
	#define MAIN main()
#else
	#define MAIN WinMain( HINSTANCE	hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int ShowCmd)
#endif

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
	float texIndex;

	bool operator==(const Vertex& other) const {
		return position == other.position && color == other.color && texCoord == other.texCoord && texIndex == other.texIndex;
	}
};