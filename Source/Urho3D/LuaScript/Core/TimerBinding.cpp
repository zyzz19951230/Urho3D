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

#include "../../Core/Timer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterTimer(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Time : Object
    lua["Time"].setClass(UserdataMetatable<Time, Object>()

        // [Method] unsigned GetFrameNumber() const
        .addFunction("GetFrameNumber", &Time::GetFrameNumber)
        // [Method] float GetTimeStep() const
        .addFunction("GetTimeStep", &Time::GetTimeStep)
        // [Method] unsigned GetTimerPeriod() const
        .addFunction("GetTimerPeriod", &Time::GetTimerPeriod)
        // [Method] float GetElapsedTime()
        .addFunction("GetElapsedTime", &Time::GetElapsedTime)

        // [StaticMethod] unsigned GetSystemTime()
        .addStaticFunction("GetSystemTime", &Time::GetSystemTime)
        // [StaticMethod] unsigned GetTimeSinceEpoch()
        .addStaticFunction("GetTimeSinceEpoch", &Time::GetTimeSinceEpoch)
        // [StaticMethod] String GetTimeStamp()
        .addStaticFunction("GetTimeStamp", &Time::GetTimeStamp)
        // [StaticMethod] void Sleep(unsigned mSec)
        .addStaticFunction("Sleep", &Time::Sleep)

        // [Property(Readonly)] unsigned frameNumber
        .addProperty("frameNumber", &Time::GetFrameNumber)
        // [Property(Readonly)] float timeStep
        .addProperty("timeStep", &Time::GetTimeStep)
        // [Property(Readonly)] unsigned timerPeriod
        .addProperty("timerPeriod", &Time::GetTimerPeriod)
        // [Property(Readonly)] float elapsedTime
        .addProperty("elapsedTime", &Time::GetElapsedTime)
    );
}
}

