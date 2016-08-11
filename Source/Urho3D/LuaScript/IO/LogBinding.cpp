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

    // [Constant] int LOG_RAW
    lua["LOG_RAW"] = LOG_RAW;
    // [Constant] int LOG_DEBUG
    lua["LOG_DEBUG"] = LOG_DEBUG;
    // [Constant] int LOG_INFO
    lua["LOG_INFO"] = LOG_INFO;
    // [Constant] int LOG_WARNING
    lua["LOG_WARNING"] = LOG_WARNING;
    // [Constant] int LOG_ERROR
    lua["LOG_ERROR"] = LOG_ERROR;
    // [Constant] int LOG_NONE
    lua["LOG_NONE"] = LOG_NONE;

    // [Class] Log : Object
    lua["Log"].setClass(UserdataMetatable<Log, Object>()

        // [Method] void Open(const String& fileName)
        .addFunction("Open", &Log::Open)
        // [Method] void Close()
        .addFunction("Close", &Log::Close)

        // [Method] void SetLevel(int level)
        .addFunction("SetLevel", &Log::SetLevel)
        // [Method] void SetTimeStamp(bool enable)
        .addFunction("SetTimeStamp", &Log::SetTimeStamp)
        // [Method] void SetQuiet(bool quiet)
        .addFunction("SetQuiet", &Log::SetQuiet)

        // [Method] int GetLevel() const
        .addFunction("GetLevel", &Log::GetLevel)
        // [Method] bool GetTimeStamp() const
        .addFunction("GetTimeStamp", &Log::GetTimeStamp)
        // [Method] String GetLastMessage() const
        .addFunction("GetLastMessage", &Log::GetLastMessage)
        // [Method] bool IsQuiet() const
        .addFunction("IsQuiet", &Log::IsQuiet)

        // [StaticMethod] void Write(int level, const String& message)
        .addStaticFunction("Write", &Log::Write)
        // [StaticMethod] void WriteRaw(const String& message, bool error = false)
        ADD_OVERLOADED_FUNCTIONS_2(Log, WriteRaw)

        // [Property] int level
        .addProperty("level", &Log::GetLevel, &Log::SetLevel)
        // [Property] bool timeStamp
        .addProperty("timeStamp", &Log::GetTimeStamp, &Log::SetTimeStamp)
        // [Property] bool quiet
        .addProperty("quiet", &Log::IsQuiet, &Log::SetQuiet)
        );

    // [Variable] Log* log
    lua["log"] = GetSubsystem<Log>();
    // [Function] Log* GetLog()
    lua["GetLog"] = static_cast<Log*(*)()>(&GetSubsystem<Log>);
}
}

