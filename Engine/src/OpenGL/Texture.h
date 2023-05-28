#pragma once
#include "Core\KRMpch.h"

#include "OpenGL\glInterface.h"

namespace krm {

	class Texture : public OpenGL
	{
	public:
		Texture(std::string filepath, unsigned int slot = 1);

		~Texture();

		void bind() const override;
		void unbind() const override;

	public:
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		inline const unsigned int getSlot() const { return m_Slot; }
		inline std::string checkFilePath() const { return m_FilePath; }

	public:
		unsigned int m_Slot;
	private:
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	};

}