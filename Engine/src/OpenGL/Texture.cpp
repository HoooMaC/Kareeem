#include "Core\KRMpch.h"

#include "Texture.h"

#include "Core\Log.h"

#include "stb_image.h"

#include "GLEW\glew.h"

namespace krm {

	Texture::Texture(std::string filepath, unsigned int slot)
		: m_FilePath(filepath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), m_Slot(slot)
	{
		if (m_Slot == 0)
		{
			KRM_LOG_CORE_WARN("Slot 0 is for object with no texture");
			ASSERT(false);
		}

		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
		KRM_LOG_CORE_INFO("Succes to create new Texture with Id : {0} and slot : {1}", m_RendererID, m_Slot);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
		KRM_LOG_CORE_INFO("Texture with Id : {0} and slot {1} has been deleted", m_RendererID, m_Slot);
	}

	void Texture::bind() const
	{
		glBindTextureUnit(m_Slot, m_RendererID);
		KRM_LOG_CORE_INFO("Texture with Id : {0} and slot {1} has been bound", m_RendererID, m_Slot);
	}

	void Texture::unbind() const
	{
		glBindTextureUnit(m_Slot, 0);
		KRM_LOG_CORE_INFO("Texture with Id : {0} and slot {1} has been unbound", m_RendererID, m_Slot);
	}

}