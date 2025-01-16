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
#include "BindGroupLayout.h"

namespace WGF
{
	class BindGroupLayoutBuilder
	{
		static WGPUBindGroupLayout CreateBindGroupLayout(const WGPUBindGroupLayoutDescriptor& desc)
		{
			return wgpuDeviceCreateBindGroupLayout(Device::Get(), &desc);
		}

		using WGPUBGLayout = GraphicObject<WGPUBindGroupLayout, WGPUBindGroupLayoutDescriptor, CreateBindGroupLayout, wgpuBindGroupLayoutRelease>;

		//WGPUBGLayout m_bindGroupLayout;

		std::vector<WGPUBindGroupLayoutEntry> m_entries;
		WGPUBindGroupLayoutDescriptor m_desc{};

	public:

		BindGroupLayoutBuilder() = default;

		BindGroupLayoutBuilder(const std::vector<WGPUBindGroupLayoutEntry>& entries);

		BindGroupLayoutBuilder& AddUniformBinding(uint32_t binding, ShaderStage visibility, size_t uniformSize);

		BindGroupLayoutBuilder& AddStorageBinding(uint32_t binding, ShaderStage visibility);

		BindGroupLayoutBuilder& AddTextureBinding(uint32_t binding, ShaderStage visibility, TexViewDimension dimension, TexSampleType sampleType);

		BindGroupLayoutBuilder& AddTextureStorage(uint32_t binding, ShaderStage visibility,
			TextureAccess access, TextureFormat format, TexViewDimension dimension);

		BindGroupLayout Build();

	private:
		void setDefault(WGPUBindGroupLayoutEntry& bindingLayout);
	};
}
