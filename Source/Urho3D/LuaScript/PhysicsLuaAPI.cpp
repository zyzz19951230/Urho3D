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

#include "../Precompiled.h"

#include "../Graphics/Model.h"
#include "../Graphics/CustomGeometry.h"
#include "../LuaScript/LuaScriptUtils.h"
#include "../Math/Ray.h"
#include "../Physics/CollisionShape.h"
#include "../Physics/Constraint.h"
#include "../Physics/PhysicsUtils.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/RigidBody.h"

#include <Bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <Bullet/BulletCollision/CollisionShapes/btCompoundShape.h>
#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetBox, CollisionShape, SetBox, 1, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetSphere, CollisionShape, SetSphere, 1, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetStaticPlane, CollisionShape, SetStaticPlane, 0, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCylinder, CollisionShape, SetCylinder, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCapsule, CollisionShape, SetCapsule, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCone, CollisionShape, SetCone, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetTriangleMesh, CollisionShape, SetTriangleMesh, 1, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCustomTriangleMesh, CollisionShape, SetCustomTriangleMesh, 1, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetConvexHull, CollisionShape, SetConvexHull, 1, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCustomConvexHull, CollisionShape, SetCustomConvexHull, 1, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetTerrain, CollisionShape, SetTerrain, 0, 1);

static void RegisterCollisionShape(kaguya::State& lua)
{
    using namespace kaguya;

    // enum ShapeType;
    lua["SHAPE_BOX"] = SHAPE_BOX;
    lua["SHAPE_SPHERE"] = SHAPE_SPHERE;
    lua["SHAPE_STATICPLANE"] = SHAPE_STATICPLANE;
    lua["SHAPE_CYLINDER"] = SHAPE_CYLINDER;
    lua["SHAPE_CAPSULE"] = SHAPE_CAPSULE;
    lua["SHAPE_CONE"] = SHAPE_CONE;
    lua["SHAPE_TRIANGLEMESH"] = SHAPE_TRIANGLEMESH;
    lua["SHAPE_CONVEXHULL"] = SHAPE_CONVEXHULL;
    lua["SHAPE_TERRAIN"] = SHAPE_TERRAIN;
    
    lua["CollisionShape"].setClass(UserdataMetatable<CollisionShape, Component>()
        .addStaticFunction("new", &CreateObject<CollisionShape>)

        .addFunction("SetBox", CollisionShapeSetBox())
        .addFunction("SetSphere", CollisionShapeSetSphere())
        .addFunction("SetStaticPlane", CollisionShapeSetStaticPlane())
        .addFunction("SetCylinder", CollisionShapeSetCylinder())
        .addFunction("SetCapsule", CollisionShapeSetCapsule())
        .addFunction("SetCone", CollisionShapeSetCone())
        .addFunction("SetTriangleMesh", CollisionShapeSetTriangleMesh())
        .addFunction("SetCustomTriangleMesh", CollisionShapeSetCustomTriangleMesh())
        .addFunction("SetConvexHull", CollisionShapeSetConvexHull())
        .addFunction("SetCustomConvexHull", CollisionShapeSetCustomConvexHull())
        .addFunction("SetTerrain", CollisionShapeSetTerrain())

        .addFunction("SetShapeType", &CollisionShape::SetShapeType)
        .addFunction("SetSize", &CollisionShape::SetSize)
        .addFunction("SetPosition", &CollisionShape::SetPosition)
        .addFunction("SetRotation", &CollisionShape::SetRotation)
        .addFunction("SetTransform", &CollisionShape::SetTransform)
        .addFunction("SetMargin", &CollisionShape::SetMargin)
        .addFunction("SetModel", &CollisionShape::SetModel)
        .addFunction("SetLodLevel", &CollisionShape::SetLodLevel)

        .addFunction("GetPhysicsWorld", &CollisionShape::GetPhysicsWorld)
        .addFunction("GetShapeType", &CollisionShape::GetShapeType)
        .addFunction("GetSize", &CollisionShape::GetSize)
        .addFunction("GetPosition", &CollisionShape::GetPosition)
        .addFunction("GetRotation", &CollisionShape::GetRotation)
        .addFunction("GetMargin", &CollisionShape::GetMargin)
        .addFunction("GetModel", &CollisionShape::GetModel)
        .addFunction("GetLodLevel", &CollisionShape::GetLodLevel)
        .addFunction("GetWorldBoundingBox", &CollisionShape::GetWorldBoundingBox)

        .addProperty("physicsWorld", &CollisionShape::GetPhysicsWorld)
        .addProperty("shapeType", &CollisionShape::GetShapeType, &CollisionShape::SetShapeType)
        .addProperty("size", &CollisionShape::GetSize, &CollisionShape::SetSize)
        .addProperty("position", &CollisionShape::GetPosition, &CollisionShape::SetPosition)
        .addProperty("rotation", &CollisionShape::GetRotation, &CollisionShape::SetRotation)
        .addProperty("margin", &CollisionShape::GetMargin, &CollisionShape::SetMargin)
        .addProperty("model", &CollisionShape::GetModel, &CollisionShape::SetModel)
        .addProperty("lodLevel", &CollisionShape::GetLodLevel, &CollisionShape::SetLodLevel)
        .addProperty("worldBoundingBox", &CollisionShape::GetWorldBoundingBox)
        .addProperty("terrain", &CollisionShape::SetTerrain)
        );
}

