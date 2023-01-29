#pragma once

#include "ImGui/imgui.h"

namespace NightOwl::DebugTools
{
	class DockSpace
	{
	public:
		DockSpace();
		~DockSpace();

		void DockSpaceSetup();

	private:
		const char* name;

		ImGuiDockNodeFlags dockFlags;

		ImGuiWindowFlags windowFlags;

		ImGuiID dockSpaceID;

		bool initFlag;
	};
}
