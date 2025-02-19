#include "Application/Application.h"
#include "WGF4.h"
#include <imgui.h>

#ifdef WEBGPU_BACKEND_DAWN
#define IMGUI_IMPL_WEBGPU_BACKEND_DAWN
#endif // WEBGPU_BACKEND_DAWN
#include <backends/imgui_impl_wgpu.h>
#include <backends/imgui_impl_glfw.h>

using namespace WGF::App;

Application::Application(const DeviceLimits& limits, const WindowParameters& window, bool useDepthBuffer)
{
	/// initialize WGF
	WGF::Initialize(limits, window);

	if(useDepthBuffer) WGF::Window().UseDepth();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO();

	ImGui_ImplWGPU_InitInfo info;
	info.Device = WGF::Device::Get();
	info.RenderTargetFormat = static_cast<WGPUTextureFormat>(WGF::Window().GetTextureFormat());
	info.DepthStencilFormat = static_cast<WGPUTextureFormat>(WGF::Window().GetDepthFormat());
	info.NumFramesInFlight = 3;

	ImGui_ImplGlfw_InitForOther(WGF::Window().GetGLFWwin(), true);
	ImGui_ImplWGPU_Init(&info);

	WGF::Window().SetMouseClickCallback(MOUSEBUTTON_CALLBACK(Application::OnMouseButton, *this));
	WGF::Window().SetMouseMoveCallback(MOUSEMOVE_CALLBACK(Application::OnMouseMove, *this));
	WGF::Window().SetKeyCallback(KEYBOARD_CALLBACK(Application::OnKeyboardEvent, *this));
	WGF::Window().SetResizeCallback(RESIZE_CALLBACK(Application::OnResize, *this));
}

void Application::Run()
{
	WGF::ScreenPassFactory screenPassFactory;
	screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { 0.0f, 0.0f, 0.0f, 1.0f });


	std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentFrameTime = lastFrameTime;
	std::chrono::steady_clock::duration frameTime = currentFrameTime - lastFrameTime;

	while (!WGF::ShouldClose())
	{
		auto pass = screenPassFactory.BeginPass();

		if (!pass.IsValid()) break;

		ImGui_ImplWGPU_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		m_guiStyle.ApplyStyle();

		OnFrame(frameTime);

		m_guiStyle.RevertStyle();

		ImGui::Render();
		ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass.Get());


		screenPassFactory.EndPass(pass);
		WGF::Window().PollEvents();

		currentFrameTime = std::chrono::steady_clock::now();
		frameTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplWGPU_Shutdown();
	ImGui::DestroyContext();
	WGF::Finish();
}

void Application::OnFrame(std::chrono::steady_clock::duration frameTime)
{
	m_activeScene->OnFrame(frameTime);

	if (m_activeScene->ShouldChangeScene())
	{
		SetScene(std::move(m_activeScene->GetNewScene()));
		m_activeScene->SceneStart();
	}
}

void Application::OnKeyboardEvent(WGF::KeyboardEvent& e)
{
	m_activeScene->OnKeyboardEvent(e);
}

void Application::OnMouseMove(WGF::MouseMoveEvent& e)
{
	m_activeScene->OnMouseMove(e);
}

void Application::OnMouseButton(WGF::MouseButtonEvent& e)
{
	m_activeScene->OnMouseButton(e);
}

void Application::OnResize(WGF::ResizeEvent& e)
{
	m_activeScene->OnResize(e);
}

Application::~Application()
{
}
