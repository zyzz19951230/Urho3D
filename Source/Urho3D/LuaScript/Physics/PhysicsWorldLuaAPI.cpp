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
}

#endif
