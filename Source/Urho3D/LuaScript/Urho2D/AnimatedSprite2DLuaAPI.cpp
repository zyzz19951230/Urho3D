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

#ifdef URHO3D_URHO2D

#include "../../Precompiled.h"

#include "../../Urho2D/AnimatedSprite2D.h"
#include "../../Urho2D/AnimationSet2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimatedSprite2DSetAnimation, AnimatedSprite2D, SetAnimation, 1, 2);

void RegisterAnimatedSprite2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] LoopMode2D
    // [Constant] void SetAnimation(String& name, LoopMode2D loopMode
    lua["LM_DEFAULT"] = LM_DEFAULT;
    // [Variable] LM_FORCE_LOOPED,
    lua["LM_FORCE_LOOPED"] = LM_FORCE_LOOPED;
    // [Variable] LM_FORCE_CLAMPED
    lua["LM_FORCE_CLAMPED"] = LM_FORCE_CLAMPED;

    // [Class] AnimatedSprite2D : StaticSprite2D
    lua["AnimatedSprite2D"].setClass(UserdataMetatable<AnimatedSprite2D, StaticSprite2D>()
        .addStaticFunction("new", &CreateObject<AnimatedSprite2D>)

        // [Method] void SetAnimationSet(AnimationSet2D* animationSet)
        .addFunction("SetAnimationSet", &AnimatedSprite2D::SetAnimationSet)
        // [Method] void SetEntity(const String& name)
        .addFunction("SetEntity", &AnimatedSprite2D::SetEntity)

        // [Method] void SetAnimation(const String& name, LoopMode2D loopMode = LM_DEFAULT)
        .addFunction("SetAnimation", AnimatedSprite2DSetAnimation())

        // [Method] void SetLoopMode(LoopMode2D loopMode)
        .addFunction("SetLoopMode", &AnimatedSprite2D::SetLoopMode)
        // [Method] void SetSpeed(float speed)
        .addFunction("SetSpeed", &AnimatedSprite2D::SetSpeed)

        // [Method] AnimationSet2D* GetAnimationSet() const
        .addFunction("GetAnimationSet", &AnimatedSprite2D::GetAnimationSet)
        // [Method] const String& GetEntity() const
        .addFunction("GetEntity", &AnimatedSprite2D::GetEntity)
        // [Method] const String& GetAnimation() const
        .addFunction("GetAnimation", &AnimatedSprite2D::GetAnimation)
        // [Method] LoopMode2D GetLoopMode() const
        .addFunction("GetLoopMode", &AnimatedSprite2D::GetLoopMode)
        // [Method] float GetSpeed() const
        .addFunction("GetSpeed", &AnimatedSprite2D::GetSpeed)

        // [Property] AnimationSet2D* animationSet
        .addProperty("animationSet", &AnimatedSprite2D::GetAnimationSet, &AnimatedSprite2D::SetAnimationSet)
        // [Property] const String& entity
        .addProperty("entity", &AnimatedSprite2D::GetEntity, &AnimatedSprite2D::SetEntity)
        // [Property(ReadOnly)] const String& animation
        .addProperty("animation", &AnimatedSprite2D::GetAnimation)
        // [Property] LoopMode2D loopMode
        .addProperty("loopMode", &AnimatedSprite2D::GetLoopMode, &AnimatedSprite2D::SetLoopMode)
        // [Property] float speed
        .addProperty("speed", &AnimatedSprite2D::GetSpeed, &AnimatedSprite2D::SetSpeed)
    );
}
}

#endif
