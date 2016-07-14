#include "../Core/Context.h"
#include "../Graphics/Model.h"
#include "../Physics/CollisionShape.h"
#include "../Physics/Constraint.h"
#include "../Physics/PhysicsEvents.h"
#include "../Physics/PhysicsUtils.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/RigidBody.h"

#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

    static void CollisionShapeSetBox0(CollisionShape* self, const Vector3& size)
    {
        self->SetBox(size);
    }

    static void CollisionShapeSetBox1(CollisionShape* self, const Vector3& size, const Vector3& position)
    {
        self->SetBox(size, position);
    }

    static void CollisionShapeSetBox2(CollisionShape* self, const Vector3& size, const Vector3& position, const Quaternion& rotation)
    {
        self->SetBox(size, position, rotation);
    }

    static void CollisionShapeSetSphere0(CollisionShape* self, float diameter)
    {
        self->SetSphere(diameter);
    }

    static void CollisionShapeSetSphere1(CollisionShape* self, float diameter, const Vector3& position)
    {
        self->SetSphere(diameter, position);
    }

    static void CollisionShapeSetSphere2(CollisionShape* self, float diameter, const Vector3& position, const Quaternion& rotation)
    {
        self->SetSphere(diameter, position, rotation);
    }

    static void CollisionShapeSetStaticPlane0(CollisionShape* self)
    {
        self->SetStaticPlane();
    }

    static void CollisionShapeSetStaticPlane1(CollisionShape* self, const Vector3& position)
    {
        self->SetStaticPlane(position);
    }

    static void CollisionShapeSetStaticPlane2(CollisionShape* self, const Vector3& position, const Quaternion& rotation)
    {
        self->SetStaticPlane(position, rotation);
    }

    static void CollisionShapeSetCylinder0(CollisionShape* self, float diameter, float height)
    {
        self->SetCylinder(diameter, height);
    }

    static void CollisionShapeSetCylinder1(CollisionShape* self, float diameter, float height, const Vector3& position)
    {
        self->SetCylinder(diameter, height, position);
    }

    static void CollisionShapeSetCylinder2(CollisionShape* self, float diameter, float height, const Vector3& position, const Quaternion& rotation)
    {
        self->SetCylinder(diameter, height, position, rotation);
    }

    static void CollisionShapeSetCapsule0(CollisionShape* self, float diameter, float height)
    {
        self->SetCapsule(diameter, height);
    }

    static void CollisionShapeSetCapsule1(CollisionShape* self, float diameter, float height, const Vector3& position)
    {
        self->SetCapsule(diameter, height, position);
    }

    static void CollisionShapeSetCapsule2(CollisionShape* self, float diameter, float height, const Vector3& position, const Quaternion& rotation)
    {
        self->SetCapsule(diameter, height, position, rotation);
    }
    
    static void CollisionShapeSetCone0(CollisionShape* self, float diameter, float height)
    {
        self->SetCone(diameter, height);
    }

    static void CollisionShapeSetCone1(CollisionShape* self, float diameter, float height, const Vector3& position)
    {
        self->SetCone(diameter, height, position);
    }

    static void CollisionShapeSetCone2(CollisionShape* self, float diameter, float height, const Vector3& position, const Quaternion& rotation)
    {
        self->SetCone(diameter, height, position, rotation);
    }

    static void CollisionShapeSetTriangleMesh0(CollisionShape* self, Model* model)
    {
        self->SetTriangleMesh(model);
    }

    static void CollisionShapeSetTriangleMesh1(CollisionShape* self, Model* model, unsigned int lodLevel)
    {
        self->SetTriangleMesh(model, lodLevel);
    }

    static void CollisionShapeSetTriangleMesh2(CollisionShape* self, Model* model, unsigned int lodLevel, const Vector3& scale)
    {
        self->SetTriangleMesh(model, lodLevel, scale);
    }

    static void CollisionShapeSetTriangleMesh3(CollisionShape* self, Model* model, unsigned int lodLevel, const Vector3& scale, const Vector3& position)
    {
        self->SetTriangleMesh(model, lodLevel, scale, position);
    }

    static void CollisionShapeSetTriangleMesh4(CollisionShape* self, Model* model, unsigned int lodLevel, const Vector3& scale, const Vector3& position, const Quaternion& rotation)
    {
        self->SetTriangleMesh(model, lodLevel, scale, position, rotation);
    }

    static void CollisionShapeSetCustomTriangleMesh0(CollisionShape* self, CustomGeometry* custom)
    {
        self->SetCustomTriangleMesh(custom);
    }

    static void CollisionShapeSetCustomTriangleMesh1(CollisionShape* self, CustomGeometry* custom, const Vector3& scale)
    {
        self->SetCustomTriangleMesh(custom, scale);
    }

    static void CollisionShapeSetCustomTriangleMesh2(CollisionShape* self, CustomGeometry* custom, const Vector3& scale, const Vector3& position)
    {
        self->SetCustomTriangleMesh(custom, scale, position);
    }

    static void CollisionShapeSetCustomTriangleMesh3(CollisionShape* self, CustomGeometry* custom, const Vector3& scale, const Vector3& position, const Quaternion& rotation)
    {
        self->SetCustomTriangleMesh(custom, scale, position, rotation);
    }

    static void CollisionShapeSetConvexHull0(CollisionShape* self, Model* model)
    {
        self->SetConvexHull(model);
    }

    static void CollisionShapeSetConvexHull1(CollisionShape* self, Model* model, unsigned int lodLevel)
    {
        self->SetConvexHull(model, lodLevel);
    }

    static void CollisionShapeSetConvexHull2(CollisionShape* self, Model* model, unsigned int lodLevel, const Vector3& scale)
    {
        self->SetConvexHull(model, lodLevel, scale);
    }

    static void CollisionShapeSetConvexHull3(CollisionShape* self, Model* model, unsigned int lodLevel, const Vector3& scale, const Vector3& position)
    {
        self->SetConvexHull(model, lodLevel, scale, position);
    }

    static void CollisionShapeSetConvexHull4(CollisionShape* self, Model* model, unsigned int lodLevel, const Vector3& scale, const Vector3& position, const Quaternion& rotation)
    {
        self->SetConvexHull(model, lodLevel, scale, position, rotation);
    }
    
    static void CollisionShapeSetCustomConvexHull0(CollisionShape* self, CustomGeometry* custom)
    {
        self->SetCustomConvexHull(custom);
    }

    static void CollisionShapeSetCustomConvexHull1(CollisionShape* self, CustomGeometry* custom, const Vector3& scale)
    {
        self->SetCustomConvexHull(custom, scale);
    }

    static void CollisionShapeSetCustomConvexHull2(CollisionShape* self, CustomGeometry* custom, const Vector3& scale, const Vector3& position)
    {
        self->SetCustomConvexHull(custom, scale, position);
    }

    static void CollisionShapeSetCustomConvexHull3(CollisionShape* self, CustomGeometry* custom, const Vector3& scale, const Vector3& position, const Quaternion& rotation)
    {
        self->SetCustomConvexHull(custom, scale, position, rotation);
    }
    
    static void CollisionShapeSetTerrain0(CollisionShape* self)
    {
        self->SetTerrain();
    }

    static void CollisionShapeSetTerrain1(CollisionShape* self, unsigned int lodLevel)
    {
        self->SetTerrain(lodLevel);
    }
    
    static void CollisionShapeNotifyRigidBody0(CollisionShape* self)
    {
        self->NotifyRigidBody();
    }

    static void CollisionShapeNotifyRigidBody1(CollisionShape* self, bool updateMass)
    {
        self->NotifyRigidBody(updateMass);
    }

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
        .addStaticFunction("new", &KCreateObject<CollisionShape>)
        
        ADD_OVERLOADED_FUNCTIONS_3(CollisionShape, SetBox)        
        ADD_OVERLOADED_FUNCTIONS_3(CollisionShape, SetSphere)
        ADD_OVERLOADED_FUNCTIONS_3(CollisionShape, SetStaticPlane)
        ADD_OVERLOADED_FUNCTIONS_3(CollisionShape, SetCylinder)
        ADD_OVERLOADED_FUNCTIONS_3(CollisionShape, SetCapsule)
        ADD_OVERLOADED_FUNCTIONS_3(CollisionShape, SetCone)
        ADD_OVERLOADED_FUNCTIONS_5(CollisionShape, SetTriangleMesh)
        ADD_OVERLOADED_FUNCTIONS_4(CollisionShape, SetCustomTriangleMesh)
        ADD_OVERLOADED_FUNCTIONS_5(CollisionShape, SetConvexHull)
        ADD_OVERLOADED_FUNCTIONS_4(CollisionShape, SetCustomConvexHull)
        ADD_OVERLOADED_FUNCTIONS_2(CollisionShape, SetTerrain)
        
        .addFunction("SetShapeType", &CollisionShape::SetShapeType)
        .addFunction("SetSize", &CollisionShape::SetSize)
        .addFunction("SetPosition", &CollisionShape::SetPosition)
        .addFunction("SetRotation", &CollisionShape::SetRotation)
        .addFunction("SetTransform", &CollisionShape::SetTransform)
        .addFunction("SetMargin", &CollisionShape::SetMargin)
        .addFunction("SetModel", &CollisionShape::SetModel)
        .addFunction("SetLodLevel", &CollisionShape::SetLodLevel)
        .addFunction("GetCollisionShape", &CollisionShape::GetCollisionShape)
        .addFunction("GetGeometryData", &CollisionShape::GetGeometryData)
        .addFunction("GetPhysicsWorld", &CollisionShape::GetPhysicsWorld)
        .addFunction("GetShapeType", &CollisionShape::GetShapeType)
        .addFunction("GetSize", &CollisionShape::GetSize)
        .addFunction("GetPosition", &CollisionShape::GetPosition)
        .addFunction("GetRotation", &CollisionShape::GetRotation)
        .addFunction("GetMargin", &CollisionShape::GetMargin)
        .addFunction("GetModel", &CollisionShape::GetModel)
        .addFunction("GetLodLevel", &CollisionShape::GetLodLevel)
        .addFunction("GetWorldBoundingBox", &CollisionShape::GetWorldBoundingBox)
        
        ADD_OVERLOADED_FUNCTIONS_2(CollisionShape, NotifyRigidBody)

        .addFunction("ReleaseShape", &CollisionShape::ReleaseShape)

        .addProperty("collisionShape", &CollisionShape::GetCollisionShape)
        .addProperty("geometryData", &CollisionShape::GetGeometryData)
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
        .addStaticFunction("new", &KCreateObject<Constraint>)
        
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
        .addFunction("GetConstraint", &Constraint::GetConstraint)
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
        .addFunction("ReleaseConstraint", &Constraint::ReleaseConstraint)
        .addFunction("ApplyFrames", &Constraint::ApplyFrames)

        .addProperty("physicsWorld", &Constraint::GetPhysicsWorld)
        .addProperty("constraint", &Constraint::GetConstraint)
        .addProperty("constraintType", &Constraint::GetConstraintType, &Constraint::SetConstraintType)
        .addProperty("ownBody", &Constraint::GetOwnBody)
        .addProperty("otherBody", &Constraint::GetOtherBody, &Constraint::SetOtherBody)
        .addProperty("position", &Constraint::GetPosition, &Constraint::SetPosition)
        .addProperty("rotation", &Constraint::GetRotation, &Constraint::SetRotation)
        .addProperty("otherPosition", &Constraint::GetOtherPosition, &Constraint::SetOtherPosition)
        .addProperty("otherRotation", &Constraint::GetOtherRotation, &Constraint::SetOtherRotation)
        .addProperty("worldPosition", &Constraint::GetWorldPosition, &Constraint::SetWorldPosition)
        .addProperty("highLimit", &Constraint::GetHighLimit, &Constraint::SetHighLimit)
        .addProperty("lowLimit", &Constraint::GetLowLimit, &Constraint::SetLowLimit)
        .addProperty("eRP", &Constraint::GetERP, &Constraint::SetERP)
        .addProperty("cFM", &Constraint::GetCFM, &Constraint::SetCFM)
        .addProperty("disableCollision", &Constraint::GetDisableCollision, &Constraint::SetDisableCollision)
        .addProperty("axis", &Constraint::SetAxis)
        .addProperty("otherAxis", &Constraint::SetOtherAxis)
    );
}

