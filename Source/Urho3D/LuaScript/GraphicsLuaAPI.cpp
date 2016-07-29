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

#include "../Precompiled.h"

#include "../Graphics/Animation.h"
#include "../Graphics/AnimationController.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/DrawableEvents.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Model.h"
#include "../Graphics/Octree.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/Terrain.h"
#include "../Graphics/VertexBuffer.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationClone, Animation, Clone, 0, 1);

static void RegisterAnimation(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CHANNEL_POSITION"] = CHANNEL_POSITION;
    lua["CHANNEL_ROTATION"] = CHANNEL_ROTATION;
    lua["CHANNEL_SCALE"] = CHANNEL_SCALE;

    lua["AnimationKeyFrame"].setClass(UserdataMetatable<AnimationKeyFrame>()
    	
        .addProperty("time", &AnimationKeyFrame::time_)
    	.addProperty("position", &AnimationKeyFrame::position_)
    	.addProperty("rotation", &AnimationKeyFrame::rotation_)
    	.addProperty("scale", &AnimationKeyFrame::scale_)
    	);

	lua["AnimationTrack"].setClass(UserdataMetatable<AnimationTrack>()
    	
        .addFunction("SetKeyFrame", &AnimationTrack::SetKeyFrame)
    	.addFunction("AddKeyFrame", &AnimationTrack::AddKeyFrame)
    	.addFunction("InsertKeyFrame", &AnimationTrack::InsertKeyFrame)
    	.addFunction("RemoveKeyFrame", &AnimationTrack::RemoveKeyFrame)
    	.addFunction("RemoveAllKeyFrames", &AnimationTrack::RemoveAllKeyFrames)
    	.addFunction("GetKeyFrame", &AnimationTrack::GetKeyFrame)
    	.addFunction("GetNumKeyFrames", &AnimationTrack::GetNumKeyFrames)

    	.addProperty("name", &AnimationTrack::name_)
    	.addProperty("nameHash", &AnimationTrack::nameHash_)
    	.addProperty("channelMask", &AnimationTrack::channelMask_)
    	.addProperty("keyFrames", &AnimationTrack::keyFrames_)
    	.addProperty("numKeyFrames", &AnimationTrack::GetNumKeyFrames)
    	);

	lua["AnimationTriggerPoint"].setClass(UserdataMetatable<AnimationTriggerPoint>()
		.setConstructors<AnimationTriggerPoint()>()

		.addProperty("time", &AnimationTriggerPoint::time_)
    	.addProperty("data", &AnimationTriggerPoint::data_)
    	);

    lua["Animation"].setClass(UserdataMetatable<Animation, Resource>()
        .addStaticFunction("new", &CreateObject<Animation>)

        .addFunction("SetAnimationName", &Animation::SetAnimationName)
        .addFunction("SetLength", &Animation::SetLength)

        .addFunction("CreateTrack", &Animation::CreateTrack)
        .addFunction("RemoveTrack", &Animation::RemoveTrack)
        .addFunction("RemoveAllTracks", &Animation::RemoveAllTracks)

		.addFunction("SetTrigger", &Animation::SetTrigger)

        .addOverloadedFunctions("AddTrigger", 
        	static_cast<void(Animation::*)(const AnimationTriggerPoint&)>(&Animation::AddTrigger),
        	static_cast<void(Animation::*)(float, bool, const Variant&)>(&Animation::AddTrigger))
        
        .addFunction("RemoveTrigger", &Animation::RemoveTrigger)
        .addFunction("RemoveAllTriggers", &Animation::RemoveAllTriggers)
        
        .addFunction("Clone", AnimationClone())

        .addFunction("GetAnimationName", &Animation::GetAnimationName)
        .addFunction("GetAnimationNameHash", &Animation::GetAnimationNameHash)
        .addFunction("GetLength", &Animation::GetLength)
        .addFunction("GetNumTracks", &Animation::GetNumTracks)
        
        .addFunction("GetTrack", static_cast<AnimationTrack*(Animation::*)(const String&)>(&Animation::GetTrack))

        .addFunction("GetNumTriggers", &Animation::GetNumTriggers)

        .addFunction("GetTrigger", &Animation::GetTrigger)
        
        .addProperty("animationName", &Animation::GetAnimationName, &Animation::SetAnimationName)
        .addProperty("animationNameHash", &Animation::GetAnimationNameHash)
        .addProperty("length", &Animation::GetLength, &Animation::SetLength)
        .addProperty("numTracks", &Animation::GetNumTracks)
        .addProperty("numTriggers", &Animation::GetNumTriggers, &Animation::SetNumTriggers)
        );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerPlay, AnimationController, Play, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerPlayExclusive, AnimationController, PlayExclusive, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerStop, AnimationController, Stop, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerStopLayer, AnimationController, StopLayer, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimationControllerStopAll, AnimationController, StopAll, 0, 1);

