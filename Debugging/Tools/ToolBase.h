#pragma once

namespace NightOwl::DebugTools
{
	class ToolBase
	{
	public:
		ToolBase();

		ToolBase(const ToolBase&) = delete;

		ToolBase(ToolBase&&) = delete;

		ToolBase& operator=(const ToolBase& tool) = delete;

		virtual ~ToolBase();

		virtual void Render();

		virtual bool& ShowFlag();

	protected:
		bool showWindow;
	};
}