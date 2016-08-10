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

#include "../../Math/BoundingBox.h"
#include "../../Math/Frustum.h"
#include "../../Math/Plane.h"
#include "../../Math/Ray.h"
#include "../../Math/Sphere.h"
#include "../../Math/Sphere.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(RayHitDistance0, Ray, HitDistance, 1, 2, float(Ray::*)(const Frustum&, bool)const);

static kaguya::standard::tuple<float, Vector3, Vector3> RayHitDistance1(const Ray* self, const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
    Vector3 outNormal;
    Vector3 outBary;
    float distance = self->HitDistance(v0, v1, v2, &outNormal, &outBary);
    return kaguya::standard::make_tuple(distance, outNormal, outBary);
}

void RegisterRay(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Ray
    lua["Ray"].setClass(UserdataMetatable<Ray>()
        // [Constructor] Ray()
        .setConstructors<Ray(),
        // [Constructor] Ray(const Vector3& origin, const Vector3& direction)
        Ray(const Vector3&, const Vector3&),
        // [Constructor] Ray(const Ray& ray)
        Ray(const Ray&)>()

        // [Method] bool operator ==(const Ray& rhs) const
        .addFunction("__eq", &Ray::operator==)

        // [Method] void Define(const Vector3& origin, const Vector3& direction)
        .addFunction("Define", &Ray::Define)
        // [Method] Vector3 Project(const Vector3& point) const
        .addFunction("Project", &Ray::Project)
        // [Method] float Distance(const Vector3& point) const
        .addFunction("Distance", &Ray::Distance)
        // [Method] Vector3 ClosestPoint(const Ray& ray) const
        .addFunction("ClosestPoint", &Ray::ClosestPoint)

        .addOverloadedFunctions("HitDistance",
            // [Method] float HitDistance(const Plane& plane) const
            static_cast<float(Ray::*)(const Plane&) const>(&Ray::HitDistance),
            // [Method] float HitDistance(const BoundingBox& box) const
            static_cast<float(Ray::*)(const BoundingBox&) const>(&Ray::HitDistance),
            // [Method] float HitDistance(const Frustum& frustum, bool solidInside = true) const
            RayHitDistance0(),
            // [Method] float HitDistance(const Sphere& sphere) const
            static_cast<float(Ray::*)(const Sphere&) const>(&Ray::HitDistance),
            // [Method] tuple<float, Vector3, Vector3> HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2) const
            &RayHitDistance1)

        // [Method] Ray Transformed(const Matrix3x4& transform) const
        .addFunction("Transformed", &Ray::Transformed)

        // [Field] Vector3 origin
        .addProperty("origin", &Ray::origin_)
        // [Field] Vector3 direction
        .addProperty("direction", &Ray::direction_)
        );
}
}

