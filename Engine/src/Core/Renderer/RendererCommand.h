#pragma once

#include "OpenGL/Mesh/VertexArray.h"

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
		static void draw(std::shared_ptr<VertexArray>& va);
	};

}