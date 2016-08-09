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

#include "../../Math/Matrix3.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterMatrix3(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Matrix3
    lua["Matrix3"].setClass(UserdataMetatable<Matrix3>()
        .setConstructors<Matrix3(),
        Matrix3(const Matrix3&),
        Matrix3(float, float, float, float, float, float, float, float, float)>()

        .addFunction("__eq", &Matrix3::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Vector3(Matrix3::*)(const Vector3&) const>(&Matrix3::operator*),
            static_cast<Matrix3(Matrix3::*)(float) const>(&Matrix3::operator*),
            static_cast<Matrix3(Matrix3::*)(const Matrix3&) const>(&Matrix3::operator*))

        .addFunction("__add", &Matrix3::operator+)
        .addFunction("__sub", &Matrix3::operator-)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Matrix3::*)(const Vector3&)>(&Matrix3::SetScale),
            static_cast<void(Matrix3::*)(float)>(&Matrix3::SetScale))

        // [Method] Vector3 Scale() const
        .addFunction("Scale", &Matrix3::Scale)
        // [Method] Matrix3 Transpose() const
        .addFunction("Transpose", &Matrix3::Transpose)
        // [Method] Matrix3 Scaled(const Vector3& scale) const
        .addFunction("Scaled", &Matrix3::Scaled)
        // [Method] bool Equals(const Matrix3& rhs) const
        .addFunction("Equals", &Matrix3::Equals)
        // [Method] Matrix3 Inverse() const
        .addFunction("Inverse", &Matrix3::Inverse)

        // [Method] String ToString() const
        .addFunction("ToString", &Matrix3::ToString)

        .addProperty("m00", &Matrix3::m00_)
        .addProperty("m01", &Matrix3::m01_)
        .addProperty("m02", &Matrix3::m02_)
        .addProperty("m10", &Matrix3::m10_)
        .addProperty("m11", &Matrix3::m11_)
        .addProperty("m12", &Matrix3::m12_)
        .addProperty("m20", &Matrix3::m20_)
        .addProperty("m21", &Matrix3::m21_)
        .addProperty("m22", &Matrix3::m22_)

        .addStaticField("ZERO", &Matrix3::ZERO)
        .addStaticField("IDENTITY", &Matrix3::IDENTITY)
        );
}
}

