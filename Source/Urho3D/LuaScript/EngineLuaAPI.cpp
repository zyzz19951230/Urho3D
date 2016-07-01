// #include "../Engine/Application.h"
// #include "../Engine/Console.h"
// #include "../Engine/DebugHud.h"
// #include "../Engine/Engine.h"
// #include "../Engine/EngineEvents.h"

// #include "../LuaScript/LuaScriptUtils.h"

// #include <kaguya.hpp>

// namespace Urho3D
// {

// static void RegisterApplication(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KApplication"].setClass(UserdataMetatable<Application, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Application>)
//         .addStaticFunction("__gc", &KReleaseObject<Application>)

//         .addFunction("GetType", &Application::GetType)
//         .addFunction("GetTypeName", &Application::GetTypeName)
//         .addFunction("GetTypeInfo", &Application::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Application::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Application::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Application::GetTypeInfoStatic)
//         .addFunction("Setup", &Application::Setup)
//         .addFunction("Start", &Application::Start)
//         .addFunction("Stop", &Application::Stop)
//         .addFunction("Run", &Application::Run)
//         .addFunction("ErrorExit", &Application::ErrorExit)

//         .addProperty("type", &Application::GetType)
//         .addProperty("typeName", &Application::GetTypeName)
//         .addProperty("typeInfo", &Application::GetTypeInfo)
//     );
// }

// static void RegisterConsole(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KConsole"].setClass(UserdataMetatable<Console, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Console>)
//         .addStaticFunction("__gc", &KReleaseObject<Console>)

//         .addFunction("GetType", &Console::GetType)
//         .addFunction("GetTypeName", &Console::GetTypeName)
//         .addFunction("GetTypeInfo", &Console::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Console::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Console::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Console::GetTypeInfoStatic)
//         .addFunction("SetDefaultStyle", &Console::SetDefaultStyle)
//         .addFunction("SetVisible", &Console::SetVisible)
//         .addFunction("Toggle", &Console::Toggle)
//         .addFunction("SetAutoVisibleOnError", &Console::SetAutoVisibleOnError)
//         .addFunction("SetCommandInterpreter", &Console::SetCommandInterpreter)
//         .addFunction("SetNumBufferedRows", &Console::SetNumBufferedRows)
//         .addFunction("SetNumRows", &Console::SetNumRows)
//         .addFunction("SetNumHistoryRows", &Console::SetNumHistoryRows)
//         .addFunction("SetFocusOnShow", &Console::SetFocusOnShow)
//         .addFunction("UpdateElements", &Console::UpdateElements)
//         .addFunction("GetDefaultStyle", &Console::GetDefaultStyle)
//         .addFunction("GetBackground", &Console::GetBackground)
//         .addFunction("GetLineEdit", &Console::GetLineEdit)
//         .addFunction("GetCloseButton", &Console::GetCloseButton)
//         .addFunction("IsVisible", &Console::IsVisible)
//         .addFunction("IsAutoVisibleOnError", &Console::IsAutoVisibleOnError)
//         .addFunction("GetCommandInterpreter", &Console::GetCommandInterpreter)
//         .addFunction("GetNumBufferedRows", &Console::GetNumBufferedRows)
//         .addFunction("GetNumRows", &Console::GetNumRows)
//         .addFunction("CopySelectedRows", &Console::CopySelectedRows)
//         .addFunction("GetNumHistoryRows", &Console::GetNumHistoryRows)
//         .addFunction("GetHistoryPosition", &Console::GetHistoryPosition)
//         .addFunction("GetHistoryRow", &Console::GetHistoryRow)
//         .addFunction("GetFocusOnShow", &Console::GetFocusOnShow)

//         .addProperty("type", &Console::GetType)
//         .addProperty("typeName", &Console::GetTypeName)
//         .addProperty("typeInfo", &Console::GetTypeInfo)
//         .addProperty("defaultStyle", &Console::GetDefaultStyle, &Console::SetDefaultStyle)
//         .addProperty("background", &Console::GetBackground)
//         .addProperty("lineEdit", &Console::GetLineEdit)
//         .addProperty("closeButton", &Console::GetCloseButton)
//         .addProperty("visible", &Console::IsVisible, &Console::SetVisible)
//         .addProperty("autoVisibleOnError", &Console::IsAutoVisibleOnError, &Console::SetAutoVisibleOnError)
//         .addProperty("commandInterpreter", &Console::GetCommandInterpreter, &Console::SetCommandInterpreter)
//         .addProperty("numBufferedRows", &Console::GetNumBufferedRows, &Console::SetNumBufferedRows)
//         .addProperty("numRows", &Console::GetNumRows, &Console::SetNumRows)
//         .addProperty("numHistoryRows", &Console::GetNumHistoryRows, &Console::SetNumHistoryRows)
//         .addProperty("historyPosition", &Console::GetHistoryPosition)
//         .addProperty("focusOnShow", &Console::GetFocusOnShow, &Console::SetFocusOnShow)
//     );
// }

