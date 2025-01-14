#include "GraphicObject/PipelineBuilder/PipelineBuilder.h"
#include "WGF4.h"

using namespace WGF;

PipelineBuilder& WGF::PipelineBuilder::SetShaderFromPath(const std::filesystem::path& path)
{
	m_shaderPath = path;
	m_shaderType = ShaderSourceType::Filepath;
	return *this;
}

PipelineBuilder& WGF::PipelineBuilder::SetShaderFromText(const std::string& source)
{
	m_shaderSource = source;
	m_shaderType = ShaderSourceType::Text;
	return *this;
}

PipelineLayout WGF::PipelineBuilder::BuildPipelineLayout()
{
	std::vector<BindGroupLayout> bgLayouts = GetBindGroupLayouts();
	std::vector<WGPUBindGroupLayout> wgpuBgLayouts;

	for(auto& bgLayout : bgLayouts)
	{
		wgpuBgLayouts.push_back(bgLayout.Get());
	}
	WGPUPipelineLayoutDescriptor desc = {};
	desc.bindGroupLayoutCount = wgpuBgLayouts.size();
	desc.bindGroupLayouts = wgpuBgLayouts.data();
	desc.label = "Pipeline Layout";

	return PipelineLayout(desc, std::move(bgLayouts));
}

std::vector<BindGroupLayout> WGF::PipelineBuilder::GetBindGroupLayouts()
{
	std::vector<BindGroupLayout> bindGroupLayouts;

	for (auto& layout : m_bindGroupLayouts)
	{
		bindGroupLayouts.push_back(layout.Build());
	}
	return bindGroupLayouts;
}
