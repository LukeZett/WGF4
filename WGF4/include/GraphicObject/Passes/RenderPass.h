#pragma once
#include "GraphicObject/Pipeline/RenderPipeline.h"
#include <GraphicObject/BindGroup/BindGroup.h>
#include <GraphicObject/Buffer/Buffer.h>

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

		void BindBindGroup(BindGroup& bindGroup, uint32_t index) const
		{
			wgpuRenderPassEncoderSetBindGroup(m_pass, index, bindGroup.Get(), 0, 0);
		}

		template<typename T>
		void BindVertexBuffer(Buffer<T>& buffer, uint32_t slot, uint64_t offset, uint64_t size) const
		{
			wgpuRenderPassEncoderSetVertexBuffer(m_pass, slot, buffer.Get(), offset, size);
		}

		~RenderPass() = default;
	private:
	};
}
