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
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterPolyhedron(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Polyhedron
    lua["Polyhedron"].setClass(UserdataMetatable<Polyhedron>()
        // [Constructor]Polyhedron()
        .setConstructors<Polyhedron(),
        // [Constructor] Polyhedron(const Polyhedron& polyhedron)
        Polyhedron(const Polyhedron&),
        // [Constructor]Polyhedron(const BoundingBox& box)
        Polyhedron(const BoundingBox&),
        // [Constructor] Polyhedron(const Frustum& frustum)
        Polyhedron(const Frustum&)>()

        .addOverloadedFunctions("Define",
            // [Method] void Define(const BoundingBox& box)
            static_cast<void(Polyhedron::*)(const BoundingBox&)>(&Polyhedron::Define),
            // [Method] void Define(const Frustum& frustum)
            static_cast<void(Polyhedron::*)(const Frustum&)>(&Polyhedron::Define))

        .addOverloadedFunctions("AddFace",
            // [Method] void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2)
            static_cast<void(Polyhedron::*)(const Vector3&, const Vector3&, const Vector3&)>(&Polyhedron::AddFace),
            // [Method] void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3)
            static_cast<void(Polyhedron::*)(const Vector3&, const Vector3&, const Vector3&, const Vector3&)>(&Polyhedron::AddFace))
        
        .addOverloadedFunctions("Clip",
            // [Method] void Clip(const Plane& plane)
            static_cast<void(Polyhedron::*)(const Plane&)>(&Polyhedron::Clip),
            // [Method] void Clip(const BoundingBox& box)
            static_cast<void(Polyhedron::*)(const BoundingBox&)>(&Polyhedron::Clip),
            // [Method] void Clip(const Frustum& box)
            static_cast<void(Polyhedron::*)(const Frustum&)>(&Polyhedron::Clip))

        // [Method] void Clear()
        .addFunction("Clear", &Polyhedron::Clear)

        .addOverloadedFunctions("Transform",
            // [Method] void Transform(const Matrix3& transform)
            static_cast<void(Polyhedron::*)(const Matrix3&)>(&Polyhedron::Transform),
            // [Method] void Transform(const Matrix3x4& transform)
            static_cast<void(Polyhedron::*)(const Matrix3x4&)>(&Polyhedron::Transform))
        
        .addOverloadedFunctions("Transformed",
            // [Method] Polyhedron Transformed(const Matrix3& transform) const
            static_cast<Polyhedron(Polyhedron::*)(const Matrix3&) const>(&Polyhedron::Transformed),
            // [Method] Polyhedron Transformed(const Matrix3x4& transform) const
            static_cast<Polyhedron(Polyhedron::*)(const Matrix3x4&) const>(&Polyhedron::Transformed))

        // [Method] bool Empty() const
        .addFunction("Empty", &Polyhedron::Empty)

        // [Property(ReadOnly)] bool empty
        .addProperty("empty", &Polyhedron::Empty)
        );
}
}

