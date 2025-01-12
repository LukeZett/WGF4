#pragma once
#include "RenderPassFactory.h"

namespace WGF
{
	class ScreenPassFactory : public RenderPassFactory<1>
	{
		WGPUTextureView m_surface = nullptr;
	public:

		inline RenderPass BeginPass()
		{
			m_surface = WGF::Framework::Get().WGF::Framework::Window()->GetNextSurfaceTextureView();

			if (!m_surface) return RenderPass();

			WGPUTextureView depthTarget = nullptr;
			if (WGF::Framework::Get().WGF::Framework::Window()->DepthEnabled())
			{
				depthTarget = WGF::Framework::Get().WGF::Framework::Window()->GetDepthTexView();
			}

			return i_BeginPass( { m_surface }, depthTarget);
		}

		inline void EndPass(RenderPass& pass)
		{
			wgpuTextureViewRelease(m_surface);
			RenderPassFactory<1>::EndPass(pass);
			WGF::Framework::Get().WGF::Framework::Window()->PresentSurface();
		}
	};
}
