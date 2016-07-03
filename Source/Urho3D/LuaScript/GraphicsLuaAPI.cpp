#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationController.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/BillboardSet.h"
#include "../Graphics/CustomGeometry.h"
#include "../Graphics/DecalSet.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/DrawableEvents.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Light.h"
#include "../Graphics/Model.h"
#include "../Graphics/Octree.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/ParticleEmitter.h"
#include "../Graphics/RibbonTrail.h"
#include "../Graphics/Skeleton.h"
#include "../Graphics/Skybox.h"
#include "../Graphics/StaticModel.h"
#include "../Graphics/StaticModelGroup.h"
#include "../Graphics/Terrain.h"
#include "../Graphics/TerrainPatch.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Zone.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterAnimatedModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KAnimatedModel"].setClass(UserdataMetatable<AnimatedModel, StaticModel>(false)
        .addStaticFunction("new", &KCreateObject<AnimatedModel>)
        .addStaticFunction("__gc", &KReleaseObject<AnimatedModel>)

        .addFunction("SetModel", &AnimatedModel::SetModel)
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
        .addFunction("GetAnimationStates", &AnimatedModel::GetAnimationStates)
        .addFunction("GetNumAnimationStates", &AnimatedModel::GetNumAnimationStates)

        .addOverloadedFunctions("GetAnimationState",
            static_cast<AnimationState*(AnimatedModel::*)(Animation*) const>(&AnimatedModel::GetAnimationState),
            static_cast<AnimationState*(AnimatedModel::*)(const String&) const>(&AnimatedModel::GetAnimationState),
            static_cast<AnimationState*(AnimatedModel::*)(const StringHash) const>(&AnimatedModel::GetAnimationState),
            static_cast<AnimationState*(AnimatedModel::*)(unsigned) const>(&AnimatedModel::GetAnimationState))

        .addFunction("GetAnimationLodBias", &AnimatedModel::GetAnimationLodBias)
        .addFunction("GetUpdateInvisible", &AnimatedModel::GetUpdateInvisible)
        .addFunction("GetMorphs", &AnimatedModel::GetMorphs)
        .addFunction("GetMorphVertexBuffers", &AnimatedModel::GetMorphVertexBuffers)
        .addFunction("GetNumMorphs", &AnimatedModel::GetNumMorphs)

        .addOverloadedFunctions("GetMorphWeight",
            static_cast<float(AnimatedModel::*)(unsigned) const>(&AnimatedModel::GetMorphWeight),
            static_cast<float(AnimatedModel::*)(const String&) const>(&AnimatedModel::GetMorphWeight),
            static_cast<float(AnimatedModel::*)(StringHash) const>(&AnimatedModel::GetMorphWeight))

        .addFunction("IsMaster", &AnimatedModel::IsMaster)
        .addFunction("GetGeometryBoneMappings", &AnimatedModel::GetGeometryBoneMappings)
        .addFunction("GetGeometrySkinMatrices", &AnimatedModel::GetGeometrySkinMatrices)
        .addFunction("UpdateBoneBoundingBox", &AnimatedModel::UpdateBoneBoundingBox)

        .addProperty("updateGeometryType", &AnimatedModel::GetUpdateGeometryType)
        .addProperty("skeleton", &AnimatedModel::GetSkeleton)
        .addProperty("animationStates", &AnimatedModel::GetAnimationStates)
        .addProperty("numAnimationStates", &AnimatedModel::GetNumAnimationStates)
        .addProperty("animationLodBias", &AnimatedModel::GetAnimationLodBias, &AnimatedModel::SetAnimationLodBias)
        .addProperty("updateInvisible", &AnimatedModel::GetUpdateInvisible, &AnimatedModel::SetUpdateInvisible)
        // .addProperty("morphs", &AnimatedModel::GetMorphs)
        // .addProperty("morphVertexBuffers", &AnimatedModel::GetMorphVertexBuffers)
        .addProperty("numMorphs", &AnimatedModel::GetNumMorphs)
        .addProperty("master", &AnimatedModel::IsMaster)
        .addProperty("geometryBoneMappings", &AnimatedModel::GetGeometryBoneMappings)
        .addProperty("geometrySkinMatrices", &AnimatedModel::GetGeometrySkinMatrices)
    );
}

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

    lua["KAnimation"].setClass(UserdataMetatable<Animation, Resource>(false)
        .addStaticFunction("new", &KCreateObject<Animation>)
        .addStaticFunction("__gc", &KReleaseObject<Animation>)

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

    lua["KAnimationController"].setClass(UserdataMetatable<AnimationController, Component>(false)
        .addStaticFunction("new", &KCreateObject<AnimationController>)
        .addStaticFunction("__gc", &KReleaseObject<AnimationController>)

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

static void RegisterBillboardSet(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KBillboard"].setClass(UserdataMetatable<Billboard>()

        .addProperty("position", &Billboard::position_)
        .addProperty("size", &Billboard::size_)
        .addProperty("uv", &Billboard::uv_)
        .addProperty("color", &Billboard::color_)
        .addProperty("rotation", &Billboard::rotation_)
        .addProperty("direction", &Billboard::direction_)
        .addProperty("enabled", &Billboard::enabled_)
        .addProperty("sortDistance", &Billboard::sortDistance_)
        .addProperty("screenScaleFactor", &Billboard::screenScaleFactor_)
    );

    lua["KMAX_BILLBOARDS"] = MAX_BILLBOARDS;

    lua["KBillboardSet"].setClass(UserdataMetatable<BillboardSet, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<BillboardSet>)
        .addStaticFunction("__gc", &KReleaseObject<BillboardSet>)

        .addFunction("SetMaterial", &BillboardSet::SetMaterial)
        .addFunction("SetNumBillboards", &BillboardSet::SetNumBillboards)
        .addFunction("SetRelative", &BillboardSet::SetRelative)
        .addFunction("SetScaled", &BillboardSet::SetScaled)
        .addFunction("SetSorted", &BillboardSet::SetSorted)
        .addFunction("SetFixedScreenSize", &BillboardSet::SetFixedScreenSize)
        .addFunction("SetFaceCameraMode", &BillboardSet::SetFaceCameraMode)
        .addFunction("SetAnimationLodBias", &BillboardSet::SetAnimationLodBias)
        .addFunction("Commit", &BillboardSet::Commit)
        .addFunction("GetMaterial", &BillboardSet::GetMaterial)
        .addFunction("GetNumBillboards", &BillboardSet::GetNumBillboards)
        .addFunction("GetBillboards", &BillboardSet::GetBillboards)
        .addFunction("GetBillboard", &BillboardSet::GetBillboard)
        .addFunction("IsRelative", &BillboardSet::IsRelative)
        .addFunction("IsScaled", &BillboardSet::IsScaled)
        .addFunction("IsSorted", &BillboardSet::IsSorted)
        .addFunction("IsFixedScreenSize", &BillboardSet::IsFixedScreenSize)
        .addFunction("GetFaceCameraMode", &BillboardSet::GetFaceCameraMode)
        .addFunction("GetAnimationLodBias", &BillboardSet::GetAnimationLodBias)

        .addProperty("material", &BillboardSet::GetMaterial, &BillboardSet::SetMaterial)
        .addProperty("numBillboards", &BillboardSet::GetNumBillboards, &BillboardSet::SetNumBillboards)
        .addProperty("billboards", &BillboardSet::GetBillboards)
        .addProperty("relative", &BillboardSet::IsRelative, &BillboardSet::SetRelative)
        .addProperty("scaled", &BillboardSet::IsScaled, &BillboardSet::SetScaled)
        .addProperty("sorted", &BillboardSet::IsSorted, &BillboardSet::SetSorted)
        .addProperty("fixedScreenSize", &BillboardSet::IsFixedScreenSize, &BillboardSet::SetFixedScreenSize)
        // .addProperty("faceCameraMode", &BillboardSet::GetFaceCameraMode, &BillboardSet::SetFaceCameraMode)
        .addProperty("animationLodBias", &BillboardSet::GetAnimationLodBias, &BillboardSet::SetAnimationLodBias)
    );
}



