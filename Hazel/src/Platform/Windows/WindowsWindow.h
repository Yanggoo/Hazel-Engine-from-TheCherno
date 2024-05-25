#pragma once

#include "Hazel/Core/Window.h"
#include "GLFW/glfw3.h"
#include "Hazel/Renderer/GraphicContext.h"
namespace Hazel {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate()override;

		inline unsigned int GetHeight() const override { return m_Data.Height; };
		inline unsigned int GetWidth() const override { return m_Data.Width; };

		//Window attribute
		inline void SetEventCallback(const EventCallbackFn& callback) override {
			m_Data.EventCallback = callback;
		}


		void SetVSync(bool enable) override;


		bool IsVSync() const override;

		inline virtual void* GetNativeWindow()const override { return m_Window; };

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Height, Width;
			bool VSync;
			EventCallbackFn EventCallback;
			WindowData() {
				Title = "";
				Height = Width = 0;
				VSync = false;
				EventCallback = nullptr;
			}
		};

		WindowData m_Data;
		Scope<GraphicContext> m_Context;
	};
}

