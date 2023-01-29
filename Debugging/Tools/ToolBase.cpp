#include <NightOwlPch.h>

#include "ToolBase.h"

namespace NightOwl::DebugTools
{
	ToolBase::ToolBase()
		:	showWindow(false)
	{
		
	}

	ToolBase::~ToolBase() = default;

	void ToolBase::Render()
	{
		
	}

	bool& ToolBase::ShowFlag()
	{
		return showWindow;
	}

}