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

static void RegisterAnimation(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KAnimationTrack"].setClass(UserdataMetatable<AnimationTrack>()
        .setConstructors<AnimationTrack()>()

        .addFunction("SetKeyFrame", &AnimationTrack::SetKeyFrame)
        .addFunction("AddKeyFrame", &AnimationTrack::AddKeyFrame)
        .addFunction("InsertKeyFrame", &AnimationTrack::InsertKeyFrame)
        .addFunction("RemoveKeyFrame", &AnimationTrack::RemoveKeyFrame)
        .addFunction("RemoveAllKeyFrames", &AnimationTrack::RemoveAllKeyFrames)
        .addFunction("GetKeyFrame", &AnimationTrack::GetKeyFrame)
        .addFunction("GetNumKeyFrames", &AnimationTrack::GetNumKeyFrames)
        .addFunction("GetKeyFrameIndex", &AnimationTrack::GetKeyFrameIndex)

        .addProperty("numKeyFrames", &AnimationTrack::GetNumKeyFrames)
        .addProperty("name", &AnimationTrack::name_)
        .addProperty("nameHash", &AnimationTrack::nameHash_)
        .addProperty("channelMask", &AnimationTrack::channelMask_)
        .addProperty("keyFrames", &AnimationTrack::keyFrames_)
        );

    lua["KCHANNEL_POSITION"] = CHANNEL_POSITION;
    lua["KCHANNEL_ROTATION"] = CHANNEL_ROTATION;
    lua["KCHANNEL_SCALE"] = CHANNEL_SCALE;

    lua["KAnimation"].setClass(UserdataMetatable<Animation, Resource>()
        .addStaticFunction("new", &KCreateObject<Animation>)

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
        .addFunction("SetNumTriggers", &Animation::SetNumTriggers)
        .addFunction("Clone", &Animation::Clone)
        .addFunction("GetAnimationName", &Animation::GetAnimationName)
        .addFunction("GetAnimationNameHash", &Animation::GetAnimationNameHash)
        .addFunction("GetLength", &Animation::GetLength)
        .addFunction("GetTracks", &Animation::GetTracks)
        .addFunction("GetNumTracks", &Animation::GetNumTracks)

        .addOverloadedFunctions("GetTrack",
            static_cast<AnimationTrack*(Animation::*)(const String&)>(&Animation::GetTrack),
            static_cast<AnimationTrack*(Animation::*)(StringHash)>(&Animation::GetTrack))

        .addFunction("GetTriggers", &Animation::GetTriggers)
        .addFunction("GetNumTriggers", &Animation::GetNumTriggers)
        .addFunction("GetTrigger", &Animation::GetTrigger)

        .addProperty("animationName", &Animation::GetAnimationName, &Animation::SetAnimationName)
        .addProperty("animationNameHash", &Animation::GetAnimationNameHash)
        .addProperty("length", &Animation::GetLength, &Animation::SetLength)
        // .addProperty("tracks", &Animation::GetTracks)
        .addProperty("numTracks", &Animation::GetNumTracks)
        // .addProperty("triggers", &Animation::GetTriggers)
        .addProperty("numTriggers", &Animation::GetNumTriggers, &Animation::SetNumTriggers)
        );
}

static void RegisterAnimationController(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KAnimationController"].setClass(UserdataMetatable<AnimationController, Component>()
        .addStaticFunction("new", &KCreateObject<AnimationController>)

        .addFunction("Play", &AnimationController::Play)
        .addFunction("PlayExclusive", &AnimationController::PlayExclusive)
        .addFunction("Stop", &AnimationController::Stop)
        .addFunction("StopLayer", &AnimationController::StopLayer)
        .addFunction("StopAll", &AnimationController::StopAll)
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

        .addOverloadedFunctions("GetAnimationState",
            static_cast<AnimationState*(AnimationController::*)(const String&) const>(&AnimationController::GetAnimationState),
            static_cast<AnimationState*(AnimationController::*)(StringHash) const>(&AnimationController::GetAnimationState))


        );
}

