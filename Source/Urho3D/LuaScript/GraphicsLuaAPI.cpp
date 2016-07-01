#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationController.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/BillboardSet.h"
#include "../Graphics/Camera.h"
#include "../Graphics/CustomGeometry.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/DecalSet.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/DrawableEvents.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/GPUObject.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Graphics/GraphicsImpl.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "../Graphics/Model.h"
#include "../Graphics/OcclusionBuffer.h"
#include "../Graphics/Octree.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/ParticleEmitter.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/RibbonTrail.h"
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderPrecache.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/ShaderVariation.h"
#include "../Graphics/Skeleton.h"
#include "../Graphics/Skybox.h"
#include "../Graphics/StaticModel.h"
#include "../Graphics/StaticModelGroup.h"
#include "../Graphics/Tangent.h"
#include "../Graphics/Technique.h"
#include "../Graphics/Terrain.h"
#include "../Graphics/TerrainPatch.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Texture2DArray.h"
#include "../Graphics/Texture3D.h"
#include "../Graphics/TextureCube.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/VertexDeclaration.h"
#include "../Graphics/View.h"
#include "../Graphics/Viewport.h"
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

        .addFunction("GetType", &AnimatedModel::GetType)
        .addFunction("GetTypeName", &AnimatedModel::GetTypeName)
        .addFunction("GetTypeInfo", &AnimatedModel::GetTypeInfo)

        .addStaticFunction("GetTypeStatic", &AnimatedModel::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &AnimatedModel::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &AnimatedModel::GetTypeInfoStatic)

        .addFunction("SetModel", &AnimatedModel::SetModel)
        .addFunction("AddAnimationState", &AnimatedModel::AddAnimationState)

        .addOverloadedFunctions("RemoveAnimationState",
            static_cast<void(AnimatedModel::*)(Animation*)>(&AnimatedModel::RemoveAnimationState),
            static_cast<void(AnimatedModel::*)(const String&)>(&AnimatedModel::RemoveAnimationState),
            static_cast<void(AnimatedModel::*)(StringHash)>(&AnimatedModel::RemoveAnimationState),
            static_cast<void(AnimatedModel::*)(AnimationState*)>(&AnimatedModel::RemoveAnimationState),
            static_cast<void(AnimatedModel::*)(unsigned int)>(&AnimatedModel::RemoveAnimationState))

        .addFunction("RemoveAllAnimationStates", &AnimatedModel::RemoveAllAnimationStates)
        .addFunction("SetAnimationLodBias", &AnimatedModel::SetAnimationLodBias)
        .addFunction("SetUpdateInvisible", &AnimatedModel::SetUpdateInvisible)

        .addOverloadedFunctions("SetMorphWeight",
            static_cast<void(AnimatedModel::*)(unsigned int, float)>(&AnimatedModel::SetMorphWeight),
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
            static_cast<AnimationState*(AnimatedModel::*)(unsigned int) const>(&AnimatedModel::GetAnimationState))

        .addFunction("GetAnimationLodBias", &AnimatedModel::GetAnimationLodBias)
        .addFunction("GetUpdateInvisible", &AnimatedModel::GetUpdateInvisible)
        .addFunction("GetMorphs", &AnimatedModel::GetMorphs)
        .addFunction("GetMorphVertexBuffers", &AnimatedModel::GetMorphVertexBuffers)
        .addFunction("GetNumMorphs", &AnimatedModel::GetNumMorphs)

        .addOverloadedFunctions("GetMorphWeight",
            static_cast<float(AnimatedModel::*)(unsigned int) const>(&AnimatedModel::GetMorphWeight),
            static_cast<float(AnimatedModel::*)(const String&) const>(&AnimatedModel::GetMorphWeight),
            static_cast<float(AnimatedModel::*)(StringHash) const>(&AnimatedModel::GetMorphWeight))

        .addFunction("IsMaster", &AnimatedModel::IsMaster)
        .addFunction("GetGeometryBoneMappings", &AnimatedModel::GetGeometryBoneMappings)
        .addFunction("GetGeometrySkinMatrices", &AnimatedModel::GetGeometrySkinMatrices)
        .addFunction("UpdateBoneBoundingBox", &AnimatedModel::UpdateBoneBoundingBox)

        .addProperty("type", &AnimatedModel::GetType)
        .addProperty("typeName", &AnimatedModel::GetTypeName)
        .addProperty("typeInfo", &AnimatedModel::GetTypeInfo)
        .addProperty("updateGeometryType", &AnimatedModel::GetUpdateGeometryType)
        .addProperty("skeleton", &AnimatedModel::GetSkeleton)
        .addProperty("animationStates", &AnimatedModel::GetAnimationStates)
        .addProperty("numAnimationStates", &AnimatedModel::GetNumAnimationStates)
        .addProperty("animationLodBias", &AnimatedModel::GetAnimationLodBias, &AnimatedModel::SetAnimationLodBias)
        .addProperty("updateInvisible", &AnimatedModel::GetUpdateInvisible, &AnimatedModel::SetUpdateInvisible)
        .addProperty("morphs", &AnimatedModel::GetMorphs)
        .addProperty("morphVertexBuffers", &AnimatedModel::GetMorphVertexBuffers)
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

        .addFunction("GetType", &Animation::GetType)
        .addFunction("GetTypeName", &Animation::GetTypeName)
        .addFunction("GetTypeInfo", &Animation::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &Animation::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &Animation::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &Animation::GetTypeInfoStatic)

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

        .addProperty("type", &Animation::GetType)
        .addProperty("typeName", &Animation::GetTypeName)
        .addProperty("typeInfo", &Animation::GetTypeInfo)
        .addProperty("animationName", &Animation::GetAnimationName, &Animation::SetAnimationName)
        .addProperty("animationNameHash", &Animation::GetAnimationNameHash)
        .addProperty("length", &Animation::GetLength, &Animation::SetLength)
        .addProperty("tracks", &Animation::GetTracks)
        .addProperty("numTracks", &Animation::GetNumTracks)
        .addProperty("triggers", &Animation::GetTriggers)
        .addProperty("numTriggers", &Animation::GetNumTriggers, &Animation::SetNumTriggers)
        );
}

