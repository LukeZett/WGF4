#pragma once
#include <webgpu/webgpu.h>
#include "GraphicObject/GraphicObject.h"
#include "Framework/Device.h"
#include <GraphicObject/BindGroup/BindGroupLayout.h>

namespace WGF
{
	class PipelineLayout
	{
		static WGPUPipelineLayout CreatePipelineLayout(const WGPUPipelineLayoutDescriptor& desc)
		{
			return wgpuDeviceCreatePipelineLayout(Device::Get(), &desc);
		}

		using Layout = GraphicObject<WGPUPipelineLayout, WGPUPipelineLayoutDescriptor, CreatePipelineLayout, wgpuPipelineLayoutRelease>;
		Layout m_pipelineLayout;
		std::vector<BindGroupLayout> m_bindGroupLayouts;
	public:
		PipelineLayout() = default;

		PipelineLayout(const WGPUPipelineLayoutDescriptor& desc, std::vector<BindGroupLayout>&& bgLayouts) : m_pipelineLayout(desc), m_bindGroupLayouts(std::move(bgLayouts)) {}
	
		inline const WGPUPipelineLayout& Get() const { return m_pipelineLayout.Get(); };

		inline BindGroupLayout& GetBindGroupLayout(size_t index) { return m_bindGroupLayouts[index]; }
	};
}