static void RegisterAnimationState(kaguya::State& lua)
{
    using namespace kaguya;

    // enum AnimationBlendMode;
    lua["KABM_LERP"] = ABM_LERP;
    lua["KABM_ADDITIVE"] = ABM_ADDITIVE;

    lua["KAnimationState"].setClass(UserdataMetatable<AnimationState, RefCounted>()
        .setConstructors<AnimationState(AnimatedModel*, Animation*)>()

        .addFunction("SetStartBone", &AnimationState::SetStartBone)
        .addFunction("SetLooped", &AnimationState::SetLooped)
        .addFunction("SetWeight", &AnimationState::SetWeight)
        .addFunction("SetBlendMode", &AnimationState::SetBlendMode)
        .addFunction("SetTime", &AnimationState::SetTime)

        .addOverloadedFunctions("SetBoneWeight",
            static_cast<void(AnimationState::*)(unsigned, float, bool)>(&AnimationState::SetBoneWeight),
            static_cast<void(AnimationState::*)(const String&, float, bool)>(&AnimationState::SetBoneWeight))

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


        /*
        .addOverloadedFunctions("GetTrackIndex",
            static_cast<unsigned(AnimationState::*)(int*) const>(&AnimationState::GetTrackIndex),
            static_cast<unsigned(AnimationState::*)(const String&) const>(&AnimationState::GetTrackIndex))
            */

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

static void RegisterModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KModel"].setClass(UserdataMetatable<Model, Resource>()
        .addStaticFunction("new", &KCreateObject<Model>)

        .addFunction("SetBoundingBox", &Model::SetBoundingBox)
        .addFunction("SetVertexBuffers", &Model::SetVertexBuffers)
        .addFunction("SetIndexBuffers", &Model::SetIndexBuffers)
        .addFunction("SetNumGeometries", &Model::SetNumGeometries)
        .addFunction("SetNumGeometryLodLevels", &Model::SetNumGeometryLodLevels)
        .addFunction("SetGeometry", &Model::SetGeometry)
        .addFunction("SetGeometryCenter", &Model::SetGeometryCenter)
        .addFunction("SetSkeleton", &Model::SetSkeleton)
        .addFunction("SetGeometryBoneMappings", &Model::SetGeometryBoneMappings)
        .addFunction("SetMorphs", &Model::SetMorphs)
        .addFunction("Clone", &Model::Clone)

        .addFunction("GetBoundingBox", &Model::GetBoundingBox)
        .addFunction("GetSkeleton", &Model::GetSkeleton)
        .addFunction("GetVertexBuffers", &Model::GetVertexBuffers)
        .addFunction("GetIndexBuffers", &Model::GetIndexBuffers)
        .addFunction("GetNumGeometries", &Model::GetNumGeometries)
        .addFunction("GetNumGeometryLodLevels", &Model::GetNumGeometryLodLevels)
        .addFunction("GetGeometries", &Model::GetGeometries)
        .addFunction("GetGeometryCenters", &Model::GetGeometryCenters)
        .addFunction("GetGeometry", &Model::GetGeometry)
        .addFunction("GetGeometryCenter", &Model::GetGeometryCenter)
        .addFunction("GetGeometryBoneMappings", &Model::GetGeometryBoneMappings)
        .addFunction("GetMorphs", &Model::GetMorphs)
        .addFunction("GetNumMorphs", &Model::GetNumMorphs)

        .addOverloadedFunctions("GetMorph",
            static_cast<const ModelMorph*(Model::*)(unsigned) const>(&Model::GetMorph),
            static_cast<const ModelMorph*(Model::*)(const String&) const>(&Model::GetMorph),
            static_cast<const ModelMorph*(Model::*)(StringHash) const>(&Model::GetMorph))

        .addFunction("GetMorphRangeStart", &Model::GetMorphRangeStart)
        .addFunction("GetMorphRangeCount", &Model::GetMorphRangeCount)


        .addProperty("boundingBox", &Model::GetBoundingBox, &Model::SetBoundingBox)
        .addProperty("numGeometries", &Model::GetNumGeometries, &Model::SetNumGeometries)
        .addProperty("numMorphs", &Model::GetNumMorphs)
        );
}

