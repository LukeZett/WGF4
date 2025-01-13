#pragma once
#include <filesystem>
#include "GraphicObject/Enums/CullMode.h"
#include "GraphicObject/Enums/Topology.h"
#include "GraphicObject/Enums/FrontFace.h"
#include "GraphicObject/Enums/IndexFormat.h"
#include "GraphicObject/Enums/TextureFormat.h"
#include <GraphicObject/Shader/Shader.h>
#include "DepthStencilState.h"
#include "BlendState.h"
#include "GraphicObject/Pipeline/RenderPipeline.h"

namespace WGF
{
	class RenderPipelineBuilder
	{
		std::vector<WGPUColorTargetState> m_colorTargets;
		std::vector<WGPUBlendState> m_blendStates;
		WGPUDepthStencilState m_depthStencilState{};
		WGPURenderPipelineDescriptor m_desc{};
		WGPUFragmentState m_fragmentState{};
		Shader m_shader = Shader();

	public:
		RenderPipelineBuilder();

		RenderPipelineBuilder& SetShader(const std::filesystem::path& path, const char* vs_main = "vs_main", const char* fs_main = "fs_main");

		RenderPipelineBuilder& SetPrimitiveState(Topology primitiveTopology, FrontFace frontFace, CullMode cullMode, IndexFormat stripIndexFormat = Undefined);

		RenderPipelineBuilder& AddColorTarget(TextureFormat targetFormat, const BlendState& blendState);

		RenderPipelineBuilder& AddScreenTarget(const BlendState& blendState);

		RenderPipelineBuilder& AddScreenTarget(const BlendState& blendState, const DepthStencilState& depthState);

		RenderPipelineBuilder& SetDepthStencilState(TextureFormat depthFormat, const DepthStencilState& depthState);

		RenderPipelineBuilder& SetMultisampleState(uint32_t samplecount, uint32_t mask, bool alphaToCoverage);

		RenderPipeline Build();

	private:
		void ConnectChain();
	};
}
