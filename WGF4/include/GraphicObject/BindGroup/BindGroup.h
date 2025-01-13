#pragma once
#include "Framework/Device.h"
#include "GraphicObject/GraphicObject.h"

namespace WGF
{

	static WGPUBindGroup CreateBindGroup(const WGPUBindGroupDescriptor& desc)
	{
		return wgpuDeviceCreateBindGroup(Device::Get(), &desc);
	}

	class BindGroup
	{
		WGPUBindGroupDescriptor m_bindGroupDesc{};
		std::vector<WGPUBindGroupEntry> m_bindings;
		GraphicObject<WGPUBindGroup, WGPUBindGroupDescriptor, CreateBindGroup, wgpuBindGroupRelease> m_bindGroup;
	public:
		BindGroup();

		void SetLayout(const WGPUBindGroupLayout& bgLayout);

		BindGroup(const WGPUBindGroupLayout& bgLayout);

		void AddUniformBinding(uint32_t  binding, WGPUBuffer buffer, uint32_t offset, uint32_t bindingSize);

		void AddTextureBinding(uint32_t bindingIndex, WGPUTextureView texView);

		WGPUBindGroup& Init();

		WGPUBindGroup& Get() { return m_bindGroup.Get(); }
	};
}