#pragma once
#include <webgpu/webgpu.h>
#include <GraphicObject/Enums/CompareFunction.h>

namespace WGF
{
	class DepthStencilState
	{
		friend class RenderPipelineBuilder;

		WGPUDepthStencilState m_depthState{};

		static void setDefault(WGPUStencilFaceState& stencilFaceState);

		static void setDefault(WGPUDepthStencilState& depthStencilState);

	public:
		DepthStencilState()
		{
			setDefault(m_depthState);
			m_depthState.depthCompare = WGPUCompareFunction_Less;
			m_depthState.depthWriteEnabled = true;
			m_depthState.stencilReadMask = 0;
			m_depthState.stencilWriteMask = 0;
		}

		DepthStencilState(CompareFunction function, bool depthWrite, uint32_t stencilReadMask = 0, uint32_t stencilWriteMask = 0)
		{
			setDefault(m_depthState);
			m_depthState.depthCompare = static_cast<WGPUCompareFunction>(function);
			m_depthState.depthWriteEnabled = depthWrite;
			m_depthState.stencilReadMask = stencilReadMask;
			m_depthState.stencilWriteMask = stencilWriteMask;
		}
	};

	inline void DepthStencilState::setDefault(WGPUStencilFaceState& stencilFaceState) {
		stencilFaceState.compare = WGPUCompareFunction_Always;
		stencilFaceState.failOp = WGPUStencilOperation_Keep;
		stencilFaceState.depthFailOp = WGPUStencilOperation_Keep;
		stencilFaceState.passOp = WGPUStencilOperation_Keep;
	}

	inline void DepthStencilState::setDefault(WGPUDepthStencilState& depthStencilState) {
		depthStencilState.format = WGPUTextureFormat_Undefined;
		depthStencilState.depthWriteEnabled = false;
		depthStencilState.depthCompare = WGPUCompareFunction_Always;
		depthStencilState.stencilReadMask = 0xFFFFFFFF;
		depthStencilState.stencilWriteMask = 0xFFFFFFFF;
		depthStencilState.depthBias = 0;
		depthStencilState.depthBiasSlopeScale = 0;
		depthStencilState.depthBiasClamp = 0;
		setDefault(depthStencilState.stencilFront);
		setDefault(depthStencilState.stencilBack);
	}
}
