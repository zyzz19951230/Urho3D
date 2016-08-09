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

#include "../../Math/Vector3.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterVector3(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Vector3
    lua["Vector3"].setClass(UserdataMetatable<Vector3>()
        // [Constructor] Vector3()
        .setConstructors<Vector3(),
        // [Constructor] Vector3(const Vector3& vector)
        Vector3(const Vector3&),
        // [Constructor] Vector3(const Vector2& vector, float z)
        Vector3(const Vector2&, float),
        // [Constructor] Vector3(const Vector2& vector)
        Vector3(const Vector2&),
        // [Constructor] Vector3(float x, float y, float z)
        Vector3(float, float, float),
        // [Constructor] Vector3(float x, float y)
        Vector3(float, float)>()

        // [Method] bool operator==(const Vector3& rhs) const
        .addFunction("__eq", &Vector3::operator==)
        // [Method] Vector3 operator+(const Vector3&) const
        .addFunction("__add", &Vector3::operator+)

        .addOverloadedFunctions("__sub",
            // [Method] Vector3 operator-() const
            static_cast<Vector3(Vector3::*)() const>(&Vector3::operator-),
            // [Method] Vector3 operator-(const Vector3&) const
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator-))

        .addOverloadedFunctions("__mul",
            // [Method] Vector3 operator*(float) const
            static_cast<Vector3(Vector3::*)(float) const>(&Vector3::operator*),
            // [Method] Vector3 operator*(const Vector3&) const
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator*))

        .addOverloadedFunctions("__div",
            // [Method] Vector3 operator/(float) const
            static_cast<Vector3(Vector3::*)(float) const>(&Vector3::operator/),
            // [Method] Vector3 operator/(const Vector3&) const
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator/))

        // [Method] void Normalize()
        .addFunction("Normalize", &Vector3::Normalize)
        // [Method] float Length() const
        .addFunction("Length", &Vector3::Length)
        // [Method] float lenSquared = LengthSquared()
        .addFunction("LengthSquared", &Vector3::LengthSquared)
        // [Method] float DotProduct(const Vector3& rhs) const
        .addFunction("DotProduct", &Vector3::DotProduct)
        // [Method] float AbsDotProduct(const Vector3& rhs) const
        .addFunction("AbsDotProduct", &Vector3::AbsDotProduct)
        // [Method] Vector3 CrossProduct(const Vector3& rhs) const
        .addFunction("CrossProduct", &Vector3::CrossProduct)
        // [Method] Vector3 Abs() const
        .addFunction("Abs", &Vector3::Abs)
        // [Method] Vector3 Lerp(const Vector3& rhs, float t) const
        .addFunction("Lerp", &Vector3::Lerp)
        // [Method] bool Equals(const Vector3& rhs) const
        .addFunction("Equals", &Vector3::Equals)
        // [Method] float Angle(const Vector3& rhs) const
        .addFunction("Angle", &Vector3::Angle)
        // [Method] bool IsNaN() const
        .addFunction("IsNaN", &Vector3::IsNaN)
        // [Method] Vector3 Normalized() const
        .addFunction("Normalized", &Vector3::Normalized)

        // [Method] String ToString() const
        .addFunction("ToString", &Vector3::ToString)

        // [Field] float x
        .addProperty("x", &Vector3::x_)
        // [Field] float y
        .addProperty("y", &Vector3::y_)
        // [Field] float z
        .addProperty("z", &Vector3::z_)
        
        // [StaticConstant] Vector3 ZERO
        .addStaticField("ZERO", &Vector3::ZERO)
        // [StaticConstant] Vector3 LEFT
        .addStaticField("LEFT", &Vector3::LEFT)
        // [StaticConstant] Vector3 RIGHT
        .addStaticField("RIGHT", &Vector3::RIGHT)
        // [StaticConstant] Vector3 UP
        .addStaticField("UP", &Vector3::UP)
        // [StaticConstant] Vector3 DOWN
        .addStaticField("DOWN", &Vector3::DOWN)
        // [StaticConstant] Vector3 FORWARD
        .addStaticField("FORWARD", &Vector3::FORWARD)
        // [StaticConstant] Vector3 BACK
        .addStaticField("BACK", &Vector3::BACK)
        // [StaticConstant] Vector3 ONE
        .addStaticField("ONE", &Vector3::ONE)
        );
}
}

