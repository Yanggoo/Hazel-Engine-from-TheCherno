#pragma once
#include <glm/glm.hpp>
#include "Hazel/Renderer/Shader.h"
#include <unordered_map>

typedef unsigned int GLenum;
namespace Hazel {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filePath);
		~OpenGLShader();
		void Bind() const;
		void UnBind() const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);


		virtual void SetMat4(const std::string& name, const glm::mat4& matrix)  override;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix)  override;
		virtual void SetFloat(const std::string& name, float value)             override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetInt(const std::string& name, int value)                 override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		inline virtual const std::string GetName() const override { return m_Name; };
	private:
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
		std::string Readfile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		std::string m_Name;
	private:
		uint32_t m_RenderID;

	};
}
