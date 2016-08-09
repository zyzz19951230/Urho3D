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

#ifdef URHO3D_URHO2D

#include "../../Precompiled.h"

#include "../../Urho2D/ConstraintRevolute2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintRevolute2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] ConstraintRevolute2D : Constraint2D
    lua["ConstraintRevolute2D"].setClass(UserdataMetatable<ConstraintRevolute2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintRevolute2D>)

        // [Method] void SetAnchor(const Vector2& anchor)
        .addFunction("SetAnchor", &ConstraintRevolute2D::SetAnchor)
        // [Method] void SetEnableLimit(bool enableLimit)
        .addFunction("SetEnableLimit", &ConstraintRevolute2D::SetEnableLimit)
        // [Method] void SetLowerAngle(float lowerAngle)
        .addFunction("SetLowerAngle", &ConstraintRevolute2D::SetLowerAngle)
        // [Method] void SetUpperAngle(float upperAngle)
        .addFunction("SetUpperAngle", &ConstraintRevolute2D::SetUpperAngle)
        // [Method] void SetEnableMotor(bool enableMotor)
        .addFunction("SetEnableMotor", &ConstraintRevolute2D::SetEnableMotor)
        // [Method] void SetMotorSpeed(float motorSpeed)
        .addFunction("SetMotorSpeed", &ConstraintRevolute2D::SetMotorSpeed)
        // [Method] void SetMaxMotorTorque(float maxMotorTorque)
        .addFunction("SetMaxMotorTorque", &ConstraintRevolute2D::SetMaxMotorTorque)

        // [Method] const Vector2& GetAnchor() const
        .addFunction("GetAnchor", &ConstraintRevolute2D::GetAnchor)
        // [Method] bool GetEnableLimit() const
        .addFunction("GetEnableLimit", &ConstraintRevolute2D::GetEnableLimit)
        // [Method] float GetLowerAngle() const
        .addFunction("GetLowerAngle", &ConstraintRevolute2D::GetLowerAngle)
        // [Method] float GetUpperAngle() const
        .addFunction("GetUpperAngle", &ConstraintRevolute2D::GetUpperAngle)
        // [Method] bool GetEnableMotor() const
        .addFunction("GetEnableMotor", &ConstraintRevolute2D::GetEnableMotor)
        // [Method] float GetMotorSpeed() const
        .addFunction("GetMotorSpeed", &ConstraintRevolute2D::GetMotorSpeed)
        // [Method] float GetMaxMotorTorque() const
        .addFunction("GetMaxMotorTorque", &ConstraintRevolute2D::GetMaxMotorTorque)

        // [Property] const Vector2& anchor
        .addProperty("anchor", &ConstraintRevolute2D::GetAnchor, &ConstraintRevolute2D::SetAnchor)
        // [Property] bool enableLimit
        .addProperty("enableLimit", &ConstraintRevolute2D::GetEnableLimit, &ConstraintRevolute2D::SetEnableLimit)
        // [Property] float lowerAngle
        .addProperty("lowerAngle", &ConstraintRevolute2D::GetLowerAngle, &ConstraintRevolute2D::SetLowerAngle)
        // [Property] float upperAngle
        .addProperty("upperAngle", &ConstraintRevolute2D::GetUpperAngle, &ConstraintRevolute2D::SetUpperAngle)
        // [Property] bool enableMotor
        .addProperty("enableMotor", &ConstraintRevolute2D::GetEnableMotor, &ConstraintRevolute2D::SetEnableMotor)
        // [Property] float motorSpeed
        .addProperty("motorSpeed", &ConstraintRevolute2D::GetMotorSpeed, &ConstraintRevolute2D::SetMotorSpeed)
        // [Property] float maxMotorTorque
        .addProperty("maxMotorTorque", &ConstraintRevolute2D::GetMaxMotorTorque, &ConstraintRevolute2D::SetMaxMotorTorque)
    );
}
}

#endif
