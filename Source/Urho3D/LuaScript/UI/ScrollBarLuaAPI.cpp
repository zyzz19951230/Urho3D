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
#include "../../UI/ScrollBar.h"
#include "../../UI/Slider.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterScrollBar(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ScrollBar"].setClass(UserdataMetatable<ScrollBar, BorderImage>()
        .addStaticFunction("new", &CreateObject<ScrollBar>)

        .addFunction("SetOrientation", &ScrollBar::SetOrientation)
        .addFunction("SetRange", &ScrollBar::SetRange)
        .addFunction("SetValue", &ScrollBar::SetValue)
        .addFunction("ChangeValue", &ScrollBar::ChangeValue)
        .addFunction("SetScrollStep", &ScrollBar::SetScrollStep)
        .addFunction("SetStepFactor", &ScrollBar::SetStepFactor)
        .addFunction("StepBack", &ScrollBar::StepBack)
        .addFunction("StepForward", &ScrollBar::StepForward)

        .addFunction("GetOrientation", &ScrollBar::GetOrientation)
        .addFunction("GetRange", &ScrollBar::GetRange)
        .addFunction("GetValue", &ScrollBar::GetValue)
        .addFunction("GetScrollStep", &ScrollBar::GetScrollStep)
        .addFunction("GetStepFactor", &ScrollBar::GetStepFactor)
        .addFunction("GetEffectiveScrollStep", &ScrollBar::GetEffectiveScrollStep)
        .addFunction("GetBackButton", &ScrollBar::GetBackButton)
        .addFunction("GetForwardButton", &ScrollBar::GetForwardButton)
        .addFunction("GetSlider", &ScrollBar::GetSlider)

        .addProperty("orientation", &ScrollBar::GetOrientation, &ScrollBar::SetOrientation)
        .addProperty("range", &ScrollBar::GetRange, &ScrollBar::SetRange)
        .addProperty("value", &ScrollBar::GetValue, &ScrollBar::SetValue)
        .addProperty("scrollStep", &ScrollBar::GetScrollStep, &ScrollBar::SetScrollStep)
        .addProperty("stepFactor", &ScrollBar::GetStepFactor, &ScrollBar::SetStepFactor)
        .addProperty("effectiveScrollStep", &ScrollBar::GetEffectiveScrollStep)
        .addProperty("backButton", &ScrollBar::GetBackButton)
        .addProperty("forwardButton", &ScrollBar::GetForwardButton)
        .addProperty("slider", &ScrollBar::GetSlider)
        );
}
}

