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

#include "../../Math/Matrix2.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterMatrix2(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Matrix2
    lua["Matrix2"].setClass(UserdataMetatable<Matrix2>()
        // [Construct] Matrix2()
        .setConstructors<Matrix2(),
        // [Construct] Matrix2(const Matrix2& matrix)
        Matrix2(const Matrix2&),
        // [Construct] Matrix2(float v00, float v01, float v10, float v11)
        Matrix2(float, float, float, float)>()

        // [Method] bool operator ==(const Matrix2& rhs) const
        .addFunction("__eq", &Matrix2::operator==)

        .addOverloadedFunctions("__mul",
            // [Method] Vector2 operator *(const Vector2& rhs) const
            static_cast<Vector2(Matrix2::*)(const Vector2&) const>(&Matrix2::operator*),
            // [Method] Matrix2 operator *(float rhs) const
            static_cast<Matrix2(Matrix2::*)(float) const>(&Matrix2::operator*),
            // [Method] Matrix2 operator *(const Matrix2& rhs) const
            static_cast<Matrix2(Matrix2::*)(const Matrix2&) const>(&Matrix2::operator*))

        // [Method] Matrix2 operator +(const Matrix2& rhs) const
        .addFunction("__add", &Matrix2::operator+)
        // [Method] Matrix2 operator -(const Matrix2& rhs) const
        .addFunction("__sub", &Matrix2::operator-)

        .addOverloadedFunctions("SetScale",
            // [Method] void SetScale(const Vector2& scale)
            static_cast<void(Matrix2::*)(const Vector2&)>(&Matrix2::SetScale),
            // [Method] void SetScale(float scale)
            static_cast<void(Matrix2::*)(float)>(&Matrix2::SetScale))

        // [Method] Vector2 Scale() const
        .addFunction("Scale", &Matrix2::Scale)
        // [Method] Matrix2 Transpose() const
        .addFunction("Transpose", &Matrix2::Transpose)
        // [Method] Matrix2 Scaled(const Vector2& scale) const
        .addFunction("Scaled", &Matrix2::Scaled)
        // [Method] bool Equals(const Matrix2& rhs) const
        .addFunction("Equals", &Matrix2::Equals)
        // [Method] Matrix2 Inverse() const
        .addFunction("Inverse", &Matrix2::Inverse)

        // [Method] String ToString() const
        .addFunction("ToString", &Matrix2::ToString)

        // [Field] float m00
        .addProperty("m00", &Matrix2::m00_)
        // [Field] float m01
        .addProperty("m01", &Matrix2::m01_)
        // [Field] float m10
        .addProperty("m10", &Matrix2::m10_)
        // [Field] float m11
        .addProperty("m11", &Matrix2::m11_)

        // [StaticConstant] Matrix2 ZERO
        .addStaticField("ZERO", &Matrix2::ZERO)
        // [StaticConstant] Matrix2 IDENTITY
        .addStaticField("IDENTITY", &Matrix2::IDENTITY)
        );
}
}

