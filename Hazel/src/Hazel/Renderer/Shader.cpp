#include "hzpch.h"
#include "Shader.h"
#include "Platform//OpenGL/OpenGLShader.h"
#include "Hazel/Renderer/Renderer.h"
namespace Hazel {


	Hazel::Ref<Shader> Shader::Create(const std::string& name,const std::string& vertexSrc, const std::string& indexSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name,vertexSrc, indexSrc);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Hazel::Ref<Hazel::Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(path);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& Shader)
	{
		HZ_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = Shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& Shader)
	{
		auto name = Shader->GetName();
		Add(name, Shader);
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name,shader);
		return shader;
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::Get(const std::string& name)
	{
		HZ_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name)!= m_Shaders.end();
	}

}
