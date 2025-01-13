#include "GraphicObject/Buffer/BaseBuffer.h"

using namespace WGF;





WGF::BaseBuffer::BaseBuffer(WGPUBufferUsageFlags usage, size_t size)
{
	m_bufferDesc.nextInChain = nullptr;
	m_bufferDesc.label = "GPU buffer";
	m_bufferDesc.usage = usage;
	m_bufferDesc.mappedAtCreation = false;
	if ((usage | size) == 0) return;
	Allocate(size);
}

WGF::BaseBuffer::BaseBuffer(WGPUBufferUsageFlags usage, size_t size, void* data) : BaseBuffer(usage, size)
{
	Write(data, 0, size);
}

void WGF::BaseBuffer::Write(const void* data, size_t offset, size_t size)
{
	wgpuQueueWriteBuffer(Device::GetQueue(), GetBufferHandle(), offset, data, size);
}

void WGF::BaseBuffer::CopyTo(BaseBuffer& dst)
{
	if (Device::GetEncoder() == nullptr)
	{
		Device::CreateEncoder();
		wgpuCommandEncoderCopyBufferToBuffer(Device::GetEncoder(), GetBufferHandle(), 0, dst.GetBufferHandle(), 0, m_bufferDesc.size);
		Device::ReleaseEncoder();
	}
	else
	{
		wgpuCommandEncoderCopyBufferToBuffer(Device::GetEncoder(), GetBufferHandle(), 0, dst.GetBufferHandle(), 0, m_bufferDesc.size);
	}
}

BaseBuffer WGF::BaseBuffer::Copy()
{
	BaseBuffer buffer(m_bufferDesc.usage, m_bufferDesc.size);
	buffer.m_bufferDesc = m_bufferDesc;
	CopyTo(buffer);
	return buffer;
}

void BaseBuffer::Allocate(size_t size)
{
	m_bufferDesc.size = size;
	m_buffer = GraphicObject<WGPUBuffer, WGPUBufferDescriptor, CreateBuffer, wgpuBufferRelease>(m_bufferDesc);
}