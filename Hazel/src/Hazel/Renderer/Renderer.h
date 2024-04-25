#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include "OrthographicCamera.h"
#include "Shader.h" 
namespace Hazel {

	class Renderer
	{
	public:
		static void Begin(OrthographicCamera&camera);
		static void End();
		static void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray);
		inline static RendererAPI::API GetAPI(){ return RendererAPI::GetAPI(); };
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};

}
