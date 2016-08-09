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

#include "../../Graphics/AnimatedModel.h"
#include "../../Graphics/Animation.h"
#include "../../Graphics/AnimationState.h"
#include "../../Scene/Node.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(AnimationStateSetBoneWeight0, AnimationState, SetBoneWeight, 2, 3, void(AnimationState::*)(unsigned, float, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(AnimationStateSetBoneWeight1, AnimationState, SetBoneWeight, 2, 3, void(AnimationState::*)(const String&, float, bool));

void RegisterAnimationState(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] AnimationBlendMode
    lua["ABM_LERP"] = ABM_LERP;
    lua["ABM_ADDITIVE"] = ABM_ADDITIVE;

    // [Class] AnimationState : RefCounted
    lua["AnimationState"].setClass(UserdataMetatable<AnimationState, RefCounted>()
        // [Constructor] AnimationState(AnimatedModel* model, Animation* animation)
        .setConstructors<AnimationState(AnimatedModel*, Animation*)>()

        // [Method] void SetStartBone(Bone* bone)
        .addFunction("SetStartBone", &AnimationState::SetStartBone)
        // [Method] void SetLooped(bool looped)
        .addFunction("SetLooped", &AnimationState::SetLooped)
        // [Method] void SetWeight(float weight)
        .addFunction("SetWeight", &AnimationState::SetWeight)
        // [Method] void SetBlendMode(AnimationBlendMode mode)
        .addFunction("SetBlendMode", &AnimationState::SetBlendMode)
        // [Method] void SetTime(float time)
        .addFunction("SetTime", &AnimationState::SetTime)

        .addOverloadedFunctions("SetBoneWeight",
            // [Method] void SetBoneWeight(unsigned index, float weight, bool recursive = false)
            AnimationStateSetBoneWeight0(),
            // [Method] void SetBoneWeight(const String& name, float weight, bool recursive = false)
            AnimationStateSetBoneWeight1())

        // [Method] void AddWeight(float delta)
        .addFunction("AddWeight", &AnimationState::AddWeight)
        // [Method] void AddTime(float delta)
        .addFunction("AddTime", &AnimationState::AddTime)
        // [Method] void SetLayer(unsigned char layer)
        .addFunction("SetLayer", &AnimationState::SetLayer)
        // [Method] Animation* GetAnimation() const
        .addFunction("GetAnimation", &AnimationState::GetAnimation)
        // [Method] AnimatedModel* GetModel() const
        .addFunction("GetModel", &AnimationState::GetModel)
        // [Method] Node* GetNode() const
        .addFunction("GetNode", &AnimationState::GetNode)
        // [Method] Bone* GetStartBone() const
        .addFunction("GetStartBone", &AnimationState::GetStartBone)

        .addOverloadedFunctions("GetBoneWeight",
            // [Method] float AnimationState::GetBoneWeight(unsigned index) const
            static_cast<float(AnimationState::*)(unsigned) const>(&AnimationState::GetBoneWeight),
            // [Method] float AnimationState::GetBoneWeight(const String& name) const
            static_cast<float(AnimationState::*)(const String&) const>(&AnimationState::GetBoneWeight))

        // [Method] unsigned GetTrackIndex(const String& name) const
        .addFunction("GetTrackIndex", static_cast<unsigned(AnimationState::*)(const String&) const>(&AnimationState::GetTrackIndex))

        // [Method] bool IsEnabled() const
        .addFunction("IsEnabled", &AnimationState::IsEnabled)
        // [Method] bool IsLooped() const
        .addFunction("IsLooped", &AnimationState::IsLooped)
        // [Method] float GetWeight() const
        .addFunction("GetWeight", &AnimationState::GetWeight)
        // [Method] AnimationBlendMode GetBlendMode() const
        .addFunction("GetBlendMode", &AnimationState::GetBlendMode)
        // [Method] float GetTime() const
        .addFunction("GetTime", &AnimationState::GetTime)
        // [Method] float GetLength() const
        .addFunction("GetLength", &AnimationState::GetLength)
        // [Method] unsigned char GetLayer() const
        .addFunction("GetLayer", &AnimationState::GetLayer)
        // [Method] void Apply()
        .addFunction("Apply", &AnimationState::Apply)

        // [Property(ReadOnly)] Animation* animation
        .addProperty("animation", &AnimationState::GetAnimation)
        // [Property(ReadOnly)] AnimatedModel* model
        .addProperty("model", &AnimationState::GetModel)
        // [Property(ReadOnly)] Node* node
        .addProperty("node", &AnimationState::GetNode)
        // [Property] Bone* startBone
        .addProperty("startBone", &AnimationState::GetStartBone, &AnimationState::SetStartBone)
        // [Property(ReadOnly)] bool enabled
        .addProperty("enabled", &AnimationState::IsEnabled)
        // [Property] bool looped
        .addProperty("looped", &AnimationState::IsLooped, &AnimationState::SetLooped)
        // [Property] float weight
        .addProperty("weight", &AnimationState::GetWeight, &AnimationState::SetWeight)
        // [Property] AnimationBlendMode blendMode
        .addProperty("blendMode", &AnimationState::GetBlendMode, &AnimationState::SetBlendMode)
        // [Property] float time
        .addProperty("time", &AnimationState::GetTime, &AnimationState::SetTime)
        // [Property(ReadOnly)] float length
        .addProperty("length", &AnimationState::GetLength)
        // [Property] unsigned char layer
        .addProperty("layer", &AnimationState::GetLayer, &AnimationState::SetLayer)
        );
}
}

