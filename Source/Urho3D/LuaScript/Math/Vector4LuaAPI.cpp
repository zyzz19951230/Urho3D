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

#include "../../Math/Vector4.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterVector4(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Vector4
    lua["Vector4"].setClass(UserdataMetatable<Vector4>()
        // [Constructor] Vector4()
        .setConstructors<Vector4(),
        // [Constructor] Vector4(const Vector4& vector)
        Vector4(const Vector4&),
        // [Constructor] Vector4(const Vector3& vector, float w)
        Vector4(const Vector3&, float),
        // [Constructor] Vector4(float x, float y, float z, float w)
        Vector4(float, float, float, float)>()

        // [Method] bool operator==(const Vector4& rhs) const
        .addFunction("__eq", &Vector4::operator==)
        // [Method] Vector4 operator+(const Vector4& rhs) const
        .addFunction("__add", &Vector4::operator+)

        .addOverloadedFunctions("__sub",
            // [Method] Vector4 operator-() const
            static_cast<Vector4(Vector4::*)() const>(&Vector4::operator-),
            // [Method] Vector4 operator-(const Vector4& rhs) const
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator-))

        .addOverloadedFunctions("__mul",
            // [Method] Vector4 operator*(float rhs) const
            static_cast<Vector4(Vector4::*)(float) const>(&Vector4::operator*),
            // [Method] Vector4 operator*(const Vector4& rhs) const
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator*))

        .addOverloadedFunctions("__div",
            // [Method] Vector4 operator/(float rhs) const
            static_cast<Vector4(Vector4::*)(float) const>(&Vector4::operator/),
            // [Method] Vector4 operator/(const Vector4& rhs) const
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator/))

        // [Method] float DotProduct(const Vector4& rhs) const
        .addFunction("DotProduct", &Vector4::DotProduct)
        // [Method] float AbsDotProduct(const Vector4& rhs) const
        .addFunction("AbsDotProduct", &Vector4::AbsDotProduct)
        // [Method] Vector4 Abs() const
        .addFunction("Abs", &Vector4::Abs)
        // [Method] Vector4 Lerp(const Vector4& rhs, float t) const
        .addFunction("Lerp", &Vector4::Lerp)
        // [Method] bool Equals(const Vector4& rhs) const
        .addFunction("Equals", &Vector4::Equals)
        // [Method] bool IsNaN() const
        .addFunction("IsNaN", &Vector4::IsNaN)

        // [Method] String ToString() const
        .addFunction("ToString", &Vector4::ToString)

        // [Field] float x
        .addProperty("x", &Vector4::x_)
        // [Field] float y
        .addProperty("y", &Vector4::y_)
        // [Field] float z
        .addProperty("z", &Vector4::z_)
        // [Field] float w
        .addProperty("w", &Vector4::w_)

        // [StaticConstant] Vector4 ZERO
        .addStaticField("ZERO", &Vector4::ZERO)
        // [StaticConstant] Vector4 ONE
        .addStaticField("ONE", &Vector4::ONE)
        );
}
}

