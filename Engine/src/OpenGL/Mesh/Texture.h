#pragma once

#include <string>
namespace krm {

	class Texture
	{
	public:
		Texture(const std::string& filepath, unsigned int slot = 0);
		~Texture();

		void bind();
		void unbind();

		inline unsigned int getWidth() const { return m_Width; }
		inline unsigned int getHegiht() const { return m_Height; }

		const unsigned int& getSlot() const { return m_Slot; }

	private:
		std::string m_Filepath;
		unsigned int m_Slot;

		unsigned int m_RendererID;

		unsigned int m_Width, m_Height;
	};


}
