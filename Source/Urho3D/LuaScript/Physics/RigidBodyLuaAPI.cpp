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

#include "../../Physics/PhysicsWorld.h"
#include "../../Physics/RigidBody.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <Bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <Bullet/BulletCollision/CollisionShapes/btCompoundShape.h>
#include <kaguya.hpp>

namespace Urho3D
{

static PODVector<RigidBody*> RigidBodyGetCollidingBodies(RigidBody* self)
{
    PODVector<RigidBody*> result;
    self->GetCollidingBodies(result);
    return result;
}

void RegisterRigidBody(kaguya::State& lua)
{
    using namespace kaguya;

    // enum CollisionEventMode;
    lua["COLLISION_NEVER"] = COLLISION_NEVER;
    lua["COLLISION_ACTIVE"] = COLLISION_ACTIVE;
    lua["COLLISION_ALWAYS"] = COLLISION_ALWAYS;

    lua["RigidBody"].setClass(UserdataMetatable<RigidBody, Component>()
        .addStaticFunction("new", &CreateObject<RigidBody>)

        .addFunction("SetMass", &RigidBody::SetMass)
        .addFunction("SetPosition", &RigidBody::SetPosition)
        .addFunction("SetRotation", &RigidBody::SetRotation)
        .addFunction("SetTransform", &RigidBody::SetTransform)
        .addFunction("SetLinearVelocity", &RigidBody::SetLinearVelocity)
        .addFunction("SetLinearFactor", &RigidBody::SetLinearFactor)
        .addFunction("SetLinearRestThreshold", &RigidBody::SetLinearRestThreshold)
        .addFunction("SetLinearDamping", &RigidBody::SetLinearDamping)
        .addFunction("SetAngularVelocity", &RigidBody::SetAngularVelocity)
        .addFunction("SetAngularFactor", &RigidBody::SetAngularFactor)
        .addFunction("SetAngularRestThreshold", &RigidBody::SetAngularRestThreshold)
        .addFunction("SetAngularDamping", &RigidBody::SetAngularDamping)
        .addFunction("SetFriction", &RigidBody::SetFriction)
        .addFunction("SetAnisotropicFriction", &RigidBody::SetAnisotropicFriction)
        .addFunction("SetRollingFriction", &RigidBody::SetRollingFriction)
        .addFunction("SetRestitution", &RigidBody::SetRestitution)
        .addFunction("SetContactProcessingThreshold", &RigidBody::SetContactProcessingThreshold)
        .addFunction("SetCcdRadius", &RigidBody::SetCcdRadius)
        .addFunction("SetCcdMotionThreshold", &RigidBody::SetCcdMotionThreshold)
        .addFunction("SetUseGravity", &RigidBody::SetUseGravity)
        .addFunction("SetGravityOverride", &RigidBody::SetGravityOverride)
        .addFunction("SetKinematic", &RigidBody::SetKinematic)
        .addFunction("SetTrigger", &RigidBody::SetTrigger)
        .addFunction("SetCollisionLayer", &RigidBody::SetCollisionLayer)
        .addFunction("SetCollisionMask", &RigidBody::SetCollisionMask)
        .addFunction("SetCollisionLayerAndMask", &RigidBody::SetCollisionLayerAndMask)
        .addFunction("SetCollisionEventMode", &RigidBody::SetCollisionEventMode)

        .addOverloadedFunctions("ApplyForce",
            static_cast<void(RigidBody::*)(const Vector3&)>(&RigidBody::ApplyForce),
            static_cast<void(RigidBody::*)(const Vector3&, const Vector3&)>(&RigidBody::ApplyForce))

        .addFunction("ApplyTorque", &RigidBody::ApplyTorque)

        .addOverloadedFunctions("ApplyImpulse",
            static_cast<void(RigidBody::*)(const Vector3&)>(&RigidBody::ApplyImpulse),
            static_cast<void(RigidBody::*)(const Vector3&, const Vector3&)>(&RigidBody::ApplyImpulse))

        .addFunction("ApplyTorqueImpulse", &RigidBody::ApplyTorqueImpulse)
        .addFunction("ResetForces", &RigidBody::ResetForces)
        .addFunction("Activate", &RigidBody::Activate)
        .addFunction("ReAddBodyToWorld", &RigidBody::ReAddBodyToWorld)
        .addFunction("DisableMassUpdate", &RigidBody::DisableMassUpdate)
        .addFunction("EnableMassUpdate", &RigidBody::EnableMassUpdate)
        
        .addFunction("GetPhysicsWorld", &RigidBody::GetPhysicsWorld)
        .addFunction("GetBody", &RigidBody::GetBody)
        .addFunction("GetCompoundShape", &RigidBody::GetCompoundShape)
        .addFunction("GetMass", &RigidBody::GetMass)
        .addFunction("GetPosition", &RigidBody::GetPosition)
        .addFunction("GetRotation", &RigidBody::GetRotation)
        .addFunction("GetLinearVelocity", &RigidBody::GetLinearVelocity)
        .addFunction("GetLinearFactor", &RigidBody::GetLinearFactor)
        .addFunction("GetVelocityAtPoint", &RigidBody::GetVelocityAtPoint)
        .addFunction("GetLinearRestThreshold", &RigidBody::GetLinearRestThreshold)
        .addFunction("GetLinearDamping", &RigidBody::GetLinearDamping)
        .addFunction("GetAngularVelocity", &RigidBody::GetAngularVelocity)
        .addFunction("GetAngularFactor", &RigidBody::GetAngularFactor)
        .addFunction("GetAngularRestThreshold", &RigidBody::GetAngularRestThreshold)
        .addFunction("GetAngularDamping", &RigidBody::GetAngularDamping)
        .addFunction("GetFriction", &RigidBody::GetFriction)
        .addFunction("GetAnisotropicFriction", &RigidBody::GetAnisotropicFriction)
        .addFunction("GetRollingFriction", &RigidBody::GetRollingFriction)
        .addFunction("GetRestitution", &RigidBody::GetRestitution)
        .addFunction("GetContactProcessingThreshold", &RigidBody::GetContactProcessingThreshold)
        .addFunction("GetCcdRadius", &RigidBody::GetCcdRadius)
        .addFunction("GetCcdMotionThreshold", &RigidBody::GetCcdMotionThreshold)
        .addFunction("GetUseGravity", &RigidBody::GetUseGravity)
        .addFunction("GetGravityOverride", &RigidBody::GetGravityOverride)
        .addFunction("GetCenterOfMass", &RigidBody::GetCenterOfMass)
        .addFunction("IsKinematic", &RigidBody::IsKinematic)
        .addFunction("IsTrigger", &RigidBody::IsTrigger)
        .addFunction("IsActive", &RigidBody::IsActive)
        .addFunction("GetCollisionLayer", &RigidBody::GetCollisionLayer)
        .addFunction("GetCollisionMask", &RigidBody::GetCollisionMask)
        .addFunction("GetCollisionEventMode", &RigidBody::GetCollisionEventMode)
        
        .addStaticFunction("GetCollidingBodies", &RigidBodyGetCollidingBodies)
        
        .addProperty("physicsWorld", &RigidBody::GetPhysicsWorld)
        .addProperty("body", &RigidBody::GetBody)
        .addProperty("compoundShape", &RigidBody::GetCompoundShape)
        .addProperty("mass", &RigidBody::GetMass, &RigidBody::SetMass)
        .addProperty("position", &RigidBody::GetPosition, &RigidBody::SetPosition)
        .addProperty("rotation", &RigidBody::GetRotation, &RigidBody::SetRotation)
        .addProperty("linearVelocity", &RigidBody::GetLinearVelocity, &RigidBody::SetLinearVelocity)
        .addProperty("linearFactor", &RigidBody::GetLinearFactor, &RigidBody::SetLinearFactor)
        .addProperty("linearRestThreshold", &RigidBody::GetLinearRestThreshold, &RigidBody::SetLinearRestThreshold)
        .addProperty("linearDamping", &RigidBody::GetLinearDamping, &RigidBody::SetLinearDamping)
        .addProperty("angularVelocity", &RigidBody::GetAngularVelocity, &RigidBody::SetAngularVelocity)
        .addProperty("angularFactor", &RigidBody::GetAngularFactor, &RigidBody::SetAngularFactor)
        .addProperty("angularRestThreshold", &RigidBody::GetAngularRestThreshold, &RigidBody::SetAngularRestThreshold)
        .addProperty("angularDamping", &RigidBody::GetAngularDamping, &RigidBody::SetAngularDamping)
        .addProperty("friction", &RigidBody::GetFriction, &RigidBody::SetFriction)
        .addProperty("anisotropicFriction", &RigidBody::GetAnisotropicFriction, &RigidBody::SetAnisotropicFriction)
        .addProperty("rollingFriction", &RigidBody::GetRollingFriction, &RigidBody::SetRollingFriction)
        .addProperty("restitution", &RigidBody::GetRestitution, &RigidBody::SetRestitution)
        .addProperty("contactProcessingThreshold", &RigidBody::GetContactProcessingThreshold, &RigidBody::SetContactProcessingThreshold)
        .addProperty("ccdRadius", &RigidBody::GetCcdRadius, &RigidBody::SetCcdRadius)
        .addProperty("ccdMotionThreshold", &RigidBody::GetCcdMotionThreshold, &RigidBody::SetCcdMotionThreshold)
        .addProperty("useGravity", &RigidBody::GetUseGravity, &RigidBody::SetUseGravity)
        .addProperty("gravityOverride", &RigidBody::GetGravityOverride, &RigidBody::SetGravityOverride)
        .addProperty("centerOfMass", &RigidBody::GetCenterOfMass)
        .addProperty("kinematic", &RigidBody::IsKinematic, &RigidBody::SetKinematic)
        .addProperty("trigger", &RigidBody::IsTrigger, &RigidBody::SetTrigger)
        .addProperty("active", &RigidBody::IsActive)
        .addProperty("collisionLayer", &RigidBody::GetCollisionLayer, &RigidBody::SetCollisionLayer)
        .addProperty("collisionMask", &RigidBody::GetCollisionMask, &RigidBody::SetCollisionMask)
        .addProperty("collisionEventMode", &RigidBody::GetCollisionEventMode, &RigidBody::SetCollisionEventMode)
        );
}
}

#endif
