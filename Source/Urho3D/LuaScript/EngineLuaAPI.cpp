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

#include "../Precompiled.h"

#include "../Engine/Application.h"
#include "../Engine/Console.h"
#include "../Engine/DebugHud.h"
#include "../Engine/Engine.h"
#include "../LuaScript/LuaScript.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterConsole(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Console"].setClass(UserdataMetatable<Console, Object>()

        .addFunction("SetDefaultStyle", &Console::SetDefaultStyle)
        .addFunction("SetVisible", &Console::SetVisible)
        .addFunction("Toggle", &Console::Toggle)
        .addFunction("SetAutoVisibleOnError", &Console::SetAutoVisibleOnError)
        .addFunction("SetCommandInterpreter", &Console::SetCommandInterpreter)
        .addFunction("SetNumBufferedRows", &Console::SetNumBufferedRows)
        .addFunction("SetNumRows", &Console::SetNumRows)
        .addFunction("SetNumHistoryRows", &Console::SetNumHistoryRows)
        .addFunction("SetFocusOnShow", &Console::SetFocusOnShow)
        .addFunction("UpdateElements", &Console::UpdateElements)

        .addFunction("GetDefaultStyle", &Console::GetDefaultStyle)
        .addFunction("GetBackground", &Console::GetBackground)
        .addFunction("GetLineEdit", &Console::GetLineEdit)
        .addFunction("GetCloseButton", &Console::GetCloseButton)
        .addFunction("IsVisible", &Console::IsVisible)
        .addFunction("IsAutoVisibleOnError", &Console::IsAutoVisibleOnError)
        .addFunction("GetCommandInterpreter", &Console::GetCommandInterpreter)
        .addFunction("GetNumBufferedRows", &Console::GetNumBufferedRows)
        .addFunction("GetNumRows", &Console::GetNumRows)
        .addFunction("CopySelectedRows", &Console::CopySelectedRows)
        .addFunction("GetNumHistoryRows", &Console::GetNumHistoryRows)
        .addFunction("GetHistoryPosition", &Console::GetHistoryPosition)
        .addFunction("GetHistoryRow", &Console::GetHistoryRow)
        .addFunction("GetFocusOnShow", &Console::GetFocusOnShow)

        .addProperty("defaultStyle", &Console::GetDefaultStyle, &Console::SetDefaultStyle)
        .addProperty("background", &Console::GetBackground)
        .addProperty("lineEdit", &Console::GetLineEdit)
        .addProperty("closeButton", &Console::GetCloseButton)
        .addProperty("visible", &Console::IsVisible, &Console::SetVisible)
        .addProperty("autoVisibleOnError", &Console::IsAutoVisibleOnError, &Console::SetAutoVisibleOnError)
        .addProperty("commandInterpreter", &Console::GetCommandInterpreter, &Console::SetCommandInterpreter)
        .addProperty("numBufferedRows", &Console::GetNumBufferedRows, &Console::SetNumBufferedRows)
        .addProperty("numRows", &Console::GetNumRows, &Console::SetNumRows)
        .addProperty("numHistoryRows", &Console::GetNumHistoryRows, &Console::SetNumHistoryRows)
        .addProperty("historyPosition", &Console::GetHistoryPosition)
        .addProperty("focusOnShow", &Console::GetFocusOnShow, &Console::SetFocusOnShow)
        );
}

static void RegisterDebugHud(kaguya::State& lua)
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

static Console* EngineCreateConsole(Engine* self)
{
    Console* console = self->CreateConsole();

    LuaScript* luaScript = GetSubsystem<LuaScript>();
    kaguya::State lua(luaScript->GetState());
    lua["console"] = console;

    return console;
}

static DebugHud* EngineCreateDebugHud(Engine* self)
{
    DebugHud* debugHud = self->CreateDebugHud();

    LuaScript* luaScript = GetSubsystem<LuaScript>();
    kaguya::State lua(luaScript->GetState());
    lua["debugHud"] = debugHud;

    return debugHud;
}

static void EngineDumpResources0(Engine* self)
{
    self->DumpResources();
}

static void EngineDumpResources1(Engine* self, bool dumpFileName)
{
    self->DumpResources(dumpFileName);
}

static void RegisterEngine(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Engine"].setClass(UserdataMetatable<Engine, Object>()

        .addFunction("RunFrame", &Engine::RunFrame)

        .addStaticFunction("CreateConsole", &EngineCreateConsole)
        .addStaticFunction("CreateDebugHud", &EngineCreateDebugHud)

        .addFunction("SetMinFps", &Engine::SetMinFps)
        .addFunction("SetMaxFps", &Engine::SetMaxFps)
        .addFunction("SetMaxInactiveFps", &Engine::SetMaxInactiveFps)
        .addFunction("SetTimeStepSmoothing", &Engine::SetTimeStepSmoothing)
        .addFunction("SetPauseMinimized", &Engine::SetPauseMinimized)
        .addFunction("SetAutoExit", &Engine::SetAutoExit)
        .addFunction("SetNextTimeStep", &Engine::SetNextTimeStep)
        .addFunction("Exit", &Engine::Exit)
        .addFunction("DumpProfiler", &Engine::DumpProfiler)
        ADD_OVERLOADED_FUNCTIONS_2(Engine, DumpResources)
        .addFunction("DumpMemory", &Engine::DumpMemory)

        .addFunction("GetMinFps", &Engine::GetMinFps)
        .addFunction("GetMaxFps", &Engine::GetMaxFps)
        .addFunction("GetMaxInactiveFps", &Engine::GetMaxInactiveFps)
        .addFunction("GetTimeStepSmoothing", &Engine::GetTimeStepSmoothing)
        .addFunction("GetPauseMinimized", &Engine::GetPauseMinimized)
        .addFunction("GetAutoExit", &Engine::GetAutoExit)
        .addFunction("IsInitialized", &Engine::IsInitialized)
        .addFunction("IsExiting", &Engine::IsExiting)
        .addFunction("IsHeadless", &Engine::IsHeadless)

        .addProperty("minFps", &Engine::GetMinFps, &Engine::SetMinFps)
        .addProperty("maxFps", &Engine::GetMaxFps, &Engine::SetMaxFps)
        .addProperty("maxInactiveFps", &Engine::GetMaxInactiveFps, &Engine::SetMaxInactiveFps)
        .addProperty("timeStepSmoothing", &Engine::GetTimeStepSmoothing, &Engine::SetTimeStepSmoothing)
        .addProperty("pauseMinimized", &Engine::GetPauseMinimized, &Engine::SetPauseMinimized)
        .addProperty("autoExit", &Engine::GetAutoExit, &Engine::SetAutoExit)
        .addProperty("initialized", &Engine::IsInitialized)
        .addProperty("exiting", &Engine::IsExiting)
        .addProperty("headless", &Engine::IsHeadless)
        );
}

void RegisterEngineLuaAPI(kaguya::State& lua)
{
    RegisterConsole(lua);
    RegisterDebugHud(lua);
    RegisterEngine(lua);

    lua["engine"] = GetSubsystem<Engine>();
    lua["GetEngine"] = GetSubsystem<Engine>;

    Console* console = GetSubsystem<Console>();
    if (console)
        lua["console"] = console;
    
    lua["GetConsole"] = GetSubsystem<Console>;

    DebugHud* debugHud = GetSubsystem<DebugHud>();
    if (debugHud)
        lua["debugHud"] = debugHud;

    lua["GetDebugHud"] = GetSubsystem<DebugHud>;
}
}
