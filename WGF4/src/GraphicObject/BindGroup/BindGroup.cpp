#include "GraphicObject/BindGroup/BindGroup.h"

using namespace WGF;

BindGroup::BindGroup(const WGPUBindGroupLayout& bgLayout)
{
	m_bindGroupDesc.nextInChain = nullptr;
	m_bindGroupDesc.layout = bgLayout;
}

void BindGroup::AddUniformBinding(uint32_t bindingIndex, WGPUBuffer buffer, uint32_t offset, uint32_t bindingSize)
{
	auto& binding = m_bindings.emplace_back();
	binding.nextInChain = nullptr;
	binding.binding = bindingIndex;
	binding.buffer = buffer;
	binding.offset = offset;
	binding.size = bindingSize;
}

void BindGroup::AddTextureBinding(uint32_t bindingIndex, WGPUTextureView texView)
{
	auto& binding = m_bindings.emplace_back();
	binding.nextInChain = nullptr;
	binding.binding = bindingIndex;
	binding.textureView = texView;
}

WGPUBindGroup& BindGroup::Init()
{
	m_bindGroupDesc.entryCount = m_bindings.size();
	m_bindGroupDesc.entries = &m_bindings[0];
	m_bindGroup = GraphicObject<WGPUBindGroup, WGPUBindGroupDescriptor, CreateBindGroup, wgpuBindGroupRelease>(m_bindGroupDesc);
	return m_bindGroup.Get();
}
