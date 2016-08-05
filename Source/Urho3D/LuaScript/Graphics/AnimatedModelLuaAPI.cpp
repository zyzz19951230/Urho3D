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
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimatedModelSetModel, AnimatedModel, SetModel, 1, 2);

static void AnimatedModelModelSetter(AnimatedModel* self, Model* model)
{
    self->SetModel(model);
}

static Model* AnimatedModelModelGetter(const AnimatedModel* self)
{
    return self->GetModel();
}

void RegisterAnimatedModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["AnimatedModel"].setClass(UserdataMetatable<AnimatedModel, StaticModel>()
        .addStaticFunction("new", &CreateObject<AnimatedModel>)

        .addFunction("SetModel", AnimatedModelSetModel())

        .addFunction("AddAnimationState", &AnimatedModel::AddAnimationState)

        .addOverloadedFunctions("RemoveAnimationState",
            static_cast<void(AnimatedModel::*)(Animation*)>(&AnimatedModel::RemoveAnimationState),
            static_cast<void(AnimatedModel::*)(const String&)>(&AnimatedModel::RemoveAnimationState),
            static_cast<void(AnimatedModel::*)(StringHash)>(&AnimatedModel::RemoveAnimationState),
            static_cast<void(AnimatedModel::*)(AnimationState*)>(&AnimatedModel::RemoveAnimationState),
            static_cast<void(AnimatedModel::*)(unsigned)>(&AnimatedModel::RemoveAnimationState))

        .addFunction("RemoveAllAnimationStates", &AnimatedModel::RemoveAllAnimationStates)
        .addFunction("SetAnimationLodBias", &AnimatedModel::SetAnimationLodBias)
        .addFunction("SetUpdateInvisible", &AnimatedModel::SetUpdateInvisible)

        .addOverloadedFunctions("SetMorphWeight",
            static_cast<void(AnimatedModel::*)(unsigned, float)>(&AnimatedModel::SetMorphWeight),
            static_cast<void(AnimatedModel::*)(const String&, float)>(&AnimatedModel::SetMorphWeight),
            static_cast<void(AnimatedModel::*)(StringHash, float)>(&AnimatedModel::SetMorphWeight))

        .addFunction("ResetMorphWeights", &AnimatedModel::ResetMorphWeights)

        .addFunction("GetSkeleton", &AnimatedModel::GetSkeleton)
        
        .addFunction("GetNumAnimationStates", &AnimatedModel::GetNumAnimationStates)

        .addOverloadedFunctions("GetAnimationState",
            static_cast<AnimationState*(AnimatedModel::*)(Animation*) const>(&AnimatedModel::GetAnimationState),
            static_cast<AnimationState*(AnimatedModel::*)(const String&) const>(&AnimatedModel::GetAnimationState),
            static_cast<AnimationState*(AnimatedModel::*)(const StringHash) const>(&AnimatedModel::GetAnimationState),
            static_cast<AnimationState*(AnimatedModel::*)(unsigned) const>(&AnimatedModel::GetAnimationState))

        .addFunction("GetAnimationLodBias", &AnimatedModel::GetAnimationLodBias)
        .addFunction("GetUpdateInvisible", &AnimatedModel::GetUpdateInvisible)
        .addFunction("GetMorphs", &AnimatedModel::GetMorphs)
        .addFunction("GetNumMorphs", &AnimatedModel::GetNumMorphs)

        .addOverloadedFunctions("GetMorphWeight",
            static_cast<float(AnimatedModel::*)(unsigned) const>(&AnimatedModel::GetMorphWeight),
            static_cast<float(AnimatedModel::*)(const String&) const>(&AnimatedModel::GetMorphWeight),
            static_cast<float(AnimatedModel::*)(StringHash) const>(&AnimatedModel::GetMorphWeight))

        .addFunction("IsMaster", &AnimatedModel::IsMaster)
        
        .addFunction("UpdateBoneBoundingBox", &AnimatedModel::UpdateBoneBoundingBox)

        .addProperty("model", &AnimatedModelModelGetter, &AnimatedModelModelSetter)

        .addProperty("updateGeometryType", &AnimatedModel::GetUpdateGeometryType)
        .addProperty("skeleton", &AnimatedModel::GetSkeleton)
        .addProperty("numAnimationStates", &AnimatedModel::GetNumAnimationStates)
        .addProperty("animationLodBias", &AnimatedModel::GetAnimationLodBias, &AnimatedModel::SetAnimationLodBias)
        .addProperty("updateInvisible", &AnimatedModel::GetUpdateInvisible, &AnimatedModel::SetUpdateInvisible)
        .addProperty("numMorphs", &AnimatedModel::GetNumMorphs)
        .addProperty("master", &AnimatedModel::IsMaster)
        );
}
}

