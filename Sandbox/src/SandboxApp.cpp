#include <Hazel.h>
#include "hzpch.h"
#include "SandBox2D.h"

//---Entry Point----------------- 
#include "Hazel/Core/EntryPoint.h"


class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		PushLayer(new SandBox2D());
	}
	~Sandbox() {

	}
private:
};

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}
