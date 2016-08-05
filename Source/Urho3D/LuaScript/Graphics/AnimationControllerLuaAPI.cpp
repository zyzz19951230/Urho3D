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

#include "../../Graphics/AnimationController.h"
#include "../../Graphics/Skeleton.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerPlay, AnimationController, Play, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerPlayExclusive, AnimationController, PlayExclusive, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerStop, AnimationController, Stop, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerStopLayer, AnimationController, StopLayer, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerStopAll, AnimationController, StopAll, 0, 1);

void RegisterAnimationController(kaguya::State& lua)
{
    using namespace kaguya;

    lua["AnimationController"].setClass(UserdataMetatable<AnimationController, Component>()
        .addStaticFunction("new", &CreateObject<AnimationController>)

        .addFunction("Play", AnimationControllerPlay())
        .addFunction("PlayExclusive", AnimationControllerPlayExclusive())
        .addFunction("Stop", AnimationControllerStop())
        .addFunction("StopLayer", AnimationControllerStopLayer())
        .addFunction("StopAll", AnimationControllerStopAll())

        .addFunction("Fade", &AnimationController::Fade)
        .addFunction("FadeOthers", &AnimationController::FadeOthers)

        .addFunction("SetLayer", &AnimationController::SetLayer)
        .addFunction("SetStartBone", &AnimationController::SetStartBone)
        .addFunction("SetTime", &AnimationController::SetTime)
        .addFunction("SetWeight", &AnimationController::SetWeight)
        .addFunction("SetLooped", &AnimationController::SetLooped)
        .addFunction("SetSpeed", &AnimationController::SetSpeed)
        .addFunction("SetAutoFade", &AnimationController::SetAutoFade)
        .addFunction("SetRemoveOnCompletion", &AnimationController::SetRemoveOnCompletion)
        .addFunction("SetBlendMode", &AnimationController::SetBlendMode)
        
        .addFunction("IsPlaying", &AnimationController::IsPlaying)
        .addFunction("IsFadingIn", &AnimationController::IsFadingIn)
        .addFunction("IsFadingOut", &AnimationController::IsFadingOut)
        .addFunction("IsAtEnd", &AnimationController::IsAtEnd)
        .addFunction("GetLayer", &AnimationController::GetLayer)
        .addFunction("GetStartBone", &AnimationController::GetStartBone)
        .addFunction("GetStartBoneName", &AnimationController::GetStartBoneName)
        .addFunction("GetTime", &AnimationController::GetTime)
        .addFunction("GetWeight", &AnimationController::GetWeight)
        .addFunction("IsLooped", &AnimationController::IsLooped)
        .addFunction("GetBlendMode", &AnimationController::GetBlendMode)
        .addFunction("GetLength", &AnimationController::GetLength)
        .addFunction("GetSpeed", &AnimationController::GetSpeed)
        .addFunction("GetFadeTarget", &AnimationController::GetFadeTarget)
        .addFunction("GetFadeTime", &AnimationController::GetFadeTime)
        .addFunction("GetAutoFade", &AnimationController::GetAutoFade)
        .addFunction("GetRemoveOnCompletion", &AnimationController::GetRemoveOnCompletion)

        .addFunction("GetAnimationState", static_cast<AnimationState*(AnimationController::*)(const String&) const>(&AnimationController::GetAnimationState))
        );
}
}

