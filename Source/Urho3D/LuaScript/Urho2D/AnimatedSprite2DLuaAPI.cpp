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

    // enum LoopMode2D;
    lua["LM_DEFAULT"] = LM_DEFAULT;
    lua["LM_FORCE_LOOPED"] = LM_FORCE_LOOPED;
    lua["LM_FORCE_CLAMPED"] = LM_FORCE_CLAMPED;

    lua["AnimatedSprite2D"].setClass(UserdataMetatable<AnimatedSprite2D, StaticSprite2D>()
        .addStaticFunction("new", &CreateObject<AnimatedSprite2D>)

        .addFunction("SetAnimationSet", &AnimatedSprite2D::SetAnimationSet)
        .addFunction("SetEntity", &AnimatedSprite2D::SetEntity)

        .addFunction("SetAnimation", AnimatedSprite2DSetAnimation())

        .addFunction("SetLoopMode", &AnimatedSprite2D::SetLoopMode)
        .addFunction("SetSpeed", &AnimatedSprite2D::SetSpeed)

        .addFunction("GetAnimationSet", &AnimatedSprite2D::GetAnimationSet)
        .addFunction("GetEntity", &AnimatedSprite2D::GetEntity)
        .addFunction("GetAnimation", &AnimatedSprite2D::GetAnimation)
        .addFunction("GetLoopMode", &AnimatedSprite2D::GetLoopMode)
        .addFunction("GetSpeed", &AnimatedSprite2D::GetSpeed)

        .addProperty("animationSet", &AnimatedSprite2D::GetAnimationSet, &AnimatedSprite2D::SetAnimationSet)
        .addProperty("entity", &AnimatedSprite2D::GetEntity, &AnimatedSprite2D::SetEntity)
        .addProperty("animation", &AnimatedSprite2D::GetAnimation)
        .addProperty("loopMode", &AnimatedSprite2D::GetLoopMode, &AnimatedSprite2D::SetLoopMode)
        .addProperty("speed", &AnimatedSprite2D::GetSpeed, &AnimatedSprite2D::SetSpeed)
    );
}
}

#endif