static void RegisterCustomGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KCustomGeometry"].setClass(UserdataMetatable<CustomGeometry, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<CustomGeometry>)
        .addStaticFunction("__gc", &KReleaseObject<CustomGeometry>)

        .addFunction("GetLodGeometry", &CustomGeometry::GetLodGeometry)
        .addFunction("GetNumOccluderTriangles", &CustomGeometry::GetNumOccluderTriangles)
        .addFunction("DrawOcclusion", &CustomGeometry::DrawOcclusion)
        .addFunction("Clear", &CustomGeometry::Clear)
        .addFunction("SetNumGeometries", &CustomGeometry::SetNumGeometries)
        .addFunction("SetDynamic", &CustomGeometry::SetDynamic)
        .addFunction("BeginGeometry", &CustomGeometry::BeginGeometry)
        .addFunction("DefineVertex", &CustomGeometry::DefineVertex)
        .addFunction("DefineNormal", &CustomGeometry::DefineNormal)
        .addFunction("DefineColor", &CustomGeometry::DefineColor)
        .addFunction("DefineTexCoord", &CustomGeometry::DefineTexCoord)
        .addFunction("DefineTangent", &CustomGeometry::DefineTangent)
        .addFunction("DefineGeometry", &CustomGeometry::DefineGeometry)
        .addFunction("Commit", &CustomGeometry::Commit)

        .addOverloadedFunctions("SetMaterial",
            static_cast<void(CustomGeometry::*)(Material*)>(&CustomGeometry::SetMaterial),
            static_cast<bool(CustomGeometry::*)(unsigned, Material*)>(&CustomGeometry::SetMaterial))

        .addFunction("GetNumGeometries", &CustomGeometry::GetNumGeometries)
        .addFunction("GetNumVertices", &CustomGeometry::GetNumVertices)
        .addFunction("IsDynamic", &CustomGeometry::IsDynamic)
        .addFunction("GetMaterial", &CustomGeometry::GetMaterial)
        .addFunction("GetVertices", &CustomGeometry::GetVertices)
        .addFunction("GetVertex", &CustomGeometry::GetVertex)

        .addProperty("numOccluderTriangles", &CustomGeometry::GetNumOccluderTriangles)
        .addProperty("numGeometries", &CustomGeometry::GetNumGeometries, &CustomGeometry::SetNumGeometries)
        .addProperty("dynamic", &CustomGeometry::IsDynamic, &CustomGeometry::SetDynamic)
        // .addProperty("vertices", &CustomGeometry::GetVertices)
    );
}


