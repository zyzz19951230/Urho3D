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

    lua["Matrix2"].setClass(UserdataMetatable<Matrix2>()
        .setConstructors<Matrix2(),
        Matrix2(const Matrix2&),
        Matrix2(float, float, float, float)>()

        .addFunction("__eq", &Matrix2::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Vector2(Matrix2::*)(const Vector2&) const>(&Matrix2::operator*),
            static_cast<Matrix2(Matrix2::*)(float) const>(&Matrix2::operator*),
            static_cast<Matrix2(Matrix2::*)(const Matrix2&) const>(&Matrix2::operator*))

        .addFunction("__add", &Matrix2::operator+)
        .addFunction("__sub", &Matrix2::operator-)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Matrix2::*)(const Vector2&)>(&Matrix2::SetScale),
            static_cast<void(Matrix2::*)(float)>(&Matrix2::SetScale))

        .addFunction("Scale", &Matrix2::Scale)
        .addFunction("Transpose", &Matrix2::Transpose)
        .addFunction("Scaled", &Matrix2::Scaled)
        .addFunction("Equals", &Matrix2::Equals)
        .addFunction("Inverse", &Matrix2::Inverse)

        .addFunction("ToString", &Matrix2::ToString)

        .addProperty("m00", &Matrix2::m00_)
        .addProperty("m01", &Matrix2::m01_)
        .addProperty("m10", &Matrix2::m10_)
        .addProperty("m11", &Matrix2::m11_)

        .addStaticField("ZERO", &Matrix2::ZERO)
        .addStaticField("IDENTITY", &Matrix2::IDENTITY)
        );
}
}

