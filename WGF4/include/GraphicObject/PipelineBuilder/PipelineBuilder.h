#pragma once
#include <string>
#include <filesystem>
#include <GraphicObject/BindGroup/BindGroupLayout.h>
#include <GraphicObject/BindGroup/BindGroupLayoutBuilder.h>
#include "GraphicObject/Pipeline/PipelineLayout.h"

namespace WGF
{
	class PipelineBuilder
	{
	protected:
		enum ShaderSourceType
		{
			Text,
			Filepath,
			None
		};

		ShaderSourceType m_shaderType = ShaderSourceType::None;
		std::string m_shaderSource = "";
		std::filesystem::path m_shaderPath = "";

		std::vector<BindGroupLayoutBuilder> m_bindGroupLayouts;


	public:
		PipelineBuilder& SetShaderFromPath(const std::filesystem::path& path);

		PipelineBuilder& SetShaderFromText(const std::string& source);

		inline BindGroupLayoutBuilder& AddBindGroupLayout() { return m_bindGroupLayouts.emplace_back(); };

		inline BindGroupLayoutBuilder& GetBindGroupLayout(size_t index) { return m_bindGroupLayouts[index]; };

	protected:
		PipelineLayout BuildPipelineLayout();

		std::vector<BindGroupLayout> GetBindGroupLayouts();
	};
}