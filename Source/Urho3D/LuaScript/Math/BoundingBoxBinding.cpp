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

    // [Class] BoundingBox
    lua["BoundingBox"].setClass(UserdataMetatable<BoundingBox>()
    	// [Constructor] BoundingBox()
		.setConstructors<BoundingBox(),
		// [Constructor] BoundingBox(const BoundingBox& box)
		BoundingBox(const BoundingBox&),
		// [Constructor] BoundingBox(const Rect& rect)
		BoundingBox(const Rect&),
		// [Constructor] BoundingBox(const Vector3& min, const Vector3& max)
		BoundingBox(const Vector3&, const Vector3&),
		// [Constructor] BoundingBox(float min, float max)
		BoundingBox(float, float),
		// [Constructor] BoundingBox(const Frustum& frustum)
		BoundingBox(const Frustum&),
		// [Constructor] BoundingBox(const Polyhedron& poly)
		BoundingBox(const Polyhedron&),
		// [Constructor] BoundingBox(const Sphere& sphere)
		BoundingBox(const Sphere&)>()

		// [Method] bool ==(const BoundingBox& rhs) const
        .addFunction("__eq", &BoundingBox::operator==)

        .addOverloadedFunctions("Define",
        	// [Method] void Define(const BoundingBox& box)
            static_cast<void(BoundingBox::*)(const BoundingBox&)>(&BoundingBox::Define),
            // [Method] void Define(const Rect& rect)
            static_cast<void(BoundingBox::*)(const Rect&)>(&BoundingBox::Define),
            // [Method] void Define(const Vector3& min, const Vector3& max)
            static_cast<void(BoundingBox::*)(const Vector3&, const Vector3&)>(&BoundingBox::Define),
            // [Method] void Define(float min, float max)
            static_cast<void(BoundingBox::*)(float, float)>(&BoundingBox::Define),
            // [Method] void Define(const Vector3* vertices, unsigned count)
            static_cast<void(BoundingBox::*)(const Vector3&)>(&BoundingBox::Define),
            // [Method] void Define(const Frustum& frustum)
            static_cast<void(BoundingBox::*)(const Frustum&)>(&BoundingBox::Define),
            // [Method] void Define(const Polyhedron& poly)
            static_cast<void(BoundingBox::*)(const Polyhedron&)>(&BoundingBox::Define),
            // [Method] void Define(const Sphere& sphere)
            static_cast<void(BoundingBox::*)(const Sphere&)>(&BoundingBox::Define))

        .addOverloadedFunctions("Merge",
        	// [Method] void Merge(const Vector3& point)
            static_cast<void(BoundingBox::*)(const Vector3&)>(&BoundingBox::Merge),
            // [Method] void Merge(const BoundingBox& box)
            static_cast<void(BoundingBox::*)(const BoundingBox&)>(&BoundingBox::Merge),
            // [Method] void Merge(const Frustum& frustum);
            static_cast<void(BoundingBox::*)(const Frustum&)>(&BoundingBox::Merge),
			// [Method] void Merge(const Polyhedron& poly);
            static_cast<void(BoundingBox::*)(const Polyhedron&)>(&BoundingBox::Merge),
			// [Method] void Merge(const Sphere& sphere);
            static_cast<void(BoundingBox::*)(const Sphere&)>(&BoundingBox::Merge))

        // [Method] void Clip(const BoundingBox& box)
        .addFunction("Clip", &BoundingBox::Clip)

        .addOverloadedFunctions("Transform",
            // [Method] void Transform(const Matrix3& transform)
            static_cast<void(BoundingBox::*)(const Matrix3&)>(&BoundingBox::Transform),
            // [Method] void Transform(const Matrix3x4& transform)
            static_cast<void(BoundingBox::*)(const Matrix3x4&)>(&BoundingBox::Transform))

        // [Method] void Clear()
        .addFunction("Clear", &BoundingBox::Clear)
        // [Method] bool Defined() const
        .addFunction("Defined", &BoundingBox::Defined)
        // [Method] Vector3 Center() const
        .addFunction("Center", &BoundingBox::Center)
        // [Method] Vector3 Size() const
        .addFunction("Size", &BoundingBox::Size)
        // [Method] Vector3 HalfSize() const
        .addFunction("HalfSize", &BoundingBox::HalfSize)

        .addOverloadedFunctions("Transformed",
            // [Method] BoundingBox Transformed(const Matrix3& transform) const
            static_cast<BoundingBox(BoundingBox::*)(const Matrix3&) const>(&BoundingBox::Transformed),
            // [Method] BoundingBox Transformed(const Matrix3x4& transform) const
            static_cast<BoundingBox(BoundingBox::*)(const Matrix3x4&) const>(&BoundingBox::Transformed))

        // [Method] Rect Projected(const Matrix4& projection) const
        .addFunction("Projected", &BoundingBox::Projected)

        .addOverloadedFunctions("IsInside",
            // [Method] Intersection IsInside(const Vector3& point) const
            static_cast<Intersection(BoundingBox::*)(const Vector3&) const>(&BoundingBox::IsInside),
            // [Method] Intersection IsInside(const BoundingBox& box) const
            static_cast<Intersection(BoundingBox::*)(const BoundingBox&) const>(&BoundingBox::IsInside),
            // [Method] Intersection IsInside(const Sphere& sphere) const
            static_cast<Intersection(BoundingBox::*)(const Sphere&) const>(&BoundingBox::IsInside))


        .addOverloadedFunctions("IsInsideFast",
            // [Method] Intersection IsInsideFast(const BoundingBox& box) const
            static_cast<Intersection(BoundingBox::*)(const BoundingBox&) const>(&BoundingBox::IsInsideFast),
            // [Method] Intersection IsInsideFast(const Sphere& sphere) const
            static_cast<Intersection(BoundingBox::*)(const Sphere&) const>(&BoundingBox::IsInsideFast))

        // [Method] String ToString() const
        .addFunction("ToString", &BoundingBox::ToString)

        // [Field] Vector3 min
        .addProperty("min", &BoundingBox::min_)
        // [Field] Vector3 max
        .addProperty("max", &BoundingBox::max_)

        // [Property(Readonly)] Vector3 center
        .addProperty("center", &BoundingBox::Center)
        // [Property(Readonly)] Vector3 size
        .addProperty("size", &BoundingBox::Size)
        // [Property(Readonly)] Vector3 halfSize
        .addProperty("halfSize", &BoundingBox::HalfSize)
        );
}
}

