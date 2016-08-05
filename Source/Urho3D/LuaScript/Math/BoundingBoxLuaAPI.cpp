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
#include "../../Math/Polyhedron.h"
#include "../../Math/Sphere.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterBoundingBox(kaguya::State& lua)
{
    using namespace kaguya;

    lua["BoundingBox"].setClass(UserdataMetatable<BoundingBox>()
        .setConstructors<BoundingBox(),
        BoundingBox(const BoundingBox&),
        BoundingBox(const Rect&),
        BoundingBox(const Vector3&, const Vector3&),
        BoundingBox(float, float),
        BoundingBox(const Frustum&),
        BoundingBox(const Polyhedron&),
        BoundingBox(const Sphere&)>()

        .addFunction("__eq", &BoundingBox::operator==)

        .addOverloadedFunctions("Define",
            static_cast<void(BoundingBox::*)(const BoundingBox&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Rect&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Vector3&, const Vector3&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(float, float)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Vector3&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Frustum&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Polyhedron&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Sphere&)>(&BoundingBox::Define))

        .addOverloadedFunctions("Merge",
            static_cast<void(BoundingBox::*)(const Vector3&)>(&BoundingBox::Merge),
            static_cast<void(BoundingBox::*)(const BoundingBox&)>(&BoundingBox::Merge),
            static_cast<void(BoundingBox::*)(const Frustum&)>(&BoundingBox::Merge),
            static_cast<void(BoundingBox::*)(const Polyhedron&)>(&BoundingBox::Merge),
            static_cast<void(BoundingBox::*)(const Sphere&)>(&BoundingBox::Merge))

        .addFunction("Clip", &BoundingBox::Clip)

        .addOverloadedFunctions("Transform",
            static_cast<void(BoundingBox::*)(const Matrix3&)>(&BoundingBox::Transform),
            static_cast<void(BoundingBox::*)(const Matrix3x4&)>(&BoundingBox::Transform))

        .addFunction("Clear", &BoundingBox::Clear)
        .addFunction("Defined", &BoundingBox::Defined)
        .addFunction("Center", &BoundingBox::Center)
        .addFunction("Size", &BoundingBox::Size)
        .addFunction("HalfSize", &BoundingBox::HalfSize)

        .addOverloadedFunctions("Transformed",
            static_cast<BoundingBox(BoundingBox::*)(const Matrix3&) const>(&BoundingBox::Transformed),
            static_cast<BoundingBox(BoundingBox::*)(const Matrix3x4&) const>(&BoundingBox::Transformed))

        .addFunction("Projected", &BoundingBox::Projected)

        .addOverloadedFunctions("IsInside",
            static_cast<Intersection(BoundingBox::*)(const Vector3&) const>(&BoundingBox::IsInside),
            static_cast<Intersection(BoundingBox::*)(const BoundingBox&) const>(&BoundingBox::IsInside),
            static_cast<Intersection(BoundingBox::*)(const Sphere&) const>(&BoundingBox::IsInside))


        .addOverloadedFunctions("IsInsideFast",
            static_cast<Intersection(BoundingBox::*)(const BoundingBox&) const>(&BoundingBox::IsInsideFast),
            static_cast<Intersection(BoundingBox::*)(const Sphere&) const>(&BoundingBox::IsInsideFast))

        .addFunction("ToString", &BoundingBox::ToString)

        .addProperty("min", &BoundingBox::min_)
        .addProperty("max", &BoundingBox::max_)

        .addProperty("center", &BoundingBox::Center)
        .addProperty("size", &BoundingBox::Size)
        .addProperty("halfSize", &BoundingBox::HalfSize)
        );
}
}

