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

static std::tuple<Vector3, Quaternion, Vector3> Matrix3x4Decompose(const Matrix3x4* self)
{
    Vector3 translation;
    Quaternion rotation;
    Vector3 scale;
    self->Decompose(translation, rotation, scale);
    return std::make_tuple(translation, rotation, scale);
}

void RegisterMatrix3x4(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Matrix3x4"].setClass(UserdataMetatable<Matrix3x4>()
        .setConstructors<Matrix3x4(),
        Matrix3x4(const Matrix3x4&),
        Matrix3x4(const Matrix3&),
        Matrix3x4(const Matrix4&),
        Matrix3x4(const Vector3&, const Quaternion&, float),
        Matrix3x4(const Vector3&, const Quaternion&, const Vector3&)>()

        .addFunction("__eq", &Matrix3x4::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Vector3(Matrix3x4::*)(const Vector3&) const>(&Matrix3x4::operator*),
            static_cast<Vector3(Matrix3x4::*)(const Vector4&) const>(&Matrix3x4::operator*),
            static_cast<Matrix3x4(Matrix3x4::*)(float) const>(&Matrix3x4::operator*),
            static_cast<Matrix3x4(Matrix3x4::*)(const Matrix3x4&) const>(&Matrix3x4::operator*),
            static_cast<Matrix4(Matrix3x4::*)(const Matrix4&) const>(&Matrix3x4::operator*))

        .addFunction("__add", &Matrix3x4::operator+)
        .addFunction("__sub", &Matrix3x4::operator-)

        .addFunction("SetTranslation", &Matrix3x4::SetTranslation)
        .addFunction("SetRotation", &Matrix3x4::SetRotation)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Matrix3x4::*)(const Vector3&)>(&Matrix3x4::SetScale),
            static_cast<void(Matrix3x4::*)(float)>(&Matrix3x4::SetScale))

        .addFunction("ToMatrix3", &Matrix3x4::ToMatrix3)
        .addFunction("ToMatrix4", &Matrix3x4::ToMatrix4)
        .addFunction("RotationMatrix", &Matrix3x4::RotationMatrix)
        .addFunction("Translation", &Matrix3x4::Translation)
        .addFunction("Rotation", &Matrix3x4::Rotation)
        .addFunction("Scale", &Matrix3x4::Scale)
        .addFunction("Equals", &Matrix3x4::Equals)

        .addStaticFunction("Decompose", &Matrix3x4Decompose)

        .addFunction("Inverse", &Matrix3x4::Inverse)

        .addFunction("ToString", &Matrix3x4::ToString)

        .addProperty("m00", &Matrix3x4::m00_)
        .addProperty("m01", &Matrix3x4::m01_)
        .addProperty("m02", &Matrix3x4::m02_)
        .addProperty("m03", &Matrix3x4::m03_)
        .addProperty("m10", &Matrix3x4::m10_)
        .addProperty("m11", &Matrix3x4::m11_)
        .addProperty("m12", &Matrix3x4::m12_)
        .addProperty("m13", &Matrix3x4::m13_)
        .addProperty("m20", &Matrix3x4::m20_)
        .addProperty("m21", &Matrix3x4::m21_)
        .addProperty("m22", &Matrix3x4::m22_)
        .addProperty("m23", &Matrix3x4::m23_)

        .addStaticField("ZERO", &Matrix3x4::ZERO)
        .addStaticField("IDENTITY", &Matrix3x4::IDENTITY)
        );
}
}

