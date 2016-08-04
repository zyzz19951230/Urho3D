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

#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/BillboardSet.h"
#include "../Graphics/Camera.h"
#include "../Graphics/CustomGeometry.h"
#include "../Graphics/DecalSet.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/ParticleEmitter.h"
#include "../Graphics/RibbonTrail.h"
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

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimatedModelSetModel, AnimatedModel, SetModel, 1, 2);

static void AnimatedModelModelSetter(AnimatedModel* self, Model* model)
{
    self->SetModel(model);
}

static Model* AnimatedModelModelGetter(const AnimatedModel* self)
{
    return self->GetModel();
}

static void RegisterAnimatedModel(kaguya::State& lua)
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

static void RegisterBillboardSet(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Billboard"].setClass(UserdataMetatable<Billboard>()

        .addProperty("position", &Billboard::position_)
        .addProperty("size", &Billboard::size_)
        .addProperty("uv", &Billboard::uv_)
        .addProperty("color", &Billboard::color_)
        .addProperty("rotation", &Billboard::rotation_)
        .addProperty("direction", &Billboard::direction_)
        .addProperty("enabled", &Billboard::enabled_)
        );

    lua["BillboardSet"].setClass(UserdataMetatable<BillboardSet, Drawable>()
        .addStaticFunction("new", &CreateObject<BillboardSet>)

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
        .addFunction("GetBillboard", &BillboardSet::GetBillboard)
        .addFunction("IsRelative", &BillboardSet::IsRelative)
        .addFunction("IsScaled", &BillboardSet::IsScaled)
        .addFunction("IsSorted", &BillboardSet::IsSorted)
        .addFunction("IsFixedScreenSize", &BillboardSet::IsFixedScreenSize)
        .addFunction("GetFaceCameraMode", &BillboardSet::GetFaceCameraMode)
        .addFunction("GetAnimationLodBias", &BillboardSet::GetAnimationLodBias)

        .addProperty("material", &BillboardSet::GetMaterial, &BillboardSet::SetMaterial)
        .addProperty("numBillboards", &BillboardSet::GetNumBillboards, &BillboardSet::SetNumBillboards)
        .addProperty("relative", &BillboardSet::IsRelative, &BillboardSet::SetRelative)
        .addProperty("scaled", &BillboardSet::IsScaled, &BillboardSet::SetScaled)
        .addProperty("sorted", &BillboardSet::IsSorted, &BillboardSet::SetSorted)
        .addProperty("fixedScreenSize", &BillboardSet::IsFixedScreenSize, &BillboardSet::SetFixedScreenSize)
        .addProperty("faceCameraMode", &BillboardSet::GetFaceCameraMode, &BillboardSet::SetFaceCameraMode)
        .addProperty("animationLodBias", &BillboardSet::GetAnimationLodBias, &BillboardSet::SetAnimationLodBias)
        );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(CustomGeometryGetMaterial, CustomGeometry, GetMaterial, 0, 1);

static void CustomGeometryMaterialSetter(CustomGeometry* self, Material* material)
{
    self->SetMaterial(material);
}

static Material* CustomGeometryMaterialGetter(const CustomGeometry* self)
{
    return self->GetMaterial();
}

static void RegisterCustomGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CustomGeometryVertex"].setClass(UserdataMetatable<CustomGeometryVertex>()
    
    .addProperty("position", &CustomGeometryVertex::position_)
    .addProperty("normal", &CustomGeometryVertex::normal_)
    .addProperty("color", &CustomGeometryVertex::color_)
    .addProperty("texCoord", &CustomGeometryVertex::texCoord_)
    .addProperty("tangent", &CustomGeometryVertex::tangent_)
    );

    lua["CustomGeometry"].setClass(UserdataMetatable<CustomGeometry, Drawable>()
        .addStaticFunction("new", &CreateObject<CustomGeometry>)

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
        
        .addFunction("GetMaterial", CustomGeometryGetMaterial())

        .addFunction("GetVertex", &CustomGeometry::GetVertex)

        .addProperty("numGeometries", &CustomGeometry::GetNumGeometries, &CustomGeometry::SetNumGeometries)
        .addProperty("dynamic", &CustomGeometry::IsDynamic, &CustomGeometry::SetDynamic)
        .addProperty("material", &CustomGeometryMaterialGetter, &CustomGeometryMaterialSetter)
        );
}

