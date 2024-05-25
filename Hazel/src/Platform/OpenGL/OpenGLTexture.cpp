#include "hzpch.h"
#include "OpenGLTexture.h"
#include <stb_image.h>
#include "Glad/glad.h"
namespace Hazel {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path):m_path(path)
	{
		HZ_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		if (channels == 3) {
			m_dataFormat = GL_RGB;
			m_internalFormat = GL_RGB8;
		}
		else if (channels == 4) {
			m_dataFormat = GL_RGBA;
			m_internalFormat = GL_RGBA8;
		}
		HZ_CORE_ASSERT(m_dataFormat && m_internalFormat,"Format not supported!");
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		glTextureStorage2D(m_RenderID, 1, m_internalFormat, m_Width, m_Height);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, m_dataFormat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height):m_Width(width),m_Height(height)
	{
		HZ_PROFILE_FUNCTION();

		m_dataFormat = GL_RGBA;
		m_internalFormat = GL_RGBA8;

		glCreateTextures(GL_TEXTURE_2D,1, &m_RenderID);
		glTextureStorage2D(m_RenderID, 1, m_internalFormat, m_Width, m_Height);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteTextures(1,&m_RenderID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot /*= 0*/) const
	{
		HZ_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RenderID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		HZ_PROFILE_FUNCTION();

		uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
		HZ_CORE_ASSERT(m_Width*m_Height* bpp == size, "Data must be entire texture!");
		glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height,m_dataFormat, GL_UNSIGNED_BYTE, data);
	}

	bool OpenGLTexture2D::operator==(const Texture& other)
	{
		return m_RenderID == ((OpenGLTexture2D&)other).m_RenderID;
	}

}