static void RegisterAnimationController(kaguya::State& lua)
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

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(AnimationStateSetBoneWeight0, AnimationState, SetBoneWeight, 2, 3, void(AnimationState::*)(unsigned, float, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(AnimationStateSetBoneWeight1, AnimationState, SetBoneWeight, 2, 3, void(AnimationState::*)(const String&, float, bool));

static void RegisterAnimationState(kaguya::State& lua)
{
    using namespace kaguya;

    // enum AnimationBlendMode;
    lua["ABM_LERP"] = ABM_LERP;
    lua["ABM_ADDITIVE"] = ABM_ADDITIVE;

    lua["AnimationState"].setClass(UserdataMetatable<AnimationState, RefCounted>()
        .setConstructors<AnimationState(AnimatedModel*, Animation*)>()

        .addFunction("SetStartBone", &AnimationState::SetStartBone)
        .addFunction("SetLooped", &AnimationState::SetLooped)
        .addFunction("SetWeight", &AnimationState::SetWeight)
        .addFunction("SetBlendMode", &AnimationState::SetBlendMode)
        .addFunction("SetTime", &AnimationState::SetTime)

        .addOverloadedFunctions("SetBoneWeight", 
            AnimationStateSetBoneWeight0(),
            AnimationStateSetBoneWeight1())

        .addFunction("AddWeight", &AnimationState::AddWeight)
        .addFunction("AddTime", &AnimationState::AddTime)
        .addFunction("SetLayer", &AnimationState::SetLayer)
        .addFunction("GetAnimation", &AnimationState::GetAnimation)
        .addFunction("GetModel", &AnimationState::GetModel)
        .addFunction("GetNode", &AnimationState::GetNode)
        .addFunction("GetStartBone", &AnimationState::GetStartBone)

        .addOverloadedFunctions("GetBoneWeight",
            static_cast<float(AnimationState::*)(unsigned) const>(&AnimationState::GetBoneWeight),
            static_cast<float(AnimationState::*)(const String&) const>(&AnimationState::GetBoneWeight))
        
        .addFunction("GetTrackIndex",
            static_cast<unsigned(AnimationState::*)(const String&) const>(&AnimationState::GetTrackIndex))

        .addFunction("IsEnabled", &AnimationState::IsEnabled)
        .addFunction("IsLooped", &AnimationState::IsLooped)
        .addFunction("GetWeight", &AnimationState::GetWeight)
        .addFunction("GetBlendMode", &AnimationState::GetBlendMode)
        .addFunction("GetTime", &AnimationState::GetTime)
        .addFunction("GetLength", &AnimationState::GetLength)
        .addFunction("GetLayer", &AnimationState::GetLayer)
        .addFunction("Apply", &AnimationState::Apply)

        .addProperty("animation", &AnimationState::GetAnimation)
        .addProperty("model", &AnimationState::GetModel)
        .addProperty("node", &AnimationState::GetNode)
        .addProperty("startBone", &AnimationState::GetStartBone, &AnimationState::SetStartBone)
        .addProperty("enabled", &AnimationState::IsEnabled)
        .addProperty("looped", &AnimationState::IsLooped, &AnimationState::SetLooped)
        .addProperty("weight", &AnimationState::GetWeight, &AnimationState::SetWeight)
        .addProperty("blendMode", &AnimationState::GetBlendMode, &AnimationState::SetBlendMode)
        .addProperty("time", &AnimationState::GetTime, &AnimationState::SetTime)
        .addProperty("length", &AnimationState::GetLength)
        .addProperty("layer", &AnimationState::GetLayer, &AnimationState::SetLayer)
        );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ModelClone, Model, Clone, 0, 1);

static void RegisterModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Model"].setClass(UserdataMetatable<Model, Resource>()
        .addStaticFunction("new", &CreateObject<Model>)

        .addFunction("SetBoundingBox", &Model::SetBoundingBox)
        
        .addFunction("SetNumGeometries", &Model::SetNumGeometries)
        .addFunction("SetNumGeometryLodLevels", &Model::SetNumGeometryLodLevels)
        .addFunction("SetGeometry", &Model::SetGeometry)
        .addFunction("SetGeometryCenter", &Model::SetGeometryCenter)
        .addFunction("SetSkeleton", &Model::SetSkeleton)
        
        .addFunction("Clone", ModelClone())

        .addFunction("GetBoundingBox", &Model::GetBoundingBox)
        .addFunction("GetSkeleton", &Model::GetSkeleton)
        .addFunction("GetNumGeometries", &Model::GetNumGeometries)
        .addFunction("GetNumGeometryLodLevels", &Model::GetNumGeometryLodLevels)
        .addFunction("GetGeometries", &Model::GetGeometries)
        .addFunction("GetGeometryCenters", &Model::GetGeometryCenters)
        .addFunction("GetGeometry", &Model::GetGeometry)
        .addFunction("GetGeometryCenter", &Model::GetGeometryCenter)
        .addFunction("GetNumMorphs", &Model::GetNumMorphs)

        .addOverloadedFunctions("GetMorph",
            static_cast<const ModelMorph*(Model::*)(unsigned) const>(&Model::GetMorph),
            static_cast<const ModelMorph*(Model::*)(const String&) const>(&Model::GetMorph),
            static_cast<const ModelMorph*(Model::*)(StringHash) const>(&Model::GetMorph))

        .addFunction("GetMorphRangeStart", &Model::GetMorphRangeStart)
        .addFunction("GetMorphRangeCount", &Model::GetMorphRangeCount)


        .addProperty("boundingBox", &Model::GetBoundingBox, &Model::SetBoundingBox)
        .addProperty("skeleton", &Model::GetSkeleton)
        .addProperty("numGeometries", &Model::GetNumGeometries, &Model::SetNumGeometries)
        .addProperty("numMorphs", &Model::GetNumMorphs)
        );
}