static void RegisterDecalSet(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDecalSet"].setClass(UserdataMetatable<DecalSet, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<DecalSet>)
        .addStaticFunction("__gc", &KReleaseObject<DecalSet>)

        .addFunction("SetMaterial", &DecalSet::SetMaterial)
        .addFunction("SetMaxVertices", &DecalSet::SetMaxVertices)
        .addFunction("SetMaxIndices", &DecalSet::SetMaxIndices)
        .addFunction("AddDecal", &DecalSet::AddDecal)
        .addFunction("RemoveDecals", &DecalSet::RemoveDecals)
        .addFunction("RemoveAllDecals", &DecalSet::RemoveAllDecals)
        .addFunction("GetMaterial", &DecalSet::GetMaterial)
        .addFunction("GetNumDecals", &DecalSet::GetNumDecals)
        .addFunction("GetNumVertices", &DecalSet::GetNumVertices)
        .addFunction("GetNumIndices", &DecalSet::GetNumIndices)
        .addFunction("GetMaxVertices", &DecalSet::GetMaxVertices)
        .addFunction("GetMaxIndices", &DecalSet::GetMaxIndices)

        .addProperty("updateGeometryType", &DecalSet::GetUpdateGeometryType)
        .addProperty("material", &DecalSet::GetMaterial, &DecalSet::SetMaterial)
        .addProperty("numDecals", &DecalSet::GetNumDecals)
        .addProperty("numVertices", &DecalSet::GetNumVertices)
        .addProperty("numIndices", &DecalSet::GetNumIndices)
        .addProperty("maxVertices", &DecalSet::GetMaxVertices, &DecalSet::SetMaxVertices)
        .addProperty("maxIndices", &DecalSet::GetMaxIndices, &DecalSet::SetMaxIndices)
    );
}

static void RegisterDrawable(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDRAWABLE_GEOMETRY"] = DRAWABLE_GEOMETRY;
    lua["KDRAWABLE_LIGHT"] = DRAWABLE_LIGHT;
    lua["KDRAWABLE_ZONE"] = DRAWABLE_ZONE;
    lua["KDRAWABLE_GEOMETRY2D"] = DRAWABLE_GEOMETRY2D;
    lua["KDRAWABLE_ANY"] = DRAWABLE_ANY;
    lua["KDEFAULT_VIEWMASK"] = DEFAULT_VIEWMASK;
    lua["KDEFAULT_LIGHTMASK"] = DEFAULT_LIGHTMASK;
    lua["KDEFAULT_SHADOWMASK"] = DEFAULT_SHADOWMASK;
    lua["KDEFAULT_ZONEMASK"] = DEFAULT_ZONEMASK;
    lua["KMAX_VERTEX_LIGHTS"] = MAX_VERTEX_LIGHTS;
    lua["KANIMATION_LOD_BASESCALE"] = ANIMATION_LOD_BASESCALE;

    // enum UpdateGeometryType;
    lua["KUPDATE_NONE"] = UPDATE_NONE;
    lua["KUPDATE_MAIN_THREAD"] = UPDATE_MAIN_THREAD;
    lua["KUPDATE_WORKER_THREAD"] = UPDATE_WORKER_THREAD;

    lua["KSourceBatch"].setClass(UserdataMetatable<SourceBatch>()
        .setConstructors<SourceBatch(),
        SourceBatch(const SourceBatch&)>()

        .addProperty("distance", &SourceBatch::distance_)
        .addProperty("geometry", &SourceBatch::geometry_)
        /*
        .addProperty("material", &SourceBatch::material_)
        .addProperty("worldTransform", &SourceBatch::worldTransform_)
        .addProperty("numWorldTransforms", &SourceBatch::numWorldTransforms_)
        .addProperty("geometryType", &SourceBatch::geometryType_)
        */
    );

    lua["KDrawable"].setClass(UserdataMetatable<Drawable, Component>(false)
        .addStaticFunction("__gc", &KReleaseObject<Drawable>)

        .addFunction("SetDrawDistance", &Drawable::SetDrawDistance)
        .addFunction("SetShadowDistance", &Drawable::SetShadowDistance)
        .addFunction("SetLodBias", &Drawable::SetLodBias)
        .addFunction("SetViewMask", &Drawable::SetViewMask)
        .addFunction("SetLightMask", &Drawable::SetLightMask)
        .addFunction("SetShadowMask", &Drawable::SetShadowMask)
        .addFunction("SetZoneMask", &Drawable::SetZoneMask)
        .addFunction("SetMaxLights", &Drawable::SetMaxLights)
        .addFunction("SetCastShadows", &Drawable::SetCastShadows)
        .addFunction("SetOccluder", &Drawable::SetOccluder)
        .addFunction("SetOccludee", &Drawable::SetOccludee)

        .addFunction("GetBoundingBox", &Drawable::GetBoundingBox)
        .addFunction("GetWorldBoundingBox", &Drawable::GetWorldBoundingBox)
        .addFunction("GetDrawDistance", &Drawable::GetDrawDistance)
        .addFunction("GetShadowDistance", &Drawable::GetShadowDistance)
        .addFunction("GetLodBias", &Drawable::GetLodBias)
        .addFunction("GetViewMask", &Drawable::GetViewMask)
        .addFunction("GetLightMask", &Drawable::GetLightMask)
        .addFunction("GetShadowMask", &Drawable::GetShadowMask)
        .addFunction("GetZoneMask", &Drawable::GetZoneMask)
        .addFunction("GetMaxLights", &Drawable::GetMaxLights)
        .addFunction("GetCastShadows", &Drawable::GetCastShadows)
        .addFunction("IsOccluder", &Drawable::IsOccluder)
        .addFunction("IsOccludee", &Drawable::IsOccludee)

        .addOverloadedFunctions("IsInView",
            static_cast<bool(Drawable::*)() const>(&Drawable::IsInView),
            static_cast<bool(Drawable::*)(Camera*) const>(&Drawable::IsInView))

        .addProperty("boundingBox", &Drawable::GetBoundingBox)
        .addProperty("worldBoundingBox", &Drawable::GetWorldBoundingBox)
        .addProperty("drawDistance", &Drawable::GetDrawDistance, &Drawable::SetDrawDistance)
        .addProperty("shadowDistance", &Drawable::GetShadowDistance, &Drawable::SetShadowDistance)
        .addProperty("lodBias", &Drawable::GetLodBias, &Drawable::SetLodBias)
        .addProperty("viewMask", &Drawable::GetViewMask, &Drawable::SetViewMask)
        .addProperty("lightMask", &Drawable::GetLightMask, &Drawable::SetLightMask)
        .addProperty("shadowMask", &Drawable::GetShadowMask, &Drawable::SetShadowMask)
        .addProperty("zoneMask", &Drawable::GetZoneMask, &Drawable::SetZoneMask)
        .addProperty("maxLights", &Drawable::GetMaxLights, &Drawable::SetMaxLights)
        .addProperty("castShadows", &Drawable::GetCastShadows, &Drawable::SetCastShadows)

        .addProperty("occluder", &Drawable::IsOccluder, &Drawable::SetOccluder)
        .addProperty("occludee", &Drawable::IsOccludee, &Drawable::SetOccludee)
    );
}

