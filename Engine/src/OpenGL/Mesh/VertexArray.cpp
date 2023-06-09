#include "Core/KRMpch.h"
#include "VertexArray.h"

#include "Core/Log.h"

#include "OpenGL/Mesh/MeshLog.h"

#include <GLEW/glew.h>


namespace krm {

	/// ////////////////////////////////////////////////////////////////////
	///  Vertex Array	
	/// /////////////////////////////////////////////////////////	

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
		KRM_WARN_MESSAGE("WARN Vertex Array has been generated and bound succesfully with Id : {}", m_RendererID);
		KRM_INFO_MESSAGE("INFO Vertex Array has been generated and bound succesfully with Id : {}", m_RendererID);
		KRM_ERROR_MESSAGE("ERROR Vertex Array has been generated and bound succesfully with Id : {}", m_RendererID);
		KRM_TRACE_MESSAGE("TRACE Vertex Array has been generated and bound succesfully with Id : {}", m_RendererID);
		KRM_LOG_CORE_INFO("Vertex Array has been generated and bound succesfully with Id : {0}", m_RendererID);

		m_VertexBuffers = std::make_unique<VertexBuffer>();
		m_IndexBuffer = std::make_unique<IndexBuffer>();
	}

	VertexArray::~VertexArray()
	{
		(glDeleteVertexArrays(1, &m_RendererID));
		KRM_LOG_CORE_INFO("Vertex Array with Id : {0} has been deleted", m_RendererID);
	}

	void VertexArray::setVertexArray()
	{

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OFFSETOF(Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OFFSETOF(Vertex, color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OFFSETOF(Vertex, texCoord));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OFFSETOF(Vertex, texIndex));

		KRM_LOG_CORE_INFO("Vertex Array with Id : {0} has layout successfully", m_RendererID);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_RendererID);
		KRM_LOG_CORE_INFO("Vertex Array with Id : {0} has been bound", m_RendererID);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
		KRM_LOG_CORE_INFO("Vertex Array with Id : {0} has been unbound", m_RendererID);
	}

	void VertexArray::addDatatoVertexBuffer(Vertex* data, int count)
	{
		m_VertexBuffers->bind();
		m_VertexBuffers->inputData(data, count);
		m_VertexBuffers->setData();
	}

	void VertexArray::addDatatoIndexBuffer(unsigned int* data, int count)
	{
		m_IndexBuffer->bind();
		m_IndexBuffer->inputData(data, count);
		m_IndexBuffer->setData();
	}

}