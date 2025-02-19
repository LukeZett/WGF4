#include "Application/Application.h"
#include "Application/Scene.h"
#include "GUI/GUIPage.h"


class DemoScene : public WGF::App::Scene
{
	WGF::UI::GUIPage m_uiPage;
public:
	DemoScene() : m_uiPage()
	{
		m_uiPage.GridLayout()
			.AddColumn(WGF::UI::GridSegment(1, WGF::UI::SizeType::RELATIVE))
			.AddColumn(WGF::UI::GridSegment(3, WGF::UI::SizeType::RELATIVE, 500))
			.AddColumn(WGF::UI::GridSegment(1, WGF::UI::SizeType::RELATIVE))
			.AddRow(WGF::UI::GridSegment(100, WGF::UI::SizeType::PIXELS))
			.AddRow(WGF::UI::GridSegment(1, WGF::UI::SizeType::RELATIVE))
			.AddRow(WGF::UI::GridSegment(100, WGF::UI::SizeType::PIXELS));

		m_uiPage.GridLayout()
			.AddContainer(1, 1, "Test");
	}
	// Inherited via Scene
	void OnFrame(std::chrono::steady_clock::duration frameTime) override
	{
		m_uiPage.OnFrame();
	}
	void SceneStart() override
	{
	}
	void OnKeyboardEvent(WGF::KeyboardEvent& e) override
	{
	}
	void OnMouseMove(WGF::MouseMoveEvent& e) override
	{
	}
	void OnMouseButton(WGF::MouseButtonEvent& e) override
	{
	}
	void OnResize(WGF::ResizeEvent& e) override
	{
		m_uiPage.OnResize(e);
	}
};

int main()
{
	WGF::App::Application app = 
		WGF::App::Application(
			WGF::DeviceLimits()
				.SetTextureLimits(4096, 4096, 1, 1, 1) // Set texture limits to 4096x4096 pixels, needed for the screen pass
				.SetBindGroupsLimits(4, 4, 96, 4) // Set bind group limits
				.SetVertexRequiredLimits(4, 4, 4000960, 96)
				.SetInterShaderStageLimits(16, 8)
				.SetSamplersLimits(8, 8),
			WGF::WindowParameters(720, 480, "Hello World"),
			true
	);
	app.SetScene<DemoScene>();
	app.Run();
	return 0;
}