static void RegisterPhysicsEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["E_PHYSICSPRESTEP"] = E_PHYSICSPRESTEP;
    lua["E_PHYSICSPOSTSTEP"] = E_PHYSICSPOSTSTEP;
    lua["E_PHYSICSCOLLISIONSTART"] = E_PHYSICSCOLLISIONSTART;
    lua["E_PHYSICSCOLLISION"] = E_PHYSICSCOLLISION;
    lua["E_PHYSICSCOLLISIONEND"] = E_PHYSICSCOLLISIONEND;
    lua["E_NODECOLLISIONSTART"] = E_NODECOLLISIONSTART;
    lua["E_NODECOLLISION"] = E_NODECOLLISION;
    lua["E_NODECOLLISIONEND"] = E_NODECOLLISIONEND;
}

static PODVector<PhysicsRaycastResult> PhysicsWorldRaycast0(PhysicsWorld* self, const Ray& ray, float maxDistance)
{
    PODVector<PhysicsRaycastResult> result; 
    self->Raycast(result, ray, maxDistance);
    return result;
}

static PODVector<PhysicsRaycastResult> PhysicsWorldRaycast1(PhysicsWorld* self, const Ray& ray, float maxDistance, unsigned int collisionMask)
{
    PODVector<PhysicsRaycastResult> result;
    self->Raycast(result, ray, maxDistance, collisionMask);
    return result;
}

