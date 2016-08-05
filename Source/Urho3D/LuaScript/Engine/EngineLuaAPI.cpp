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
        
        .addFunction("DumpResources", EngineDumpResources())

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
}

