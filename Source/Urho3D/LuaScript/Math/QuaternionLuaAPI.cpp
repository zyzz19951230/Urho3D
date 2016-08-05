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

#include "../../Math/Quaternion.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(QuaternionFromLookRotation, Quaternion, FromLookRotation, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(QuaternionNlerp, Quaternion, Nlerp, 2, 3);

void RegisterQuaternion(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Quaternion"].setClass(UserdataMetatable<Quaternion>()
        .setConstructors<Quaternion(),
        Quaternion(const Quaternion&),
        Quaternion(float, float, float, float),
        Quaternion(float, const Vector3&),
        Quaternion(float),
        Quaternion(float, float, float),
        Quaternion(const Vector3&, const Vector3&),
        Quaternion(const Vector3&, const Vector3&, const Vector3&),
        Quaternion(const Matrix3&)>()

        .addFunction("__eq", &Quaternion::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Quaternion(Quaternion::*)(float) const>(&Quaternion::operator*),
            static_cast<Quaternion(Quaternion::*)(const Quaternion&) const>(&Quaternion::operator*),
            static_cast<Vector3(Quaternion::*)(const Vector3&) const>(&Quaternion::operator*))

        .addOverloadedFunctions("__sub",
            static_cast<Quaternion(Quaternion::*)() const>(&Quaternion::operator-),
            static_cast<Quaternion(Quaternion::*)(const Quaternion&) const>(&Quaternion::operator-))

        .addFunction("__add", &Quaternion::operator+)

        .addFunction("FromAngleAxis", &Quaternion::FromAngleAxis)
        .addFunction("FromEulerAngles", &Quaternion::FromEulerAngles)
        .addFunction("FromRotationTo", &Quaternion::FromRotationTo)
        .addFunction("FromAxes", &Quaternion::FromAxes)
        .addFunction("FromRotationMatrix", &Quaternion::FromRotationMatrix)

        .addFunction("FromLookRotation", QuaternionFromLookRotation())

        .addFunction("Normalize", &Quaternion::Normalize)

        .addFunction("Normalized", &Quaternion::Normalized)
        .addFunction("Inverse", &Quaternion::Inverse)
        .addFunction("LengthSquared", &Quaternion::LengthSquared)
        .addFunction("DotProduct", &Quaternion::DotProduct)
        .addFunction("Equals", &Quaternion::Equals)
        .addFunction("IsNaN", &Quaternion::IsNaN)

        .addFunction("Conjugate", &Quaternion::Conjugate)
        .addFunction("EulerAngles", &Quaternion::EulerAngles)
        .addFunction("YawAngle", &Quaternion::YawAngle)
        .addFunction("PitchAngle", &Quaternion::PitchAngle)
        .addFunction("RollAngle", &Quaternion::RollAngle)
        .addFunction("RotationMatrix", &Quaternion::RotationMatrix)
        .addFunction("Slerp", &Quaternion::Slerp)

        .addFunction("Nlerp", QuaternionNlerp())

        .addFunction("ToString", &Quaternion::ToString)

        .addProperty("w", &Quaternion::w_)
        .addProperty("x", &Quaternion::x_)
        .addProperty("y", &Quaternion::y_)
        .addProperty("z", &Quaternion::z_)

        .addStaticField("IDENTITY", &Quaternion::IDENTITY)
        );
}
}

