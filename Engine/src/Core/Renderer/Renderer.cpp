#include "Core/KRMpch.h"

#include "Renderer.h"

#include "GLEW/glew.h"

namespace krm {

	void Renderer::beginScene()
	{
	}

	void Renderer::endScene()
	{
	}

	void Renderer::draw(const Shader& shader, const VertexArray& vertexArray)
	{
		shader.bindAndUploadUniform();

		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, vertexArray.getCount(), GL_UNSIGNED_INT, nullptr);
	}

}