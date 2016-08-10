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

#include "../../Core/Context.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern Context* globalContext;

static Context* GlobalGetContext()
{
    return globalContext;
}

static SharedPtr<Object> GlobalGetEventSender()
{
    return SharedPtr<Object>(globalContext->GetEventSender());
}

void RegisterContext(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Context : RefCounted
    lua["Context"].setClass(UserdataMetatable<Context, RefCounted>()

        // [Method] Object* GetEventSender() const
        .addFunction("GetEventSender", &Context::GetEventSender)
        // [Method] EventHandler* GetEventHandler() const
        .addFunction("GetEventHandler", &Context::GetEventHandler)
        // [Method] const String& GetTypeName(StringHash objectType) const
        .addFunction("GetTypeName", &Context::GetTypeName)

        // [Property(ReadOnly)] Object* eventSender
        .addProperty("eventSender", &Context::GetEventSender)
        // [Property(ReadOnly)] EventHandler* eventHandler
        .addProperty("eventHandler", &Context::GetEventHandler)
    );

    // [Variable] Context* context
    lua["context"] = globalContext;
    // [Function] Context* GetContext()
    lua["GetContext"] = GlobalGetContext();

    // [Function] SharedPtr<Object> GetEventSender()
    lua["GetEventSender"] = function(GlobalGetEventSender);
}
}

