#pragma once

#include <memory>

#include "OpenGL/Mesh/Shader.h"
#include "OpenGL/Mesh/VertexArray.h"

namespace krm {

	class Renderer2D
	{
	public:
		static void init();
		static void beginScene(const glm::mat4& projectionViewMatrix);
		static void endScene();
		static void submit(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float textureIndex);
		static void flush();
	private:
	};


}