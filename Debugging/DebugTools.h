#pragma once

#include "Tools/StatusWindow.h"
#include "DockSpace.h"

namespace NightOwl::DebugTools
{
	struct BasicWindowProperties
	{
		bool noTitlebar;
		bool noScrollbar;
		bool noMenu;
	};

	class DebugTools
	{
	public:
		DebugTools();
		
		~DebugTools();

		void RunDebugTools();

		bool& ShowBasicWindow();

	private:
		void InitImGui();

		void TerminateImGui();

		void BasicWindow();

		void BeginFrame();

		void EndFrame();

		bool showBasicWindow;

		BasicWindowProperties properties{};

		StatusWindow statusWindow;

		DockSpace dockSpace;
	};
}