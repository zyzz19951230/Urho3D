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

#include "../../Engine/Console.h"
#include "../../Engine/DebugHud.h"
#include "../../Engine/Engine.h"
#include "../../LuaScript/LuaScript.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

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

KAGUYA_MEMBER_FUNCTION_OVERLOADS(EngineDumpResources, Engine, DumpResources, 0, 1);

void RegisterEngine(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Engine : Object
    lua["Engine"].setClass(UserdataMetatable<Engine, Object>()

        // [Method] void RunFrame()
        .addFunction("RunFrame", &Engine::RunFrame)

        // [Method] Console* CreateConsole()
        .addStaticFunction("CreateConsole", &EngineCreateConsole)
        // [Method] DebugHud* CreateDebugHud()
        .addStaticFunction("CreateDebugHud", &EngineCreateDebugHud)

        // [Method] void SetMinFps(int fps)
        .addFunction("SetMinFps", &Engine::SetMinFps)
        // [Method] void SetMaxFps(int fps)
        .addFunction("SetMaxFps", &Engine::SetMaxFps)
        // [Method] void SetMaxInactiveFps(int fps)
        .addFunction("SetMaxInactiveFps", &Engine::SetMaxInactiveFps)
        // [Method] void SetTimeStepSmoothing(int frames)
        .addFunction("SetTimeStepSmoothing", &Engine::SetTimeStepSmoothing)
        // [Method] void SetPauseMinimized(bool enable)
        .addFunction("SetPauseMinimized", &Engine::SetPauseMinimized)
        // [Method] void SetAutoExit(bool enable)
        .addFunction("SetAutoExit", &Engine::SetAutoExit)
        // [Method] void SetNextTimeStep(float seconds)
        .addFunction("SetNextTimeStep", &Engine::SetNextTimeStep)
        // [Method] void Exit()
        .addFunction("Exit", &Engine::Exit)
        // [Method] void DumpProfiler()
        .addFunction("DumpProfiler", &Engine::DumpProfiler)
        
        // [Method] void DumpResources(bool dumpFileName = false)
        .addFunction("DumpResources", EngineDumpResources())

        // [Method] void DumpMemory()
        .addFunction("DumpMemory", &Engine::DumpMemory)

        // [Method] int GetMinFps() const
        .addFunction("GetMinFps", &Engine::GetMinFps)
        // [Method] int GetMaxFps() const
        .addFunction("GetMaxFps", &Engine::GetMaxFps)
        // [Method] int GetMaxInactiveFps() const
        .addFunction("GetMaxInactiveFps", &Engine::GetMaxInactiveFps)
        // [Method] int GetTimeStepSmoothing() const
        .addFunction("GetTimeStepSmoothing", &Engine::GetTimeStepSmoothing)
        // [Method] bool GetPauseMinimized() const
        .addFunction("GetPauseMinimized", &Engine::GetPauseMinimized)
        // [Method] bool GetAutoExit() const
        .addFunction("GetAutoExit", &Engine::GetAutoExit)
        // [Method] bool IsInitialized() const
        .addFunction("IsInitialized", &Engine::IsInitialized)
        // [Method] bool IsExiting() const
        .addFunction("IsExiting", &Engine::IsExiting)
        // [Method] bool IsHeadless() const
        .addFunction("IsHeadless", &Engine::IsHeadless)

        // [Property] int minFps
        .addProperty("minFps", &Engine::GetMinFps, &Engine::SetMinFps)
        // [Property] int maxFps
        .addProperty("maxFps", &Engine::GetMaxFps, &Engine::SetMaxFps)
        // [Property] int maxInactiveFps
        .addProperty("maxInactiveFps", &Engine::GetMaxInactiveFps, &Engine::SetMaxInactiveFps)
        // [Property] int timeStepSmoothing
        .addProperty("timeStepSmoothing", &Engine::GetTimeStepSmoothing, &Engine::SetTimeStepSmoothing)
        // [Property] bool pauseMinimized
        .addProperty("pauseMinimized", &Engine::GetPauseMinimized, &Engine::SetPauseMinimized)
        // [Property] bool autoExit
        .addProperty("autoExit", &Engine::GetAutoExit, &Engine::SetAutoExit)
        // [Property(Readonly)] bool initialized
        .addProperty("initialized", &Engine::IsInitialized)
        // [Property(Readonly)] bool exiting
        .addProperty("exiting", &Engine::IsExiting)
        // [Property(Readonly)] bool headless
        .addProperty("headless", &Engine::IsHeadless)
        );


    // [Variable] Engine* engine
    lua["engine"] = GetSubsystem<Engine>();
    // [Function] Engine* GetEngine()
    lua["GetEngine"] = static_cast<Engine*(*)()>(&GetSubsystem<Engine>);

    Console* console = GetSubsystem<Console>();
    if (console)
        // [Variable] Console* console
        lua["console"] = console;
    
    // [Function] Console* GetConsole()
    lua["GetConsole"] = static_cast<Console*(*)()>(&GetSubsystem<Console>);

    DebugHud* debugHud = GetSubsystem<DebugHud>();
    if (debugHud)
        // [Variable] DebugHud* debugHud
        lua["debugHud"] = debugHud;

    // [Function] DebugHud* GetDebugHud()
    lua["GetDebugHud"] = static_cast<DebugHud*(*)()>(&GetSubsystem<DebugHud>);
}
}

