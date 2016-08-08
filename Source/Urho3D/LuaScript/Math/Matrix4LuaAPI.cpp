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

    lua["Matrix4"].setClass(UserdataMetatable<Matrix4>()
        .setConstructors<Matrix4(),
        Matrix4(const Matrix4&),
        Matrix4(const Matrix3&)>()

        .addFunction("__eq", &Matrix4::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Vector3(Matrix4::*)(const Vector3&) const>(&Matrix4::operator*),
            static_cast<Vector4(Matrix4::*)(const Vector4&) const>(&Matrix4::operator*),
            static_cast<Matrix4(Matrix4::*)(float) const>(&Matrix4::operator*),
            static_cast<Matrix4(Matrix4::*)(const Matrix4&) const>(&Matrix4::operator*),
            static_cast<Matrix4(Matrix4::*)(const Matrix3x4&) const>(&Matrix4::operator*))

        .addFunction("__add", &Matrix4::operator+)
        .addFunction("__sub", &Matrix4::operator-)

        .addFunction("SetTranslation", &Matrix4::SetTranslation)
        .addFunction("SetRotation", &Matrix4::SetRotation)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Matrix4::*)(const Vector3&)>(&Matrix4::SetScale),
            static_cast<void(Matrix4::*)(float)>(&Matrix4::SetScale))

        .addFunction("ToMatrix3", &Matrix4::ToMatrix3)
        .addFunction("RotationMatrix", &Matrix4::RotationMatrix)
        .addFunction("Translation", &Matrix4::Translation)
        .addFunction("Rotation", &Matrix4::Rotation)
        .addFunction("Scale", &Matrix4::Scale)
        .addFunction("Transpose", &Matrix4::Transpose)
        .addFunction("Equals", &Matrix4::Equals)

        .addStaticFunction("Decompose", &Matrix4Decompose)

        .addFunction("Inverse", &Matrix4::Inverse)

        .addFunction("ToString", &Matrix4::ToString)

        .addProperty("m00", &Matrix4::m00_)
        .addProperty("m01", &Matrix4::m01_)
        .addProperty("m02", &Matrix4::m02_)
        .addProperty("m03", &Matrix4::m03_)
        .addProperty("m10", &Matrix4::m10_)
        .addProperty("m11", &Matrix4::m11_)
        .addProperty("m12", &Matrix4::m12_)
        .addProperty("m13", &Matrix4::m13_)
        .addProperty("m20", &Matrix4::m20_)
        .addProperty("m21", &Matrix4::m21_)
        .addProperty("m22", &Matrix4::m22_)
        .addProperty("m23", &Matrix4::m23_)
        .addProperty("m30", &Matrix4::m30_)
        .addProperty("m31", &Matrix4::m31_)
        .addProperty("m32", &Matrix4::m32_)
        .addProperty("m33", &Matrix4::m33_)

        .addStaticField("ZERO", &Matrix4::ZERO)
        .addStaticField("IDENTITY", &Matrix4::IDENTITY)
        );
}
}