static void RegisterDrawableEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KE_BONEHIERARCHYCREATED"] = E_BONEHIERARCHYCREATED;
    lua["KE_ANIMATIONTRIGGER"] = E_ANIMATIONTRIGGER;
    lua["KE_ANIMATIONFINISHED"] = E_ANIMATIONFINISHED;
    lua["KE_PARTICLEEFFECTFINISHED"] = E_PARTICLEEFFECTFINISHED;
    lua["KE_TERRAINCREATED"] = E_TERRAINCREATED;
}

static void RegisterLight(kaguya::State& lua)
{
    using namespace kaguya;

    // enum LightType;
    lua["KLIGHT_DIRECTIONAL"] = LIGHT_DIRECTIONAL;
    lua["KLIGHT_SPOT"] = LIGHT_SPOT;
    lua["KLIGHT_POINT"] = LIGHT_POINT;

    lua["KSHADOW_MIN_QUANTIZE"] = SHADOW_MIN_QUANTIZE;
    lua["KSHADOW_MIN_VIEW"] = SHADOW_MIN_VIEW;
    lua["KMAX_LIGHT_SPLITS"] = MAX_LIGHT_SPLITS;
    lua["KMAX_CASCADE_SPLITS"] = MAX_CASCADE_SPLITS;

    lua["KBiasParameters"].setClass(UserdataMetatable<BiasParameters>()
        .setConstructors<BiasParameters(),
        BiasParameters(float, float, float)>()

        .addFunction("Validate", &BiasParameters::Validate)

        .addProperty("constantBias", &BiasParameters::constantBias_)
        .addProperty("slopeScaledBias", &BiasParameters::slopeScaledBias_)
        .addProperty("normalOffset", &BiasParameters::normalOffset_)
    );

    lua["KCascadeParameters"].setClass(UserdataMetatable<CascadeParameters>()
        .setConstructors<CascadeParameters(),
        CascadeParameters(float, float, float, float, float, float)>()

        .addFunction("Validate", &CascadeParameters::Validate)
        .addFunction("GetShadowRange", &CascadeParameters::GetShadowRange)

        .addProperty("shadowRange", &CascadeParameters::GetShadowRange)
        .addProperty("fadeStart", &CascadeParameters::fadeStart_)
        .addProperty("biasAutoAdjust", &CascadeParameters::biasAutoAdjust_)
    );

    lua["KFocusParameters"].setClass(UserdataMetatable<FocusParameters>()
        .setConstructors<FocusParameters(),
        FocusParameters(bool, bool, bool, float, float)>()

        .addFunction("Validate", &FocusParameters::Validate)

        .addProperty("focus", &FocusParameters::focus_)
        .addProperty("nonUniform", &FocusParameters::nonUniform_)
        .addProperty("autoSize", &FocusParameters::autoSize_)
        .addProperty("quantize", &FocusParameters::quantize_)
        .addProperty("minView", &FocusParameters::minView_)
    );

    lua["KLight"].setClass(UserdataMetatable<Light, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<Light>)
        .addStaticFunction("__gc", &KReleaseObject<Light>)

        //.addFunction("SetLightType", &Light::SetLightType)
        //.addFunction("SetPerVertex", &Light::SetPerVertex)
        //.addFunction("SetColor", &Light::SetColor)
        //.addFunction("SetSpecularIntensity", &Light::SetSpecularIntensity)
        //.addFunction("SetBrightness", &Light::SetBrightness)
        //.addFunction("SetRange", &Light::SetRange)
        //.addFunction("SetFov", &Light::SetFov)
        //.addFunction("SetAspectRatio", &Light::SetAspectRatio)
        //.addFunction("SetFadeDistance", &Light::SetFadeDistance)
        //.addFunction("SetShadowFadeDistance", &Light::SetShadowFadeDistance)
        //// .addFunction("SetShadowBias", &Light::SetShadowBias)
        //// .addFunction("SetShadowCascade", &Light::SetShadowCascade)
        //// .addFunction("SetShadowFocus", &Light::SetShadowFocus)
        //.addFunction("SetShadowIntensity", &Light::SetShadowIntensity)
        //.addFunction("SetShadowResolution", &Light::SetShadowResolution)
        //.addFunction("SetShadowNearFarRatio", &Light::SetShadowNearFarRatio)
        //.addFunction("SetRampTexture", &Light::SetRampTexture)
        //.addFunction("SetShapeTexture", &Light::SetShapeTexture)

        //.addFunction("GetLightType", &Light::GetLightType)
        //.addFunction("GetPerVertex", &Light::GetPerVertex)
        //.addFunction("GetColor", &Light::GetColor)
        //.addFunction("GetSpecularIntensity", &Light::GetSpecularIntensity)
        //.addFunction("GetBrightness", &Light::GetBrightness)
        //.addFunction("GetEffectiveColor", &Light::GetEffectiveColor)
        //.addFunction("GetEffectiveSpecularIntensity", &Light::GetEffectiveSpecularIntensity)
        //.addFunction("GetRange", &Light::GetRange)
        //.addFunction("GetFov", &Light::GetFov)
        //.addFunction("GetAspectRatio", &Light::GetAspectRatio)
        //.addFunction("GetFadeDistance", &Light::GetFadeDistance)
        //.addFunction("GetShadowFadeDistance", &Light::GetShadowFadeDistance)
        //// .addFunction("GetShadowBias", &Light::GetShadowBias)
        //// .addFunction("GetShadowCascade", &Light::GetShadowCascade)
        //// .addFunction("GetShadowFocus", &Light::GetShadowFocus)
        //.addFunction("GetShadowIntensity", &Light::GetShadowIntensity)
        //.addFunction("GetShadowResolution", &Light::GetShadowResolution)
        //.addFunction("GetShadowNearFarRatio", &Light::GetShadowNearFarRatio)
        //.addFunction("GetRampTexture", &Light::GetRampTexture)
        //.addFunction("GetShapeTexture", &Light::GetShapeTexture)
        //.addFunction("GetFrustum", &Light::GetFrustum)
        //.addFunction("GetViewSpaceFrustum", &Light::GetViewSpaceFrustum)
        //.addFunction("GetNumShadowSplits", &Light::GetNumShadowSplits)
        //.addFunction("IsNegative", &Light::IsNegative)

        //.addProperty("lightType", &Light::GetLightType, &Light::SetLightType)
        //.addProperty("perVertex", &Light::GetPerVertex, &Light::SetPerVertex)
        //.addProperty("color", &Light::GetColor, &Light::SetColor)
        //.addProperty("specularIntensity", &Light::GetSpecularIntensity, &Light::SetSpecularIntensity)
        //.addProperty("brightness", &Light::GetBrightness, &Light::SetBrightness)
        //.addProperty("effectiveColor", &Light::GetEffectiveColor)
        //.addProperty("effectiveSpecularIntensity", &Light::GetEffectiveSpecularIntensity)
        //.addProperty("range", &Light::GetRange, &Light::SetRange)
        //.addProperty("fov", &Light::GetFov, &Light::SetFov)
        //.addProperty("aspectRatio", &Light::GetAspectRatio, &Light::SetAspectRatio)
        //.addProperty("fadeDistance", &Light::GetFadeDistance, &Light::SetFadeDistance)
        //.addProperty("shadowFadeDistance", &Light::GetShadowFadeDistance, &Light::SetShadowFadeDistance)
        //// .addProperty("shadowBias", &Light::GetShadowBias, &Light::SetShadowBias)
        //// .addProperty("shadowCascade", &Light::GetShadowCascade, &Light::SetShadowCascade)
        //// .addProperty("shadowFocus", &Light::GetShadowFocus, &Light::SetShadowFocus)
        //.addProperty("shadowIntensity", &Light::GetShadowIntensity, &Light::SetShadowIntensity)
        //.addProperty("shadowResolution", &Light::GetShadowResolution, &Light::SetShadowResolution)
        //.addProperty("shadowNearFarRatio", &Light::GetShadowNearFarRatio, &Light::SetShadowNearFarRatio)
        //.addProperty("rampTexture", &Light::GetRampTexture, &Light::SetRampTexture)
        //.addProperty("shapeTexture", &Light::GetShapeTexture, &Light::SetShapeTexture)
        //.addProperty("frustum", &Light::GetFrustum)
        //.addProperty("numShadowSplits", &Light::GetNumShadowSplits)
        //.addProperty("negative", &Light::IsNegative)
    );
}

