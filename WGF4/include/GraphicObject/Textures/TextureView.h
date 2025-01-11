#pragma once
#include "GraphicObject/GraphicObject.h"
#include <webgpu/webgpu.h>

namespace WGF
{
	struct TextureViewDesc
	{
		const WGPUTextureViewDescriptor& desc;
		const WGPUTexture& texture;

		TextureViewDesc(const WGPUTextureViewDescriptor& desc, const WGPUTexture& texture) : desc(desc), texture(texture) {}
	};

	static WGPUTextureView CreateTextureView(const TextureViewDesc& descriptor)
	{
		return wgpuTextureCreateView(descriptor.texture, &descriptor.desc);
	}

	class TextureView
	{
		GraphicObject<WGPUTextureView, TextureViewDesc, CreateTextureView, wgpuTextureViewRelease> m_textureView;

	public:
		TextureView() = default;

		TextureView(const WGPUTextureViewDescriptor& desc, WGPUTexture& texture) : m_textureView(TextureViewDesc(desc, texture)) {}

		WGPUTextureView Get() { return m_textureView.Get(); }
	};
}
