#pragma once
#include <webgpu/webgpu.h>
#include "GraphicObject/GraphicObject.h"
#include "Framework/Device.h"
#include <vector>
#include "GraphicObject/Enums/ShaderStage.h"
#include "GraphicObject/Enums/TexDimension.h"
#include <GraphicObject/Enums/TexSampleType.h>
#include <GraphicObject/Enums/TextureFormat.h>
#include <GraphicObject/Enums/TextureAccess.h>

namespace WGF
{
	class BindGroupLayout
	{
		static WGPUBindGroupLayout CreateBindGroupLayout(const WGPUBindGroupLayoutDescriptor& desc)
		{
			return wgpuDeviceCreateBindGroupLayout(Device::Get(), &desc);
		}

		using WGPUBGLayout = GraphicObject<WGPUBindGroupLayout, WGPUBindGroupLayoutDescriptor, CreateBindGroupLayout, wgpuBindGroupLayoutRelease>;

		WGPUBGLayout m_bindGroupLayout;
	public:
		BindGroupLayout(const WGPUBindGroupLayoutDescriptor& desc) : m_bindGroupLayout(desc) {}

		inline WGPUBindGroupLayout Get() const { return m_bindGroupLayout.Get(); }
	};
}