static bool DecalSetAddDecal0(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV)
{
    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV);
}

static bool DecalSetAddDecal1(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive)
{
    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive);
}

static bool DecalSetAddDecal2(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff)
{
    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive, normalCutoff);
}

static bool DecalSetAddDecal3(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff, unsigned int subGeometry)
{
    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive, normalCutoff, subGeometry);
}

// KAGUYA_MEMBER_FUNCTION_OVERLOADS(DecalSetAddDecal, DecalSet, AddDecal, 8, 11);

static void RegisterDecalSet(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DecalSet"].setClass(UserdataMetatable<DecalSet, Drawable>()
        .addStaticFunction("new", &CreateObject<DecalSet>)

        .addFunction("SetMaterial", &DecalSet::SetMaterial)
        .addFunction("SetMaxVertices", &DecalSet::SetMaxVertices)
        .addFunction("SetMaxIndices", &DecalSet::SetMaxIndices)
        
        ADD_OVERLOADED_FUNCTIONS_4(DecalSet, AddDecal)
        // .addFunction("AddDecal", DecalSetAddDecal())

        .addFunction("RemoveDecals", &DecalSet::RemoveDecals)
        .addFunction("RemoveAllDecals", &DecalSet::RemoveAllDecals)

        .addFunction("GetMaterial", &DecalSet::GetMaterial)
        .addFunction("GetNumDecals", &DecalSet::GetNumDecals)
        .addFunction("GetNumVertices", &DecalSet::GetNumVertices)
        .addFunction("GetNumIndices", &DecalSet::GetNumIndices)
        .addFunction("GetMaxVertices", &DecalSet::GetMaxVertices)
        .addFunction("GetMaxIndices", &DecalSet::GetMaxIndices)

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

    lua["DRAWABLE_GEOMETRY"] = DRAWABLE_GEOMETRY;
    lua["DRAWABLE_LIGHT"] = DRAWABLE_LIGHT;
    lua["DRAWABLE_ZONE"] = DRAWABLE_ZONE;
    lua["DRAWABLE_GEOMETRY2D"] = DRAWABLE_GEOMETRY2D;
    lua["DRAWABLE_ANY"] = DRAWABLE_ANY;
    lua["DEFAULT_VIEWMASK"] = DEFAULT_VIEWMASK;
    lua["DEFAULT_LIGHTMASK"] = DEFAULT_LIGHTMASK;
    lua["DEFAULT_SHADOWMASK"] = DEFAULT_SHADOWMASK;
    lua["DEFAULT_ZONEMASK"] = DEFAULT_ZONEMASK;
    lua["MAX_VERTEX_LIGHTS"] = MAX_VERTEX_LIGHTS;
    lua["ANIMATION_LOD_BASESCALE"] = ANIMATION_LOD_BASESCALE;

    lua["Drawable"].setClass(UserdataMetatable<Drawable, Component>()

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
            static_cast<bool(Drawable::*)(Camera*) const>(&Drawable::IsInView))

        .addProperty("boundingBox", &Drawable::GetBoundingBox)
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

        .addProperty("inView", static_cast<bool(Drawable::*)() const>(&Drawable::IsInView))
        .addProperty("zone", &Drawable::GetZone)
        );
}

