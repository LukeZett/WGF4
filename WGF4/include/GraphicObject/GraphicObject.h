#pragma once
#include "Logging/Tracker.h"

#define TRACKGRAPHICOBJECT

namespace WGF
{
	template<typename T, typename DESC, T INIT(const DESC&), void DESTRUCT(T)>
	class GraphicObject
	{
		T m_object = nullptr;
	public:
		GraphicObject() {}

		GraphicObject(const DESC& desc) : m_object(INIT(desc))
		{
			#ifdef TRACKGRAPHICOBJECT
			Tracker::AddResource<T>(sizeof(T), reinterpret_cast<uint64_t>(m_object));
			#endif
		}
		
		GraphicObject(const GraphicObject& other) = delete;

		GraphicObject(GraphicObject&& other) noexcept : m_object(other.m_object)
		{
			other.m_object = nullptr;
		}

		GraphicObject& operator=(const GraphicObject& other) = delete;

		GraphicObject& operator=(GraphicObject&& other) noexcept
		{
			if (this == &other) return *this;

			if (m_object != nullptr)
			{
				#ifdef TRACKGRAPHICOBJECT
				Tracker::RemoveResource<T>(reinterpret_cast<uint64_t>(m_object));
				#endif
				DESTRUCT(m_object);
			}

			m_object = other.m_object;
			other.m_object = nullptr;
			return *this;
		}

		~GraphicObject()
		{
			if (m_object == nullptr) return;

			#ifdef TRACKGRAPHICOBJECT
			Tracker::RemoveResource<T>(reinterpret_cast<uint64_t>(m_object));
			#endif
			DESTRUCT(m_object);
		}

		T& Get() { return m_object; }

		const T& Get() const { return m_object; }

		bool IsValid() const { return m_object != nullptr; }
	};
};
