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

#include "../../Graphics/Camera.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern Context* globalContext;

void RegisterCamera(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DEFAULT_NEARCLIP"] = DEFAULT_NEARCLIP;
    lua["DEFAULT_FARCLIP"] = DEFAULT_FARCLIP;
    lua["DEFAULT_CAMERA_FOV"] = DEFAULT_CAMERA_FOV;
    lua["DEFAULT_ORTHOSIZE"] = DEFAULT_ORTHOSIZE;

    lua["VO_NONE"] = VO_NONE;
    lua["VO_LOW_MATERIAL_QUALITY"] = VO_LOW_MATERIAL_QUALITY;
    lua["VO_DISABLE_SHADOWS"] = VO_DISABLE_SHADOWS;
    lua["VO_DISABLE_OCCLUSION"] = VO_DISABLE_OCCLUSION;

    lua["Camera"].setClass(UserdataMetatable<Camera, Component>()
        .addStaticFunction("new", &CreateObject<Camera>)
        
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
        
        .addFunction("GetDistance", &Camera::GetDistance)
        .addFunction("GetDistanceSquared", &Camera::GetDistanceSquared)
        .addFunction("GetLodDistance", &Camera::GetLodDistance)
        .addFunction("IsProjectionValid", &Camera::IsProjectionValid)
        .addFunction("GetEffectiveWorldTransform", &Camera::GetEffectiveWorldTransform)

        .addProperty("farClip", &Camera::GetFarClip, &Camera::SetFarClip)
        .addProperty("nearClip", &Camera::GetNearClip, &Camera::SetNearClip)
        .addProperty("fov", &Camera::GetFov, &Camera::SetFov)
        .addProperty("orthoSize", &Camera::GetOrthoSize, static_cast<void(Camera::*)(float)>(&Camera::SetOrthoSize))
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
        .addProperty("projectionValid", &Camera::IsProjectionValid)
    );
}
}

