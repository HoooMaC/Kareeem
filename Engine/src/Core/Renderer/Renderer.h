#pragma once

#include "OpenGL/Mesh/Shader.h"
#include "OpenGL/Mesh/VertexArray.h"

namespace krm {

	class Renderer
	{
	public:
		static void beginScene();
		static void endScene();
		static void submit(const std::unique_ptr<Shader>& shader, const std::unique_ptr<VertexArray>& vertexArray);
		static void flush();
	private:
		struct SceneData
		{

		};
		static SceneData m_Data;
	};

}
