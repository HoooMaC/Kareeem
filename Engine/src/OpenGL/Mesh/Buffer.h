#pragma once
#include "Core\KRMpch.h"
#include "Core\Core.h"

namespace krm {

	/// ////////////////////////////////////////////////////////////////////
	///  Vertex Buffer
	/// ////////////////////////////////////////////////////////////////////

	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void bind() const;
		void unbind() const;
		void setData(std::vector<Vertex>& vertexData) const;
	private: 
		unsigned int m_RendererID;
	};

	/// ////////////////////////////////////////////////////////////////////
	///  Index Buffer
	/// ////////////////////////////////////////////////////////////////////

	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void bind() const;
		void unbind() const;
		void setData(std::vector<unsigned int>& indexData) const;

	private:
		unsigned int m_RendererID;
	};

}