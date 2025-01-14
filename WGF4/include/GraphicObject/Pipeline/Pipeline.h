#pragma once
#include "GraphicObject/GraphicObject.h"
#include <webgpu/webgpu.h>
#include "Framework/Device.h"
#include <GraphicObject/Shader/Shader.h>
#include <GraphicObject/BindGroup/BindGroupLayout.h>
#include "PipelineLayout.h"


namespace WGF
{
	class Pipeline
	{
		friend class PipelineBuilder;
		friend class RenderPipelineBuilder;
	protected:
		Shader m_shaderModule;
		PipelineLayout m_pipelineLayout;

		~Pipeline() = default; // do not allow to delete through pointer to base class

	public:
		Pipeline() = default;

		Pipeline(Shader&& shadermodule) : m_shaderModule(std::move(shadermodule)) {}

		Pipeline(Shader&& shadermodule, PipelineLayout&& pipelineLayout) : m_shaderModule(std::move(shadermodule)), m_pipelineLayout(std::move(pipelineLayout)) {}

		inline BindGroupLayout& GetBindGroupLayout(size_t index) { return m_pipelineLayout.GetBindGroupLayout(index); }

	protected:
	};
}