static PODVector<RayQueryResult> OctreeRaycast(const Octree* self, const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask = DEFAULT_VIEWMASK)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    self->Raycast(query);
    return result;
}

static RayQueryResult OctreeRaycastSingle0(const Octree* self, const Ray& ray)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

static RayQueryResult OctreeRaycastSingle1(const Octree* self, const Ray& ray, RayQueryLevel level)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

static RayQueryResult OctreeRaycastSingle2(const Octree* self, const Ray& ray, RayQueryLevel level, float maxDistance)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

static RayQueryResult OctreeRaycastSingle3(const Octree* self, const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();
    return result[0];
}

static RayQueryResult OctreeRaycastSingle4(const Octree* self, const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

static void RegisterOctree(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Octree"].setClass(UserdataMetatable<Octree, Component>()
        .addStaticFunction("new", &CreateObject<Octree>)

        .addOverloadedFunctions("DrawDebugGeometry",
            static_cast<void(Octree::*)(DebugRenderer*, bool)>(&Octree::DrawDebugGeometry),
            static_cast<void(Octree::*)(bool)>(&Octree::DrawDebugGeometry))

        .addFunction("SetSize", &Octree::SetSize)
        .addFunction("Update", &Octree::Update)
        .addFunction("AddManualDrawable", &Octree::AddManualDrawable)
        .addFunction("RemoveManualDrawable", &Octree::RemoveManualDrawable)

        // .addStaticFunction("GetDrawables", &Octree::GetDrawables)

        .addStaticFunction("Raycast", &OctreeRaycast)
        
        ADD_OVERLOADED_FUNCTIONS_5(Octree, RaycastSingle)

        .addFunction("GetNumLevels", &Octree::GetNumLevels)
        .addFunction("QueueUpdate", &Octree::QueueUpdate)
        
        .addProperty("numLevels", &Octree::GetNumLevels)
        );
}

