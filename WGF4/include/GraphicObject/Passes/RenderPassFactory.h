#pragma once
#include <webgpu/webgpu.h>
#include <array>
#include "Framework/Device.h"
#include "GraphicObject/Passes/RenderPass.h"
#include "GraphicObject/Textures/Texture2D.h"
#include "GraphicObject/Textures/DepthTexture.h"
#include <ranges>
#include <GraphicObject/Textures/TextureView.h>
#include "Framework/Instance.h"

namespace WGF
{
	enum StoreOp
	{
		Store = WGPUStoreOp_Store,
		Discard = WGPUStoreOp_Discard,
	};

	enum LoadOp
	{
		Clear = WGPULoadOp_Clear,
		Load = WGPULoadOp_Load,
	};

	template<size_t colorAttachments>
	class RenderPassFactory
	{
		WGPURenderPassDescriptor m_desc{};
		
		std::array<WGPURenderPassColorAttachment, colorAttachments> m_colorAttachments;
		WGPURenderPassDepthStencilAttachment m_depthAttachment;
		
		std::array<WGPUTextureView, colorAttachments> m_colorViews;
		WGPUTextureView m_depthView;
	
	public:
		inline RenderPassFactory(const char* name = "Render pass");

		inline void SetColorAttachment(uint32_t index, LoadOp loadOp, StoreOp storeOp, WGPUColor clearColor);

		inline void SetDepthAttachment(LoadOp loadOp, StoreOp storeOp, float clearValue, bool readOnly = false);

		inline void SetStencilAttachment(LoadOp loadOp, StoreOp storeOp, uint32_t clearValue, bool readOnly = false);

		inline void SetDepthStencilTexture(TextureView& texture) { m_depthView = texture.Get(); }

		inline void SetColorTexture(TextureView& texture, uint32_t index) { m_colorViews[index] = texture.Get(); }

		inline RenderPass BeginPass();

		inline void EndPass(RenderPass& pass);

		~RenderPassFactory() = default;

	protected:

		inline RenderPass i_BeginPass(const std::array<WGPUTextureView, colorAttachments>& target, WGPUTextureView depthTarget);
	};
}




template<size_t colorAttachments>
inline WGF::RenderPassFactory<colorAttachments>::RenderPassFactory(const char* name)
{

	m_desc.label = name;
	m_desc.nextInChain = nullptr;
	m_desc.depthStencilAttachment = nullptr;
	m_desc.timestampWrites = nullptr;
	m_desc.colorAttachmentCount = colorAttachments;
	m_desc.colorAttachments = &m_colorAttachments[0];
	m_desc.depthStencilAttachment = nullptr;

	SetDepthAttachment(LoadOp::Clear, StoreOp::Store, 1.0f);
	SetStencilAttachment(LoadOp::Clear, StoreOp::Store, 0);
	for (size_t i = 0; i < colorAttachments; i++)
	{
		SetColorAttachment(static_cast<uint32_t>(i), LoadOp::Clear, StoreOp::Store, { 0.0f, 0.0f, 0.0f, 1.0f });
	}
}


template<size_t colorAttachments>
inline void WGF::RenderPassFactory<colorAttachments>::SetColorAttachment(uint32_t index, LoadOp loadOp, StoreOp storeOp, WGPUColor clearColor)
{
	m_colorAttachments[index].loadOp = static_cast<WGPULoadOp>(loadOp);
	m_colorAttachments[index].storeOp = static_cast<WGPUStoreOp>(storeOp);
	m_colorAttachments[index].clearValue = clearColor;
#ifndef WEBGPU_BACKEND_WGPU
	m_colorAttachments[i].depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
#endif // NOT WEBGPU_BACKEND_WGPU
}


template<size_t colorAttachments>
inline void WGF::RenderPassFactory<colorAttachments>::SetDepthAttachment(LoadOp loadOp, StoreOp storeOp, float clearValue, bool readOnly)
{
	m_depthAttachment.depthLoadOp = static_cast<WGPULoadOp>(loadOp);
	m_depthAttachment.depthStoreOp = static_cast<WGPUStoreOp>(storeOp);
	m_depthAttachment.depthClearValue = clearValue;
	m_depthAttachment.depthReadOnly = readOnly;
}


template<size_t colorAttachments>
inline void WGF::RenderPassFactory<colorAttachments>::SetStencilAttachment(LoadOp loadOp, StoreOp storeOp, uint32_t clearValue, bool readOnly)
{
	m_depthAttachment.stencilLoadOp = static_cast<WGPULoadOp>(loadOp);
	m_depthAttachment.stencilStoreOp = static_cast<WGPUStoreOp>(storeOp);
	m_depthAttachment.stencilClearValue = clearValue;
	m_depthAttachment.stencilReadOnly = readOnly;
}


template<size_t colorAttachments>
inline WGF::RenderPass WGF::RenderPassFactory<colorAttachments>::BeginPass()
{
	return i_BeginPass(m_colorViews, m_depthView);
}


template<size_t colorAttachments>
inline void WGF::RenderPassFactory<colorAttachments>::EndPass(RenderPass& pass)
{
	wgpuRenderPassEncoderEnd(pass.m_pass);
	wgpuRenderPassEncoderRelease(pass.m_pass);
	pass.m_pass = nullptr;

	WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
	cmdBufferDescriptor.nextInChain = nullptr;
	cmdBufferDescriptor.label = "Command buffer";
	WGPUCommandBuffer command = wgpuCommandEncoderFinish(Device::GetEncoder(), &cmdBufferDescriptor);
	Device::ReleaseEncoder();
	wgpuQueueSubmit(Device::GetQueue(), 1, &command);
	wgpuCommandBufferRelease(command);
}

template<size_t colorAttachments>
inline WGF::RenderPass WGF::RenderPassFactory<colorAttachments>::i_BeginPass(const std::array<WGPUTextureView, colorAttachments>& target, WGPUTextureView depthTarget)
{
	for (size_t i = 0; i < colorAttachments; i++)
	{
		m_colorAttachments[i].view = target[i];
		m_colorAttachments[i].resolveTarget = nullptr;
	}
	m_desc.colorAttachments = &m_colorAttachments[0];

	if (depthTarget != nullptr)
	{
		m_depthAttachment.view = depthTarget;
		m_depthAttachment.depthClearValue = 1.0f;
		m_depthAttachment.depthLoadOp = WGPULoadOp_Clear;
		m_desc.depthStencilAttachment = &m_depthAttachment;
	}
	else {
		m_desc.depthStencilAttachment = nullptr;
	}

	Device::CreateEncoder();
	return RenderPass(wgpuCommandEncoderBeginRenderPass(Device::GetEncoder(), &m_desc));
}
