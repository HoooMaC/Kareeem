#include "Core\KRMpch.h"
#include "Buffer.h"

#include "Core\Core.h"
#include "Core\Log.h"
#include "GLEW\glew.h"

#include "OpenGL\Mesh\MeshLog.h"


namespace krm {

	/// ////////////////////////////////////////////////////////////////////
	///  Vertex Buffer
	/// ////////////////////////////////////////////////////////////////////


	VertexBuffer::VertexBuffer()
	{
		GLsizeiptr size = static_cast<GLsizeiptr>(1000) * 4 * sizeof(Vertex);

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

		KRM_INFO_MESSAGE("Vertex Buffer has been generated with Id : {} and bound succesfully", m_RendererID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
		//KRM_LOG_CORE_INFO("Vertex Buffer with Id : {} has been deleted", m_RendererID);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		KRM_INFO_MESSAGE("Vertex Buffer with Id : {} has been bound", m_RendererID);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		KRM_INFO_MESSAGE("Vertex Buffer with Id : {} has been unbound", m_RendererID);
	}

	void VertexBuffer::setData(std::vector<Vertex>& vertexData) const 
	{
		GLsizeiptr sizeVBO = vertexData.size() * sizeof(Vertex);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVBO, vertexData.data());
	}

	/// ////////////////////////////////////////////////////////////////////
	///  Index Buffer
	/// ////////////////////////////////////////////////////////////////////

	IndexBuffer::IndexBuffer()
	{
		ASSERT(sizeof(unsigned int) == sizeof(GLuint))
		GLsizeiptr sizeIBO =  static_cast<GLsizeiptr>(1000) * 6 * sizeof(unsigned int);

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIBO, nullptr, GL_DYNAMIC_DRAW);
		KRM_INFO_MESSAGE("Index Buffer has been created and bound with Id : {}", m_RendererID);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
		//KRM_LOG_CORE_INFO("Index Buffer with Id : {} has been deleted", m_RendererID);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		KRM_INFO_MESSAGE("Index Buffer with Id : {} has been bound", m_RendererID);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		KRM_INFO_MESSAGE("Index Buffer with Id : {} has been unbound", m_RendererID);
	}

	void IndexBuffer::setData(std::vector<unsigned int>& indexData) const 
	{
		GLsizeiptr sizeIBO = indexData.size() * sizeof(unsigned int);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeIBO, indexData.data());
	}

}