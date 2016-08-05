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
}

