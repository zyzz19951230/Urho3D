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

#include "../../Graphics/Model.h"
#include "../../Math/Ray.h"
#include "../../Physics/CollisionShape.h"
#include "../../Physics/PhysicsWorld.h"
#include "../../Physics/RigidBody.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

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

void RegisterPhysicsWorld(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] PhysicsRaycastResult
    lua["PhysicsRaycastResult"].setClass(UserdataMetatable<PhysicsRaycastResult>()
        .setConstructors<PhysicsRaycastResult()>()

        .addProperty("position", &PhysicsRaycastResult::position_)
        .addProperty("normal", &PhysicsRaycastResult::normal_)
        .addProperty("distance", &PhysicsRaycastResult::distance_)
        .addProperty("hitFraction", &PhysicsRaycastResult::hitFraction_)
        .addProperty("body", &PhysicsRaycastResult::body_)
        );

    // [Constant] float DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY
    lua["DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY"] = DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY;

    // [Class] PhysicsWorld : Component
    lua["PhysicsWorld"].setClass(UserdataMetatable<PhysicsWorld, Component>()
        .addStaticFunction("new", &CreateObject<PhysicsWorld>)

        // [Method] void DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
        .addFunction("DrawDebugGeometry", static_cast<void(PhysicsWorld::*)(bool)>(&PhysicsWorld::DrawDebugGeometry))

        // [Method] void SetFps(int fps)
        .addFunction("SetFps", &PhysicsWorld::SetFps)
        // [Method] void SetGravity(const Vector3& gravity)
        .addFunction("SetGravity", &PhysicsWorld::SetGravity)
        // [Method] void SetMaxSubSteps(int num)
        .addFunction("SetMaxSubSteps", &PhysicsWorld::SetMaxSubSteps)
        // [Method] void SetNumIterations(int num)
        .addFunction("SetNumIterations", &PhysicsWorld::SetNumIterations)
        // [Method] void SetUpdateEnabled(bool enable)
        .addFunction("SetUpdateEnabled", &PhysicsWorld::SetUpdateEnabled)
        // [Method] void SetInterpolation(bool enable)
        .addFunction("SetInterpolation", &PhysicsWorld::SetInterpolation)
        // [Method] void SetInternalEdge(bool enable)
        .addFunction("SetInternalEdge", &PhysicsWorld::SetInternalEdge)
        // [Method] void SetSplitImpulse(bool enable)
        .addFunction("SetSplitImpulse", &PhysicsWorld::SetSplitImpulse)
        // [Method] void SetMaxNetworkAngularVelocity(float velocity)
        .addFunction("SetMaxNetworkAngularVelocity", &PhysicsWorld::SetMaxNetworkAngularVelocity)

        .addStaticFunction("Raycast", PhysicsWorldRaycastOverloads())
        .addStaticFunction("RaycastSingle", PhysicsWorldRaycastSingleOverloads())
        .addStaticFunction("RaycastSingleSegmented", PhysicsWorldRaycastSingleSegmentedOverloads())
        .addStaticFunction("SphereCast", PhysicsWorldSphereCastOverloads())
        .addStaticFunction("ConvexCast", PhysicsWorldConvexCastOverloads())

        // [Method] void RemoveCachedGeometry(Model* model)
        .addFunction("RemoveCachedGeometry", &PhysicsWorld::RemoveCachedGeometry)

        .addOverloadedFunctions("GetRigidBodies", PhysicsWorldGetRigidBodiesOverloads0(), PhysicsWorldGetRigidBodiesOverloads1())

        .addStaticFunction("GetCollidingBodies", &PhysicsWorldGetCollidingBodies)

        // [Method] Vector3 GetGravity() const
        .addFunction("GetGravity", &PhysicsWorld::GetGravity)
        // [Method] int GetMaxSubSteps() const
        .addFunction("GetMaxSubSteps", &PhysicsWorld::GetMaxSubSteps)
        // [Method] int GetNumIterations() const
        .addFunction("GetNumIterations", &PhysicsWorld::GetNumIterations)
        // [Method] bool IsUpdateEnabled() const
        .addFunction("IsUpdateEnabled", &PhysicsWorld::IsUpdateEnabled)
        // [Method] bool GetInterpolation() const
        .addFunction("GetInterpolation", &PhysicsWorld::GetInterpolation)
        // [Method] bool GetInternalEdge() const
        .addFunction("GetInternalEdge", &PhysicsWorld::GetInternalEdge)
        // [Method] bool GetSplitImpulse() const
        .addFunction("GetSplitImpulse", &PhysicsWorld::GetSplitImpulse)
        // [Method] int GetFps() const
        .addFunction("GetFps", &PhysicsWorld::GetFps)
        // [Method] float GetMaxNetworkAngularVelocity() const
        .addFunction("GetMaxNetworkAngularVelocity", &PhysicsWorld::GetMaxNetworkAngularVelocity)
        
        // [Property] Vector3 gravity
        .addProperty("gravity", &PhysicsWorld::GetGravity, &PhysicsWorld::SetGravity)
        // [Property] int maxSubSteps
        .addProperty("maxSubSteps", &PhysicsWorld::GetMaxSubSteps, &PhysicsWorld::SetMaxSubSteps)
        // [Property] int numIterations
        .addProperty("numIterations", &PhysicsWorld::GetNumIterations, &PhysicsWorld::SetNumIterations)
        // [Property] bool updateEnabled
        .addProperty("updateEnabled", &PhysicsWorld::IsUpdateEnabled, &PhysicsWorld::SetUpdateEnabled)
        // [Property] bool interpolation
        .addProperty("interpolation", &PhysicsWorld::GetInterpolation, &PhysicsWorld::SetInterpolation)
        // [Property] bool internalEdge
        .addProperty("internalEdge", &PhysicsWorld::GetInternalEdge, &PhysicsWorld::SetInternalEdge)
        // [Property] bool splitImpulse
        .addProperty("splitImpulse", &PhysicsWorld::GetSplitImpulse, &PhysicsWorld::SetSplitImpulse)
        // [Property] int fps
        .addProperty("fps", &PhysicsWorld::GetFps, &PhysicsWorld::SetFps)
        // [Property] float maxNetworkAngularVelocity
        .addProperty("maxNetworkAngularVelocity", &PhysicsWorld::GetMaxNetworkAngularVelocity, &PhysicsWorld::SetMaxNetworkAngularVelocity)
        );

    // [Function] void URHO3D_API RegisterPhysicsLibrary(Context* context)
    lua["RegisterPhysicsLibrary"] = function(&RegisterPhysicsLibrary);
}
}

#endif
