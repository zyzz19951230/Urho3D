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

    // [Class] PhysicsRaycastResult2D
    lua["PhysicsRaycastResult2D"].setClass(UserdataMetatable<PhysicsRaycastResult2D>()
        // [Constructor] PhysicsRaycastResult2D()
        .setConstructors<PhysicsRaycastResult2D()>()

        // [Field] Vector3 position
        .addProperty("position", &PhysicsRaycastResult2D::position_)
        // [Field] Vector3 normal
        .addProperty("normal", &PhysicsRaycastResult2D::normal_)
        // [Field] float distance
        .addProperty("distance", &PhysicsRaycastResult2D::distance_)
        // [Field] RigidBody2D* body
        .addProperty("body", &PhysicsRaycastResult2D::body_)
    );

    // [Class] PhysicsWorld2D : Component
    lua["PhysicsWorld2D"].setClass(UserdataMetatable<PhysicsWorld2D, Component>()
        // [Constructor] PhysicsWorld2D()
        .addStaticFunction("new", &CreateObject<PhysicsWorld2D>)

        // [Method] void DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
        .addFunction("DrawDebugGeometry", static_cast<void(PhysicsWorld2D::*)()>(&PhysicsWorld2D::DrawDebugGeometry))

        // [Method] void SetUpdateEnabled(bool enable)
        .addFunction("SetUpdateEnabled", &PhysicsWorld2D::SetUpdateEnabled)
        // [Method] void SetDrawShape(bool drawShape)
        .addFunction("SetDrawShape", &PhysicsWorld2D::SetDrawShape)
        // [Method] void SetDrawJoint(bool drawJoint)
        .addFunction("SetDrawJoint", &PhysicsWorld2D::SetDrawJoint)
        // [Method] void SetDrawAabb(bool drawAabb)
        .addFunction("SetDrawAabb", &PhysicsWorld2D::SetDrawAabb)
        // [Method] void SetDrawPair(bool drawPair)
        .addFunction("SetDrawPair", &PhysicsWorld2D::SetDrawPair)
        // [Method] void SetDrawCenterOfMass(bool drawCenterOfMass)
        .addFunction("SetDrawCenterOfMass", &PhysicsWorld2D::SetDrawCenterOfMass)
        // [Method] void SetAllowSleeping(bool enable)
        .addFunction("SetAllowSleeping", &PhysicsWorld2D::SetAllowSleeping)
        // [Method] void SetWarmStarting(bool enable)
        .addFunction("SetWarmStarting", &PhysicsWorld2D::SetWarmStarting)
        // [Method] void SetContinuousPhysics(bool enable)
        .addFunction("SetContinuousPhysics", &PhysicsWorld2D::SetContinuousPhysics)
        // [Method] void SetSubStepping(bool enable)
        .addFunction("SetSubStepping", &PhysicsWorld2D::SetSubStepping)
        // [Method] void SetGravity(const Vector2& gravity)
        .addFunction("SetGravity", &PhysicsWorld2D::SetGravity)
        // [Method] void SetAutoClearForces(bool enable)
        .addFunction("SetAutoClearForces", &PhysicsWorld2D::SetAutoClearForces)
        // [Method] void SetVelocityIterations(int velocityIterations)
        .addFunction("SetVelocityIterations", &PhysicsWorld2D::SetVelocityIterations)
        // [Method] void SetPositionIterations(int positionIterations)
        .addFunction("SetPositionIterations", &PhysicsWorld2D::SetPositionIterations)

        // [Method] PODVector<PhysicsRaycastResult2D> Raycast(const Vector2& startPoint, const Vector2& endPoint, unsigned int collisionMask = M_MAX_UNSIGNED)
        .addStaticFunction("Raycast", PhysicsWorld2DRaycastOverloads())

        // [Method] PhysicsRaycastResult2D RaycastSingle(const Vector2& startPoint, const Vector2& endPoint, unsigned int collisionMask = M_MAX_UNSIGNED)
        .addStaticFunction("RaycastSingle", PhysicsWorld2DRaycastSingleOverloads())
        
        .addOverloadedFunctions("GetRigidBody", 
            // [Method] RigidBody2D* GetRigidBody(const Vector2& point, unsigned collisionMask = M_MAX_UNSIGNED)
            PhysicsWorld2DGetRigidBody0(), 
            // [Method] RigidBody2D* GetRigidBody(int screenX, int screenY, unsigned collisionMask = M_MAX_UNSIGNED)
            PhysicsWorld2DGetRigidBody1())

        // [Method] PODVector<RigidBody2D*> GetRigidBodies(const Rect& aabb, unsigned int collisionMask = M_MAX_UNSIGNED)
        .addStaticFunction("GetRigidBodies", PhysicsWorld2DGetRigidBodiesOverloads())

        // [Method] bool IsUpdateEnabled() const
        .addFunction("IsUpdateEnabled", &PhysicsWorld2D::IsUpdateEnabled)
        // [Method] bool GetDrawShape() const
        .addFunction("GetDrawShape", &PhysicsWorld2D::GetDrawShape)
        // [Method] bool GetDrawJoint() const
        .addFunction("GetDrawJoint", &PhysicsWorld2D::GetDrawJoint)
        // [Method] bool GetDrawAabb() const
        .addFunction("GetDrawAabb", &PhysicsWorld2D::GetDrawAabb)
        // [Method] bool GetDrawPair() const
        .addFunction("GetDrawPair", &PhysicsWorld2D::GetDrawPair)
        // [Method] bool GetDrawCenterOfMass() const
        .addFunction("GetDrawCenterOfMass", &PhysicsWorld2D::GetDrawCenterOfMass)
        // [Method] bool GetAllowSleeping() const
        .addFunction("GetAllowSleeping", &PhysicsWorld2D::GetAllowSleeping)
        // [Method] bool GetWarmStarting() const
        .addFunction("GetWarmStarting", &PhysicsWorld2D::GetWarmStarting)
        // [Method] bool GetContinuousPhysics() const
        .addFunction("GetContinuousPhysics", &PhysicsWorld2D::GetContinuousPhysics)
        // [Method] bool GetSubStepping() const
        .addFunction("GetSubStepping", &PhysicsWorld2D::GetSubStepping)
        // [Method] bool GetAutoClearForces() const
        .addFunction("GetAutoClearForces", &PhysicsWorld2D::GetAutoClearForces)
        // [Method] const Vector2& GetGravity() const
        .addFunction("GetGravity", &PhysicsWorld2D::GetGravity)
        // [Method] int GetVelocityIterations() const
        .addFunction("GetVelocityIterations", &PhysicsWorld2D::GetVelocityIterations)
        // [Method] int GetPositionIterations() const
        .addFunction("GetPositionIterations", &PhysicsWorld2D::GetPositionIterations)

        // [Property] bool updateEnabled
        .addProperty("updateEnabled", &PhysicsWorld2D::IsUpdateEnabled, &PhysicsWorld2D::SetUpdateEnabled)
        // [Property] bool drawShape
        .addProperty("drawShape", &PhysicsWorld2D::GetDrawShape, &PhysicsWorld2D::SetDrawShape)
        // [Property] bool drawJoint
        .addProperty("drawJoint", &PhysicsWorld2D::GetDrawJoint, &PhysicsWorld2D::SetDrawJoint)
        // [Property] bool drawAabb
        .addProperty("drawAabb", &PhysicsWorld2D::GetDrawAabb, &PhysicsWorld2D::SetDrawAabb)
        // [Property] bool drawPair
        .addProperty("drawPair", &PhysicsWorld2D::GetDrawPair, &PhysicsWorld2D::SetDrawPair)
        // [Property] bool drawCenterOfMass
        .addProperty("drawCenterOfMass", &PhysicsWorld2D::GetDrawCenterOfMass, &PhysicsWorld2D::SetDrawCenterOfMass)
        // [Property] bool allowSleeping
        .addProperty("allowSleeping", &PhysicsWorld2D::GetAllowSleeping, &PhysicsWorld2D::SetAllowSleeping)
        // [Property] bool warmStarting
        .addProperty("warmStarting", &PhysicsWorld2D::GetWarmStarting, &PhysicsWorld2D::SetWarmStarting)
        // [Property] bool continuousPhysics
        .addProperty("continuousPhysics", &PhysicsWorld2D::GetContinuousPhysics, &PhysicsWorld2D::SetContinuousPhysics)
        // [Property] bool subStepping
        .addProperty("subStepping", &PhysicsWorld2D::GetSubStepping, &PhysicsWorld2D::SetSubStepping)
        // [Property] bool autoClearForces
        .addProperty("autoClearForces", &PhysicsWorld2D::GetAutoClearForces, &PhysicsWorld2D::SetAutoClearForces)
        // [Property] const Vector2& gravity
        .addProperty("gravity", &PhysicsWorld2D::GetGravity, &PhysicsWorld2D::SetGravity)
        // [Property] int velocityIterations
        .addProperty("velocityIterations", &PhysicsWorld2D::GetVelocityIterations, &PhysicsWorld2D::SetVelocityIterations)
        // [Property] int positionIterations
        .addProperty("positionIterations", &PhysicsWorld2D::GetPositionIterations, &PhysicsWorld2D::SetPositionIterations)
    );
}
}

#endif
