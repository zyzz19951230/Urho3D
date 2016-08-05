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

#include "../../UI/Button.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterButton(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Button"].setClass(UserdataMetatable<Button, BorderImage>()
        .addStaticFunction("new", &CreateObject<Button>)

        .addOverloadedFunctions("SetPressedOffset",
            static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedOffset),
            static_cast<void(Button::*)(int, int)>(&Button::SetPressedOffset))

        .addOverloadedFunctions("SetPressedChildOffset",
            static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedChildOffset),
            static_cast<void(Button::*)(int, int)>(&Button::SetPressedChildOffset))

        .addFunction("SetRepeat", &Button::SetRepeat)
        .addFunction("SetRepeatDelay", &Button::SetRepeatDelay)
        .addFunction("SetRepeatRate", &Button::SetRepeatRate)

        .addFunction("GetPressedOffset", &Button::GetPressedOffset)
        .addFunction("GetPressedChildOffset", &Button::GetPressedChildOffset)
        .addFunction("GetRepeatDelay", &Button::GetRepeatDelay)
        .addFunction("GetRepeatRate", &Button::GetRepeatRate)
        .addFunction("IsPressed", &Button::IsPressed)

        .addProperty("pressedOffset", &Button::GetPressedOffset, static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedOffset))
        .addProperty("pressedChildOffset", &Button::GetPressedChildOffset, static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedChildOffset))
        .addProperty("repeatDelay", &Button::GetRepeatDelay, &Button::SetRepeatDelay)
        .addProperty("repeatRate", &Button::GetRepeatRate, &Button::SetRepeatRate)
        .addProperty("pressed", &Button::IsPressed)
        );
}
}

