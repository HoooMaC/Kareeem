#include "Core/KRMpch.h"

#include "Renderer2D.h"

#include "Core/Renderer/RendererCommand.h"

#include "OpenGL/Mesh/VertexArray.h"
#include "OpenGL/Mesh/Shader.h"

namespace krm {

	struct Renderer2DData
	{
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<Shader> shader;
	};

	static Renderer2DData s_Data;

	void Renderer2D::beginScene(std::shared_ptr<Shader>& shader, std::shared_ptr<VertexArray>& vertexArray)
	{
		s_Data.shader = shader;
		s_Data.vertexArray = vertexArray;
	}

	void Renderer2D::endScene()
	{
		s_Data.shader->bindAndUploadUniform();
		s_Data.vertexArray->bind();

		RendererCommand::draw(s_Data.vertexArray);
	}

	void Renderer2D::submit()
	{
	}

	void Renderer2D::flush()
	{
	}

}