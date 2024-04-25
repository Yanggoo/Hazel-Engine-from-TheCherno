#pragma once
#include <glm/glm.hpp>
namespace Hazel {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& indexSrc);
		~Shader();
		void Bind() const;
		void UnBind() const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RenderID;

	};
}

