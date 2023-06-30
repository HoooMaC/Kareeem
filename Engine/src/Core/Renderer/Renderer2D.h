#pragma once

#include <memory>

#include "OpenGL/Mesh/Shader.h"
#include "OpenGL/Mesh/VertexArray.h"

namespace krm {

	class Renderer2D
	{
	public:
		static void beginScene(std::shared_ptr<Shader>& shader, std::shared_ptr<VertexArray>& va);
		static void endScene();
		static void submit();
		static void flush();
	private:
	};


}