static PhysicsRaycastResult PhysicsWorldRaycastSingle0(PhysicsWorld* self, const Ray& ray, float maxDistance)
{
    PhysicsRaycastResult result; 
    self->RaycastSingle(result, ray, maxDistance);
    return result;
}

static PhysicsRaycastResult PhysicsWorldRaycastSingle1(PhysicsWorld* self, const Ray& ray, float maxDistance, unsigned int collisionMask)
{
    PhysicsRaycastResult result; 
    self->RaycastSingle(result, ray, maxDistance, collisionMask);
    return result;
}

static PhysicsRaycastResult PhysicsWorldRaycastSingleSegmented0(PhysicsWorld* self, const Ray& ray, float maxDistance, float segmentDistance)
{
    PhysicsRaycastResult result; 
    self->RaycastSingleSegmented(result, ray, maxDistance, segmentDistance);
    return result;
}

static PhysicsRaycastResult PhysicsWorldRaycastSingleSegmented1(PhysicsWorld* self, const Ray& ray, float maxDistance, float segmentDistance, unsigned int collisionMask)
{
    PhysicsRaycastResult result; 
    self->RaycastSingleSegmented(result, ray, maxDistance, segmentDistance, collisionMask);
    return result;
}

static PhysicsRaycastResult PhysicsWorldSphereCast0(PhysicsWorld* self, const Ray& ray, float radius, float maxDistance)
{
    PhysicsRaycastResult result;
    self->SphereCast(result, ray, radius, maxDistance);
    return result;
}

