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

    // [Enum] InterpMethod
    // [Variable] IM_NONE
    lua["IM_NONE"] = IM_NONE;
    // [Variable] IM_LINEAR,
    lua["IM_LINEAR"] = IM_LINEAR;
    // [Variable] IM_SPLINE,
    lua["IM_SPLINE"] = IM_SPLINE;

    // [Class] ValueAnimation : Resource
    lua["ValueAnimation"].setClass(UserdataMetatable<ValueAnimation, Resource>()
        .addStaticFunction("new", &CreateObject<ValueAnimation>)

        // [Method] void SetInterpolationMethod(InterpMethod method)
        .addFunction("SetInterpolationMethod", &ValueAnimation::SetInterpolationMethod)
        // [Method] void SetSplineTension(float tension)
        .addFunction("SetSplineTension", &ValueAnimation::SetSplineTension)
        // [Method] void SetValueType(VariantType valueType)
        .addFunction("SetValueType", &ValueAnimation::SetValueType)
        // [Method] bool SetKeyFrame(float time, const Variant& value)
        .addFunction("SetKeyFrame", &ValueAnimation::SetKeyFrame)

        // [Method] void SetEventFrame(float time, const StringHash& eventType, const VariantMap& eventData = VariantMap())
        .addFunction("SetEventFrame", ValueAnimationSetEventFrame())

        // [Method] bool IsValid() const
        .addFunction("IsValid", &ValueAnimation::IsValid)
        // [Method] InterpMethod GetInterpolationMethod() const
        .addFunction("GetInterpolationMethod", &ValueAnimation::GetInterpolationMethod)
        // [Method] float GetSplineTension() const
        .addFunction("GetSplineTension", &ValueAnimation::GetSplineTension)
        // [Method] VariantType GetValueType() const
        .addFunction("GetValueType", &ValueAnimation::GetValueType)
        // [Method] float GetBeginTime() const
        .addFunction("GetBeginTime", &ValueAnimation::GetBeginTime)
        // [Method] float GetEndTime() const
        .addFunction("GetEndTime", &ValueAnimation::GetEndTime)
        // [Method] Variant GetAnimationValue(float scaledTime)
        .addFunction("GetAnimationValue", &ValueAnimation::GetAnimationValue)
        // [Method] bool HasEventFrames() const
        .addFunction("HasEventFrames", &ValueAnimation::HasEventFrames)

        // [Property(ReadOnly)] bool valid
        .addProperty("valid", &ValueAnimation::IsValid)
        // [Property] InterpMethod interpolationMethod
        .addProperty("interpolationMethod", &ValueAnimation::GetInterpolationMethod, &ValueAnimation::SetInterpolationMethod)
        // [Property] float splineTension
        .addProperty("splineTension", &ValueAnimation::GetSplineTension, &ValueAnimation::SetSplineTension)
        // [Property] VariantType valueType
        .addProperty("valueType", &ValueAnimation::GetValueType, &ValueAnimation::SetValueType)
        );
}
}

