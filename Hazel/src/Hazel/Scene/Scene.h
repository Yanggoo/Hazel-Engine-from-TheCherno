#pragma once
#include"entt.hpp"
#include "Hazel/Core/Timestep.h"
namespace Hazel {
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name);

		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
		void OnViewPortResize(uint32_t width, uint32_t height);
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
		void DestroyEntity(Entity entity);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewPortWidth = 0;
		uint32_t m_ViewPortHeight = 0;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

}