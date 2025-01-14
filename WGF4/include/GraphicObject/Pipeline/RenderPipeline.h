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
		RenderPipeline() = default;

		RenderPipeline(WGPURenderPipelineDescriptor& desc, Shader&& shader) : Pipeline(std::move(shader))
		{
			const_cast<WGPUFragmentState*>(desc.fragment)->module = m_shaderModule.Get();
			desc.vertex.module = m_shaderModule.Get();
			desc.layout = m_pipelineLayout.Get();
			m_renderPipeline = GraphicObject<WGPURenderPipeline, WGPURenderPipelineDescriptor, CreateRenderPipeline, wgpuRenderPipelineRelease>(desc);
		}

		RenderPipeline(WGPURenderPipelineDescriptor& desc, Shader&& shader, PipelineLayout&& layout) : Pipeline(std::move(shader), std::move(layout))
		{
			const_cast<WGPUFragmentState*>(desc.fragment)->module = m_shaderModule.Get();
			desc.vertex.module = m_shaderModule.Get();
			desc.layout = m_pipelineLayout.Get();
			m_renderPipeline = GraphicObject<WGPURenderPipeline, WGPURenderPipelineDescriptor, CreateRenderPipeline, wgpuRenderPipelineRelease>(desc);
		}

		inline const WGPURenderPipeline& Get() const { return m_renderPipeline.Get(); };

		~RenderPipeline() noexcept = default;
	};
}
