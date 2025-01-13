#pragma once
#include "GraphicObject/Pipeline/RenderPipeline.h"

namespace WGF
{
	class RenderPass
	{
		template<size_t T>
		friend class RenderPassFactory;

		WGPURenderPassEncoder m_pass{};
		bool m_valid = true;

	public:
		RenderPass() : m_valid(false) {}

		bool IsValid() const { return m_valid; }

		WGPURenderPassEncoder Get() const { return m_pass; }
		
		RenderPass(WGPURenderPassEncoder pass) : m_pass(pass) {}
		
		void Draw(uint32_t vertexCount, uint32_t instanceCount = 1, uint32_t firstVertex = 0, uint32_t firstInstance = 0) const
		{
			wgpuRenderPassEncoderDraw(m_pass, vertexCount, instanceCount, firstVertex, firstInstance);
		}

		void BindPipeline(const RenderPipeline& pipeline) const
		{
			wgpuRenderPassEncoderSetPipeline(m_pass, pipeline.Get());
		}

		~RenderPass() = default;
	private:
	};
}
