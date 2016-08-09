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
    // [Variable] PLANE_NEAR
    lua["PLANE_NEAR"] = PLANE_NEAR;
    // [Variable] PLANE_LEFT,
    lua["PLANE_LEFT"] = PLANE_LEFT;
    // [Variable] PLANE_RIGHT,
    lua["PLANE_RIGHT"] = PLANE_RIGHT;
    // [Variable] PLANE_UP,
    lua["PLANE_UP"] = PLANE_UP;
    // [Variable] PLANE_DOWN,
    lua["PLANE_DOWN"] = PLANE_DOWN;
    // [Variable] PLANE_FAR,
    lua["PLANE_FAR"] = PLANE_FAR;

    // [Constant] unsigned NUM_FRUSTUM_PLANES
    lua["NUM_FRUSTUM_PLANES"] = NUM_FRUSTUM_PLANES;
    // [Constant] unsigned NUM_FRUSTUM_VERTICES
    lua["NUM_FRUSTUM_VERTICES"] = NUM_FRUSTUM_VERTICES;

    // [Class] Frustum
    lua["Frustum"].setClass(UserdataMetatable<Frustum>()
        .setConstructors<Frustum(), 
        Frustum(const Frustum&)>()

        .addOverloadedFunctions("Define", 
            FrustumDefine0(), 
            FrustumDefine1(), 
            FrustumDefine2())

        .addFunction("DefineOrtho", FrustumDefineOrtho())

        .addOverloadedFunctions("Transform",
            static_cast<void(Frustum::*)(const Matrix3&)>(&Frustum::Transform),
            static_cast<void(Frustum::*)(const Matrix3x4&)>(&Frustum::Transform))
        
        .addOverloadedFunctions("IsInside",
            static_cast<Intersection(Frustum::*)(const Vector3&) const>(&Frustum::IsInside),
            static_cast<Intersection(Frustum::*)(const Sphere&) const>(&Frustum::IsInside),
            static_cast<Intersection(Frustum::*)(const BoundingBox&) const>(&Frustum::IsInside))
        
        .addOverloadedFunctions("IsInsideFast",
            static_cast<Intersection(Frustum::*)(const Sphere&) const>(&Frustum::IsInsideFast),
            static_cast<Intersection(Frustum::*)(const BoundingBox&) const>(&Frustum::IsInsideFast))

        // [Method] float Distance(const Vector3& point) const
        .addFunction("Distance", &Frustum::Distance)

        .addOverloadedFunctions("Transformed",
            static_cast<Frustum(Frustum::*)(const Matrix3&) const>(&Frustum::Transformed),
            static_cast<Frustum(Frustum::*)(const Matrix3x4&) const>(&Frustum::Transformed))

        // [Method] Rect Projected(const Matrix4& transform) const
        .addFunction("Projected", &Frustum::Projected)
        // [Method] void UpdatePlanes()
        .addFunction("UpdatePlanes", &Frustum::UpdatePlanes)
        );
}
}

