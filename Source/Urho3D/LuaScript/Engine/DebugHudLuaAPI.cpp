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

    lua["DEBUGHUD_SHOW_NONE"] = DEBUGHUD_SHOW_NONE;
    lua["DEBUGHUD_SHOW_STATS"] = DEBUGHUD_SHOW_STATS;
    lua["DEBUGHUD_SHOW_MODE"] = DEBUGHUD_SHOW_MODE;
    lua["DEBUGHUD_SHOW_PROFILER"] = DEBUGHUD_SHOW_PROFILER;
    lua["DEBUGHUD_SHOW_MEMORY"] = DEBUGHUD_SHOW_MEMORY;
    lua["DEBUGHUD_SHOW_ALL"] = DEBUGHUD_SHOW_ALL;
    lua["DEBUGHUD_SHOW_ALL_MEMORY"] = DEBUGHUD_SHOW_ALL_MEMORY;
    lua["DEBUGHUD_SHOW_EVENTPROFILER"] = DEBUGHUD_SHOW_EVENTPROFILER;

    lua["DebugHud"].setClass(UserdataMetatable<DebugHud, Object>()

        // .addFunction("Update", &DebugHud::Update)

        .addFunction("SetDefaultStyle", &DebugHud::SetDefaultStyle)
        .addFunction("SetMode", &DebugHud::SetMode)
        .addFunction("SetProfilerMaxDepth", &DebugHud::SetProfilerMaxDepth)
        .addFunction("SetProfilerInterval", &DebugHud::SetProfilerInterval)
        .addFunction("SetUseRendererStats", &DebugHud::SetUseRendererStats)
        .addFunction("Toggle", &DebugHud::Toggle)
        .addFunction("ToggleAll", &DebugHud::ToggleAll)

        .addFunction("GetDefaultStyle", &DebugHud::GetDefaultStyle)
        .addFunction("GetStatsText", &DebugHud::GetStatsText)
        .addFunction("GetModeText", &DebugHud::GetModeText)
        .addFunction("GetProfilerText", &DebugHud::GetProfilerText)
        .addFunction("GetMemoryText", &DebugHud::GetMemoryText)
        .addFunction("GetMode", &DebugHud::GetMode)
        .addFunction("GetProfilerMaxDepth", &DebugHud::GetProfilerMaxDepth)
        .addFunction("GetProfilerInterval", &DebugHud::GetProfilerInterval)
        .addFunction("GetUseRendererStats", &DebugHud::GetUseRendererStats)

        .addOverloadedFunctions("SetAppStats",
            static_cast<void(DebugHud::*)(const String&, const Variant&)>(&DebugHud::SetAppStats),
            static_cast<void(DebugHud::*)(const String&, const String&)>(&DebugHud::SetAppStats))

        .addFunction("ResetAppStats", &DebugHud::ResetAppStats)
        .addFunction("ClearAppStats", &DebugHud::ClearAppStats)

        .addProperty("defaultStyle", &DebugHud::GetDefaultStyle, &DebugHud::SetDefaultStyle)
        .addProperty("statsText", &DebugHud::GetStatsText)
        .addProperty("modeText", &DebugHud::GetModeText)
        .addProperty("profilerText", &DebugHud::GetProfilerText)
        .addProperty("mode", &DebugHud::GetMode, &DebugHud::SetMode)
        .addProperty("profilerMaxDepth", &DebugHud::GetProfilerMaxDepth, &DebugHud::SetProfilerMaxDepth)
        .addProperty("profilerInterval", &DebugHud::GetProfilerInterval, &DebugHud::SetProfilerInterval)
        .addProperty("useRendererStats", &DebugHud::GetUseRendererStats, &DebugHud::SetUseRendererStats)
        );
}
}

