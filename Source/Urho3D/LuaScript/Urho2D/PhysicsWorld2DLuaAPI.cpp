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

#include "../../Urho2D/PhysicsWorld2D.h"
#include "../../Urho2D/RigidBody2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static PODVector<PhysicsRaycastResult2D> PhysicsWorld2DRaycast(PhysicsWorld2D* self, const Vector2& startPoint, const Vector2& endPoint, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PODVector<PhysicsRaycastResult2D> results;
    self->Raycast(results, startPoint, endPoint, collisionMask);
    return results;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorld2DRaycastOverloads, PhysicsWorld2DRaycast, 3, 4);

static PhysicsRaycastResult2D PhysicsWorld2DRaycastSingle(PhysicsWorld2D* self, const Vector2& startPoint, const Vector2& endPoint, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PhysicsRaycastResult2D result;
    self->RaycastSingle(result, startPoint, endPoint, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorld2DRaycastSingleOverloads, PhysicsWorld2DRaycastSingle, 3, 4);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(PhysicsWorld2DGetRigidBody0, PhysicsWorld2D, GetRigidBody, 1, 2, RigidBody2D*(PhysicsWorld2D::*)(const Vector2&, unsigned));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(PhysicsWorld2DGetRigidBody1, PhysicsWorld2D, GetRigidBody, 2, 3, RigidBody2D*(PhysicsWorld2D::*)(int, int, unsigned));

static PODVector<RigidBody2D*> PhysicsWorld2DGetRigidBodies(PhysicsWorld2D* self, const Rect& aabb, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PODVector<RigidBody2D*> result;
    self->GetRigidBodies(result, aabb, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorld2DGetRigidBodiesOverloads, PhysicsWorld2DGetRigidBodies, 2, 3);

void RegisterPhysicsWorld2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["PhysicsRaycastResult2D"].setClass(UserdataMetatable<PhysicsRaycastResult2D>()
        .setConstructors<PhysicsRaycastResult2D()>()

        .addProperty("position", &PhysicsRaycastResult2D::position_)
        .addProperty("normal", &PhysicsRaycastResult2D::normal_)
        .addProperty("distance", &PhysicsRaycastResult2D::distance_)
        .addProperty("body", &PhysicsRaycastResult2D::body_)
    );

    lua["PhysicsWorld2D"].setClass(UserdataMetatable<PhysicsWorld2D, Component>()
        .addStaticFunction("new", &CreateObject<PhysicsWorld2D>)

        .addFunction("DrawDebugGeometry", static_cast<void(PhysicsWorld2D::*)()>(&PhysicsWorld2D::DrawDebugGeometry))

        .addFunction("SetUpdateEnabled", &PhysicsWorld2D::SetUpdateEnabled)
        .addFunction("SetDrawShape", &PhysicsWorld2D::SetDrawShape)
        .addFunction("SetDrawJoint", &PhysicsWorld2D::SetDrawJoint)
        .addFunction("SetDrawAabb", &PhysicsWorld2D::SetDrawAabb)
        .addFunction("SetDrawPair", &PhysicsWorld2D::SetDrawPair)
        .addFunction("SetDrawCenterOfMass", &PhysicsWorld2D::SetDrawCenterOfMass)
        .addFunction("SetAllowSleeping", &PhysicsWorld2D::SetAllowSleeping)
        .addFunction("SetWarmStarting", &PhysicsWorld2D::SetWarmStarting)
        .addFunction("SetContinuousPhysics", &PhysicsWorld2D::SetContinuousPhysics)
        .addFunction("SetSubStepping", &PhysicsWorld2D::SetSubStepping)
        .addFunction("SetGravity", &PhysicsWorld2D::SetGravity)
        .addFunction("SetAutoClearForces", &PhysicsWorld2D::SetAutoClearForces)
        .addFunction("SetVelocityIterations", &PhysicsWorld2D::SetVelocityIterations)
        .addFunction("SetPositionIterations", &PhysicsWorld2D::SetPositionIterations)

        .addStaticFunction("Raycast", PhysicsWorld2DRaycastOverloads())

        .addStaticFunction("RaycastSingle", PhysicsWorld2DRaycastSingleOverloads())
        
        .addOverloadedFunctions("GetRigidBody", PhysicsWorld2DGetRigidBody0(), PhysicsWorld2DGetRigidBody1())

        .addStaticFunction("GetRigidBodies", PhysicsWorld2DGetRigidBodiesOverloads())

        .addFunction("IsUpdateEnabled", &PhysicsWorld2D::IsUpdateEnabled)
        .addFunction("GetDrawShape", &PhysicsWorld2D::GetDrawShape)
        .addFunction("GetDrawJoint", &PhysicsWorld2D::GetDrawJoint)
        .addFunction("GetDrawAabb", &PhysicsWorld2D::GetDrawAabb)
        .addFunction("GetDrawPair", &PhysicsWorld2D::GetDrawPair)
        .addFunction("GetDrawCenterOfMass", &PhysicsWorld2D::GetDrawCenterOfMass)
        .addFunction("GetAllowSleeping", &PhysicsWorld2D::GetAllowSleeping)
        .addFunction("GetWarmStarting", &PhysicsWorld2D::GetWarmStarting)
        .addFunction("GetContinuousPhysics", &PhysicsWorld2D::GetContinuousPhysics)
        .addFunction("GetSubStepping", &PhysicsWorld2D::GetSubStepping)
        .addFunction("GetAutoClearForces", &PhysicsWorld2D::GetAutoClearForces)
        .addFunction("GetGravity", &PhysicsWorld2D::GetGravity)
        .addFunction("GetVelocityIterations", &PhysicsWorld2D::GetVelocityIterations)
        .addFunction("GetPositionIterations", &PhysicsWorld2D::GetPositionIterations)

        .addProperty("updateEnabled", &PhysicsWorld2D::IsUpdateEnabled, &PhysicsWorld2D::SetUpdateEnabled)
        .addProperty("drawShape", &PhysicsWorld2D::GetDrawShape, &PhysicsWorld2D::SetDrawShape)
        .addProperty("drawJoint", &PhysicsWorld2D::GetDrawJoint, &PhysicsWorld2D::SetDrawJoint)
        .addProperty("drawAabb", &PhysicsWorld2D::GetDrawAabb, &PhysicsWorld2D::SetDrawAabb)
        .addProperty("drawPair", &PhysicsWorld2D::GetDrawPair, &PhysicsWorld2D::SetDrawPair)
        .addProperty("drawCenterOfMass", &PhysicsWorld2D::GetDrawCenterOfMass, &PhysicsWorld2D::SetDrawCenterOfMass)
        .addProperty("allowSleeping", &PhysicsWorld2D::GetAllowSleeping, &PhysicsWorld2D::SetAllowSleeping)
        .addProperty("warmStarting", &PhysicsWorld2D::GetWarmStarting, &PhysicsWorld2D::SetWarmStarting)
        .addProperty("continuousPhysics", &PhysicsWorld2D::GetContinuousPhysics, &PhysicsWorld2D::SetContinuousPhysics)
        .addProperty("subStepping", &PhysicsWorld2D::GetSubStepping, &PhysicsWorld2D::SetSubStepping)
        .addProperty("autoClearForces", &PhysicsWorld2D::GetAutoClearForces, &PhysicsWorld2D::SetAutoClearForces)
        .addProperty("gravity", &PhysicsWorld2D::GetGravity, &PhysicsWorld2D::SetGravity)
        .addProperty("velocityIterations", &PhysicsWorld2D::GetVelocityIterations, &PhysicsWorld2D::SetVelocityIterations)
        .addProperty("positionIterations", &PhysicsWorld2D::GetPositionIterations, &PhysicsWorld2D::SetPositionIterations)
    );
}
}

#endif
