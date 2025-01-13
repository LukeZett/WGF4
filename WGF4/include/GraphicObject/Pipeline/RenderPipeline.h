#pragma once
#include "GraphicObject/GraphicObject.h"
#include "Pipeline.h"

namespace WGF
{
	static WGPURenderPipeline CreateRenderPipeline(const WGPURenderPipelineDescriptor& desc)
	{
		return wgpuDeviceCreateRenderPipeline(Device::Get(), &desc);
	}

	class RenderPipeline : public Pipeline
	{
		friend class RenderPipelineBuilder;

		GraphicObject<WGPURenderPipeline, WGPURenderPipelineDescriptor, CreateRenderPipeline, wgpuRenderPipelineRelease> m_renderPipeline;
	
	public:
		RenderPipeline(const WGPURenderPipelineDescriptor& desc) : m_renderPipeline(desc) {}

		inline const WGPURenderPipeline& Get() const { return m_renderPipeline.Get(); };

		~RenderPipeline() noexcept = default;
	};
}
