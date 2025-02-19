#pragma once
#include <chrono>
#include <AppWindow/Events.h>
#include <memory>


namespace WGF::App
{
	class Scene
	{
		bool m_useNewScene = false;
		std::unique_ptr<Scene> m_nextScene;

	public:
		virtual void OnFrame(std::chrono::steady_clock::duration frameTime) = 0;

		virtual void SceneStart() = 0;

		virtual void OnKeyboardEvent(WGF::KeyboardEvent& e) = 0;

		virtual void OnMouseMove(WGF::MouseMoveEvent& e) = 0;

		virtual void OnMouseButton(WGF::MouseButtonEvent& e) = 0;

		virtual void OnResize(WGF::ResizeEvent& e) = 0;

		virtual ~Scene() = default;
		
		std::unique_ptr<Scene> GetNewScene() { m_useNewScene = false; return std::move(m_nextScene); }

		bool ShouldChangeScene() const { return m_useNewScene; }
	
	protected:
		void SetNewScene(std::unique_ptr<Scene>&& scene);
	};
}
