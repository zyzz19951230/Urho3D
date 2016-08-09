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

#include "../../Urho2D/RigidBody2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterRigidBody2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] BodyType2D
    // [Variable] BT_STATIC
    lua["BT_STATIC"] = BT_STATIC;
    // [Variable] BT_KINEMATIC
    lua["BT_KINEMATIC"] = BT_KINEMATIC;
    // [Variable] BT_DYNAMIC
    lua["BT_DYNAMIC"] = BT_DYNAMIC;

    // [Class] RigidBody2D : Component
    lua["RigidBody2D"].setClass(UserdataMetatable<RigidBody2D, Component>()
        .addStaticFunction("new", &CreateObject<RigidBody2D>)

        // [Method] void SetBodyType(BodyType2D bodyType)
        .addFunction("SetBodyType", &RigidBody2D::SetBodyType)
        // [Method] void SetMass(float mass)
        .addFunction("SetMass", &RigidBody2D::SetMass)
        // [Method] void SetInertia(float inertia)
        .addFunction("SetInertia", &RigidBody2D::SetInertia)
        // [Method] void SetMassCenter(const Vector2& center)
        .addFunction("SetMassCenter", &RigidBody2D::SetMassCenter)
        // [Method] void SetUseFixtureMass(bool useFixtureMass)
        .addFunction("SetUseFixtureMass", &RigidBody2D::SetUseFixtureMass)
        // [Method] void SetLinearDamping(float linearDamping)
        .addFunction("SetLinearDamping", &RigidBody2D::SetLinearDamping)
        // [Method] void SetAngularDamping(float angularDamping)
        .addFunction("SetAngularDamping", &RigidBody2D::SetAngularDamping)
        // [Method] void SetAllowSleep(bool allowSleep)
        .addFunction("SetAllowSleep", &RigidBody2D::SetAllowSleep)
        // [Method] void SetFixedRotation(bool fixedRotation)
        .addFunction("SetFixedRotation", &RigidBody2D::SetFixedRotation)
        // [Method] void SetBullet(bool bullet)
        .addFunction("SetBullet", &RigidBody2D::SetBullet)
        // [Method] void SetGravityScale(float gravityScale)
        .addFunction("SetGravityScale", &RigidBody2D::SetGravityScale)
        // [Method] void SetAwake(bool awake)
        .addFunction("SetAwake", &RigidBody2D::SetAwake)
        // [Method] void SetLinearVelocity(const Vector2& linearVelocity)
        .addFunction("SetLinearVelocity", &RigidBody2D::SetLinearVelocity)
        // [Method] void SetAngularVelocity(float angularVelocity)
        .addFunction("SetAngularVelocity", &RigidBody2D::SetAngularVelocity)

        // [Method] void ApplyForce(const Vector2& force, const Vector2& point, bool wake)
        .addFunction("ApplyForce", &RigidBody2D::ApplyForce)
        // [Method] void ApplyForceToCenter(const Vector2& force, bool wake)
        .addFunction("ApplyForceToCenter", &RigidBody2D::ApplyForceToCenter)
        // [Method] void ApplyTorque(float torque, bool wake)
        .addFunction("ApplyTorque", &RigidBody2D::ApplyTorque)
        // [Method] void ApplyLinearImpulse(const Vector2& impulse, const Vector2& point, bool wake)
        .addFunction("ApplyLinearImpulse", &RigidBody2D::ApplyLinearImpulse)
        // [Method] void ApplyAngularImpulse(float impulse, bool wake)
        .addFunction("ApplyAngularImpulse", &RigidBody2D::ApplyAngularImpulse)

        // [Method] BodyType2D GetBodyType() const
        .addFunction("GetBodyType", &RigidBody2D::GetBodyType)
        // [Method] float GetMass() const
        .addFunction("GetMass", &RigidBody2D::GetMass)
        // [Method] float GetInertia() const
        .addFunction("GetInertia", &RigidBody2D::GetInertia)
        // [Method] Vector2 GetMassCenter() const
        .addFunction("GetMassCenter", &RigidBody2D::GetMassCenter)
        // [Method] bool GetUseFixtureMass() const
        .addFunction("GetUseFixtureMass", &RigidBody2D::GetUseFixtureMass)
        // [Method] float GetLinearDamping() const
        .addFunction("GetLinearDamping", &RigidBody2D::GetLinearDamping)
        // [Method] float GetAngularDamping() const
        .addFunction("GetAngularDamping", &RigidBody2D::GetAngularDamping)

        // [Method] bool IsAllowSleep() const
        .addFunction("IsAllowSleep", &RigidBody2D::IsAllowSleep)
        // [Method] bool IsFixedRotation() const
        .addFunction("IsFixedRotation", &RigidBody2D::IsFixedRotation)
        // [Method] bool IsBullet() const
        .addFunction("IsBullet", &RigidBody2D::IsBullet)
        // [Method] float GetGravityScale() const
        .addFunction("GetGravityScale", &RigidBody2D::GetGravityScale)
        // [Method] bool IsAwake() const
        .addFunction("IsAwake", &RigidBody2D::IsAwake)
        // [Method] Vector2 GetLinearVelocity() const
        .addFunction("GetLinearVelocity", &RigidBody2D::GetLinearVelocity)
        // [Method] float GetAngularVelocity() const
        .addFunction("GetAngularVelocity", &RigidBody2D::GetAngularVelocity)

        // [Property] BodyType2D bodyType
        .addProperty("bodyType", &RigidBody2D::GetBodyType, &RigidBody2D::SetBodyType)
        // [Property] float mass
        .addProperty("mass", &RigidBody2D::GetMass, &RigidBody2D::SetMass)
        // [Property] float inertia
        .addProperty("inertia", &RigidBody2D::GetInertia, &RigidBody2D::SetInertia)
        // [Property] Vector2 massCenter
        .addProperty("massCenter", &RigidBody2D::GetMassCenter, &RigidBody2D::SetMassCenter)
        // [Property] bool useFixtureMass
        .addProperty("useFixtureMass", &RigidBody2D::GetUseFixtureMass, &RigidBody2D::SetUseFixtureMass)
        // [Property] float linearDamping
        .addProperty("linearDamping", &RigidBody2D::GetLinearDamping, &RigidBody2D::SetLinearDamping)
        // [Property] float angularDamping
        .addProperty("angularDamping", &RigidBody2D::GetAngularDamping, &RigidBody2D::SetAngularDamping)
        // [Property] bool allowSleep
        .addProperty("allowSleep", &RigidBody2D::IsAllowSleep, &RigidBody2D::SetAllowSleep)
        // [Property] bool fixedRotation
        .addProperty("fixedRotation", &RigidBody2D::IsFixedRotation, &RigidBody2D::SetFixedRotation)
        // [Property] bool bullet
        .addProperty("bullet", &RigidBody2D::IsBullet, &RigidBody2D::SetBullet)
        // [Property] float gravityScale
        .addProperty("gravityScale", &RigidBody2D::GetGravityScale, &RigidBody2D::SetGravityScale)
        // [Property] bool awake
        .addProperty("awake", &RigidBody2D::IsAwake, &RigidBody2D::SetAwake)
        // [Property] Vector2 linearVelocity
        .addProperty("linearVelocity", &RigidBody2D::GetLinearVelocity, &RigidBody2D::SetLinearVelocity)
        // [Property] float angularVelocity
        .addProperty("angularVelocity", &RigidBody2D::GetAngularVelocity, &RigidBody2D::SetAngularVelocity)
    );
}
}

#endif