// static void RegisterDebugHud(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KDEBUGHUD_SHOW_NONE"] = DEBUGHUD_SHOW_NONE;
//     lua["KDEBUGHUD_SHOW_STATS"] = DEBUGHUD_SHOW_STATS;
//     lua["KDEBUGHUD_SHOW_MODE"] = DEBUGHUD_SHOW_MODE;
//     lua["KDEBUGHUD_SHOW_PROFILER"] = DEBUGHUD_SHOW_PROFILER;
//     lua["KDEBUGHUD_SHOW_MEMORY"] = DEBUGHUD_SHOW_MEMORY;
//     lua["KDEBUGHUD_SHOW_ALL"] = DEBUGHUD_SHOW_ALL;
//     lua["KDEBUGHUD_SHOW_ALL_MEMORY"] = DEBUGHUD_SHOW_ALL_MEMORY;
//     lua["KDEBUGHUD_SHOW_EVENTPROFILER"] = DEBUGHUD_SHOW_EVENTPROFILER;
//     lua["KDebugHud"].setClass(UserdataMetatable<DebugHud, Object>(false)
//         .addStaticFunction("new", &KCreateObject<DebugHud>)
//         .addStaticFunction("__gc", &KReleaseObject<DebugHud>)

//         .addFunction("GetType", &DebugHud::GetType)
//         .addFunction("GetTypeName", &DebugHud::GetTypeName)
//         .addFunction("GetTypeInfo", &DebugHud::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &DebugHud::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &DebugHud::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &DebugHud::GetTypeInfoStatic)
//         .addFunction("Update", &DebugHud::Update)
//         .addFunction("SetDefaultStyle", &DebugHud::SetDefaultStyle)
//         .addFunction("SetMode", &DebugHud::SetMode)
//         .addFunction("SetProfilerMaxDepth", &DebugHud::SetProfilerMaxDepth)
//         .addFunction("SetProfilerInterval", &DebugHud::SetProfilerInterval)
//         .addFunction("SetUseRendererStats", &DebugHud::SetUseRendererStats)
//         .addFunction("Toggle", &DebugHud::Toggle)
//         .addFunction("ToggleAll", &DebugHud::ToggleAll)
//         .addFunction("GetDefaultStyle", &DebugHud::GetDefaultStyle)
//         .addFunction("GetStatsText", &DebugHud::GetStatsText)
//         .addFunction("GetModeText", &DebugHud::GetModeText)
//         .addFunction("GetProfilerText", &DebugHud::GetProfilerText)
//         .addFunction("GetMemoryText", &DebugHud::GetMemoryText)
//         .addFunction("GetMode", &DebugHud::GetMode)
//         .addFunction("GetProfilerMaxDepth", &DebugHud::GetProfilerMaxDepth)
//         .addFunction("GetProfilerInterval", &DebugHud::GetProfilerInterval)
//         .addFunction("GetUseRendererStats", &DebugHud::GetUseRendererStats)

//         .addOverloadedFunctions("SetAppStats",
//             static_cast<void(DebugHud::*)(const String&, const Variant&)>(&DebugHud::SetAppStats),
//             static_cast<void(DebugHud::*)(const String&, const String&)>(&DebugHud::SetAppStats))

//         .addFunction("ResetAppStats", &DebugHud::ResetAppStats)
//         .addFunction("ClearAppStats", &DebugHud::ClearAppStats)

//         .addProperty("type", &DebugHud::GetType)
//         .addProperty("typeName", &DebugHud::GetTypeName)
//         .addProperty("typeInfo", &DebugHud::GetTypeInfo)
//         .addProperty("defaultStyle", &DebugHud::GetDefaultStyle, &DebugHud::SetDefaultStyle)
//         .addProperty("statsText", &DebugHud::GetStatsText)
//         .addProperty("modeText", &DebugHud::GetModeText)
//         .addProperty("profilerText", &DebugHud::GetProfilerText)
//         .addProperty("memoryText", &DebugHud::GetMemoryText)
//         .addProperty("mode", &DebugHud::GetMode, &DebugHud::SetMode)
//         .addProperty("profilerMaxDepth", &DebugHud::GetProfilerMaxDepth, &DebugHud::SetProfilerMaxDepth)
//         .addProperty("profilerInterval", &DebugHud::GetProfilerInterval, &DebugHud::SetProfilerInterval)
//         .addProperty("useRendererStats", &DebugHud::GetUseRendererStats, &DebugHud::SetUseRendererStats)
//     );
// }

