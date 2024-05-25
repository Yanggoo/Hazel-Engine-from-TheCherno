#pragma once
#include "Hazel/Renderer/Texture.h"
#include <string>
#include "Glad/glad.h"
namespace Hazel {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D() override;
		inline virtual uint32_t GetWidth() const override { return m_Width; };
		inline virtual uint32_t GetHeight() const override { return m_Height; };
		virtual void Bind(uint32_t slot = 0) const override;
		inline virtual uint32_t GetRendererID() const override { return m_RenderID; };

		void SetData(void* data, uint32_t size) override;
		bool operator == (const Texture& other) override;

	private:
		uint32_t m_RenderID;
		uint32_t m_Height, m_Width;
		std::string m_path;
		GLenum m_internalFormat;
		GLenum m_dataFormat;

	};
}

