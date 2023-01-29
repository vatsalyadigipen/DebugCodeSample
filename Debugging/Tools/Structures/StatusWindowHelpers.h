#pragma once

#include "ImGui/imgui.h"
#include "NightOwl/Core/Debugging/DebugConstants.h"

namespace NightOwl::DebugTools
{
	struct ScrollingBuffer
	{
		int maxSize;

		int offset;

		ImVector<ImVec2> data;

		ScrollingBuffer(const int& maxSize = NightOwl::DebugTools::SCROLLING_BUFFER_SIZE);

		void AddPoint(float x, float y);

		void Erase();
	};

	struct RollingBuffer
	{
		float Span;

		ImVector<ImVec2> Data;

		RollingBuffer();

		void AddPoint(float x, float y);
	};

	struct StatusWindowProperties
	{
		int FPS;

		int lockFPS;

		bool confirmLockFPS;

		float xGraphHistory;	// Graph history

		float xMax;		// length of X_Axis of Graph

		float yMax;		// highestFPS aka Y-axis Scaling factor

		ScrollingBuffer scrollingData1, scrollingData2;

		RollingBuffer rollingData1, rollingData2;

		StatusWindowProperties();
	};
}