#pragma once

#include "ToolBase.h"

#include "Structures/StatusWindowHelpers.h"

namespace NightOwl::DebugTools
{
	class StatusWindow : public ToolBase
	{
	public:
		StatusWindow();

		void Render() override;

	private:
		StatusWindowProperties properties;
	};
}
