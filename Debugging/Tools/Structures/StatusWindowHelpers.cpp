#include <NightOwlPch.h>

#include "StatusWindowHelpers.h"

namespace NightOwl::DebugTools
{
    ScrollingBuffer::ScrollingBuffer(const int& size)
    {
        maxSize = size;
        offset = 0;
        data.reserve(maxSize);
    }

    void ScrollingBuffer::AddPoint(float x, float y)
    {
        if (data.size() < maxSize)
        {
            data.push_back(ImVec2(x, y));
        }
        else
        {
            data[offset] = ImVec2(x, y);
            offset = (offset + 1) % maxSize;
        }
    }

    void ScrollingBuffer::Erase()
    {
        if (!data.empty())
        {
            data.shrink(0);
            offset = 0;
        }
    }

    RollingBuffer::RollingBuffer()
    {
        Span = 10.0f;
        Data.reserve(2000);
    }

    void RollingBuffer::AddPoint(float x, float y)
    {
        float xmod = fmodf(x, Span);
        if (!Data.empty() && xmod < Data.back().x)
            Data.shrink(0);
        Data.push_back(ImVec2(xmod, y));
    }

    StatusWindowProperties::StatusWindowProperties()
        :   FPS(NightOwl::DebugTools::FPS),
			lockFPS(1),
			confirmLockFPS(false),
			xGraphHistory(NightOwl::DebugTools::GRAPH_HISTORY),
			xMax(NightOwl::DebugTools::X_GRAPH_RANGE),
			yMax(NightOwl::DebugTools::Y_GRAPH_RANGE)
    {

    }
}
