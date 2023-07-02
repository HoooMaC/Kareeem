#include "Core/KRMpch.h"

#include "OpenGL/Mesh/Texture.h"
#include "OpenGL/Mesh/MeshLog.h"

#include <stb_image.h>

#include <GLEW/glew.h>
namespace krm {



	Texture::Texture(const std::string& filepath, unsigned int slot)
		: m_Filepath(filepath), m_Slot(slot)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channel;
		stbi_uc* imageBuffer = stbi_load(m_Filepath.c_str(), &width, &height, &channel, 0);

		KRM_MESH_ASSERT(imageBuffer);
			
		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);

		stbi_image_free(imageBuffer);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::bind()
	{
		glBindTextureUnit(m_Slot, m_RendererID);
	}

	void Texture::unbind()
	{
		glBindTextureUnit(m_Slot, 0);
	}
}