static void RegisterModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KModel"].setClass(UserdataMetatable<Model, Resource>(false)
        .addStaticFunction("new", &KCreateObject<Model>)
        .addStaticFunction("__gc", &KReleaseObject<Model>)

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

    lua["KOctree"].setClass(UserdataMetatable<Octree, Component>(false)
        .addStaticFunction("new", &KCreateObject<Octree>)
        .addStaticFunction("__gc", &KReleaseObject<Octree>)

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

    lua["KParticleEffect"].setClass(UserdataMetatable<ParticleEffect, Resource>(false)
        .addStaticFunction("new", &KCreateObject<ParticleEffect>)
        .addStaticFunction("__gc", &KReleaseObject<ParticleEffect>)

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

static void RegisterParticleEmitter(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KParticleEmitter"].setClass(UserdataMetatable<ParticleEmitter, BillboardSet>(false)
        .addStaticFunction("new", &KCreateObject<ParticleEmitter>)
        .addStaticFunction("__gc", &KReleaseObject<ParticleEmitter>)

        .addFunction("SetEffect", &ParticleEmitter::SetEffect)
        .addFunction("SetNumParticles", &ParticleEmitter::SetNumParticles)
        .addFunction("SetEmitting", &ParticleEmitter::SetEmitting)
        .addFunction("SetSerializeParticles", &ParticleEmitter::SetSerializeParticles)
        .addFunction("ResetEmissionTimer", &ParticleEmitter::ResetEmissionTimer)
        .addFunction("RemoveAllParticles", &ParticleEmitter::RemoveAllParticles)
        .addFunction("Reset", &ParticleEmitter::Reset)
        .addFunction("ApplyEffect", &ParticleEmitter::ApplyEffect)
        .addFunction("GetEffect", &ParticleEmitter::GetEffect)
        .addFunction("GetNumParticles", &ParticleEmitter::GetNumParticles)
        .addFunction("IsEmitting", &ParticleEmitter::IsEmitting)
        .addFunction("GetSerializeParticles", &ParticleEmitter::GetSerializeParticles)

        .addProperty("effect", &ParticleEmitter::GetEffect, &ParticleEmitter::SetEffect)
        .addProperty("numParticles", &ParticleEmitter::GetNumParticles, &ParticleEmitter::SetNumParticles)
        .addProperty("emitting", &ParticleEmitter::IsEmitting, &ParticleEmitter::SetEmitting)
        .addProperty("serializeParticles", &ParticleEmitter::GetSerializeParticles, &ParticleEmitter::SetSerializeParticles)
    );
}

static void RegisterRibbonTrail(kaguya::State& lua)
{
    using namespace kaguya;

    // enum TrailType;
    lua["KTT_FACE_CAMERA"] = TT_FACE_CAMERA;
    lua["KTT_BONE"] = TT_BONE;

    lua["KTrailPoint"].setClass(UserdataMetatable<TrailPoint>()

        .addProperty("position", &TrailPoint::position_)
        .addProperty("forward", &TrailPoint::forward_)
        .addProperty("parentPos", &TrailPoint::parentPos_)
        .addProperty("elapsedLength", &TrailPoint::elapsedLength_)
        .addProperty("next", &TrailPoint::next_)
        .addProperty("lifetime", &TrailPoint::lifetime_)
        .addProperty("sortDistance", &TrailPoint::sortDistance_)
    );

    lua["KRibbonTrail"].setClass(UserdataMetatable<RibbonTrail, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<RibbonTrail>)
        .addStaticFunction("__gc", &KReleaseObject<RibbonTrail>)

        .addFunction("SetMaterial", &RibbonTrail::SetMaterial)
        .addFunction("SetVertexDistance", &RibbonTrail::SetVertexDistance)
        .addFunction("SetWidth", &RibbonTrail::SetWidth)
        .addFunction("SetStartColor", &RibbonTrail::SetStartColor)
        .addFunction("SetEndColor", &RibbonTrail::SetEndColor)
        .addFunction("SetStartScale", &RibbonTrail::SetStartScale)
        .addFunction("SetEndScale", &RibbonTrail::SetEndScale)
        .addFunction("SetTrailType", &RibbonTrail::SetTrailType)
        .addFunction("SetSorted", &RibbonTrail::SetSorted)
        .addFunction("SetLifetime", &RibbonTrail::SetLifetime)
        .addFunction("SetEmitting", &RibbonTrail::SetEmitting)
        .addFunction("SetUpdateInvisible", &RibbonTrail::SetUpdateInvisible)
        .addFunction("SetTailColumn", &RibbonTrail::SetTailColumn)
        .addFunction("SetAnimationLodBias", &RibbonTrail::SetAnimationLodBias)
        .addFunction("Commit", &RibbonTrail::Commit)
        .addFunction("GetMaterial", &RibbonTrail::GetMaterial)
        .addFunction("GetVertexDistance", &RibbonTrail::GetVertexDistance)
        .addFunction("GetWidth", &RibbonTrail::GetWidth)
        .addFunction("GetStartColor", &RibbonTrail::GetStartColor)
        .addFunction("GetEndColor", &RibbonTrail::GetEndColor)
        .addFunction("GetStartScale", &RibbonTrail::GetStartScale)
        .addFunction("GetEndScale", &RibbonTrail::GetEndScale)
        .addFunction("IsSorted", &RibbonTrail::IsSorted)
        .addFunction("GetLifetime", &RibbonTrail::GetLifetime)
        .addFunction("GetAnimationLodBias", &RibbonTrail::GetAnimationLodBias)
        .addFunction("GetTrailType", &RibbonTrail::GetTrailType)
        .addFunction("GetTailColumn", &RibbonTrail::GetTailColumn)
        .addFunction("IsEmitting", &RibbonTrail::IsEmitting)
        .addFunction("GetUpdateInvisible", &RibbonTrail::GetUpdateInvisible)

        .addProperty("material", &RibbonTrail::GetMaterial, &RibbonTrail::SetMaterial)
        .addProperty("vertexDistance", &RibbonTrail::GetVertexDistance, &RibbonTrail::SetVertexDistance)
        .addProperty("width", &RibbonTrail::GetWidth, &RibbonTrail::SetWidth)
        .addProperty("startColor", &RibbonTrail::GetStartColor, &RibbonTrail::SetStartColor)
        .addProperty("endColor", &RibbonTrail::GetEndColor, &RibbonTrail::SetEndColor)
        .addProperty("startScale", &RibbonTrail::GetStartScale, &RibbonTrail::SetStartScale)
        .addProperty("endScale", &RibbonTrail::GetEndScale, &RibbonTrail::SetEndScale)
        .addProperty("sorted", &RibbonTrail::IsSorted, &RibbonTrail::SetSorted)
        .addProperty("lifetime", &RibbonTrail::GetLifetime, &RibbonTrail::SetLifetime)
        .addProperty("animationLodBias", &RibbonTrail::GetAnimationLodBias, &RibbonTrail::SetAnimationLodBias)
        .addProperty("trailType", &RibbonTrail::GetTrailType, &RibbonTrail::SetTrailType)
        .addProperty("tailColumn", &RibbonTrail::GetTailColumn, &RibbonTrail::SetTailColumn)
        .addProperty("emitting", &RibbonTrail::IsEmitting, &RibbonTrail::SetEmitting)
        .addProperty("updateInvisible", &RibbonTrail::GetUpdateInvisible, &RibbonTrail::SetUpdateInvisible)
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

static void RegisterSkybox(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KSkybox"].setClass(UserdataMetatable<Skybox, StaticModel>(false)
        .addStaticFunction("new", &KCreateObject<Skybox>)
        .addStaticFunction("__gc", &KReleaseObject<Skybox>)
    );
}

static void RegisterStaticModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KStaticModel"].setClass(UserdataMetatable<StaticModel, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<StaticModel>)
        .addStaticFunction("__gc", &KReleaseObject<StaticModel>)

        .addFunction("SetModel", &StaticModel::SetModel)

        .addOverloadedFunctions("SetMaterial",
            static_cast<void(StaticModel::*)(Material*)>(&StaticModel::SetMaterial),
            static_cast<bool(StaticModel::*)(unsigned, Material*)>(&StaticModel::SetMaterial))

        .addFunction("SetOcclusionLodLevel", &StaticModel::SetOcclusionLodLevel)
        .addFunction("ApplyMaterialList", &StaticModel::ApplyMaterialList)
        .addFunction("GetModel", &StaticModel::GetModel)
        .addFunction("GetNumGeometries", &StaticModel::GetNumGeometries)
        .addFunction("GetMaterial", &StaticModel::GetMaterial)
        .addFunction("GetOcclusionLodLevel", &StaticModel::GetOcclusionLodLevel)
        .addFunction("IsInside", &StaticModel::IsInside)
        .addFunction("IsInsideLocal", &StaticModel::IsInsideLocal)

        .addProperty("model", &StaticModel::GetModel, &StaticModel::SetModel)
        .addProperty("numGeometries", &StaticModel::GetNumGeometries)
        .addProperty("occlusionLodLevel", &StaticModel::GetOcclusionLodLevel, &StaticModel::SetOcclusionLodLevel)
    );
}

