#pragma once
#include "Layer.h"
#include <vector>
#include "Core.h"
namespace Hazel {
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverLayer(Layer* layer);
		inline std::vector<Layer*>::iterator begin() {
			return m_Layers.begin();
		}
		inline std::vector<Layer*>::iterator end() {
			return m_Layers.end();
		}
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;

	};
}

