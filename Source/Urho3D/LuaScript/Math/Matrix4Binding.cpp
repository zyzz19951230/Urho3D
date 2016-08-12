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

#include "../../Math/Matrix4.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static kaguya::standard::tuple<Vector3, Quaternion, Vector3> Matrix4Decompose(const Matrix4* self)
{
    Vector3 translation;
    Quaternion rotation;
    Vector3 scale;
    self->Decompose(translation, rotation, scale);
    return kaguya::standard::make_tuple(translation, rotation, scale);
}

void RegisterMatrix4(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Matrix4
    lua["Matrix4"].setClass(UserdataMetatable<Matrix4>()
        // [Constructor] Matrix4()
        .setConstructors<Matrix4(),
        // [Constructor] Matrix4(const Matrix4& matrix)
         Matrix4(const Matrix4&),
        // [Constructor] Matrix4(const Matrix3& matrix)
         Matrix4(const Matrix3&)>()

        // [Method] bool operator==(const Matrix4& rhs) const
        .addFunction("__eq", &Matrix4::operator==)

        .addOverloadedFunctions("__mul",
            // [Method] Vector3 operator*(const Vector3& rhs) const
            static_cast<Vector3(Matrix4::*)(const Vector3&) const>(&Matrix4::operator*),
            // [Method] Vector4 operator*(const Vector4& rhs) const
            static_cast<Vector4(Matrix4::*)(const Vector4&) const>(&Matrix4::operator*),
            // [Method] Matrix4 operator*(float rhs) const
            static_cast<Matrix4(Matrix4::*)(float) const>(&Matrix4::operator*),
            // [Method] Matrix4 operator*(const Matrix4& rhs) const
            static_cast<Matrix4(Matrix4::*)(const Matrix4&) const>(&Matrix4::operator*),
            // [Method] Matrix4 operator*(const Matrix3x4& rhs) const;
            static_cast<Matrix4(Matrix4::*)(const Matrix3x4&) const>(&Matrix4::operator*))

        // [Method] 
        .addFunction("__add", &Matrix4::operator+)
        // [Method] 
        .addFunction("__sub", &Matrix4::operator-)

        // [Method] void SetTranslation(const Vector3& translation)
        .addFunction("SetTranslation", &Matrix4::SetTranslation)
        // [Method] void SetRotation(const Matrix3& rotation)
        .addFunction("SetRotation", &Matrix4::SetRotation)

        .addOverloadedFunctions("SetScale",
            // [Method] void SetScale(const Vector3& scale)
            static_cast<void(Matrix4::*)(const Vector3&)>(&Matrix4::SetScale),
            // [Method] void SetScale(float scale)
            static_cast<void(Matrix4::*)(float)>(&Matrix4::SetScale))

        // [Method] Matrix3 ToMatrix3() const
        .addFunction("ToMatrix3", &Matrix4::ToMatrix3)
        // [Method] Matrix3 RotationMatrix() const
        .addFunction("RotationMatrix", &Matrix4::RotationMatrix)
        // [Method] Vector3 Translation() const
        .addFunction("Translation", &Matrix4::Translation)
        // [Method] Quaternion Rotation() const
        .addFunction("Rotation", &Matrix4::Rotation)
        // [Method] Vector3 Scale() const
        .addFunction("Scale", &Matrix4::Scale)
        // [Method] Matrix4 Transpose() const
        .addFunction("Transpose", &Matrix4::Transpose)
        // [Method] bool Equals(const Matrix4& rhs) const
        .addFunction("Equals", &Matrix4::Equals)

        // [Method] tuple<Vector3, Quaternion, Vector3> Decompose() const
        .addStaticFunction("Decompose", &Matrix4Decompose)

        // [Method] Matrix4 Inverse() const
        .addFunction("Inverse", &Matrix4::Inverse)

        // [Method] String ToString() const
        .addFunction("ToString", &Matrix4::ToString)

        // [Field] float m00
        .addProperty("m00", &Matrix4::m00_)
        // [Field] float m01
        .addProperty("m01", &Matrix4::m01_)
        // [Field] float m02
        .addProperty("m02", &Matrix4::m02_)
        // [Field] float m03
        .addProperty("m03", &Matrix4::m03_)
        // [Field] float m10
        .addProperty("m10", &Matrix4::m10_)
        // [Field] float m11
        .addProperty("m11", &Matrix4::m11_)
        // [Field] float m12
        .addProperty("m12", &Matrix4::m12_)
        // [Field] float m13
        .addProperty("m13", &Matrix4::m13_)
        // [Field] float m20
        .addProperty("m20", &Matrix4::m20_)
        // [Field] float m21
        .addProperty("m21", &Matrix4::m21_)
        // [Field] float m22
        .addProperty("m22", &Matrix4::m22_)
        // [Field] float m23
        .addProperty("m23", &Matrix4::m23_)
        // [Field] float m30
        .addProperty("m30", &Matrix4::m30_)
        // [Field] float m31
        .addProperty("m31", &Matrix4::m31_)
        // [Field] float m32
        .addProperty("m32", &Matrix4::m32_)
        // [Field] float m33
        .addProperty("m33", &Matrix4::m33_)
        
        // [StaticConstant] Matrix4 ZERO
        .addStaticField("ZERO", &Matrix4::ZERO)
        // [StaticConstant] Matrix4 IDENTITY
        .addStaticField("IDENTITY", &Matrix4::IDENTITY)
        );
}
}

