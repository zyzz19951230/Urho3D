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

    // [Class] AnimatedModel : StaticModel
    lua["AnimatedModel"].setClass(UserdataMetatable<AnimatedModel, StaticModel>()
        // [Constructor] AnimatedModel()
        .addStaticFunction("new", &CreateObject<AnimatedModel>)

        // [Method] void SetModel(Model* model, bool createBones = true)
        .addFunction("SetModel", AnimatedModelSetModel())

        // [Method] AnimationState* AddAnimationState(Animation* animation)
        .addFunction("AddAnimationState", &AnimatedModel::AddAnimationState)

        .addOverloadedFunctions("RemoveAnimationState",
            // [Method] void AnimatedModel::RemoveAnimationState(Animation* animation)
            static_cast<void(AnimatedModel::*)(Animation*)>(&AnimatedModel::RemoveAnimationState),
            // [Method] void AnimatedModel::RemoveAnimationState(const String& animationName)
            static_cast<void(AnimatedModel::*)(const String&)>(&AnimatedModel::RemoveAnimationState),
            // [Method] void AnimatedModel::RemoveAnimationState(StringHash animationNameHash)
            static_cast<void(AnimatedModel::*)(StringHash)>(&AnimatedModel::RemoveAnimationState),
            // [Method] void AnimatedModel::RemoveAnimationState(AnimationState* state)
            static_cast<void(AnimatedModel::*)(AnimationState*)>(&AnimatedModel::RemoveAnimationState),
            // [Method] void AnimatedModel::RemoveAnimationState(unsigned index)
            static_cast<void(AnimatedModel::*)(unsigned)>(&AnimatedModel::RemoveAnimationState))

        // [Method] void RemoveAllAnimationStates()
        .addFunction("RemoveAllAnimationStates", &AnimatedModel::RemoveAllAnimationStates)
        // [Method] void SetAnimationLodBias(float bias)
        .addFunction("SetAnimationLodBias", &AnimatedModel::SetAnimationLodBias)
        // [Method] void SetUpdateInvisible(bool enable)
        .addFunction("SetUpdateInvisible", &AnimatedModel::SetUpdateInvisible)

        .addOverloadedFunctions("SetMorphWeight",
            // [Method] void SetMorphWeight(unsigned index, float weight)
            static_cast<void(AnimatedModel::*)(unsigned, float)>(&AnimatedModel::SetMorphWeight),
            // [Method] void SetMorphWeight(const String& name, float weight)
            static_cast<void(AnimatedModel::*)(const String&, float)>(&AnimatedModel::SetMorphWeight),
            // [Method] void SetMorphWeight(StringHash nameHash, float weight)
            static_cast<void(AnimatedModel::*)(StringHash, float)>(&AnimatedModel::SetMorphWeight))

        // [Method] void ResetMorphWeights()
        .addFunction("ResetMorphWeights", &AnimatedModel::ResetMorphWeights)

        // [Method] Skeleton& GetSkeleton()
        .addFunction("GetSkeleton", &AnimatedModel::GetSkeleton)
        
        // [Method] unsigned GetNumAnimationStates() const
        .addFunction("GetNumAnimationStates", &AnimatedModel::GetNumAnimationStates)

        .addOverloadedFunctions("GetAnimationState",
            // [Method] AnimationState* GetAnimationState(Animation* animation) const
            static_cast<AnimationState*(AnimatedModel::*)(Animation*) const>(&AnimatedModel::GetAnimationState),
            // [Method] AnimationState* GetAnimationState(const String& animationName) const
            static_cast<AnimationState*(AnimatedModel::*)(const String&) const>(&AnimatedModel::GetAnimationState),
            // [Method] AnimationState* GetAnimationState(StringHash animationNameHash) const
            static_cast<AnimationState*(AnimatedModel::*)(const StringHash) const>(&AnimatedModel::GetAnimationState),
            // [Method] AnimationState* GetAnimationState(unsigned index) const
            static_cast<AnimationState*(AnimatedModel::*)(unsigned) const>(&AnimatedModel::GetAnimationState))

        // [Method] float GetAnimationLodBias() const
        .addFunction("GetAnimationLodBias", &AnimatedModel::GetAnimationLodBias)
        // [Method] bool GetUpdateInvisible() const
        .addFunction("GetUpdateInvisible", &AnimatedModel::GetUpdateInvisible)
        // [Method] const Vector<ModelMorph>& GetMorphs() const
        .addFunction("GetMorphs", &AnimatedModel::GetMorphs)
        // [Method] unsigned GetNumMorphs() const
        .addFunction("GetNumMorphs", &AnimatedModel::GetNumMorphs)

        .addOverloadedFunctions("GetMorphWeight",
            // [Method] float GetMorphWeight(unsigned index) const
            static_cast<float(AnimatedModel::*)(unsigned) const>(&AnimatedModel::GetMorphWeight),
            // [Method] float GetMorphWeight(const String& name) const
            static_cast<float(AnimatedModel::*)(const String&) const>(&AnimatedModel::GetMorphWeight),
            // [Method] float GetMorphWeight(StringHash nameHash) const
            static_cast<float(AnimatedModel::*)(StringHash) const>(&AnimatedModel::GetMorphWeight))

        // [Method] bool IsMaster() const
        .addFunction("IsMaster", &AnimatedModel::IsMaster)
        
        // [Method] void UpdateBoneBoundingBox()
        .addFunction("UpdateBoneBoundingBox", &AnimatedModel::UpdateBoneBoundingBox)

        // [Property] Model* model
        .addProperty("model", &AnimatedModelModelGetter, &AnimatedModelModelSetter)

        // [Property(Readonly)] UpdateGeometryType updateGeometryType
        .addProperty("updateGeometryType", &AnimatedModel::GetUpdateGeometryType)
        // [Property(Readonly)] Skeleton& skeleton
        .addProperty("skeleton", &AnimatedModel::GetSkeleton)
        // [Property(Readonly)] unsigned numAnimationStates
        .addProperty("numAnimationStates", &AnimatedModel::GetNumAnimationStates)
        // [Property] float animationLodBias
        .addProperty("animationLodBias", &AnimatedModel::GetAnimationLodBias, &AnimatedModel::SetAnimationLodBias)
        // [Property] bool updateInvisible
        .addProperty("updateInvisible", &AnimatedModel::GetUpdateInvisible, &AnimatedModel::SetUpdateInvisible)
        // [Property(Readonly)] unsigned numMorphs
        .addProperty("numMorphs", &AnimatedModel::GetNumMorphs)
        // [Property(Readonly)] bool master
        .addProperty("master", &AnimatedModel::IsMaster)
        );
}
}