static void RegisterOctree(kaguya::State& lua)
{
    using namespace kaguya;

    // lua["KNUM_OCTANTS"] = NUM_OCTANTS;
    // lua["KROOT_INDEX"] = ROOT_INDEX;

    lua["KOctant"].setClass(UserdataMetatable<Octant>()
        .setConstructors<Octant(const BoundingBox&, unsigned, Octant*, Octree*, unsigned)>()

        .addFunction("GetOrCreateChild", &Octant::GetOrCreateChild)
        .addFunction("DeleteChild", &Octant::DeleteChild)
        .addFunction("InsertDrawable", &Octant::InsertDrawable)
        .addFunction("CheckDrawableFit", &Octant::CheckDrawableFit)
        .addFunction("AddDrawable", &Octant::AddDrawable)
        .addFunction("RemoveDrawable", &Octant::RemoveDrawable)
        .addFunction("GetWorldBoundingBox", &Octant::GetWorldBoundingBox)
        .addFunction("GetCullingBox", &Octant::GetCullingBox)
        .addFunction("GetLevel", &Octant::GetLevel)
        .addFunction("GetParent", &Octant::GetParent)
        .addFunction("GetRoot", &Octant::GetRoot)
        .addFunction("GetNumDrawables", &Octant::GetNumDrawables)
        .addFunction("IsEmpty", &Octant::IsEmpty)
        .addFunction("ResetRoot", &Octant::ResetRoot)
        .addFunction("DrawDebugGeometry", &Octant::DrawDebugGeometry)

        .addProperty("worldBoundingBox", &Octant::GetWorldBoundingBox)
        .addProperty("cullingBox", &Octant::GetCullingBox)
        .addProperty("level", &Octant::GetLevel)
        .addProperty("parent", &Octant::GetParent)
        .addProperty("root", &Octant::GetRoot)
        .addProperty("numDrawables", &Octant::GetNumDrawables)
        .addProperty("empty", &Octant::IsEmpty)
        );

    lua["KOctree"].setClass(UserdataMetatable<Octree, Component>()
        .addStaticFunction("new", &KCreateObject<Octree>)

        .addOverloadedFunctions("DrawDebugGeometry",
            static_cast<void(Octree::*)(DebugRenderer*, bool)>(&Octree::DrawDebugGeometry),
            static_cast<void(Octree::*)(bool)>(&Octree::DrawDebugGeometry))

        .addFunction("SetSize", &Octree::SetSize)
        .addFunction("Update", &Octree::Update)
        .addFunction("AddManualDrawable", &Octree::AddManualDrawable)
        .addFunction("RemoveManualDrawable", &Octree::RemoveManualDrawable)
        .addFunction("GetDrawables", &Octree::GetDrawables)
        .addFunction("Raycast", &Octree::Raycast)
        .addFunction("RaycastSingle", &Octree::RaycastSingle)
        .addFunction("GetNumLevels", &Octree::GetNumLevels)
        .addFunction("QueueUpdate", &Octree::QueueUpdate)
        .addFunction("CancelUpdate", &Octree::CancelUpdate)

        .addProperty("numLevels", &Octree::GetNumLevels)
        );
}