static void RegisterStaticModelGroup(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KStaticModelGroup"].setClass(UserdataMetatable<StaticModelGroup, StaticModel>(false)
        .addStaticFunction("new", &KCreateObject<StaticModelGroup>)
        .addStaticFunction("__gc", &KReleaseObject<StaticModelGroup>)

        .addFunction("AddInstanceNode", &StaticModelGroup::AddInstanceNode)
        .addFunction("RemoveInstanceNode", &StaticModelGroup::RemoveInstanceNode)
        .addFunction("RemoveAllInstanceNodes", &StaticModelGroup::RemoveAllInstanceNodes)
        .addFunction("GetNumInstanceNodes", &StaticModelGroup::GetNumInstanceNodes)
        .addFunction("GetInstanceNode", &StaticModelGroup::GetInstanceNode)

        .addProperty("numOccluderTriangles", &StaticModelGroup::GetNumOccluderTriangles)
        .addProperty("numInstanceNodes", &StaticModelGroup::GetNumInstanceNodes)
    );
}

static void RegisterTerrain(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KTerrain"].setClass(UserdataMetatable<Terrain, Component>(false)
        .addStaticFunction("new", &KCreateObject<Terrain>)
        .addStaticFunction("__gc", &KReleaseObject<Terrain>)

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

static void RegisterTerrainPatch(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KTerrainPatch"].setClass(UserdataMetatable<TerrainPatch, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<TerrainPatch>)
        .addStaticFunction("__gc", &KReleaseObject<TerrainPatch>)

        .addFunction("SetOwner", &TerrainPatch::SetOwner)
        .addFunction("SetNeighbors", &TerrainPatch::SetNeighbors)
        .addFunction("SetMaterial", &TerrainPatch::SetMaterial)
        .addFunction("SetBoundingBox", &TerrainPatch::SetBoundingBox)
        .addFunction("SetCoordinates", &TerrainPatch::SetCoordinates)
        .addFunction("ResetLod", &TerrainPatch::ResetLod)
        .addFunction("GetGeometry", &TerrainPatch::GetGeometry)
        .addFunction("GetMaxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
        .addFunction("GetOcclusionGeometry", &TerrainPatch::GetOcclusionGeometry)
        .addFunction("GetVertexBuffer", &TerrainPatch::GetVertexBuffer)
        .addFunction("GetOwner", &TerrainPatch::GetOwner)
        .addFunction("GetNorthPatch", &TerrainPatch::GetNorthPatch)
        .addFunction("GetSouthPatch", &TerrainPatch::GetSouthPatch)
        .addFunction("GetWestPatch", &TerrainPatch::GetWestPatch)
        .addFunction("GetEastPatch", &TerrainPatch::GetEastPatch)
        .addFunction("GetLodErrors", &TerrainPatch::GetLodErrors)
        .addFunction("GetCoordinates", &TerrainPatch::GetCoordinates)
        .addFunction("GetLodLevel", &TerrainPatch::GetLodLevel)

        .addProperty("updateGeometryType", &TerrainPatch::GetUpdateGeometryType)
        .addProperty("numOccluderTriangles", &TerrainPatch::GetNumOccluderTriangles)
        .addProperty("geometry", &TerrainPatch::GetGeometry)
        .addProperty("maxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
        .addProperty("occlusionGeometry", &TerrainPatch::GetOcclusionGeometry)
        .addProperty("vertexBuffer", &TerrainPatch::GetVertexBuffer)
        .addProperty("owner", &TerrainPatch::GetOwner, &TerrainPatch::SetOwner)
        .addProperty("northPatch", &TerrainPatch::GetNorthPatch)
        .addProperty("southPatch", &TerrainPatch::GetSouthPatch)
        .addProperty("westPatch", &TerrainPatch::GetWestPatch)
        .addProperty("eastPatch", &TerrainPatch::GetEastPatch)
        .addProperty("lodErrors", &TerrainPatch::GetLodErrors)
        .addProperty("coordinates", &TerrainPatch::GetCoordinates, &TerrainPatch::SetCoordinates)
        .addProperty("lodLevel", &TerrainPatch::GetLodLevel)
        .addProperty("material", &TerrainPatch::SetMaterial)
        .addProperty("boundingBox", &TerrainPatch::SetBoundingBox)
    );
}

static void RegisterZone(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KZone"].setClass(UserdataMetatable<Zone, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<Zone>)
        .addStaticFunction("__gc", &KReleaseObject<Zone>)

        .addFunction("SetBoundingBox", &Zone::SetBoundingBox)
        .addFunction("SetAmbientColor", &Zone::SetAmbientColor)
        .addFunction("SetFogColor", &Zone::SetFogColor)
        .addFunction("SetFogStart", &Zone::SetFogStart)
        .addFunction("SetFogEnd", &Zone::SetFogEnd)
        .addFunction("SetFogHeight", &Zone::SetFogHeight)
        .addFunction("SetFogHeightScale", &Zone::SetFogHeightScale)
        .addFunction("SetPriority", &Zone::SetPriority)
        .addFunction("SetHeightFog", &Zone::SetHeightFog)
        .addFunction("SetOverride", &Zone::SetOverride)
        .addFunction("SetAmbientGradient", &Zone::SetAmbientGradient)
        .addFunction("SetZoneTexture", &Zone::SetZoneTexture)
        .addFunction("GetInverseWorldTransform", &Zone::GetInverseWorldTransform)
        .addFunction("GetAmbientColor", &Zone::GetAmbientColor)
        .addFunction("GetAmbientStartColor", &Zone::GetAmbientStartColor)
        .addFunction("GetAmbientEndColor", &Zone::GetAmbientEndColor)
        .addFunction("GetFogColor", &Zone::GetFogColor)
        .addFunction("GetFogStart", &Zone::GetFogStart)
        .addFunction("GetFogEnd", &Zone::GetFogEnd)
        .addFunction("GetFogHeight", &Zone::GetFogHeight)
        .addFunction("GetFogHeightScale", &Zone::GetFogHeightScale)
        .addFunction("GetPriority", &Zone::GetPriority)
        .addFunction("GetHeightFog", &Zone::GetHeightFog)
        .addFunction("GetOverride", &Zone::GetOverride)
        .addFunction("GetAmbientGradient", &Zone::GetAmbientGradient)
        .addFunction("GetZoneTexture", &Zone::GetZoneTexture)
        .addFunction("IsInside", &Zone::IsInside)

        .addProperty("inverseWorldTransform", &Zone::GetInverseWorldTransform)
        .addProperty("ambientColor", &Zone::GetAmbientColor, &Zone::SetAmbientColor)
        .addProperty("ambientStartColor", &Zone::GetAmbientStartColor)
        .addProperty("ambientEndColor", &Zone::GetAmbientEndColor)
        .addProperty("fogColor", &Zone::GetFogColor, &Zone::SetFogColor)
        .addProperty("fogStart", &Zone::GetFogStart, &Zone::SetFogStart)
        .addProperty("fogEnd", &Zone::GetFogEnd, &Zone::SetFogEnd)
        .addProperty("fogHeight", &Zone::GetFogHeight, &Zone::SetFogHeight)
        .addProperty("fogHeightScale", &Zone::GetFogHeightScale, &Zone::SetFogHeightScale)
        .addProperty("priority", &Zone::GetPriority, &Zone::SetPriority)
        .addProperty("heightFog", &Zone::GetHeightFog, &Zone::SetHeightFog)
        .addProperty("override", &Zone::GetOverride, &Zone::SetOverride)
        .addProperty("ambientGradient", &Zone::GetAmbientGradient, &Zone::SetAmbientGradient)
        .addProperty("zoneTexture", &Zone::GetZoneTexture, &Zone::SetZoneTexture)
        .addProperty("boundingBox", &Zone::SetBoundingBox)
    );
}

void RegisterGraphicsLuaAPI(kaguya::State& lua)
{
    RegisterDrawable(lua);
    RegisterStaticModel(lua);

    RegisterAnimatedModel(lua);
    RegisterAnimation(lua);
    RegisterAnimationController(lua);
    RegisterAnimationState(lua);
    RegisterBillboardSet(lua);
    RegisterCustomGeometry(lua);
    RegisterDecalSet(lua);
    RegisterDrawableEvents(lua);
    RegisterLight(lua);
    RegisterModel(lua);
    RegisterOctree(lua);
    RegisterOctreeQuery(lua);
    RegisterParticleEffect(lua);
    RegisterParticleEmitter(lua);
    RegisterRibbonTrail(lua);
    RegisterSkeleton(lua);
    RegisterSkybox(lua);
    RegisterStaticModelGroup(lua);
    RegisterTerrain(lua);
    RegisterTerrainPatch(lua);
    RegisterZone(lua);
}
}
