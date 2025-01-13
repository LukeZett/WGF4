#pragma once
#include <webgpu/webgpu.h>
#include <GraphicObject/Enums/BlendOperation.h>
#include <GraphicObject/Enums/BlendFactor.h>

namespace WGF
{
	class BlendState
	{
		friend class RenderPipelineBuilder;

		WGPUBlendState m_blendState{};

	public:
		BlendState()
		{
			m_blendState.color.srcFactor = WGPUBlendFactor_SrcAlpha;
			m_blendState.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
			m_blendState.color.operation = WGPUBlendOperation_Add;
			m_blendState.alpha.srcFactor = WGPUBlendFactor_Zero;
			m_blendState.alpha.dstFactor = WGPUBlendFactor_One;
			m_blendState.alpha.operation = WGPUBlendOperation_Add;
		}

		BlendState& SetColorBlend(BlendFactor srcFactor, BlendFactor dstFactor, BlendOperation operation)
		{
			m_blendState.color.srcFactor = static_cast<WGPUBlendFactor>(srcFactor);
			m_blendState.color.dstFactor = static_cast<WGPUBlendFactor>(dstFactor);
			m_blendState.color.operation = static_cast<WGPUBlendOperation>(operation);
			return *this;
		}

		BlendState& SetAlphaBlend(BlendFactor srcFactor, BlendFactor dstFactor, BlendOperation operation)
		{
			m_blendState.alpha.srcFactor = static_cast<WGPUBlendFactor>(srcFactor);
			m_blendState.alpha.dstFactor = static_cast<WGPUBlendFactor>(dstFactor);
			m_blendState.alpha.operation = static_cast<WGPUBlendOperation>(operation);
			return *this;
		}
	};
}
