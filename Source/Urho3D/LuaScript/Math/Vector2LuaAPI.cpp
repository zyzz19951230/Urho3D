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

#include "../../Math/Vector2.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterVector2(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Vector2
    lua["Vector2"].setClass(UserdataMetatable<Vector2>()
        .setConstructors<Vector2(),
        Vector2(const Vector2&),
        Vector2(float, float)>()

        .addFunction("__eq", &Vector2::operator==)
        .addFunction("__add", &Vector2::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<Vector2(Vector2::*)() const>(&Vector2::operator-),
            static_cast<Vector2(Vector2::*)(const Vector2&) const>(&Vector2::operator-))
        
        .addOverloadedFunctions("__mul",
            static_cast<Vector2(Vector2::*)(float) const>(&Vector2::operator*),
            static_cast<Vector2(Vector2::*)(const Vector2&) const>(&Vector2::operator*))
        
        .addOverloadedFunctions("__div",
            static_cast<Vector2(Vector2::*)(float) const>(&Vector2::operator/),
            static_cast<Vector2(Vector2::*)(const Vector2&) const>(&Vector2::operator/))

        // [Method] void Normalize()
        .addFunction("Normalize", &Vector2::Normalize)
        // [Method] float Length() const
        .addFunction("Length", &Vector2::Length)
        // [Method] float lenSquared = LengthSquared()
        .addFunction("LengthSquared", &Vector2::LengthSquared)
        // [Method] float DotProduct(const Vector2& rhs) const
        .addFunction("DotProduct", &Vector2::DotProduct)
        // [Method] float AbsDotProduct(const Vector2& rhs) const
        .addFunction("AbsDotProduct", &Vector2::AbsDotProduct)
        // [Method] float Angle(const Vector2& rhs) const
        .addFunction("Angle", &Vector2::Angle)
        // [Method] Vector2 Abs() const
        .addFunction("Abs", &Vector2::Abs)
        // [Method] Vector2 Lerp(const Vector2& rhs, float t) const
        .addFunction("Lerp", &Vector2::Lerp)
        // [Method] bool Equals(const Vector2& rhs) const
        .addFunction("Equals", &Vector2::Equals)
        // [Method] bool IsNaN() const
        .addFunction("IsNaN", &Vector2::IsNaN)
        
        // [Method] Vector2 Normalized() const
        .addFunction("Normalized", &Vector2::Normalized)
        // [Method] String ToString() const
        .addFunction("ToString", &Vector2::ToString)

        .addProperty("x", &Vector2::x_)
        .addProperty("y", &Vector2::y_)

        .addStaticField("ZERO", &Vector2::ZERO)
        .addStaticField("LEFT", &Vector2::LEFT)
        .addStaticField("RIGHT", &Vector2::RIGHT)
        .addStaticField("UP", &Vector2::UP)
        .addStaticField("DOWN", &Vector2::DOWN)
        .addStaticField("ONE", &Vector2::ONE)
        );

    // [Class] IntVector2
    lua["IntVector2"].setClass(UserdataMetatable<IntVector2>()
        .setConstructors<IntVector2(),
        IntVector2(int, int),
        IntVector2(const IntVector2&)>()

        .addFunction("__eq", &IntVector2::operator==)
        .addFunction("__add", &IntVector2::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<IntVector2(IntVector2::*)() const>(&IntVector2::operator-),
            static_cast<IntVector2(IntVector2::*)(const IntVector2&) const>(&IntVector2::operator-))

        .addFunction("__mul", &IntVector2::operator*)
        .addFunction("__div", &IntVector2::operator/)

        // [Method] String ToString() const
        .addFunction("ToString", &IntVector2::ToString)

        .addProperty("x", &IntVector2::x_)
        .addProperty("y", &IntVector2::y_)

        .addStaticField("ZERO", &IntVector2::ZERO)
        );
}
}

