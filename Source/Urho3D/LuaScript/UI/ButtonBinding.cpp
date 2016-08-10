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

    // [Class] Button : BorderImage
    lua["Button"].setClass(UserdataMetatable<Button, BorderImage>()
        // [Constructor] Button()
        .addStaticFunction("new", &CreateObject<Button>)

        .addOverloadedFunctions("SetPressedOffset",
            // [Method] void SetPressedOffset(const IntVector2& offset)
            static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedOffset),
            // [Method] void SetPressedOffset(int x, int y)
            static_cast<void(Button::*)(int, int)>(&Button::SetPressedOffset))

        .addOverloadedFunctions("SetPressedChildOffset",
            // [Method] void SetPressedChildOffset(const IntVector2& offset)
            static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedChildOffset),
            // [Method] void SetPressedChildOffset(int x, int y)
            static_cast<void(Button::*)(int, int)>(&Button::SetPressedChildOffset))

        // [Method] void SetRepeat(float delay, float rate)
        .addFunction("SetRepeat", &Button::SetRepeat)
        // [Method] void SetRepeatDelay(float delay)
        .addFunction("SetRepeatDelay", &Button::SetRepeatDelay)
        // [Method] void SetRepeatRate(float rate)
        .addFunction("SetRepeatRate", &Button::SetRepeatRate)

        // [Method] const IntVector2& GetPressedOffset() const
        .addFunction("GetPressedOffset", &Button::GetPressedOffset)
        // [Method] const IntVector2& GetPressedChildOffset() const
        .addFunction("GetPressedChildOffset", &Button::GetPressedChildOffset)
        // [Method] float GetRepeatDelay() const
        .addFunction("GetRepeatDelay", &Button::GetRepeatDelay)
        // [Method] float GetRepeatRate() const
        .addFunction("GetRepeatRate", &Button::GetRepeatRate)
        // [Method] bool IsPressed() const
        .addFunction("IsPressed", &Button::IsPressed)

        // [Property] const IntVector2& pressedOffset
        .addProperty("pressedOffset", &Button::GetPressedOffset, static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedOffset))
        // [Property] const IntVector2& pressedChildOffset
        .addProperty("pressedChildOffset", &Button::GetPressedChildOffset, static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedChildOffset))
        // [Property] float repeatDelay
        .addProperty("repeatDelay", &Button::GetRepeatDelay, &Button::SetRepeatDelay)
        // [Property] float repeatRate
        .addProperty("repeatRate", &Button::GetRepeatRate, &Button::SetRepeatRate)
        // [Property(Readonly)] bool pressed
        .addProperty("pressed", &Button::IsPressed)
        );
}
}

