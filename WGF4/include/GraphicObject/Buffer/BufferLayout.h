#pragma once
#include <cstdint>
#include <webgpu/webgpu.h>
#include <vector>
#include <Logging/Logging.h>


namespace WGF
{
	class BufferLayout
	{
		struct Element
		{
			WGPUVertexFormat format;
			uint16_t elementSize = 0;
			uint16_t elementoffset = 0;
		
			Element(WGPUVertexFormat format, uint16_t elementSize = 0, uint16_t elementoffset = 0)
				: format(format), elementSize(elementSize), elementoffset(elementoffset) {}
		};

		std::vector<BufferLayout::Element> m_elements;
		uint32_t m_stride = 0;
		WGPUVertexStepMode m_mode;
		WGPUVertexBufferLayout m_vertexBufferLayout;
		std::vector<WGPUVertexAttribute> m_vertexAttributes;

	public:
		BufferLayout(bool instanced);

		void PrintLayout();

		WGPUVertexBufferLayout& GenerateVertexBufferLayout(uint16_t shaderLocOffset = 0);

		template<typename T>
		inline BufferLayout& AddElement(int count) { LOG_ERROR("Unsupported vertex attribute type, skipping"); return *this; };

		template<>
		inline BufferLayout& AddElement<int>(int count) { return i_AddElement<WGPUVertexFormat_Sint32, int>(count); }

		template<>
		inline BufferLayout& AddElement<unsigned int>(int count) { return i_AddElement<WGPUVertexFormat_Uint32, unsigned int>(count); }

		template<>
		inline BufferLayout& AddElement<float>(int count) { return i_AddElement<WGPUVertexFormat_Float32, float>(count); }

	private:
		template<WGPUVertexFormat format, typename T>
		inline BufferLayout& i_AddElement(int count)
		{
			if (count > 4)
			{
				LOG_ERROR("Unsupported vertex attribute count, skipping");
				return *this;
			}
			// (format + count - 1) is for choosing the correct vector type (defined by count)
			Element element(static_cast<WGPUVertexFormat>(format + count - 1), static_cast<uint16_t>(sizeof(T) * (uint16_t)count), static_cast<uint16_t>(m_stride));
			m_elements.push_back(element);
			m_stride += element.elementSize;
			return *this;
		}
	};
};
