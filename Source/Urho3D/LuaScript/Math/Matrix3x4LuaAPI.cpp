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

#include "../../Math/Matrix3x4.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static kaguya::standard::tuple<Vector3, Quaternion, Vector3> Matrix3x4Decompose(const Matrix3x4* self)
{
    Vector3 translation;
    Quaternion rotation;
    Vector3 scale;
    self->Decompose(translation, rotation, scale);
    return kaguya::standard::make_tuple(translation, rotation, scale);
}

void RegisterMatrix3x4(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Matrix3x4
    lua["Matrix3x4"].setClass(UserdataMetatable<Matrix3x4>()
        // [Constructor] Matrix3x4()
        .setConstructors<Matrix3x4(),
        // [Constructor] Matrix3x4(const Matrix3x4& matrix)
        Matrix3x4(const Matrix3x4&),
        // [Constructor] Matrix3x4(const Matrix3& matrix)
        Matrix3x4(const Matrix3&),
        // [Constructor] Matrix3x4(const Matrix4& matrix)
        Matrix3x4(const Matrix4&),
        // [Constructor] Matrix3x4(const Vector3& translation, const Quaternion& rotation, float scale)
        Matrix3x4(const Vector3&, const Quaternion&, float),
        // [Constructor] Matrix3x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
        Matrix3x4(const Vector3&, const Quaternion&, const Vector3&)>()

        // [Method] bool operator ==(const Matrix3x4& rhs) const
        .addFunction("__eq", &Matrix3x4::operator==)

        .addOverloadedFunctions("__mul",
            // [Method] Vector3 operator *(const Vector3& rhs) const
            static_cast<Vector3(Matrix3x4::*)(const Vector3&) const>(&Matrix3x4::operator*),
            // [Method] Vector3 operator *(const Vector4& rhs) const
            static_cast<Vector3(Matrix3x4::*)(const Vector4&) const>(&Matrix3x4::operator*),
            // [Method] Matrix3x4 operator *(float rhs) const
            static_cast<Matrix3x4(Matrix3x4::*)(float) const>(&Matrix3x4::operator*),
            // [Method] Matrix3x4 operator *(const Matrix3x4& rhs) const
            static_cast<Matrix3x4(Matrix3x4::*)(const Matrix3x4&) const>(&Matrix3x4::operator*),
            // [Method] Matrix4 operator *(const Matrix4& rhs) const
            static_cast<Matrix4(Matrix3x4::*)(const Matrix4&) const>(&Matrix3x4::operator*))

        // [Method] Matrix3x4 operator +(const Matrix3x4& rhs) const
        .addFunction("__add", &Matrix3x4::operator+)
        // [Method] Matrix3x4 operator -(const Matrix3x4& rhs) const
        .addFunction("__sub", &Matrix3x4::operator-)

        // [Method] void SetTranslation(const Vector3& translation)
        .addFunction("SetTranslation", &Matrix3x4::SetTranslation)
        // [Method] void SetRotation(const Matrix3& rotation)
        .addFunction("SetRotation", &Matrix3x4::SetRotation)

        .addOverloadedFunctions("SetScale",
            // [Method] void SetScale(const Vector3& scale)
            static_cast<void(Matrix3x4::*)(const Vector3&)>(&Matrix3x4::SetScale),
            // [Method] void SetScale(float scale)
            static_cast<void(Matrix3x4::*)(float)>(&Matrix3x4::SetScale))

        // [Method] Matrix3 ToMatrix3() const
        .addFunction("ToMatrix3", &Matrix3x4::ToMatrix3)
        // [Method] Matrix4 ToMatrix4() const
        .addFunction("ToMatrix4", &Matrix3x4::ToMatrix4)
        // [Method] Matrix3 RotationMatrix() const
        .addFunction("RotationMatrix", &Matrix3x4::RotationMatrix)
        // [Method] Vector3 Translation() const
        .addFunction("Translation", &Matrix3x4::Translation)
        // [Method] Quaternion Rotation() const
        .addFunction("Rotation", &Matrix3x4::Rotation)
        // [Method] Vector3 Scale() const
        .addFunction("Scale", &Matrix3x4::Scale)
        // [Method] bool Equals(const Matrix3x4& rhs) const
        .addFunction("Equals", &Matrix3x4::Equals)

        // [Method] tuple<Vector3, Quaternion, Vector3> Decompose() const
        .addStaticFunction("Decompose", &Matrix3x4Decompose)

        // [Method] Matrix3x4 Inverse() const
        .addFunction("Inverse", &Matrix3x4::Inverse)

        // [Method] String ToString() const
        .addFunction("ToString", &Matrix3x4::ToString)

        // [Field] float m00
        .addProperty("m00", &Matrix3x4::m00_)
        // [Field] float m01
        .addProperty("m01", &Matrix3x4::m01_)
        // [Field] float m02
        .addProperty("m02", &Matrix3x4::m02_)
        // [Field] float m03
        .addProperty("m03", &Matrix3x4::m03_)
        // [Field] float m10
        .addProperty("m10", &Matrix3x4::m10_)
        // [Field] float m11
        .addProperty("m11", &Matrix3x4::m11_)
        // [Field] float m12
        .addProperty("m12", &Matrix3x4::m12_)
        // [Field] float m13
        .addProperty("m13", &Matrix3x4::m13_)
        // [Field] float m20
        .addProperty("m20", &Matrix3x4::m20_)
        // [Field] float m21
        .addProperty("m21", &Matrix3x4::m21_)
        // [Field] float m22
        .addProperty("m22", &Matrix3x4::m22_)
        // [Field] float m23
        .addProperty("m23", &Matrix3x4::m23_)

        // [StaticConstant] Matrix3x4ZERO
        .addStaticField("ZERO", &Matrix3x4::ZERO)
        // [StaticConstant] Matrix3x4IDENTITY
        .addStaticField("IDENTITY", &Matrix3x4::IDENTITY)
        );
}
}