static void RegisterConstraint(kaguya::State& lua)
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

static PODVector<PhysicsRaycastResult> PhysicsWorldRaycast(PhysicsWorld* self, const Ray& ray, float maxDistance, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PODVector<PhysicsRaycastResult> result;
    self->Raycast(result, ray, maxDistance, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorldRaycastOverloads, PhysicsWorldRaycast, 3, 4);

static PhysicsRaycastResult PhysicsWorldRaycastSingle(PhysicsWorld* self, const Ray& ray, float maxDistance, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PhysicsRaycastResult result;
    self->RaycastSingle(result, ray, maxDistance, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorldRaycastSingleOverloads, PhysicsWorldRaycastSingle, 3, 4);

static PhysicsRaycastResult PhysicsWorldRaycastSingleSegmented(PhysicsWorld* self, const Ray& ray, float maxDistance, float segmentDistance, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PhysicsRaycastResult result;
    self->RaycastSingleSegmented(result, ray, maxDistance, segmentDistance, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorldRaycastSingleSegmentedOverloads, PhysicsWorldRaycastSingleSegmented, 4, 5);

static PhysicsRaycastResult PhysicsWorldSphereCast(PhysicsWorld* self, const Ray& ray, float radius, float maxDistance, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PhysicsRaycastResult result;
    self->SphereCast(result, ray, radius, maxDistance, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorldSphereCastOverloads, PhysicsWorldSphereCast, 4, 5);

static PhysicsRaycastResult PhysicsWorldConvexCast(PhysicsWorld* self, CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PhysicsRaycastResult result;
    self->ConvexCast(result, shape, startPos, startRot, endPos, endRot, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorldConvexCastOverloads, PhysicsWorldConvexCast, 6, 7);

static PODVector<RigidBody*> PhysicsWorldGetRigidBodies0(PhysicsWorld* self, const Sphere& sphere, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PODVector<RigidBody*> result;
    self->GetRigidBodies(result, sphere, collisionMask);
    return result;
}

static PODVector<RigidBody*> PhysicsWorldGetRigidBodies1(PhysicsWorld* self, const BoundingBox& box, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PODVector<RigidBody*> result;
    self->GetRigidBodies(result, box, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorldGetRigidBodiesOverloads0, PhysicsWorldGetRigidBodies0, 2, 3);
KAGUYA_FUNCTION_OVERLOADS(PhysicsWorldGetRigidBodiesOverloads1, PhysicsWorldGetRigidBodies1, 2, 3);

static PODVector<RigidBody*> PhysicsWorldGetCollidingBodies(PhysicsWorld* self, const RigidBody* body)
{
    PODVector<RigidBody*> result;
    self->GetCollidingBodies(result, body);
    return result;
}

static void RegisterPhysicsWorld(kaguya::State& lua)
{
    using namespace kaguya;

    lua["PhysicsRaycastResult"].setClass(UserdataMetatable<PhysicsRaycastResult>()
        .setConstructors<PhysicsRaycastResult()>()

        .addProperty("position", &PhysicsRaycastResult::position_)
        .addProperty("normal", &PhysicsRaycastResult::normal_)
        .addProperty("distance", &PhysicsRaycastResult::distance_)
        .addProperty("hitFraction", &PhysicsRaycastResult::hitFraction_)
        .addProperty("body", &PhysicsRaycastResult::body_)
        );

    lua["DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY"] = DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY;

    lua["PhysicsWorld"].setClass(UserdataMetatable<PhysicsWorld, Component>()
        .addStaticFunction("new", &CreateObject<PhysicsWorld>)

        .addFunction("DrawDebugGeometry", static_cast<void(PhysicsWorld::*)(bool)>(&PhysicsWorld::DrawDebugGeometry))

        .addFunction("SetFps", &PhysicsWorld::SetFps)
        .addFunction("SetGravity", &PhysicsWorld::SetGravity)
        .addFunction("SetMaxSubSteps", &PhysicsWorld::SetMaxSubSteps)
        .addFunction("SetNumIterations", &PhysicsWorld::SetNumIterations)
        .addFunction("SetUpdateEnabled", &PhysicsWorld::SetUpdateEnabled)
        .addFunction("SetInterpolation", &PhysicsWorld::SetInterpolation)
        .addFunction("SetInternalEdge", &PhysicsWorld::SetInternalEdge)
        .addFunction("SetSplitImpulse", &PhysicsWorld::SetSplitImpulse)
        .addFunction("SetMaxNetworkAngularVelocity", &PhysicsWorld::SetMaxNetworkAngularVelocity)

        .addStaticFunction("Raycast", PhysicsWorldRaycastOverloads())
        .addStaticFunction("RaycastSingle", PhysicsWorldRaycastSingleOverloads())
        .addStaticFunction("RaycastSingleSegmented", PhysicsWorldRaycastSingleSegmentedOverloads())
        .addStaticFunction("SphereCast", PhysicsWorldSphereCastOverloads())
        .addStaticFunction("ConvexCast", PhysicsWorldConvexCastOverloads())

        .addFunction("RemoveCachedGeometry", &PhysicsWorld::RemoveCachedGeometry)

        .addOverloadedFunctions("GetRigidBodies", PhysicsWorldGetRigidBodiesOverloads0(), PhysicsWorldGetRigidBodiesOverloads1())

        .addStaticFunction("GetCollidingBodies", &PhysicsWorldGetCollidingBodies)

        .addFunction("GetGravity", &PhysicsWorld::GetGravity)
        .addFunction("GetMaxSubSteps", &PhysicsWorld::GetMaxSubSteps)
        .addFunction("GetNumIterations", &PhysicsWorld::GetNumIterations)
        .addFunction("IsUpdateEnabled", &PhysicsWorld::IsUpdateEnabled)
        .addFunction("GetInterpolation", &PhysicsWorld::GetInterpolation)
        .addFunction("GetInternalEdge", &PhysicsWorld::GetInternalEdge)
        .addFunction("GetSplitImpulse", &PhysicsWorld::GetSplitImpulse)
        .addFunction("GetFps", &PhysicsWorld::GetFps)
        .addFunction("GetMaxNetworkAngularVelocity", &PhysicsWorld::GetMaxNetworkAngularVelocity)
        
        .addProperty("gravity", &PhysicsWorld::GetGravity, &PhysicsWorld::SetGravity)
        .addProperty("maxSubSteps", &PhysicsWorld::GetMaxSubSteps, &PhysicsWorld::SetMaxSubSteps)
        .addProperty("numIterations", &PhysicsWorld::GetNumIterations, &PhysicsWorld::SetNumIterations)
        .addProperty("updateEnabled", &PhysicsWorld::IsUpdateEnabled, &PhysicsWorld::SetUpdateEnabled)
        .addProperty("interpolation", &PhysicsWorld::GetInterpolation, &PhysicsWorld::SetInterpolation)
        .addProperty("internalEdge", &PhysicsWorld::GetInternalEdge, &PhysicsWorld::SetInternalEdge)
        .addProperty("splitImpulse", &PhysicsWorld::GetSplitImpulse, &PhysicsWorld::SetSplitImpulse)
        .addProperty("fps", &PhysicsWorld::GetFps, &PhysicsWorld::SetFps)
        .addProperty("maxNetworkAngularVelocity", &PhysicsWorld::GetMaxNetworkAngularVelocity, &PhysicsWorld::SetMaxNetworkAngularVelocity)
        );

    lua["RegisterPhysicsLibrary"] = function(&RegisterPhysicsLibrary);
}

static PODVector<RigidBody*> RigidBodyGetCollidingBodies(RigidBody* self)
{
    PODVector<RigidBody*> result;
    self->GetCollidingBodies(result);
    return result;
}

static void RegisterRigidBody(kaguya::State& lua)
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

void RegisterPhysicsLuaAPI(kaguya::State& lua)
{
    RegisterCollisionShape(lua);
    RegisterConstraint(lua);
    RegisterPhysicsWorld(lua);
    RegisterRigidBody(lua);
}
}

#endif
