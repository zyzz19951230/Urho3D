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

    // [Constant] float DEFAULT_NEARCLIP
    lua["DEFAULT_NEARCLIP"] = DEFAULT_NEARCLIP;
    // [Constant] float DEFAULT_FARCLIP
    lua["DEFAULT_FARCLIP"] = DEFAULT_FARCLIP;
    // [Constant] float DEFAULT_CAMERA_FOV
    lua["DEFAULT_CAMERA_FOV"] = DEFAULT_CAMERA_FOV;
    // [Constant] float DEFAULT_ORTHOSIZE
    lua["DEFAULT_ORTHOSIZE"] = DEFAULT_ORTHOSIZE;

    // [Constant] unsigned VO_NONE
    lua["VO_NONE"] = VO_NONE;
    // [Constant] unsigned VO_LOW_MATERIAL_QUALITY
    lua["VO_LOW_MATERIAL_QUALITY"] = VO_LOW_MATERIAL_QUALITY;
    // [Constant] unsigned VO_DISABLE_SHADOWS
    lua["VO_DISABLE_SHADOWS"] = VO_DISABLE_SHADOWS;
    // [Constant] unsigned VO_DISABLE_OCCLUSION
    lua["VO_DISABLE_OCCLUSION"] = VO_DISABLE_OCCLUSION;

    // [Class] Camera : Component
    lua["Camera"].setClass(UserdataMetatable<Camera, Component>()
        // [Constructor] Camera()
        .addStaticFunction("new", &CreateObject<Camera>)
        
        // [Method] void SetNearClip(float nearClip)
        .addFunction("SetNearClip", &Camera::SetNearClip)
        // [Method] void SetFarClip(float farClip)
        .addFunction("SetFarClip", &Camera::SetFarClip)
        // [Method] void SetFov(float fov)
        .addFunction("SetFov", &Camera::SetFov)

        .addOverloadedFunctions("SetOrthoSize",
            // [Method] void SetOrthoSize(float orthoSize)
            static_cast<void(Camera::*)(float)>(&Camera::SetOrthoSize),
            // [Method] void SetOrthoSize(const Vector2& orthoSize)
            static_cast<void(Camera::*)(const Vector2&)>(&Camera::SetOrthoSize))

        // [Method] void SetAspectRatio(float aspectRatio)
        .addFunction("SetAspectRatio", &Camera::SetAspectRatio)
        // [Method] void SetFillMode(FillMode mode)
        .addFunction("SetFillMode", &Camera::SetFillMode)
        // [Method] void SetZoom(float zoom)
        .addFunction("SetZoom", &Camera::SetZoom)
        // [Method] void SetLodBias(float bias)
        .addFunction("SetLodBias", &Camera::SetLodBias)
        // [Method] void SetViewMask(unsigned mask)
        .addFunction("SetViewMask", &Camera::SetViewMask)
        // [Method] void SetViewOverrideFlags(unsigned flags)
        .addFunction("SetViewOverrideFlags", &Camera::SetViewOverrideFlags)
        // [Method] void SetOrthographic(bool enable)
        .addFunction("SetOrthographic", &Camera::SetOrthographic)
        // [Method] void SetAutoAspectRatio(bool enable)
        .addFunction("SetAutoAspectRatio", &Camera::SetAutoAspectRatio)
        // [Method] void SetProjectionOffset(const Vector2& offset)
        .addFunction("SetProjectionOffset", &Camera::SetProjectionOffset)
        // [Method] void SetUseReflection(bool enable)
        .addFunction("SetUseReflection", &Camera::SetUseReflection)
        // [Method] void SetReflectionPlane(const Plane& plane)
        .addFunction("SetReflectionPlane", &Camera::SetReflectionPlane)
        // [Method] void SetUseClipping(bool enable)
        .addFunction("SetUseClipping", &Camera::SetUseClipping)
        // [Method] void SetClipPlane(const Plane& plane)
        .addFunction("SetClipPlane", &Camera::SetClipPlane)
        // [Method] void SetFlipVertical(bool enable)
        .addFunction("SetFlipVertical", &Camera::SetFlipVertical)

        // [Method] float GetFarClip() const
        .addFunction("GetFarClip", &Camera::GetFarClip)
        // [Method] float GetNearClip() const
        .addFunction("GetNearClip", &Camera::GetNearClip)
        // [Method] float GetFov() const
        .addFunction("GetFov", &Camera::GetFov)
        // [Method] float GetOrthoSize() const
        .addFunction("GetOrthoSize", &Camera::GetOrthoSize)
        // [Method] float GetAspectRatio() const
        .addFunction("GetAspectRatio", &Camera::GetAspectRatio)
        // [Method] float GetZoom() const
        .addFunction("GetZoom", &Camera::GetZoom)
        // [Method] float GetLodBias() const
        .addFunction("GetLodBias", &Camera::GetLodBias)
        // [Method] unsigned GetViewMask() const
        .addFunction("GetViewMask", &Camera::GetViewMask)
        // [Method] unsigned GetViewOverrideFlags() const
        .addFunction("GetViewOverrideFlags", &Camera::GetViewOverrideFlags)
        // [Method] FillMode GetFillMode() const
        .addFunction("GetFillMode", &Camera::GetFillMode)
        // [Method] bool IsOrthographic() const
        .addFunction("IsOrthographic", &Camera::IsOrthographic)
        // [Method] bool GetAutoAspectRatio() const
        .addFunction("GetAutoAspectRatio", &Camera::GetAutoAspectRatio)
        // [Method] const Frustum& GetFrustum() const
        .addFunction("GetFrustum", &Camera::GetFrustum)

        .addOverloadedFunctions("GetProjection",
            // [Method] const Matrix4& GetProjection() const
            static_cast<const Matrix4&(Camera::*)() const>(&Camera::GetProjection),
            // [Method] Matrix4 GetProjection(bool apiSpecific) const
            static_cast<Matrix4(Camera::*)(bool) const>(&Camera::GetProjection))

        // [Method] const Matrix3x4& GetView() const
        .addFunction("GetView", &Camera::GetView)
        // [Method] void GetFrustumSize(Vector3& near, Vector3& far) const
        .addFunction("GetFrustumSize", &Camera::GetFrustumSize)
        // [Method] float GetHalfViewSize() const
        .addFunction("GetHalfViewSize", &Camera::GetHalfViewSize)
        
        // [Method] Frustum GetSplitFrustum(float nearClip, float farClip) const
        .addFunction("GetSplitFrustum", &Camera::GetSplitFrustum)
        // [Method] Frustum GetViewSpaceFrustum() const
        .addFunction("GetViewSpaceFrustum", &Camera::GetViewSpaceFrustum)
        // [Method] Frustum GetViewSpaceSplitFrustum(float nearClip, float farClip) const
        .addFunction("GetViewSpaceSplitFrustum", &Camera::GetViewSpaceSplitFrustum)

        // [Method] Ray GetScreenRay(float x, float y) const
        .addFunction("GetScreenRay", &Camera::GetScreenRay)
        // [Method] Vector2 WorldToScreenPoint(const Vector3& worldPos) const
        .addFunction("WorldToScreenPoint", &Camera::WorldToScreenPoint)
        // [Method] Vector3 ScreenToWorldPoint(const Vector3& screenPos) const
        .addFunction("ScreenToWorldPoint", &Camera::ScreenToWorldPoint)
        // [Method] const Vector2& GetProjectionOffset() const
        .addFunction("GetProjectionOffset", &Camera::GetProjectionOffset)
        // [Method] bool GetUseReflection() const
        .addFunction("GetUseReflection", &Camera::GetUseReflection)
        // [Method] const Plane& GetReflectionPlane() const
        .addFunction("GetReflectionPlane", &Camera::GetReflectionPlane)
        // [Method] bool GetUseClipping() const
        .addFunction("GetUseClipping", &Camera::GetUseClipping)
        // [Method] const Plane& GetClipPlane() const
        .addFunction("GetClipPlane", &Camera::GetClipPlane)
        // [Method] bool GetFlipVertical() const
        .addFunction("GetFlipVertical", &Camera::GetFlipVertical)
        
        // [Method] float GetDistance(const Vector3& worldPos) const
        .addFunction("GetDistance", &Camera::GetDistance)
        // [Method] float GetDistanceSquared(const Vector3& worldPos) const
        .addFunction("GetDistanceSquared", &Camera::GetDistanceSquared)
        // [Method] float GetLodDistance(float distance, float scale, float bias) const
        .addFunction("GetLodDistance", &Camera::GetLodDistance)
        // [Method] bool IsProjectionValid() const
        .addFunction("IsProjectionValid", &Camera::IsProjectionValid)
        // [Method] Matrix3x4 GetEffectiveWorldTransform() const
        .addFunction("GetEffectiveWorldTransform", &Camera::GetEffectiveWorldTransform)

        // [Property] float farClip
        .addProperty("farClip", &Camera::GetFarClip, &Camera::SetFarClip)
        // [Property] float nearClip
        .addProperty("nearClip", &Camera::GetNearClip, &Camera::SetNearClip)
        // [Property] float fov
        .addProperty("fov", &Camera::GetFov, &Camera::SetFov)
        // [Property] float orthoSize
        .addProperty("orthoSize", &Camera::GetOrthoSize, static_cast<void(Camera::*)(float)>(&Camera::SetOrthoSize))
        // [Property] float aspectRatio
        .addProperty("aspectRatio", &Camera::GetAspectRatio, &Camera::SetAspectRatio)
        // [Property] float zoom
        .addProperty("zoom", &Camera::GetZoom, &Camera::SetZoom)
        // [Property] float lodBias
        .addProperty("lodBias", &Camera::GetLodBias, &Camera::SetLodBias)
        // [Property] unsigned viewMask
        .addProperty("viewMask", &Camera::GetViewMask, &Camera::SetViewMask)
        // [Property] unsigned viewOverrideFlags
        .addProperty("viewOverrideFlags", &Camera::GetViewOverrideFlags, &Camera::SetViewOverrideFlags)
        // [Property] FillMode fillMode
        .addProperty("fillMode", &Camera::GetFillMode, &Camera::SetFillMode)
        // [Property] bool orthographic
        .addProperty("orthographic", &Camera::IsOrthographic, &Camera::SetOrthographic)
        // [Property] bool autoAspectRatio
        .addProperty("autoAspectRatio", &Camera::GetAutoAspectRatio, &Camera::SetAutoAspectRatio)
        // [Property(ReadOnly)] const Frustum& frustum
        .addProperty("frustum", &Camera::GetFrustum)
        // [Property(ReadOnly)] const Matrix3x4& view
        .addProperty("view", &Camera::GetView)
        // [Property(ReadOnly)] float halfViewSize
        .addProperty("halfViewSize", &Camera::GetHalfViewSize)
        // [Property(ReadOnly)] Frustum viewSpaceFrustum
        .addProperty("viewSpaceFrustum", &Camera::GetViewSpaceFrustum)
        // [Property] const Vector2& projectionOffset
        .addProperty("projectionOffset", &Camera::GetProjectionOffset, &Camera::SetProjectionOffset)
        // [Property] bool useReflection
        .addProperty("useReflection", &Camera::GetUseReflection, &Camera::SetUseReflection)
        // [Property] const Plane& reflectionPlane
        .addProperty("reflectionPlane", &Camera::GetReflectionPlane, &Camera::SetReflectionPlane)
        // [Property] bool useClipping
        .addProperty("useClipping", &Camera::GetUseClipping, &Camera::SetUseClipping)
        // [Property] const Plane& clipPlane
        .addProperty("clipPlane", &Camera::GetClipPlane, &Camera::SetClipPlane)
        // [Property] bool flipVertical
        .addProperty("flipVertical", &Camera::GetFlipVertical, &Camera::SetFlipVertical)
        // [Property(ReadOnly)] bool projectionValid
        .addProperty("projectionValid", &Camera::IsProjectionValid)
    );
}
}