static void RegisterOctreeQuery(kaguya::State& lua)
{
    using namespace kaguya;

    lua["OctreeQueryResult"].setClass(UserdataMetatable<OctreeQueryResult>()
        .setConstructors<OctreeQueryResult()>()

        .addProperty("drawable", &OctreeQueryResult::drawable_)
        .addProperty("node", &OctreeQueryResult::node_)
        );

    // enum RayQueryLevel;
    lua["RAY_AABB"] = RAY_AABB;
    lua["RAY_OBB"] = RAY_OBB;
    lua["RAY_TRIANGLE"] = RAY_TRIANGLE;
    lua["RAY_TRIANGLE_UV"] = RAY_TRIANGLE_UV;

    lua["RayQueryResult"].setClass(UserdataMetatable<RayQueryResult>()
        .setConstructors<RayQueryResult()>()

        .addProperty("position", &RayQueryResult::position_)
        .addProperty("normal", &RayQueryResult::normal_)
        .addProperty("textureUV", &RayQueryResult::textureUV_)
        .addProperty("distance", &RayQueryResult::distance_)
        .addProperty("drawable", &RayQueryResult::drawable_)
        .addProperty("node", &RayQueryResult::node_)
        .addProperty("subObject", &RayQueryResult::subObject_)
        );
}

