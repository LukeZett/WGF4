#pragma once
#include "webgpu/webgpu.h"
#include "Framework/Device.h"
#include <filesystem>
#include "GraphicObject/GraphicObject.h"
namespace WGF
{
	class RenderPipeline;

	static WGPUShaderModule CreateShaderModule(const WGPUShaderModuleDescriptor& desc)
	{
		return wgpuDeviceCreateShaderModule(Device::Get(), &desc);
	}

	class Shader
	{

		friend RenderPipeline;

		GraphicObject<WGPUShaderModule, WGPUShaderModuleDescriptor, CreateShaderModule, wgpuShaderModuleRelease> m_shaderModule;
		WGPUShaderModuleDescriptor m_desc = {};
		WGPUShaderModuleWGSLDescriptor m_codeDesc = {};
		std::filesystem::path m_source;
	public:
		Shader();
		
		Shader(const std::filesystem::path& source);

		void SetDesc();

		inline const WGPUShaderModule& Get() const { return m_shaderModule.Get(); };

		void ReloadModule();

		std::string LoadFromPath(const std::filesystem::path& path);

		bool IsValid() const { return m_shaderModule.IsValid(); }
	};
}