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

    lua["ConstraintRevolute2D"].setClass(UserdataMetatable<ConstraintRevolute2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintRevolute2D>)

        .addFunction("SetAnchor", &ConstraintRevolute2D::SetAnchor)
        .addFunction("SetEnableLimit", &ConstraintRevolute2D::SetEnableLimit)
        .addFunction("SetLowerAngle", &ConstraintRevolute2D::SetLowerAngle)
        .addFunction("SetUpperAngle", &ConstraintRevolute2D::SetUpperAngle)
        .addFunction("SetEnableMotor", &ConstraintRevolute2D::SetEnableMotor)
        .addFunction("SetMotorSpeed", &ConstraintRevolute2D::SetMotorSpeed)
        .addFunction("SetMaxMotorTorque", &ConstraintRevolute2D::SetMaxMotorTorque)

        .addFunction("GetAnchor", &ConstraintRevolute2D::GetAnchor)
        .addFunction("GetEnableLimit", &ConstraintRevolute2D::GetEnableLimit)
        .addFunction("GetLowerAngle", &ConstraintRevolute2D::GetLowerAngle)
        .addFunction("GetUpperAngle", &ConstraintRevolute2D::GetUpperAngle)
        .addFunction("GetEnableMotor", &ConstraintRevolute2D::GetEnableMotor)
        .addFunction("GetMotorSpeed", &ConstraintRevolute2D::GetMotorSpeed)
        .addFunction("GetMaxMotorTorque", &ConstraintRevolute2D::GetMaxMotorTorque)

        .addProperty("anchor", &ConstraintRevolute2D::GetAnchor, &ConstraintRevolute2D::SetAnchor)
        .addProperty("enableLimit", &ConstraintRevolute2D::GetEnableLimit, &ConstraintRevolute2D::SetEnableLimit)
        .addProperty("lowerAngle", &ConstraintRevolute2D::GetLowerAngle, &ConstraintRevolute2D::SetLowerAngle)
        .addProperty("upperAngle", &ConstraintRevolute2D::GetUpperAngle, &ConstraintRevolute2D::SetUpperAngle)
        .addProperty("enableMotor", &ConstraintRevolute2D::GetEnableMotor, &ConstraintRevolute2D::SetEnableMotor)
        .addProperty("motorSpeed", &ConstraintRevolute2D::GetMotorSpeed, &ConstraintRevolute2D::SetMotorSpeed)
        .addProperty("maxMotorTorque", &ConstraintRevolute2D::GetMaxMotorTorque, &ConstraintRevolute2D::SetMaxMotorTorque)
    );
}
}

#endif
