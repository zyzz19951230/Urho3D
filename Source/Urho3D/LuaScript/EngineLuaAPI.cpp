#include "../Engine/Application.h"
#include "../Engine/Console.h"
#include "../Engine/DebugHud.h"
#include "../Engine/Engine.h"
#include "../Engine/EngineEvents.h"

#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterConsole(kaguya::State& lua)
{
    using namespace kaguya;

    // GC is disable for subsystem object
    lua["KConsole"].setClass(UserdataMetatable<Console, Object>()

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

    lua["KDEBUGHUD_SHOW_NONE"] = DEBUGHUD_SHOW_NONE;
    lua["KDEBUGHUD_SHOW_STATS"] = DEBUGHUD_SHOW_STATS;
    lua["KDEBUGHUD_SHOW_MODE"] = DEBUGHUD_SHOW_MODE;
    lua["KDEBUGHUD_SHOW_PROFILER"] = DEBUGHUD_SHOW_PROFILER;
    lua["KDEBUGHUD_SHOW_MEMORY"] = DEBUGHUD_SHOW_MEMORY;
    lua["KDEBUGHUD_SHOW_ALL"] = DEBUGHUD_SHOW_ALL;
    lua["KDEBUGHUD_SHOW_ALL_MEMORY"] = DEBUGHUD_SHOW_ALL_MEMORY;
    lua["KDEBUGHUD_SHOW_EVENTPROFILER"] = DEBUGHUD_SHOW_EVENTPROFILER;

    // GC is disable for subsystem object
    lua["KDebugHud"].setClass(UserdataMetatable<DebugHud, Object>()

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
        .addProperty("memoryText", &DebugHud::GetMemoryText)
        .addProperty("mode", &DebugHud::GetMode, &DebugHud::SetMode)
        .addProperty("profilerMaxDepth", &DebugHud::GetProfilerMaxDepth, &DebugHud::SetProfilerMaxDepth)
        .addProperty("profilerInterval", &DebugHud::GetProfilerInterval, &DebugHud::SetProfilerInterval)
        .addProperty("useRendererStats", &DebugHud::GetUseRendererStats, &DebugHud::SetUseRendererStats)
    );
}


static void RegisterEngine(kaguya::State& lua)
{
    using namespace kaguya;

    // GC is disable for subsystem object
    lua["KEngine"].setClass(UserdataMetatable<Engine, Object>()

        .addFunction("RunFrame", &Engine::RunFrame)
        .addFunction("CreateConsole", &Engine::CreateConsole)
        .addFunction("CreateDebugHud", &Engine::CreateDebugHud)

        .addFunction("SetMinFps", &Engine::SetMinFps)
        .addFunction("SetMaxFps", &Engine::SetMaxFps)
        .addFunction("SetMaxInactiveFps", &Engine::SetMaxInactiveFps)
        .addFunction("SetTimeStepSmoothing", &Engine::SetTimeStepSmoothing)
        .addFunction("SetPauseMinimized", &Engine::SetPauseMinimized)
        .addFunction("SetAutoExit", &Engine::SetAutoExit)
        .addFunction("SetNextTimeStep", &Engine::SetNextTimeStep)

        .addFunction("Exit", &Engine::Exit)

        .addFunction("DumpProfiler", &Engine::DumpProfiler)
        .addFunction("DumpResources", &Engine::DumpResources)
        .addFunction("DumpMemory", &Engine::DumpMemory)

        .addFunction("GetNextTimeStep", &Engine::GetNextTimeStep)
        .addFunction("GetMinFps", &Engine::GetMinFps)
        .addFunction("GetMaxFps", &Engine::GetMaxFps)
        .addFunction("GetMaxInactiveFps", &Engine::GetMaxInactiveFps)
        .addFunction("GetTimeStepSmoothing", &Engine::GetTimeStepSmoothing)
        .addFunction("GetPauseMinimized", &Engine::GetPauseMinimized)
        .addFunction("GetAutoExit", &Engine::GetAutoExit)
        .addFunction("IsInitialized", &Engine::IsInitialized)
        .addFunction("IsExiting", &Engine::IsExiting)
        .addFunction("IsHeadless", &Engine::IsHeadless)

        .addFunction("ApplyFrameLimit", &Engine::ApplyFrameLimit)

        .addProperty("nextTimeStep", &Engine::GetNextTimeStep, &Engine::SetNextTimeStep)
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

static void RegisterEngineEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KE_CONSOLECOMMAND"] = E_CONSOLECOMMAND;
}

void RegisterEngineLuaAPI(kaguya::State& lua)
{
    RegisterConsole(lua);
    RegisterDebugHud(lua);
    RegisterEngine(lua);
    RegisterEngineEvents(lua);

    lua["kengine"] = KGetSubsystem<Engine>();
    lua["KGetEngine"] = KGetSubsystem<Engine>;

    lua["KGetConsole"] = KGetSubsystem<Console>;
    lua["GetDebugHud"] = KGetSubsystem<DebugHud>;
}
}
