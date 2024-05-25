#pragma once
#include "Layer.h"
#include <vector>
#include "Base.h"
namespace Hazel {
	class  LayerStack
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
		inline std::vector<Layer*>::reverse_iterator rbegin() {
			return m_Layers.rbegin();
		}
		inline std::vector<Layer*>::reverse_iterator rend() {
			return m_Layers.rend();
		}

		inline std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		inline std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		inline std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		inline std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;

	};
}

