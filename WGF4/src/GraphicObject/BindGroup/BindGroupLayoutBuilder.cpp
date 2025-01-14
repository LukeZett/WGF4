#include "GraphicObject/BindGroup/BindGroupLayoutBuilder.h"

using namespace WGF;

BindGroupLayoutBuilder::BindGroupLayoutBuilder(const std::vector<WGPUBindGroupLayoutEntry>& entries)
{
	m_entries = entries;
}

BindGroupLayoutBuilder& WGF::BindGroupLayoutBuilder::AddUniformBinding(uint32_t binding, ShaderStage visibility, size_t uniformSize)
{
	auto& entry = m_entries.emplace_back();
	setDefault(entry);
	entry.binding = binding;
	entry.visibility = static_cast<WGPUShaderStage>(visibility);
	entry.buffer.type = WGPUBufferBindingType_Uniform;
	entry.buffer.minBindingSize = uniformSize;
	return *this;
}

BindGroupLayoutBuilder& WGF::BindGroupLayoutBuilder::AddStorageBinding(uint32_t binding, ShaderStage visibility)
{
	auto& entry = m_entries.emplace_back();
	setDefault(entry);
	entry.binding = binding;
	entry.visibility = static_cast<WGPUShaderStage>(visibility);
	entry.buffer.type = WGPUBufferBindingType_Storage;
	return *this;
}

BindGroupLayoutBuilder& WGF::BindGroupLayoutBuilder::AddTextureBinding(uint32_t binding, ShaderStage visibility, TexViewDimension dimension, TexSampleType sampleType)
{
	auto& entry = m_entries.emplace_back();
	setDefault(entry);
	entry.binding = binding;
	entry.visibility = static_cast<WGPUShaderStage>(visibility);
	entry.texture.sampleType = static_cast<WGPUTextureSampleType>(sampleType);
	entry.texture.viewDimension = static_cast<WGPUTextureViewDimension>(dimension);
	return *this;
}

BindGroupLayoutBuilder& WGF::BindGroupLayoutBuilder::AddTextureStorage(uint32_t binding, ShaderStage visibility, TextureAccess access, TextureFormat format, TexViewDimension dimension)
{
	auto& entry = m_entries.emplace_back();
	setDefault(entry);
	entry.binding = binding;
	entry.visibility = static_cast<WGPUShaderStage>(visibility);
	entry.storageTexture.access = static_cast<WGPUStorageTextureAccess>(access);
	entry.storageTexture.format = static_cast<WGPUTextureFormat>(format);
	entry.storageTexture.viewDimension = static_cast<WGPUTextureViewDimension>(dimension);
	return *this;
}

BindGroupLayout WGF::BindGroupLayoutBuilder::Build()
{
	m_desc.entryCount = m_entries.size();
	m_desc.entries = m_entries.data();
	return BindGroupLayout(m_desc);
}

void WGF::BindGroupLayoutBuilder::setDefault(WGPUBindGroupLayoutEntry& bindingLayout) {
	bindingLayout.buffer.nextInChain = nullptr;
	bindingLayout.buffer.type = WGPUBufferBindingType_Undefined;
	bindingLayout.buffer.hasDynamicOffset = false;

	bindingLayout.sampler.nextInChain = nullptr;
	bindingLayout.sampler.type = WGPUSamplerBindingType_Undefined;

	bindingLayout.storageTexture.nextInChain = nullptr;
	bindingLayout.storageTexture.access = WGPUStorageTextureAccess_Undefined;
	bindingLayout.storageTexture.format = WGPUTextureFormat_Undefined;
	bindingLayout.storageTexture.viewDimension = WGPUTextureViewDimension_Undefined;

	bindingLayout.texture.nextInChain = nullptr;
	bindingLayout.texture.multisampled = false;
	bindingLayout.texture.sampleType = WGPUTextureSampleType_Undefined;
	bindingLayout.texture.viewDimension = WGPUTextureViewDimension_Undefined;
}
