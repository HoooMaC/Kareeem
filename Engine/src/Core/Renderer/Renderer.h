#pragma once

#include "OpenGL/Mesh/Shader.h"
#include "OpenGL/Mesh/VertexArray.h"

namespace krm {

	class Renderer
	{
	public:
		static void beginScene();
		static void endScene();
		static void draw(const Shader& shader, const VertexArray& vertexArray);
	private:
		struct SceneData
		{

		};
		static SceneData m_Data;
	};

}