static void RegisterOctreeQuery(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KOctreeQueryResult"].setClass(UserdataMetatable<OctreeQueryResult>()
        .setConstructors<OctreeQueryResult()>()

        .addProperty("drawable", &OctreeQueryResult::drawable_)
        .addProperty("node", &OctreeQueryResult::node_)
        );

    // enum RayQueryLevel;
    lua["KRAY_AABB"] = RAY_AABB;
    lua["KRAY_OBB"] = RAY_OBB;
    lua["KRAY_TRIANGLE"] = RAY_TRIANGLE;
    lua["KRAY_TRIANGLE_UV"] = RAY_TRIANGLE_UV;

    lua["KRayQueryResult"].setClass(UserdataMetatable<RayQueryResult>()
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
    lua["KEMITTER_SPHERE"] = EMITTER_SPHERE;
    lua["KEMITTER_BOX"] = EMITTER_BOX;

    lua["KDEFAULT_NUM_PARTICLES"] = DEFAULT_NUM_PARTICLES;

    lua["KParticleEffect"].setClass(UserdataMetatable<ParticleEffect, Resource>()
        .addStaticFunction("new", &KCreateObject<ParticleEffect>)

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
        .addFunction("GetRandomDirection", &ParticleEffect::GetRandomDirection)
        .addFunction("GetRandomSize", &ParticleEffect::GetRandomSize)
        .addFunction("GetRandomVelocity", &ParticleEffect::GetRandomVelocity)
        .addFunction("GetRandomTimeToLive", &ParticleEffect::GetRandomTimeToLive)
        .addFunction("GetRandomRotationSpeed", &ParticleEffect::GetRandomRotationSpeed)
        .addFunction("GetRandomRotation", &ParticleEffect::GetRandomRotation)

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
        .addProperty("randomDirection", &ParticleEffect::GetRandomDirection)
        .addProperty("randomSize", &ParticleEffect::GetRandomSize)
        .addProperty("randomVelocity", &ParticleEffect::GetRandomVelocity)
        .addProperty("randomTimeToLive", &ParticleEffect::GetRandomTimeToLive)
        .addProperty("randomRotationSpeed", &ParticleEffect::GetRandomRotationSpeed)
        .addProperty("randomRotation", &ParticleEffect::GetRandomRotation)
        );
}

static void RegisterSkeleton(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KBONECOLLISION_NONE"] = BONECOLLISION_NONE;
    lua["KBONECOLLISION_SPHERE"] = BONECOLLISION_SPHERE;
    lua["KBONECOLLISION_BOX"] = BONECOLLISION_BOX;

    lua["KSkeleton"].setClass(UserdataMetatable<Skeleton>()
        .setConstructors<Skeleton()>()

        .addFunction("Load", &Skeleton::Load)
        .addFunction("Save", &Skeleton::Save)
        .addFunction("Define", &Skeleton::Define)
        .addFunction("SetRootBoneIndex", &Skeleton::SetRootBoneIndex)
        .addFunction("ClearBones", &Skeleton::ClearBones)
        .addFunction("Reset", &Skeleton::Reset)
        .addFunction("GetBones", &Skeleton::GetBones)
        .addFunction("GetModifiableBones", &Skeleton::GetModifiableBones)
        .addFunction("GetNumBones", &Skeleton::GetNumBones)
        .addFunction("GetRootBone", &Skeleton::GetRootBone)

        .addOverloadedFunctions("GetBone",
            static_cast<Bone*(Skeleton::*)(unsigned)>(&Skeleton::GetBone),
            static_cast<Bone*(Skeleton::*)(const char*)>(&Skeleton::GetBone),
            static_cast<Bone*(Skeleton::*)(StringHash)>(&Skeleton::GetBone))

        .addFunction("ResetSilent", &Skeleton::ResetSilent)

        .addProperty("bones", &Skeleton::GetBones)
        .addProperty("modifiableBones", &Skeleton::GetModifiableBones)
        .addProperty("numBones", &Skeleton::GetNumBones)
        .addProperty("rootBone", &Skeleton::GetRootBone)
        .addProperty("rootBoneIndex", &Skeleton::SetRootBoneIndex)
        );
}
static void RegisterTerrain(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KTerrain"].setClass(UserdataMetatable<Terrain, Component>()
        .addStaticFunction("new", &KCreateObject<Terrain>)

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
