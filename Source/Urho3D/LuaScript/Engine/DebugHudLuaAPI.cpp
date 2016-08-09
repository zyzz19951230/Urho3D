//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../../Precompiled.h"

#include "../../Engine/DebugHud.h"
#include "../../Resource/XMLFile.h"
#include "../../UI/Text.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterDebugHud(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] unsigned DEBUGHUD_SHOW_NONE
    lua["DEBUGHUD_SHOW_NONE"] = DEBUGHUD_SHOW_NONE;
    // [Constant] unsigned DEBUGHUD_SHOW_ALL
    lua["DEBUGHUD_SHOW_STATS"] = DEBUGHUD_SHOW_STATS;
    // [Constant] unsigned DEBUGHUD_SHOW_MODE
    lua["DEBUGHUD_SHOW_MODE"] = DEBUGHUD_SHOW_MODE;
    // [Constant] unsigned DEBUGHUD_SHOW_PROFILER
    lua["DEBUGHUD_SHOW_PROFILER"] = DEBUGHUD_SHOW_PROFILER;
    // [Constant] unsigned DEBUGHUD_SHOW_MEMORY
    lua["DEBUGHUD_SHOW_MEMORY"] = DEBUGHUD_SHOW_MEMORY;
    // [Constant] unsigned DEBUGHUD_SHOW_ALL
    lua["DEBUGHUD_SHOW_ALL"] = DEBUGHUD_SHOW_ALL;
    // [Constant] unsigned DEBUGHUD_SHOW_EVENTPROFILER
    lua["DEBUGHUD_SHOW_EVENTPROFILER"] = DEBUGHUD_SHOW_EVENTPROFILER;

    // [Class] DebugHud : Object
    lua["DebugHud"].setClass(UserdataMetatable<DebugHud, Object>()

        // .addFunction("Update", &DebugHud::Update)

        // [Method] void SetDefaultStyle(XMLFile* style)
        .addFunction("SetDefaultStyle", &DebugHud::SetDefaultStyle)
        // [Method] void SetMode(unsigned mode)
        .addFunction("SetMode", &DebugHud::SetMode)
        // [Method] void SetProfilerMaxDepth(unsigned depth)
        .addFunction("SetProfilerMaxDepth", &DebugHud::SetProfilerMaxDepth)
        // [Method] void SetProfilerInterval(float interval)
        .addFunction("SetProfilerInterval", &DebugHud::SetProfilerInterval)
        // [Method] void SetUseRendererStats(bool enable)
        .addFunction("SetUseRendererStats", &DebugHud::SetUseRendererStats)
        // [Method] void Toggle(unsigned mode)
        .addFunction("Toggle", &DebugHud::Toggle)
        // [Method] void ToggleAll()
        .addFunction("ToggleAll", &DebugHud::ToggleAll)

        // [Method] XMLFile* GetDefaultStyle() const
        .addFunction("GetDefaultStyle", &DebugHud::GetDefaultStyle)
        // [Method] Text* GetStatsText() const
        .addFunction("GetStatsText", &DebugHud::GetStatsText)
        // [Method] Text* GetModeText() const
        .addFunction("GetModeText", &DebugHud::GetModeText)
        // [Method] Text* GetProfilerText() const
        .addFunction("GetProfilerText", &DebugHud::GetProfilerText)
        // [Method] Text* GetMemoryText() const
        .addFunction("GetMemoryText", &DebugHud::GetMemoryText)
        // [Method] unsigned GetMode() const
        .addFunction("GetMode", &DebugHud::GetMode)
        // [Method] unsigned GetProfilerMaxDepth() const
        .addFunction("GetProfilerMaxDepth", &DebugHud::GetProfilerMaxDepth)
        // [Method] float GetProfilerInterval() const
        .addFunction("GetProfilerInterval", &DebugHud::GetProfilerInterval)
        // [Method] bool GetUseRendererStats() const
        .addFunction("GetUseRendererStats", &DebugHud::GetUseRendererStats)

        .addOverloadedFunctions("SetAppStats",
            static_cast<void(DebugHud::*)(const String&, const Variant&)>(&DebugHud::SetAppStats),
            static_cast<void(DebugHud::*)(const String&, const String&)>(&DebugHud::SetAppStats))

        // [Method] bool ResetAppStats(const String& label)
        .addFunction("ResetAppStats", &DebugHud::ResetAppStats)
        // [Method] void ClearAppStats()
        .addFunction("ClearAppStats", &DebugHud::ClearAppStats)

        // [Property] XMLFile* defaultStyle
        .addProperty("defaultStyle", &DebugHud::GetDefaultStyle, &DebugHud::SetDefaultStyle)
        // [Property(ReadOnly)] Text* statsText
        .addProperty("statsText", &DebugHud::GetStatsText)
        // [Property(ReadOnly)] Text* modeText
        .addProperty("modeText", &DebugHud::GetModeText)
        // [Property(ReadOnly)] Text* profilerText
        .addProperty("profilerText", &DebugHud::GetProfilerText)
        // [Property] unsigned mode
        .addProperty("mode", &DebugHud::GetMode, &DebugHud::SetMode)
        // [Property] unsigned profilerMaxDepth
        .addProperty("profilerMaxDepth", &DebugHud::GetProfilerMaxDepth, &DebugHud::SetProfilerMaxDepth)
        // [Property] float profilerInterval
        .addProperty("profilerInterval", &DebugHud::GetProfilerInterval, &DebugHud::SetProfilerInterval)
        // [Property] bool useRendererStats
        .addProperty("useRendererStats", &DebugHud::GetUseRendererStats, &DebugHud::SetUseRendererStats)
        );
}
}

