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

#include "../../Graphics/Light.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterLight(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] LightType
    lua["LIGHT_DIRECTIONAL"] = LIGHT_DIRECTIONAL;
    lua["LIGHT_SPOT"] = LIGHT_SPOT;
    lua["LIGHT_POINT"] = LIGHT_POINT;

    // [Constant] float SHADOW_MIN_QUANTIZE
    lua["SHADOW_MIN_QUANTIZE"] = SHADOW_MIN_QUANTIZE;
    // [Constant] float SHADOW_MIN_VIEW
    lua["SHADOW_MIN_VIEW"] = SHADOW_MIN_VIEW;
    // [Constant] int MAX_LIGHT_SPLITS
    lua["MAX_LIGHT_SPLITS"] = MAX_LIGHT_SPLITS;
    // [Constant] unsigned MAX_CASCADE_SPLITS
    lua["MAX_CASCADE_SPLITS"] = MAX_CASCADE_SPLITS;

    // [Class] BiasParameters
    lua["BiasParameters"].setClass(UserdataMetatable<BiasParameters>()
        // [Constructor] BiasParameters()
        .setConstructors<BiasParameters(),
        // [Constructor] BiasParameters(float constantBias, float slopeScaledBias, float normalOffset = 0.0f)
        BiasParameters(float, float),        
        BiasParameters(float, float, float)>()

        // [Field] float constantBias
        .addProperty("constantBias", &BiasParameters::constantBias_)
        // [Field] float slopeScaledBias
        .addProperty("slopeScaledBias", &BiasParameters::slopeScaledBias_)
        // [Field] float normalOffset
        .addProperty("normalOffset", &BiasParameters::normalOffset_)
        );

    // [Class] CascadeParameters
    lua["CascadeParameters"].setClass(UserdataMetatable<CascadeParameters>()
        // [Constructor] CascadeParameters()
        .setConstructors<CascadeParameters(),
        // [Constructor] CascadeParameters(float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust = 1.0f)
        CascadeParameters(float, float, float, float, float),         
        CascadeParameters(float, float, float, float, float, float)>()

        // [Field] float fadeStart
        .addProperty("fadeStart", &CascadeParameters::fadeStart_)
        // [Field] float biasAutoAdjust
        .addProperty("biasAutoAdjust", &CascadeParameters::biasAutoAdjust_)
        );

    // [Class] FocusParameters
    lua["FocusParameters"].setClass(UserdataMetatable<FocusParameters>()
        // [Constructor] FocusParameters()
        .setConstructors<FocusParameters(),
        // [Constructor] FocusParameters(bool focus, bool nonUniform, bool autoSize, float quantize, float minView)
        FocusParameters(bool, bool, bool, float, float)>()

        // [Method] void Validate()
        .addFunction("Validate", &FocusParameters::Validate)

        // [Field] bool focus
        .addProperty("focus", &FocusParameters::focus_)
        // [Field] bool nonUniform
        .addProperty("nonUniform", &FocusParameters::nonUniform_)
        // [Field] bool autoSize
        .addProperty("autoSize", &FocusParameters::autoSize_)
        // [Field] float quantize
        .addProperty("quantize", &FocusParameters::quantize_)
        // [Field] float minView
        .addProperty("minView", &FocusParameters::minView_)
        );

    // [Class] Light : Drawable
    lua["Light"].setClass(UserdataMetatable<Light, Drawable>()
        // [Constructor] Light()
        .addStaticFunction("new", &CreateObject<Light>)

        // [Method] void SetLightType(LightType type)
        .addFunction("SetLightType", &Light::SetLightType)
        // [Method] void SetPerVertex(bool enable)
        .addFunction("SetPerVertex", &Light::SetPerVertex)
        // [Method] void SetColor(const Color& color)
        .addFunction("SetColor", &Light::SetColor)
        // [Method] void SetSpecularIntensity(float intensity)
        .addFunction("SetSpecularIntensity", &Light::SetSpecularIntensity)
        // [Method] void SetBrightness(float brightness)
        .addFunction("SetBrightness", &Light::SetBrightness)
        // [Method] void SetRange(float range)
        .addFunction("SetRange", &Light::SetRange)
        // [Method] void SetFov(float fov)
        .addFunction("SetFov", &Light::SetFov)
        // [Method] void SetAspectRatio(float aspectRatio)
        .addFunction("SetAspectRatio", &Light::SetAspectRatio)
        // [Method] void SetFadeDistance(float distance)
        .addFunction("SetFadeDistance", &Light::SetFadeDistance)
        // [Method] void SetShadowFadeDistance(float distance)
        .addFunction("SetShadowFadeDistance", &Light::SetShadowFadeDistance)
        // [Method] void SetShadowBias(const BiasParameters& parameters)
        .addFunction("SetShadowBias", &Light::SetShadowBias)
        // [Method] void SetShadowCascade(const CascadeParameters& parameters)
        .addFunction("SetShadowCascade", &Light::SetShadowCascade)
        // [Method] void SetShadowFocus(const FocusParameters& parameters)
        .addFunction("SetShadowFocus", &Light::SetShadowFocus)
        // [Method] void SetShadowIntensity(float intensity)
        .addFunction("SetShadowIntensity", &Light::SetShadowIntensity)
        // [Method] void SetShadowResolution(float resolution)
        .addFunction("SetShadowResolution", &Light::SetShadowResolution)
        // [Method] void SetShadowNearFarRatio(float nearFarRatio)
        .addFunction("SetShadowNearFarRatio", &Light::SetShadowNearFarRatio)
        // [Method] void SetRampTexture(Texture* texture)
        .addFunction("SetRampTexture", &Light::SetRampTexture)
        // [Method] void SetShapeTexture(Texture* texture)
        .addFunction("SetShapeTexture", &Light::SetShapeTexture)

        // [Method] LightType GetLightType() const
        .addFunction("GetLightType", &Light::GetLightType)
        // [Method] bool GetPerVertex() const
        .addFunction("GetPerVertex", &Light::GetPerVertex)
        // [Method] const Color& GetColor() const
        .addFunction("GetColor", &Light::GetColor)
        // [Method] float GetSpecularIntensity() const
        .addFunction("GetSpecularIntensity", &Light::GetSpecularIntensity)
        // [Method] float GetBrightness() const
        .addFunction("GetBrightness", &Light::GetBrightness)
        // [Method] Color GetEffectiveColor() const
        .addFunction("GetEffectiveColor", &Light::GetEffectiveColor)
        // [Method] float GetEffectiveSpecularIntensity() const
        .addFunction("GetEffectiveSpecularIntensity", &Light::GetEffectiveSpecularIntensity)
        // [Method] float GetRange() const
        .addFunction("GetRange", &Light::GetRange)
        // [Method] float GetFov() const
        .addFunction("GetFov", &Light::GetFov)
        // [Method] float GetAspectRatio() const
        .addFunction("GetAspectRatio", &Light::GetAspectRatio)
        // [Method] float GetFadeDistance() const
        .addFunction("GetFadeDistance", &Light::GetFadeDistance)
        // [Method] float GetShadowFadeDistance() const
        .addFunction("GetShadowFadeDistance", &Light::GetShadowFadeDistance)
        // [Method] const BiasParameters& GetShadowBias() const
        .addFunction("GetShadowBias", &Light::GetShadowBias)
        // [Method] const CascadeParameters& GetShadowCascade() const
        .addFunction("GetShadowCascade", &Light::GetShadowCascade)
        // [Method] const FocusParameters& GetShadowFocus() const
        .addFunction("GetShadowFocus", &Light::GetShadowFocus)
        // [Method] float GetShadowIntensity() const
        .addFunction("GetShadowIntensity", &Light::GetShadowIntensity)
        // [Method] float GetShadowResolution() const
        .addFunction("GetShadowResolution", &Light::GetShadowResolution)
        // [Method] float GetShadowNearFarRatio() const
        .addFunction("GetShadowNearFarRatio", &Light::GetShadowNearFarRatio)
        // [Method] Texture* GetRampTexture() const
        .addFunction("GetRampTexture", &Light::GetRampTexture)
        // [Method] Texture* GetShapeTexture() const
        .addFunction("GetShapeTexture", &Light::GetShapeTexture)
        // [Method] Frustum GetFrustum() const
        .addFunction("GetFrustum", &Light::GetFrustum)
        // [Method] Frustum GetViewSpaceFrustum(const Matrix3x4& view) const
        .addFunction("GetViewSpaceFrustum", &Light::GetViewSpaceFrustum)
        // [Method] int GetNumShadowSplits() const
        .addFunction("GetNumShadowSplits", &Light::GetNumShadowSplits)
        // [Method] bool IsNegative() const
        .addFunction("IsNegative", &Light::IsNegative)

        // [Property] LightType lightType
        .addProperty("lightType", &Light::GetLightType, &Light::SetLightType)
        // [Property] bool perVertex
        .addProperty("perVertex", &Light::GetPerVertex, &Light::SetPerVertex)
        // [Property] const Color& color
        .addProperty("color", &Light::GetColor, &Light::SetColor)
        // [Property] float specularIntensity
        .addProperty("specularIntensity", &Light::GetSpecularIntensity, &Light::SetSpecularIntensity)
        // [Property] float brightness
        .addProperty("brightness", &Light::GetBrightness, &Light::SetBrightness)
        // [Property(Readonly)] Color effectiveColor
        .addProperty("effectiveColor", &Light::GetEffectiveColor)
        // [Property(Readonly)] float effectiveSpecularIntensity
        .addProperty("effectiveSpecularIntensity", &Light::GetEffectiveSpecularIntensity)
        // [Property] float range
        .addProperty("range", &Light::GetRange, &Light::SetRange)
        // [Property] float fov
        .addProperty("fov", &Light::GetFov, &Light::SetFov)
        // [Property] float aspectRatio
        .addProperty("aspectRatio", &Light::GetAspectRatio, &Light::SetAspectRatio)
        // [Property] float fadeDistance
        .addProperty("fadeDistance", &Light::GetFadeDistance, &Light::SetFadeDistance)
        // [Property] float shadowFadeDistance
        .addProperty("shadowFadeDistance", &Light::GetShadowFadeDistance, &Light::SetShadowFadeDistance)
        // [Property] const BiasParameters& shadowBias
        .addProperty("shadowBias", &Light::GetShadowBias, &Light::SetShadowBias)
        // [Property] const CascadeParameters& shadowCascade
        .addProperty("shadowCascade", &Light::GetShadowCascade, &Light::SetShadowCascade)
        // [Property] const FocusParameters& shadowFocus
        .addProperty("shadowFocus", &Light::GetShadowFocus, &Light::SetShadowFocus)
        // [Property] float shadowIntensity
        .addProperty("shadowIntensity", &Light::GetShadowIntensity, &Light::SetShadowIntensity)
        // [Property] float shadowResolution
        .addProperty("shadowResolution", &Light::GetShadowResolution, &Light::SetShadowResolution)
        // [Property] float shadowNearFarRatio
        .addProperty("shadowNearFarRatio", &Light::GetShadowNearFarRatio, &Light::SetShadowNearFarRatio)
        // [Property] Texture* rampTexture
        .addProperty("rampTexture", &Light::GetRampTexture, &Light::SetRampTexture)
        // [Property] Texture* shapeTexture
        .addProperty("shapeTexture", &Light::GetShapeTexture, &Light::SetShapeTexture)
        // [Property(Readonly)] Frustum frustum
        .addProperty("frustum", &Light::GetFrustum)
        // [Property(Readonly)] int numShadowSplits
        .addProperty("numShadowSplits", &Light::GetNumShadowSplits)
        // [Property(Readonly)] bool negative
        .addProperty("negative", &Light::IsNegative)
        );
}
}

