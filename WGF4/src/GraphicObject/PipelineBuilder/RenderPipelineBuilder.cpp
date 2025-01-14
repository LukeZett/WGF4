#include "GraphicObject/PipelineBuilder/RenderPipelineBuilder.h"
#include "WGF4.h"

	

using namespace WGF;

WGF::RenderPipelineBuilder::RenderPipelineBuilder()
{
	m_desc.label = "Render Pipeline";
	m_desc.vertex.entryPoint = "vs_main";
	m_fragmentState.entryPoint = "fs_main";

	SetPrimitiveState(Topology::TriangleList, FrontFace::CCW, CullMode::None);
	SetMultisampleState(1, ~0u, false);
	SetDepthStencilState(WGF::Window().GetTextureFormat(), DepthStencilState());

}

RenderPipelineBuilder& WGF::RenderPipelineBuilder::SetShaderFromPath(const std::filesystem::path& path, const char* vs_main, const char* fs_main)
{
	m_shaderPath = path;
	m_shaderType = ShaderSourceType::Filepath;
	m_desc.vertex.entryPoint = vs_main;
	m_fragmentState.entryPoint = fs_main;
	return *this;
}

RenderPipelineBuilder& WGF::RenderPipelineBuilder::SetShaderFromText(const std::string& source, const char* vs_main, const char* fs_main)
{
	m_shaderSource = source;
	m_shaderType = ShaderSourceType::Text;
	m_desc.vertex.entryPoint = vs_main;
	m_fragmentState.entryPoint = fs_main;
	return *this;
}

RenderPipelineBuilder& WGF::RenderPipelineBuilder::SetPrimitiveState(Topology primitiveTopology, FrontFace frontFace, CullMode cullMode, IndexFormat stripIndexFormat)
{
	m_desc.primitive.topology = static_cast<WGPUPrimitiveTopology>(primitiveTopology);
	m_desc.primitive.stripIndexFormat = static_cast<WGPUIndexFormat>(stripIndexFormat);
	m_desc.primitive.frontFace = static_cast<WGPUFrontFace>(frontFace);
	m_desc.primitive.cullMode = static_cast<WGPUCullMode>(cullMode);
	m_desc.primitive.nextInChain = nullptr;

	return *this;
}

RenderPipelineBuilder& WGF::RenderPipelineBuilder::AddColorTarget(TextureFormat targetFormat, const BlendState& blendState)
{
	m_blendStates.push_back(blendState.m_blendState);
	WGPUColorTargetState colorTarget = {};
	colorTarget.format = static_cast<WGPUTextureFormat>(targetFormat);
	colorTarget.writeMask = WGPUColorWriteMask_All;
	m_colorTargets.push_back(colorTarget);
	return *this;
}

RenderPipelineBuilder& WGF::RenderPipelineBuilder::AddScreenTarget(const BlendState& blendState)
{
	AddColorTarget(WGF::Window().GetTextureFormat(), blendState);
	return *this;
}

RenderPipelineBuilder& WGF::RenderPipelineBuilder::AddScreenTarget(const BlendState& blendState, const DepthStencilState& depthState)
{
	AddColorTarget(WGF::Window().GetTextureFormat(), blendState);
	if (WGF::Window().DepthEnabled())
	{
		return SetDepthStencilState(WGF::Window().GetDepthFormat(), depthState);
	}
	LOG_ERROR("Application window does not have a depth texture, skipping depth state setting!");
	return *this;
}

RenderPipelineBuilder& WGF::RenderPipelineBuilder::SetDepthStencilState(TextureFormat depthFormat, const DepthStencilState& depthState)
{
	m_depthStencilState = depthState.m_depthState;
	m_depthStencilState.format = static_cast<WGPUTextureFormat>(depthFormat);
	return *this;
}

RenderPipelineBuilder& WGF::RenderPipelineBuilder::SetMultisampleState(uint32_t samplecount, uint32_t mask, bool alphaToCoverage)
{
	m_desc.multisample.count = samplecount;
	m_desc.multisample.mask = mask;
	m_desc.multisample.alphaToCoverageEnabled = static_cast<WGPUBool>(alphaToCoverage);
	return *this;
}

RenderPipeline WGF::RenderPipelineBuilder::Build()
{
	ConnectChain();

	Shader shader = CreateShader();

	return RenderPipeline(m_desc, std::move(shader));
}

Shader WGF::RenderPipelineBuilder::CreateShader()
{
	switch (m_shaderType)
	{
	case WGF::RenderPipelineBuilder::Text:
		return Shader::CreateFromText(m_shaderSource);
	case WGF::RenderPipelineBuilder::Filepath:
		return Shader(m_shaderPath);
	case WGF::RenderPipelineBuilder::None:
		return Shader();
	default:
		return Shader();
	}
}

void WGF::RenderPipelineBuilder::ConnectChain()
{
	m_desc.fragment = &m_fragmentState;
	m_desc.depthStencil = &m_depthStencilState;

	for (size_t i = 0; i < m_colorTargets.size(); i++)
	{
		m_colorTargets[i].blend = &m_blendStates[i];
	}
	m_fragmentState.targetCount = static_cast<uint32_t>(m_colorTargets.size());
	m_fragmentState.targets = m_colorTargets.data();
	m_desc.layout = nullptr;
}
