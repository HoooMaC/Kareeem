#include "Core/KRMpch.h"

#include "Renderer2D.h"

#include "Core/Renderer/RendererCommand.h"

#include "OpenGL/Mesh/Buffer.h"
#include "OpenGL/Mesh/VertexArray.h"
#include "OpenGL/Mesh/Shader.h"

namespace krm {

	struct Renderer2DData
	{
		const unsigned int maxData = 1000;
		const unsigned int maxVertex = maxData * 4;
		const unsigned int maxIndex = maxData * 6;

		std::shared_ptr<Shader> shader;

		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;

		std::vector<Vertex> vertexData;
		std::vector<unsigned int> indexData;
	};

	static Renderer2DData s_Data;
	static unsigned int quadCount = 0;

	void Renderer2D::init()
	{
		s_Data.shader = std::make_shared<Shader>("Resource/Shader/default/default.vert.shader", "Resource/Shader/default/default.frag.shader");

		s_Data.vertexArray = std::make_shared<VertexArray>();
		s_Data.vertexBuffer = std::make_shared<VertexBuffer>();
		s_Data.indexBuffer = std::make_shared<IndexBuffer>();

		s_Data.vertexArray->setVertexArray();
	}
	
	//TO DO check the performance of this function
	void Renderer2D::beginScene(const glm::mat4& projectionViewMatrix)
	{
		quadCount = 0;

		//TO DO maybe this should be change
		glm::mat4 model(1.0f);

		s_Data.shader->setUniformData("projectionView", glm::value_ptr(projectionViewMatrix));
		s_Data.shader->setUniformData("model", glm::value_ptr(model));

		s_Data.vertexData.reserve(s_Data.maxVertex);
		s_Data.indexData.reserve(s_Data.maxIndex);
	}

	void Renderer2D::endScene()
	{
		s_Data.shader->bindAndUploadUniform();
		s_Data.vertexArray->bind();

		RendererCommand::draw(s_Data.indexData.size());

		s_Data.vertexData.clear();
		s_Data.indexData.clear();
	}

	//maybe something like this
	//void Renderer2D::submit(glm::vec3 pos, glm::vec4 color, Texture texture, float rotation = 0)
	void Renderer2D::submit(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float textureIndex)
	{
		Vertex vertices[] = {
			{ { position.x,			 position.y,			0.0f },	{ color }, { 0.0f, 0.0f }, 1.0f },
			{ { position.x + size.x, position.y,			0.0f },	{ color }, { 1.0f, 0.0f }, 1.0f },
			{ { position.x + size.x, position.y + size.y,	0.0f },	{ color }, { 1.0f, 1.0f }, 1.0f },
			{ { position.x,			 position.y + size.y,	0.0f },	{ color }, { 0.0f, 1.0f }, 1.0f }
		};

		s_Data.vertexData.insert(s_Data.vertexData.end(), vertices, vertices + 4);

		//TO DO
		//what is the value of offset
		unsigned int offset = quadCount * 4;
		unsigned int indices[] =
		{
			offset,
			offset + 1,
			offset + 2,
			offset + 2,
			offset + 3,
			offset
		};

		s_Data.indexData.insert(s_Data.indexData.end(), indices, indices + 6);

		quadCount++;

		s_Data.vertexBuffer->bind();
		s_Data.vertexBuffer->setData(s_Data.vertexData);

		s_Data.indexBuffer->bind();
		s_Data.indexBuffer->setData(s_Data.indexData);
	}

	//TO DO make the overload function for submit
	// void Renderer2D::submit(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float textureIndex)
	// { 
	// 
	// }

	//TO DO to limit the batch renderer and flush if the renderer is full
	void Renderer2D::flush()
	{
	}

}