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

#include "../../Math/Vector3.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterVector3(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Vector3"].setClass(UserdataMetatable<Vector3>()
        .setConstructors<Vector3(),
        Vector3(const Vector3&),
        Vector3(const Vector2&, float),
        Vector3(const Vector2&),
        Vector3(float, float, float),
        Vector3(float, float)>()

        .addFunction("__eq", &Vector3::operator==)
        .addFunction("__add", &Vector3::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<Vector3(Vector3::*)() const>(&Vector3::operator-),
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator-))

        .addOverloadedFunctions("__mul",
            static_cast<Vector3(Vector3::*)(float) const>(&Vector3::operator*),
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator*))

        .addOverloadedFunctions("__div",
            static_cast<Vector3(Vector3::*)(float) const>(&Vector3::operator/),
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator/))

        .addFunction("Normalize", &Vector3::Normalize)
        .addFunction("Length", &Vector3::Length)
        .addFunction("LengthSquared", &Vector3::LengthSquared)
        .addFunction("DotProduct", &Vector3::DotProduct)
        .addFunction("AbsDotProduct", &Vector3::AbsDotProduct)
        .addFunction("CrossProduct", &Vector3::CrossProduct)
        .addFunction("Abs", &Vector3::Abs)
        .addFunction("Lerp", &Vector3::Lerp)
        .addFunction("Equals", &Vector3::Equals)
        .addFunction("Angle", &Vector3::Angle)
        .addFunction("IsNaN", &Vector3::IsNaN)
        .addFunction("Normalized", &Vector3::Normalized)

        .addFunction("ToString", &Vector3::ToString)

        .addProperty("x", &Vector3::x_)
        .addProperty("y", &Vector3::y_)
        .addProperty("z", &Vector3::z_)
        
        .addStaticField("ZERO", &Vector3::ZERO)
        .addStaticField("LEFT", &Vector3::LEFT)
        .addStaticField("RIGHT", &Vector3::RIGHT)
        .addStaticField("UP", &Vector3::UP)
        .addStaticField("DOWN", &Vector3::DOWN)
        .addStaticField("FORWARD", &Vector3::FORWARD)
        .addStaticField("BACK", &Vector3::BACK)
        .addStaticField("ONE", &Vector3::ONE)
        );
}
}

