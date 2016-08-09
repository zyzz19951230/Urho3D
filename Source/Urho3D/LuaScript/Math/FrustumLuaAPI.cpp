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

#include "../../Math/Frustum.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(FrustumDefine0, Frustum, Define, 5, 6, void(Frustum::*)(float, float, float, float, float, const Matrix3x4&));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(FrustumDefine1, Frustum, Define, 2, 3, void(Frustum::*)(const Vector3&, const Vector3&, const Matrix3x4&));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(FrustumDefine2, Frustum, Define, 1, 2, void(Frustum::*)(const BoundingBox&, const Matrix3x4&));
KAGUYA_MEMBER_FUNCTION_OVERLOADS(FrustumDefineOrtho, Frustum, DefineOrtho, 5, 6);

void RegisterFrustum(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] FrustumPlane
    lua["PLANE_NEAR"] = PLANE_NEAR;
    lua["PLANE_LEFT"] = PLANE_LEFT;
    lua["PLANE_RIGHT"] = PLANE_RIGHT;
    lua["PLANE_UP"] = PLANE_UP;
    lua["PLANE_DOWN"] = PLANE_DOWN;
    lua["PLANE_FAR"] = PLANE_FAR;

    // [Constant] unsigned NUM_FRUSTUM_PLANES
    lua["NUM_FRUSTUM_PLANES"] = NUM_FRUSTUM_PLANES;
    // [Constant] unsigned NUM_FRUSTUM_VERTICES
    lua["NUM_FRUSTUM_VERTICES"] = NUM_FRUSTUM_VERTICES;

    // [Class] Frustum
    lua["Frustum"].setClass(UserdataMetatable<Frustum>()
        // [Constructor] Frustum()
        .setConstructors<Frustum(), 
        // [Constructor] Frustum(const Frustum& frustum)
        Frustum(const Frustum&)>()

        .addOverloadedFunctions("Define", 
            // [Method] void Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform = Matrix3x4::IDENTITY)
            FrustumDefine0(), 
            // [Method] void Define(const Vector3& near, const Vector3& far, const Matrix3x4& transform = Matrix3x4::IDENTITY)
            FrustumDefine1(), 
            // [Method] void Define(const BoundingBox& box, const Matrix3x4& transform = Matrix3x4::IDENTITY)
            FrustumDefine2())

        // [Method] void DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4& transform = Matrix3x4::IDENTITY)
        .addFunction("DefineOrtho", FrustumDefineOrtho())

        .addOverloadedFunctions("Transform",
            // [Method] void Transform(const Matrix3& transform)
            static_cast<void(Frustum::*)(const Matrix3&)>(&Frustum::Transform),
            // [Method] void Transform(const Matrix3x4& transform)
            static_cast<void(Frustum::*)(const Matrix3x4&)>(&Frustum::Transform))
        
        .addOverloadedFunctions("IsInside",
            // [Method] Intersection IsInside(const Vector3& point) const
            static_cast<Intersection(Frustum::*)(const Vector3&) const>(&Frustum::IsInside),
            // [Method] Intersection IsInside(const Sphere& sphere) const
            static_cast<Intersection(Frustum::*)(const Sphere&) const>(&Frustum::IsInside),
            // [Method] Intersection IsInside(const BoundingBox& box) const
            static_cast<Intersection(Frustum::*)(const BoundingBox&) const>(&Frustum::IsInside))
        
        .addOverloadedFunctions("IsInsideFast",
            // [Method] Intersection IsInsideFast(const Sphere& sphere) const
            static_cast<Intersection(Frustum::*)(const Sphere&) const>(&Frustum::IsInsideFast),
            // [Method] Intersection IsInsideFast(const BoundingBox& box) const
            static_cast<Intersection(Frustum::*)(const BoundingBox&) const>(&Frustum::IsInsideFast))

        // [Method] float Distance(const Vector3& point) const
        .addFunction("Distance", &Frustum::Distance)

        .addOverloadedFunctions("Transformed",
            // [Method] Frustum Transformed(const Matrix3& transform) const
            static_cast<Frustum(Frustum::*)(const Matrix3&) const>(&Frustum::Transformed),
            // [Method] Frustum Transformed(const Matrix3x4& transform) const
            static_cast<Frustum(Frustum::*)(const Matrix3x4&) const>(&Frustum::Transformed))

        // [Method] Rect Projected(const Matrix4& transform) const
        .addFunction("Projected", &Frustum::Projected)
        // [Method] void UpdatePlanes()
        .addFunction("UpdatePlanes", &Frustum::UpdatePlanes)
        );
}
}

