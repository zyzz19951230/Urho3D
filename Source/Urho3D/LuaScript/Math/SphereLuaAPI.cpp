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
#include "../../Math/Polyhedron.h"
#include "../../Math/Sphere.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSphere(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Sphere
    lua["Sphere"].setClass(UserdataMetatable<Sphere>()
        // [Constructor] Sphere()
        .setConstructors<Sphere(),
        // [Constructor] Sphere(const Sphere& sphere)
        Sphere(const Sphere&),
        // [Constructor] Sphere(const Vector3& center, float radius)
        Sphere(const Vector3&, float),
        // [Constructor] Sphere(const BoundingBox& box)
        Sphere(const BoundingBox&),
        // [Constructor] Sphere(const Frustum& frustum)
        Sphere(const Frustum&),
        // [Constructor] Sphere(const Polyhedron& poly)
        Sphere(const Polyhedron&)>()

        // [Method] 
        .addFunction("__eq", &Sphere::operator==)

        .addOverloadedFunctions("Define",
            // [Method] void Define(const Sphere& sphere)
            static_cast<void(Sphere::*)(const Sphere&)>(&Sphere::Define),
            // [Method] void Define(const Vector3& center, float radius)
            static_cast<void(Sphere::*)(const Vector3&, float)>(&Sphere::Define),
            // [Method] void Define(const BoundingBox& box)
            static_cast<void(Sphere::*)(const BoundingBox&)>(&Sphere::Define),
            // [Method] void Define(const Frustum& frustum)
            static_cast<void(Sphere::*)(const Frustum&)>(&Sphere::Define),
            // [Method] void Define(const Polyhedron& poly)
            static_cast<void(Sphere::*)(const Polyhedron&)>(&Sphere::Define))

        .addOverloadedFunctions("Merge",
            // [Method] void Merge(const Vector3& point)
            static_cast<void(Sphere::*)(const Vector3&)>(&Sphere::Merge),            
            // [Method] void Merge(const BoundingBox& box)
            static_cast<void(Sphere::*)(const BoundingBox&)>(&Sphere::Merge),
            // [Method] void Merge(const Frustum& frustum)
            static_cast<void(Sphere::*)(const Frustum&)>(&Sphere::Merge),
            // [Method] void Merge(const Polyhedron& poly)
            static_cast<void(Sphere::*)(const Polyhedron&)>(&Sphere::Merge),
            // [Method] void Merge(const Sphere& sphere)
            static_cast<void(Sphere::*)(const Sphere&)>(&Sphere::Merge))

        // [Method] void Clear()
        .addFunction("Clear", &Sphere::Clear)

        // [Method] bool Defined() const
        .addFunction("Defined", &Sphere::Defined)

        .addOverloadedFunctions("IsInside",
            // [Method] Intersection IsInside(const Vector3& point) const
            static_cast<Intersection(Sphere::*)(const Vector3&) const>(&Sphere::IsInside),
            // [Method] Intersection IsInside(const Sphere& sphere) const
            static_cast<Intersection(Sphere::*)(const Sphere&) const>(&Sphere::IsInside),
            // [Method] Intersection IsInside(const BoundingBox& box) const
            static_cast<Intersection(Sphere::*)(const BoundingBox&) const>(&Sphere::IsInside))

        .addOverloadedFunctions("IsInsideFast",
            // [Method] Intersection IsInsideFast(const Sphere& sphere) const
            static_cast<Intersection(Sphere::*)(const Sphere&) const>(&Sphere::IsInsideFast),
            // [Method] Intersection IsInsideFast(const BoundingBox& box) const
            static_cast<Intersection(Sphere::*)(const BoundingBox&) const>(&Sphere::IsInsideFast))

        // [Field] Vector3 center
        .addProperty("center", &Sphere::center_)
        // [Field] float radius
        .addProperty("radius", &Sphere::radius_)
        );
}
}

