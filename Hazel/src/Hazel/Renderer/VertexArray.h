#pragma once
#include "Buffer.h"
#include <vector>
#include "Hazel/Core/Base.h"
namespace Hazel {
	class VertexArray {
	public:
		virtual ~VertexArray() = default;
		virtual void AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer) = 0;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer> GetIndexBUffer() const = 0;
		static Ref<VertexArray> Create();

	};

}