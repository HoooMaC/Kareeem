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

	void Renderer::submit(const std::unique_ptr<Shader>& shader, const std::unique_ptr<VertexArray>& vertexArray)
	{
		shader->bind();
		//shader->bindAndUploadUniform();
		vertexArray->bind();
		glDrawElements(GL_TRIANGLES, vertexArray->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::flush()
	{

	}

}