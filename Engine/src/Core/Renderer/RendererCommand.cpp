#include "Core/KRMpch.h"

#include "RendererCommand.h"

#include <GLEW/glew.h>

namespace krm {




	void RendererCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RendererCommand::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

}