static void RegisterLight(kaguya::State& lua)
{
    using namespace kaguya;

    // enum LightType;
    lua["LIGHT_DIRECTIONAL"] = LIGHT_DIRECTIONAL;
    lua["LIGHT_SPOT"] = LIGHT_SPOT;
    lua["LIGHT_POINT"] = LIGHT_POINT;

    lua["SHADOW_MIN_QUANTIZE"] = SHADOW_MIN_QUANTIZE;
    lua["SHADOW_MIN_VIEW"] = SHADOW_MIN_VIEW;
    lua["MAX_LIGHT_SPLITS"] = MAX_LIGHT_SPLITS;
    lua["MAX_CASCADE_SPLITS"] = MAX_CASCADE_SPLITS;

    lua["BiasParameters"].setClass(UserdataMetatable<BiasParameters>()
        .setConstructors<BiasParameters(),
        BiasParameters(float, float),
        BiasParameters(float, float, float)>()

        .addProperty("constantBias", &BiasParameters::constantBias_)
        .addProperty("slopeScaledBias", &BiasParameters::slopeScaledBias_)
        .addProperty("normalOffset", &BiasParameters::normalOffset_)
        );

    lua["CascadeParameters"].setClass(UserdataMetatable<CascadeParameters>()
        .setConstructors<CascadeParameters(),
        CascadeParameters(float, float, float, float, float), 
        CascadeParameters(float, float, float, float, float, float)>()

        .addProperty("fadeStart", &CascadeParameters::fadeStart_)
        .addProperty("biasAutoAdjust", &CascadeParameters::biasAutoAdjust_)
        );

    lua["FocusParameters"].setClass(UserdataMetatable<FocusParameters>()
        .setConstructors<FocusParameters(),
        FocusParameters(bool, bool, bool, float, float)>()

        .addFunction("Validate", &FocusParameters::Validate)

        .addProperty("focus", &FocusParameters::focus_)
        .addProperty("nonUniform", &FocusParameters::nonUniform_)
        .addProperty("autoSize", &FocusParameters::autoSize_)
        .addProperty("quantize", &FocusParameters::quantize_)
        .addProperty("minView", &FocusParameters::minView_)
        );

    lua["Light"].setClass(UserdataMetatable<Light, Drawable>()
        .addStaticFunction("new", &CreateObject<Light>)

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
        );
}

