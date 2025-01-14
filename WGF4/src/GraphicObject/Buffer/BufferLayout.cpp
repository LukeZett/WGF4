#include "GraphicObject/Buffer/BufferLayout.h"
#include <Logging/Logging.h>

using namespace WGF;

WGF::BufferLayout::BufferLayout(bool instanced)
	: m_mode(instanced ? WGPUVertexStepMode_Instance : WGPUVertexStepMode_Vertex)
{
}

void WGF::BufferLayout::PrintLayout()
{
	if (m_mode & WGPUVertexStepMode_Instance)
		LOG_INFO("Requested buffer layout: Instanced");
	else
		LOG_INFO("Requested buffer layout: Not Instanced");

	for (size_t i = 0; i < m_elements.size(); i++)
	{
		auto& elem = m_elements[i];

		LOG_INFO(std::string("Element: Size ") + std::to_string(elem.elementSize) + "B, offset: " + std::to_string(elem.elementoffset) + "B");
	}
}

WGPUVertexBufferLayout& WGF::BufferLayout::GenerateVertexBufferLayout(uint16_t shaderLocOffset)
{
	m_vertexAttributes.resize(m_elements.size());
	for (size_t i = 0; i < m_elements.size(); i++)
	{
		auto& elem = m_elements[i];
		m_vertexAttributes[i].format = elem.format;
		m_vertexAttributes[i].offset = elem.elementoffset;
		m_vertexAttributes[i].shaderLocation = static_cast<uint32_t>(i + shaderLocOffset);
	}

	m_vertexBufferLayout.arrayStride = m_stride;
	m_vertexBufferLayout.stepMode = m_mode;
	m_vertexBufferLayout.attributeCount = static_cast<uint32_t>(m_elements.size());
	m_vertexBufferLayout.attributes = m_vertexAttributes.data();
	return m_vertexBufferLayout;
}
