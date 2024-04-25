#include "hzpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
namespace Hazel {
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::Begin(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::End()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}

}
