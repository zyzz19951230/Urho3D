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

    // [Class] ConstraintWheel2D : Constraint2D
    lua["ConstraintWheel2D"].setClass(UserdataMetatable<ConstraintWheel2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintWheel2D>)

        // [Method] void SetAnchor(const Vector2& anchor)
        .addFunction("SetAnchor", &ConstraintWheel2D::SetAnchor)
        // [Method] void SetAxis(const Vector2& axis)
        .addFunction("SetAxis", &ConstraintWheel2D::SetAxis)
        // [Method] void SetEnableMotor(bool enableMotor)
        .addFunction("SetEnableMotor", &ConstraintWheel2D::SetEnableMotor)
        // [Method] void SetMaxMotorTorque(float maxMotorTorque)
        .addFunction("SetMaxMotorTorque", &ConstraintWheel2D::SetMaxMotorTorque)
        // [Method] void SetMotorSpeed(float motorSpeed)
        .addFunction("SetMotorSpeed", &ConstraintWheel2D::SetMotorSpeed)
        // [Method] void SetFrequencyHz(float frequencyHz)
        .addFunction("SetFrequencyHz", &ConstraintWheel2D::SetFrequencyHz)
        // [Method] void SetDampingRatio(float dampingRatio)
        .addFunction("SetDampingRatio", &ConstraintWheel2D::SetDampingRatio)

        // [Method] const Vector2& GetAnchor() const
        .addFunction("GetAnchor", &ConstraintWheel2D::GetAnchor)
        // [Method] const Vector2& GetAxis() const
        .addFunction("GetAxis", &ConstraintWheel2D::GetAxis)
        // [Method] bool GetEnableMotor() const
        .addFunction("GetEnableMotor", &ConstraintWheel2D::GetEnableMotor)
        // [Method] float GetMaxMotorTorque() const
        .addFunction("GetMaxMotorTorque", &ConstraintWheel2D::GetMaxMotorTorque)
        // [Method] float GetMotorSpeed() const
        .addFunction("GetMotorSpeed", &ConstraintWheel2D::GetMotorSpeed)
        // [Method] float GetFrequencyHz() const
        .addFunction("GetFrequencyHz", &ConstraintWheel2D::GetFrequencyHz)
        // [Method] float GetDampingRatio() const
        .addFunction("GetDampingRatio", &ConstraintWheel2D::GetDampingRatio)

        // [Property] const Vector2& anchor
        .addProperty("anchor", &ConstraintWheel2D::GetAnchor, &ConstraintWheel2D::SetAnchor)
        // [Property] const Vector2& axis
        .addProperty("axis", &ConstraintWheel2D::GetAxis, &ConstraintWheel2D::SetAxis)
        // [Property] bool enableMotor
        .addProperty("enableMotor", &ConstraintWheel2D::GetEnableMotor, &ConstraintWheel2D::SetEnableMotor)
        // [Property] float maxMotorTorque
        .addProperty("maxMotorTorque", &ConstraintWheel2D::GetMaxMotorTorque, &ConstraintWheel2D::SetMaxMotorTorque)
        // [Property] float motorSpeed
        .addProperty("motorSpeed", &ConstraintWheel2D::GetMotorSpeed, &ConstraintWheel2D::SetMotorSpeed)
        // [Property] float frequencyHz
        .addProperty("frequencyHz", &ConstraintWheel2D::GetFrequencyHz, &ConstraintWheel2D::SetFrequencyHz)
        // [Property] float dampingRatio
        .addProperty("dampingRatio", &ConstraintWheel2D::GetDampingRatio, &ConstraintWheel2D::SetDampingRatio)
    );
}
}

#endif
