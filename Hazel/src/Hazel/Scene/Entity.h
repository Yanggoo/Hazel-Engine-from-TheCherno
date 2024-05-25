#pragma once
#include "entt.hpp"
#include "Scene.h"
namespace Hazel {
	class Entity {
	public:
		Entity() = default;
		Entity(const Entity& other) = default;
		Entity(entt::entity handle, Scene* scene);
		template<typename T>
		bool HasComponent() {
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		};

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			auto& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded(*this, component);
			return component;
		};

		template<typename T>
		void RemoveComponent() {
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		};

		template<typename T>
		T& GetComponent() {
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);

		};

		operator bool() const { return m_EntityHandle != entt::null; };
		bool operator ==(const Entity& other) const {
			return ((m_EntityHandle==other.m_EntityHandle)&& (m_Scene == other.m_Scene));
		}
		bool operator !=(const Entity& other) const {
			return !(*this == other);
		}
		operator entt::entity() const {
			return m_EntityHandle;
		}
		operator uint32_t() const {
			return (uint32_t)m_EntityHandle;
		}

	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}