#include <NightOwlPch.h>

#include "DockSpace.h"

#include "ImGui/imgui_internal.h"
#include "NightOwl/Core/Utitlity/Logging/LoggerManager.h"

namespace NightOwl::DebugTools
{
	DockSpace::DockSpace()
		:	name("MyDockSpace"), dockSpaceID(0), initFlag(false)
	{
		dockFlags = ImGuiDockNodeFlags_PassthruCentralNode;

		windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	DockSpace::~DockSpace()
	{

	}

	void DockSpace::DockSpaceSetup()
	{
		if (!ImGui::Begin("DockSpace", nullptr, windowFlags))
		{
			ENGINE_LOG_ERROR("Cannot Init Dockspace!");

			ImGui::End();
			return;
		}

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID(name);
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockFlags);

			static bool first_time = true;
			if (first_time)
			{
				first_time = false;

				ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
				ImGui::DockBuilderAddNode(dockspace_id, dockFlags | ImGuiDockNodeFlags_DockSpace);
				ImGui::DockBuilderSetNodeSize(dockspace_id, ImVec2(200, 400));

				auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 2.0f, nullptr, &dockspace_id);

				ImGui::DockBuilderDockWindow("Main Viewport", dock_id_left);
				ImGui::DockBuilderFinish(dockspace_id);
			}
		}

		ImGui::End();
	}
}
