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

    // [Class] Quaternion
    lua["Quaternion"].setClass(UserdataMetatable<Quaternion>()
        // [Constructor] Quaternion()
        .setConstructors<Quaternion(),
        // [Constructor] Quaternion(const Quaternion& quat)
        Quaternion(const Quaternion&),
        // [Constructor] Quaternion(float w, float x, float y, float z)
        Quaternion(float, float, float, float),
        // [Constructor] Quaternion(float angle, const Vector3& axis)
        Quaternion(float, const Vector3&),
        // [Constructor] Quaternion(float angle)
        Quaternion(float),
        // [Constructor] Quaternion(float x, float y, float z)
        Quaternion(float, float, float),
        // [Constructor] Quaternion(const Vector3& start, const Vector3& end)
        Quaternion(const Vector3&, const Vector3&),
        // [Constructor] Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
        Quaternion(const Vector3&, const Vector3&, const Vector3&),
        // [Constructor] Quaternion(const Matrix3& matrix)
        Quaternion(const Matrix3&)>()

        // [Method] bool operator==(const Quaternion& rhs) const
        .addFunction("__eq", &Quaternion::operator==)

        .addOverloadedFunctions("__mul",
            // [Method] Quaternion operator*(float rhs) const
            static_cast<Quaternion(Quaternion::*)(float) const>(&Quaternion::operator*),
            // [Method] Quaternion operator*(const Quaternion& rhs) const
            static_cast<Quaternion(Quaternion::*)(const Quaternion&) const>(&Quaternion::operator*),
            // [Method] Vector3 operator*(const Vector3& rhs) const
            static_cast<Vector3(Quaternion::*)(const Vector3&) const>(&Quaternion::operator*))

        .addOverloadedFunctions("__sub",
            // [Method] Quaternion operator-() const
            static_cast<Quaternion(Quaternion::*)() const>(&Quaternion::operator-),
            // [Method] Quaternion operator-(const Quaternion& rhs) const
            static_cast<Quaternion(Quaternion::*)(const Quaternion&) const>(&Quaternion::operator-))

        // [Method] Quaternion operator+(const Quaternion& rhs) const
        .addFunction("__add", &Quaternion::operator+)

        // [Method] void FromAngleAxis(float angle, const Vector3& axis)
        .addFunction("FromAngleAxis", &Quaternion::FromAngleAxis)
        // [Method] void FromEulerAngles(float x, float y, float z)
        .addFunction("FromEulerAngles", &Quaternion::FromEulerAngles)
        // [Method] void FromRotationTo(const Vector3& start, const Vector3& end)
        .addFunction("FromRotationTo", &Quaternion::FromRotationTo)
        // [Method] void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
        .addFunction("FromAxes", &Quaternion::FromAxes)
        // [Method] void FromRotationMatrix(const Matrix3& matrix)
        .addFunction("FromRotationMatrix", &Quaternion::FromRotationMatrix)

        // [Method] bool FromLookRotation(const Vector3& direction, const Vector3& up = Vector3::UP)
        .addFunction("FromLookRotation", QuaternionFromLookRotation())

        // [Method] void Normalize()
        .addFunction("Normalize", &Quaternion::Normalize)

        // [Method] Quaternion Normalized() const
        .addFunction("Normalized", &Quaternion::Normalized)
        // [Method] Quaternion Inverse() const
        .addFunction("Inverse", &Quaternion::Inverse)
        // [Method] float lenSquared = LengthSquared()
        .addFunction("LengthSquared", &Quaternion::LengthSquared)
        // [Method] float DotProduct(const Quaternion& rhs) const
        .addFunction("DotProduct", &Quaternion::DotProduct)
        // [Method] bool Equals(const Quaternion& rhs) const
        .addFunction("Equals", &Quaternion::Equals)
        // [Method] bool IsNaN() const
        .addFunction("IsNaN", &Quaternion::IsNaN)

        // [Method] return Conjugate()
        .addFunction("Conjugate", &Quaternion::Conjugate)
        // [Method] Vector3 EulerAngles() const
        .addFunction("EulerAngles", &Quaternion::EulerAngles)
        // [Method] float YawAngle() const
        .addFunction("YawAngle", &Quaternion::YawAngle)
        // [Method] float PitchAngle() const
        .addFunction("PitchAngle", &Quaternion::PitchAngle)
        // [Method] float RollAngle() const
        .addFunction("RollAngle", &Quaternion::RollAngle)
        // [Method] Matrix3 RotationMatrix() const
        .addFunction("RotationMatrix", &Quaternion::RotationMatrix)
        // [Method] Quaternion Slerp(Quaternion rhs, float t) const
        .addFunction("Slerp", &Quaternion::Slerp)

        // [Method] Quaternion Nlerp(Quaternion rhs, float t, bool shortestPath = false) const
        .addFunction("Nlerp", QuaternionNlerp())

        // [Method] String ToString() const
        .addFunction("ToString", &Quaternion::ToString)

        // [Field] float w
        .addProperty("w", &Quaternion::w_)
        // [Field] float x
        .addProperty("x", &Quaternion::x_)
        // [Field] float y
        .addProperty("y", &Quaternion::y_)
        // [Field] float z
        .addProperty("z", &Quaternion::z_)

        // [StaticConstant] Quaternion IDENTITY
        .addStaticField("IDENTITY", &Quaternion::IDENTITY)
        );
}
}

