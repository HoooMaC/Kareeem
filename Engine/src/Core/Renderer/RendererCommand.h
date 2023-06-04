#pragma once

#include <glm.hpp>

typedef unsigned int GLenum;

namespace krm {

	class RendererCommand
	{
	public:
		static void Clear();
		static void setClearColor(const glm::vec4& color);
		static void enableBlend();
		static void enableDepth();
	};

}