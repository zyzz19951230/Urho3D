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

#include "../../Urho2D/ConstraintMotor2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintMotor2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintMotor2D"].setClass(UserdataMetatable<ConstraintMotor2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintMotor2D>)

        .addFunction("SetLinearOffset", &ConstraintMotor2D::SetLinearOffset)
        .addFunction("SetAngularOffset", &ConstraintMotor2D::SetAngularOffset)
        .addFunction("SetMaxForce", &ConstraintMotor2D::SetMaxForce)
        .addFunction("SetMaxTorque", &ConstraintMotor2D::SetMaxTorque)
        .addFunction("SetCorrectionFactor", &ConstraintMotor2D::SetCorrectionFactor)

        .addFunction("GetLinearOffset", &ConstraintMotor2D::GetLinearOffset)
        .addFunction("GetAngularOffset", &ConstraintMotor2D::GetAngularOffset)
        .addFunction("GetMaxForce", &ConstraintMotor2D::GetMaxForce)
        .addFunction("GetMaxTorque", &ConstraintMotor2D::GetMaxTorque)
        .addFunction("GetCorrectionFactor", &ConstraintMotor2D::GetCorrectionFactor)

        .addProperty("linearOffset", &ConstraintMotor2D::GetLinearOffset, &ConstraintMotor2D::SetLinearOffset)
        .addProperty("angularOffset", &ConstraintMotor2D::GetAngularOffset, &ConstraintMotor2D::SetAngularOffset)
        .addProperty("maxForce", &ConstraintMotor2D::GetMaxForce, &ConstraintMotor2D::SetMaxForce)
        .addProperty("maxTorque", &ConstraintMotor2D::GetMaxTorque, &ConstraintMotor2D::SetMaxTorque)
        .addProperty("correctionFactor", &ConstraintMotor2D::GetCorrectionFactor, &ConstraintMotor2D::SetCorrectionFactor)
    );
}
}

#endif