static void RegisterParticleEffect(kaguya::State& lua)
{
    using namespace kaguya;

    // enum EmitterType;
    lua["EMITTER_SPHERE"] = EMITTER_SPHERE;
    lua["EMITTER_BOX"] = EMITTER_BOX;


    lua["ColorFrame"].setClass(UserdataMetatable<ColorFrame>()
    	.setConstructors<ColorFrame(),
    		ColorFrame(const Color&),
    		ColorFrame(const Color&, float)>()

		.addFunction("Interpolate", &ColorFrame::Interpolate)
    	.addProperty("color", &ColorFrame::color_)
    	.addProperty("time", &ColorFrame::time_)
    	);

	lua["TextureFrame"].setClass(UserdataMetatable<TextureFrame>()
		.setConstructors<TextureFrame()>()

		.addProperty("uv", &TextureFrame::uv_)
		.addProperty("time", &TextureFrame::time_)
		);

    lua["ParticleEffect"].setClass(UserdataMetatable<ParticleEffect, Resource>()
        .addStaticFunction("new", &CreateObject<ParticleEffect>)

        .addFunction("SetMaterial", &ParticleEffect::SetMaterial)
        .addFunction("SetNumParticles", &ParticleEffect::SetNumParticles)
        .addFunction("SetUpdateInvisible", &ParticleEffect::SetUpdateInvisible)
        .addFunction("SetRelative", &ParticleEffect::SetRelative)
        .addFunction("SetScaled", &ParticleEffect::SetScaled)
        .addFunction("SetSorted", &ParticleEffect::SetSorted)
        
        .addFunction("SetFixedScreenSize", &ParticleEffect::SetFixedScreenSize)
        .addFunction("SetAnimationLodBias", &ParticleEffect::SetAnimationLodBias)
        .addFunction("SetEmitterType", &ParticleEffect::SetEmitterType)
        .addFunction("SetEmitterSize", &ParticleEffect::SetEmitterSize)
        .addFunction("SetMinDirection", &ParticleEffect::SetMinDirection)
        .addFunction("SetMaxDirection", &ParticleEffect::SetMaxDirection)
        
        .addFunction("SetConstantForce", &ParticleEffect::SetConstantForce)
        .addFunction("SetDampingForce", &ParticleEffect::SetDampingForce)
        .addFunction("SetActiveTime", &ParticleEffect::SetActiveTime)
        .addFunction("SetInactiveTime", &ParticleEffect::SetInactiveTime)
        .addFunction("SetMinEmissionRate", &ParticleEffect::SetMinEmissionRate)
        .addFunction("SetMaxEmissionRate", &ParticleEffect::SetMaxEmissionRate)
        
        .addFunction("SetMinParticleSize", &ParticleEffect::SetMinParticleSize)
        .addFunction("SetMaxParticleSize", &ParticleEffect::SetMaxParticleSize)
        .addFunction("SetMinTimeToLive", &ParticleEffect::SetMinTimeToLive)
        .addFunction("SetMaxTimeToLive", &ParticleEffect::SetMaxTimeToLive)
        .addFunction("SetMinVelocity", &ParticleEffect::SetMinVelocity)
        .addFunction("SetMaxVelocity", &ParticleEffect::SetMaxVelocity)
        
        .addFunction("SetMinRotation", &ParticleEffect::SetMinRotation)
        .addFunction("SetMaxRotation", &ParticleEffect::SetMaxRotation)
        .addFunction("SetMinRotationSpeed", &ParticleEffect::SetMinRotationSpeed)
        .addFunction("SetMaxRotationSpeed", &ParticleEffect::SetMaxRotationSpeed)
        .addFunction("SetSizeAdd", &ParticleEffect::SetSizeAdd)
        .addFunction("SetSizeMul", &ParticleEffect::SetSizeMul)
        
        .addFunction("SetFaceCameraMode", &ParticleEffect::SetFaceCameraMode)
        
        .addFunction("AddColorTime", &ParticleEffect::AddColorTime)
        .addFunction("AddColorFrame", &ParticleEffect::AddColorFrame)
        .addFunction("RemoveColorFrame", &ParticleEffect::RemoveColorFrame)
        .addFunction("SetColorFrames", &ParticleEffect::SetColorFrames)
        .addFunction("SetColorFrame", &ParticleEffect::SetColorFrame)
        .addFunction("SetNumColorFrames", &ParticleEffect::SetNumColorFrames)
        .addFunction("SortColorFrames", &ParticleEffect::SortColorFrames)
        
        .addFunction("AddTextureTime", &ParticleEffect::AddTextureTime)
        .addFunction("AddTextureFrame", &ParticleEffect::AddTextureFrame)
        .addFunction("RemoveTextureFrame", &ParticleEffect::RemoveTextureFrame)
        .addFunction("SetTextureFrames", &ParticleEffect::SetTextureFrames)
        .addFunction("SetTextureFrame", &ParticleEffect::SetTextureFrame)
        .addFunction("SetNumTextureFrames", &ParticleEffect::SetNumTextureFrames)
        .addFunction("SortTextureFrames", &ParticleEffect::SortTextureFrames)
        
        .addFunction("GetMaterial", &ParticleEffect::GetMaterial)
        .addFunction("GetNumParticles", &ParticleEffect::GetNumParticles)
        .addFunction("GetUpdateInvisible", &ParticleEffect::GetUpdateInvisible)
        .addFunction("IsRelative", &ParticleEffect::IsRelative)
        .addFunction("IsScaled", &ParticleEffect::IsScaled)
        .addFunction("IsSorted", &ParticleEffect::IsSorted)
        .addFunction("IsFixedScreenSize", &ParticleEffect::IsFixedScreenSize)
        .addFunction("GetAnimationLodBias", &ParticleEffect::GetAnimationLodBias)
        .addFunction("GetEmitterType", &ParticleEffect::GetEmitterType)
        .addFunction("GetEmitterSize", &ParticleEffect::GetEmitterSize)
        .addFunction("GetMinDirection", &ParticleEffect::GetMinDirection)
        .addFunction("GetMaxDirection", &ParticleEffect::GetMaxDirection)
        .addFunction("GetConstantForce", &ParticleEffect::GetConstantForce)
        .addFunction("GetDampingForce", &ParticleEffect::GetDampingForce)
        .addFunction("GetActiveTime", &ParticleEffect::GetActiveTime)
        .addFunction("GetInactiveTime", &ParticleEffect::GetInactiveTime)
        .addFunction("GetMinEmissionRate", &ParticleEffect::GetMinEmissionRate)
        .addFunction("GetMaxEmissionRate", &ParticleEffect::GetMaxEmissionRate)
        .addFunction("GetMinParticleSize", &ParticleEffect::GetMinParticleSize)
        .addFunction("GetMaxParticleSize", &ParticleEffect::GetMaxParticleSize)
        .addFunction("GetMinTimeToLive", &ParticleEffect::GetMinTimeToLive)
        .addFunction("GetMaxTimeToLive", &ParticleEffect::GetMaxTimeToLive)
        .addFunction("GetMinVelocity", &ParticleEffect::GetMinVelocity)
        .addFunction("GetMaxVelocity", &ParticleEffect::GetMaxVelocity)
        .addFunction("GetMinRotation", &ParticleEffect::GetMinRotation)
        .addFunction("GetMaxRotation", &ParticleEffect::GetMaxRotation)
        .addFunction("GetMinRotationSpeed", &ParticleEffect::GetMinRotationSpeed)
        .addFunction("GetMaxRotationSpeed", &ParticleEffect::GetMaxRotationSpeed)
        .addFunction("GetSizeAdd", &ParticleEffect::GetSizeAdd)
        .addFunction("GetSizeMul", &ParticleEffect::GetSizeMul)
        .addFunction("GetColorFrames", &ParticleEffect::GetColorFrames)
        .addFunction("GetNumColorFrames", &ParticleEffect::GetNumColorFrames)
        .addFunction("GetColorFrame", &ParticleEffect::GetColorFrame)
        .addFunction("GetTextureFrames", &ParticleEffect::GetTextureFrames)
        .addFunction("GetNumTextureFrames", &ParticleEffect::GetNumTextureFrames)
        .addFunction("GetTextureFrame", &ParticleEffect::GetTextureFrame)
        .addFunction("GetFaceCameraMode", &ParticleEffect::GetFaceCameraMode)
        
        .addProperty("material", &ParticleEffect::GetMaterial, &ParticleEffect::SetMaterial)
        .addProperty("numParticles", &ParticleEffect::GetNumParticles, &ParticleEffect::SetNumParticles)
        .addProperty("updateInvisible", &ParticleEffect::GetUpdateInvisible, &ParticleEffect::SetUpdateInvisible)
        .addProperty("relative", &ParticleEffect::IsRelative, &ParticleEffect::SetRelative)
        .addProperty("scaled", &ParticleEffect::IsScaled, &ParticleEffect::SetScaled)
        .addProperty("sorted", &ParticleEffect::IsSorted, &ParticleEffect::SetSorted)
        .addProperty("fixedScreenSize", &ParticleEffect::IsFixedScreenSize, &ParticleEffect::SetFixedScreenSize)
        .addProperty("animationLodBias", &ParticleEffect::GetAnimationLodBias, &ParticleEffect::SetAnimationLodBias)
        .addProperty("emitterType", &ParticleEffect::GetEmitterType, &ParticleEffect::SetEmitterType)
        .addProperty("emitterSize", &ParticleEffect::GetEmitterSize, &ParticleEffect::SetEmitterSize)
        .addProperty("minDirection", &ParticleEffect::GetMinDirection, &ParticleEffect::SetMinDirection)
        .addProperty("maxDirection", &ParticleEffect::GetMaxDirection, &ParticleEffect::SetMaxDirection)
        .addProperty("constantForce", &ParticleEffect::GetConstantForce, &ParticleEffect::SetConstantForce)
        .addProperty("dampingForce", &ParticleEffect::GetDampingForce, &ParticleEffect::SetDampingForce)
        .addProperty("activeTime", &ParticleEffect::GetActiveTime, &ParticleEffect::SetActiveTime)
        .addProperty("inactiveTime", &ParticleEffect::GetInactiveTime, &ParticleEffect::SetInactiveTime)
        .addProperty("minEmissionRate", &ParticleEffect::GetMinEmissionRate, &ParticleEffect::SetMinEmissionRate)
        .addProperty("maxEmissionRate", &ParticleEffect::GetMaxEmissionRate, &ParticleEffect::SetMaxEmissionRate)
        .addProperty("minParticleSize", &ParticleEffect::GetMinParticleSize, &ParticleEffect::SetMinParticleSize)
        .addProperty("maxParticleSize", &ParticleEffect::GetMaxParticleSize, &ParticleEffect::SetMaxParticleSize)
        .addProperty("minTimeToLive", &ParticleEffect::GetMinTimeToLive, &ParticleEffect::SetMinTimeToLive)
        .addProperty("maxTimeToLive", &ParticleEffect::GetMaxTimeToLive, &ParticleEffect::SetMaxTimeToLive)
        .addProperty("minVelocity", &ParticleEffect::GetMinVelocity, &ParticleEffect::SetMinVelocity)
        .addProperty("maxVelocity", &ParticleEffect::GetMaxVelocity, &ParticleEffect::SetMaxVelocity)
        .addProperty("minRotation", &ParticleEffect::GetMinRotation, &ParticleEffect::SetMinRotation)
        .addProperty("maxRotation", &ParticleEffect::GetMaxRotation, &ParticleEffect::SetMaxRotation)
        .addProperty("minRotationSpeed", &ParticleEffect::GetMinRotationSpeed, &ParticleEffect::SetMinRotationSpeed)
        .addProperty("maxRotationSpeed", &ParticleEffect::GetMaxRotationSpeed, &ParticleEffect::SetMaxRotationSpeed)
        .addProperty("sizeAdd", &ParticleEffect::GetSizeAdd, &ParticleEffect::SetSizeAdd)
        .addProperty("sizeMul", &ParticleEffect::GetSizeMul, &ParticleEffect::SetSizeMul)
        .addProperty("colorFrames", &ParticleEffect::GetColorFrames, &ParticleEffect::SetColorFrames)
        .addProperty("numColorFrames", &ParticleEffect::GetNumColorFrames, &ParticleEffect::SetNumColorFrames)
        .addProperty("textureFrames", &ParticleEffect::GetTextureFrames, &ParticleEffect::SetTextureFrames)
        .addProperty("numTextureFrames", &ParticleEffect::GetNumTextureFrames, &ParticleEffect::SetNumTextureFrames)
        .addProperty("faceCameraMode", &ParticleEffect::GetFaceCameraMode, &ParticleEffect::SetFaceCameraMode)
        );
}