static void RegisterParticleEmitter(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ParticleEmitter"].setClass(UserdataMetatable<ParticleEmitter, BillboardSet>()
        .addStaticFunction("new", &CreateObject<ParticleEmitter>)

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
    lua["TT_FACE_CAMERA"] = TT_FACE_CAMERA;
    lua["TT_BONE"] = TT_BONE;

    lua["RibbonTrail"].setClass(UserdataMetatable<RibbonTrail, Drawable>()
        .addStaticFunction("new", &CreateObject<RibbonTrail>)

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

static void RegisterSkybox(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Skybox"].setClass(UserdataMetatable<Skybox, StaticModel>()
        .addStaticFunction("new", &CreateObject<Skybox>)
        );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(StaticModelApplyMaterialList, StaticModel, ApplyMaterialList, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(StaticModelGetMaterial, StaticModel, GetMaterial, 0, 1);

static void StaticModelMaterialSetter(StaticModel* self, Material* material)
{
    self->SetMaterial(material);
}

static Material* StaticModelMaterialGetter(const StaticModel* self)
{
    return self->GetMaterial();
}

static void RegisterStaticModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["StaticModel"].setClass(UserdataMetatable<StaticModel, Drawable>()
        .addStaticFunction("new", &CreateObject<StaticModel>)

        .addFunction("SetModel", &StaticModel::SetModel)

        .addOverloadedFunctions("SetMaterial",
            static_cast<void(StaticModel::*)(Material*)>(&StaticModel::SetMaterial),
            static_cast<bool(StaticModel::*)(unsigned, Material*)>(&StaticModel::SetMaterial))

        .addFunction("SetOcclusionLodLevel", &StaticModel::SetOcclusionLodLevel)
        
        .addFunction("ApplyMaterialList", StaticModelApplyMaterialList())

        .addFunction("GetModel", &StaticModel::GetModel)
        .addFunction("GetNumGeometries", &StaticModel::GetNumGeometries)

        .addFunction("GetMaterial", StaticModelGetMaterial())
        
        .addFunction("GetOcclusionLodLevel", &StaticModel::GetOcclusionLodLevel)
        .addFunction("IsInside", &StaticModel::IsInside)
        .addFunction("IsInsideLocal", &StaticModel::IsInsideLocal)

        .addProperty("model", &StaticModel::GetModel, &StaticModel::SetModel)

        .addProperty("material", &StaticModelMaterialGetter, &StaticModelMaterialSetter)

        .addProperty("numGeometries", &StaticModel::GetNumGeometries)
        .addProperty("occlusionLodLevel", &StaticModel::GetOcclusionLodLevel, &StaticModel::SetOcclusionLodLevel)
        );
}

static void RegisterStaticModelGroup(kaguya::State& lua)
{
    using namespace kaguya;

    lua["StaticModelGroup"].setClass(UserdataMetatable<StaticModelGroup, StaticModel>()
        .addStaticFunction("new", &CreateObject<StaticModelGroup>)

        .addFunction("AddInstanceNode", &StaticModelGroup::AddInstanceNode)
        .addFunction("RemoveInstanceNode", &StaticModelGroup::RemoveInstanceNode)
        .addFunction("RemoveAllInstanceNodes", &StaticModelGroup::RemoveAllInstanceNodes)
        
        .addFunction("GetNumInstanceNodes", &StaticModelGroup::GetNumInstanceNodes)
        .addFunction("GetInstanceNode", &StaticModelGroup::GetInstanceNode)

        .addProperty("numInstanceNodes", &StaticModelGroup::GetNumInstanceNodes)
        );
}

static void RegisterTerrainPatch(kaguya::State& lua)
{
    using namespace kaguya;

    lua["TerrainPatch"].setClass(UserdataMetatable<TerrainPatch, Drawable>()
        .addStaticFunction("new", &CreateObject<TerrainPatch>)

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
        .addFunction("GetCoordinates", &TerrainPatch::GetCoordinates)
        .addFunction("GetLodLevel", &TerrainPatch::GetLodLevel)

        .addProperty("geometry", &TerrainPatch::GetGeometry)
        .addProperty("maxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
        .addProperty("occlusionGeometry", &TerrainPatch::GetOcclusionGeometry)
        .addProperty("owner", &TerrainPatch::GetOwner, &TerrainPatch::SetOwner)
        .addProperty("northPatch", &TerrainPatch::GetNorthPatch)
        .addProperty("southPatch", &TerrainPatch::GetSouthPatch)
        .addProperty("westPatch", &TerrainPatch::GetWestPatch)
        .addProperty("eastPatch", &TerrainPatch::GetEastPatch)
        .addProperty("coordinates", &TerrainPatch::GetCoordinates, &TerrainPatch::SetCoordinates)
        .addProperty("lodLevel", &TerrainPatch::GetLodLevel)
        .addProperty("boundingBox", &TerrainPatch::SetBoundingBox)
        );
}

static void RegisterZone(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Zone"].setClass(UserdataMetatable<Zone, Drawable>()
        .addStaticFunction("new", &CreateObject<Zone>)

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

void RegisterDrawableLuaAPI(kaguya::State& lua)
{
    RegisterDrawable(lua);
    RegisterStaticModel(lua);

    RegisterAnimatedModel(lua);
    RegisterBillboardSet(lua);
    RegisterCustomGeometry(lua);
    RegisterDecalSet(lua);
    RegisterLight(lua);
    RegisterParticleEmitter(lua);
    RegisterRibbonTrail(lua);
    RegisterSkybox(lua);
    RegisterStaticModelGroup(lua);
    RegisterTerrainPatch(lua);
    RegisterZone(lua);
}
}