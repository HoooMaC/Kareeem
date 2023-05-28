#pragma once
#include "Core\KRMpch.h"
#include "Core\Core.h"

namespace krm {

	class OpenGL
	{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		inline virtual const unsigned int& getID() const { return m_RendererID; }
	protected:
		unsigned int m_RendererID = 0;
	};

	template<typename T>
	class Buffer
	{
	public:
		virtual void clearData() { m_Data.clear(); }
		virtual void setData() = 0;
	public:
		std::vector<T> m_Data;
	private:
	};

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
	};

	/// ////////////////////////////////////////////////////////////////////
	///  Vertex Buffer
	/// ////////////////////////////////////////////////////////////////////

	class VertexBuffer : public OpenGL, public Buffer<Vertex>
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void bind() const override;
		void unbind() const override;

		void clearData() override;
		void setData() override;
	};

	/// ////////////////////////////////////////////////////////////////////
	///  Index Buffer
	/// ////////////////////////////////////////////////////////////////////

	class IndexBuffer : public OpenGL, public Buffer<unsigned int>
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void bind() const override;
		void unbind() const override;

		void clearData() override;
		void setData() override;

		inline unsigned int GetCount() const { return m_Data.size(); }
	};
}