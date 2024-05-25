#pragma once
#include "Hazel/Core/Base.h"
#include "Scene.h"
namespace Hazel {
	class SceneSerializer {
	public:
		SceneSerializer(const Ref<Scene>& scene);
		void Serialize(const std::string& filePath);
		void SerializeRuntime(const std::string& filePath);

		bool DeSerialize(const std::string& filePath);
		bool DeSerializeRuntime(const std::string& filePath);
	private:
		Ref<Scene> m_Scene;
	};
}