static PhysicsRaycastResult PhysicsWorldSphereCast1(PhysicsWorld* self, const Ray& ray, float radius, float maxDistance, unsigned int collisionMask)
{
    PhysicsRaycastResult result;
    self->SphereCast(result, ray, radius, maxDistance, collisionMask);
    return result;
}

static PhysicsRaycastResult PhysicsWorldConvexCast0(PhysicsWorld* self, CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot)
{
    PhysicsRaycastResult result;
    self->ConvexCast(result, shape, startPos, startRot, endPos, endRot);
    return result;
}

static PhysicsRaycastResult PhysicsWorldConvexCast1(PhysicsWorld* self, CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned int collisionMask)
{
    PhysicsRaycastResult result;
    self->ConvexCast(result, shape, startPos, startRot, endPos, endRot, collisionMask);
    return result;
}

static PODVector<RigidBody*> PhysicsWorldGetRigidBodies0(PhysicsWorld* self, const Sphere& sphere)
{
    PODVector<RigidBody*> result;
    self->GetRigidBodies(result, sphere);
    return result;
}

static PODVector<RigidBody*> PhysicsWorldGetRigidBodies1(PhysicsWorld* self, const Sphere& sphere, unsigned int collisionMask)
{
    PODVector<RigidBody*> result;
    self->GetRigidBodies(result, sphere, collisionMask);
    return result;
}

