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

    // [Class] ScrollBar : BorderImage
    lua["ScrollBar"].setClass(UserdataMetatable<ScrollBar, BorderImage>()
        // [Constructor] ScrollBar()
        .addStaticFunction("new", &CreateObject<ScrollBar>)

        // [Method] void SetOrientation(Orientation orientation)
        .addFunction("SetOrientation", &ScrollBar::SetOrientation)
        // [Method] void SetRange(float range)
        .addFunction("SetRange", &ScrollBar::SetRange)
        // [Method] void SetValue(float value)
        .addFunction("SetValue", &ScrollBar::SetValue)
        // [Method] void ChangeValue(float delta)
        .addFunction("ChangeValue", &ScrollBar::ChangeValue)
        // [Method] void SetScrollStep(float step)
        .addFunction("SetScrollStep", &ScrollBar::SetScrollStep)
        // [Method] void SetStepFactor(float factor)
        .addFunction("SetStepFactor", &ScrollBar::SetStepFactor)
        // [Method] void StepBack()
        .addFunction("StepBack", &ScrollBar::StepBack)
        // [Method] void StepForward()
        .addFunction("StepForward", &ScrollBar::StepForward)

        // [Method] Orientation GetOrientation() const
        .addFunction("GetOrientation", &ScrollBar::GetOrientation)
        // [Method] float GetRange() const
        .addFunction("GetRange", &ScrollBar::GetRange)
        // [Method] float GetValue() const
        .addFunction("GetValue", &ScrollBar::GetValue)
        // [Method] float GetScrollStep() const
        .addFunction("GetScrollStep", &ScrollBar::GetScrollStep)
        // [Method] float GetStepFactor() const
        .addFunction("GetStepFactor", &ScrollBar::GetStepFactor)
        // [Method] float GetEffectiveScrollStep() const
        .addFunction("GetEffectiveScrollStep", &ScrollBar::GetEffectiveScrollStep)
        // [Method] Button* GetBackButton() const
        .addFunction("GetBackButton", &ScrollBar::GetBackButton)
        // [Method] Button* GetForwardButton() const
        .addFunction("GetForwardButton", &ScrollBar::GetForwardButton)
        // [Method] Slider* GetSlider() const
        .addFunction("GetSlider", &ScrollBar::GetSlider)

        // [Property] Orientation orientation
        .addProperty("orientation", &ScrollBar::GetOrientation, &ScrollBar::SetOrientation)
        // [Property] float range
        .addProperty("range", &ScrollBar::GetRange, &ScrollBar::SetRange)
        // [Property] float value
        .addProperty("value", &ScrollBar::GetValue, &ScrollBar::SetValue)
        // [Property] float scrollStep
        .addProperty("scrollStep", &ScrollBar::GetScrollStep, &ScrollBar::SetScrollStep)
        // [Property] float stepFactor
        .addProperty("stepFactor", &ScrollBar::GetStepFactor, &ScrollBar::SetStepFactor)
        // [Property(Readonly)] float effectiveScrollStep
        .addProperty("effectiveScrollStep", &ScrollBar::GetEffectiveScrollStep)
        // [Property(Readonly)] Button* backButton
        .addProperty("backButton", &ScrollBar::GetBackButton)
        // [Property(Readonly)] Button* forwardButton
        .addProperty("forwardButton", &ScrollBar::GetForwardButton)
        // [Property(Readonly)] Slider* slider
        .addProperty("slider", &ScrollBar::GetSlider)
        );
}
}

