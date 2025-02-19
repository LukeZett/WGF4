#pragma once
#include <AppWindow/Events.h>
#include "GUIStyle.h"
#include "GUI/Grid/Grid.h"

namespace WGF::UI
{
	class GUIPage
	{
		GUIStyle m_style;
		Grid m_grid;
	public:
		void OnFrame();

		inline Grid& GridLayout() { return m_grid; };

		void OnResize(WGF::ResizeEvent& e);

	protected:
		void DrawInterface();
	};
}