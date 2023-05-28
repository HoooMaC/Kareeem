#include "Core\KRMpch.h"
#include "Core\Log.h"

#include "GLEW\glew.h"

#include "OpenGL\glInterface.h"

namespace krm {

	/// ////////////////////////////////////////////////////////////////////
	///  Vertex Array
	/// ////////////////////////////////////////////////////////////////////

	VertexArray::VertexArray()
	{
		(glGenVertexArrays(1, &m_RendererID));
		(glBindVertexArray(m_RendererID));
		KRM_LOG_CORE_INFO("Vertex Array has been generated and bound succesfully with Id : {0}", m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		(glDeleteVertexArrays(1, &m_RendererID));
		KRM_LOG_CORE_INFO("Vertex Array with Id : {0} has been deleted", m_RendererID);
	}

	void VertexArray::setVertexArray()
	{

		(glEnableVertexAttribArray(0));
		(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OFFSETOF(Vertex, position)));

		(glEnableVertexAttribArray(1));
		(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OFFSETOF(Vertex, color)));

		(glEnableVertexAttribArray(2));
		(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OFFSETOF(Vertex, texCoord)));

		(glEnableVertexAttribArray(3));
		(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OFFSETOF(Vertex, texIndex)));

		KRM_LOG_CORE_INFO("Vertex Array with Id : {0} has layout successfully", m_RendererID);
	}

	void VertexArray::bind() const
	{
		(glBindVertexArray(m_RendererID));
		KRM_LOG_CORE_INFO("Vertex Array with Id : {0} has been bound", m_RendererID);
	}

	void VertexArray::unbind() const
	{
		(glBindVertexArray(0));
		KRM_LOG_CORE_INFO("Vertex Array with Id : {0} has been unbound", m_RendererID);
	}


	/// ////////////////////////////////////////////////////////////////////
	///  Vertex Buffer
	/// ////////////////////////////////////////////////////////////////////


	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, 1000 * 4 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		KRM_LOG_CORE_INFO("Vertex Buffer has been generated with Id : {0} and bound succesfully", m_RendererID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
		KRM_LOG_CORE_INFO("Vertex Buffer with Id : {0} has been deleted", m_RendererID);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		KRM_LOG_CORE_INFO("Vertex Buffer with Id : {0} has been bound", m_RendererID);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		KRM_LOG_CORE_INFO("Vertex Buffer with Id : {0} has been unbound", m_RendererID);
	}

	void VertexBuffer::setData()
	{
		GLsizeiptr sizeVBO = m_Data.size() * sizeof(Vertex);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVBO, m_Data.data());
	}

	void VertexBuffer::clearData()
	{
		m_Data.clear();
		KRM_LOG_CORE_INFO("All of the vertex buffer with Id : {0} has been cleared", m_RendererID);
	}

	/// ////////////////////////////////////////////////////////////////////
	///  Index Buffer
	/// ////////////////////////////////////////////////////////////////////

	IndexBuffer::IndexBuffer()
	{
		//ASSERT(sizeof(unsigned int) == sizeof(GLuint))

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1000 * 6 * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
		KRM_LOG_CORE_INFO("Index Buffer has been created and bound with Id : {0}", m_RendererID);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
		KRM_LOG_CORE_INFO("Index Buffer with Id : {0} has been deleted", m_RendererID);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		KRM_LOG_CORE_INFO("Index Buffer with Id : {0} has been bound", m_RendererID);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		KRM_LOG_CORE_INFO("Index Buffer with Id : {0} has been unbound", m_RendererID);
	}

	void IndexBuffer::clearData()
	{
		m_Data.clear();
		KRM_LOG_CORE_INFO("All of the index buffer with Id : {0} has been cleared", m_RendererID);
	}

	void IndexBuffer::setData()
	{
		GLsizeiptr sizeIBO = m_Data.size() * sizeof(unsigned int);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeIBO, m_Data.data());
	}

}