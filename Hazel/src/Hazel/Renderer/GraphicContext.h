#pragma once
namespace Hazel {
	class GraphicContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};
}