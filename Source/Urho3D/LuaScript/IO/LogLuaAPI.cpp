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

#include "../../IO/Log.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void LogWriteRaw0(Log* self, const String& message)
{
    self->WriteRaw(message);
}

static void LogWriteRaw1(Log* self, const String& message, bool error)
{
    self->WriteRaw(message, error);
}

void RegisterLog(kaguya::State& lua)
{
    using namespace kaguya;

    lua["LOG_RAW"] = LOG_RAW;
    lua["LOG_DEBUG"] = LOG_DEBUG;
    lua["LOG_INFO"] = LOG_INFO;
    lua["LOG_WARNING"] = LOG_WARNING;
    lua["LOG_ERROR"] = LOG_ERROR;
    lua["LOG_NONE"] = LOG_NONE;

    lua["Log"].setClass(UserdataMetatable<Log, Object>()

        .addFunction("Open", &Log::Open)
        .addFunction("Close", &Log::Close)

        .addFunction("SetLevel", &Log::SetLevel)
        .addFunction("SetTimeStamp", &Log::SetTimeStamp)
        .addFunction("SetQuiet", &Log::SetQuiet)

        .addFunction("GetLevel", &Log::GetLevel)
        .addFunction("GetTimeStamp", &Log::GetTimeStamp)
        .addFunction("GetLastMessage", &Log::GetLastMessage)
        .addFunction("IsQuiet", &Log::IsQuiet)

        .addStaticFunction("Write", &Log::Write)
        ADD_OVERLOADED_FUNCTIONS_2(Log, WriteRaw)

        .addProperty("level", &Log::GetLevel, &Log::SetLevel)
        .addProperty("timeStamp", &Log::GetTimeStamp, &Log::SetTimeStamp)
        .addProperty("quiet", &Log::IsQuiet, &Log::SetQuiet)
        );
}
}