static void RegisterSkeleton(kaguya::State& lua)
{
    using namespace kaguya;

    lua["BONECOLLISION_NONE"] = BONECOLLISION_NONE;
    lua["BONECOLLISION_SPHERE"] = BONECOLLISION_SPHERE;
    lua["BONECOLLISION_BOX"] = BONECOLLISION_BOX;

	lua["Bone"].setClass(UserdataMetatable<Bone>()
		.setConstructors<Bone()>()

		.addProperty("name", &Bone::name_)
    	.addProperty("nameHash", &Bone::nameHash_)
    	.addProperty("parentIndex", &Bone::parentIndex_)
    	.addProperty("initialPosition", &Bone::initialPosition_)
    	.addProperty("initialRotation", &Bone::initialRotation_)
    	.addProperty("initialScale", &Bone::initialScale_)
    	.addProperty("offsetMatrix", &Bone::offsetMatrix_)
    	.addProperty("animated", &Bone::animated_)
    	.addProperty("collisionMask", &Bone::collisionMask_)
    	.addProperty("radius", &Bone::radius_)
    	.addProperty("boundingBox", &Bone::boundingBox_)
    	.addProperty("node", &Bone::node_)
		);

    lua["Skeleton"].setClass(UserdataMetatable<Skeleton>()
        .setConstructors<Skeleton()>()

        .addFunction("GetNumBones", &Skeleton::GetNumBones)
        .addFunction("GetRootBone", &Skeleton::GetRootBone)

        .addOverloadedFunctions("GetBone",
            static_cast<Bone*(Skeleton::*)(unsigned)>(&Skeleton::GetBone),
            static_cast<Bone*(Skeleton::*)(const char*)>(&Skeleton::GetBone),
            static_cast<Bone*(Skeleton::*)(StringHash)>(&Skeleton::GetBone))

        .addProperty("numBones", &Skeleton::GetNumBones)
        .addProperty("rootBone", &Skeleton::GetRootBone)
        );
}

