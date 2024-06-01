#include "hzpch.h"
#include "Scene.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "Hazel/Core/Log.h"
#include "Entity.h"
#include "Components.h"
namespace Hazel {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}


	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity( m_Registry.create(), this);
		entity.AddComponent<TransformComponent>(glm::vec3(1.0f));
		entity.AddComponent<TagComponent>(name.empty() ? "Entity" : name);
		return entity;
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		//Update Scripts
		{
			auto view = m_Registry.view<NativeScriptComponent>();
			view.each([=](auto entity, auto& nsc)->void {
				if (!nsc.Instance) {
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{entity,this};

					nsc.Instance->OnCreate();
				}
				nsc.Instance->OnUpdate(ts);
				});
		}

		SceneCamera* mainCamera = nullptr;
		glm::mat4 maincameraTransform;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto& entity : view) {
				auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary) {
					mainCamera = &(camera.Camera);
					maincameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera) {
			Renderer2D::BeginScene(*mainCamera, maincameraTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto& entity : group) {
				auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}
			Renderer2D::EndScene();
		}

	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
		}

		Renderer2D::EndScene();
	}

	void Scene::OnViewPortResize(uint32_t width, uint32_t height)
	{
		m_ViewPortWidth = width;
		m_ViewPortHeight = height;
		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewPortSize(width, height);
		}
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	Hazel::Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity(entity, this);
		}
		return Entity{};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewPortSize(m_ViewPortWidth, m_ViewPortHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}

}