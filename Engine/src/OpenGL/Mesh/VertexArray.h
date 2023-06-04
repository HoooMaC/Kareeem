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

	//	void setVertexBuffer();
		void addDatatoVertexBuffer(unsigned int index, Vertex* data, int count);
		void addDatatoIndexBuffer(unsigned int* data, int count);

		unsigned int getCount() const { return m_IndexBuffer.GetCount(); }
	private:
		std::unique_ptr<VertexBuffer> m_VertexBuffers;
		IndexBuffer m_IndexBuffer;
	};

}