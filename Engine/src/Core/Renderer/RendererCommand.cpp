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

	void RendererCommand::enableBlend()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RendererCommand::enableDepth()
	{
		glEnable(GL_DEPTH_TEST);
	}

}