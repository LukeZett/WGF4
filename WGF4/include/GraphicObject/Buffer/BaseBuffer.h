#pragma once
#include <webgpu/webgpu.h>
#include "Framework/Device.h"
#include "Logging/Logging.h"
#include "GraphicObject/GraphicObject.h"

namespace WGF
{
	static WGPUBuffer CreateBuffer(const WGPUBufferDescriptor& desc)
	{
		return wgpuDeviceCreateBuffer(Device::Get(), &desc);
	}

	class BaseBuffer
	{
#ifdef WEBGPU_BACKEND_DAWN
		using WGPUBufferUsageFlags = WGPUBufferUsage;
#endif // WEBGPU_BACKEND_DAWN
		
		GraphicObject<WGPUBuffer, WGPUBufferDescriptor, CreateBuffer, wgpuBufferRelease> m_buffer;
		WGPUBufferDescriptor m_bufferDesc = {};
	public:
		BaseBuffer() = default;

		BaseBuffer(WGPUBufferUsageFlags usage, size_t size);

		BaseBuffer(WGPUBufferUsageFlags usage, size_t size, void* data);

		WGPUBuffer& GetBufferHandle() { return m_buffer.Get(); }

		const WGPUBufferDescriptor& GetDesc() const { return m_bufferDesc; }

		size_t Size() const { return m_bufferDesc.size; };

		void Write(const void* data, size_t offset, size_t size);

		void CopyTo(BaseBuffer& dst);

		BaseBuffer Copy();

	private:
		void Allocate(size_t size);
	};
}