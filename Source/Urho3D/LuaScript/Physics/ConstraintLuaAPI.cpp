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

    // [Enum] ConstraintType
    // [Variable] CONSTRAINT_POINT
    lua["CONSTRAINT_POINT"] = CONSTRAINT_POINT;
    // [Variable] CONSTRAINT_HINGE,
    lua["CONSTRAINT_HINGE"] = CONSTRAINT_HINGE;
    // [Variable] CONSTRAINT_SLIDER,
    lua["CONSTRAINT_SLIDER"] = CONSTRAINT_SLIDER;
    // [Variable] CONSTRAINT_CONETWIST
    lua["CONSTRAINT_CONETWIST"] = CONSTRAINT_CONETWIST;

    // [Class] Constraint : Component
    lua["Constraint"].setClass(UserdataMetatable<Constraint, Component>()
        // [Constructor] Constraint()
        .addStaticFunction("new", &CreateObject<Constraint>)

        // [Method] void SetConstraintType(ConstraintType type)
        .addFunction("SetConstraintType", &Constraint::SetConstraintType)
        // [Method] void SetOtherBody(RigidBody* body)
        .addFunction("SetOtherBody", &Constraint::SetOtherBody)
        // [Method] void SetPosition(const Vector3& position)
        .addFunction("SetPosition", &Constraint::SetPosition)
        // [Method] void SetRotation(const Quaternion& rotation)
        .addFunction("SetRotation", &Constraint::SetRotation)
        // [Method] void SetAxis(const Vector3& axis)
        .addFunction("SetAxis", &Constraint::SetAxis)
        // [Method] void SetOtherPosition(const Vector3& position)
        .addFunction("SetOtherPosition", &Constraint::SetOtherPosition)
        // [Method] void SetOtherRotation(const Quaternion& rotation)
        .addFunction("SetOtherRotation", &Constraint::SetOtherRotation)
        // [Method] void SetOtherAxis(const Vector3& axis)
        .addFunction("SetOtherAxis", &Constraint::SetOtherAxis)
        // [Method] void SetWorldPosition(const Vector3& position)
        .addFunction("SetWorldPosition", &Constraint::SetWorldPosition)
        // [Method] void SetHighLimit(const Vector2& limit)
        .addFunction("SetHighLimit", &Constraint::SetHighLimit)
        // [Method] void SetLowLimit(const Vector2& limit)
        .addFunction("SetLowLimit", &Constraint::SetLowLimit)
        // [Method] void SetERP(float erp)
        .addFunction("SetERP", &Constraint::SetERP)
        // [Method] void SetCFM(float cfm)
        .addFunction("SetCFM", &Constraint::SetCFM)
        // [Method] void SetDisableCollision(bool disable)
        .addFunction("SetDisableCollision", &Constraint::SetDisableCollision)
        
        // [Method] PhysicsWorld* GetPhysicsWorld() const
        .addFunction("GetPhysicsWorld", &Constraint::GetPhysicsWorld)
        // [Method] ConstraintType GetConstraintType() const
        .addFunction("GetConstraintType", &Constraint::GetConstraintType)
        // [Method] RigidBody* GetOwnBody() const
        .addFunction("GetOwnBody", &Constraint::GetOwnBody)
        // [Method] RigidBody* GetOtherBody() const
        .addFunction("GetOtherBody", &Constraint::GetOtherBody)
        // [Method] const Vector3& GetPosition() const
        .addFunction("GetPosition", &Constraint::GetPosition)
        // [Method] const Quaternion& GetRotation() const
        .addFunction("GetRotation", &Constraint::GetRotation)
        // [Method] const Vector3& GetOtherPosition() const
        .addFunction("GetOtherPosition", &Constraint::GetOtherPosition)
        // [Method] const Quaternion& GetOtherRotation() const
        .addFunction("GetOtherRotation", &Constraint::GetOtherRotation)
        // [Method] Vector3 GetWorldPosition() const
        .addFunction("GetWorldPosition", &Constraint::GetWorldPosition)
        // [Method] const Vector2& GetHighLimit() const
        .addFunction("GetHighLimit", &Constraint::GetHighLimit)
        // [Method] const Vector2& GetLowLimit() const
        .addFunction("GetLowLimit", &Constraint::GetLowLimit)
        // [Method] float GetERP() const
        .addFunction("GetERP", &Constraint::GetERP)
        // [Method] float GetCFM() const
        .addFunction("GetCFM", &Constraint::GetCFM)
        // [Method] bool GetDisableCollision() const
        .addFunction("GetDisableCollision", &Constraint::GetDisableCollision)
        
        // [Property(ReadOnly)] PhysicsWorld* physicsWorld
        .addProperty("physicsWorld", &Constraint::GetPhysicsWorld)
        // [Property] ConstraintType constraintType
        .addProperty("constraintType", &Constraint::GetConstraintType, &Constraint::SetConstraintType)
        // [Property(ReadOnly)] RigidBody* ownBody
        .addProperty("ownBody", &Constraint::GetOwnBody)
        // [Property] RigidBody* otherBody
        .addProperty("otherBody", &Constraint::GetOtherBody, &Constraint::SetOtherBody)
        // [Property] const Vector3& position
        .addProperty("position", &Constraint::GetPosition, &Constraint::SetPosition)
        // [Property] const Quaternion& rotation
        .addProperty("rotation", &Constraint::GetRotation, &Constraint::SetRotation)

        // [Property(WriteOnly)] const Vector3& axis
        .addProperty("axis", &Constraint::SetAxis)

        // [Property] const Vector3& otherPosition
        .addProperty("otherPosition", &Constraint::GetOtherPosition, &Constraint::SetOtherPosition)
        // [Property] const Quaternion& otherRotation
        .addProperty("otherRotation", &Constraint::GetOtherRotation, &Constraint::SetOtherRotation)

        // Write only property
        // [Property(WriteOnly)] const Vector3& otherAxis
        .addProperty("otherAxis", &Constraint::SetOtherAxis)

        // [Property] Vector3 worldPosition
        .addProperty("worldPosition", &Constraint::GetWorldPosition, &Constraint::SetWorldPosition)
        // [Property] const Vector2& highLimit
        .addProperty("highLimit", &Constraint::GetHighLimit, &Constraint::SetHighLimit)
        // [Property] const Vector2& lowLimit
        .addProperty("lowLimit", &Constraint::GetLowLimit, &Constraint::SetLowLimit)
        // [Property] float ERP
        .addProperty("ERP", &Constraint::GetERP, &Constraint::SetERP)
        // [Property] float CFM
        .addProperty("CFM", &Constraint::GetCFM, &Constraint::SetCFM)
        // [Property] bool disableCollision
        .addProperty("disableCollision", &Constraint::GetDisableCollision, &Constraint::SetDisableCollision)
        );
}
}

#endif
