#pragma once

#include "OpenGL\glInterface.h"

namespace krm {

	class Renderer
	{
	private:
		VertexArray m_vao;
		VertexBuffer m_vbo;
		IndexBuffer m_ibo;
	};


}