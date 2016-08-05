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

    // enum BodyType2D;
    lua["BT_STATIC"] = BT_STATIC;
    lua["BT_KINEMATIC"] = BT_KINEMATIC;
    lua["BT_DYNAMIC"] = BT_DYNAMIC;

    lua["RigidBody2D"].setClass(UserdataMetatable<RigidBody2D, Component>()
        .addStaticFunction("new", &CreateObject<RigidBody2D>)

        .addFunction("SetBodyType", &RigidBody2D::SetBodyType)
        .addFunction("SetMass", &RigidBody2D::SetMass)
        .addFunction("SetInertia", &RigidBody2D::SetInertia)
        .addFunction("SetMassCenter", &RigidBody2D::SetMassCenter)
        .addFunction("SetUseFixtureMass", &RigidBody2D::SetUseFixtureMass)
        .addFunction("SetLinearDamping", &RigidBody2D::SetLinearDamping)
        .addFunction("SetAngularDamping", &RigidBody2D::SetAngularDamping)
        .addFunction("SetAllowSleep", &RigidBody2D::SetAllowSleep)
        .addFunction("SetFixedRotation", &RigidBody2D::SetFixedRotation)
        .addFunction("SetBullet", &RigidBody2D::SetBullet)
        .addFunction("SetGravityScale", &RigidBody2D::SetGravityScale)
        .addFunction("SetAwake", &RigidBody2D::SetAwake)
        .addFunction("SetLinearVelocity", &RigidBody2D::SetLinearVelocity)
        .addFunction("SetAngularVelocity", &RigidBody2D::SetAngularVelocity)

        .addFunction("ApplyForce", &RigidBody2D::ApplyForce)
        .addFunction("ApplyForceToCenter", &RigidBody2D::ApplyForceToCenter)
        .addFunction("ApplyTorque", &RigidBody2D::ApplyTorque)
        .addFunction("ApplyLinearImpulse", &RigidBody2D::ApplyLinearImpulse)
        .addFunction("ApplyAngularImpulse", &RigidBody2D::ApplyAngularImpulse)

        .addFunction("GetBodyType", &RigidBody2D::GetBodyType)
        .addFunction("GetMass", &RigidBody2D::GetMass)
        .addFunction("GetInertia", &RigidBody2D::GetInertia)
        .addFunction("GetMassCenter", &RigidBody2D::GetMassCenter)
        .addFunction("GetUseFixtureMass", &RigidBody2D::GetUseFixtureMass)
        .addFunction("GetLinearDamping", &RigidBody2D::GetLinearDamping)
        .addFunction("GetAngularDamping", &RigidBody2D::GetAngularDamping)

        .addFunction("IsAllowSleep", &RigidBody2D::IsAllowSleep)
        .addFunction("IsFixedRotation", &RigidBody2D::IsFixedRotation)
        .addFunction("IsBullet", &RigidBody2D::IsBullet)
        .addFunction("GetGravityScale", &RigidBody2D::GetGravityScale)
        .addFunction("IsAwake", &RigidBody2D::IsAwake)
        .addFunction("GetLinearVelocity", &RigidBody2D::GetLinearVelocity)
        .addFunction("GetAngularVelocity", &RigidBody2D::GetAngularVelocity)

        .addProperty("bodyType", &RigidBody2D::GetBodyType, &RigidBody2D::SetBodyType)
        .addProperty("mass", &RigidBody2D::GetMass, &RigidBody2D::SetMass)
        .addProperty("inertia", &RigidBody2D::GetInertia, &RigidBody2D::SetInertia)
        .addProperty("massCenter", &RigidBody2D::GetMassCenter, &RigidBody2D::SetMassCenter)
        .addProperty("useFixtureMass", &RigidBody2D::GetUseFixtureMass, &RigidBody2D::SetUseFixtureMass)
        .addProperty("linearDamping", &RigidBody2D::GetLinearDamping, &RigidBody2D::SetLinearDamping)
        .addProperty("angularDamping", &RigidBody2D::GetAngularDamping, &RigidBody2D::SetAngularDamping)
        .addProperty("allowSleep", &RigidBody2D::IsAllowSleep, &RigidBody2D::SetAllowSleep)
        .addProperty("fixedRotation", &RigidBody2D::IsFixedRotation, &RigidBody2D::SetFixedRotation)
        .addProperty("bullet", &RigidBody2D::IsBullet, &RigidBody2D::SetBullet)
        .addProperty("gravityScale", &RigidBody2D::GetGravityScale, &RigidBody2D::SetGravityScale)
        .addProperty("awake", &RigidBody2D::IsAwake, &RigidBody2D::SetAwake)
        .addProperty("linearVelocity", &RigidBody2D::GetLinearVelocity, &RigidBody2D::SetLinearVelocity)
        .addProperty("angularVelocity", &RigidBody2D::GetAngularVelocity, &RigidBody2D::SetAngularVelocity)
    );
}
}

#endif
