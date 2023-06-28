#pragma once
#include "Core\KRMpch.h"
#include "Core\Core.h"

namespace krm {

/*	class OpenGL
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
		inline virtual std::vector<T>& getData() { return m_Data; }
	protected:
		std::vector<T> m_Data;
	};
*/
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

		void clearData();
		void setData();

		void inputData(Vertex* data, int count);
	private: 
		unsigned int m_RendererID;
		std::vector<Vertex> m_Data;
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

		void clearData();
		void setData();

		void inputData(unsigned int* data, int count);

		inline unsigned int GetCount() const { return (unsigned int)m_Data.size(); }

	private:
		unsigned int m_RendererID;
		std::vector<unsigned int> m_Data;
	};

}