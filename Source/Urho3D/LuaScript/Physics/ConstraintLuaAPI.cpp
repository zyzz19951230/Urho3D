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

#ifdef URHO3D_PHYSICS

#include "../../Precompiled.h"

#include "../../Physics/Constraint.h"
#include "../../Physics/PhysicsWorld.h"
#include "../../Physics/RigidBody.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraint(kaguya::State& lua)
{
    using namespace kaguya;

    // enum ConstraintType;
    lua["CONSTRAINT_POINT"] = CONSTRAINT_POINT;
    lua["CONSTRAINT_HINGE"] = CONSTRAINT_HINGE;
    lua["CONSTRAINT_SLIDER"] = CONSTRAINT_SLIDER;
    lua["CONSTRAINT_CONETWIST"] = CONSTRAINT_CONETWIST;

    lua["Constraint"].setClass(UserdataMetatable<Constraint, Component>()
        .addStaticFunction("new", &CreateObject<Constraint>)

        .addFunction("SetConstraintType", &Constraint::SetConstraintType)
        .addFunction("SetOtherBody", &Constraint::SetOtherBody)
        .addFunction("SetPosition", &Constraint::SetPosition)
        .addFunction("SetRotation", &Constraint::SetRotation)
        .addFunction("SetAxis", &Constraint::SetAxis)
        .addFunction("SetOtherPosition", &Constraint::SetOtherPosition)
        .addFunction("SetOtherRotation", &Constraint::SetOtherRotation)
        .addFunction("SetOtherAxis", &Constraint::SetOtherAxis)
        .addFunction("SetWorldPosition", &Constraint::SetWorldPosition)
        .addFunction("SetHighLimit", &Constraint::SetHighLimit)
        .addFunction("SetLowLimit", &Constraint::SetLowLimit)
        .addFunction("SetERP", &Constraint::SetERP)
        .addFunction("SetCFM", &Constraint::SetCFM)
        .addFunction("SetDisableCollision", &Constraint::SetDisableCollision)
        
        .addFunction("GetPhysicsWorld", &Constraint::GetPhysicsWorld)
        .addFunction("GetConstraintType", &Constraint::GetConstraintType)
        .addFunction("GetOwnBody", &Constraint::GetOwnBody)
        .addFunction("GetOtherBody", &Constraint::GetOtherBody)
        .addFunction("GetPosition", &Constraint::GetPosition)
        .addFunction("GetRotation", &Constraint::GetRotation)
        .addFunction("GetOtherPosition", &Constraint::GetOtherPosition)
        .addFunction("GetOtherRotation", &Constraint::GetOtherRotation)
        .addFunction("GetWorldPosition", &Constraint::GetWorldPosition)
        .addFunction("GetHighLimit", &Constraint::GetHighLimit)
        .addFunction("GetLowLimit", &Constraint::GetLowLimit)
        .addFunction("GetERP", &Constraint::GetERP)
        .addFunction("GetCFM", &Constraint::GetCFM)
        .addFunction("GetDisableCollision", &Constraint::GetDisableCollision)
        
        .addProperty("physicsWorld", &Constraint::GetPhysicsWorld)
        .addProperty("constraintType", &Constraint::GetConstraintType, &Constraint::SetConstraintType)
        .addProperty("ownBody", &Constraint::GetOwnBody)
        .addProperty("otherBody", &Constraint::GetOtherBody, &Constraint::SetOtherBody)
        .addProperty("position", &Constraint::GetPosition, &Constraint::SetPosition)
        .addProperty("rotation", &Constraint::GetRotation, &Constraint::SetRotation)

		// Write only property
		.addProperty("axis", &Constraint::SetAxis)

        .addProperty("otherPosition", &Constraint::GetOtherPosition, &Constraint::SetOtherPosition)
        .addProperty("otherRotation", &Constraint::GetOtherRotation, &Constraint::SetOtherRotation)

		// Write only property
		.addProperty("otherAxis", &Constraint::SetOtherAxis)

        .addProperty("worldPosition", &Constraint::GetWorldPosition, &Constraint::SetWorldPosition)
        .addProperty("highLimit", &Constraint::GetHighLimit, &Constraint::SetHighLimit)
        .addProperty("lowLimit", &Constraint::GetLowLimit, &Constraint::SetLowLimit)
        .addProperty("ERP", &Constraint::GetERP, &Constraint::SetERP)
        .addProperty("CFM", &Constraint::GetCFM, &Constraint::SetCFM)
        .addProperty("disableCollision", &Constraint::GetDisableCollision, &Constraint::SetDisableCollision)
        );
}
}

#endif
