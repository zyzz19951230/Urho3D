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

    // [Class] ConstraintPrismatic2D : Constraint2D
    lua["ConstraintPrismatic2D"].setClass(UserdataMetatable<ConstraintPrismatic2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintPrismatic2D>)

        // [Method] void SetAnchor(const Vector2& anchor)
        .addFunction("SetAnchor", &ConstraintPrismatic2D::SetAnchor)
        // [Method] void SetAxis(const Vector2& axis)
        .addFunction("SetAxis", &ConstraintPrismatic2D::SetAxis)
        // [Method] void SetEnableLimit(bool enableLimit)
        .addFunction("SetEnableLimit", &ConstraintPrismatic2D::SetEnableLimit)
        // [Method] void SetLowerTranslation(float lowerTranslation)
        .addFunction("SetLowerTranslation", &ConstraintPrismatic2D::SetLowerTranslation)
        // [Method] void SetUpperTranslation(float upperTranslation)
        .addFunction("SetUpperTranslation", &ConstraintPrismatic2D::SetUpperTranslation)
        // [Method] void SetEnableMotor(bool enableMotor)
        .addFunction("SetEnableMotor", &ConstraintPrismatic2D::SetEnableMotor)
        // [Method] void SetMaxMotorForce(float maxMotorForce)
        .addFunction("SetMaxMotorForce", &ConstraintPrismatic2D::SetMaxMotorForce)
        // [Method] void SetMotorSpeed(float motorSpeed)
        .addFunction("SetMotorSpeed", &ConstraintPrismatic2D::SetMotorSpeed)

        // [Method] const Vector2& GetAnchor() const
        .addFunction("GetAnchor", &ConstraintPrismatic2D::GetAnchor)
        // [Method] const Vector2& GetAxis() const
        .addFunction("GetAxis", &ConstraintPrismatic2D::GetAxis)
        // [Method] bool GetEnableLimit() const
        .addFunction("GetEnableLimit", &ConstraintPrismatic2D::GetEnableLimit)
        // [Method] float GetLowerTranslation() const
        .addFunction("GetLowerTranslation", &ConstraintPrismatic2D::GetLowerTranslation)
        // [Method] float GetUpperTranslation() const
        .addFunction("GetUpperTranslation", &ConstraintPrismatic2D::GetUpperTranslation)
        // [Method] bool GetEnableMotor() const
        .addFunction("GetEnableMotor", &ConstraintPrismatic2D::GetEnableMotor)
        // [Method] float GetMaxMotorForce() const
        .addFunction("GetMaxMotorForce", &ConstraintPrismatic2D::GetMaxMotorForce)
        // [Method] float GetMotorSpeed() const
        .addFunction("GetMotorSpeed", &ConstraintPrismatic2D::GetMotorSpeed)

        // [Property] const Vector2& anchor
        .addProperty("anchor", &ConstraintPrismatic2D::GetAnchor, &ConstraintPrismatic2D::SetAnchor)
        // [Property] const Vector2& axis
        .addProperty("axis", &ConstraintPrismatic2D::GetAxis, &ConstraintPrismatic2D::SetAxis)
        // [Property] bool enableLimit
        .addProperty("enableLimit", &ConstraintPrismatic2D::GetEnableLimit, &ConstraintPrismatic2D::SetEnableLimit)
        // [Property] float lowerTranslation
        .addProperty("lowerTranslation", &ConstraintPrismatic2D::GetLowerTranslation, &ConstraintPrismatic2D::SetLowerTranslation)
        // [Property] float upperTranslation
        .addProperty("upperTranslation", &ConstraintPrismatic2D::GetUpperTranslation, &ConstraintPrismatic2D::SetUpperTranslation)
        // [Property] bool enableMotor
        .addProperty("enableMotor", &ConstraintPrismatic2D::GetEnableMotor, &ConstraintPrismatic2D::SetEnableMotor)
        // [Property] float maxMotorForce
        .addProperty("maxMotorForce", &ConstraintPrismatic2D::GetMaxMotorForce, &ConstraintPrismatic2D::SetMaxMotorForce)
        // [Property] float motorSpeed
        .addProperty("motorSpeed", &ConstraintPrismatic2D::GetMotorSpeed, &ConstraintPrismatic2D::SetMotorSpeed)
    );
}
}

#endif
