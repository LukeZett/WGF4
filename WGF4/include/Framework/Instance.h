#pragma once
#include "DeviceLimits.h"
#include "Device.h"
#include "Adapter.h"
#include <memory>
#include "AppWindow/AppWindow.h"
#include <Logging/Logging.h>


namespace WGF
{

	class Framework
	{
	public:

		bool Init(const DeviceLimits& deviceLimits, [[maybe_unused]] const WindowParameters& windowParameters)
		{
			if (!s_instance.CreateInstance()) return false;
			m_appWindow = std::make_unique<AppWindow>();
			m_appWindow->Init(windowParameters);
			m_appWindow->InitSurface(m_wgpuInstance);
			if (Adapter::Init(m_wgpuInstance, m_appWindow->GetSurface())
				&& Device::Init(Adapter::Get(), deviceLimits))
			{
				m_appWindow->ConfigureSurface(Adapter::Get());
				return true;
			}
			return false;
		}

		bool InitHeadless(const DeviceLimits& deviceLimits)
		{
			return CreateInstance()
				&& Adapter::Init(s_instance.m_wgpuInstance, NULL)
				&& Device::Init(Adapter::Get(), deviceLimits);
		}

		AppWindow* Window()
		{
			return m_appWindow.get();
		}

		void Finish()
		{
			Device::Release();
			Adapter::Release();
			wgpuInstanceRelease(s_instance.m_wgpuInstance);
			LOG_INFO("WGPU uninitialized");
		}

		bool ShouldClose()
		{
			return m_appWindow->ShouldClose();
		}

		static Framework& Get() { return s_instance; }

	private:
		static Framework s_instance;

	private:
		WGPUInstance m_wgpuInstance = nullptr;
		std::unique_ptr<AppWindow> m_appWindow = nullptr;

	private:
		bool CreateInstance();

		Framework() {}
		~Framework() {}
	};
}