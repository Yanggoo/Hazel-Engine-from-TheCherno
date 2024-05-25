#include <Hazel.h>
#include "hzpch.h"
#include "EditorLayer.h"

//---Entry Point----------------- 
#include "Hazel/Core/EntryPoint.h"

namespace Hazel {
	class HazelEditor : public Application {
	public:
		HazelEditor() : Application("Hazel Editor") {
			PushLayer(new EditorLayer());
		}
		~HazelEditor() {

		}
	private:
	};

	Application* CreateApplication() {
		return new HazelEditor();
	}
}
