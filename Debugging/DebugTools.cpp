#include <NightOwlPch.h>

#include "DebugTools.h"

#include <ImGui/backends/imgui_impl_glfw.h>
#include <ImGui/backends/imgui_impl_opengl3.h>

#include "ImGui/imgui_internal.h"
#include "ImPlot/implot.h"
#include "NightOwl/Window/WindowApi.h"

#include "NightOwl/Core/Utitlity/Logging/LoggerManager.h"
#include "NightOwl/Core/Debugging/DebugConstants.h"

namespace NightOwl::DebugTools
{
	DebugTools::DebugTools()
		:	showBasicWindow(true)
	{
		properties.noTitlebar = false;
		properties.noScrollbar = false;
		properties.noMenu = false;

		InitImGui();
	}

	DebugTools::~DebugTools()
	{
		TerminateImGui();
	}

	void DebugTools::RunDebugTools()
	{
		BeginFrame();

		BasicWindow();

		EndFrame();
	}

	void DebugTools::InitImGui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImPlot::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		// Removing ".ini" file extension due to the CRT Guidelines
		io.IniFilename = NULL;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		auto* window = static_cast<GLFWwindow*>(Window::WindowApi::GetWindow()->GetWindowHandle());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(IMGUI_OPENGL_VERSION);
	}

	void DebugTools::TerminateImGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImPlot::DestroyContext();
		ImGui::DestroyContext();
	}

	void DebugTools::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void DebugTools::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void DebugTools::BasicWindow()
	{
		ImGuiWindowFlags window_flags = 0;
		if (properties.noTitlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (properties.noScrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!properties.noMenu)           window_flags |= ImGuiWindowFlags_MenuBar;

		// Since ".ini" file violates CRT guidelines we need to specify ViewPort size in the beginning
		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		float xOffset = main_viewport->WorkPos.x + NightOwl::DebugTools::IMGUI_WINDOW_XOFFSET;
		float yOffset = main_viewport->WorkPos.y + NightOwl::DebugTools::IMGUI_WINDOW_YOFFSET;
		ImGui::SetNextWindowPos(ImVec2(xOffset, yOffset), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(NightOwl::DebugTools::BASIC_WINDOW_XSIZE, NightOwl::DebugTools::BASIC_WINDOW_YSIZE), ImGuiCond_FirstUseEver);

		dockSpace.DockSpaceSetup();

		if (!ImGui::Begin("Main Viewport", &showBasicWindow, window_flags))
		{
			ENGINE_LOG_ERROR("ImGui Failed to Initialize");

			ImGui::End();
			return;
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Tools"))
			{
				ImGui::MenuItem("Status Window", nullptr, &statusWindow.ShowFlag());
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		if (statusWindow.ShowFlag())
			statusWindow.Render();

		ImGui::End();
	}
}