static Image* TerrainGetHeightMap(const Terrain* terrain)
{
    return terrain->GetHeightMap();
}

static void TerrainSetHeightMap(Terrain* terrain, Image* heightMap)
{
    terrain->SetHeightMap(heightMap);
}

static void RegisterTerrain(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Terrain"].setClass(UserdataMetatable<Terrain, Component>()
        .addStaticFunction("new", &CreateObject<Terrain>)

        .addFunction("SetPatchSize", &Terrain::SetPatchSize)
        .addFunction("SetSpacing", &Terrain::SetSpacing)
        .addFunction("SetMaxLodLevels", &Terrain::SetMaxLodLevels)
        .addFunction("SetOcclusionLodLevel", &Terrain::SetOcclusionLodLevel)
        .addFunction("SetSmoothing", &Terrain::SetSmoothing)
        .addFunction("SetHeightMap", &Terrain::SetHeightMap)
        .addFunction("SetMaterial", &Terrain::SetMaterial)
        .addFunction("SetDrawDistance", &Terrain::SetDrawDistance)
        .addFunction("SetShadowDistance", &Terrain::SetShadowDistance)
        .addFunction("SetLodBias", &Terrain::SetLodBias)
        .addFunction("SetViewMask", &Terrain::SetViewMask)
        .addFunction("SetLightMask", &Terrain::SetLightMask)
        .addFunction("SetShadowMask", &Terrain::SetShadowMask)
        .addFunction("SetZoneMask", &Terrain::SetZoneMask)
        .addFunction("SetMaxLights", &Terrain::SetMaxLights)
        .addFunction("SetCastShadows", &Terrain::SetCastShadows)
        .addFunction("SetOccluder", &Terrain::SetOccluder)
        .addFunction("SetOccludee", &Terrain::SetOccludee)
        .addFunction("ApplyHeightMap", &Terrain::ApplyHeightMap)
        
        .addFunction("GetPatchSize", &Terrain::GetPatchSize)
        .addFunction("GetSpacing", &Terrain::GetSpacing)
        .addFunction("GetNumVertices", &Terrain::GetNumVertices)
        .addFunction("GetNumPatches", &Terrain::GetNumPatches)
        .addFunction("GetMaxLodLevels", &Terrain::GetMaxLodLevels)
        .addFunction("GetOcclusionLodLevel", &Terrain::GetOcclusionLodLevel)
        .addFunction("GetSmoothing", &Terrain::GetSmoothing)
        .addFunction("GetHeightMap", &Terrain::GetHeightMap)
        .addFunction("GetMaterial", &Terrain::GetMaterial)

        .addOverloadedFunctions("GetPatch",
            static_cast<TerrainPatch*(Terrain::*)(unsigned) const>(&Terrain::GetPatch),
            static_cast<TerrainPatch*(Terrain::*)(int, int) const>(&Terrain::GetPatch))

        .addFunction("GetHeight", &Terrain::GetHeight)
        .addFunction("GetNormal", &Terrain::GetNormal)
        .addFunction("WorldToHeightMap", &Terrain::WorldToHeightMap)
        .addFunction("UpdatePatchLod", &Terrain::UpdatePatchLod)

        .addProperty("patchSize", &Terrain::GetPatchSize, &Terrain::SetPatchSize)
        .addProperty("spacing", &Terrain::GetSpacing, &Terrain::SetSpacing)
        .addProperty("numVertices", &Terrain::GetNumVertices)
        .addProperty("numPatches", &Terrain::GetNumPatches)
        .addProperty("maxLodLevels", &Terrain::GetMaxLodLevels, &Terrain::SetMaxLodLevels)
        .addProperty("occlusionLodLevel", &Terrain::GetOcclusionLodLevel, &Terrain::SetOcclusionLodLevel)
        .addProperty("smoothing", &Terrain::GetSmoothing, &Terrain::SetSmoothing)
        .addProperty("heightMap", &TerrainGetHeightMap, &TerrainSetHeightMap)
        .addProperty("material", &Terrain::GetMaterial, &Terrain::SetMaterial)
        .addProperty("drawDistance", &Terrain::SetDrawDistance)
        .addProperty("shadowDistance", &Terrain::SetShadowDistance)
        .addProperty("lodBias", &Terrain::SetLodBias)
        .addProperty("viewMask", &Terrain::SetViewMask)
        .addProperty("lightMask", &Terrain::SetLightMask)
        .addProperty("shadowMask", &Terrain::SetShadowMask)
        .addProperty("zoneMask", &Terrain::SetZoneMask)
        .addProperty("maxLights", &Terrain::SetMaxLights)
        .addProperty("castShadows", &Terrain::SetCastShadows)
        .addProperty("occluder", &Terrain::SetOccluder)
        .addProperty("occludee", &Terrain::SetOccludee)
        );
}

void RegisterGraphicsLuaAPI(kaguya::State& lua)
{
    RegisterAnimation(lua);
    RegisterAnimationController(lua);
    RegisterAnimationState(lua);
    RegisterModel(lua);
    RegisterOctree(lua);
    RegisterOctreeQuery(lua);
    RegisterParticleEffect(lua);
    RegisterSkeleton(lua);
    RegisterTerrain(lua);
}
}
