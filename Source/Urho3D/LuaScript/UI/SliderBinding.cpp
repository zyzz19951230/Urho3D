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

#include "../../UI/Slider.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSlider(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Slider : BorderImage
    lua["Slider"].setClass(UserdataMetatable<Slider, BorderImage>()
        // [Constructor] Slider()
        .addStaticFunction("new", &CreateObject<Slider>)

        // [Method] void SetOrientation(Orientation orientation)
        .addFunction("SetOrientation", &Slider::SetOrientation)
        // [Method] void SetRange(float range)
        .addFunction("SetRange", &Slider::SetRange)
        // [Method] void SetValue(float value)
        .addFunction("SetValue", &Slider::SetValue)
        // [Method] void ChangeValue(float delta)
        .addFunction("ChangeValue", &Slider::ChangeValue)
        // [Method] void SetRepeatRate(float rate)
        .addFunction("SetRepeatRate", &Slider::SetRepeatRate)

        // [Method] Orientation GetOrientation() const
        .addFunction("GetOrientation", &Slider::GetOrientation)
        // [Method] float GetRange() const
        .addFunction("GetRange", &Slider::GetRange)
        // [Method] float GetValue() const
        .addFunction("GetValue", &Slider::GetValue)
        // [Method] BorderImage* GetKnob() const
        .addFunction("GetKnob", &Slider::GetKnob)
        // [Method] float GetRepeatRate() const
        .addFunction("GetRepeatRate", &Slider::GetRepeatRate)

        // [Property] Orientation orientation
        .addProperty("orientation", &Slider::GetOrientation, &Slider::SetOrientation)
        // [Property] float range
        .addProperty("range", &Slider::GetRange, &Slider::SetRange)
        // [Property] float value
        .addProperty("value", &Slider::GetValue, &Slider::SetValue)
        // [Property(ReadOnly)] BorderImage* knob
        .addProperty("knob", &Slider::GetKnob)
        // [Property] float repeatRate
        .addProperty("repeatRate", &Slider::GetRepeatRate, &Slider::SetRepeatRate)
        );
}
}

