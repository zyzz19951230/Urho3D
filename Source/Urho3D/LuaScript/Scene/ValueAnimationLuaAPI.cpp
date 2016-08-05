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

#include "../../Scene/ValueAnimation.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ValueAnimationSetEventFrame, ValueAnimation, SetEventFrame, 2, 3);

void RegisterValueAnimation(kaguya::State& lua)
{
    using namespace kaguya;

    // enum InterpMethod;
    lua["IM_NONE"] = IM_NONE;
    lua["IM_LINEAR"] = IM_LINEAR;
    lua["IM_SPLINE"] = IM_SPLINE;

    lua["ValueAnimation"].setClass(UserdataMetatable<ValueAnimation, Resource>()
        .addStaticFunction("new", &CreateObject<ValueAnimation>)

        .addFunction("SetInterpolationMethod", &ValueAnimation::SetInterpolationMethod)
        .addFunction("SetSplineTension", &ValueAnimation::SetSplineTension)
        .addFunction("SetValueType", &ValueAnimation::SetValueType)
        .addFunction("SetKeyFrame", &ValueAnimation::SetKeyFrame)

        .addFunction("SetEventFrame", ValueAnimationSetEventFrame())

        .addFunction("IsValid", &ValueAnimation::IsValid)
        .addFunction("GetInterpolationMethod", &ValueAnimation::GetInterpolationMethod)
        .addFunction("GetSplineTension", &ValueAnimation::GetSplineTension)
        .addFunction("GetValueType", &ValueAnimation::GetValueType)
        .addFunction("GetBeginTime", &ValueAnimation::GetBeginTime)
        .addFunction("GetEndTime", &ValueAnimation::GetEndTime)
        .addFunction("GetAnimationValue", &ValueAnimation::GetAnimationValue)
        .addFunction("HasEventFrames", &ValueAnimation::HasEventFrames)

        .addProperty("valid", &ValueAnimation::IsValid)
        .addProperty("interpolationMethod", &ValueAnimation::GetInterpolationMethod, &ValueAnimation::SetInterpolationMethod)
        .addProperty("splineTension", &ValueAnimation::GetSplineTension, &ValueAnimation::SetSplineTension)
        .addProperty("valueType", &ValueAnimation::GetValueType, &ValueAnimation::SetValueType)
        );
}
}