static PODVector<RigidBody*> PhysicsWorldGetRigidBodies2(PhysicsWorld* self, const BoundingBox& box)
{
    PODVector<RigidBody*> result;
    self->GetRigidBodies(result, box);
    return result;
}

static PODVector<RigidBody*> PhysicsWorldGetRigidBodies3(PhysicsWorld* self, const BoundingBox& box, unsigned int collisionMask)
{
    PODVector<RigidBody*> result;
    self->GetRigidBodies(result, box, collisionMask);
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
        .addStaticFunction("new", &KCreateObject<PhysicsWorld>)
        
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
        
        ADD_OVERLOADED_FUNCTIONS_2(PhysicsWorld, Raycast)

        ADD_OVERLOADED_FUNCTIONS_2(PhysicsWorld, RaycastSingle)
        ADD_OVERLOADED_FUNCTIONS_2(PhysicsWorld, RaycastSingleSegmented)
        ADD_OVERLOADED_FUNCTIONS_2(PhysicsWorld, SphereCast)

        // .addFunction("ConvexCast", static_cast<void(PhysicsWorld::*)(PhysicsRaycastResult&, CollisionShape*, const Vector3&, const Quaternion&, const Vector3&, const Quaternion&, unsigned)>(&PhysicsWorld::ConvexCast))
        ADD_OVERLOADED_FUNCTIONS_2(PhysicsWorld, ConvexCast)

        .addFunction("RemoveCachedGeometry", &PhysicsWorld::RemoveCachedGeometry)

        /*
        .addOverloadedFunctions("GetRigidBodies",
            static_cast<void(PhysicsWorld::*)(PODVector<RigidBody*>&, const Sphere&, unsigned)>(&PhysicsWorld::GetRigidBodies),
            static_cast<void(PhysicsWorld::*)(PODVector<RigidBody*>&, const BoundingBox&, unsigned)>(&PhysicsWorld::GetRigidBodies),
            static_cast<void(PhysicsWorld::*)(PODVector<RigidBody*>&, const RigidBody*)>(&PhysicsWorld::GetRigidBodies))
            */

            // .addFunction("GetCollidingBodies", &PhysicsWorld::GetCollidingBodies)
        ADD_OVERLOADED_FUNCTIONS_4(PhysicsWorld, GetRigidBodies)

        .addFunction("GetGravity", &PhysicsWorld::GetGravity)
        .addFunction("GetMaxSubSteps", &PhysicsWorld::GetMaxSubSteps)
        .addFunction("GetNumIterations", &PhysicsWorld::GetNumIterations)
        .addFunction("IsUpdateEnabled", &PhysicsWorld::IsUpdateEnabled)
        .addFunction("GetInterpolation", &PhysicsWorld::GetInterpolation)
        .addFunction("GetInternalEdge", &PhysicsWorld::GetInternalEdge)
        .addFunction("GetSplitImpulse", &PhysicsWorld::GetSplitImpulse)
        .addFunction("GetFps", &PhysicsWorld::GetFps)
        .addFunction("GetMaxNetworkAngularVelocity", &PhysicsWorld::GetMaxNetworkAngularVelocity)
        .addFunction("AddRigidBody", &PhysicsWorld::AddRigidBody)
        .addFunction("RemoveRigidBody", &PhysicsWorld::RemoveRigidBody)
        .addFunction("AddCollisionShape", &PhysicsWorld::AddCollisionShape)
        .addFunction("RemoveCollisionShape", &PhysicsWorld::RemoveCollisionShape)
        .addFunction("AddConstraint", &PhysicsWorld::AddConstraint)
        .addFunction("RemoveConstraint", &PhysicsWorld::RemoveConstraint)
        .addFunction("AddDelayedWorldTransform", &PhysicsWorld::AddDelayedWorldTransform)
        .addFunction("SetDebugRenderer", &PhysicsWorld::SetDebugRenderer)
        .addFunction("SetDebugDepthTest", &PhysicsWorld::SetDebugDepthTest)
        .addFunction("GetWorld", &PhysicsWorld::GetWorld)
        .addFunction("CleanupGeometryCache", &PhysicsWorld::CleanupGeometryCache)
        .addFunction("GetTriMeshCache", &PhysicsWorld::GetTriMeshCache)
        .addFunction("GetConvexCache", &PhysicsWorld::GetConvexCache)
        .addFunction("SetApplyingTransforms", &PhysicsWorld::SetApplyingTransforms)
        .addFunction("IsApplyingTransforms", &PhysicsWorld::IsApplyingTransforms)
        .addFunction("IsSimulating", &PhysicsWorld::IsSimulating)

        .addProperty("gravity", &PhysicsWorld::GetGravity, &PhysicsWorld::SetGravity)
        .addProperty("maxSubSteps", &PhysicsWorld::GetMaxSubSteps, &PhysicsWorld::SetMaxSubSteps)
        .addProperty("numIterations", &PhysicsWorld::GetNumIterations, &PhysicsWorld::SetNumIterations)
        .addProperty("updateEnabled", &PhysicsWorld::IsUpdateEnabled, &PhysicsWorld::SetUpdateEnabled)
        .addProperty("interpolation", &PhysicsWorld::GetInterpolation, &PhysicsWorld::SetInterpolation)
        .addProperty("internalEdge", &PhysicsWorld::GetInternalEdge, &PhysicsWorld::SetInternalEdge)
        .addProperty("splitImpulse", &PhysicsWorld::GetSplitImpulse, &PhysicsWorld::SetSplitImpulse)
        .addProperty("fps", &PhysicsWorld::GetFps, &PhysicsWorld::SetFps)
        .addProperty("maxNetworkAngularVelocity", &PhysicsWorld::GetMaxNetworkAngularVelocity, &PhysicsWorld::SetMaxNetworkAngularVelocity)
        .addProperty("world", &PhysicsWorld::GetWorld)
        .addProperty("triMeshCache", &PhysicsWorld::GetTriMeshCache)
        .addProperty("convexCache", &PhysicsWorld::GetConvexCache)
        .addProperty("applyingTransforms", &PhysicsWorld::IsApplyingTransforms, &PhysicsWorld::SetApplyingTransforms)
        .addProperty("simulating", &PhysicsWorld::IsSimulating)
        .addProperty("debugRenderer", &PhysicsWorld::SetDebugRenderer)
        .addProperty("debugDepthTest", &PhysicsWorld::SetDebugDepthTest)
    );
    lua["RegisterPhysicsLibrary"] = function(&RegisterPhysicsLibrary);
}

static void RegisterRigidBody(kaguya::State& lua)
{
    using namespace kaguya;

    // enum CollisionEventMode;
    lua["COLLISION_NEVER"] = COLLISION_NEVER;
    lua["COLLISION_ACTIVE"] = COLLISION_ACTIVE;
    lua["COLLISION_ALWAYS"] = COLLISION_ALWAYS;

    lua["RigidBody"].setClass(UserdataMetatable<RigidBody, Component>()
        .addStaticFunction("new", &KCreateObject<RigidBody>)
        
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
        .addFunction("GetCollidingBodies", &RigidBody::GetCollidingBodies)
        .addFunction("ApplyWorldTransform", &RigidBody::ApplyWorldTransform)
        .addFunction("UpdateMass", &RigidBody::UpdateMass)
        .addFunction("UpdateGravity", &RigidBody::UpdateGravity)
        .addFunction("AddConstraint", &RigidBody::AddConstraint)
        .addFunction("RemoveConstraint", &RigidBody::RemoveConstraint)
        .addFunction("ReleaseBody", &RigidBody::ReleaseBody)

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
    RegisterPhysicsEvents(lua);
    RegisterPhysicsWorld(lua);
    RegisterRigidBody(lua);
}
}
