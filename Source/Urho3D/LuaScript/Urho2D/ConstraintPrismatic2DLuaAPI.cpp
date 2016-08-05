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

#include "../../Urho2D/ConstraintPrismatic2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintPrismatic2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintPrismatic2D"].setClass(UserdataMetatable<ConstraintPrismatic2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintPrismatic2D>)

        .addFunction("SetAnchor", &ConstraintPrismatic2D::SetAnchor)
        .addFunction("SetAxis", &ConstraintPrismatic2D::SetAxis)
        .addFunction("SetEnableLimit", &ConstraintPrismatic2D::SetEnableLimit)
        .addFunction("SetLowerTranslation", &ConstraintPrismatic2D::SetLowerTranslation)
        .addFunction("SetUpperTranslation", &ConstraintPrismatic2D::SetUpperTranslation)
        .addFunction("SetEnableMotor", &ConstraintPrismatic2D::SetEnableMotor)
        .addFunction("SetMaxMotorForce", &ConstraintPrismatic2D::SetMaxMotorForce)
        .addFunction("SetMotorSpeed", &ConstraintPrismatic2D::SetMotorSpeed)

        .addFunction("GetAnchor", &ConstraintPrismatic2D::GetAnchor)
        .addFunction("GetAxis", &ConstraintPrismatic2D::GetAxis)
        .addFunction("GetEnableLimit", &ConstraintPrismatic2D::GetEnableLimit)
        .addFunction("GetLowerTranslation", &ConstraintPrismatic2D::GetLowerTranslation)
        .addFunction("GetUpperTranslation", &ConstraintPrismatic2D::GetUpperTranslation)
        .addFunction("GetEnableMotor", &ConstraintPrismatic2D::GetEnableMotor)
        .addFunction("GetMaxMotorForce", &ConstraintPrismatic2D::GetMaxMotorForce)
        .addFunction("GetMotorSpeed", &ConstraintPrismatic2D::GetMotorSpeed)

        .addProperty("anchor", &ConstraintPrismatic2D::GetAnchor, &ConstraintPrismatic2D::SetAnchor)
        .addProperty("axis", &ConstraintPrismatic2D::GetAxis, &ConstraintPrismatic2D::SetAxis)
        .addProperty("enableLimit", &ConstraintPrismatic2D::GetEnableLimit, &ConstraintPrismatic2D::SetEnableLimit)
        .addProperty("lowerTranslation", &ConstraintPrismatic2D::GetLowerTranslation, &ConstraintPrismatic2D::SetLowerTranslation)
        .addProperty("upperTranslation", &ConstraintPrismatic2D::GetUpperTranslation, &ConstraintPrismatic2D::SetUpperTranslation)
        .addProperty("enableMotor", &ConstraintPrismatic2D::GetEnableMotor, &ConstraintPrismatic2D::SetEnableMotor)
        .addProperty("maxMotorForce", &ConstraintPrismatic2D::GetMaxMotorForce, &ConstraintPrismatic2D::SetMaxMotorForce)
        .addProperty("motorSpeed", &ConstraintPrismatic2D::GetMotorSpeed, &ConstraintPrismatic2D::SetMotorSpeed)
    );
}
}

#endif
