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

    // [Constant] unsigned char USE_UPDATE
    lua["USE_UPDATE"] = USE_UPDATE;
    // [Constant] unsigned char USE_POSTUPDATE
    lua["USE_POSTUPDATE"] = USE_POSTUPDATE;
    // [Constant] unsigned char USE_FIXEDUPDATE
    lua["USE_FIXEDUPDATE"] = USE_FIXEDUPDATE;
    // [Constant] unsigned char USE_FIXEDPOSTUPDATE
    lua["USE_FIXEDPOSTUPDATE"] = USE_FIXEDPOSTUPDATE;

    // [Class] LogicComponent : Component
    lua["LogicComponent"].setClass(UserdataMetatable<LogicComponent, Component>()
        // [Constructor] LogicComponent()
        .addStaticFunction("new", &CreateObject<LogicComponent>)

        // [Method] void SetUpdateEventMask(unsigned char mask)
        .addFunction("SetUpdateEventMask", &LogicComponent::SetUpdateEventMask)
        // [Method] unsigned char GetUpdateEventMask() const
        .addFunction("GetUpdateEventMask", &LogicComponent::GetUpdateEventMask)
        // [Method] bool IsDelayedStartCalled() const
        .addFunction("IsDelayedStartCalled", &LogicComponent::IsDelayedStartCalled)

        // [Property] unsigned char updateEventMask
        .addProperty("updateEventMask", &LogicComponent::GetUpdateEventMask, &LogicComponent::SetUpdateEventMask)
        // [Property(Readonly)] bool delayedStartCalled
        .addProperty("delayedStartCalled", &LogicComponent::IsDelayedStartCalled)
        );
}
}

