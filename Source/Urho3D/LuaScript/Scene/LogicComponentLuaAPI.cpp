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

#include "../../Scene/LogicComponent.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterLogicComponent(kaguya::State& lua)
{
    using namespace kaguya;

    lua["USE_UPDATE"] = USE_UPDATE;
    lua["USE_POSTUPDATE"] = USE_POSTUPDATE;
    lua["USE_FIXEDUPDATE"] = USE_FIXEDUPDATE;
    lua["USE_FIXEDPOSTUPDATE"] = USE_FIXEDPOSTUPDATE;

    lua["LogicComponent"].setClass(UserdataMetatable<LogicComponent, Component>()
        .addStaticFunction("new", &CreateObject<LogicComponent>)

        .addFunction("SetUpdateEventMask", &LogicComponent::SetUpdateEventMask)
        .addFunction("GetUpdateEventMask", &LogicComponent::GetUpdateEventMask)
        .addFunction("IsDelayedStartCalled", &LogicComponent::IsDelayedStartCalled)

        .addProperty("updateEventMask", &LogicComponent::GetUpdateEventMask, &LogicComponent::SetUpdateEventMask)
        .addProperty("delayedStartCalled", &LogicComponent::IsDelayedStartCalled)
        );
}
}

