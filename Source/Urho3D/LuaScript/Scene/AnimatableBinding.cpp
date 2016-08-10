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

    // [Class] Animatable : Serializable
    lua["Animatable"].setClass(UserdataMetatable<Animatable, Serializable>()

        // [Method] void SetAnimationEnabled(bool enable)
        .addFunction("SetAnimationEnabled", &Animatable::SetAnimationEnabled)
        // [Method] void SetAnimationTime(float time)
        .addFunction("SetAnimationTime", &Animatable::SetAnimationTime)
        // [Method] void SetObjectAnimation(ObjectAnimation* objectAnimation)
        .addFunction("SetObjectAnimation", &Animatable::SetObjectAnimation)

        // [Method] void SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode = WM_LOOP, float speed = 1.0f)
        .addFunction("SetAttributeAnimation", AnimatableSetAttributeAnimation())

        // [Method] void SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode)
        .addFunction("SetAttributeAnimationWrapMode", &Animatable::SetAttributeAnimationWrapMode)
        // [Method] void SetAttributeAnimationSpeed(const String& name, float speed)
        .addFunction("SetAttributeAnimationSpeed", &Animatable::SetAttributeAnimationSpeed)
        // [Method] void SetAttributeAnimationTime(const String& name, float time)
        .addFunction("SetAttributeAnimationTime", &Animatable::SetAttributeAnimationTime)
        // [Method] void RemoveObjectAnimation()
        .addFunction("RemoveObjectAnimation", &Animatable::RemoveObjectAnimation)
        // [Method] void RemoveAttributeAnimation(const String& name)
        .addFunction("RemoveAttributeAnimation", &Animatable::RemoveAttributeAnimation)

        // [Method] bool GetAnimationEnabled() const
        .addFunction("GetAnimationEnabled", &Animatable::GetAnimationEnabled)
        // [Method] ObjectAnimation* GetObjectAnimation() const
        .addFunction("GetObjectAnimation", &Animatable::GetObjectAnimation)
        // [Method] ValueAnimation* GetAttributeAnimation(const String& name) const
        .addFunction("GetAttributeAnimation", &Animatable::GetAttributeAnimation)
        // [Method] WrapMode GetAttributeAnimationWrapMode(const String& name) const
        .addFunction("GetAttributeAnimationWrapMode", &Animatable::GetAttributeAnimationWrapMode)
        // [Method] float GetAttributeAnimationSpeed(const String& name) const
        .addFunction("GetAttributeAnimationSpeed", &Animatable::GetAttributeAnimationSpeed)
        // [Method] float GetAttributeAnimationTime(const String& name) const
        .addFunction("GetAttributeAnimationTime", &Animatable::GetAttributeAnimationTime)

        // [Property] bool animationEnabled
        .addProperty("animationEnabled", &Animatable::GetAnimationEnabled, &Animatable::SetAnimationEnabled)
        // [Property] ObjectAnimation* objectAnimation
        .addProperty("objectAnimation", &Animatable::GetObjectAnimation, &Animatable::SetObjectAnimation)
        // [Property(Writeonly)] float animationTime
        .addProperty("animationTime", &Animatable::SetAnimationTime)
        );
}
}

