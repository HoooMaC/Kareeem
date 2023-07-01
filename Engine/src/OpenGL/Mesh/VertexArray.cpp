#include "Core/KRMpch.h"
#include "VertexArray.h"

#include "Core/Log.h"
#include "Core/Core.h"

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
		KRM_INFO_MESSAGE("Vertex Array has been generated and bound succesfully with Id : {}", m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
		//KRM_LOG_CORE_INFO("Vertex Array with Id : {} has been deleted", m_RendererID);
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

		KRM_INFO_MESSAGE("Vertex Array with Id : {} has layout successfully", m_RendererID);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_RendererID);
		KRM_INFO_MESSAGE("Vertex Array with Id : {} has been bound", m_RendererID);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
		KRM_INFO_MESSAGE("Vertex Array with Id : {} has been unbound", m_RendererID);
	}

}