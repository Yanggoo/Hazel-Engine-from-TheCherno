#pragma once
#include "Entity.h"
namespace Hazel {
	class ScriptableEntity {
	public:
		~ScriptableEntity()=default;
		template<typename T>
		T& GetComponent() {
			return m_Entity.GetComponent<T>();
		}
		virtual void OnCreate() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnDestroy() {};
	private:
		Entity m_Entity;
		friend class Scene;
	};
}