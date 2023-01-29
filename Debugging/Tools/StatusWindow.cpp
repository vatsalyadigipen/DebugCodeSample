#include <NightOwlPch.h>

#include "StatusWindow.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImPlot/implot.h"

#include "NightOwl/Core/Time/Time.h"
#include "NightOwl/Core/Debugging/DebugConstants.h"

namespace NightOwl::DebugTools
{
	StatusWindow::StatusWindow()
		:   ToolBase()
	{
		
	}

	void StatusWindow::Render()
	{
        if (ImGui::CollapsingHeader("FPS Counter"))
        {
            // NOTE: Graph assumes 60 FPS, bigger data buffer required for higher FPS
            ImVec2 mouse = ImGui::GetMousePos();
            properties.xMax += ImGui::GetIO().DeltaTime;
            properties.FPS = NightOwl::Core::Time::GetFrameRate();
            properties.scrollingData1.AddPoint(properties.xMax, static_cast<float>(properties.FPS));
            properties.rollingData1.AddPoint(properties.xMax,   static_cast<float>(properties.FPS));
            properties.scrollingData2.AddPoint(properties.xMax, static_cast<float>(properties.FPS));
            properties.rollingData2.AddPoint(properties.xMax,   static_cast<float>(properties.FPS));

            ImGui::Text("FPS: %d", NightOwl::Core::Time::GetFrameRate());
            ImGui::SliderInt("Lock FPS", &properties.lockFPS, 1, 300);
            ImGui::SameLine(); ImGui::Checkbox("LOCK", &properties.confirmLockFPS);
            if (properties.confirmLockFPS)
                NightOwl::Core::Time::LockFrameRate(properties.lockFPS);
            else
                NightOwl::Core::Time::UnlockFrameRate();
            ImGui::SliderFloat("X-Axis Range", &properties.xGraphHistory, 1, 30, "%.1f s");

            properties.rollingData1.Span = properties.xGraphHistory;
            properties.rollingData2.Span = properties.xGraphHistory;

            if (properties.yMax < properties.FPS)
                properties.yMax = properties.FPS + NightOwl::DebugTools::STATUS_WINDOW_GRAPH_YOFFSET;

            static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

            if (ImPlot::BeginPlot("Scrolling Graph", ImVec2(-1, 150)))
            {
                ImPlot::SetupAxes(NULL, NULL, flags, 0);
                ImPlot::SetupAxisLimits(ImAxis_X1, properties.xMax - properties.xGraphHistory, properties.xMax, ImGuiCond_Always);
                ImPlot::SetupAxisLimits(ImAxis_Y1, 0, properties.yMax, ImGuiCond_Always);

                ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
                ImPlot::PlotShaded("FPS", &properties.scrollingData1.data[0].x, &properties.scrollingData1.data[0].y, properties.scrollingData1.data.size(), -INFINITY, 0, properties.scrollingData1.offset, 2 * sizeof(float));
                ImPlot::PlotLine("Time", &properties.scrollingData2.data[0].x, &properties.scrollingData2.data[0].y, properties.scrollingData2.data.size(), 0, properties.scrollingData2.offset, 2 * sizeof(float));

                ImPlot::EndPlot();
            }

            if (ImPlot::BeginPlot("Rolling Graph", ImVec2(-1, 150)))
            {
                ImPlot::SetupAxes(NULL, NULL, flags, 0);
                ImPlot::SetupAxisLimits(ImAxis_X1, 0, properties.xGraphHistory, ImGuiCond_Always);
                ImPlot::SetupAxisLimits(ImAxis_Y1, 0, properties.yMax, ImGuiCond_Always);

                ImPlot::PlotLine("FPS", &properties.rollingData1.Data[0].x, &properties.rollingData1.Data[0].y, properties.rollingData1.Data.size(), 0, 0, 2 * sizeof(float));
                ImPlot::PlotLine("Time", &properties.rollingData2.Data[0].x, &properties.rollingData2.Data[0].y, properties.rollingData2.Data.size(), 0, 0, 2 * sizeof(float));

                ImPlot::EndPlot();
            }
        }
	}
}
