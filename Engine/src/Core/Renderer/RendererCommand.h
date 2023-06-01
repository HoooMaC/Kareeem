#pragma once

#include <glm.hpp>

namespace krm {

	class RendererCommand
	{
	public:
		static void Clear();
		static void setClearColor(const glm::vec4& color);
	};

}