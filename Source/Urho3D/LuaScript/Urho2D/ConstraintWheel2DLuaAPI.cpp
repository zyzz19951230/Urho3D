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

#include "../../Urho2D/ConstraintWheel2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintWheel2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintWheel2D"].setClass(UserdataMetatable<ConstraintWheel2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintWheel2D>)

        .addFunction("SetAnchor", &ConstraintWheel2D::SetAnchor)
        .addFunction("SetAxis", &ConstraintWheel2D::SetAxis)
        .addFunction("SetEnableMotor", &ConstraintWheel2D::SetEnableMotor)
        .addFunction("SetMaxMotorTorque", &ConstraintWheel2D::SetMaxMotorTorque)
        .addFunction("SetMotorSpeed", &ConstraintWheel2D::SetMotorSpeed)
        .addFunction("SetFrequencyHz", &ConstraintWheel2D::SetFrequencyHz)
        .addFunction("SetDampingRatio", &ConstraintWheel2D::SetDampingRatio)

        .addFunction("GetAnchor", &ConstraintWheel2D::GetAnchor)
        .addFunction("GetAxis", &ConstraintWheel2D::GetAxis)
        .addFunction("GetEnableMotor", &ConstraintWheel2D::GetEnableMotor)
        .addFunction("GetMaxMotorTorque", &ConstraintWheel2D::GetMaxMotorTorque)
        .addFunction("GetMotorSpeed", &ConstraintWheel2D::GetMotorSpeed)
        .addFunction("GetFrequencyHz", &ConstraintWheel2D::GetFrequencyHz)
        .addFunction("GetDampingRatio", &ConstraintWheel2D::GetDampingRatio)

        .addProperty("anchor", &ConstraintWheel2D::GetAnchor, &ConstraintWheel2D::SetAnchor)
        .addProperty("axis", &ConstraintWheel2D::GetAxis, &ConstraintWheel2D::SetAxis)
        .addProperty("enableMotor", &ConstraintWheel2D::GetEnableMotor, &ConstraintWheel2D::SetEnableMotor)
        .addProperty("maxMotorTorque", &ConstraintWheel2D::GetMaxMotorTorque, &ConstraintWheel2D::SetMaxMotorTorque)
        .addProperty("motorSpeed", &ConstraintWheel2D::GetMotorSpeed, &ConstraintWheel2D::SetMotorSpeed)
        .addProperty("frequencyHz", &ConstraintWheel2D::GetFrequencyHz, &ConstraintWheel2D::SetFrequencyHz)
        .addProperty("dampingRatio", &ConstraintWheel2D::GetDampingRatio, &ConstraintWheel2D::SetDampingRatio)
    );
}
}

#endif
