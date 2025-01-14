#pragma once
#include "GraphicObject/GraphicObject.h"
#include <webgpu/webgpu.h>
#include "Framework/Device.h"
#include <GraphicObject/Shader/Shader.h>


namespace WGF
{
	static WGPUPipelineLayout CreatePipelineLayout(const WGPUPipelineLayoutDescriptor& desc)
	{
		return wgpuDeviceCreatePipelineLayout(Device::Get(), &desc);
	}

	class Pipeline
	{
	protected:
		GraphicObject<WGPUPipelineLayout, WGPUPipelineLayoutDescriptor, CreatePipelineLayout, wgpuPipelineLayoutRelease> m_pipelineLayout;
		Shader m_shaderModule;
		std::vector<WGPUBindGroupLayout> m_bindGroupLayouts;

		~Pipeline() = default; // do not allow to delete through pointer to base class

	public:
		Pipeline() = default;

		Pipeline(Shader&& shadermodule) : m_shaderModule(std::move(shadermodule)) {}
	};
}
