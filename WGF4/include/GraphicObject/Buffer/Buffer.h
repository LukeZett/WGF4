#pragma once
#include "BaseBuffer.h"


namespace WGF
{
	template<typename T>
	class Buffer
	{
#ifdef WEBGPU_BACKEND_DAWN
		using WGPUBufferUsageFlags = WGPUBufferUsage;
#endif // WEBGPU_BACKEND_DAWN

	protected:
		BaseBuffer m_buffer;
		size_t m_length = 0;
	public:
		Buffer() = default;

		Buffer(WGPUBufferUsageFlags usage, size_t capacity) : m_buffer(usage, capacity * sizeof(T)) {}

		size_t Capacity() const { return m_buffer.Size() / sizeof(T); }

		uint32_t Length() const { return static_cast<uint32_t>(m_length); }

		size_t CapacityInBytes() const { return m_buffer.Size(); }

		size_t SizeInBytes() const { return m_length * sizeof(T); }

		WGPUBuffer& Get() { return m_buffer.GetBufferHandle(); }

		void Write(const std::vector<T>& data)
		{
			Write(&data[0], data.size(), 0);
		}

		void Write(const std::vector<T>& data, size_t offset)
		{
			Write(&data[0], data.size(), offset);
		}

		void Write(const T* data, uint64_t size, uint64_t offset)
		{
			m_length = std::max(size + offset, m_length);
			m_buffer.Write(data, offset * sizeof(T), size * sizeof(T));
		}

		void Realloc(uint64_t newCapacity)
		{
			BaseBuffer newBuffer = BaseBuffer(this->m_buffer.GetDesc().usage, newCapacity);
			m_buffer.CopyTo(newBuffer);
			m_buffer = std::move(newBuffer);
		}
	};
}