// static void RegisterEngine(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KEngine"].setClass(UserdataMetatable<Engine, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Engine>)
//         .addStaticFunction("__gc", &KReleaseObject<Engine>)

//         .addFunction("GetType", &Engine::GetType)
//         .addFunction("GetTypeName", &Engine::GetTypeName)
//         .addFunction("GetTypeInfo", &Engine::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Engine::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Engine::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Engine::GetTypeInfoStatic)
//         .addFunction("Initialize", &Engine::Initialize)
//         .addFunction("RunFrame", &Engine::RunFrame)
//         .addFunction("CreateConsole", &Engine::CreateConsole)
//         .addFunction("CreateDebugHud", &Engine::CreateDebugHud)
//         .addFunction("SetMinFps", &Engine::SetMinFps)
//         .addFunction("SetMaxFps", &Engine::SetMaxFps)
//         .addFunction("SetMaxInactiveFps", &Engine::SetMaxInactiveFps)
//         .addFunction("SetTimeStepSmoothing", &Engine::SetTimeStepSmoothing)
//         .addFunction("SetPauseMinimized", &Engine::SetPauseMinimized)
//         .addFunction("SetAutoExit", &Engine::SetAutoExit)
//         .addFunction("SetNextTimeStep", &Engine::SetNextTimeStep)
//         .addFunction("Exit", &Engine::Exit)
//         .addFunction("DumpProfiler", &Engine::DumpProfiler)
//         .addFunction("DumpResources", &Engine::DumpResources)
//         .addFunction("DumpMemory", &Engine::DumpMemory)
//         .addFunction("GetNextTimeStep", &Engine::GetNextTimeStep)
//         .addFunction("GetMinFps", &Engine::GetMinFps)
//         .addFunction("GetMaxFps", &Engine::GetMaxFps)
//         .addFunction("GetMaxInactiveFps", &Engine::GetMaxInactiveFps)
//         .addFunction("GetTimeStepSmoothing", &Engine::GetTimeStepSmoothing)
//         .addFunction("GetPauseMinimized", &Engine::GetPauseMinimized)
//         .addFunction("GetAutoExit", &Engine::GetAutoExit)
//         .addFunction("IsInitialized", &Engine::IsInitialized)
//         .addFunction("IsExiting", &Engine::IsExiting)
//         .addFunction("IsHeadless", &Engine::IsHeadless)
//         .addFunction("Update", &Engine::Update)
//         .addFunction("Render", &Engine::Render)
//         .addFunction("ApplyFrameLimit", &Engine::ApplyFrameLimit)
//         .addStaticFunction("ParseParameters", &Engine::ParseParameters)
//         .addStaticFunction("HasParameter", &Engine::HasParameter)
//         .addStaticFunction("GetParameter", &Engine::GetParameter)

//         .addProperty("type", &Engine::GetType)
//         .addProperty("typeName", &Engine::GetTypeName)
//         .addProperty("typeInfo", &Engine::GetTypeInfo)
//         .addProperty("nextTimeStep", &Engine::GetNextTimeStep, &Engine::SetNextTimeStep)
//         .addProperty("minFps", &Engine::GetMinFps, &Engine::SetMinFps)
//         .addProperty("maxFps", &Engine::GetMaxFps, &Engine::SetMaxFps)
//         .addProperty("maxInactiveFps", &Engine::GetMaxInactiveFps, &Engine::SetMaxInactiveFps)
//         .addProperty("timeStepSmoothing", &Engine::GetTimeStepSmoothing, &Engine::SetTimeStepSmoothing)
//         .addProperty("pauseMinimized", &Engine::GetPauseMinimized, &Engine::SetPauseMinimized)
//         .addProperty("autoExit", &Engine::GetAutoExit, &Engine::SetAutoExit)
//         .addProperty("initialized", &Engine::IsInitialized)
//         .addProperty("exiting", &Engine::IsExiting)
//         .addProperty("headless", &Engine::IsHeadless)
//     );
// }

// static void RegisterEngineEvents(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KE_CONSOLECOMMAND"] = E_CONSOLECOMMAND;
// }

// void RegisterEngineLuaAPI(kaguya::State& lua)
// {
//     RegisterApplication(lua);
//     RegisterConsole(lua);
//     RegisterDebugHud(lua);
//     RegisterEngine(lua);
//     RegisterEngineEvents(lua);
// }
// }
