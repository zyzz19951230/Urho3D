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

    lua["Vector4"].setClass(UserdataMetatable<Vector4>()
        .setConstructors<Vector4(),
        Vector4(const Vector4&),
        Vector4(const Vector3&, float),
        Vector4(float, float, float, float)>()

        .addFunction("__eq", &Vector4::operator==)
        .addFunction("__add", &Vector4::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<Vector4(Vector4::*)() const>(&Vector4::operator-),
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator-))

        .addOverloadedFunctions("__mul",
            static_cast<Vector4(Vector4::*)(float) const>(&Vector4::operator*),
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator*))

        .addOverloadedFunctions("__div",
            static_cast<Vector4(Vector4::*)(float) const>(&Vector4::operator/),
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator/))

        .addFunction("DotProduct", &Vector4::DotProduct)
        .addFunction("AbsDotProduct", &Vector4::AbsDotProduct)
        .addFunction("Abs", &Vector4::Abs)
        .addFunction("Lerp", &Vector4::Lerp)
        .addFunction("Equals", &Vector4::Equals)
        .addFunction("IsNaN", &Vector4::IsNaN)

        .addFunction("ToString", &Vector4::ToString)

        .addProperty("x", &Vector4::x_)
        .addProperty("y", &Vector4::y_)
        .addProperty("z", &Vector4::z_)
        .addProperty("w", &Vector4::w_)

        .addStaticField("ZERO", &Vector4::ZERO)
        .addStaticField("ONE", &Vector4::ONE)
        );
}
}

