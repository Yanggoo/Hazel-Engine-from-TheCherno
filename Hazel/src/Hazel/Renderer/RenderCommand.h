#pragma once
#include "RendererAPI.h"
namespace Hazel {
	class RenderCommand {
	public:
		static void init();
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); };
		inline static void Clear() { s_RendererAPI->Clear(); };
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count=0) { s_RendererAPI->DrawIndexed(vertexArray, count); };
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}