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

#include "../../Scene/Animatable.h"
#include "../../Scene/ObjectAnimation.h"
#include "../../Scene/ValueAnimation.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimatableSetAttributeAnimation, Animatable, SetAttributeAnimation, 2, 4);

void RegisterAnimatable(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Animatable"].setClass(UserdataMetatable<Animatable, Serializable>()

        .addFunction("SetAnimationEnabled", &Animatable::SetAnimationEnabled)
        .addFunction("SetAnimationTime", &Animatable::SetAnimationTime)
        .addFunction("SetObjectAnimation", &Animatable::SetObjectAnimation)

        .addFunction("SetAttributeAnimation", AnimatableSetAttributeAnimation())

        .addFunction("SetAttributeAnimationWrapMode", &Animatable::SetAttributeAnimationWrapMode)
        .addFunction("SetAttributeAnimationSpeed", &Animatable::SetAttributeAnimationSpeed)
        .addFunction("SetAttributeAnimationTime", &Animatable::SetAttributeAnimationTime)
        .addFunction("RemoveObjectAnimation", &Animatable::RemoveObjectAnimation)
        .addFunction("RemoveAttributeAnimation", &Animatable::RemoveAttributeAnimation)

        .addFunction("GetAnimationEnabled", &Animatable::GetAnimationEnabled)
        .addFunction("GetObjectAnimation", &Animatable::GetObjectAnimation)
        .addFunction("GetAttributeAnimation", &Animatable::GetAttributeAnimation)
        .addFunction("GetAttributeAnimationWrapMode", &Animatable::GetAttributeAnimationWrapMode)
        .addFunction("GetAttributeAnimationSpeed", &Animatable::GetAttributeAnimationSpeed)
        .addFunction("GetAttributeAnimationTime", &Animatable::GetAttributeAnimationTime)

        .addProperty("animationEnabled", &Animatable::GetAnimationEnabled, &Animatable::SetAnimationEnabled)
        .addProperty("objectAnimation", &Animatable::GetObjectAnimation, &Animatable::SetObjectAnimation)
        .addProperty("animationTime", &Animatable::SetAnimationTime)
        );
}
}

