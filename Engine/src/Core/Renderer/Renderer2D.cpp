#include "Core/KRMpch.h"

#include "Renderer2D.h"

#include "OpenGL/Mesh/VertexArray.h"
#include "OpenGL/Mesh/Shader.h"

namespace krm {

	struct Renderer2DData
	{
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<Shader> shader;
	};


	void Renderer2D::BeginScene()
	{
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::Submit()
	{
	}

	void Renderer2D::Flush()
	{
	}

}