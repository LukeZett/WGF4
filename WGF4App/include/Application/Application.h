#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <memory>
#include "Scene.h"
#include <Framework/DeviceLimits.h>
#include <AppWindow/Events.h>
#include <AppWindow/WindowParameters.h>
#include <GUI/GUIStyle.h>
#include <chrono>

namespace WGF::App
{
	class Application
	{
		std::unique_ptr<Scene> m_activeScene;
		UI::GUIStyle m_guiStyle;
	public:
		Application(const DeviceLimits& limits, const WindowParameters& window, bool useDepthBuffer = false);

		template<typename SceneType, typename... Args>
		void SetScene(Args&&... args) { m_activeScene = std::make_unique<SceneType>(std::forward<Args>(args)...); }

		void SetScene(std::unique_ptr<Scene>&& scene) { m_activeScene = std::move(scene); }

		void Run();

		void OnFrame(std::chrono::steady_clock::duration frameTime);

		void OnKeyboardEvent(WGF::KeyboardEvent& e);

		void OnMouseMove(WGF::MouseMoveEvent& e);

		void OnMouseButton(WGF::MouseButtonEvent& e);

		void OnResize(WGF::ResizeEvent& e);

		~Application();
	};
}