static void RegisterAnimationController(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KAnimationController"].setClass(UserdataMetatable<AnimationController, Component>(false)
        .addStaticFunction("new", &KCreateObject<AnimationController>)
        .addStaticFunction("__gc", &KReleaseObject<AnimationController>)

        .addFunction("GetType", &AnimationController::GetType)
        .addFunction("GetTypeName", &AnimationController::GetTypeName)
        .addFunction("GetTypeInfo", &AnimationController::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &AnimationController::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &AnimationController::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &AnimationController::GetTypeInfoStatic)

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


        .addProperty("type", &AnimationController::GetType)
        .addProperty("typeName", &AnimationController::GetTypeName)
        .addProperty("typeInfo", &AnimationController::GetTypeInfo)
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
            static_cast<void(AnimationState::*)(unsigned int, float, bool)>(&AnimationState::SetBoneWeight),
            static_cast<void(AnimationState::*)(const String&, float, bool)>(&AnimationState::SetBoneWeight))

        .addFunction("AddWeight", &AnimationState::AddWeight)
        .addFunction("AddTime", &AnimationState::AddTime)
        .addFunction("SetLayer", &AnimationState::SetLayer)
        .addFunction("GetAnimation", &AnimationState::GetAnimation)
        .addFunction("GetModel", &AnimationState::GetModel)
        .addFunction("GetNode", &AnimationState::GetNode)
        .addFunction("GetStartBone", &AnimationState::GetStartBone)

        .addOverloadedFunctions("GetBoneWeight",
            static_cast<float(AnimationState::*)(unsigned int) const>(&AnimationState::GetBoneWeight),
            static_cast<float(AnimationState::*)(const String&) const>(&AnimationState::GetBoneWeight))


        /*
        .addOverloadedFunctions("GetTrackIndex",
            static_cast<unsigned int(AnimationState::*)(int*) const>(&AnimationState::GetTrackIndex),
            static_cast<unsigned int(AnimationState::*)(const String&) const>(&AnimationState::GetTrackIndex))
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

        .addFunction("GetType", &BillboardSet::GetType)
        .addFunction("GetTypeName", &BillboardSet::GetTypeName)
        .addFunction("GetTypeInfo", &BillboardSet::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &BillboardSet::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &BillboardSet::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &BillboardSet::GetTypeInfoStatic)

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

        .addProperty("type", &BillboardSet::GetType)
        .addProperty("typeName", &BillboardSet::GetTypeName)
        .addProperty("typeInfo", &BillboardSet::GetTypeInfo)
        .addProperty("material", &BillboardSet::GetMaterial, &BillboardSet::SetMaterial)
        .addProperty("numBillboards", &BillboardSet::GetNumBillboards, &BillboardSet::SetNumBillboards)
        .addProperty("billboards", &BillboardSet::GetBillboards)
        .addProperty("relative", &BillboardSet::IsRelative, &BillboardSet::SetRelative)
        .addProperty("scaled", &BillboardSet::IsScaled, &BillboardSet::SetScaled)
        .addProperty("sorted", &BillboardSet::IsSorted, &BillboardSet::SetSorted)
        .addProperty("fixedScreenSize", &BillboardSet::IsFixedScreenSize, &BillboardSet::SetFixedScreenSize)
        .addProperty("faceCameraMode", &BillboardSet::GetFaceCameraMode, &BillboardSet::SetFaceCameraMode)
        .addProperty("animationLodBias", &BillboardSet::GetAnimationLodBias, &BillboardSet::SetAnimationLodBias)
        );
}

static void RegisterCamera(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDEFAULT_NEARCLIP"] = DEFAULT_NEARCLIP;
    lua["KDEFAULT_FARCLIP"] = DEFAULT_FARCLIP;
    lua["KDEFAULT_CAMERA_FOV"] = DEFAULT_CAMERA_FOV;
    lua["KDEFAULT_ORTHOSIZE"] = DEFAULT_ORTHOSIZE;
    lua["KVO_NONE"] = VO_NONE;
    lua["KVO_LOW_MATERIAL_QUALITY"] = VO_LOW_MATERIAL_QUALITY;
    lua["KVO_DISABLE_SHADOWS"] = VO_DISABLE_SHADOWS;
    lua["KVO_DISABLE_OCCLUSION"] = VO_DISABLE_OCCLUSION;

    lua["KCamera"].setClass(UserdataMetatable<Camera, Component>(false)
        .addStaticFunction("new", &KCreateObject<Camera>)
        .addStaticFunction("__gc", &KReleaseObject<Camera>)

        .addFunction("GetType", &Camera::GetType)
        .addFunction("GetTypeName", &Camera::GetTypeName)
        .addFunction("GetTypeInfo", &Camera::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &Camera::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &Camera::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &Camera::GetTypeInfoStatic)

        .addFunction("SetNearClip", &Camera::SetNearClip)
        .addFunction("SetFarClip", &Camera::SetFarClip)
        .addFunction("SetFov", &Camera::SetFov)

        .addOverloadedFunctions("SetOrthoSize",
            static_cast<void(Camera::*)(float)>(&Camera::SetOrthoSize),
            static_cast<void(Camera::*)(const Vector2&)>(&Camera::SetOrthoSize))

        .addFunction("SetAspectRatio", &Camera::SetAspectRatio)
        .addFunction("SetFillMode", &Camera::SetFillMode)
        .addFunction("SetZoom", &Camera::SetZoom)
        .addFunction("SetLodBias", &Camera::SetLodBias)
        .addFunction("SetViewMask", &Camera::SetViewMask)
        .addFunction("SetViewOverrideFlags", &Camera::SetViewOverrideFlags)
        .addFunction("SetOrthographic", &Camera::SetOrthographic)
        .addFunction("SetAutoAspectRatio", &Camera::SetAutoAspectRatio)
        .addFunction("SetProjectionOffset", &Camera::SetProjectionOffset)
        .addFunction("SetUseReflection", &Camera::SetUseReflection)
        .addFunction("SetReflectionPlane", &Camera::SetReflectionPlane)
        .addFunction("SetUseClipping", &Camera::SetUseClipping)
        .addFunction("SetClipPlane", &Camera::SetClipPlane)
        .addFunction("SetFlipVertical", &Camera::SetFlipVertical)
        .addFunction("GetFarClip", &Camera::GetFarClip)
        .addFunction("GetNearClip", &Camera::GetNearClip)
        .addFunction("GetFov", &Camera::GetFov)
        .addFunction("GetOrthoSize", &Camera::GetOrthoSize)
        .addFunction("GetAspectRatio", &Camera::GetAspectRatio)
        .addFunction("GetZoom", &Camera::GetZoom)
        .addFunction("GetLodBias", &Camera::GetLodBias)
        .addFunction("GetViewMask", &Camera::GetViewMask)
        .addFunction("GetViewOverrideFlags", &Camera::GetViewOverrideFlags)
        .addFunction("GetFillMode", &Camera::GetFillMode)
        .addFunction("IsOrthographic", &Camera::IsOrthographic)
        .addFunction("GetAutoAspectRatio", &Camera::GetAutoAspectRatio)
        .addFunction("GetFrustum", &Camera::GetFrustum)

        .addOverloadedFunctions("GetProjection",
            static_cast<const Matrix4&(Camera::*)() const>(&Camera::GetProjection),
            static_cast<Matrix4(Camera::*)(bool) const>(&Camera::GetProjection))

        .addFunction("GetView", &Camera::GetView)
        .addFunction("GetFrustumSize", &Camera::GetFrustumSize)
        .addFunction("GetHalfViewSize", &Camera::GetHalfViewSize)
        .addFunction("GetSplitFrustum", &Camera::GetSplitFrustum)
        .addFunction("GetViewSpaceFrustum", &Camera::GetViewSpaceFrustum)
        .addFunction("GetViewSpaceSplitFrustum", &Camera::GetViewSpaceSplitFrustum)
        .addFunction("GetScreenRay", &Camera::GetScreenRay)
        .addFunction("WorldToScreenPoint", &Camera::WorldToScreenPoint)
        .addFunction("ScreenToWorldPoint", &Camera::ScreenToWorldPoint)
        .addFunction("GetProjectionOffset", &Camera::GetProjectionOffset)
        .addFunction("GetUseReflection", &Camera::GetUseReflection)
        .addFunction("GetReflectionPlane", &Camera::GetReflectionPlane)
        .addFunction("GetUseClipping", &Camera::GetUseClipping)
        .addFunction("GetClipPlane", &Camera::GetClipPlane)
        .addFunction("GetFlipVertical", &Camera::GetFlipVertical)
        .addFunction("GetReverseCulling", &Camera::GetReverseCulling)
        .addFunction("GetDistance", &Camera::GetDistance)
        .addFunction("GetDistanceSquared", &Camera::GetDistanceSquared)
        .addFunction("GetLodDistance", &Camera::GetLodDistance)
        .addFunction("GetFaceCameraRotation", &Camera::GetFaceCameraRotation)
        .addFunction("GetEffectiveWorldTransform", &Camera::GetEffectiveWorldTransform)
        .addFunction("IsProjectionValid", &Camera::IsProjectionValid)
        .addFunction("SetAspectRatioInternal", &Camera::SetAspectRatioInternal)

        .addProperty("type", &Camera::GetType)
        .addProperty("typeName", &Camera::GetTypeName)
        .addProperty("typeInfo", &Camera::GetTypeInfo)
        .addProperty("farClip", &Camera::GetFarClip, &Camera::SetFarClip)
        .addProperty("nearClip", &Camera::GetNearClip, &Camera::SetNearClip)
        .addProperty("fov", &Camera::GetFov, &Camera::SetFov)
        .addProperty("orthoSize", &Camera::GetOrthoSize)
        .addProperty("aspectRatio", &Camera::GetAspectRatio, &Camera::SetAspectRatio)
        .addProperty("zoom", &Camera::GetZoom, &Camera::SetZoom)
        .addProperty("lodBias", &Camera::GetLodBias, &Camera::SetLodBias)
        .addProperty("viewMask", &Camera::GetViewMask, &Camera::SetViewMask)
        .addProperty("viewOverrideFlags", &Camera::GetViewOverrideFlags, &Camera::SetViewOverrideFlags)
        .addProperty("fillMode", &Camera::GetFillMode, &Camera::SetFillMode)
        .addProperty("orthographic", &Camera::IsOrthographic, &Camera::SetOrthographic)
        .addProperty("autoAspectRatio", &Camera::GetAutoAspectRatio, &Camera::SetAutoAspectRatio)
        .addProperty("frustum", &Camera::GetFrustum)
        .addProperty("view", &Camera::GetView)
        .addProperty("halfViewSize", &Camera::GetHalfViewSize)
        .addProperty("viewSpaceFrustum", &Camera::GetViewSpaceFrustum)
        .addProperty("projectionOffset", &Camera::GetProjectionOffset, &Camera::SetProjectionOffset)
        .addProperty("useReflection", &Camera::GetUseReflection, &Camera::SetUseReflection)
        .addProperty("reflectionPlane", &Camera::GetReflectionPlane, &Camera::SetReflectionPlane)
        .addProperty("useClipping", &Camera::GetUseClipping, &Camera::SetUseClipping)
        .addProperty("clipPlane", &Camera::GetClipPlane, &Camera::SetClipPlane)
        .addProperty("flipVertical", &Camera::GetFlipVertical, &Camera::SetFlipVertical)
        .addProperty("reverseCulling", &Camera::GetReverseCulling)
        .addProperty("effectiveWorldTransform", &Camera::GetEffectiveWorldTransform)
        .addProperty("projectionValid", &Camera::IsProjectionValid)
        .addProperty("aspectRatioInternal", &Camera::SetAspectRatioInternal)
        );
}

static void RegisterCustomGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KCustomGeometry"].setClass(UserdataMetatable<CustomGeometry, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<CustomGeometry>)
        .addStaticFunction("__gc", &KReleaseObject<CustomGeometry>)

        .addFunction("GetType", &CustomGeometry::GetType)
        .addFunction("GetTypeName", &CustomGeometry::GetTypeName)
        .addFunction("GetTypeInfo", &CustomGeometry::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &CustomGeometry::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &CustomGeometry::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &CustomGeometry::GetTypeInfoStatic)

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
            static_cast<bool(CustomGeometry::*)(unsigned int, Material*)>(&CustomGeometry::SetMaterial))

        .addFunction("GetNumGeometries", &CustomGeometry::GetNumGeometries)
        .addFunction("GetNumVertices", &CustomGeometry::GetNumVertices)
        .addFunction("IsDynamic", &CustomGeometry::IsDynamic)
        .addFunction("GetMaterial", &CustomGeometry::GetMaterial)
        .addFunction("GetVertices", &CustomGeometry::GetVertices)
        .addFunction("GetVertex", &CustomGeometry::GetVertex)

        .addProperty("type", &CustomGeometry::GetType)
        .addProperty("typeName", &CustomGeometry::GetTypeName)
        .addProperty("typeInfo", &CustomGeometry::GetTypeInfo)
        .addProperty("numOccluderTriangles", &CustomGeometry::GetNumOccluderTriangles)
        .addProperty("numGeometries", &CustomGeometry::GetNumGeometries, &CustomGeometry::SetNumGeometries)
        .addProperty("dynamic", &CustomGeometry::IsDynamic, &CustomGeometry::SetDynamic)
        .addProperty("vertices", &CustomGeometry::GetVertices)
        );
}

static void RegisterDebugRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDebugRenderer"].setClass(UserdataMetatable<DebugRenderer, Component>(false)
        .addStaticFunction("new", &KCreateObject<DebugRenderer>)
        .addStaticFunction("__gc", &KReleaseObject<DebugRenderer>)

        .addFunction("GetType", &DebugRenderer::GetType)
        .addFunction("GetTypeName", &DebugRenderer::GetTypeName)
        .addFunction("GetTypeInfo", &DebugRenderer::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &DebugRenderer::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &DebugRenderer::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &DebugRenderer::GetTypeInfoStatic)

        .addFunction("SetView", &DebugRenderer::SetView)

        .addOverloadedFunctions("AddLine",
            static_cast<void(DebugRenderer::*)(const Vector3&, const Vector3&, const Color&, bool)>(&DebugRenderer::AddLine),
            static_cast<void(DebugRenderer::*)(const Vector3&, const Vector3&, unsigned int, bool)>(&DebugRenderer::AddLine))


        .addOverloadedFunctions("AddTriangle",
            static_cast<void(DebugRenderer::*)(const Vector3&, const Vector3&, const Vector3&, const Color&, bool)>(&DebugRenderer::AddTriangle),
            static_cast<void(DebugRenderer::*)(const Vector3&, const Vector3&, const Vector3&, unsigned int, bool)>(&DebugRenderer::AddTriangle))

        .addFunction("AddNode", &DebugRenderer::AddNode)

        .addOverloadedFunctions("AddBoundingBox",
            static_cast<void(DebugRenderer::*)(const BoundingBox&, const Color&, bool)>(&DebugRenderer::AddBoundingBox),
            static_cast<void(DebugRenderer::*)(const BoundingBox&, const Matrix3x4&, const Color&, bool)>(&DebugRenderer::AddBoundingBox))

        .addFunction("AddFrustum", &DebugRenderer::AddFrustum)
        .addFunction("AddPolyhedron", &DebugRenderer::AddPolyhedron)
        .addFunction("AddSphere", &DebugRenderer::AddSphere)
        .addFunction("AddCylinder", &DebugRenderer::AddCylinder)
        .addFunction("AddSkeleton", &DebugRenderer::AddSkeleton)
        .addFunction("AddTriangleMesh", &DebugRenderer::AddTriangleMesh)
        .addFunction("AddCircle", &DebugRenderer::AddCircle)
        .addFunction("AddCross", &DebugRenderer::AddCross)
        .addFunction("AddQuad", &DebugRenderer::AddQuad)
        .addFunction("Render", &DebugRenderer::Render)
        .addFunction("GetView", &DebugRenderer::GetView)
        .addFunction("GetProjection", &DebugRenderer::GetProjection)
        .addFunction("GetFrustum", &DebugRenderer::GetFrustum)
        .addFunction("IsInside", &DebugRenderer::IsInside)
        .addFunction("HasContent", &DebugRenderer::HasContent)

        .addProperty("type", &DebugRenderer::GetType)
        .addProperty("typeName", &DebugRenderer::GetTypeName)
        .addProperty("typeInfo", &DebugRenderer::GetTypeInfo)
        .addProperty("view", &DebugRenderer::GetView, &DebugRenderer::SetView)
        .addProperty("projection", &DebugRenderer::GetProjection)
        .addProperty("frustum", &DebugRenderer::GetFrustum)
        );
}

static void RegisterDecalSet(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDecalSet"].setClass(UserdataMetatable<DecalSet, Drawable>(false)
        .addStaticFunction("new", &KCreateObject<DecalSet>)
        .addStaticFunction("__gc", &KReleaseObject<DecalSet>)

        .addFunction("GetType", &DecalSet::GetType)
        .addFunction("GetTypeName", &DecalSet::GetTypeName)
        .addFunction("GetTypeInfo", &DecalSet::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &DecalSet::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &DecalSet::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &DecalSet::GetTypeInfoStatic)

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

        .addProperty("type", &DecalSet::GetType)
        .addProperty("typeName", &DecalSet::GetTypeName)
        .addProperty("typeInfo", &DecalSet::GetTypeInfo)
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

        .addFunction("GetType", &Drawable::GetType)
        .addFunction("GetTypeName", &Drawable::GetTypeName)
        .addFunction("GetTypeInfo", &Drawable::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &Drawable::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &Drawable::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &Drawable::GetTypeInfoStatic)

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

        .addFunction("MarkForUpdate", &Drawable::MarkForUpdate)
        .addFunction("GetBoundingBox", &Drawable::GetBoundingBox)
        .addFunction("GetWorldBoundingBox", &Drawable::GetWorldBoundingBox)
        .addFunction("GetDrawableFlags", &Drawable::GetDrawableFlags)
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
            static_cast<bool(Drawable::*)(Camera*) const>(&Drawable::IsInView),
            static_cast<bool(Drawable::*)(const FrameInfo&, bool) const>(&Drawable::IsInView))

        .addFunction("GetBatches", &Drawable::GetBatches)
        .addFunction("SetZone", &Drawable::SetZone)
        .addFunction("SetSortValue", &Drawable::SetSortValue)
        .addFunction("SetMinMaxZ", &Drawable::SetMinMaxZ)

        .addOverloadedFunctions("MarkInView",
            static_cast<void(Drawable::*)(const FrameInfo&)>(&Drawable::MarkInView),
            static_cast<void(Drawable::*)(unsigned int)>(&Drawable::MarkInView))

        .addFunction("LimitLights", &Drawable::LimitLights)
        .addFunction("LimitVertexLights", &Drawable::LimitVertexLights)
        .addFunction("SetBasePass", &Drawable::SetBasePass)
        .addFunction("GetOctant", &Drawable::GetOctant)
        .addFunction("GetZone", &Drawable::GetZone)
        .addFunction("IsZoneDirty", &Drawable::IsZoneDirty)
        .addFunction("GetDistance", &Drawable::GetDistance)
        .addFunction("GetLodDistance", &Drawable::GetLodDistance)
        .addFunction("GetSortValue", &Drawable::GetSortValue)
        .addFunction("HasBasePass", &Drawable::HasBasePass)
        .addFunction("GetLights", &Drawable::GetLights)
        .addFunction("GetVertexLights", &Drawable::GetVertexLights)
        .addFunction("GetFirstLight", &Drawable::GetFirstLight)
        .addFunction("GetMinZ", &Drawable::GetMinZ)
        .addFunction("GetMaxZ", &Drawable::GetMaxZ)
        .addFunction("AddLight", &Drawable::AddLight)
        .addFunction("AddVertexLight", &Drawable::AddVertexLight)

        .addProperty("type", &Drawable::GetType)
        .addProperty("typeName", &Drawable::GetTypeName)
        .addProperty("typeInfo", &Drawable::GetTypeInfo)
        .addProperty("updateGeometryType", &Drawable::GetUpdateGeometryType)
        .addProperty("numOccluderTriangles", &Drawable::GetNumOccluderTriangles)
        .addProperty("boundingBox", &Drawable::GetBoundingBox)
        .addProperty("worldBoundingBox", &Drawable::GetWorldBoundingBox)
        .addProperty("drawableFlags", &Drawable::GetDrawableFlags)
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

        .addProperty("batches", &Drawable::GetBatches)
        .addProperty("octant", &Drawable::GetOctant)
        .addProperty("zone", &Drawable::GetZone)
        .addProperty("zoneDirty", &Drawable::IsZoneDirty)
        .addProperty("distance", &Drawable::GetDistance)
        .addProperty("lodDistance", &Drawable::GetLodDistance)
        .addProperty("sortValue", &Drawable::GetSortValue, &Drawable::SetSortValue)
        .addProperty("lights", &Drawable::GetLights)
        .addProperty("vertexLights", &Drawable::GetVertexLights)
        .addProperty("firstLight", &Drawable::GetFirstLight)
        .addProperty("minZ", &Drawable::GetMinZ)
        .addProperty("maxZ", &Drawable::GetMaxZ)
        .addProperty("basePass", &Drawable::SetBasePass)
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

static void RegisterGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KGeometry"].setClass(UserdataMetatable<Geometry, Object>(false)
        .addStaticFunction("new", &KCreateObject<Geometry>)
        .addStaticFunction("__gc", &KReleaseObject<Geometry>)

        .addFunction("GetType", &Geometry::GetType)
        .addFunction("GetTypeName", &Geometry::GetTypeName)
        .addFunction("GetTypeInfo", &Geometry::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &Geometry::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &Geometry::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &Geometry::GetTypeInfoStatic)
        .addFunction("SetNumVertexBuffers", &Geometry::SetNumVertexBuffers)
        .addFunction("SetVertexBuffer", &Geometry::SetVertexBuffer)
        .addFunction("SetIndexBuffer", &Geometry::SetIndexBuffer)

        .addOverloadedFunctions("SetDrawRange",
            static_cast<bool(Geometry::*)(PrimitiveType, unsigned int, unsigned int, bool)>(&Geometry::SetDrawRange),
            static_cast<bool(Geometry::*)(PrimitiveType, unsigned int, unsigned int, unsigned int, unsigned int, bool)>(&Geometry::SetDrawRange))

        .addFunction("SetLodDistance", &Geometry::SetLodDistance)

        .addFunction("GetVertexBuffers", &Geometry::GetVertexBuffers)
        .addFunction("GetNumVertexBuffers", &Geometry::GetNumVertexBuffers)
        .addFunction("GetVertexBuffer", &Geometry::GetVertexBuffer)
        .addFunction("GetIndexBuffer", &Geometry::GetIndexBuffer)
        .addFunction("GetPrimitiveType", &Geometry::GetPrimitiveType)
        .addFunction("GetIndexStart", &Geometry::GetIndexStart)
        .addFunction("GetIndexCount", &Geometry::GetIndexCount)
        .addFunction("GetVertexStart", &Geometry::GetVertexStart)
        .addFunction("GetVertexCount", &Geometry::GetVertexCount)
        .addFunction("GetLodDistance", &Geometry::GetLodDistance)
        .addFunction("GetBufferHash", &Geometry::GetBufferHash)

        .addFunction("GetHitDistance", &Geometry::GetHitDistance)
        .addFunction("IsInside", &Geometry::IsInside)
        .addFunction("IsEmpty", &Geometry::IsEmpty)

        .addProperty("type", &Geometry::GetType)
        .addProperty("typeName", &Geometry::GetTypeName)
        .addProperty("typeInfo", &Geometry::GetTypeInfo)

        .addProperty("indexBuffer", &Geometry::GetIndexBuffer, &Geometry::SetIndexBuffer)
        .addProperty("primitiveType", &Geometry::GetPrimitiveType)
        .addProperty("indexStart", &Geometry::GetIndexStart)
        .addProperty("indexCount", &Geometry::GetIndexCount)
        .addProperty("vertexStart", &Geometry::GetVertexStart)
        .addProperty("vertexCount", &Geometry::GetVertexCount)
        .addProperty("lodDistance", &Geometry::GetLodDistance, &Geometry::SetLodDistance)
        .addProperty("empty", &Geometry::IsEmpty)
        );
}

static void RegisterGraphics(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KNUM_SCREEN_BUFFERS"] = NUM_SCREEN_BUFFERS;

    lua["KGraphics"].setClass(UserdataMetatable<Graphics, Object>(false)
        .addStaticFunction("__gc", &KReleaseObject<Graphics>)

        .addFunction("GetType", &Graphics::GetType)
        .addFunction("GetTypeName", &Graphics::GetTypeName)
        .addFunction("GetTypeInfo", &Graphics::GetTypeInfo)

        .addStaticFunction("GetTypeStatic", &Graphics::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &Graphics::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &Graphics::GetTypeInfoStatic)

        .addFunction("SetExternalWindow", &Graphics::SetExternalWindow)
        .addFunction("SetWindowIcon", &Graphics::SetWindowIcon)
        .addFunction("SetWindowTitle", &Graphics::SetWindowTitle)

        .addOverloadedFunctions("SetWindowPosition",
            static_cast<void(Graphics::*)(const IntVector2&)>(&Graphics::SetWindowPosition),
            static_cast<void(Graphics::*)(int, int)>(&Graphics::SetWindowPosition))

        .addOverloadedFunctions("SetMode",
            static_cast<bool(Graphics::*)(int, int, bool, bool, bool, bool, bool, bool, int)>(&Graphics::SetMode),
            static_cast<bool(Graphics::*)(int, int)>(&Graphics::SetMode))

        .addFunction("SetSRGB", &Graphics::SetSRGB)
        .addFunction("SetOrientations", &Graphics::SetOrientations)
        .addFunction("ToggleFullscreen", &Graphics::ToggleFullscreen)
        .addFunction("Close", &Graphics::Close)
        .addFunction("TakeScreenShot", &Graphics::TakeScreenShot)

        .addFunction("SetViewport", &Graphics::SetViewport)

        .addFunction("IsInitialized", &Graphics::IsInitialized)
        .addFunction("GetExternalWindow", &Graphics::GetExternalWindow)
        .addFunction("GetWindowTitle", &Graphics::GetWindowTitle)
        .addFunction("GetApiName", &Graphics::GetApiName)
        .addFunction("GetWindowPosition", &Graphics::GetWindowPosition)
        .addFunction("GetWidth", &Graphics::GetWidth)
        .addFunction("GetHeight", &Graphics::GetHeight)
        .addFunction("GetMultiSample", &Graphics::GetMultiSample)
        .addFunction("GetFullscreen", &Graphics::GetFullscreen)
        .addFunction("GetBorderless", &Graphics::GetBorderless)
        .addFunction("GetResizable", &Graphics::GetResizable)
        .addFunction("GetHighDPI", &Graphics::GetHighDPI)
        .addFunction("GetVSync", &Graphics::GetVSync)
        .addFunction("GetTripleBuffer", &Graphics::GetTripleBuffer)
        .addFunction("GetSRGB", &Graphics::GetSRGB)
        .addFunction("GetOrientations", &Graphics::GetOrientations)

        .addFunction("GetNumPrimitives", &Graphics::GetNumPrimitives)
        .addFunction("GetNumBatches", &Graphics::GetNumBatches)
        .addFunction("GetDummyColorFormat", &Graphics::GetDummyColorFormat)
        .addFunction("GetShadowMapFormat", &Graphics::GetShadowMapFormat)
        .addFunction("GetHiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        .addFunction("GetInstancingSupport", &Graphics::GetInstancingSupport)
        .addFunction("GetLightPrepassSupport", &Graphics::GetLightPrepassSupport)
        .addFunction("GetDeferredSupport", &Graphics::GetDeferredSupport)
        .addFunction("GetAnisotropySupport", &Graphics::GetAnisotropySupport)
        .addFunction("GetHardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addFunction("GetReadableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addFunction("GetSRGBSupport", &Graphics::GetSRGBSupport)
        .addFunction("GetSRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        .addFunction("GetResolutions", &Graphics::GetResolutions)
        .addFunction("GetMultiSampleLevels", &Graphics::GetMultiSampleLevels)
        .addFunction("GetDesktopResolution", &Graphics::GetDesktopResolution)

        .addFunction("GetDefaultTextureFilterMode", &Graphics::GetDefaultTextureFilterMode)

        .addFunction("GetViewport", &Graphics::GetViewport)
        .addFunction("GetTextureAnisotropy", &Graphics::GetTextureAnisotropy)

        .addFunction("GetStencilCompareMask", &Graphics::GetStencilCompareMask)
        .addFunction("GetStencilWriteMask", &Graphics::GetStencilWriteMask)
        .addFunction("GetUseClipPlane", &Graphics::GetUseClipPlane)
        .addFunction("GetRenderTargetDimensions", &Graphics::GetRenderTargetDimensions)

        .addFunction("Restore", &Graphics::Restore)
        .addFunction("Maximize", &Graphics::Maximize)
        .addFunction("Minimize", &Graphics::Minimize)

        .addStaticFunction("GetAlphaFormat", &Graphics::GetAlphaFormat)
        .addStaticFunction("GetLuminanceFormat", &Graphics::GetLuminanceFormat)
        .addStaticFunction("GetLuminanceAlphaFormat", &Graphics::GetLuminanceAlphaFormat)
        .addStaticFunction("GetRGBFormat", &Graphics::GetRGBFormat)
        .addStaticFunction("GetRGBAFormat", &Graphics::GetRGBAFormat)
        .addStaticFunction("GetRGBA16Format", &Graphics::GetRGBA16Format)
        .addStaticFunction("GetRGBAFloat16Format", &Graphics::GetRGBAFloat16Format)
        .addStaticFunction("GetRGBAFloat32Format", &Graphics::GetRGBAFloat32Format)
        .addStaticFunction("GetRG16Format", &Graphics::GetRG16Format)
        .addStaticFunction("GetRGFloat16Format", &Graphics::GetRGFloat16Format)
        .addStaticFunction("GetRGFloat32Format", &Graphics::GetRGFloat32Format)
        .addStaticFunction("GetFloat16Format", &Graphics::GetFloat16Format)
        .addStaticFunction("GetFloat32Format", &Graphics::GetFloat32Format)
        .addStaticFunction("GetLinearDepthFormat", &Graphics::GetLinearDepthFormat)
        .addStaticFunction("GetDepthStencilFormat", &Graphics::GetDepthStencilFormat)
        .addStaticFunction("GetReadableDepthFormat", &Graphics::GetReadableDepthFormat)
        .addStaticFunction("GetPixelUVOffset", &Graphics::GetPixelUVOffset)
        .addStaticFunction("GetMaxBones", &Graphics::GetMaxBones)
        .addStaticFunction("GetGL3Support", &Graphics::GetGL3Support)

        .addProperty("type", &Graphics::GetType)
        .addProperty("typeName", &Graphics::GetTypeName)
        .addProperty("typeInfo", &Graphics::GetTypeInfo)
        .addProperty("initialized", &Graphics::IsInitialized)
        .addProperty("externalWindow", &Graphics::GetExternalWindow, &Graphics::SetExternalWindow)
        .addProperty("windowTitle", &Graphics::GetWindowTitle, &Graphics::SetWindowTitle)
        .addProperty("apiName", &Graphics::GetApiName)
        .addProperty("windowPosition", &Graphics::GetWindowPosition)
        .addProperty("width", &Graphics::GetWidth)
        .addProperty("height", &Graphics::GetHeight)
        .addProperty("multiSample", &Graphics::GetMultiSample)

        .addProperty("fullscreen", &Graphics::GetFullscreen)
        .addProperty("borderless", &Graphics::GetBorderless)
        .addProperty("resizable", &Graphics::GetResizable)

        .addProperty("highDPI", &Graphics::GetHighDPI)
        .addProperty("vSync", &Graphics::GetVSync)
        .addProperty("tripleBuffer", &Graphics::GetTripleBuffer)
        .addProperty("sRGB", &Graphics::GetSRGB, &Graphics::SetSRGB)
        .addProperty("orientations", &Graphics::GetOrientations, &Graphics::SetOrientations)

        .addProperty("numPrimitives", &Graphics::GetNumPrimitives)
        .addProperty("numBatches", &Graphics::GetNumBatches)
        .addProperty("dummyColorFormat", &Graphics::GetDummyColorFormat)
        .addProperty("shadowMapFormat", &Graphics::GetShadowMapFormat)
        .addProperty("hiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        .addProperty("instancingSupport", &Graphics::GetInstancingSupport)
        .addProperty("lightPrepassSupport", &Graphics::GetLightPrepassSupport)
        .addProperty("deferredSupport", &Graphics::GetDeferredSupport)
        .addProperty("anisotropySupport", &Graphics::GetAnisotropySupport)
        .addProperty("hardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addProperty("readableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addProperty("sRGBSupport", &Graphics::GetSRGBSupport)
        .addProperty("sRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        .addProperty("resolutions", &Graphics::GetResolutions)
        .addProperty("multiSampleLevels", &Graphics::GetMultiSampleLevels)
        .addProperty("desktopResolution", &Graphics::GetDesktopResolution)

        .addProperty("defaultTextureFilterMode", &Graphics::GetDefaultTextureFilterMode, &Graphics::SetDefaultTextureFilterMode)

        .addProperty("viewport", &Graphics::GetViewport, &Graphics::SetViewport)
        .addProperty("textureAnisotropy", &Graphics::GetTextureAnisotropy, &Graphics::SetTextureAnisotropy)

        .addProperty("useClipPlane", &Graphics::GetUseClipPlane)
        .addProperty("renderTargetDimensions", &Graphics::GetRenderTargetDimensions)
        .addProperty("windowIcon", &Graphics::SetWindowIcon)
        );
}

// static void RegisterGraphicsDefs(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum PrimitiveType;
//     lua["KTRIANGLE_LIST"] = TRIANGLE_LIST;
//     lua["KLINE_LIST"] = LINE_LIST;
//     lua["KPOINT_LIST"] = POINT_LIST;
//     lua["KTRIANGLE_STRIP"] = TRIANGLE_STRIP;
//     lua["KLINE_STRIP"] = LINE_STRIP;
//     lua["KTRIANGLE_FAN"] = TRIANGLE_FAN;

//     // enum GeometryType;
//     lua["KGEOM_STATIC"] = GEOM_STATIC;
//     lua["KGEOM_SKINNED"] = GEOM_SKINNED;
//     lua["KGEOM_INSTANCED"] = GEOM_INSTANCED;
//     lua["KGEOM_BILLBOARD"] = GEOM_BILLBOARD;
//     lua["KGEOM_DIRBILLBOARD"] = GEOM_DIRBILLBOARD;
//     lua["KGEOM_TRAIL_FACE_CAMERA"] = GEOM_TRAIL_FACE_CAMERA;
//     lua["KGEOM_TRAIL_BONE"] = GEOM_TRAIL_BONE;
//     lua["KGEOM_STATIC_NOINSTANCING"] = GEOM_STATIC_NOINSTANCING;
//     lua["KMAX_GEOMETRYTYPES"] = MAX_GEOMETRYTYPES;

//     // enum BlendMode;
//     lua["KBLEND_REPLACE"] = BLEND_REPLACE;
//     lua["KBLEND_ADD"] = BLEND_ADD;
//     lua["KBLEND_MULTIPLY"] = BLEND_MULTIPLY;
//     lua["KBLEND_ALPHA"] = BLEND_ALPHA;
//     lua["KBLEND_ADDALPHA"] = BLEND_ADDALPHA;
//     lua["KBLEND_PREMULALPHA"] = BLEND_PREMULALPHA;
//     lua["KBLEND_INVDESTALPHA"] = BLEND_INVDESTALPHA;
//     lua["KBLEND_SUBTRACT"] = BLEND_SUBTRACT;
//     lua["KBLEND_SUBTRACTALPHA"] = BLEND_SUBTRACTALPHA;
//     lua["KMAX_BLENDMODES"] = MAX_BLENDMODES;

//     // enum CompareMode;
//     lua["KCMP_ALWAYS"] = CMP_ALWAYS;
//     lua["KCMP_EQUAL"] = CMP_EQUAL;
//     lua["KCMP_NOTEQUAL"] = CMP_NOTEQUAL;
//     lua["KCMP_LESS"] = CMP_LESS;
//     lua["KCMP_LESSEQUAL"] = CMP_LESSEQUAL;
//     lua["KCMP_GREATER"] = CMP_GREATER;
//     lua["KCMP_GREATEREQUAL"] = CMP_GREATEREQUAL;
//     lua["KMAX_COMPAREMODES"] = MAX_COMPAREMODES;

//     // enum CullMode;
//     lua["KCULL_NONE"] = CULL_NONE;
//     lua["KCULL_CCW"] = CULL_CCW;
//     lua["KCULL_CW"] = CULL_CW;
//     lua["KMAX_CULLMODES"] = MAX_CULLMODES;

//     // enum FillMode;
//     lua["KFILL_SOLID"] = FILL_SOLID;
//     lua["KFILL_WIREFRAME"] = FILL_WIREFRAME;
//     lua["KFILL_POINT"] = FILL_POINT;

//     // enum StencilOp;
//     lua["KOP_KEEP"] = OP_KEEP;
//     lua["KOP_ZERO"] = OP_ZERO;
//     lua["KOP_REF"] = OP_REF;
//     lua["KOP_INCR"] = OP_INCR;
//     lua["KOP_DECR"] = OP_DECR;

//     // enum LockState;
//     lua["KLOCK_NONE"] = LOCK_NONE;
//     lua["KLOCK_HARDWARE"] = LOCK_HARDWARE;
//     lua["KLOCK_SHADOW"] = LOCK_SHADOW;
//     lua["KLOCK_SCRATCH"] = LOCK_SCRATCH;

//     // enum LegacyVertexElement;
//     lua["KELEMENT_POSITION"] = ELEMENT_POSITION;
//     lua["KELEMENT_NORMAL"] = ELEMENT_NORMAL;
//     lua["KELEMENT_COLOR"] = ELEMENT_COLOR;
//     lua["KELEMENT_TEXCOORD1"] = ELEMENT_TEXCOORD1;
//     lua["KELEMENT_TEXCOORD2"] = ELEMENT_TEXCOORD2;
//     lua["KELEMENT_CUBETEXCOORD1"] = ELEMENT_CUBETEXCOORD1;
//     lua["KELEMENT_CUBETEXCOORD2"] = ELEMENT_CUBETEXCOORD2;
//     lua["KELEMENT_TANGENT"] = ELEMENT_TANGENT;
//     lua["KELEMENT_BLENDWEIGHTS"] = ELEMENT_BLENDWEIGHTS;
//     lua["KELEMENT_BLENDINDICES"] = ELEMENT_BLENDINDICES;
//     lua["KELEMENT_INSTANCEMATRIX1"] = ELEMENT_INSTANCEMATRIX1;
//     lua["KELEMENT_INSTANCEMATRIX2"] = ELEMENT_INSTANCEMATRIX2;
//     lua["KELEMENT_INSTANCEMATRIX3"] = ELEMENT_INSTANCEMATRIX3;
//     lua["KELEMENT_OBJECTINDEX"] = ELEMENT_OBJECTINDEX;
//     lua["KMAX_LEGACY_VERTEX_ELEMENTS"] = MAX_LEGACY_VERTEX_ELEMENTS;

//     // enum VertexElementType;
//     lua["KTYPE_INT"] = TYPE_INT;
//     lua["KTYPE_FLOAT"] = TYPE_FLOAT;
//     lua["KTYPE_VECTOR2"] = TYPE_VECTOR2;
//     lua["KTYPE_VECTOR3"] = TYPE_VECTOR3;
//     lua["KTYPE_VECTOR4"] = TYPE_VECTOR4;
//     lua["KTYPE_UBYTE4"] = TYPE_UBYTE4;
//     lua["KTYPE_UBYTE4_NORM"] = TYPE_UBYTE4_NORM;
//     lua["KMAX_VERTEX_ELEMENT_TYPES"] = MAX_VERTEX_ELEMENT_TYPES;

//     // enum VertexElementSemantic;
//     lua["KSEM_POSITION"] = SEM_POSITION;
//     lua["KSEM_NORMAL"] = SEM_NORMAL;
//     lua["KSEM_BINORMAL"] = SEM_BINORMAL;
//     lua["KSEM_TANGENT"] = SEM_TANGENT;
//     lua["KSEM_TEXCOORD"] = SEM_TEXCOORD;
//     lua["KSEM_COLOR"] = SEM_COLOR;
//     lua["KSEM_BLENDWEIGHTS"] = SEM_BLENDWEIGHTS;
//     lua["KSEM_BLENDINDICES"] = SEM_BLENDINDICES;
//     lua["KSEM_OBJECTINDEX"] = SEM_OBJECTINDEX;
//     lua["KMAX_VERTEX_ELEMENT_SEMANTICS"] = MAX_VERTEX_ELEMENT_SEMANTICS;

//     lua["KVertexElement"].setClass(UserdataMetatable<VertexElement>()
//         .setConstructors<VertexElement(),
//             VertexElement(VertexElementType, VertexElementSemantic, unsigned char, bool)>()

//         .addFunction("__eq", &VertexElement::operator==)
//         .addProperty("type", &VertexElement::type_)
//         .addProperty("semantic", &VertexElement::semantic_)
//         .addProperty("index", &VertexElement::index_)
//         .addProperty("perInstance", &VertexElement::perInstance_)
//         .addProperty("offset", &VertexElement::offset_)
//     );
//     lua["KELEMENT_TYPESIZES"] = ELEMENT_TYPESIZES;
//     lua["KLEGACY_VERTEXELEMENTS"] = LEGACY_VERTEXELEMENTS;
//     // enum TextureFilterMode;
//     lua["KFILTER_NEAREST"] = FILTER_NEAREST;
//     lua["KFILTER_BILINEAR"] = FILTER_BILINEAR;
//     lua["KFILTER_TRILINEAR"] = FILTER_TRILINEAR;
//     lua["KFILTER_ANISOTROPIC"] = FILTER_ANISOTROPIC;
//     lua["KFILTER_DEFAULT"] = FILTER_DEFAULT;
//     lua["KMAX_FILTERMODES"] = MAX_FILTERMODES;

//     // enum TextureAddressMode;
//     lua["KADDRESS_WRAP"] = ADDRESS_WRAP;
//     lua["KADDRESS_MIRROR"] = ADDRESS_MIRROR;
//     lua["KADDRESS_CLAMP"] = ADDRESS_CLAMP;
//     lua["KADDRESS_BORDER"] = ADDRESS_BORDER;
//     lua["KMAX_ADDRESSMODES"] = MAX_ADDRESSMODES;

//     // enum TextureCoordinate;
//     lua["KCOORD_U"] = COORD_U;
//     lua["KCOORD_V"] = COORD_V;
//     lua["KCOORD_W"] = COORD_W;
//     lua["KMAX_COORDS"] = MAX_COORDS;

//     // enum TextureUsage;
//     lua["KTEXTURE_STATIC"] = TEXTURE_STATIC;
//     lua["KTEXTURE_DYNAMIC"] = TEXTURE_DYNAMIC;
//     lua["KTEXTURE_RENDERTARGET"] = TEXTURE_RENDERTARGET;
//     lua["KTEXTURE_DEPTHSTENCIL"] = TEXTURE_DEPTHSTENCIL;

//     // enum CubeMapFace;
//     lua["KFACE_POSITIVE_X"] = FACE_POSITIVE_X;
//     lua["KFACE_NEGATIVE_X"] = FACE_NEGATIVE_X;
//     lua["KFACE_POSITIVE_Y"] = FACE_POSITIVE_Y;
//     lua["KFACE_NEGATIVE_Y"] = FACE_NEGATIVE_Y;
//     lua["KFACE_POSITIVE_Z"] = FACE_POSITIVE_Z;
//     lua["KFACE_NEGATIVE_Z"] = FACE_NEGATIVE_Z;
//     lua["KMAX_CUBEMAP_FACES"] = MAX_CUBEMAP_FACES;

//     // enum CubeMapLayout;
//     lua["KCML_HORIZONTAL"] = CML_HORIZONTAL;
//     lua["KCML_HORIZONTALNVIDIA"] = CML_HORIZONTALNVIDIA;
//     lua["KCML_HORIZONTALCROSS"] = CML_HORIZONTALCROSS;
//     lua["KCML_VERTICALCROSS"] = CML_VERTICALCROSS;
//     lua["KCML_BLENDER"] = CML_BLENDER;

//     // enum RenderSurfaceUpdateMode;
//     lua["KSURFACE_MANUALUPDATE"] = SURFACE_MANUALUPDATE;
//     lua["KSURFACE_UPDATEVISIBLE"] = SURFACE_UPDATEVISIBLE;
//     lua["KSURFACE_UPDATEALWAYS"] = SURFACE_UPDATEALWAYS;

//     // enum ShaderType;
//     lua["KVS"] = VS;
//     lua["KPS"] = PS;

//     // enum ShaderParameterGroup;
//     lua["KSP_FRAME"] = SP_FRAME;
//     lua["KSP_CAMERA"] = SP_CAMERA;
//     lua["KSP_ZONE"] = SP_ZONE;
//     lua["KSP_LIGHT"] = SP_LIGHT;
//     lua["KSP_MATERIAL"] = SP_MATERIAL;
//     lua["KSP_OBJECT"] = SP_OBJECT;
//     lua["KSP_CUSTOM"] = SP_CUSTOM;
//     lua["KMAX_SHADER_PARAMETER_GROUPS"] = MAX_SHADER_PARAMETER_GROUPS;

//     // enum TextureUnit;
//     lua["KTU_DIFFUSE"] = TU_DIFFUSE;
//     lua["KTU_ALBEDOBUFFER"] = TU_ALBEDOBUFFER;
//     lua["KTU_NORMAL"] = TU_NORMAL;
//     lua["KTU_NORMALBUFFER"] = TU_NORMALBUFFER;
//     lua["KTU_SPECULAR"] = TU_SPECULAR;
//     lua["KTU_EMISSIVE"] = TU_EMISSIVE;
//     lua["KTU_ENVIRONMENT"] = TU_ENVIRONMENT;
//     lua["KTU_VOLUMEMAP"] = TU_VOLUMEMAP;
//     lua["KTU_CUSTOM1"] = TU_CUSTOM1;
//     lua["KTU_CUSTOM2"] = TU_CUSTOM2;
//     lua["KTU_LIGHTRAMP"] = TU_LIGHTRAMP;
//     lua["KTU_LIGHTSHAPE"] = TU_LIGHTSHAPE;
//     lua["KTU_SHADOWMAP"] = TU_SHADOWMAP;
//     lua["KTU_FACESELECT"] = TU_FACESELECT;
//     lua["KTU_INDIRECTION"] = TU_INDIRECTION;
//     lua["KTU_DEPTHBUFFER"] = TU_DEPTHBUFFER;
//     lua["KTU_LIGHTBUFFER"] = TU_LIGHTBUFFER;
//     lua["KTU_ZONE"] = TU_ZONE;
//     lua["KMAX_MATERIAL_TEXTURE_UNITS"] = MAX_MATERIAL_TEXTURE_UNITS;
//     lua["KMAX_TEXTURE_UNITS"] = MAX_TEXTURE_UNITS;

//     // enum FaceCameraMode;
//     lua["KFC_NONE"] = FC_NONE;
//     lua["KFC_ROTATE_XYZ"] = FC_ROTATE_XYZ;
//     lua["KFC_ROTATE_Y"] = FC_ROTATE_Y;
//     lua["KFC_LOOKAT_XYZ"] = FC_LOOKAT_XYZ;
//     lua["KFC_LOOKAT_Y"] = FC_LOOKAT_Y;
//     lua["KFC_DIRECTION"] = FC_DIRECTION;

//     // enum ShadowQuality;
//     lua["KSHADOWQUALITY_SIMPLE_16BIT"] = SHADOWQUALITY_SIMPLE_16BIT;
//     lua["KSHADOWQUALITY_SIMPLE_24BIT"] = SHADOWQUALITY_SIMPLE_24BIT;
//     lua["KSHADOWQUALITY_PCF_16BIT"] = SHADOWQUALITY_PCF_16BIT;
//     lua["KSHADOWQUALITY_PCF_24BIT"] = SHADOWQUALITY_PCF_24BIT;
//     lua["KSHADOWQUALITY_VSM"] = SHADOWQUALITY_VSM;
//     lua["KSHADOWQUALITY_BLUR_VSM"] = SHADOWQUALITY_BLUR_VSM;

//     lua["KVSP_AMBIENTSTARTCOLOR"] = VSP_AMBIENTSTARTCOLOR;
//     lua["KVSP_AMBIENTENDCOLOR"] = VSP_AMBIENTENDCOLOR;
//     lua["KVSP_BILLBOARDROT"] = VSP_BILLBOARDROT;
//     lua["KVSP_CAMERAPOS"] = VSP_CAMERAPOS;
//     lua["KVSP_CLIPPLANE"] = VSP_CLIPPLANE;
//     lua["KVSP_NEARCLIP"] = VSP_NEARCLIP;
//     lua["KVSP_FARCLIP"] = VSP_FARCLIP;
//     lua["KVSP_DEPTHMODE"] = VSP_DEPTHMODE;
//     lua["KVSP_DELTATIME"] = VSP_DELTATIME;
//     lua["KVSP_ELAPSEDTIME"] = VSP_ELAPSEDTIME;
//     lua["KVSP_FRUSTUMSIZE"] = VSP_FRUSTUMSIZE;
//     lua["KVSP_GBUFFEROFFSETS"] = VSP_GBUFFEROFFSETS;
//     lua["KVSP_LIGHTDIR"] = VSP_LIGHTDIR;
//     lua["KVSP_LIGHTPOS"] = VSP_LIGHTPOS;
//     lua["KVSP_NORMALOFFSETSCALE"] = VSP_NORMALOFFSETSCALE;
//     lua["KVSP_MODEL"] = VSP_MODEL;
//     lua["KVSP_VIEW"] = VSP_VIEW;
//     lua["KVSP_VIEWINV"] = VSP_VIEWINV;
//     lua["KVSP_VIEWPROJ"] = VSP_VIEWPROJ;
//     lua["KVSP_UOFFSET"] = VSP_UOFFSET;
//     lua["KVSP_VOFFSET"] = VSP_VOFFSET;
//     lua["KVSP_ZONE"] = VSP_ZONE;
//     lua["KVSP_LIGHTMATRICES"] = VSP_LIGHTMATRICES;
//     lua["KVSP_SKINMATRICES"] = VSP_SKINMATRICES;
//     lua["KVSP_VERTEXLIGHTS"] = VSP_VERTEXLIGHTS;
//     lua["KPSP_AMBIENTCOLOR"] = PSP_AMBIENTCOLOR;
//     lua["KPSP_CAMERAPOS"] = PSP_CAMERAPOS;
//     lua["KPSP_DELTATIME"] = PSP_DELTATIME;
//     lua["KPSP_DEPTHRECONSTRUCT"] = PSP_DEPTHRECONSTRUCT;
//     lua["KPSP_ELAPSEDTIME"] = PSP_ELAPSEDTIME;
//     lua["KPSP_FOGCOLOR"] = PSP_FOGCOLOR;
//     lua["KPSP_FOGPARAMS"] = PSP_FOGPARAMS;
//     lua["KPSP_GBUFFERINVSIZE"] = PSP_GBUFFERINVSIZE;
//     lua["KPSP_LIGHTCOLOR"] = PSP_LIGHTCOLOR;
//     lua["KPSP_LIGHTDIR"] = PSP_LIGHTDIR;
//     lua["KPSP_LIGHTPOS"] = PSP_LIGHTPOS;
//     lua["KPSP_NORMALOFFSETSCALE"] = PSP_NORMALOFFSETSCALE;
//     lua["KPSP_MATDIFFCOLOR"] = PSP_MATDIFFCOLOR;
//     lua["KPSP_MATEMISSIVECOLOR"] = PSP_MATEMISSIVECOLOR;
//     lua["KPSP_MATENVMAPCOLOR"] = PSP_MATENVMAPCOLOR;
//     lua["KPSP_MATSPECCOLOR"] = PSP_MATSPECCOLOR;
//     lua["KPSP_NEARCLIP"] = PSP_NEARCLIP;
//     lua["KPSP_FARCLIP"] = PSP_FARCLIP;
//     lua["KPSP_SHADOWCUBEADJUST"] = PSP_SHADOWCUBEADJUST;
//     lua["KPSP_SHADOWDEPTHFADE"] = PSP_SHADOWDEPTHFADE;
//     lua["KPSP_SHADOWINTENSITY"] = PSP_SHADOWINTENSITY;
//     lua["KPSP_SHADOWMAPINVSIZE"] = PSP_SHADOWMAPINVSIZE;
//     lua["KPSP_SHADOWSPLITS"] = PSP_SHADOWSPLITS;
//     lua["KPSP_LIGHTMATRICES"] = PSP_LIGHTMATRICES;
//     lua["KPSP_VSMSHADOWPARAMS"] = PSP_VSMSHADOWPARAMS;
//     lua["KPSP_ROUGHNESS"] = PSP_ROUGHNESS;
//     lua["KPSP_METALLIC"] = PSP_METALLIC;
//     lua["KDOT_SCALE"] = DOT_SCALE;
//     lua["KQUALITY_LOW"] = QUALITY_LOW;
//     lua["KQUALITY_MEDIUM"] = QUALITY_MEDIUM;
//     lua["KQUALITY_HIGH"] = QUALITY_HIGH;
//     lua["KQUALITY_MAX"] = QUALITY_MAX;
//     lua["KCLEAR_COLOR"] = CLEAR_COLOR;
//     lua["KCLEAR_DEPTH"] = CLEAR_DEPTH;
//     lua["KCLEAR_STENCIL"] = CLEAR_STENCIL;
//     lua["KMASK_NONE"] = MASK_NONE;
//     lua["KMASK_POSITION"] = MASK_POSITION;
//     lua["KMASK_NORMAL"] = MASK_NORMAL;
//     lua["KMASK_COLOR"] = MASK_COLOR;
//     lua["KMASK_TEXCOORD1"] = MASK_TEXCOORD1;
//     lua["KMASK_TEXCOORD2"] = MASK_TEXCOORD2;
//     lua["KMASK_CUBETEXCOORD1"] = MASK_CUBETEXCOORD1;
//     lua["KMASK_CUBETEXCOORD2"] = MASK_CUBETEXCOORD2;
//     lua["KMASK_TANGENT"] = MASK_TANGENT;
//     lua["KMASK_BLENDWEIGHTS"] = MASK_BLENDWEIGHTS;
//     lua["KMASK_BLENDINDICES"] = MASK_BLENDINDICES;
//     lua["KMASK_INSTANCEMATRIX1"] = MASK_INSTANCEMATRIX1;
//     lua["KMASK_INSTANCEMATRIX2"] = MASK_INSTANCEMATRIX2;
//     lua["KMASK_INSTANCEMATRIX3"] = MASK_INSTANCEMATRIX3;
//     lua["KMASK_OBJECTINDEX"] = MASK_OBJECTINDEX;
//     lua["KMAX_RENDERTARGETS"] = MAX_RENDERTARGETS;
//     lua["KMAX_VERTEX_STREAMS"] = MAX_VERTEX_STREAMS;
//     lua["KMAX_CONSTANT_REGISTERS"] = MAX_CONSTANT_REGISTERS;
//     lua["KBITS_PER_COMPONENT"] = BITS_PER_COMPONENT;
// }

static void RegisterGraphicsEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KE_SCREENMODE"] = E_SCREENMODE;
    lua["KE_WINDOWPOS"] = E_WINDOWPOS;
    lua["KE_RENDERSURFACEUPDATE"] = E_RENDERSURFACEUPDATE;
    lua["KE_BEGINRENDERING"] = E_BEGINRENDERING;
    lua["KE_ENDRENDERING"] = E_ENDRENDERING;
    lua["KE_BEGINVIEWUPDATE"] = E_BEGINVIEWUPDATE;
    lua["KE_ENDVIEWUPDATE"] = E_ENDVIEWUPDATE;
    lua["KE_BEGINVIEWRENDER"] = E_BEGINVIEWRENDER;
    lua["KE_ENDVIEWRENDER"] = E_ENDVIEWRENDER;
    lua["KE_RENDERPATHEVENT"] = E_RENDERPATHEVENT;
    lua["KE_DEVICELOST"] = E_DEVICELOST;
    lua["KE_DEVICERESET"] = E_DEVICERESET;
}

static void RegisterIndexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KIndexBuffer"].setClass(UserdataMetatable<IndexBuffer, Object>(false)
        .addStaticFunction("new", &KCreateObject<IndexBuffer>)
        .addStaticFunction("__gc", &KReleaseObject<IndexBuffer>)

        .addFunction("GetType", &IndexBuffer::GetType)
        .addFunction("GetTypeName", &IndexBuffer::GetTypeName)
        .addFunction("GetTypeInfo", &IndexBuffer::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &IndexBuffer::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &IndexBuffer::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &IndexBuffer::GetTypeInfoStatic)

        .addFunction("SetShadowed", &IndexBuffer::SetShadowed)
        .addFunction("SetSize", &IndexBuffer::SetSize)
        .addFunction("SetDataRange", &IndexBuffer::SetDataRange)

        .addFunction("IsShadowed", &IndexBuffer::IsShadowed)
        .addFunction("IsDynamic", &IndexBuffer::IsDynamic)
        .addFunction("IsLocked", &IndexBuffer::IsLocked)

        .addFunction("GetIndexCount", &IndexBuffer::GetIndexCount)
        .addFunction("GetIndexSize", &IndexBuffer::GetIndexSize)
        .addFunction("GetUsedVertexRange", &IndexBuffer::GetUsedVertexRange)

        .addProperty("type", &IndexBuffer::GetType)
        .addProperty("typeName", &IndexBuffer::GetTypeName)
        .addProperty("typeInfo", &IndexBuffer::GetTypeInfo)

        .addProperty("shadowed", &IndexBuffer::IsShadowed, &IndexBuffer::SetShadowed)
        .addProperty("dynamic", &IndexBuffer::IsDynamic)
        .addProperty("locked", &IndexBuffer::IsLocked)
        .addProperty("indexCount", &IndexBuffer::GetIndexCount)
        .addProperty("indexSize", &IndexBuffer::GetIndexSize)
        );
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

        .addFunction("GetType", &Light::GetType)
        .addFunction("GetTypeName", &Light::GetTypeName)
        .addFunction("GetTypeInfo", &Light::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &Light::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &Light::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &Light::GetTypeInfoStatic)

        .addFunction("SetLightType", &Light::SetLightType)
        .addFunction("SetPerVertex", &Light::SetPerVertex)
        .addFunction("SetColor", &Light::SetColor)
        .addFunction("SetSpecularIntensity", &Light::SetSpecularIntensity)
        .addFunction("SetBrightness", &Light::SetBrightness)
        .addFunction("SetRange", &Light::SetRange)
        .addFunction("SetFov", &Light::SetFov)
        .addFunction("SetAspectRatio", &Light::SetAspectRatio)
        .addFunction("SetFadeDistance", &Light::SetFadeDistance)
        .addFunction("SetShadowFadeDistance", &Light::SetShadowFadeDistance)
        .addFunction("SetShadowBias", &Light::SetShadowBias)
        .addFunction("SetShadowCascade", &Light::SetShadowCascade)
        .addFunction("SetShadowFocus", &Light::SetShadowFocus)
        .addFunction("SetShadowIntensity", &Light::SetShadowIntensity)
        .addFunction("SetShadowResolution", &Light::SetShadowResolution)
        .addFunction("SetShadowNearFarRatio", &Light::SetShadowNearFarRatio)
        .addFunction("SetRampTexture", &Light::SetRampTexture)
        .addFunction("SetShapeTexture", &Light::SetShapeTexture)
        .addFunction("GetLightType", &Light::GetLightType)
        .addFunction("GetPerVertex", &Light::GetPerVertex)
        .addFunction("GetColor", &Light::GetColor)
        .addFunction("GetSpecularIntensity", &Light::GetSpecularIntensity)
        .addFunction("GetBrightness", &Light::GetBrightness)
        .addFunction("GetEffectiveColor", &Light::GetEffectiveColor)
        .addFunction("GetEffectiveSpecularIntensity", &Light::GetEffectiveSpecularIntensity)
        .addFunction("GetRange", &Light::GetRange)
        .addFunction("GetFov", &Light::GetFov)
        .addFunction("GetAspectRatio", &Light::GetAspectRatio)
        .addFunction("GetFadeDistance", &Light::GetFadeDistance)
        .addFunction("GetShadowFadeDistance", &Light::GetShadowFadeDistance)
        .addFunction("GetShadowBias", &Light::GetShadowBias)
        .addFunction("GetShadowCascade", &Light::GetShadowCascade)
        .addFunction("GetShadowFocus", &Light::GetShadowFocus)
        .addFunction("GetShadowIntensity", &Light::GetShadowIntensity)
        .addFunction("GetShadowResolution", &Light::GetShadowResolution)
        .addFunction("GetShadowNearFarRatio", &Light::GetShadowNearFarRatio)
        .addFunction("GetRampTexture", &Light::GetRampTexture)
        .addFunction("GetShapeTexture", &Light::GetShapeTexture)
        .addFunction("GetFrustum", &Light::GetFrustum)
        .addFunction("GetViewSpaceFrustum", &Light::GetViewSpaceFrustum)
        .addFunction("GetNumShadowSplits", &Light::GetNumShadowSplits)
        .addFunction("IsNegative", &Light::IsNegative)

        .addOverloadedFunctions("SetIntensitySortValue",
            static_cast<void(Light::*)(float)>(&Light::SetIntensitySortValue),
            static_cast<void(Light::*)(const BoundingBox&)>(&Light::SetIntensitySortValue))

        .addFunction("SetLightQueue", &Light::SetLightQueue)
        .addFunction("GetVolumeTransform", &Light::GetVolumeTransform)
        .addFunction("GetLightQueue", &Light::GetLightQueue)
        .addFunction("GetIntensityDivisor", &Light::GetIntensityDivisor)
        .addStaticFunction("GetFullscreenQuadTransform", &Light::GetFullscreenQuadTransform)

        .addProperty("type", &Light::GetType)
        .addProperty("typeName", &Light::GetTypeName)
        .addProperty("typeInfo", &Light::GetTypeInfo)
        .addProperty("lightType", &Light::GetLightType, &Light::SetLightType)
        .addProperty("perVertex", &Light::GetPerVertex, &Light::SetPerVertex)
        .addProperty("color", &Light::GetColor, &Light::SetColor)
        .addProperty("specularIntensity", &Light::GetSpecularIntensity, &Light::SetSpecularIntensity)
        .addProperty("brightness", &Light::GetBrightness, &Light::SetBrightness)
        .addProperty("effectiveColor", &Light::GetEffectiveColor)
        .addProperty("effectiveSpecularIntensity", &Light::GetEffectiveSpecularIntensity)
        .addProperty("range", &Light::GetRange, &Light::SetRange)
        .addProperty("fov", &Light::GetFov, &Light::SetFov)
        .addProperty("aspectRatio", &Light::GetAspectRatio, &Light::SetAspectRatio)
        .addProperty("fadeDistance", &Light::GetFadeDistance, &Light::SetFadeDistance)
        .addProperty("shadowFadeDistance", &Light::GetShadowFadeDistance, &Light::SetShadowFadeDistance)
        .addProperty("shadowBias", &Light::GetShadowBias, &Light::SetShadowBias)
        .addProperty("shadowCascade", &Light::GetShadowCascade, &Light::SetShadowCascade)
        .addProperty("shadowFocus", &Light::GetShadowFocus, &Light::SetShadowFocus)
        .addProperty("shadowIntensity", &Light::GetShadowIntensity, &Light::SetShadowIntensity)
        .addProperty("shadowResolution", &Light::GetShadowResolution, &Light::SetShadowResolution)
        .addProperty("shadowNearFarRatio", &Light::GetShadowNearFarRatio, &Light::SetShadowNearFarRatio)
        .addProperty("rampTexture", &Light::GetRampTexture, &Light::SetRampTexture)
        .addProperty("shapeTexture", &Light::GetShapeTexture, &Light::SetShapeTexture)
        .addProperty("frustum", &Light::GetFrustum)
        .addProperty("numShadowSplits", &Light::GetNumShadowSplits)
        .addProperty("negative", &Light::IsNegative)
        .addProperty("lightQueue", &Light::GetLightQueue, &Light::SetLightQueue)
        );
    lua["KCompareLights"] = function(&CompareLights);
}

static void RegisterMaterial(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDEFAULT_RENDER_ORDER"] = DEFAULT_RENDER_ORDER;

    lua["KMaterial"].setClass(UserdataMetatable<Material, Resource>(false)
        .addStaticFunction("new", &KCreateObject<Material>)
        .addStaticFunction("__gc", &KReleaseObject<Material>)

        .addFunction("GetType", &Material::GetType)
        .addFunction("GetTypeName", &Material::GetTypeName)
        .addFunction("GetTypeInfo", &Material::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &Material::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &Material::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &Material::GetTypeInfoStatic)

        .addFunction("SetNumTechniques", &Material::SetNumTechniques)
        .addFunction("SetTechnique", &Material::SetTechnique)
        .addFunction("SetShaderParameter", &Material::SetShaderParameter)
        .addFunction("SetShaderParameterAnimation", &Material::SetShaderParameterAnimation)
        .addFunction("SetShaderParameterAnimationWrapMode", &Material::SetShaderParameterAnimationWrapMode)
        .addFunction("SetShaderParameterAnimationSpeed", &Material::SetShaderParameterAnimationSpeed)
        .addFunction("SetTexture", &Material::SetTexture)

        .addOverloadedFunctions("SetUVTransform",
            static_cast<void(Material::*)(const Vector2&, float, const Vector2&)>(&Material::SetUVTransform),
            static_cast<void(Material::*)(const Vector2&, float, float)>(&Material::SetUVTransform))

        .addFunction("SetCullMode", &Material::SetCullMode)
        .addFunction("SetShadowCullMode", &Material::SetShadowCullMode)
        .addFunction("SetFillMode", &Material::SetFillMode)
        .addFunction("SetDepthBias", &Material::SetDepthBias)
        .addFunction("SetRenderOrder", &Material::SetRenderOrder)
        .addFunction("SetScene", &Material::SetScene)
        .addFunction("RemoveShaderParameter", &Material::RemoveShaderParameter)
        .addFunction("ReleaseShaders", &Material::ReleaseShaders)
        .addFunction("Clone", &Material::Clone)
        .addFunction("SortTechniques", &Material::SortTechniques)
        .addFunction("MarkForAuxView", &Material::MarkForAuxView)
        .addFunction("GetNumTechniques", &Material::GetNumTechniques)
        .addFunction("GetTechniques", &Material::GetTechniques)
        .addFunction("GetTechniqueEntry", &Material::GetTechniqueEntry)
        .addFunction("GetTechnique", &Material::GetTechnique)
        .addFunction("GetPass", &Material::GetPass)
        .addFunction("GetTexture", &Material::GetTexture)
        .addFunction("GetTextures", &Material::GetTextures)
        .addFunction("GetShaderParameter", &Material::GetShaderParameter)
        .addFunction("GetShaderParameterAnimation", &Material::GetShaderParameterAnimation)
        .addFunction("GetShaderParameterAnimationWrapMode", &Material::GetShaderParameterAnimationWrapMode)
        .addFunction("GetShaderParameterAnimationSpeed", &Material::GetShaderParameterAnimationSpeed)
        .addFunction("GetShaderParameters", &Material::GetShaderParameters)
        .addFunction("GetCullMode", &Material::GetCullMode)
        .addFunction("GetShadowCullMode", &Material::GetShadowCullMode)
        .addFunction("GetFillMode", &Material::GetFillMode)
        .addFunction("GetDepthBias", &Material::GetDepthBias)
        .addFunction("GetRenderOrder", &Material::GetRenderOrder)
        .addFunction("GetAuxViewFrameNumber", &Material::GetAuxViewFrameNumber)
        .addFunction("GetOcclusion", &Material::GetOcclusion)
        .addFunction("GetSpecular", &Material::GetSpecular)
        .addFunction("GetScene", &Material::GetScene)
        .addFunction("GetShaderParameterHash", &Material::GetShaderParameterHash)
        .addStaticFunction("GetTextureUnitName", &Material::GetTextureUnitName)
        .addStaticFunction("ParseShaderParameterValue", &Material::ParseShaderParameterValue)

        .addProperty("type", &Material::GetType)
        .addProperty("typeName", &Material::GetTypeName)
        .addProperty("typeInfo", &Material::GetTypeInfo)
        .addProperty("numTechniques", &Material::GetNumTechniques, &Material::SetNumTechniques)
        .addProperty("techniques", &Material::GetTechniques)
        .addProperty("textures", &Material::GetTextures)
        .addProperty("shaderParameters", &Material::GetShaderParameters)
        .addProperty("cullMode", &Material::GetCullMode, &Material::SetCullMode)
        .addProperty("shadowCullMode", &Material::GetShadowCullMode, &Material::SetShadowCullMode)
        .addProperty("fillMode", &Material::GetFillMode, &Material::SetFillMode)
        .addProperty("depthBias", &Material::GetDepthBias, &Material::SetDepthBias)
        .addProperty("renderOrder", &Material::GetRenderOrder, &Material::SetRenderOrder)
        .addProperty("auxViewFrameNumber", &Material::GetAuxViewFrameNumber)
        .addProperty("occlusion", &Material::GetOcclusion)
        .addProperty("specular", &Material::GetSpecular)
        .addProperty("scene", &Material::GetScene, &Material::SetScene)
        .addProperty("shaderParameterHash", &Material::GetShaderParameterHash)
        );
}

static void RegisterModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KModel"].setClass(UserdataMetatable<Model, Resource>(false)
        .addStaticFunction("new", &KCreateObject<Model>)
        .addStaticFunction("__gc", &KReleaseObject<Model>)

        .addFunction("GetType", &Model::GetType)
        .addFunction("GetTypeName", &Model::GetTypeName)
        .addFunction("GetTypeInfo", &Model::GetTypeInfo)
        .addStaticFunction("GetTypeStatic", &Model::GetTypeStatic)
        .addStaticFunction("GetTypeNameStatic", &Model::GetTypeNameStatic)
        .addStaticFunction("GetTypeInfoStatic", &Model::GetTypeInfoStatic)

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
            static_cast<const ModelMorph*(Model::*)(unsigned int) const>(&Model::GetMorph),
            static_cast<const ModelMorph*(Model::*)(const String&) const>(&Model::GetMorph),
            static_cast<const ModelMorph*(Model::*)(StringHash) const>(&Model::GetMorph))

        .addFunction("GetMorphRangeStart", &Model::GetMorphRangeStart)
        .addFunction("GetMorphRangeCount", &Model::GetMorphRangeCount)

        .addProperty("type", &Model::GetType)
        .addProperty("typeName", &Model::GetTypeName)
        .addProperty("typeInfo", &Model::GetTypeInfo)

        .addProperty("boundingBox", &Model::GetBoundingBox, &Model::SetBoundingBox)
        .addProperty("numGeometries", &Model::GetNumGeometries, &Model::SetNumGeometries)
        .addProperty("numMorphs", &Model::GetNumMorphs)
        );
}

// static void RegisterOctree(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KNUM_OCTANTS"] = NUM_OCTANTS;
//     lua["KROOT_INDEX"] = ROOT_INDEX;
//     lua["KOctant"].setClass(UserdataMetatable<Octant>()
//         .setConstructors<Octant(const BoundingBox&, unsigned int, Octant*, Octree*, unsigned int)>()

//         .addFunction("GetOrCreateChild", &Octant::GetOrCreateChild)
//         .addFunction("DeleteChild", &Octant::DeleteChild)
//         .addFunction("InsertDrawable", &Octant::InsertDrawable)
//         .addFunction("CheckDrawableFit", &Octant::CheckDrawableFit)
//         .addFunction("AddDrawable", &Octant::AddDrawable)
//         .addFunction("RemoveDrawable", &Octant::RemoveDrawable)
//         .addFunction("GetWorldBoundingBox", &Octant::GetWorldBoundingBox)
//         .addFunction("GetCullingBox", &Octant::GetCullingBox)
//         .addFunction("GetLevel", &Octant::GetLevel)
//         .addFunction("GetParent", &Octant::GetParent)
//         .addFunction("GetRoot", &Octant::GetRoot)
//         .addFunction("GetNumDrawables", &Octant::GetNumDrawables)
//         .addFunction("IsEmpty", &Octant::IsEmpty)
//         .addFunction("ResetRoot", &Octant::ResetRoot)
//         .addFunction("DrawDebugGeometry", &Octant::DrawDebugGeometry)

//         .addProperty("worldBoundingBox", &Octant::GetWorldBoundingBox)
//         .addProperty("cullingBox", &Octant::GetCullingBox)
//         .addProperty("level", &Octant::GetLevel)
//         .addProperty("parent", &Octant::GetParent)
//         .addProperty("root", &Octant::GetRoot)
//         .addProperty("numDrawables", &Octant::GetNumDrawables)
//         .addProperty("empty", &Octant::IsEmpty)
//     );
//     lua["KOctree"].setClass(UserdataMetatable<Octree, Component, Octant>(false)
//         .addStaticFunction("new", &KCreateObject<Octree>)
//         .addStaticFunction("__gc", &KReleaseObject<Octree>)

//         .addFunction("GetType", &Octree::GetType)
//         .addFunction("GetTypeName", &Octree::GetTypeName)
//         .addFunction("GetTypeInfo", &Octree::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Octree::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Octree::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Octree::GetTypeInfoStatic)
//         .addFunction("OnSetAttribute", &Octree::OnSetAttribute)

//         .addOverloadedFunctions("DrawDebugGeometry",
//             static_cast<void(Octree::*)(DebugRenderer*, bool)>(&Octree::DrawDebugGeometry),
//             static_cast<void(Octree::*)(bool)>(&Octree::DrawDebugGeometry))

//         .addFunction("SetSize", &Octree::SetSize)
//         .addFunction("Update", &Octree::Update)
//         .addFunction("AddManualDrawable", &Octree::AddManualDrawable)
//         .addFunction("RemoveManualDrawable", &Octree::RemoveManualDrawable)
//         .addFunction("GetDrawables", &Octree::GetDrawables)
//         .addFunction("Raycast", &Octree::Raycast)
//         .addFunction("RaycastSingle", &Octree::RaycastSingle)
//         .addFunction("GetNumLevels", &Octree::GetNumLevels)
//         .addFunction("QueueUpdate", &Octree::QueueUpdate)
//         .addFunction("CancelUpdate", &Octree::CancelUpdate)

//         .addProperty("type", &Octree::GetType)
//         .addProperty("typeName", &Octree::GetTypeName)
//         .addProperty("typeInfo", &Octree::GetTypeInfo)
//         .addProperty("numLevels", &Octree::GetNumLevels)
//     );
// }

// static void RegisterOctreeQuery(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KOctreeQuery"].setClass(UserdataMetatable<OctreeQuery>()
//         .setConstructors<OctreeQuery(PODVector<Drawable*>&, unsigned char, unsigned int),
//             OctreeQuery(const OctreeQuery&)>()

//         .addFunction("TestOctant", &OctreeQuery::TestOctant)
//         .addFunction("TestDrawables", &OctreeQuery::TestDrawables)
//         .addProperty("result", &OctreeQuery::result_)
//         .addProperty("drawableFlags", &OctreeQuery::drawableFlags_)
//         .addProperty("viewMask", &OctreeQuery::viewMask_)
//     );
//     lua["KPointOctreeQuery"].setClass(UserdataMetatable<PointOctreeQuery, OctreeQuery>()
//         .setConstructors<PointOctreeQuery(PODVector<Drawable*>&, const Vector3&, unsigned char, unsigned int)>()

//         .addFunction("TestOctant", &PointOctreeQuery::TestOctant)
//         .addFunction("TestDrawables", &PointOctreeQuery::TestDrawables)
//         .addProperty("point", &PointOctreeQuery::point_)
//     );
//     lua["KSphereOctreeQuery"].setClass(UserdataMetatable<SphereOctreeQuery, OctreeQuery>()
//         .setConstructors<SphereOctreeQuery(PODVector<Drawable*>&, const Sphere&, unsigned char, unsigned int)>()

//         .addFunction("TestOctant", &SphereOctreeQuery::TestOctant)
//         .addFunction("TestDrawables", &SphereOctreeQuery::TestDrawables)
//         .addProperty("sphere", &SphereOctreeQuery::sphere_)
//     );
//     lua["KBoxOctreeQuery"].setClass(UserdataMetatable<BoxOctreeQuery, OctreeQuery>()
//         .setConstructors<BoxOctreeQuery(PODVector<Drawable*>&, const BoundingBox&, unsigned char, unsigned int)>()

//         .addFunction("TestOctant", &BoxOctreeQuery::TestOctant)
//         .addFunction("TestDrawables", &BoxOctreeQuery::TestDrawables)
//         .addProperty("box", &BoxOctreeQuery::box_)
//     );
//     lua["KFrustumOctreeQuery"].setClass(UserdataMetatable<FrustumOctreeQuery, OctreeQuery>()
//         .setConstructors<FrustumOctreeQuery(PODVector<Drawable*>&, const Frustum&, unsigned char, unsigned int)>()

//         .addFunction("TestOctant", &FrustumOctreeQuery::TestOctant)
//         .addFunction("TestDrawables", &FrustumOctreeQuery::TestDrawables)
//         .addProperty("frustum", &FrustumOctreeQuery::frustum_)
//     );
//     lua["KOctreeQueryResult"].setClass(UserdataMetatable<OctreeQueryResult>()
//         .setConstructors<OctreeQueryResult()>()

//         .addProperty("drawable", &OctreeQueryResult::drawable_)
//         .addProperty("node", &OctreeQueryResult::node_)
//     );
//     // enum RayQueryLevel;
//     lua["KRAY_AABB"] = RAY_AABB;
//     lua["KRAY_OBB"] = RAY_OBB;
//     lua["KRAY_TRIANGLE"] = RAY_TRIANGLE;
//     lua["KRAY_TRIANGLE_UV"] = RAY_TRIANGLE_UV;

//     lua["KRayQueryResult"].setClass(UserdataMetatable<RayQueryResult>()
//         .setConstructors<RayQueryResult()>()

//         .addProperty("position", &RayQueryResult::position_)
//         .addProperty("normal", &RayQueryResult::normal_)
//         .addProperty("textureUV", &RayQueryResult::textureUV_)
//         .addProperty("distance", &RayQueryResult::distance_)
//         .addProperty("drawable", &RayQueryResult::drawable_)
//         .addProperty("node", &RayQueryResult::node_)
//         .addProperty("subObject", &RayQueryResult::subObject_)
//     );
//     lua["KRayOctreeQuery"].setClass(UserdataMetatable<RayOctreeQuery>()
//         .setConstructors<RayOctreeQuery(PODVector<RayQueryResult>&, const Ray&, RayQueryLevel, float, unsigned char, unsigned int),
//             RayOctreeQuery(const RayOctreeQuery&)>()

//         .addProperty("result", &RayOctreeQuery::result_)
//         .addProperty("ray", &RayOctreeQuery::ray_)
//         .addProperty("drawableFlags", &RayOctreeQuery::drawableFlags_)
//         .addProperty("viewMask", &RayOctreeQuery::viewMask_)
//         .addProperty("maxDistance", &RayOctreeQuery::maxDistance_)
//         .addProperty("level", &RayOctreeQuery::level_)
//     );
//     lua["KAllContentOctreeQuery"].setClass(UserdataMetatable<AllContentOctreeQuery, OctreeQuery>()
//         .setConstructors<AllContentOctreeQuery(PODVector<Drawable*>&, unsigned char, unsigned int)>()

//         .addFunction("TestOctant", &AllContentOctreeQuery::TestOctant)
//         .addFunction("TestDrawables", &AllContentOctreeQuery::TestDrawables)
//     );
// }

// static void RegisterParticleEffect(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum EmitterType;
//     lua["KEMITTER_SPHERE"] = EMITTER_SPHERE;
//     lua["KEMITTER_BOX"] = EMITTER_BOX;

//     lua["KColorFrame"].setClass(UserdataMetatable<ColorFrame>()
//         .setConstructors<ColorFrame(),
//             ColorFrame(const Color&),
//             ColorFrame(const Color&, float)>()

//         .addFunction("Interpolate", &ColorFrame::Interpolate)
//         .addProperty("color", &ColorFrame::color_)
//         .addProperty("time", &ColorFrame::time_)
//     );
//     lua["KTextureFrame"].setClass(UserdataMetatable<TextureFrame>()
//         .setConstructors<TextureFrame()>()

//         .addProperty("uv", &TextureFrame::uv_)
//         .addProperty("time", &TextureFrame::time_)
//     );
//     lua["KDEFAULT_NUM_PARTICLES"] = DEFAULT_NUM_PARTICLES;
//     lua["KParticleEffect"].setClass(UserdataMetatable<ParticleEffect, Resource>(false)
//         .addStaticFunction("new", &KCreateObject<ParticleEffect>)
//         .addStaticFunction("__gc", &KReleaseObject<ParticleEffect>)

//         .addFunction("GetType", &ParticleEffect::GetType)
//         .addFunction("GetTypeName", &ParticleEffect::GetTypeName)
//         .addFunction("GetTypeInfo", &ParticleEffect::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &ParticleEffect::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &ParticleEffect::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &ParticleEffect::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &ParticleEffect::BeginLoad)
//         .addFunction("EndLoad", &ParticleEffect::EndLoad)

//         .addOverloadedFunctions("Save",
//             static_cast<bool(ParticleEffect::*)(Serializer&) const>(&ParticleEffect::Save),
//             static_cast<bool(ParticleEffect::*)(XMLElement&) const>(&ParticleEffect::Save))

//         .addFunction("Load", &ParticleEffect::Load)
//         .addFunction("SetMaterial", &ParticleEffect::SetMaterial)
//         .addFunction("SetNumParticles", &ParticleEffect::SetNumParticles)
//         .addFunction("SetUpdateInvisible", &ParticleEffect::SetUpdateInvisible)
//         .addFunction("SetRelative", &ParticleEffect::SetRelative)
//         .addFunction("SetScaled", &ParticleEffect::SetScaled)
//         .addFunction("SetSorted", &ParticleEffect::SetSorted)
//         .addFunction("SetFixedScreenSize", &ParticleEffect::SetFixedScreenSize)
//         .addFunction("SetAnimationLodBias", &ParticleEffect::SetAnimationLodBias)
//         .addFunction("SetEmitterType", &ParticleEffect::SetEmitterType)
//         .addFunction("SetEmitterSize", &ParticleEffect::SetEmitterSize)
//         .addFunction("SetMinDirection", &ParticleEffect::SetMinDirection)
//         .addFunction("SetMaxDirection", &ParticleEffect::SetMaxDirection)
//         .addFunction("SetConstantForce", &ParticleEffect::SetConstantForce)
//         .addFunction("SetDampingForce", &ParticleEffect::SetDampingForce)
//         .addFunction("SetActiveTime", &ParticleEffect::SetActiveTime)
//         .addFunction("SetInactiveTime", &ParticleEffect::SetInactiveTime)
//         .addFunction("SetMinEmissionRate", &ParticleEffect::SetMinEmissionRate)
//         .addFunction("SetMaxEmissionRate", &ParticleEffect::SetMaxEmissionRate)
//         .addFunction("SetMinParticleSize", &ParticleEffect::SetMinParticleSize)
//         .addFunction("SetMaxParticleSize", &ParticleEffect::SetMaxParticleSize)
//         .addFunction("SetMinTimeToLive", &ParticleEffect::SetMinTimeToLive)
//         .addFunction("SetMaxTimeToLive", &ParticleEffect::SetMaxTimeToLive)
//         .addFunction("SetMinVelocity", &ParticleEffect::SetMinVelocity)
//         .addFunction("SetMaxVelocity", &ParticleEffect::SetMaxVelocity)
//         .addFunction("SetMinRotation", &ParticleEffect::SetMinRotation)
//         .addFunction("SetMaxRotation", &ParticleEffect::SetMaxRotation)
//         .addFunction("SetMinRotationSpeed", &ParticleEffect::SetMinRotationSpeed)
//         .addFunction("SetMaxRotationSpeed", &ParticleEffect::SetMaxRotationSpeed)
//         .addFunction("SetSizeAdd", &ParticleEffect::SetSizeAdd)
//         .addFunction("SetSizeMul", &ParticleEffect::SetSizeMul)
//         .addFunction("SetFaceCameraMode", &ParticleEffect::SetFaceCameraMode)
//         .addFunction("AddColorTime", &ParticleEffect::AddColorTime)
//         .addFunction("AddColorFrame", &ParticleEffect::AddColorFrame)
//         .addFunction("RemoveColorFrame", &ParticleEffect::RemoveColorFrame)
//         .addFunction("SetColorFrames", &ParticleEffect::SetColorFrames)
//         .addFunction("SetColorFrame", &ParticleEffect::SetColorFrame)
//         .addFunction("SetNumColorFrames", &ParticleEffect::SetNumColorFrames)
//         .addFunction("SortColorFrames", &ParticleEffect::SortColorFrames)
//         .addFunction("AddTextureTime", &ParticleEffect::AddTextureTime)
//         .addFunction("AddTextureFrame", &ParticleEffect::AddTextureFrame)
//         .addFunction("RemoveTextureFrame", &ParticleEffect::RemoveTextureFrame)
//         .addFunction("SetTextureFrames", &ParticleEffect::SetTextureFrames)
//         .addFunction("SetTextureFrame", &ParticleEffect::SetTextureFrame)
//         .addFunction("SetNumTextureFrames", &ParticleEffect::SetNumTextureFrames)
//         .addFunction("SortTextureFrames", &ParticleEffect::SortTextureFrames)
//         .addFunction("GetMaterial", &ParticleEffect::GetMaterial)
//         .addFunction("GetNumParticles", &ParticleEffect::GetNumParticles)
//         .addFunction("GetUpdateInvisible", &ParticleEffect::GetUpdateInvisible)
//         .addFunction("IsRelative", &ParticleEffect::IsRelative)
//         .addFunction("IsScaled", &ParticleEffect::IsScaled)
//         .addFunction("IsSorted", &ParticleEffect::IsSorted)
//         .addFunction("IsFixedScreenSize", &ParticleEffect::IsFixedScreenSize)
//         .addFunction("GetAnimationLodBias", &ParticleEffect::GetAnimationLodBias)
//         .addFunction("GetEmitterType", &ParticleEffect::GetEmitterType)
//         .addFunction("GetEmitterSize", &ParticleEffect::GetEmitterSize)
//         .addFunction("GetMinDirection", &ParticleEffect::GetMinDirection)
//         .addFunction("GetMaxDirection", &ParticleEffect::GetMaxDirection)
//         .addFunction("GetConstantForce", &ParticleEffect::GetConstantForce)
//         .addFunction("GetDampingForce", &ParticleEffect::GetDampingForce)
//         .addFunction("GetActiveTime", &ParticleEffect::GetActiveTime)
//         .addFunction("GetInactiveTime", &ParticleEffect::GetInactiveTime)
//         .addFunction("GetMinEmissionRate", &ParticleEffect::GetMinEmissionRate)
//         .addFunction("GetMaxEmissionRate", &ParticleEffect::GetMaxEmissionRate)
//         .addFunction("GetMinParticleSize", &ParticleEffect::GetMinParticleSize)
//         .addFunction("GetMaxParticleSize", &ParticleEffect::GetMaxParticleSize)
//         .addFunction("GetMinTimeToLive", &ParticleEffect::GetMinTimeToLive)
//         .addFunction("GetMaxTimeToLive", &ParticleEffect::GetMaxTimeToLive)
//         .addFunction("GetMinVelocity", &ParticleEffect::GetMinVelocity)
//         .addFunction("GetMaxVelocity", &ParticleEffect::GetMaxVelocity)
//         .addFunction("GetMinRotation", &ParticleEffect::GetMinRotation)
//         .addFunction("GetMaxRotation", &ParticleEffect::GetMaxRotation)
//         .addFunction("GetMinRotationSpeed", &ParticleEffect::GetMinRotationSpeed)
//         .addFunction("GetMaxRotationSpeed", &ParticleEffect::GetMaxRotationSpeed)
//         .addFunction("GetSizeAdd", &ParticleEffect::GetSizeAdd)
//         .addFunction("GetSizeMul", &ParticleEffect::GetSizeMul)
//         .addFunction("GetColorFrames", &ParticleEffect::GetColorFrames)
//         .addFunction("GetNumColorFrames", &ParticleEffect::GetNumColorFrames)
//         .addFunction("GetColorFrame", &ParticleEffect::GetColorFrame)
//         .addFunction("GetTextureFrames", &ParticleEffect::GetTextureFrames)
//         .addFunction("GetNumTextureFrames", &ParticleEffect::GetNumTextureFrames)
//         .addFunction("GetTextureFrame", &ParticleEffect::GetTextureFrame)
//         .addFunction("GetFaceCameraMode", &ParticleEffect::GetFaceCameraMode)
//         .addFunction("GetRandomDirection", &ParticleEffect::GetRandomDirection)
//         .addFunction("GetRandomSize", &ParticleEffect::GetRandomSize)
//         .addFunction("GetRandomVelocity", &ParticleEffect::GetRandomVelocity)
//         .addFunction("GetRandomTimeToLive", &ParticleEffect::GetRandomTimeToLive)
//         .addFunction("GetRandomRotationSpeed", &ParticleEffect::GetRandomRotationSpeed)
//         .addFunction("GetRandomRotation", &ParticleEffect::GetRandomRotation)

//         .addProperty("type", &ParticleEffect::GetType)
//         .addProperty("typeName", &ParticleEffect::GetTypeName)
//         .addProperty("typeInfo", &ParticleEffect::GetTypeInfo)
//         .addProperty("material", &ParticleEffect::GetMaterial, &ParticleEffect::SetMaterial)
//         .addProperty("numParticles", &ParticleEffect::GetNumParticles, &ParticleEffect::SetNumParticles)
//         .addProperty("updateInvisible", &ParticleEffect::GetUpdateInvisible, &ParticleEffect::SetUpdateInvisible)
//         .addProperty("relative", &ParticleEffect::IsRelative, &ParticleEffect::SetRelative)
//         .addProperty("scaled", &ParticleEffect::IsScaled, &ParticleEffect::SetScaled)
//         .addProperty("sorted", &ParticleEffect::IsSorted, &ParticleEffect::SetSorted)
//         .addProperty("fixedScreenSize", &ParticleEffect::IsFixedScreenSize, &ParticleEffect::SetFixedScreenSize)
//         .addProperty("animationLodBias", &ParticleEffect::GetAnimationLodBias, &ParticleEffect::SetAnimationLodBias)
//         .addProperty("emitterType", &ParticleEffect::GetEmitterType, &ParticleEffect::SetEmitterType)
//         .addProperty("emitterSize", &ParticleEffect::GetEmitterSize, &ParticleEffect::SetEmitterSize)
//         .addProperty("minDirection", &ParticleEffect::GetMinDirection, &ParticleEffect::SetMinDirection)
//         .addProperty("maxDirection", &ParticleEffect::GetMaxDirection, &ParticleEffect::SetMaxDirection)
//         .addProperty("constantForce", &ParticleEffect::GetConstantForce, &ParticleEffect::SetConstantForce)
//         .addProperty("dampingForce", &ParticleEffect::GetDampingForce, &ParticleEffect::SetDampingForce)
//         .addProperty("activeTime", &ParticleEffect::GetActiveTime, &ParticleEffect::SetActiveTime)
//         .addProperty("inactiveTime", &ParticleEffect::GetInactiveTime, &ParticleEffect::SetInactiveTime)
//         .addProperty("minEmissionRate", &ParticleEffect::GetMinEmissionRate, &ParticleEffect::SetMinEmissionRate)
//         .addProperty("maxEmissionRate", &ParticleEffect::GetMaxEmissionRate, &ParticleEffect::SetMaxEmissionRate)
//         .addProperty("minParticleSize", &ParticleEffect::GetMinParticleSize, &ParticleEffect::SetMinParticleSize)
//         .addProperty("maxParticleSize", &ParticleEffect::GetMaxParticleSize, &ParticleEffect::SetMaxParticleSize)
//         .addProperty("minTimeToLive", &ParticleEffect::GetMinTimeToLive, &ParticleEffect::SetMinTimeToLive)
//         .addProperty("maxTimeToLive", &ParticleEffect::GetMaxTimeToLive, &ParticleEffect::SetMaxTimeToLive)
//         .addProperty("minVelocity", &ParticleEffect::GetMinVelocity, &ParticleEffect::SetMinVelocity)
//         .addProperty("maxVelocity", &ParticleEffect::GetMaxVelocity, &ParticleEffect::SetMaxVelocity)
//         .addProperty("minRotation", &ParticleEffect::GetMinRotation, &ParticleEffect::SetMinRotation)
//         .addProperty("maxRotation", &ParticleEffect::GetMaxRotation, &ParticleEffect::SetMaxRotation)
//         .addProperty("minRotationSpeed", &ParticleEffect::GetMinRotationSpeed, &ParticleEffect::SetMinRotationSpeed)
//         .addProperty("maxRotationSpeed", &ParticleEffect::GetMaxRotationSpeed, &ParticleEffect::SetMaxRotationSpeed)
//         .addProperty("sizeAdd", &ParticleEffect::GetSizeAdd, &ParticleEffect::SetSizeAdd)
//         .addProperty("sizeMul", &ParticleEffect::GetSizeMul, &ParticleEffect::SetSizeMul)
//         .addProperty("colorFrames", &ParticleEffect::GetColorFrames, &ParticleEffect::SetColorFrames)
//         .addProperty("numColorFrames", &ParticleEffect::GetNumColorFrames, &ParticleEffect::SetNumColorFrames)
//         .addProperty("textureFrames", &ParticleEffect::GetTextureFrames, &ParticleEffect::SetTextureFrames)
//         .addProperty("numTextureFrames", &ParticleEffect::GetNumTextureFrames, &ParticleEffect::SetNumTextureFrames)
//         .addProperty("faceCameraMode", &ParticleEffect::GetFaceCameraMode, &ParticleEffect::SetFaceCameraMode)
//         .addProperty("randomDirection", &ParticleEffect::GetRandomDirection)
//         .addProperty("randomSize", &ParticleEffect::GetRandomSize)
//         .addProperty("randomVelocity", &ParticleEffect::GetRandomVelocity)
//         .addProperty("randomTimeToLive", &ParticleEffect::GetRandomTimeToLive)
//         .addProperty("randomRotationSpeed", &ParticleEffect::GetRandomRotationSpeed)
//         .addProperty("randomRotation", &ParticleEffect::GetRandomRotation)
//     );
// }

// static void RegisterParticleEmitter(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KParticle"].setClass(UserdataMetatable<Particle>()

//         .addProperty("velocity", &Particle::velocity_)
//         .addProperty("size", &Particle::size_)
//         .addProperty("timer", &Particle::timer_)
//         .addProperty("timeToLive", &Particle::timeToLive_)
//         .addProperty("scale", &Particle::scale_)
//         .addProperty("rotationSpeed", &Particle::rotationSpeed_)
//         .addProperty("colorIndex", &Particle::colorIndex_)
//         .addProperty("texIndex", &Particle::texIndex_)
//     );
//     lua["KParticleEmitter"].setClass(UserdataMetatable<ParticleEmitter, BillboardSet>(false)
//         .addStaticFunction("new", &KCreateObject<ParticleEmitter>)
//         .addStaticFunction("__gc", &KReleaseObject<ParticleEmitter>)

//         .addFunction("GetType", &ParticleEmitter::GetType)
//         .addFunction("GetTypeName", &ParticleEmitter::GetTypeName)
//         .addFunction("GetTypeInfo", &ParticleEmitter::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &ParticleEmitter::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &ParticleEmitter::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &ParticleEmitter::GetTypeInfoStatic)
//         .addFunction("OnSetEnabled", &ParticleEmitter::OnSetEnabled)
//         .addFunction("Update", &ParticleEmitter::Update)
//         .addFunction("SetEffect", &ParticleEmitter::SetEffect)
//         .addFunction("SetNumParticles", &ParticleEmitter::SetNumParticles)
//         .addFunction("SetEmitting", &ParticleEmitter::SetEmitting)
//         .addFunction("SetSerializeParticles", &ParticleEmitter::SetSerializeParticles)
//         .addFunction("ResetEmissionTimer", &ParticleEmitter::ResetEmissionTimer)
//         .addFunction("RemoveAllParticles", &ParticleEmitter::RemoveAllParticles)
//         .addFunction("Reset", &ParticleEmitter::Reset)
//         .addFunction("ApplyEffect", &ParticleEmitter::ApplyEffect)
//         .addFunction("GetEffect", &ParticleEmitter::GetEffect)
//         .addFunction("GetNumParticles", &ParticleEmitter::GetNumParticles)
//         .addFunction("IsEmitting", &ParticleEmitter::IsEmitting)
//         .addFunction("GetSerializeParticles", &ParticleEmitter::GetSerializeParticles)

//         .addProperty("type", &ParticleEmitter::GetType)
//         .addProperty("typeName", &ParticleEmitter::GetTypeName)
//         .addProperty("typeInfo", &ParticleEmitter::GetTypeInfo)
//         .addProperty("effect", &ParticleEmitter::GetEffect, &ParticleEmitter::SetEffect)
//         .addProperty("numParticles", &ParticleEmitter::GetNumParticles, &ParticleEmitter::SetNumParticles)
//         .addProperty("emitting", &ParticleEmitter::IsEmitting, &ParticleEmitter::SetEmitting)
//         .addProperty("serializeParticles", &ParticleEmitter::GetSerializeParticles, &ParticleEmitter::SetSerializeParticles)
//     );
// }

// static void RegisterRenderer(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KSHADOW_MIN_PIXELS"] = SHADOW_MIN_PIXELS;
//     lua["KINSTANCING_BUFFER_DEFAULT_SIZE"] = INSTANCING_BUFFER_DEFAULT_SIZE;
//     // enum LightVSVariation;
//     lua["KLVS_DIR"] = LVS_DIR;
//     lua["KLVS_SPOT"] = LVS_SPOT;
//     lua["KLVS_POINT"] = LVS_POINT;
//     lua["KLVS_SHADOW"] = LVS_SHADOW;
//     lua["KLVS_SPOTSHADOW"] = LVS_SPOTSHADOW;
//     lua["KLVS_POINTSHADOW"] = LVS_POINTSHADOW;
//     lua["KLVS_SHADOWNORMALOFFSET"] = LVS_SHADOWNORMALOFFSET;
//     lua["KLVS_SPOTSHADOWNORMALOFFSET"] = LVS_SPOTSHADOWNORMALOFFSET;
//     lua["KLVS_POINTSHADOWNORMALOFFSET"] = LVS_POINTSHADOWNORMALOFFSET;
//     lua["KMAX_LIGHT_VS_VARIATIONS"] = MAX_LIGHT_VS_VARIATIONS;

//     // enum VertexLightVSVariation;
//     lua["KVLVS_NOLIGHTS"] = VLVS_NOLIGHTS;
//     lua["KVLVS_1LIGHT"] = VLVS_1LIGHT;
//     lua["KVLVS_2LIGHTS"] = VLVS_2LIGHTS;
//     lua["KVLVS_3LIGHTS"] = VLVS_3LIGHTS;
//     lua["KVLVS_4LIGHTS"] = VLVS_4LIGHTS;
//     lua["KMAX_VERTEXLIGHT_VS_VARIATIONS"] = MAX_VERTEXLIGHT_VS_VARIATIONS;

//     // enum LightPSVariation;
//     lua["KLPS_NONE"] = LPS_NONE;
//     lua["KLPS_SPOT"] = LPS_SPOT;
//     lua["KLPS_POINT"] = LPS_POINT;
//     lua["KLPS_POINTMASK"] = LPS_POINTMASK;
//     lua["KLPS_SPEC"] = LPS_SPEC;
//     lua["KLPS_SPOTSPEC"] = LPS_SPOTSPEC;
//     lua["KLPS_POINTSPEC"] = LPS_POINTSPEC;
//     lua["KLPS_POINTMASKSPEC"] = LPS_POINTMASKSPEC;
//     lua["KLPS_SHADOW"] = LPS_SHADOW;
//     lua["KLPS_SPOTSHADOW"] = LPS_SPOTSHADOW;
//     lua["KLPS_POINTSHADOW"] = LPS_POINTSHADOW;
//     lua["KLPS_POINTMASKSHADOW"] = LPS_POINTMASKSHADOW;
//     lua["KLPS_SHADOWSPEC"] = LPS_SHADOWSPEC;
//     lua["KLPS_SPOTSHADOWSPEC"] = LPS_SPOTSHADOWSPEC;
//     lua["KLPS_POINTSHADOWSPEC"] = LPS_POINTSHADOWSPEC;
//     lua["KLPS_POINTMASKSHADOWSPEC"] = LPS_POINTMASKSHADOWSPEC;
//     lua["KMAX_LIGHT_PS_VARIATIONS"] = MAX_LIGHT_PS_VARIATIONS;

//     // enum DeferredLightVSVariation;
//     lua["KDLVS_NONE"] = DLVS_NONE;
//     lua["KDLVS_DIR"] = DLVS_DIR;
//     lua["KDLVS_ORTHO"] = DLVS_ORTHO;
//     lua["KDLVS_ORTHODIR"] = DLVS_ORTHODIR;
//     lua["KMAX_DEFERRED_LIGHT_VS_VARIATIONS"] = MAX_DEFERRED_LIGHT_VS_VARIATIONS;

//     // enum DeferredLightPSVariation;
//     lua["KDLPS_NONE"] = DLPS_NONE;
//     lua["KDLPS_SPOT"] = DLPS_SPOT;
//     lua["KDLPS_POINT"] = DLPS_POINT;
//     lua["KDLPS_POINTMASK"] = DLPS_POINTMASK;
//     lua["KDLPS_SPEC"] = DLPS_SPEC;
//     lua["KDLPS_SPOTSPEC"] = DLPS_SPOTSPEC;
//     lua["KDLPS_POINTSPEC"] = DLPS_POINTSPEC;
//     lua["KDLPS_POINTMASKSPEC"] = DLPS_POINTMASKSPEC;
//     lua["KDLPS_SHADOW"] = DLPS_SHADOW;
//     lua["KDLPS_SPOTSHADOW"] = DLPS_SPOTSHADOW;
//     lua["KDLPS_POINTSHADOW"] = DLPS_POINTSHADOW;
//     lua["KDLPS_POINTMASKSHADOW"] = DLPS_POINTMASKSHADOW;
//     lua["KDLPS_SHADOWSPEC"] = DLPS_SHADOWSPEC;
//     lua["KDLPS_SPOTSHADOWSPEC"] = DLPS_SPOTSHADOWSPEC;
//     lua["KDLPS_POINTSHADOWSPEC"] = DLPS_POINTSHADOWSPEC;
//     lua["KDLPS_POINTMASKSHADOWSPEC"] = DLPS_POINTMASKSHADOWSPEC;
//     lua["KDLPS_SHADOWNORMALOFFSET"] = DLPS_SHADOWNORMALOFFSET;
//     lua["KDLPS_SPOTSHADOWNORMALOFFSET"] = DLPS_SPOTSHADOWNORMALOFFSET;
//     lua["KDLPS_POINTSHADOWNORMALOFFSET"] = DLPS_POINTSHADOWNORMALOFFSET;
//     lua["KDLPS_POINTMASKSHADOWNORMALOFFSET"] = DLPS_POINTMASKSHADOWNORMALOFFSET;
//     lua["KDLPS_SHADOWSPECNORMALOFFSET"] = DLPS_SHADOWSPECNORMALOFFSET;
//     lua["KDLPS_SPOTSHADOWSPECNORMALOFFSET"] = DLPS_SPOTSHADOWSPECNORMALOFFSET;
//     lua["KDLPS_POINTSHADOWSPECNORMALOFFSET"] = DLPS_POINTSHADOWSPECNORMALOFFSET;
//     lua["KDLPS_POINTMASKSHADOWSPECNORMALOFFSET"] = DLPS_POINTMASKSHADOWSPECNORMALOFFSET;
//     lua["KDLPS_ORTHO"] = DLPS_ORTHO;
//     lua["KDLPS_ORTHOSPOT"] = DLPS_ORTHOSPOT;
//     lua["KDLPS_ORTHOPOINT"] = DLPS_ORTHOPOINT;
//     lua["KDLPS_ORTHOPOINTMASK"] = DLPS_ORTHOPOINTMASK;
//     lua["KDLPS_ORTHOSPEC"] = DLPS_ORTHOSPEC;
//     lua["KDLPS_ORTHOSPOTSPEC"] = DLPS_ORTHOSPOTSPEC;
//     lua["KDLPS_ORTHOPOINTSPEC"] = DLPS_ORTHOPOINTSPEC;
//     lua["KDLPS_ORTHOPOINTMASKSPEC"] = DLPS_ORTHOPOINTMASKSPEC;
//     lua["KDLPS_ORTHOSHADOW"] = DLPS_ORTHOSHADOW;
//     lua["KDLPS_ORTHOSPOTSHADOW"] = DLPS_ORTHOSPOTSHADOW;
//     lua["KDLPS_ORTHOPOINTSHADOW"] = DLPS_ORTHOPOINTSHADOW;
//     lua["KDLPS_ORTHOPOINTMASKSHADOW"] = DLPS_ORTHOPOINTMASKSHADOW;
//     lua["KDLPS_ORTHOSHADOWSPEC"] = DLPS_ORTHOSHADOWSPEC;
//     lua["KDLPS_ORTHOSPOTSHADOWSPEC"] = DLPS_ORTHOSPOTSHADOWSPEC;
//     lua["KDLPS_ORTHOPOINTSHADOWSPEC"] = DLPS_ORTHOPOINTSHADOWSPEC;
//     lua["KDLPS_ORTHOPOINTMASKSHADOWSPEC"] = DLPS_ORTHOPOINTMASKSHADOWSPEC;
//     lua["KDLPS_ORTHOSHADOWNORMALOFFSET"] = DLPS_ORTHOSHADOWNORMALOFFSET;
//     lua["KDLPS_ORTHOSPOTSHADOWNORMALOFFSET"] = DLPS_ORTHOSPOTSHADOWNORMALOFFSET;
//     lua["KDLPS_ORTHOPOINTSHADOWNORMALOFFSET"] = DLPS_ORTHOPOINTSHADOWNORMALOFFSET;
//     lua["KDLPS_ORTHOPOINTMASKSHADOWNORMALOFFSET"] = DLPS_ORTHOPOINTMASKSHADOWNORMALOFFSET;
//     lua["KDLPS_ORTHOSHADOWSPECNORMALOFFSET"] = DLPS_ORTHOSHADOWSPECNORMALOFFSET;
//     lua["KDLPS_ORTHOSPOTSHADOWSPECNORMALOFFSET"] = DLPS_ORTHOSPOTSHADOWSPECNORMALOFFSET;
//     lua["KDLPS_ORTHOPOINTSHADOWSPECNORMALOFFSET"] = DLPS_ORTHOPOINTSHADOWSPECNORMALOFFSET;
//     lua["KDLPS_ORTHOPOINTMASKSHADOWSPECNORMALOFFSET"] = DLPS_ORTHOPOINTMASKSHADOWSPECNORMALOFFSET;
//     lua["KMAX_DEFERRED_LIGHT_PS_VARIATIONS"] = MAX_DEFERRED_LIGHT_PS_VARIATIONS;

//     lua["KRenderer"].setClass(UserdataMetatable<Renderer, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Renderer>)
//         .addStaticFunction("__gc", &KReleaseObject<Renderer>)

//         .addFunction("GetType", &Renderer::GetType)
//         .addFunction("GetTypeName", &Renderer::GetTypeName)
//         .addFunction("GetTypeInfo", &Renderer::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Renderer::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Renderer::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Renderer::GetTypeInfoStatic)
//         .addFunction("SetNumViewports", &Renderer::SetNumViewports)
//         .addFunction("SetViewport", &Renderer::SetViewport)

//         .addOverloadedFunctions("SetDefaultRenderPath",
//             static_cast<void(Renderer::*)(RenderPath*)>(&Renderer::SetDefaultRenderPath),
//             static_cast<void(Renderer::*)(XMLFile*)>(&Renderer::SetDefaultRenderPath))

//         .addFunction("SetDefaultTechnique", &Renderer::SetDefaultTechnique)
//         .addFunction("SetHDRRendering", &Renderer::SetHDRRendering)
//         .addFunction("SetSpecularLighting", &Renderer::SetSpecularLighting)
//         .addFunction("SetTextureAnisotropy", &Renderer::SetTextureAnisotropy)
//         .addFunction("SetTextureFilterMode", &Renderer::SetTextureFilterMode)
//         .addFunction("SetTextureQuality", &Renderer::SetTextureQuality)
//         .addFunction("SetMaterialQuality", &Renderer::SetMaterialQuality)
//         .addFunction("SetDrawShadows", &Renderer::SetDrawShadows)
//         .addFunction("SetShadowMapSize", &Renderer::SetShadowMapSize)
//         .addFunction("SetShadowQuality", &Renderer::SetShadowQuality)
//         .addFunction("SetShadowSoftness", &Renderer::SetShadowSoftness)
//         .addFunction("SetVSMShadowParameters", &Renderer::SetVSMShadowParameters)
//         .addFunction("SetShadowMapFilter", &Renderer::SetShadowMapFilter)
//         .addFunction("SetReuseShadowMaps", &Renderer::SetReuseShadowMaps)
//         .addFunction("SetMaxShadowMaps", &Renderer::SetMaxShadowMaps)
//         .addFunction("SetDynamicInstancing", &Renderer::SetDynamicInstancing)
//         .addFunction("SetNumExtraInstancingBufferElements", &Renderer::SetNumExtraInstancingBufferElements)
//         .addFunction("SetMinInstances", &Renderer::SetMinInstances)
//         .addFunction("SetMaxSortedInstances", &Renderer::SetMaxSortedInstances)
//         .addFunction("SetMaxOccluderTriangles", &Renderer::SetMaxOccluderTriangles)
//         .addFunction("SetOcclusionBufferSize", &Renderer::SetOcclusionBufferSize)
//         .addFunction("SetOccluderSizeThreshold", &Renderer::SetOccluderSizeThreshold)
//         .addFunction("SetThreadedOcclusion", &Renderer::SetThreadedOcclusion)
//         .addFunction("SetMobileShadowBiasMul", &Renderer::SetMobileShadowBiasMul)
//         .addFunction("SetMobileShadowBiasAdd", &Renderer::SetMobileShadowBiasAdd)
//         .addFunction("SetMobileNormalOffsetMul", &Renderer::SetMobileNormalOffsetMul)
//         .addFunction("ReloadShaders", &Renderer::ReloadShaders)
//         .addFunction("ApplyShadowMapFilter", &Renderer::ApplyShadowMapFilter)
//         .addFunction("GetNumViewports", &Renderer::GetNumViewports)
//         .addFunction("GetViewport", &Renderer::GetViewport)
//         .addFunction("GetDefaultRenderPath", &Renderer::GetDefaultRenderPath)
//         .addFunction("GetDefaultTechnique", &Renderer::GetDefaultTechnique)
//         .addFunction("GetHDRRendering", &Renderer::GetHDRRendering)
//         .addFunction("GetSpecularLighting", &Renderer::GetSpecularLighting)
//         .addFunction("GetDrawShadows", &Renderer::GetDrawShadows)
//         .addFunction("GetTextureAnisotropy", &Renderer::GetTextureAnisotropy)
//         .addFunction("GetTextureFilterMode", &Renderer::GetTextureFilterMode)
//         .addFunction("GetTextureQuality", &Renderer::GetTextureQuality)
//         .addFunction("GetMaterialQuality", &Renderer::GetMaterialQuality)
//         .addFunction("GetShadowMapSize", &Renderer::GetShadowMapSize)
//         .addFunction("GetShadowQuality", &Renderer::GetShadowQuality)
//         .addFunction("GetShadowSoftness", &Renderer::GetShadowSoftness)
//         .addFunction("GetVSMShadowParameters", &Renderer::GetVSMShadowParameters)
//         .addFunction("GetReuseShadowMaps", &Renderer::GetReuseShadowMaps)
//         .addFunction("GetMaxShadowMaps", &Renderer::GetMaxShadowMaps)
//         .addFunction("GetDynamicInstancing", &Renderer::GetDynamicInstancing)
//         .addFunction("GetNumExtraInstancingBufferElements", &Renderer::GetNumExtraInstancingBufferElements)
//         .addFunction("GetMinInstances", &Renderer::GetMinInstances)
//         .addFunction("GetMaxSortedInstances", &Renderer::GetMaxSortedInstances)
//         .addFunction("GetMaxOccluderTriangles", &Renderer::GetMaxOccluderTriangles)
//         .addFunction("GetOcclusionBufferSize", &Renderer::GetOcclusionBufferSize)
//         .addFunction("GetOccluderSizeThreshold", &Renderer::GetOccluderSizeThreshold)
//         .addFunction("GetThreadedOcclusion", &Renderer::GetThreadedOcclusion)
//         .addFunction("GetMobileShadowBiasMul", &Renderer::GetMobileShadowBiasMul)
//         .addFunction("GetMobileShadowBiasAdd", &Renderer::GetMobileShadowBiasAdd)
//         .addFunction("GetMobileNormalOffsetMul", &Renderer::GetMobileNormalOffsetMul)
//         .addFunction("GetNumViews", &Renderer::GetNumViews)
//         .addFunction("GetNumPrimitives", &Renderer::GetNumPrimitives)
//         .addFunction("GetNumBatches", &Renderer::GetNumBatches)
//         .addFunction("GetNumGeometries", &Renderer::GetNumGeometries)
//         .addFunction("GetNumLights", &Renderer::GetNumLights)
//         .addFunction("GetNumShadowMaps", &Renderer::GetNumShadowMaps)
//         .addFunction("GetNumOccluders", &Renderer::GetNumOccluders)
//         .addFunction("GetDefaultZone", &Renderer::GetDefaultZone)
//         .addFunction("GetDefaultMaterial", &Renderer::GetDefaultMaterial)
//         .addFunction("GetDefaultLightRamp", &Renderer::GetDefaultLightRamp)
//         .addFunction("GetDefaultLightSpot", &Renderer::GetDefaultLightSpot)
//         .addFunction("GetFaceSelectCubeMap", &Renderer::GetFaceSelectCubeMap)
//         .addFunction("GetIndirectionCubeMap", &Renderer::GetIndirectionCubeMap)
//         .addFunction("GetInstancingBuffer", &Renderer::GetInstancingBuffer)
//         .addFunction("GetFrameInfo", &Renderer::GetFrameInfo)
//         .addFunction("Update", &Renderer::Update)
//         .addFunction("Render", &Renderer::Render)
//         .addFunction("DrawDebugGeometry", &Renderer::DrawDebugGeometry)
//         .addFunction("QueueRenderSurface", &Renderer::QueueRenderSurface)
//         .addFunction("QueueViewport", &Renderer::QueueViewport)
//         .addFunction("GetLightGeometry", &Renderer::GetLightGeometry)
//         .addFunction("GetQuadGeometry", &Renderer::GetQuadGeometry)
//         .addFunction("GetShadowMap", &Renderer::GetShadowMap)
//         .addFunction("GetScreenBuffer", &Renderer::GetScreenBuffer)
//         .addFunction("GetDepthStencil", &Renderer::GetDepthStencil)
//         .addFunction("GetOcclusionBuffer", &Renderer::GetOcclusionBuffer)
//         .addFunction("GetShadowCamera", &Renderer::GetShadowCamera)
//         .addFunction("StorePreparedView", &Renderer::StorePreparedView)
//         .addFunction("GetPreparedView", &Renderer::GetPreparedView)
//         .addFunction("SetBatchShaders", &Renderer::SetBatchShaders)
//         .addFunction("SetLightVolumeBatchShaders", &Renderer::SetLightVolumeBatchShaders)
//         .addFunction("SetCullMode", &Renderer::SetCullMode)
//         .addFunction("ResizeInstancingBuffer", &Renderer::ResizeInstancingBuffer)
//         .addFunction("SaveScreenBufferAllocations", &Renderer::SaveScreenBufferAllocations)
//         .addFunction("RestoreScreenBufferAllocations", &Renderer::RestoreScreenBufferAllocations)
//         .addFunction("OptimizeLightByScissor", &Renderer::OptimizeLightByScissor)
//         .addFunction("OptimizeLightByStencil", &Renderer::OptimizeLightByStencil)
//         .addFunction("GetLightScissor", &Renderer::GetLightScissor)
//         .addStaticFunction("GetActualView", &Renderer::GetActualView)

//         .addProperty("type", &Renderer::GetType)
//         .addProperty("typeName", &Renderer::GetTypeName)
//         .addProperty("typeInfo", &Renderer::GetTypeInfo)
//         .addProperty("numViewports", &Renderer::GetNumViewports, &Renderer::SetNumViewports)
//         .addProperty("defaultRenderPath", &Renderer::GetDefaultRenderPath)
//         .addProperty("defaultTechnique", &Renderer::GetDefaultTechnique, &Renderer::SetDefaultTechnique)
//         .addProperty("hDRRendering", &Renderer::GetHDRRendering, &Renderer::SetHDRRendering)
//         .addProperty("specularLighting", &Renderer::GetSpecularLighting, &Renderer::SetSpecularLighting)
//         .addProperty("drawShadows", &Renderer::GetDrawShadows, &Renderer::SetDrawShadows)
//         .addProperty("textureAnisotropy", &Renderer::GetTextureAnisotropy, &Renderer::SetTextureAnisotropy)
//         .addProperty("textureFilterMode", &Renderer::GetTextureFilterMode, &Renderer::SetTextureFilterMode)
//         .addProperty("textureQuality", &Renderer::GetTextureQuality, &Renderer::SetTextureQuality)
//         .addProperty("materialQuality", &Renderer::GetMaterialQuality, &Renderer::SetMaterialQuality)
//         .addProperty("shadowMapSize", &Renderer::GetShadowMapSize, &Renderer::SetShadowMapSize)
//         .addProperty("shadowQuality", &Renderer::GetShadowQuality, &Renderer::SetShadowQuality)
//         .addProperty("shadowSoftness", &Renderer::GetShadowSoftness, &Renderer::SetShadowSoftness)
//         .addProperty("vSMShadowParameters", &Renderer::GetVSMShadowParameters)
//         .addProperty("reuseShadowMaps", &Renderer::GetReuseShadowMaps, &Renderer::SetReuseShadowMaps)
//         .addProperty("maxShadowMaps", &Renderer::GetMaxShadowMaps, &Renderer::SetMaxShadowMaps)
//         .addProperty("dynamicInstancing", &Renderer::GetDynamicInstancing, &Renderer::SetDynamicInstancing)
//         .addProperty("numExtraInstancingBufferElements", &Renderer::GetNumExtraInstancingBufferElements, &Renderer::SetNumExtraInstancingBufferElements)
//         .addProperty("minInstances", &Renderer::GetMinInstances, &Renderer::SetMinInstances)
//         .addProperty("maxSortedInstances", &Renderer::GetMaxSortedInstances, &Renderer::SetMaxSortedInstances)
//         .addProperty("maxOccluderTriangles", &Renderer::GetMaxOccluderTriangles, &Renderer::SetMaxOccluderTriangles)
//         .addProperty("occlusionBufferSize", &Renderer::GetOcclusionBufferSize, &Renderer::SetOcclusionBufferSize)
//         .addProperty("occluderSizeThreshold", &Renderer::GetOccluderSizeThreshold, &Renderer::SetOccluderSizeThreshold)
//         .addProperty("threadedOcclusion", &Renderer::GetThreadedOcclusion, &Renderer::SetThreadedOcclusion)
//         .addProperty("mobileShadowBiasMul", &Renderer::GetMobileShadowBiasMul, &Renderer::SetMobileShadowBiasMul)
//         .addProperty("mobileShadowBiasAdd", &Renderer::GetMobileShadowBiasAdd, &Renderer::SetMobileShadowBiasAdd)
//         .addProperty("mobileNormalOffsetMul", &Renderer::GetMobileNormalOffsetMul, &Renderer::SetMobileNormalOffsetMul)
//         .addProperty("numViews", &Renderer::GetNumViews)
//         .addProperty("numPrimitives", &Renderer::GetNumPrimitives)
//         .addProperty("numBatches", &Renderer::GetNumBatches)
//         .addProperty("defaultZone", &Renderer::GetDefaultZone)
//         .addProperty("defaultMaterial", &Renderer::GetDefaultMaterial)
//         .addProperty("defaultLightRamp", &Renderer::GetDefaultLightRamp)
//         .addProperty("defaultLightSpot", &Renderer::GetDefaultLightSpot)
//         .addProperty("faceSelectCubeMap", &Renderer::GetFaceSelectCubeMap)
//         .addProperty("indirectionCubeMap", &Renderer::GetIndirectionCubeMap)
//         .addProperty("instancingBuffer", &Renderer::GetInstancingBuffer)
//         .addProperty("frameInfo", &Renderer::GetFrameInfo)
//         .addProperty("quadGeometry", &Renderer::GetQuadGeometry)
//         .addProperty("shadowCamera", &Renderer::GetShadowCamera)
//     );
// }

// static void RegisterRenderPath(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum RenderCommandType;
//     lua["KCMD_NONE"] = CMD_NONE;
//     lua["KCMD_CLEAR"] = CMD_CLEAR;
//     lua["KCMD_SCENEPASS"] = CMD_SCENEPASS;
//     lua["KCMD_QUAD"] = CMD_QUAD;
//     lua["KCMD_FORWARDLIGHTS"] = CMD_FORWARDLIGHTS;
//     lua["KCMD_LIGHTVOLUMES"] = CMD_LIGHTVOLUMES;
//     lua["KCMD_RENDERUI"] = CMD_RENDERUI;
//     lua["KCMD_SENDEVENT"] = CMD_SENDEVENT;

//     // enum RenderCommandSortMode;
//     lua["KSORT_FRONTTOBACK"] = SORT_FRONTTOBACK;
//     lua["KSORT_BACKTOFRONT"] = SORT_BACKTOFRONT;

//     // enum RenderTargetSizeMode;
//     lua["KSIZE_ABSOLUTE"] = SIZE_ABSOLUTE;
//     lua["KSIZE_VIEWPORTDIVISOR"] = SIZE_VIEWPORTDIVISOR;
//     lua["KSIZE_VIEWPORTMULTIPLIER"] = SIZE_VIEWPORTMULTIPLIER;

//     lua["KRenderTargetInfo"].setClass(UserdataMetatable<RenderTargetInfo>()
//         .setConstructors<RenderTargetInfo()>()

//         .addFunction("Load", &RenderTargetInfo::Load)
//         .addProperty("name", &RenderTargetInfo::name_)
//         .addProperty("tag", &RenderTargetInfo::tag_)
//         .addProperty("format", &RenderTargetInfo::format_)
//         .addProperty("size", &RenderTargetInfo::size_)
//         .addProperty("sizeMode", &RenderTargetInfo::sizeMode_)
//         .addProperty("enabled", &RenderTargetInfo::enabled_)
//         .addProperty("cubemap", &RenderTargetInfo::cubemap_)
//         .addProperty("filtered", &RenderTargetInfo::filtered_)
//         .addProperty("sRGB", &RenderTargetInfo::sRGB_)
//         .addProperty("persistent", &RenderTargetInfo::persistent_)
//     );
//     lua["KRenderPathCommand"].setClass(UserdataMetatable<RenderPathCommand>()
//         .setConstructors<RenderPathCommand()>()

//         .addFunction("Load", &RenderPathCommand::Load)
//         .addFunction("SetTextureName", &RenderPathCommand::SetTextureName)
//         .addFunction("SetShaderParameter", &RenderPathCommand::SetShaderParameter)
//         .addFunction("RemoveShaderParameter", &RenderPathCommand::RemoveShaderParameter)
//         .addFunction("SetNumOutputs", &RenderPathCommand::SetNumOutputs)
//         .addFunction("SetOutput", &RenderPathCommand::SetOutput)
//         .addFunction("SetOutputName", &RenderPathCommand::SetOutputName)
//         .addFunction("SetOutputFace", &RenderPathCommand::SetOutputFace)
//         .addFunction("SetDepthStencilName", &RenderPathCommand::SetDepthStencilName)
//         .addFunction("GetTextureName", &RenderPathCommand::GetTextureName)
//         .addFunction("GetShaderParameter", &RenderPathCommand::GetShaderParameter)
//         .addFunction("GetNumOutputs", &RenderPathCommand::GetNumOutputs)
//         .addFunction("GetOutputName", &RenderPathCommand::GetOutputName)
//         .addFunction("GetOutputFace", &RenderPathCommand::GetOutputFace)
//         .addFunction("GetDepthStencilName", &RenderPathCommand::GetDepthStencilName)

//         .addProperty("numOutputs", &RenderPathCommand::GetNumOutputs, &RenderPathCommand::SetNumOutputs)
//         .addProperty("depthStencilName", &RenderPathCommand::GetDepthStencilName, &RenderPathCommand::SetDepthStencilName)
//         .addProperty("tag", &RenderPathCommand::tag_)
//         .addProperty("type", &RenderPathCommand::type_)
//         .addProperty("sortMode", &RenderPathCommand::sortMode_)
//         .addProperty("pass", &RenderPathCommand::pass_)
//         .addProperty("passIndex", &RenderPathCommand::passIndex_)
//         .addProperty("metadata", &RenderPathCommand::metadata_)
//         .addProperty("vertexShaderName", &RenderPathCommand::vertexShaderName_)
//         .addProperty("pixelShaderName", &RenderPathCommand::pixelShaderName_)
//         .addProperty("vertexShaderDefines", &RenderPathCommand::vertexShaderDefines_)
//         .addProperty("pixelShaderDefines", &RenderPathCommand::pixelShaderDefines_)
//         .addProperty("textureNames", &RenderPathCommand::textureNames_)
//         .addProperty("depthStencilName", &RenderPathCommand::depthStencilName_)
//         .addProperty("clearFlags", &RenderPathCommand::clearFlags_)
//         .addProperty("clearColor", &RenderPathCommand::clearColor_)
//         .addProperty("clearDepth", &RenderPathCommand::clearDepth_)
//         .addProperty("clearStencil", &RenderPathCommand::clearStencil_)
//         .addProperty("blendMode", &RenderPathCommand::blendMode_)
//         .addProperty("enabled", &RenderPathCommand::enabled_)
//         .addProperty("useFogColor", &RenderPathCommand::useFogColor_)
//         .addProperty("markToStencil", &RenderPathCommand::markToStencil_)
//         .addProperty("useLitBase", &RenderPathCommand::useLitBase_)
//         .addProperty("vertexLights", &RenderPathCommand::vertexLights_)
//         .addProperty("eventName", &RenderPathCommand::eventName_)
//     );
//     lua["KRenderPath"].setClass(UserdataMetatable<RenderPath, RefCounted>()
//         .setConstructors<RenderPath()>()

//         .addFunction("Clone", &RenderPath::Clone)
//         .addFunction("Load", &RenderPath::Load)
//         .addFunction("Append", &RenderPath::Append)
//         .addFunction("SetEnabled", &RenderPath::SetEnabled)
//         .addFunction("ToggleEnabled", &RenderPath::ToggleEnabled)
//         .addFunction("SetRenderTarget", &RenderPath::SetRenderTarget)
//         .addFunction("AddRenderTarget", &RenderPath::AddRenderTarget)

//         .addOverloadedFunctions("RemoveRenderTarget",
//             static_cast<void(RenderPath::*)(unsigned int)>(&RenderPath::RemoveRenderTarget),
//             static_cast<void(RenderPath::*)(const String&)>(&RenderPath::RemoveRenderTarget))

//         .addFunction("RemoveRenderTargets", &RenderPath::RemoveRenderTargets)
//         .addFunction("SetCommand", &RenderPath::SetCommand)
//         .addFunction("AddCommand", &RenderPath::AddCommand)
//         .addFunction("InsertCommand", &RenderPath::InsertCommand)
//         .addFunction("RemoveCommand", &RenderPath::RemoveCommand)
//         .addFunction("RemoveCommands", &RenderPath::RemoveCommands)
//         .addFunction("SetShaderParameter", &RenderPath::SetShaderParameter)
//         .addFunction("GetNumRenderTargets", &RenderPath::GetNumRenderTargets)
//         .addFunction("GetNumCommands", &RenderPath::GetNumCommands)
//         .addFunction("GetCommand", &RenderPath::GetCommand)
//         .addFunction("GetShaderParameter", &RenderPath::GetShaderParameter)

//         .addProperty("numRenderTargets", &RenderPath::GetNumRenderTargets)
//         .addProperty("numCommands", &RenderPath::GetNumCommands)
//         .addProperty("renderTargets", &RenderPath::renderTargets_)
//         .addProperty("commands", &RenderPath::commands_)
//     );
// }

// static void RegisterRenderSurface(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KRenderSurface"].setClass(UserdataMetatable<RenderSurface, RefCounted>(false)
//         .setConstructors<RenderSurface(Texture*)>()
//         .addStaticFunction("__gc", &KReleaseObject<RenderSurface>)

//         .addFunction("SetNumViewports", &RenderSurface::SetNumViewports)
//         .addFunction("SetViewport", &RenderSurface::SetViewport)
//         .addFunction("SetUpdateMode", &RenderSurface::SetUpdateMode)
//         .addFunction("SetLinkedRenderTarget", &RenderSurface::SetLinkedRenderTarget)
//         .addFunction("SetLinkedDepthStencil", &RenderSurface::SetLinkedDepthStencil)
//         .addFunction("QueueUpdate", &RenderSurface::QueueUpdate)
//         .addFunction("CreateRenderBuffer", &RenderSurface::CreateRenderBuffer)
//         .addFunction("OnDeviceLost", &RenderSurface::OnDeviceLost)
//         .addFunction("Release", &RenderSurface::Release)
//         .addFunction("GetParentTexture", &RenderSurface::GetParentTexture)
//         .addFunction("GetRenderBuffer", &RenderSurface::GetRenderBuffer)
//         .addFunction("GetWidth", &RenderSurface::GetWidth)
//         .addFunction("GetHeight", &RenderSurface::GetHeight)
//         .addFunction("GetUsage", &RenderSurface::GetUsage)
//         .addFunction("GetNumViewports", &RenderSurface::GetNumViewports)
//         .addFunction("GetViewport", &RenderSurface::GetViewport)
//         .addFunction("GetUpdateMode", &RenderSurface::GetUpdateMode)
//         .addFunction("GetLinkedRenderTarget", &RenderSurface::GetLinkedRenderTarget)
//         .addFunction("GetLinkedDepthStencil", &RenderSurface::GetLinkedDepthStencil)
//         .addFunction("SetTarget", &RenderSurface::SetTarget)
//         .addFunction("GetTarget", &RenderSurface::GetTarget)
//         .addFunction("IsUpdateQueued", &RenderSurface::IsUpdateQueued)
//         .addFunction("ResetUpdateQueued", &RenderSurface::ResetUpdateQueued)

//         .addProperty("parentTexture", &RenderSurface::GetParentTexture)
//         .addProperty("renderBuffer", &RenderSurface::GetRenderBuffer)
//         .addProperty("width", &RenderSurface::GetWidth)
//         .addProperty("height", &RenderSurface::GetHeight)
//         .addProperty("usage", &RenderSurface::GetUsage)
//         .addProperty("numViewports", &RenderSurface::GetNumViewports, &RenderSurface::SetNumViewports)
//         .addProperty("updateMode", &RenderSurface::GetUpdateMode, &RenderSurface::SetUpdateMode)
//         .addProperty("linkedRenderTarget", &RenderSurface::GetLinkedRenderTarget, &RenderSurface::SetLinkedRenderTarget)
//         .addProperty("linkedDepthStencil", &RenderSurface::GetLinkedDepthStencil, &RenderSurface::SetLinkedDepthStencil)
//         .addProperty("target", &RenderSurface::GetTarget, &RenderSurface::SetTarget)
//         .addProperty("updateQueued", &RenderSurface::IsUpdateQueued)
//     );
// }

// static void RegisterRibbonTrail(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum TrailType;
//     lua["KTT_FACE_CAMERA"] = TT_FACE_CAMERA;
//     lua["KTT_BONE"] = TT_BONE;

//     lua["KTrailPoint"].setClass(UserdataMetatable<TrailPoint>()

//         .addProperty("position", &TrailPoint::position_)
//         .addProperty("forward", &TrailPoint::forward_)
//         .addProperty("parentPos", &TrailPoint::parentPos_)
//         .addProperty("elapsedLength", &TrailPoint::elapsedLength_)
//         .addProperty("next", &TrailPoint::next_)
//         .addProperty("lifetime", &TrailPoint::lifetime_)
//         .addProperty("sortDistance", &TrailPoint::sortDistance_)
//     );
//     lua["KRibbonTrail"].setClass(UserdataMetatable<RibbonTrail, Drawable>(false)
//         .addStaticFunction("new", &KCreateObject<RibbonTrail>)
//         .addStaticFunction("__gc", &KReleaseObject<RibbonTrail>)

//         .addFunction("GetType", &RibbonTrail::GetType)
//         .addFunction("GetTypeName", &RibbonTrail::GetTypeName)
//         .addFunction("GetTypeInfo", &RibbonTrail::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &RibbonTrail::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &RibbonTrail::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &RibbonTrail::GetTypeInfoStatic)
//         .addFunction("ProcessRayQuery", &RibbonTrail::ProcessRayQuery)
//         .addFunction("OnSetEnabled", &RibbonTrail::OnSetEnabled)
//         .addFunction("Update", &RibbonTrail::Update)
//         .addFunction("UpdateBatches", &RibbonTrail::UpdateBatches)
//         .addFunction("UpdateGeometry", &RibbonTrail::UpdateGeometry)
//         .addFunction("GetUpdateGeometryType", &RibbonTrail::GetUpdateGeometryType)
//         .addFunction("SetMaterial", &RibbonTrail::SetMaterial)
//         .addFunction("SetVertexDistance", &RibbonTrail::SetVertexDistance)
//         .addFunction("SetWidth", &RibbonTrail::SetWidth)
//         .addFunction("SetStartColor", &RibbonTrail::SetStartColor)
//         .addFunction("SetEndColor", &RibbonTrail::SetEndColor)
//         .addFunction("SetStartScale", &RibbonTrail::SetStartScale)
//         .addFunction("SetEndScale", &RibbonTrail::SetEndScale)
//         .addFunction("SetTrailType", &RibbonTrail::SetTrailType)
//         .addFunction("SetSorted", &RibbonTrail::SetSorted)
//         .addFunction("SetLifetime", &RibbonTrail::SetLifetime)
//         .addFunction("SetEmitting", &RibbonTrail::SetEmitting)
//         .addFunction("SetUpdateInvisible", &RibbonTrail::SetUpdateInvisible)
//         .addFunction("SetTailColumn", &RibbonTrail::SetTailColumn)
//         .addFunction("SetAnimationLodBias", &RibbonTrail::SetAnimationLodBias)
//         .addFunction("Commit", &RibbonTrail::Commit)
//         .addFunction("GetMaterial", &RibbonTrail::GetMaterial)
//         .addFunction("GetVertexDistance", &RibbonTrail::GetVertexDistance)
//         .addFunction("GetWidth", &RibbonTrail::GetWidth)
//         .addFunction("GetStartColor", &RibbonTrail::GetStartColor)
//         .addFunction("GetEndColor", &RibbonTrail::GetEndColor)
//         .addFunction("GetStartScale", &RibbonTrail::GetStartScale)
//         .addFunction("GetEndScale", &RibbonTrail::GetEndScale)
//         .addFunction("IsSorted", &RibbonTrail::IsSorted)
//         .addFunction("GetLifetime", &RibbonTrail::GetLifetime)
//         .addFunction("GetAnimationLodBias", &RibbonTrail::GetAnimationLodBias)
//         .addFunction("GetTrailType", &RibbonTrail::GetTrailType)
//         .addFunction("GetTailColumn", &RibbonTrail::GetTailColumn)
//         .addFunction("IsEmitting", &RibbonTrail::IsEmitting)
//         .addFunction("GetUpdateInvisible", &RibbonTrail::GetUpdateInvisible)

//         .addProperty("type", &RibbonTrail::GetType)
//         .addProperty("typeName", &RibbonTrail::GetTypeName)
//         .addProperty("typeInfo", &RibbonTrail::GetTypeInfo)
//         .addProperty("updateGeometryType", &RibbonTrail::GetUpdateGeometryType)
//         .addProperty("material", &RibbonTrail::GetMaterial, &RibbonTrail::SetMaterial)
//         .addProperty("vertexDistance", &RibbonTrail::GetVertexDistance, &RibbonTrail::SetVertexDistance)
//         .addProperty("width", &RibbonTrail::GetWidth, &RibbonTrail::SetWidth)
//         .addProperty("startColor", &RibbonTrail::GetStartColor, &RibbonTrail::SetStartColor)
//         .addProperty("endColor", &RibbonTrail::GetEndColor, &RibbonTrail::SetEndColor)
//         .addProperty("startScale", &RibbonTrail::GetStartScale, &RibbonTrail::SetStartScale)
//         .addProperty("endScale", &RibbonTrail::GetEndScale, &RibbonTrail::SetEndScale)
//         .addProperty("sorted", &RibbonTrail::IsSorted, &RibbonTrail::SetSorted)
//         .addProperty("lifetime", &RibbonTrail::GetLifetime, &RibbonTrail::SetLifetime)
//         .addProperty("animationLodBias", &RibbonTrail::GetAnimationLodBias, &RibbonTrail::SetAnimationLodBias)
//         .addProperty("trailType", &RibbonTrail::GetTrailType, &RibbonTrail::SetTrailType)
//         .addProperty("tailColumn", &RibbonTrail::GetTailColumn, &RibbonTrail::SetTailColumn)
//         .addProperty("emitting", &RibbonTrail::IsEmitting, &RibbonTrail::SetEmitting)
//         .addProperty("updateInvisible", &RibbonTrail::GetUpdateInvisible, &RibbonTrail::SetUpdateInvisible)
//     );
// }

// static void RegisterShader(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KShader"].setClass(UserdataMetatable<Shader, Resource>(false)
//         .addStaticFunction("new", &KCreateObject<Shader>)
//         .addStaticFunction("__gc", &KReleaseObject<Shader>)

//         .addFunction("GetType", &Shader::GetType)
//         .addFunction("GetTypeName", &Shader::GetTypeName)
//         .addFunction("GetTypeInfo", &Shader::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Shader::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Shader::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Shader::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &Shader::BeginLoad)
//         .addFunction("EndLoad", &Shader::EndLoad)
//         .addFunction("GetVariation", &Shader::GetVariation)
//         .addFunction("GetSourceCode", &Shader::GetSourceCode)
//         .addFunction("GetTimeStamp", &Shader::GetTimeStamp)

//         .addProperty("type", &Shader::GetType)
//         .addProperty("typeName", &Shader::GetTypeName)
//         .addProperty("typeInfo", &Shader::GetTypeInfo)
//         .addProperty("timeStamp", &Shader::GetTimeStamp)
//     );
// }

// static void RegisterShaderPrecache(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KShaderPrecache"].setClass(UserdataMetatable<ShaderPrecache, Object>(false)
//         .addStaticFunction("new", &KCreateObject<ShaderPrecache>)
//         .addStaticFunction("__gc", &KReleaseObject<ShaderPrecache>)

//         .addFunction("GetType", &ShaderPrecache::GetType)
//         .addFunction("GetTypeName", &ShaderPrecache::GetTypeName)
//         .addFunction("GetTypeInfo", &ShaderPrecache::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &ShaderPrecache::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &ShaderPrecache::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &ShaderPrecache::GetTypeInfoStatic)
//         .addFunction("StoreShaders", &ShaderPrecache::StoreShaders)
//         .addStaticFunction("LoadShaders", &ShaderPrecache::LoadShaders)

//         .addProperty("type", &ShaderPrecache::GetType)
//         .addProperty("typeName", &ShaderPrecache::GetTypeName)
//         .addProperty("typeInfo", &ShaderPrecache::GetTypeInfo)
//     );
// }

// static void RegisterShaderProgram(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KShaderParameter"].setClass(UserdataMetatable<ShaderParameter>()
//         .setConstructors<ShaderParameter()>()

//         .addProperty("location", &ShaderParameter::location_)
//         .addProperty("type", &ShaderParameter::type_)
//         .addProperty("bufferPtr", &ShaderParameter::bufferPtr_)
//     );
//     lua["KShaderProgram"].setClass(UserdataMetatable<ShaderProgram, RefCounted, GPUObject>()
//         .setConstructors<ShaderProgram(Graphics*, ShaderVariation*, ShaderVariation*)>()

//         .addFunction("OnDeviceLost", &ShaderProgram::OnDeviceLost)
//         .addFunction("Release", &ShaderProgram::Release)
//         .addFunction("Link", &ShaderProgram::Link)
//         .addFunction("GetVertexShader", &ShaderProgram::GetVertexShader)
//         .addFunction("GetPixelShader", &ShaderProgram::GetPixelShader)
//         .addFunction("HasParameter", &ShaderProgram::HasParameter)
//         .addFunction("HasTextureUnit", &ShaderProgram::HasTextureUnit)
//         .addFunction("GetParameter", &ShaderProgram::GetParameter)
//         .addFunction("GetLinkerOutput", &ShaderProgram::GetLinkerOutput)
//         .addFunction("GetVertexAttributes", &ShaderProgram::GetVertexAttributes)
//         .addFunction("GetUsedVertexAttributes", &ShaderProgram::GetUsedVertexAttributes)
//         .addFunction("GetConstantBuffers", &ShaderProgram::GetConstantBuffers)
//         .addFunction("NeedParameterUpdate", &ShaderProgram::NeedParameterUpdate)
//         .addFunction("ClearParameterSource", &ShaderProgram::ClearParameterSource)
//         .addStaticFunction("ClearParameterSources", &ShaderProgram::ClearParameterSources)
//         .addStaticFunction("ClearGlobalParameterSource", &ShaderProgram::ClearGlobalParameterSource)

//         .addProperty("vertexShader", &ShaderProgram::GetVertexShader)
//         .addProperty("pixelShader", &ShaderProgram::GetPixelShader)
//         .addProperty("linkerOutput", &ShaderProgram::GetLinkerOutput)
//         .addProperty("vertexAttributes", &ShaderProgram::GetVertexAttributes)
//         .addProperty("usedVertexAttributes", &ShaderProgram::GetUsedVertexAttributes)
//         .addProperty("constantBuffers", &ShaderProgram::GetConstantBuffers)
//     );
// }

// static void RegisterShaderVariation(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KShaderVariation"].setClass(UserdataMetatable<ShaderVariation, RefCounted, GPUObject>()
//         .setConstructors<ShaderVariation(Shader*, ShaderType)>()

//         .addFunction("OnDeviceLost", &ShaderVariation::OnDeviceLost)
//         .addFunction("Release", &ShaderVariation::Release)
//         .addFunction("Create", &ShaderVariation::Create)
//         .addFunction("SetName", &ShaderVariation::SetName)
//         .addFunction("SetDefines", &ShaderVariation::SetDefines)
//         .addFunction("GetOwner", &ShaderVariation::GetOwner)
//         .addFunction("GetShaderType", &ShaderVariation::GetShaderType)
//         .addFunction("GetName", &ShaderVariation::GetName)
//         .addFunction("GetDefines", &ShaderVariation::GetDefines)
//         .addFunction("GetFullName", &ShaderVariation::GetFullName)
//         .addFunction("GetCompilerOutput", &ShaderVariation::GetCompilerOutput)

//         .addProperty("owner", &ShaderVariation::GetOwner)
//         .addProperty("shaderType", &ShaderVariation::GetShaderType)
//         .addProperty("name", &ShaderVariation::GetName, &ShaderVariation::SetName)
//         .addProperty("defines", &ShaderVariation::GetDefines, &ShaderVariation::SetDefines)
//         .addProperty("fullName", &ShaderVariation::GetFullName)
//         .addProperty("compilerOutput", &ShaderVariation::GetCompilerOutput)
//     );
// }

// static void RegisterSkeleton(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KBONECOLLISION_NONE"] = BONECOLLISION_NONE;
//     lua["KBONECOLLISION_SPHERE"] = BONECOLLISION_SPHERE;
//     lua["KBONECOLLISION_BOX"] = BONECOLLISION_BOX;
//     lua["KBone"].setClass(UserdataMetatable<Bone>()
//         .setConstructors<Bone()>()

//         .addProperty("name", &Bone::name_)
//         .addProperty("nameHash", &Bone::nameHash_)
//         .addProperty("parentIndex", &Bone::parentIndex_)
//         .addProperty("initialPosition", &Bone::initialPosition_)
//         .addProperty("initialRotation", &Bone::initialRotation_)
//         .addProperty("initialScale", &Bone::initialScale_)
//         .addProperty("offsetMatrix", &Bone::offsetMatrix_)
//         .addProperty("animated", &Bone::animated_)
//         .addProperty("collisionMask", &Bone::collisionMask_)
//         .addProperty("radius", &Bone::radius_)
//         .addProperty("boundingBox", &Bone::boundingBox_)
//         .addProperty("node", &Bone::node_)
//     );
//     lua["KSkeleton"].setClass(UserdataMetatable<Skeleton>()
//         .setConstructors<Skeleton()>()

//         .addFunction("Load", &Skeleton::Load)
//         .addFunction("Save", &Skeleton::Save)
//         .addFunction("Define", &Skeleton::Define)
//         .addFunction("SetRootBoneIndex", &Skeleton::SetRootBoneIndex)
//         .addFunction("ClearBones", &Skeleton::ClearBones)
//         .addFunction("Reset", &Skeleton::Reset)
//         .addFunction("GetBones", &Skeleton::GetBones)
//         .addFunction("GetModifiableBones", &Skeleton::GetModifiableBones)
//         .addFunction("GetNumBones", &Skeleton::GetNumBones)
//         .addFunction("GetRootBone", &Skeleton::GetRootBone)

//         .addOverloadedFunctions("GetBone",
//             static_cast<Bone*(Skeleton::*)(unsigned int)>(&Skeleton::GetBone),
//             static_cast<Bone*(Skeleton::*)(const String&)>(&Skeleton::GetBone),
//             static_cast<Bone*(Skeleton::*)(const char*)>(&Skeleton::GetBone),
//             static_cast<Bone*(Skeleton::*)(StringHash)>(&Skeleton::GetBone))

//         .addFunction("ResetSilent", &Skeleton::ResetSilent)

//         .addProperty("bones", &Skeleton::GetBones)
//         .addProperty("modifiableBones", &Skeleton::GetModifiableBones)
//         .addProperty("numBones", &Skeleton::GetNumBones)
//         .addProperty("rootBone", &Skeleton::GetRootBone)
//         .addProperty("rootBoneIndex", &Skeleton::SetRootBoneIndex)
//     );
// }

// static void RegisterSkybox(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KSkybox"].setClass(UserdataMetatable<Skybox, StaticModel>(false)
//         .addStaticFunction("new", &KCreateObject<Skybox>)
//         .addStaticFunction("__gc", &KReleaseObject<Skybox>)

//         .addFunction("GetType", &Skybox::GetType)
//         .addFunction("GetTypeName", &Skybox::GetTypeName)
//         .addFunction("GetTypeInfo", &Skybox::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Skybox::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Skybox::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Skybox::GetTypeInfoStatic)
//         .addFunction("ProcessRayQuery", &Skybox::ProcessRayQuery)
//         .addFunction("UpdateBatches", &Skybox::UpdateBatches)

//         .addProperty("type", &Skybox::GetType)
//         .addProperty("typeName", &Skybox::GetTypeName)
//         .addProperty("typeInfo", &Skybox::GetTypeInfo)
//     );
// }

// static void RegisterStaticModel(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KStaticModelGeometryData"].setClass(UserdataMetatable<StaticModelGeometryData>()

//         .addProperty("center", &StaticModelGeometryData::center_)
//         .addProperty("lodLevel", &StaticModelGeometryData::lodLevel_)
//     );
//     lua["KStaticModel"].setClass(UserdataMetatable<StaticModel, Drawable>(false)
//         .addStaticFunction("new", &KCreateObject<StaticModel>)
//         .addStaticFunction("__gc", &KReleaseObject<StaticModel>)

//         .addFunction("GetType", &StaticModel::GetType)
//         .addFunction("GetTypeName", &StaticModel::GetTypeName)
//         .addFunction("GetTypeInfo", &StaticModel::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &StaticModel::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &StaticModel::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &StaticModel::GetTypeInfoStatic)
//         .addFunction("ProcessRayQuery", &StaticModel::ProcessRayQuery)
//         .addFunction("UpdateBatches", &StaticModel::UpdateBatches)
//         .addFunction("GetLodGeometry", &StaticModel::GetLodGeometry)
//         .addFunction("GetNumOccluderTriangles", &StaticModel::GetNumOccluderTriangles)
//         .addFunction("DrawOcclusion", &StaticModel::DrawOcclusion)
//         .addFunction("SetModel", &StaticModel::SetModel)

//         .addOverloadedFunctions("SetMaterial",
//             static_cast<void(StaticModel::*)(Material*)>(&StaticModel::SetMaterial),
//             static_cast<bool(StaticModel::*)(unsigned int, Material*)>(&StaticModel::SetMaterial))

//         .addFunction("SetOcclusionLodLevel", &StaticModel::SetOcclusionLodLevel)
//         .addFunction("ApplyMaterialList", &StaticModel::ApplyMaterialList)
//         .addFunction("GetModel", &StaticModel::GetModel)
//         .addFunction("GetNumGeometries", &StaticModel::GetNumGeometries)
//         .addFunction("GetMaterial", &StaticModel::GetMaterial)
//         .addFunction("GetOcclusionLodLevel", &StaticModel::GetOcclusionLodLevel)
//         .addFunction("IsInside", &StaticModel::IsInside)
//         .addFunction("IsInsideLocal", &StaticModel::IsInsideLocal)

//         .addProperty("type", &StaticModel::GetType)
//         .addProperty("typeName", &StaticModel::GetTypeName)
//         .addProperty("typeInfo", &StaticModel::GetTypeInfo)
//         .addProperty("numOccluderTriangles", &StaticModel::GetNumOccluderTriangles)
//         .addProperty("model", &StaticModel::GetModel, &StaticModel::SetModel)
//         .addProperty("numGeometries", &StaticModel::GetNumGeometries)
//         .addProperty("occlusionLodLevel", &StaticModel::GetOcclusionLodLevel, &StaticModel::SetOcclusionLodLevel)
//     );
// }

// static void RegisterStaticModelGroup(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KStaticModelGroup"].setClass(UserdataMetatable<StaticModelGroup, StaticModel>(false)
//         .addStaticFunction("new", &KCreateObject<StaticModelGroup>)
//         .addStaticFunction("__gc", &KReleaseObject<StaticModelGroup>)

//         .addFunction("GetType", &StaticModelGroup::GetType)
//         .addFunction("GetTypeName", &StaticModelGroup::GetTypeName)
//         .addFunction("GetTypeInfo", &StaticModelGroup::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &StaticModelGroup::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &StaticModelGroup::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &StaticModelGroup::GetTypeInfoStatic)
//         .addFunction("ApplyAttributes", &StaticModelGroup::ApplyAttributes)
//         .addFunction("ProcessRayQuery", &StaticModelGroup::ProcessRayQuery)
//         .addFunction("UpdateBatches", &StaticModelGroup::UpdateBatches)
//         .addFunction("GetNumOccluderTriangles", &StaticModelGroup::GetNumOccluderTriangles)
//         .addFunction("DrawOcclusion", &StaticModelGroup::DrawOcclusion)
//         .addFunction("AddInstanceNode", &StaticModelGroup::AddInstanceNode)
//         .addFunction("RemoveInstanceNode", &StaticModelGroup::RemoveInstanceNode)
//         .addFunction("RemoveAllInstanceNodes", &StaticModelGroup::RemoveAllInstanceNodes)
//         .addFunction("GetNumInstanceNodes", &StaticModelGroup::GetNumInstanceNodes)
//         .addFunction("GetInstanceNode", &StaticModelGroup::GetInstanceNode)

//         .addProperty("type", &StaticModelGroup::GetType)
//         .addProperty("typeName", &StaticModelGroup::GetTypeName)
//         .addProperty("typeInfo", &StaticModelGroup::GetTypeInfo)
//         .addProperty("numOccluderTriangles", &StaticModelGroup::GetNumOccluderTriangles)
//         .addProperty("numInstanceNodes", &StaticModelGroup::GetNumInstanceNodes)
//     );
// }

// static void RegisterTangent(kaguya::State& lua)
// {
//     using namespace kaguya;

// }

// static void RegisterTechnique(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum PassLightingMode;
//     lua["KLIGHTING_UNLIT"] = LIGHTING_UNLIT;
//     lua["KLIGHTING_PERVERTEX"] = LIGHTING_PERVERTEX;
//     lua["KLIGHTING_PERPIXEL"] = LIGHTING_PERPIXEL;

//     lua["KPass"].setClass(UserdataMetatable<Pass, RefCounted>(false)
//         .setConstructors<Pass(const String&)>()
//         .addStaticFunction("__gc", &KReleaseObject<Pass>)

//         .addFunction("SetBlendMode", &Pass::SetBlendMode)
//         .addFunction("SetCullMode", &Pass::SetCullMode)
//         .addFunction("SetDepthTestMode", &Pass::SetDepthTestMode)
//         .addFunction("SetLightingMode", &Pass::SetLightingMode)
//         .addFunction("SetDepthWrite", &Pass::SetDepthWrite)
//         .addFunction("SetAlphaMask", &Pass::SetAlphaMask)
//         .addFunction("SetIsDesktop", &Pass::SetIsDesktop)
//         .addFunction("SetVertexShader", &Pass::SetVertexShader)
//         .addFunction("SetPixelShader", &Pass::SetPixelShader)
//         .addFunction("SetVertexShaderDefines", &Pass::SetVertexShaderDefines)
//         .addFunction("SetPixelShaderDefines", &Pass::SetPixelShaderDefines)
//         .addFunction("ReleaseShaders", &Pass::ReleaseShaders)
//         .addFunction("MarkShadersLoaded", &Pass::MarkShadersLoaded)
//         .addFunction("GetName", &Pass::GetName)
//         .addFunction("GetIndex", &Pass::GetIndex)
//         .addFunction("GetBlendMode", &Pass::GetBlendMode)
//         .addFunction("GetCullMode", &Pass::GetCullMode)
//         .addFunction("GetDepthTestMode", &Pass::GetDepthTestMode)
//         .addFunction("GetLightingMode", &Pass::GetLightingMode)
//         .addFunction("GetShadersLoadedFrameNumber", &Pass::GetShadersLoadedFrameNumber)
//         .addFunction("GetDepthWrite", &Pass::GetDepthWrite)
//         .addFunction("GetAlphaMask", &Pass::GetAlphaMask)
//         .addFunction("IsDesktop", &Pass::IsDesktop)
//         .addFunction("GetVertexShader", &Pass::GetVertexShader)
//         .addFunction("GetPixelShader", &Pass::GetPixelShader)
//         .addFunction("GetVertexShaderDefines", &Pass::GetVertexShaderDefines)
//         .addFunction("GetPixelShaderDefines", &Pass::GetPixelShaderDefines)
//         .addFunction("GetVertexShaders", &Pass::GetVertexShaders)
//         .addFunction("GetPixelShaders", &Pass::GetPixelShaders)

//         .addProperty("name", &Pass::GetName)
//         .addProperty("index", &Pass::GetIndex)
//         .addProperty("blendMode", &Pass::GetBlendMode, &Pass::SetBlendMode)
//         .addProperty("cullMode", &Pass::GetCullMode, &Pass::SetCullMode)
//         .addProperty("depthTestMode", &Pass::GetDepthTestMode, &Pass::SetDepthTestMode)
//         .addProperty("lightingMode", &Pass::GetLightingMode, &Pass::SetLightingMode)
//         .addProperty("shadersLoadedFrameNumber", &Pass::GetShadersLoadedFrameNumber)
//         .addProperty("depthWrite", &Pass::GetDepthWrite, &Pass::SetDepthWrite)
//         .addProperty("alphaMask", &Pass::GetAlphaMask, &Pass::SetAlphaMask)
//         .addProperty("desktop", &Pass::IsDesktop)
//         .addProperty("vertexShader", &Pass::GetVertexShader, &Pass::SetVertexShader)
//         .addProperty("pixelShader", &Pass::GetPixelShader, &Pass::SetPixelShader)
//         .addProperty("vertexShaderDefines", &Pass::GetVertexShaderDefines, &Pass::SetVertexShaderDefines)
//         .addProperty("pixelShaderDefines", &Pass::GetPixelShaderDefines, &Pass::SetPixelShaderDefines)
//         .addProperty("vertexShaders", &Pass::GetVertexShaders)
//         .addProperty("pixelShaders", &Pass::GetPixelShaders)
//         .addProperty("isDesktop", &Pass::SetIsDesktop)
//     );
//     lua["KTechnique"].setClass(UserdataMetatable<Technique, Resource>(false)
//         .addStaticFunction("new", &KCreateObject<Technique>)
//         .addStaticFunction("__gc", &KReleaseObject<Technique>)

//         .addFunction("GetType", &Technique::GetType)
//         .addFunction("GetTypeName", &Technique::GetTypeName)
//         .addFunction("GetTypeInfo", &Technique::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Technique::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Technique::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Technique::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &Technique::BeginLoad)
//         .addFunction("SetIsDesktop", &Technique::SetIsDesktop)
//         .addFunction("CreatePass", &Technique::CreatePass)
//         .addFunction("RemovePass", &Technique::RemovePass)
//         .addFunction("ReleaseShaders", &Technique::ReleaseShaders)
//         .addFunction("Clone", &Technique::Clone)
//         .addFunction("IsDesktop", &Technique::IsDesktop)
//         .addFunction("IsSupported", &Technique::IsSupported)

//         .addOverloadedFunctions("HasPass",
//             static_cast<bool(Technique::*)(unsigned int) const>(&Technique::HasPass),
//             static_cast<bool(Technique::*)(const String&) const>(&Technique::HasPass))


//         .addOverloadedFunctions("GetPass",
//             static_cast<Pass*(Technique::*)(unsigned int) const>(&Technique::GetPass),
//             static_cast<Pass*(Technique::*)(const String&) const>(&Technique::GetPass))


//         .addOverloadedFunctions("GetSupportedPass",
//             static_cast<Pass*(Technique::*)(unsigned int) const>(&Technique::GetSupportedPass),
//             static_cast<Pass*(Technique::*)(const String&) const>(&Technique::GetSupportedPass))

//         .addFunction("GetNumPasses", &Technique::GetNumPasses)
//         .addFunction("GetPassNames", &Technique::GetPassNames)
//         .addFunction("GetPasses", &Technique::GetPasses)
//         .addStaticFunction("GetPassIndex", &Technique::GetPassIndex)

//         .addProperty("type", &Technique::GetType)
//         .addProperty("typeName", &Technique::GetTypeName)
//         .addProperty("typeInfo", &Technique::GetTypeInfo)
//         .addProperty("desktop", &Technique::IsDesktop)
//         .addProperty("supported", &Technique::IsSupported)
//         .addProperty("numPasses", &Technique::GetNumPasses)
//         .addProperty("passNames", &Technique::GetPassNames)
//         .addProperty("passes", &Technique::GetPasses)
//         .addProperty("isDesktop", &Technique::SetIsDesktop)
//         .addStaticField("basePassIndex", &Technique::basePassIndex)
//         .addStaticField("alphaPassIndex", &Technique::alphaPassIndex)
//         .addStaticField("materialPassIndex", &Technique::materialPassIndex)
//         .addStaticField("deferredPassIndex", &Technique::deferredPassIndex)
//         .addStaticField("lightPassIndex", &Technique::lightPassIndex)
//         .addStaticField("litBasePassIndex", &Technique::litBasePassIndex)
//         .addStaticField("litAlphaPassIndex", &Technique::litAlphaPassIndex)
//         .addStaticField("shadowPassIndex", &Technique::shadowPassIndex)
//     );
// }

// static void RegisterTerrain(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KTerrain"].setClass(UserdataMetatable<Terrain, Component>(false)
//         .addStaticFunction("new", &KCreateObject<Terrain>)
//         .addStaticFunction("__gc", &KReleaseObject<Terrain>)

//         .addFunction("GetType", &Terrain::GetType)
//         .addFunction("GetTypeName", &Terrain::GetTypeName)
//         .addFunction("GetTypeInfo", &Terrain::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Terrain::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Terrain::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Terrain::GetTypeInfoStatic)
//         .addFunction("OnSetAttribute", &Terrain::OnSetAttribute)
//         .addFunction("ApplyAttributes", &Terrain::ApplyAttributes)
//         .addFunction("OnSetEnabled", &Terrain::OnSetEnabled)
//         .addFunction("SetPatchSize", &Terrain::SetPatchSize)
//         .addFunction("SetSpacing", &Terrain::SetSpacing)
//         .addFunction("SetMaxLodLevels", &Terrain::SetMaxLodLevels)
//         .addFunction("SetOcclusionLodLevel", &Terrain::SetOcclusionLodLevel)
//         .addFunction("SetSmoothing", &Terrain::SetSmoothing)
//         .addFunction("SetHeightMap", &Terrain::SetHeightMap)
//         .addFunction("SetMaterial", &Terrain::SetMaterial)
//         .addFunction("SetDrawDistance", &Terrain::SetDrawDistance)
//         .addFunction("SetShadowDistance", &Terrain::SetShadowDistance)
//         .addFunction("SetLodBias", &Terrain::SetLodBias)
//         .addFunction("SetViewMask", &Terrain::SetViewMask)
//         .addFunction("SetLightMask", &Terrain::SetLightMask)
//         .addFunction("SetShadowMask", &Terrain::SetShadowMask)
//         .addFunction("SetZoneMask", &Terrain::SetZoneMask)
//         .addFunction("SetMaxLights", &Terrain::SetMaxLights)
//         .addFunction("SetCastShadows", &Terrain::SetCastShadows)
//         .addFunction("SetOccluder", &Terrain::SetOccluder)
//         .addFunction("SetOccludee", &Terrain::SetOccludee)
//         .addFunction("ApplyHeightMap", &Terrain::ApplyHeightMap)
//         .addFunction("GetPatchSize", &Terrain::GetPatchSize)
//         .addFunction("GetSpacing", &Terrain::GetSpacing)
//         .addFunction("GetNumVertices", &Terrain::GetNumVertices)
//         .addFunction("GetNumPatches", &Terrain::GetNumPatches)
//         .addFunction("GetMaxLodLevels", &Terrain::GetMaxLodLevels)
//         .addFunction("GetOcclusionLodLevel", &Terrain::GetOcclusionLodLevel)
//         .addFunction("GetSmoothing", &Terrain::GetSmoothing)
//         .addFunction("GetHeightMap", &Terrain::GetHeightMap)
//         .addFunction("GetMaterial", &Terrain::GetMaterial)

//         .addOverloadedFunctions("GetPatch",
//             static_cast<TerrainPatch*(Terrain::*)(unsigned int) const>(&Terrain::GetPatch),
//             static_cast<TerrainPatch*(Terrain::*)(int, int) const>(&Terrain::GetPatch))

//         .addFunction("GetHeight", &Terrain::GetHeight)
//         .addFunction("GetNormal", &Terrain::GetNormal)
//         .addFunction("WorldToHeightMap", &Terrain::WorldToHeightMap)
//         .addFunction("UpdatePatchLod", &Terrain::UpdatePatchLod)

//         .addProperty("type", &Terrain::GetType)
//         .addProperty("typeName", &Terrain::GetTypeName)
//         .addProperty("typeInfo", &Terrain::GetTypeInfo)
//         .addProperty("patchSize", &Terrain::GetPatchSize, &Terrain::SetPatchSize)
//         .addProperty("spacing", &Terrain::GetSpacing, &Terrain::SetSpacing)
//         .addProperty("numVertices", &Terrain::GetNumVertices)
//         .addProperty("numPatches", &Terrain::GetNumPatches)
//         .addProperty("maxLodLevels", &Terrain::GetMaxLodLevels, &Terrain::SetMaxLodLevels)
//         .addProperty("occlusionLodLevel", &Terrain::GetOcclusionLodLevel, &Terrain::SetOcclusionLodLevel)
//         .addProperty("smoothing", &Terrain::GetSmoothing, &Terrain::SetSmoothing)
//         .addProperty("heightMap", &Terrain::GetHeightMap, &Terrain::SetHeightMap)
//         .addProperty("material", &Terrain::GetMaterial, &Terrain::SetMaterial)
//         .addProperty("drawDistance", &Terrain::SetDrawDistance)
//         .addProperty("shadowDistance", &Terrain::SetShadowDistance)
//         .addProperty("lodBias", &Terrain::SetLodBias)
//         .addProperty("viewMask", &Terrain::SetViewMask)
//         .addProperty("lightMask", &Terrain::SetLightMask)
//         .addProperty("shadowMask", &Terrain::SetShadowMask)
//         .addProperty("zoneMask", &Terrain::SetZoneMask)
//         .addProperty("maxLights", &Terrain::SetMaxLights)
//         .addProperty("castShadows", &Terrain::SetCastShadows)
//         .addProperty("occluder", &Terrain::SetOccluder)
//         .addProperty("occludee", &Terrain::SetOccludee)
//     );
// }

// static void RegisterTerrainPatch(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KTerrainPatch"].setClass(UserdataMetatable<TerrainPatch, Drawable>(false)
//         .addStaticFunction("new", &KCreateObject<TerrainPatch>)
//         .addStaticFunction("__gc", &KReleaseObject<TerrainPatch>)

//         .addFunction("GetType", &TerrainPatch::GetType)
//         .addFunction("GetTypeName", &TerrainPatch::GetTypeName)
//         .addFunction("GetTypeInfo", &TerrainPatch::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &TerrainPatch::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &TerrainPatch::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &TerrainPatch::GetTypeInfoStatic)
//         .addFunction("ProcessRayQuery", &TerrainPatch::ProcessRayQuery)
//         .addFunction("UpdateBatches", &TerrainPatch::UpdateBatches)
//         .addFunction("UpdateGeometry", &TerrainPatch::UpdateGeometry)
//         .addFunction("GetUpdateGeometryType", &TerrainPatch::GetUpdateGeometryType)
//         .addFunction("GetLodGeometry", &TerrainPatch::GetLodGeometry)
//         .addFunction("GetNumOccluderTriangles", &TerrainPatch::GetNumOccluderTriangles)
//         .addFunction("DrawOcclusion", &TerrainPatch::DrawOcclusion)
//         .addFunction("DrawDebugGeometry", &TerrainPatch::DrawDebugGeometry)
//         .addFunction("SetOwner", &TerrainPatch::SetOwner)
//         .addFunction("SetNeighbors", &TerrainPatch::SetNeighbors)
//         .addFunction("SetMaterial", &TerrainPatch::SetMaterial)
//         .addFunction("SetBoundingBox", &TerrainPatch::SetBoundingBox)
//         .addFunction("SetCoordinates", &TerrainPatch::SetCoordinates)
//         .addFunction("ResetLod", &TerrainPatch::ResetLod)
//         .addFunction("GetGeometry", &TerrainPatch::GetGeometry)
//         .addFunction("GetMaxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
//         .addFunction("GetOcclusionGeometry", &TerrainPatch::GetOcclusionGeometry)
//         .addFunction("GetVertexBuffer", &TerrainPatch::GetVertexBuffer)
//         .addFunction("GetOwner", &TerrainPatch::GetOwner)
//         .addFunction("GetNorthPatch", &TerrainPatch::GetNorthPatch)
//         .addFunction("GetSouthPatch", &TerrainPatch::GetSouthPatch)
//         .addFunction("GetWestPatch", &TerrainPatch::GetWestPatch)
//         .addFunction("GetEastPatch", &TerrainPatch::GetEastPatch)
//         .addFunction("GetLodErrors", &TerrainPatch::GetLodErrors)
//         .addFunction("GetCoordinates", &TerrainPatch::GetCoordinates)
//         .addFunction("GetLodLevel", &TerrainPatch::GetLodLevel)

//         .addProperty("type", &TerrainPatch::GetType)
//         .addProperty("typeName", &TerrainPatch::GetTypeName)
//         .addProperty("typeInfo", &TerrainPatch::GetTypeInfo)
//         .addProperty("updateGeometryType", &TerrainPatch::GetUpdateGeometryType)
//         .addProperty("numOccluderTriangles", &TerrainPatch::GetNumOccluderTriangles)
//         .addProperty("geometry", &TerrainPatch::GetGeometry)
//         .addProperty("maxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
//         .addProperty("occlusionGeometry", &TerrainPatch::GetOcclusionGeometry)
//         .addProperty("vertexBuffer", &TerrainPatch::GetVertexBuffer)
//         .addProperty("owner", &TerrainPatch::GetOwner, &TerrainPatch::SetOwner)
//         .addProperty("northPatch", &TerrainPatch::GetNorthPatch)
//         .addProperty("southPatch", &TerrainPatch::GetSouthPatch)
//         .addProperty("westPatch", &TerrainPatch::GetWestPatch)
//         .addProperty("eastPatch", &TerrainPatch::GetEastPatch)
//         .addProperty("lodErrors", &TerrainPatch::GetLodErrors)
//         .addProperty("coordinates", &TerrainPatch::GetCoordinates, &TerrainPatch::SetCoordinates)
//         .addProperty("lodLevel", &TerrainPatch::GetLodLevel)
//         .addProperty("material", &TerrainPatch::SetMaterial)
//         .addProperty("boundingBox", &TerrainPatch::SetBoundingBox)
//     );
// }

// static void RegisterTexture(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KMAX_TEXTURE_QUALITY_LEVELS"] = MAX_TEXTURE_QUALITY_LEVELS;
//     lua["KTexture"].setClass(UserdataMetatable<Texture, Resource, GPUObject>(false)
//         .addStaticFunction("new", &KCreateObject<Texture>)
//         .addStaticFunction("__gc", &KReleaseObject<Texture>)

//         .addFunction("SetNumLevels", &Texture::SetNumLevels)
//         .addFunction("SetFilterMode", &Texture::SetFilterMode)
//         .addFunction("SetAddressMode", &Texture::SetAddressMode)
//         .addFunction("SetShadowCompare", &Texture::SetShadowCompare)
//         .addFunction("SetBorderColor", &Texture::SetBorderColor)
//         .addFunction("SetSRGB", &Texture::SetSRGB)
//         .addFunction("SetBackupTexture", &Texture::SetBackupTexture)
//         .addFunction("SetMipsToSkip", &Texture::SetMipsToSkip)
//         .addFunction("SetParametersDirty", &Texture::SetParametersDirty)
//         .addFunction("UpdateParameters", &Texture::UpdateParameters)
//         .addFunction("GetTarget", &Texture::GetTarget)
//         .addFunction("GetFormat", &Texture::GetFormat)
//         .addFunction("IsCompressed", &Texture::IsCompressed)
//         .addFunction("GetLevels", &Texture::GetLevels)
//         .addFunction("GetWidth", &Texture::GetWidth)
//         .addFunction("GetHeight", &Texture::GetHeight)
//         .addFunction("GetDepth", &Texture::GetDepth)
//         .addFunction("GetParametersDirty", &Texture::GetParametersDirty)
//         .addFunction("GetFilterMode", &Texture::GetFilterMode)
//         .addFunction("GetAddressMode", &Texture::GetAddressMode)
//         .addFunction("GetShadowCompare", &Texture::GetShadowCompare)
//         .addFunction("GetBorderColor", &Texture::GetBorderColor)
//         .addFunction("GetSRGB", &Texture::GetSRGB)
//         .addFunction("GetBackupTexture", &Texture::GetBackupTexture)
//         .addFunction("GetMipsToSkip", &Texture::GetMipsToSkip)
//         .addFunction("GetLevelWidth", &Texture::GetLevelWidth)
//         .addFunction("GetLevelHeight", &Texture::GetLevelHeight)
//         .addFunction("GetLevelDepth", &Texture::GetLevelDepth)
//         .addFunction("GetUsage", &Texture::GetUsage)

//         .addOverloadedFunctions("GetDataSize",
//             static_cast<unsigned int(Texture::*)(int, int) const>(&Texture::GetDataSize),
//             static_cast<unsigned int(Texture::*)(int, int, int) const>(&Texture::GetDataSize))

//         .addFunction("GetRowDataSize", &Texture::GetRowDataSize)
//         .addFunction("GetComponents", &Texture::GetComponents)
//         .addStaticFunction("GetExternalFormat", &Texture::GetExternalFormat)
//         .addStaticFunction("GetDataType", &Texture::GetDataType)

//         .addOverloadedFunctions("SetParameters",
//             static_cast<void(Texture::*)(XMLFile*)>(&Texture::SetParameters),
//             static_cast<void(Texture::*)(const XMLElement&)>(&Texture::SetParameters))

//         .addFunction("GetSRGBFormat", &Texture::GetSRGBFormat)

//         .addProperty("target", &Texture::GetTarget)
//         .addProperty("format", &Texture::GetFormat)
//         .addProperty("compressed", &Texture::IsCompressed)
//         .addProperty("levels", &Texture::GetLevels)
//         .addProperty("width", &Texture::GetWidth)
//         .addProperty("height", &Texture::GetHeight)
//         .addProperty("depth", &Texture::GetDepth)
//         .addProperty("parametersDirty", &Texture::GetParametersDirty)
//         .addProperty("filterMode", &Texture::GetFilterMode, &Texture::SetFilterMode)
//         .addProperty("shadowCompare", &Texture::GetShadowCompare, &Texture::SetShadowCompare)
//         .addProperty("borderColor", &Texture::GetBorderColor, &Texture::SetBorderColor)
//         .addProperty("sRGB", &Texture::GetSRGB, &Texture::SetSRGB)
//         .addProperty("backupTexture", &Texture::GetBackupTexture, &Texture::SetBackupTexture)
//         .addProperty("usage", &Texture::GetUsage)
//         .addProperty("components", &Texture::GetComponents)
//         .addProperty("numLevels", &Texture::SetNumLevels)
//     );
// }

// static void RegisterTexture2D(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KTexture2D"].setClass(UserdataMetatable<Texture2D, Texture>(false)
//         .addStaticFunction("new", &KCreateObject<Texture2D>)
//         .addStaticFunction("__gc", &KReleaseObject<Texture2D>)

//         .addFunction("GetType", &Texture2D::GetType)
//         .addFunction("GetTypeName", &Texture2D::GetTypeName)
//         .addFunction("GetTypeInfo", &Texture2D::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Texture2D::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Texture2D::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Texture2D::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &Texture2D::BeginLoad)
//         .addFunction("EndLoad", &Texture2D::EndLoad)
//         .addFunction("OnDeviceLost", &Texture2D::OnDeviceLost)
//         .addFunction("OnDeviceReset", &Texture2D::OnDeviceReset)
//         .addFunction("Release", &Texture2D::Release)
//         .addFunction("SetSize", &Texture2D::SetSize)

//         .addOverloadedFunctions("SetData",
//             static_cast<bool(Texture2D::*)(unsigned int, int, int, int, int, const void*)>(&Texture2D::SetData),
//             static_cast<bool(Texture2D::*)(Image*, bool)>(&Texture2D::SetData))

//         .addFunction("GetData", &Texture2D::GetData)
//         .addFunction("GetRenderSurface", &Texture2D::GetRenderSurface)

//         .addProperty("type", &Texture2D::GetType)
//         .addProperty("typeName", &Texture2D::GetTypeName)
//         .addProperty("typeInfo", &Texture2D::GetTypeInfo)
//         .addProperty("renderSurface", &Texture2D::GetRenderSurface)
//     );
// }

// static void RegisterTexture2DArray(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KTexture2DArray"].setClass(UserdataMetatable<Texture2DArray, Texture>(false)
//         .addStaticFunction("new", &KCreateObject<Texture2DArray>)
//         .addStaticFunction("__gc", &KReleaseObject<Texture2DArray>)

//         .addFunction("GetType", &Texture2DArray::GetType)
//         .addFunction("GetTypeName", &Texture2DArray::GetTypeName)
//         .addFunction("GetTypeInfo", &Texture2DArray::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Texture2DArray::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Texture2DArray::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Texture2DArray::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &Texture2DArray::BeginLoad)
//         .addFunction("EndLoad", &Texture2DArray::EndLoad)
//         .addFunction("OnDeviceLost", &Texture2DArray::OnDeviceLost)
//         .addFunction("OnDeviceReset", &Texture2DArray::OnDeviceReset)
//         .addFunction("Release", &Texture2DArray::Release)
//         .addFunction("SetLayers", &Texture2DArray::SetLayers)
//         .addFunction("SetSize", &Texture2DArray::SetSize)

//         .addOverloadedFunctions("SetData",
//             static_cast<bool(Texture2DArray::*)(unsigned int, unsigned int, int, int, int, int, const void*)>(&Texture2DArray::SetData),
//             static_cast<bool(Texture2DArray::*)(unsigned int, Deserializer&)>(&Texture2DArray::SetData),
//             static_cast<bool(Texture2DArray::*)(unsigned int, Image*, bool)>(&Texture2DArray::SetData))

//         .addFunction("GetLayers", &Texture2DArray::GetLayers)
//         .addFunction("GetData", &Texture2DArray::GetData)
//         .addFunction("GetRenderSurface", &Texture2DArray::GetRenderSurface)

//         .addProperty("type", &Texture2DArray::GetType)
//         .addProperty("typeName", &Texture2DArray::GetTypeName)
//         .addProperty("typeInfo", &Texture2DArray::GetTypeInfo)
//         .addProperty("layers", &Texture2DArray::GetLayers, &Texture2DArray::SetLayers)
//         .addProperty("renderSurface", &Texture2DArray::GetRenderSurface)
//     );
// }

// static void RegisterTexture3D(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KTexture3D"].setClass(UserdataMetatable<Texture3D, Texture>(false)
//         .addStaticFunction("new", &KCreateObject<Texture3D>)
//         .addStaticFunction("__gc", &KReleaseObject<Texture3D>)

//         .addFunction("GetType", &Texture3D::GetType)
//         .addFunction("GetTypeName", &Texture3D::GetTypeName)
//         .addFunction("GetTypeInfo", &Texture3D::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Texture3D::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Texture3D::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Texture3D::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &Texture3D::BeginLoad)
//         .addFunction("EndLoad", &Texture3D::EndLoad)
//         .addFunction("OnDeviceLost", &Texture3D::OnDeviceLost)
//         .addFunction("OnDeviceReset", &Texture3D::OnDeviceReset)
//         .addFunction("Release", &Texture3D::Release)
//         .addFunction("SetSize", &Texture3D::SetSize)

//         .addOverloadedFunctions("SetData",
//             static_cast<bool(Texture3D::*)(unsigned int, int, int, int, int, int, int, const void*)>(&Texture3D::SetData),
//             static_cast<bool(Texture3D::*)(Image*, bool)>(&Texture3D::SetData))

//         .addFunction("GetData", &Texture3D::GetData)

//         .addProperty("type", &Texture3D::GetType)
//         .addProperty("typeName", &Texture3D::GetTypeName)
//         .addProperty("typeInfo", &Texture3D::GetTypeInfo)
//     );
// }

// static void RegisterTextureCube(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KTextureCube"].setClass(UserdataMetatable<TextureCube, Texture>(false)
//         .addStaticFunction("new", &KCreateObject<TextureCube>)
//         .addStaticFunction("__gc", &KReleaseObject<TextureCube>)

//         .addFunction("GetType", &TextureCube::GetType)
//         .addFunction("GetTypeName", &TextureCube::GetTypeName)
//         .addFunction("GetTypeInfo", &TextureCube::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &TextureCube::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &TextureCube::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &TextureCube::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &TextureCube::BeginLoad)
//         .addFunction("EndLoad", &TextureCube::EndLoad)
//         .addFunction("OnDeviceLost", &TextureCube::OnDeviceLost)
//         .addFunction("OnDeviceReset", &TextureCube::OnDeviceReset)
//         .addFunction("Release", &TextureCube::Release)
//         .addFunction("SetSize", &TextureCube::SetSize)

//         .addOverloadedFunctions("SetData",
//             static_cast<bool(TextureCube::*)(CubeMapFace, unsigned int, int, int, int, int, const void*)>(&TextureCube::SetData),
//             static_cast<bool(TextureCube::*)(CubeMapFace, Deserializer&)>(&TextureCube::SetData),
//             static_cast<bool(TextureCube::*)(CubeMapFace, Image*, bool)>(&TextureCube::SetData))

//         .addFunction("GetData", &TextureCube::GetData)
//         .addFunction("GetRenderSurface", &TextureCube::GetRenderSurface)

//         .addProperty("type", &TextureCube::GetType)
//         .addProperty("typeName", &TextureCube::GetTypeName)
//         .addProperty("typeInfo", &TextureCube::GetTypeInfo)
//     );
// }

// static void RegisterVertexBuffer(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KVertexBuffer"].setClass(UserdataMetatable<VertexBuffer, GPUObject>()
//         .setConstructors<VertexBuffer(int*, bool)>()

//         .addFunction("OnDeviceReset", &VertexBuffer::OnDeviceReset)
//         .addFunction("Release", &VertexBuffer::Release)
//         .addFunction("SetShadowed", &VertexBuffer::SetShadowed)

//         .addOverloadedFunctions("SetSize",
//             static_cast<bool(VertexBuffer::*)(unsigned int, const PODVector<VertexElement>&, bool)>(&VertexBuffer::SetSize),
//             static_cast<bool(VertexBuffer::*)(unsigned int, unsigned int, bool)>(&VertexBuffer::SetSize))

//         .addFunction("SetData", &VertexBuffer::SetData)
//         .addFunction("SetDataRange", &VertexBuffer::SetDataRange)
//         .addFunction("Lock", &VertexBuffer::Lock)
//         .addFunction("Unlock", &VertexBuffer::Unlock)
//         .addFunction("IsShadowed", &VertexBuffer::IsShadowed)
//         .addFunction("IsDynamic", &VertexBuffer::IsDynamic)
//         .addFunction("IsLocked", &VertexBuffer::IsLocked)
//         .addFunction("GetVertexCount", &VertexBuffer::GetVertexCount)

//         .addOverloadedFunctions("GetVertexSize",
//             static_cast<unsigned int(VertexBuffer::*)() const>(&VertexBuffer::GetVertexSize),
//             static_cast<unsigned int(VertexBuffer::*)(const PODVector<VertexElement>&)>(&VertexBuffer::GetVertexSize),
//             static_cast<unsigned int(VertexBuffer::*)(unsigned int)>(&VertexBuffer::GetVertexSize))


//         .addOverloadedFunctions("GetElements",
//             static_cast<const PODVector<VertexElement>&(VertexBuffer::*)() const>(&VertexBuffer::GetElements),
//             static_cast<PODVector<VertexElement>(VertexBuffer::*)(unsigned int)>(&VertexBuffer::GetElements))


//         .addOverloadedFunctions("GetElement",
//             static_cast<const VertexElement*(VertexBuffer::*)(VertexElementSemantic, unsigned char) const>(&VertexBuffer::GetElement),
//             static_cast<const VertexElement*(VertexBuffer::*)(VertexElementType, VertexElementSemantic, unsigned char) const>(&VertexBuffer::GetElement),
//             static_cast<const VertexElement*(VertexBuffer::*)(const PODVector<VertexElement>&, VertexElementType, VertexElementSemantic, unsigned char)>(&VertexBuffer::GetElement))


//         .addOverloadedFunctions("HasElement",
//             static_cast<bool(VertexBuffer::*)(VertexElementSemantic, unsigned char) const>(&VertexBuffer::HasElement),
//             static_cast<bool(VertexBuffer::*)(VertexElementType, VertexElementSemantic, unsigned char) const>(&VertexBuffer::HasElement),
//             static_cast<bool(VertexBuffer::*)(const PODVector<VertexElement>&, VertexElementType, VertexElementSemantic, unsigned char)>(&VertexBuffer::HasElement))


//         .addOverloadedFunctions("GetElementOffset",
//             static_cast<unsigned int(VertexBuffer::*)(VertexElementSemantic, unsigned char) const>(&VertexBuffer::GetElementOffset),
//             static_cast<unsigned int(VertexBuffer::*)(VertexElementType, VertexElementSemantic, unsigned char) const>(&VertexBuffer::GetElementOffset),
//             static_cast<unsigned int(VertexBuffer::*)(const PODVector<VertexElement>&, VertexElementType, VertexElementSemantic, unsigned char)>(&VertexBuffer::GetElementOffset))

//         .addFunction("GetElementMask", &VertexBuffer::GetElementMask)
//         .addFunction("GetShadowData", &VertexBuffer::GetShadowData)
//         .addFunction("GetShadowDataShared", &VertexBuffer::GetShadowDataShared)
//         .addFunction("GetBufferHash", &VertexBuffer::GetBufferHash)

//         .addProperty("shadowed", &VertexBuffer::IsShadowed, &VertexBuffer::SetShadowed)
//         .addProperty("dynamic", &VertexBuffer::IsDynamic)
//         .addProperty("locked", &VertexBuffer::IsLocked)
//         .addProperty("vertexCount", &VertexBuffer::GetVertexCount)
//         .addProperty("elementMask", &VertexBuffer::GetElementMask)
//         .addProperty("shadowData", &VertexBuffer::GetShadowData)
//         .addProperty("shadowDataShared", &VertexBuffer::GetShadowDataShared)
//         .addProperty("data", &VertexBuffer::SetData)
//     );
// }

// static void RegisterVertexDeclaration(kaguya::State& lua)
// {
//     using namespace kaguya;

// }

// static void RegisterView(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KLightQueryResult"].setClass(UserdataMetatable<LightQueryResult>()

//         .addProperty("light", &LightQueryResult::light_)
//         .addProperty("litGeometries", &LightQueryResult::litGeometries_)
//         .addProperty("shadowCasters", &LightQueryResult::shadowCasters_)
//         .addProperty("shadowCameras", &LightQueryResult::shadowCameras_)
//         .addProperty("shadowCasterBegin", &LightQueryResult::shadowCasterBegin_)
//         .addProperty("shadowCasterEnd", &LightQueryResult::shadowCasterEnd_)
//         .addProperty("shadowCasterBox", &LightQueryResult::shadowCasterBox_)
//         .addProperty("shadowNearSplits", &LightQueryResult::shadowNearSplits_)
//         .addProperty("shadowFarSplits", &LightQueryResult::shadowFarSplits_)
//         .addProperty("numSplits", &LightQueryResult::numSplits_)
//     );
//     lua["KScenePassInfo"].setClass(UserdataMetatable<ScenePassInfo>()

//         .addProperty("passIndex", &ScenePassInfo::passIndex_)
//         .addProperty("allowInstancing", &ScenePassInfo::allowInstancing_)
//         .addProperty("markToStencil", &ScenePassInfo::markToStencil_)
//         .addProperty("vertexLights", &ScenePassInfo::vertexLights_)
//         .addProperty("batchQueue", &ScenePassInfo::batchQueue_)
//     );
//     lua["KPerThreadSceneResult"].setClass(UserdataMetatable<PerThreadSceneResult>()

//         .addProperty("geometries", &PerThreadSceneResult::geometries_)
//         .addProperty("lights", &PerThreadSceneResult::lights_)
//         .addProperty("minZ", &PerThreadSceneResult::minZ_)
//         .addProperty("maxZ", &PerThreadSceneResult::maxZ_)
//     );
//     lua["KMAX_VIEWPORT_TEXTURES"] = MAX_VIEWPORT_TEXTURES;
//     lua["KView"].setClass(UserdataMetatable<View, Object>(false)
//         .addStaticFunction("new", &KCreateObject<View>)
//         .addStaticFunction("__gc", &KReleaseObject<View>)

//         .addFunction("GetType", &View::GetType)
//         .addFunction("GetTypeName", &View::GetTypeName)
//         .addFunction("GetTypeInfo", &View::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &View::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &View::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &View::GetTypeInfoStatic)
//         .addFunction("Define", &View::Define)
//         .addFunction("Update", &View::Update)
//         .addFunction("Render", &View::Render)
//         .addFunction("GetGraphics", &View::GetGraphics)
//         .addFunction("GetRenderer", &View::GetRenderer)
//         .addFunction("GetScene", &View::GetScene)
//         .addFunction("GetOctree", &View::GetOctree)
//         .addFunction("GetCamera", &View::GetCamera)
//         .addFunction("GetCullCamera", &View::GetCullCamera)
//         .addFunction("GetFrameInfo", &View::GetFrameInfo)
//         .addFunction("GetRenderTarget", &View::GetRenderTarget)
//         .addFunction("GetDrawDebug", &View::GetDrawDebug)
//         .addFunction("GetGeometries", &View::GetGeometries)
//         .addFunction("GetOccluders", &View::GetOccluders)
//         .addFunction("GetLights", &View::GetLights)
//         .addFunction("GetLightQueues", &View::GetLightQueues)
//         .addFunction("GetOcclusionBuffer", &View::GetOcclusionBuffer)
//         .addFunction("GetNumActiveOccluders", &View::GetNumActiveOccluders)
//         .addFunction("GetSourceView", &View::GetSourceView)
//         .addFunction("SetGlobalShaderParameters", &View::SetGlobalShaderParameters)
//         .addFunction("SetCameraShaderParameters", &View::SetCameraShaderParameters)
//         .addFunction("SetGBufferShaderParameters", &View::SetGBufferShaderParameters)
//         .addFunction("DrawFullscreenQuad", &View::DrawFullscreenQuad)
//         .addFunction("FindNamedTexture", &View::FindNamedTexture)

//         .addProperty("type", &View::GetType)
//         .addProperty("typeName", &View::GetTypeName)
//         .addProperty("typeInfo", &View::GetTypeInfo)
//         .addProperty("graphics", &View::GetGraphics)
//         .addProperty("renderer", &View::GetRenderer)
//         .addProperty("scene", &View::GetScene)
//         .addProperty("octree", &View::GetOctree)
//         .addProperty("camera", &View::GetCamera)
//         .addProperty("cullCamera", &View::GetCullCamera)
//         .addProperty("frameInfo", &View::GetFrameInfo)
//         .addProperty("renderTarget", &View::GetRenderTarget)
//         .addProperty("drawDebug", &View::GetDrawDebug)
//         .addProperty("geometries", &View::GetGeometries)
//         .addProperty("occluders", &View::GetOccluders)
//         .addProperty("lights", &View::GetLights)
//         .addProperty("lightQueues", &View::GetLightQueues)
//         .addProperty("occlusionBuffer", &View::GetOcclusionBuffer)
//         .addProperty("numActiveOccluders", &View::GetNumActiveOccluders)
//         .addProperty("sourceView", &View::GetSourceView)
//         .addProperty("cameraShaderParameters", &View::SetCameraShaderParameters)
//     );
// }

// static void RegisterViewport(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KViewport"].setClass(UserdataMetatable<Viewport, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Viewport>)
//         .addStaticFunction("__gc", &KReleaseObject<Viewport>)

//         .addFunction("GetType", &Viewport::GetType)
//         .addFunction("GetTypeName", &Viewport::GetTypeName)
//         .addFunction("GetTypeInfo", &Viewport::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Viewport::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Viewport::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Viewport::GetTypeInfoStatic)
//         .addFunction("SetScene", &Viewport::SetScene)
//         .addFunction("SetCamera", &Viewport::SetCamera)
//         .addFunction("SetRect", &Viewport::SetRect)

//         .addOverloadedFunctions("SetRenderPath",
//             static_cast<void(Viewport::*)(RenderPath*)>(&Viewport::SetRenderPath),
//             static_cast<void(Viewport::*)(XMLFile*)>(&Viewport::SetRenderPath))

//         .addFunction("SetDrawDebug", &Viewport::SetDrawDebug)
//         .addFunction("SetCullCamera", &Viewport::SetCullCamera)
//         .addFunction("GetScene", &Viewport::GetScene)
//         .addFunction("GetCamera", &Viewport::GetCamera)
//         .addFunction("GetView", &Viewport::GetView)
//         .addFunction("GetRect", &Viewport::GetRect)
//         .addFunction("GetRenderPath", &Viewport::GetRenderPath)
//         .addFunction("GetDrawDebug", &Viewport::GetDrawDebug)
//         .addFunction("GetCullCamera", &Viewport::GetCullCamera)
//         .addFunction("GetScreenRay", &Viewport::GetScreenRay)
//         .addFunction("WorldToScreenPoint", &Viewport::WorldToScreenPoint)
//         .addFunction("ScreenToWorldPoint", &Viewport::ScreenToWorldPoint)
//         .addFunction("AllocateView", &Viewport::AllocateView)

//         .addProperty("type", &Viewport::GetType)
//         .addProperty("typeName", &Viewport::GetTypeName)
//         .addProperty("typeInfo", &Viewport::GetTypeInfo)
//         .addProperty("scene", &Viewport::GetScene, &Viewport::SetScene)
//         .addProperty("camera", &Viewport::GetCamera, &Viewport::SetCamera)
//         .addProperty("view", &Viewport::GetView)
//         .addProperty("rect", &Viewport::GetRect, &Viewport::SetRect)
//         .addProperty("renderPath", &Viewport::GetRenderPath)
//         .addProperty("drawDebug", &Viewport::GetDrawDebug, &Viewport::SetDrawDebug)
//         .addProperty("cullCamera", &Viewport::GetCullCamera, &Viewport::SetCullCamera)
//     );
// }

// static void RegisterZone(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KZone"].setClass(UserdataMetatable<Zone, Drawable>(false)
//         .addStaticFunction("new", &KCreateObject<Zone>)
//         .addStaticFunction("__gc", &KReleaseObject<Zone>)

//         .addFunction("GetType", &Zone::GetType)
//         .addFunction("GetTypeName", &Zone::GetTypeName)
//         .addFunction("GetTypeInfo", &Zone::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Zone::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Zone::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Zone::GetTypeInfoStatic)
//         .addFunction("OnSetAttribute", &Zone::OnSetAttribute)
//         .addFunction("DrawDebugGeometry", &Zone::DrawDebugGeometry)
//         .addFunction("SetBoundingBox", &Zone::SetBoundingBox)
//         .addFunction("SetAmbientColor", &Zone::SetAmbientColor)
//         .addFunction("SetFogColor", &Zone::SetFogColor)
//         .addFunction("SetFogStart", &Zone::SetFogStart)
//         .addFunction("SetFogEnd", &Zone::SetFogEnd)
//         .addFunction("SetFogHeight", &Zone::SetFogHeight)
//         .addFunction("SetFogHeightScale", &Zone::SetFogHeightScale)
//         .addFunction("SetPriority", &Zone::SetPriority)
//         .addFunction("SetHeightFog", &Zone::SetHeightFog)
//         .addFunction("SetOverride", &Zone::SetOverride)
//         .addFunction("SetAmbientGradient", &Zone::SetAmbientGradient)
//         .addFunction("SetZoneTexture", &Zone::SetZoneTexture)
//         .addFunction("GetInverseWorldTransform", &Zone::GetInverseWorldTransform)
//         .addFunction("GetAmbientColor", &Zone::GetAmbientColor)
//         .addFunction("GetAmbientStartColor", &Zone::GetAmbientStartColor)
//         .addFunction("GetAmbientEndColor", &Zone::GetAmbientEndColor)
//         .addFunction("GetFogColor", &Zone::GetFogColor)
//         .addFunction("GetFogStart", &Zone::GetFogStart)
//         .addFunction("GetFogEnd", &Zone::GetFogEnd)
//         .addFunction("GetFogHeight", &Zone::GetFogHeight)
//         .addFunction("GetFogHeightScale", &Zone::GetFogHeightScale)
//         .addFunction("GetPriority", &Zone::GetPriority)
//         .addFunction("GetHeightFog", &Zone::GetHeightFog)
//         .addFunction("GetOverride", &Zone::GetOverride)
//         .addFunction("GetAmbientGradient", &Zone::GetAmbientGradient)
//         .addFunction("GetZoneTexture", &Zone::GetZoneTexture)
//         .addFunction("IsInside", &Zone::IsInside)

//         .addProperty("type", &Zone::GetType)
//         .addProperty("typeName", &Zone::GetTypeName)
//         .addProperty("typeInfo", &Zone::GetTypeInfo)
//         .addProperty("inverseWorldTransform", &Zone::GetInverseWorldTransform)
//         .addProperty("ambientColor", &Zone::GetAmbientColor, &Zone::SetAmbientColor)
//         .addProperty("ambientStartColor", &Zone::GetAmbientStartColor)
//         .addProperty("ambientEndColor", &Zone::GetAmbientEndColor)
//         .addProperty("fogColor", &Zone::GetFogColor, &Zone::SetFogColor)
//         .addProperty("fogStart", &Zone::GetFogStart, &Zone::SetFogStart)
//         .addProperty("fogEnd", &Zone::GetFogEnd, &Zone::SetFogEnd)
//         .addProperty("fogHeight", &Zone::GetFogHeight, &Zone::SetFogHeight)
//         .addProperty("fogHeightScale", &Zone::GetFogHeightScale, &Zone::SetFogHeightScale)
//         .addProperty("priority", &Zone::GetPriority, &Zone::SetPriority)
//         .addProperty("heightFog", &Zone::GetHeightFog, &Zone::SetHeightFog)
//         .addProperty("override", &Zone::GetOverride, &Zone::SetOverride)
//         .addProperty("ambientGradient", &Zone::GetAmbientGradient, &Zone::SetAmbientGradient)
//         .addProperty("zoneTexture", &Zone::GetZoneTexture, &Zone::SetZoneTexture)
//         .addProperty("boundingBox", &Zone::SetBoundingBox)
//     );
// }

// void RegisterGraphicsLuaAPI(kaguya::State& lua)
// {
//     RegisterStaticModel(lua);


//     RegisterAnimatedModel(lua);
//     RegisterAnimation(lua);
//     RegisterAnimationController(lua);
//     RegisterAnimationState(lua);
//     RegisterBatch(lua);
//     RegisterBillboardSet(lua);
//     RegisterCamera(lua);
//     RegisterConstantBuffer(lua);
//     RegisterCustomGeometry(lua);
//     RegisterDebugRenderer(lua);
//     RegisterDecalSet(lua);
//     RegisterDrawable(lua);
//     RegisterDrawableEvents(lua);
//     RegisterGeometry(lua);
//     RegisterGPUObject(lua);
//     RegisterGraphics(lua);
//     RegisterGraphicsDefs(lua);
//     RegisterGraphicsEvents(lua);
//     RegisterGraphicsImpl(lua);
//     RegisterIndexBuffer(lua);
//     RegisterLight(lua);
//     RegisterMaterial(lua);
//     RegisterModel(lua);
//     RegisterOcclusionBuffer(lua);
//     RegisterOctree(lua);
//     RegisterOctreeQuery(lua);
//     RegisterParticleEffect(lua);
//     RegisterParticleEmitter(lua);
//     RegisterRenderer(lua);
//     RegisterRenderPath(lua);
//     RegisterRenderSurface(lua);
//     RegisterRibbonTrail(lua);
//     RegisterShader(lua);
//     RegisterShaderPrecache(lua);
//     RegisterShaderProgram(lua);
//     RegisterShaderVariation(lua);
//     RegisterSkeleton(lua);
//     RegisterSkybox(lua);

//     RegisterStaticModelGroup(lua);
//     RegisterTangent(lua);
//     RegisterTechnique(lua);
//     RegisterTerrain(lua);
//     RegisterTerrainPatch(lua);
//     RegisterTexture(lua);
//     RegisterTexture2D(lua);
//     RegisterTexture2DArray(lua);
//     RegisterTexture3D(lua);
//     RegisterTextureCube(lua);
//     RegisterVertexBuffer(lua);
//     RegisterVertexDeclaration(lua);
//     RegisterView(lua);
//     RegisterViewport(lua);
//     RegisterZone(lua);
// }
}
