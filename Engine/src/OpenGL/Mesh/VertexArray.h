#pragma once

namespace krm {

	/// ////////////////////////////////////////////////////////////////////
	///  Vertex Array
	/// ////////////////////////////////////////////////////////////////////

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void setVertexArray();

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_RendererID;
	};

}