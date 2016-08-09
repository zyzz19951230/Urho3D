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

#include "../../Math/Plane.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterPlane(kaguya::State& lua)
{
    using namespace kaguya;
	
    // [Class] Plane
    lua["Plane"].setClass(UserdataMetatable<Plane>()
        // [Constructor] Plane()
        .setConstructors<Plane(),
        // [Constructor] Plane(const Plane& plane)
        Plane(const Plane&),
        // [Constructor] Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2)
        Plane(const Vector3&, const Vector3&, const Vector3&),
        // [Constructor] Plane(const Vector3& normal, const Vector3& point)
        Plane(const Vector3&, const Vector3&),
        // [Constructor] Plane(const Vector4& plane)
        Plane(const Vector4&)>()

        .addOverloadedFunctions("Define",
            // [Method] void Define(const Vector3& v0, const Vector3& v1, const Vector3& v2)
            static_cast<void(Plane::*)(const Vector3&, const Vector3&, const Vector3&)>(&Plane::Define),
            // [Method] void Define(const Vector3& normal, const Vector3& point)
            static_cast<void(Plane::*)(const Vector3&, const Vector3&)>(&Plane::Define),
            // [Method] void Define(const Vector4& plane)
            static_cast<void(Plane::*)(const Vector4&)>(&Plane::Define))

        .addOverloadedFunctions("Transform",
            // [Method] void Transform(const Matrix3& transform)
            static_cast<void(Plane::*)(const Matrix3&)>(&Plane::Transform),
            // [Method] void Transform(const Matrix3x4& transform)  
            static_cast<void(Plane::*)(const Matrix3x4&)>(&Plane::Transform),
            // [Method] void Transform(const Matrix4& transform)
            static_cast<void(Plane::*)(const Matrix4&)>(&Plane::Transform))

        // [Method] Vector3 Project(const Vector3& point) const
        .addFunction("Project", &Plane::Project)
        // [Method] float Distance(const Vector3& point) const
        .addFunction("Distance", &Plane::Distance)
        // [Method] Vector3 Reflect(const Vector3& direction) const
        .addFunction("Reflect", &Plane::Reflect)
        // [Method] Matrix3x4 ReflectionMatrix() const
        .addFunction("ReflectionMatrix", &Plane::ReflectionMatrix)

        .addOverloadedFunctions("Transformed",
            // [Method] Plane Transformed(const Matrix3& transform) const
            static_cast<Plane(Plane::*)(const Matrix3&) const>(&Plane::Transformed),
            // [Method] Plane Transformed(const Matrix3x4& transform) const
            static_cast<Plane(Plane::*)(const Matrix3x4&) const>(&Plane::Transformed),
            // [Method] Plane Transformed(const Matrix4& transform) const
            static_cast<Plane(Plane::*)(const Matrix4&) const>(&Plane::Transformed))

        // [Method] Vector4 ToVector4() const
        .addFunction("ToVector4", &Plane::ToVector4)

        // [Property] Vector3 normal
        .addProperty("normal", &Plane::normal_)
        // [Field] Vector3 absNormal
        .addProperty("absNormal", &Plane::absNormal_)
        // [Property] float d
        .addProperty("d", &Plane::d_)

        // [StaticConstant] Plane UP
        .addStaticField("UP", &Plane::UP)
        );
}
}

