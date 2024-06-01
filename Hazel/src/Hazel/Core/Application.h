#pragma once
#include "Base.h"
#include "Log.h"
#include "Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/Event.h"
#include "LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Core/Timestep.h"

int main(int argc, char** argv);

namespace Hazel {
	class Application
	{
	public:
		Application(const std::string& name = "Hazel App");
		virtual ~Application() = default;
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		inline void Close() { m_Running = false; };
		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;
		friend int ::main(int argc, char** argv);
	};

	//to be defined in a client
	Application* CreateApplication();
}

