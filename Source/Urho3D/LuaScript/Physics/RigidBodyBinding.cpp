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

    // [Enum] CollisionEventMode
    lua["COLLISION_NEVER"] = COLLISION_NEVER;
    lua["COLLISION_ACTIVE"] = COLLISION_ACTIVE;
    lua["COLLISION_ALWAYS"] = COLLISION_ALWAYS;

    // [Class] RigidBody : Component
    lua["RigidBody"].setClass(UserdataMetatable<RigidBody, Component>()
        // [Constructor] RigidBody()
        .addStaticFunction("new", &CreateObject<RigidBody>)

        // [Method] void SetMass(float mass)
        .addFunction("SetMass", &RigidBody::SetMass)
        // [Method] void SetPosition(const Vector3& position)
        .addFunction("SetPosition", &RigidBody::SetPosition)
        // [Method] void SetRotation(const Quaternion& rotation)
        .addFunction("SetRotation", &RigidBody::SetRotation)
        // [Method] void SetTransform(const Vector3& position, const Quaternion& rotation)
        .addFunction("SetTransform", &RigidBody::SetTransform)
        // [Method] void SetLinearVelocity(const Vector3& velocity)
        .addFunction("SetLinearVelocity", &RigidBody::SetLinearVelocity)
        // [Method] void SetLinearFactor(const Vector3& factor)
        .addFunction("SetLinearFactor", &RigidBody::SetLinearFactor)
        // [Method] void SetLinearRestThreshold(float threshold)
        .addFunction("SetLinearRestThreshold", &RigidBody::SetLinearRestThreshold)
        // [Method] void SetLinearDamping(float damping)
        .addFunction("SetLinearDamping", &RigidBody::SetLinearDamping)
        // [Method] void SetAngularVelocity(const Vector3& angularVelocity)
        .addFunction("SetAngularVelocity", &RigidBody::SetAngularVelocity)
        // [Method] void SetAngularFactor(const Vector3& factor)
        .addFunction("SetAngularFactor", &RigidBody::SetAngularFactor)
        // [Method] void SetAngularRestThreshold(float threshold)
        .addFunction("SetAngularRestThreshold", &RigidBody::SetAngularRestThreshold)
        // [Method] void SetAngularDamping(float factor)
        .addFunction("SetAngularDamping", &RigidBody::SetAngularDamping)
        // [Method] void SetFriction(float friction)
        .addFunction("SetFriction", &RigidBody::SetFriction)
        // [Method] void SetAnisotropicFriction(const Vector3& friction)
        .addFunction("SetAnisotropicFriction", &RigidBody::SetAnisotropicFriction)
        // [Method] void SetRollingFriction(float friction)
        .addFunction("SetRollingFriction", &RigidBody::SetRollingFriction)
        // [Method] void SetRestitution(float restitution)
        .addFunction("SetRestitution", &RigidBody::SetRestitution)
        // [Method] void SetContactProcessingThreshold(float threshold)
        .addFunction("SetContactProcessingThreshold", &RigidBody::SetContactProcessingThreshold)
        // [Method] void SetCcdRadius(float radius)
        .addFunction("SetCcdRadius", &RigidBody::SetCcdRadius)
        // [Method] void SetCcdMotionThreshold(float threshold)
        .addFunction("SetCcdMotionThreshold", &RigidBody::SetCcdMotionThreshold)
        // [Method] void SetUseGravity(bool enable)
        .addFunction("SetUseGravity", &RigidBody::SetUseGravity)
        // [Method] void SetGravityOverride(const Vector3& gravity)
        .addFunction("SetGravityOverride", &RigidBody::SetGravityOverride)
        // [Method] void SetKinematic(bool enable)
        .addFunction("SetKinematic", &RigidBody::SetKinematic)
        // [Method] void SetTrigger(bool enable)
        .addFunction("SetTrigger", &RigidBody::SetTrigger)
        // [Method] void SetCollisionLayer(unsigned layer)
        .addFunction("SetCollisionLayer", &RigidBody::SetCollisionLayer)
        // [Method] void SetCollisionMask(unsigned mask)
        .addFunction("SetCollisionMask", &RigidBody::SetCollisionMask)
        // [Method] void SetCollisionLayerAndMask(unsigned layer, unsigned mask)
        .addFunction("SetCollisionLayerAndMask", &RigidBody::SetCollisionLayerAndMask)
        // [Method] void SetCollisionEventMode(CollisionEventMode mode)
        .addFunction("SetCollisionEventMode", &RigidBody::SetCollisionEventMode)

        .addOverloadedFunctions("ApplyForce",
            // [Method] void ApplyForce(const Vector3& force)
            static_cast<void(RigidBody::*)(const Vector3&)>(&RigidBody::ApplyForce),
            // [Method] void ApplyForce(const Vector3& force, const Vector3& position)
            static_cast<void(RigidBody::*)(const Vector3&, const Vector3&)>(&RigidBody::ApplyForce))

        // [Method] void ApplyTorque(const Vector3& torque)
        .addFunction("ApplyTorque", &RigidBody::ApplyTorque)

        .addOverloadedFunctions("ApplyImpulse",
            // [Method] void ApplyImpulse(const Vector3& impulse)
            static_cast<void(RigidBody::*)(const Vector3&)>(&RigidBody::ApplyImpulse),
            // [Method] void ApplyImpulse(const Vector3& impulse, const Vector3& position)
            static_cast<void(RigidBody::*)(const Vector3&, const Vector3&)>(&RigidBody::ApplyImpulse))

        // [Method] void ApplyTorqueImpulse(const Vector3& torque)
        .addFunction("ApplyTorqueImpulse", &RigidBody::ApplyTorqueImpulse)
        // [Method] void ResetForces()
        .addFunction("ResetForces", &RigidBody::ResetForces)
        // [Method] void Activate()
        .addFunction("Activate", &RigidBody::Activate)
        // [Method] void ReAddBodyToWorld()
        .addFunction("ReAddBodyToWorld", &RigidBody::ReAddBodyToWorld)
        // [Method] void DisableMassUpdate()
        .addFunction("DisableMassUpdate", &RigidBody::DisableMassUpdate)
        // [Method] void EnableMassUpdate()
        .addFunction("EnableMassUpdate", &RigidBody::EnableMassUpdate)
        
        // [Method] PhysicsWorld* GetPhysicsWorld() const
        .addFunction("GetPhysicsWorld", &RigidBody::GetPhysicsWorld)
        // [Method] btRigidBody* GetBody() const
        .addFunction("GetBody", &RigidBody::GetBody)
        // [Method] btCompoundShape* GetCompoundShape() const
        .addFunction("GetCompoundShape", &RigidBody::GetCompoundShape)
        // [Method] float GetMass() const
        .addFunction("GetMass", &RigidBody::GetMass)
        // [Method] Vector3 GetPosition() const
        .addFunction("GetPosition", &RigidBody::GetPosition)
        // [Method] Quaternion GetRotation() const
        .addFunction("GetRotation", &RigidBody::GetRotation)
        // [Method] Vector3 GetLinearVelocity() const
        .addFunction("GetLinearVelocity", &RigidBody::GetLinearVelocity)
        // [Method] Vector3 GetLinearFactor() const
        .addFunction("GetLinearFactor", &RigidBody::GetLinearFactor)
        // [Method] Vector3 GetVelocityAtPoint(const Vector3& position) const
        .addFunction("GetVelocityAtPoint", &RigidBody::GetVelocityAtPoint)
        // [Method] float GetLinearRestThreshold() const
        .addFunction("GetLinearRestThreshold", &RigidBody::GetLinearRestThreshold)
        // [Method] float GetLinearDamping() const
        .addFunction("GetLinearDamping", &RigidBody::GetLinearDamping)
        // [Method] Vector3 GetAngularVelocity() const
        .addFunction("GetAngularVelocity", &RigidBody::GetAngularVelocity)
        // [Method] Vector3 GetAngularFactor() const
        .addFunction("GetAngularFactor", &RigidBody::GetAngularFactor)
        // [Method] float GetAngularRestThreshold() const
        .addFunction("GetAngularRestThreshold", &RigidBody::GetAngularRestThreshold)
        // [Method] float GetAngularDamping() const
        .addFunction("GetAngularDamping", &RigidBody::GetAngularDamping)
        // [Method] float GetFriction() const
        .addFunction("GetFriction", &RigidBody::GetFriction)
        // [Method] Vector3 GetAnisotropicFriction() const
        .addFunction("GetAnisotropicFriction", &RigidBody::GetAnisotropicFriction)
        // [Method] float GetRollingFriction() const
        .addFunction("GetRollingFriction", &RigidBody::GetRollingFriction)
        // [Method] float GetRestitution() const
        .addFunction("GetRestitution", &RigidBody::GetRestitution)
        // [Method] float GetContactProcessingThreshold() const
        .addFunction("GetContactProcessingThreshold", &RigidBody::GetContactProcessingThreshold)
        // [Method] float GetCcdRadius() const
        .addFunction("GetCcdRadius", &RigidBody::GetCcdRadius)
        // [Method] float GetCcdMotionThreshold() const
        .addFunction("GetCcdMotionThreshold", &RigidBody::GetCcdMotionThreshold)
        // [Method] bool GetUseGravity() const
        .addFunction("GetUseGravity", &RigidBody::GetUseGravity)
        // [Method] const Vector3& GetGravityOverride() const
        .addFunction("GetGravityOverride", &RigidBody::GetGravityOverride)
        // [Method] const Vector3& GetCenterOfMass() const
        .addFunction("GetCenterOfMass", &RigidBody::GetCenterOfMass)
        // [Method] bool IsKinematic() const
        .addFunction("IsKinematic", &RigidBody::IsKinematic)
        // [Method] bool IsTrigger() const
        .addFunction("IsTrigger", &RigidBody::IsTrigger)
        // [Method] bool IsActive() const
        .addFunction("IsActive", &RigidBody::IsActive)
        // [Method] unsigned GetCollisionLayer() const
        .addFunction("GetCollisionLayer", &RigidBody::GetCollisionLayer)
        // [Method] unsigned GetCollisionMask() const
        .addFunction("GetCollisionMask", &RigidBody::GetCollisionMask)
        // [Method] CollisionEventMode GetCollisionEventMode() const
        .addFunction("GetCollisionEventMode", &RigidBody::GetCollisionEventMode)
        
        // [Method] PODVector<RigidBody*> GetCollidingBodies()
        .addStaticFunction("GetCollidingBodies", &RigidBodyGetCollidingBodies)
        
        // [Property(Readonly)] PhysicsWorld* physicsWorld
        .addProperty("physicsWorld", &RigidBody::GetPhysicsWorld)
        // [Property(Readonly)] btRigidBody* body
        .addProperty("body", &RigidBody::GetBody)
        // [Property(Readonly)] btCompoundShape* compoundShape
        .addProperty("compoundShape", &RigidBody::GetCompoundShape)
        // [Property] float mass
        .addProperty("mass", &RigidBody::GetMass, &RigidBody::SetMass)
        // [Property] Vector3 position
        .addProperty("position", &RigidBody::GetPosition, &RigidBody::SetPosition)
        // [Property] Quaternion rotation
        .addProperty("rotation", &RigidBody::GetRotation, &RigidBody::SetRotation)
        // [Property] Vector3 linearVelocity
        .addProperty("linearVelocity", &RigidBody::GetLinearVelocity, &RigidBody::SetLinearVelocity)
        // [Property] Vector3 linearFactor
        .addProperty("linearFactor", &RigidBody::GetLinearFactor, &RigidBody::SetLinearFactor)
        // [Property] float linearRestThreshold
        .addProperty("linearRestThreshold", &RigidBody::GetLinearRestThreshold, &RigidBody::SetLinearRestThreshold)
        // [Property] float linearDamping
        .addProperty("linearDamping", &RigidBody::GetLinearDamping, &RigidBody::SetLinearDamping)
        // [Property] Vector3 angularVelocity
        .addProperty("angularVelocity", &RigidBody::GetAngularVelocity, &RigidBody::SetAngularVelocity)
        // [Property] Vector3 angularFactor
        .addProperty("angularFactor", &RigidBody::GetAngularFactor, &RigidBody::SetAngularFactor)
        // [Property] float angularRestThreshold
        .addProperty("angularRestThreshold", &RigidBody::GetAngularRestThreshold, &RigidBody::SetAngularRestThreshold)
        // [Property] float angularDamping
        .addProperty("angularDamping", &RigidBody::GetAngularDamping, &RigidBody::SetAngularDamping)
        // [Property] float friction
        .addProperty("friction", &RigidBody::GetFriction, &RigidBody::SetFriction)
        // [Property] Vector3 anisotropicFriction
        .addProperty("anisotropicFriction", &RigidBody::GetAnisotropicFriction, &RigidBody::SetAnisotropicFriction)
        // [Property] float rollingFriction
        .addProperty("rollingFriction", &RigidBody::GetRollingFriction, &RigidBody::SetRollingFriction)
        // [Property] float restitution
        .addProperty("restitution", &RigidBody::GetRestitution, &RigidBody::SetRestitution)
        // [Property] float contactProcessingThreshold
        .addProperty("contactProcessingThreshold", &RigidBody::GetContactProcessingThreshold, &RigidBody::SetContactProcessingThreshold)
        // [Property] float ccdRadius
        .addProperty("ccdRadius", &RigidBody::GetCcdRadius, &RigidBody::SetCcdRadius)
        // [Property] float ccdMotionThreshold
        .addProperty("ccdMotionThreshold", &RigidBody::GetCcdMotionThreshold, &RigidBody::SetCcdMotionThreshold)
        // [Property] bool useGravity
        .addProperty("useGravity", &RigidBody::GetUseGravity, &RigidBody::SetUseGravity)
        // [Property] const Vector3& gravityOverride
        .addProperty("gravityOverride", &RigidBody::GetGravityOverride, &RigidBody::SetGravityOverride)
        // [Property(Readonly)] const Vector3& centerOfMass
        .addProperty("centerOfMass", &RigidBody::GetCenterOfMass)
        // [Property] bool kinematic
        .addProperty("kinematic", &RigidBody::IsKinematic, &RigidBody::SetKinematic)
        // [Property] bool trigger
        .addProperty("trigger", &RigidBody::IsTrigger, &RigidBody::SetTrigger)
        // [Property(Readonly)] bool active
        .addProperty("active", &RigidBody::IsActive)
        // [Property] unsigned collisionLayer
        .addProperty("collisionLayer", &RigidBody::GetCollisionLayer, &RigidBody::SetCollisionLayer)
        // [Property] unsigned collisionMask
        .addProperty("collisionMask", &RigidBody::GetCollisionMask, &RigidBody::SetCollisionMask)
        // [Property] CollisionEventMode collisionEventMode
        .addProperty("collisionEventMode", &RigidBody::GetCollisionEventMode, &RigidBody::SetCollisionEventMode)
        );
}
}

#endif
