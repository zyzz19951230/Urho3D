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

    lua["Slider"].setClass(UserdataMetatable<Slider, BorderImage>()
        .addStaticFunction("new", &CreateObject<Slider>)

        .addFunction("SetOrientation", &Slider::SetOrientation)
        .addFunction("SetRange", &Slider::SetRange)
        .addFunction("SetValue", &Slider::SetValue)
        .addFunction("ChangeValue", &Slider::ChangeValue)
        .addFunction("SetRepeatRate", &Slider::SetRepeatRate)

        .addFunction("GetOrientation", &Slider::GetOrientation)
        .addFunction("GetRange", &Slider::GetRange)
        .addFunction("GetValue", &Slider::GetValue)
        .addFunction("GetKnob", &Slider::GetKnob)
        .addFunction("GetRepeatRate", &Slider::GetRepeatRate)

        .addProperty("orientation", &Slider::GetOrientation, &Slider::SetOrientation)
        .addProperty("range", &Slider::GetRange, &Slider::SetRange)
        .addProperty("value", &Slider::GetValue, &Slider::SetValue)
        .addProperty("knob", &Slider::GetKnob)
        .addProperty("repeatRate", &Slider::GetRepeatRate, &Slider::SetRepeatRate)
        );
}
}

