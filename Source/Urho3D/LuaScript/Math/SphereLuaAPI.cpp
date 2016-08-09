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
        .setConstructors<Sphere(),
        Sphere(const Sphere&),
        Sphere(const Vector3&, float),
        Sphere(const Vector3*, unsigned),
        Sphere(const BoundingBox&),
        Sphere(const Frustum&),
        Sphere(const Polyhedron&)>()

        .addFunction("__eq", &Sphere::operator==)

        .addOverloadedFunctions("Define",
            static_cast<void(Sphere::*)(const Sphere&)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const Vector3&, float)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const Vector3*, unsigned)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const BoundingBox&)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const Frustum&)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const Polyhedron&)>(&Sphere::Define))

        .addOverloadedFunctions("Merge",
            static_cast<void(Sphere::*)(const Vector3&)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const Vector3*, unsigned)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const BoundingBox&)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const Frustum&)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const Polyhedron&)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const Sphere&)>(&Sphere::Merge))

        // [Method] void Clear()
        .addFunction("Clear", &Sphere::Clear)

        // [Method] bool Defined() const
        .addFunction("Defined", &Sphere::Defined)

        .addOverloadedFunctions("IsInside",
            static_cast<Intersection(Sphere::*)(const Vector3&) const>(&Sphere::IsInside),
            static_cast<Intersection(Sphere::*)(const Sphere&) const>(&Sphere::IsInside),
            static_cast<Intersection(Sphere::*)(const BoundingBox&) const>(&Sphere::IsInside))

        .addOverloadedFunctions("IsInsideFast",
            static_cast<Intersection(Sphere::*)(const Sphere&) const>(&Sphere::IsInsideFast),
            static_cast<Intersection(Sphere::*)(const BoundingBox&) const>(&Sphere::IsInsideFast))

        .addProperty("center", &Sphere::center_)
        .addProperty("radius", &Sphere::radius_)
        );
}
}

