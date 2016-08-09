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

    // [Class] AnimationController : Component
    lua["AnimationController"].setClass(UserdataMetatable<AnimationController, Component>()
        .addStaticFunction("new", &CreateObject<AnimationController>)

        // [Method] bool Play(const String& name, unsigned char layer, bool looped, float fadeInTime = 0.0f)
        .addFunction("Play", AnimationControllerPlay())
        // [Method] bool PlayExclusive(const String& name, unsigned char layer, bool looped, float fadeTime = 0.0f)
        .addFunction("PlayExclusive", AnimationControllerPlayExclusive())
        // [Method] bool Stop(const String& name, float fadeOutTime = 0.0f)
        .addFunction("Stop", AnimationControllerStop())
        // [Method] void StopLayer(unsigned char layer, float fadeOutTime = 0.0f)
        .addFunction("StopLayer", AnimationControllerStopLayer())
        // [Method] void StopAll(float fadeTime = 0.0f)
        .addFunction("StopAll", AnimationControllerStopAll())

        // [Method] bool Fade(const String& name, float targetWeight, float fadeTime)
        .addFunction("Fade", &AnimationController::Fade)
        // [Method] bool FadeOthers(const String& name, float targetWeight, float fadeTime)
        .addFunction("FadeOthers", &AnimationController::FadeOthers)

        // [Method] bool SetLayer(const String& name, unsigned char layer)
        .addFunction("SetLayer", &AnimationController::SetLayer)
        // [Method] bool SetStartBone(const String& name, const String& startBoneName)
        .addFunction("SetStartBone", &AnimationController::SetStartBone)
        // [Method] bool SetTime(const String& name, float time)
        .addFunction("SetTime", &AnimationController::SetTime)
        // [Method] bool SetWeight(const String& name, float weight)
        .addFunction("SetWeight", &AnimationController::SetWeight)
        // [Method] bool SetLooped(const String& name, bool enable)
        .addFunction("SetLooped", &AnimationController::SetLooped)
        // [Method] bool SetSpeed(const String& name, float speed)
        .addFunction("SetSpeed", &AnimationController::SetSpeed)
        // [Method] bool SetAutoFade(const String& name, float fadeOutTime)
        .addFunction("SetAutoFade", &AnimationController::SetAutoFade)
        // [Method] bool SetRemoveOnCompletion(const String& name, bool removeOnCompletion)
        .addFunction("SetRemoveOnCompletion", &AnimationController::SetRemoveOnCompletion)
        // [Method] bool SetBlendMode(const String& name, AnimationBlendMode mode)
        .addFunction("SetBlendMode", &AnimationController::SetBlendMode)
        
        // [Method] bool IsPlaying(const String& name) const
        .addFunction("IsPlaying", &AnimationController::IsPlaying)
        // [Method] bool IsFadingIn(const String& name) const
        .addFunction("IsFadingIn", &AnimationController::IsFadingIn)
        // [Method] bool IsFadingOut(const String& name) const
        .addFunction("IsFadingOut", &AnimationController::IsFadingOut)
        // [Method] bool IsAtEnd(const String& name) const
        .addFunction("IsAtEnd", &AnimationController::IsAtEnd)
        // [Method] unsigned char GetLayer(const String& name) const
        .addFunction("GetLayer", &AnimationController::GetLayer)
        // [Method] Bone* GetStartBone(const String& name) const
        .addFunction("GetStartBone", &AnimationController::GetStartBone)
        // [Method] const String& GetStartBoneName(const String& name) const
        .addFunction("GetStartBoneName", &AnimationController::GetStartBoneName)
        // [Method] float GetTime(const String& name) const
        .addFunction("GetTime", &AnimationController::GetTime)
        // [Method] float GetWeight(const String& name) const
        .addFunction("GetWeight", &AnimationController::GetWeight)
        // [Method] bool IsLooped(const String& name) const
        .addFunction("IsLooped", &AnimationController::IsLooped)
        // [Method] AnimationBlendMode GetBlendMode(const String& name) const
        .addFunction("GetBlendMode", &AnimationController::GetBlendMode)
        // [Method] float GetLength(const String& name) const
        .addFunction("GetLength", &AnimationController::GetLength)
        // [Method] float GetSpeed(const String& name) const
        .addFunction("GetSpeed", &AnimationController::GetSpeed)
        // [Method] float GetFadeTarget(const String& name) const
        .addFunction("GetFadeTarget", &AnimationController::GetFadeTarget)
        // [Method] float GetFadeTime(const String& name) const
        .addFunction("GetFadeTime", &AnimationController::GetFadeTime)
        // [Method] float GetAutoFade(const String& name) const
        .addFunction("GetAutoFade", &AnimationController::GetAutoFade)
        // [Method] bool GetRemoveOnCompletion(const String& name) const
        .addFunction("GetRemoveOnCompletion", &AnimationController::GetRemoveOnCompletion)

        // [Method] AnimationState* GetAnimationState(const String& name) const
        .addFunction("GetAnimationState", static_cast<AnimationState*(AnimationController::*)(const String&) const>(&AnimationController::GetAnimationState))
        );
}
}

