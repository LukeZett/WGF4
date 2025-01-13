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
