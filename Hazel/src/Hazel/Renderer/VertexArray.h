#pragma once
#include "Buffer.h"
#include <memory>
#include <vector>
namespace Hazel {
	class VertexArray {
	public:
		virtual ~VertexArray() = default;
		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& VertexBuffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer> GetIndexBUffer() const = 0;
		static VertexArray* Create();

	};

}