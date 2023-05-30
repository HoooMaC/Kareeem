#pragma once

#include "Core/KRMpch.h"

#include "OpenGL/Mesh/Buffer.h"

namespace krm {

	/// ////////////////////////////////////////////////////////////////////
	///  Vertex Array
	/// ////////////////////////////////////////////////////////////////////

	class VertexArray : public OpenGL
	{
	public:
		VertexArray();
		~VertexArray();

		void setVertexArray();

		void bind() const override;
		void unbind() const override;

		void setVertexBuffer();
		void setIndexBuffer();
	private:
		VertexBuffer m_VertexBuffer;
		IndexBuffer m_IndexBuffer;
	};

}