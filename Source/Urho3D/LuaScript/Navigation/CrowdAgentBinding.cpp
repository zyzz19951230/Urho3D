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

#ifdef URHO3D_NAVIGATION

#include "../../Precompiled.h"

#include "../../Navigation/CrowdAgent.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterCrowdAgent(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] CrowdAgentRequestedTarget
    lua["CA_REQUESTEDTARGET_NONE"] = CA_REQUESTEDTARGET_NONE;
    lua["CA_REQUESTEDTARGET_POSITION"] = CA_REQUESTEDTARGET_POSITION;
    lua["CA_REQUESTEDTARGET_VELOCITY"] = CA_REQUESTEDTARGET_VELOCITY;

    // [Enum] CrowdAgentTargetState
    lua["CA_TARGET_NONE"] = CA_TARGET_NONE;
    lua["CA_TARGET_FAILED"] = CA_TARGET_FAILED;
    lua["CA_TARGET_VALID"] = CA_TARGET_VALID;
    lua["CA_TARGET_REQUESTING"] = CA_TARGET_REQUESTING;
    lua["CA_TARGET_WAITINGFORQUEUE"] = CA_TARGET_WAITINGFORQUEUE;
    lua["CA_TARGET_WAITINGFORPATH"] = CA_TARGET_WAITINGFORPATH;
    lua["CA_TARGET_VELOCITY"] = CA_TARGET_VELOCITY;

    // [Enum] CrowdAgentState
    lua["CA_STATE_INVALID"] = CA_STATE_INVALID;
    lua["CA_STATE_WALKING"] = CA_STATE_WALKING;
    lua["CA_STATE_OFFMESH"] = CA_STATE_OFFMESH;

    // [Enum] NavigationQuality
    lua["NAVIGATIONQUALITY_LOW"] = NAVIGATIONQUALITY_LOW;
    lua["NAVIGATIONQUALITY_MEDIUM"] = NAVIGATIONQUALITY_MEDIUM;
    lua["NAVIGATIONQUALITY_HIGH"] = NAVIGATIONQUALITY_HIGH;

    // [Enum] NavigationPushiness
    lua["NAVIGATIONPUSHINESS_LOW"] = NAVIGATIONPUSHINESS_LOW;
    lua["NAVIGATIONPUSHINESS_MEDIUM"] = NAVIGATIONPUSHINESS_MEDIUM;
    lua["NAVIGATIONPUSHINESS_HIGH"] = NAVIGATIONPUSHINESS_HIGH;

    // [Class] CrowdAgent : Component
    lua["CrowdAgent"].setClass(UserdataMetatable<CrowdAgent, Component>()
        // [Constructor] CrowdAgent()
        .addStaticFunction("new", &CreateObject<CrowdAgent>)

        // [Method] void DrawDebugGeometry(bool)
        .addFunction("DrawDebugGeometry", static_cast<void(CrowdAgent::*)(bool)>(&CrowdAgent::DrawDebugGeometry))

        // [Method] void SetTargetPosition(const Vector3& position)
        .addFunction("SetTargetPosition", &CrowdAgent::SetTargetPosition)
        // [Method] void SetTargetVelocity(const Vector3& velocity)
        .addFunction("SetTargetVelocity", &CrowdAgent::SetTargetVelocity)
        // [Method] void ResetTarget()
        .addFunction("ResetTarget", &CrowdAgent::ResetTarget)
        // [Method] void SetUpdateNodePosition(bool unodepos)
        .addFunction("SetUpdateNodePosition", &CrowdAgent::SetUpdateNodePosition)
        // [Method] void SetMaxAccel(float maxAccel)
        .addFunction("SetMaxAccel", &CrowdAgent::SetMaxAccel)
        // [Method] void SetMaxSpeed(float maxSpeed)
        .addFunction("SetMaxSpeed", &CrowdAgent::SetMaxSpeed)
        // [Method] void SetRadius(float radius)
        .addFunction("SetRadius", &CrowdAgent::SetRadius)
        // [Method] void SetHeight(float height)
        .addFunction("SetHeight", &CrowdAgent::SetHeight)
        // [Method] void SetQueryFilterType(unsigned queryFilterType)
        .addFunction("SetQueryFilterType", &CrowdAgent::SetQueryFilterType)
        // [Method] void SetObstacleAvoidanceType(unsigned obstacleAvoidanceType)
        .addFunction("SetObstacleAvoidanceType", &CrowdAgent::SetObstacleAvoidanceType)
        // [Method] void SetNavigationQuality(NavigationQuality val)
        .addFunction("SetNavigationQuality", &CrowdAgent::SetNavigationQuality)
        // [Method] void SetNavigationPushiness(NavigationPushiness val)
        .addFunction("SetNavigationPushiness", &CrowdAgent::SetNavigationPushiness)
        
        // [Method] Vector3 GetPosition() const
        .addFunction("GetPosition", &CrowdAgent::GetPosition)
        // [Method] Vector3 GetDesiredVelocity() const
        .addFunction("GetDesiredVelocity", &CrowdAgent::GetDesiredVelocity)
        // [Method] Vector3 GetActualVelocity() const
        .addFunction("GetActualVelocity", &CrowdAgent::GetActualVelocity)
        // [Method] const Vector3& GetTargetPosition() const
        .addFunction("GetTargetPosition", &CrowdAgent::GetTargetPosition)
        // [Method] const Vector3& GetTargetVelocity() const
        .addFunction("GetTargetVelocity", &CrowdAgent::GetTargetVelocity)
        // [Method] CrowdAgentRequestedTarget GetRequestedTargetType() const
        .addFunction("GetRequestedTargetType", &CrowdAgent::GetRequestedTargetType)
        // [Method] CrowdAgentState GetAgentState() const
        .addFunction("GetAgentState", &CrowdAgent::GetAgentState)
        // [Method] CrowdAgentTargetState GetTargetState() const
        .addFunction("GetTargetState", &CrowdAgent::GetTargetState)
        // [Method] bool GetUpdateNodePosition() const
        .addFunction("GetUpdateNodePosition", &CrowdAgent::GetUpdateNodePosition)        

        // [Method] float GetMaxAccel() const
        .addFunction("GetMaxAccel", &CrowdAgent::GetMaxAccel)
        // [Method] float GetMaxSpeed() const
        .addFunction("GetMaxSpeed", &CrowdAgent::GetMaxSpeed)
        // [Method] float GetRadius() const
        .addFunction("GetRadius", &CrowdAgent::GetRadius)
        // [Method] float GetHeight() const
        .addFunction("GetHeight", &CrowdAgent::GetHeight)
        // [Method] unsigned GetQueryFilterType() const
        .addFunction("GetQueryFilterType", &CrowdAgent::GetQueryFilterType)
        // [Method] unsigned GetObstacleAvoidanceType() const
        .addFunction("GetObstacleAvoidanceType", &CrowdAgent::GetObstacleAvoidanceType)
        // [Method] NavigationQuality GetNavigationQuality() const
        .addFunction("GetNavigationQuality", &CrowdAgent::GetNavigationQuality)
        // [Method] NavigationPushiness GetNavigationPushiness() const
        .addFunction("GetNavigationPushiness", &CrowdAgent::GetNavigationPushiness)
        // [Method] bool HasRequestedTarget() const
        .addFunction("HasRequestedTarget", &CrowdAgent::HasRequestedTarget)
        // [Method] bool HasArrived() const
        .addFunction("HasArrived", &CrowdAgent::HasArrived)
        // [Method] bool IsInCrowd() const
        .addFunction("IsInCrowd", &CrowdAgent::IsInCrowd)

        // [Property(Readonly)] Vector3 position
        .addProperty("position", &CrowdAgent::GetPosition)
        // [Property(Readonly)] Vector3 desiredVelocity
        .addProperty("desiredVelocity", &CrowdAgent::GetDesiredVelocity)
        // [Property(Readonly)] Vector3 actualVelocity
        .addProperty("actualVelocity", &CrowdAgent::GetActualVelocity)
        // [Property] const Vector3& targetPosition
        .addProperty("targetPosition", &CrowdAgent::GetTargetPosition, &CrowdAgent::SetTargetPosition)
        // [Property] const Vector3& targetVelocity
        .addProperty("targetVelocity", &CrowdAgent::GetTargetVelocity, &CrowdAgent::SetTargetVelocity)
        // [Property(Readonly)] CrowdAgentRequestedTarget requestedTargetType
        .addProperty("requestedTargetType", &CrowdAgent::GetRequestedTargetType)
        // [Property(Readonly)] CrowdAgentState agentState
        .addProperty("agentState", &CrowdAgent::GetAgentState)
        // [Property(Readonly)] CrowdAgentTargetState targetState
        .addProperty("targetState", &CrowdAgent::GetTargetState)
        // [Property] bool updateNodePosition
        .addProperty("updateNodePosition", &CrowdAgent::GetUpdateNodePosition, &CrowdAgent::SetUpdateNodePosition)
        // [Property] float maxAccel
        .addProperty("maxAccel", &CrowdAgent::GetMaxAccel, &CrowdAgent::SetMaxAccel)
        // [Property] float maxSpeed
        .addProperty("maxSpeed", &CrowdAgent::GetMaxSpeed, &CrowdAgent::SetMaxSpeed)
        // [Property] float radius
        .addProperty("radius", &CrowdAgent::GetRadius, &CrowdAgent::SetRadius)
        // [Property] float height
        .addProperty("height", &CrowdAgent::GetHeight, &CrowdAgent::SetHeight)
        // [Property] unsigned queryFilterType
        .addProperty("queryFilterType", &CrowdAgent::GetQueryFilterType, &CrowdAgent::SetQueryFilterType)
        // [Property] unsigned obstacleAvoidanceType
        .addProperty("obstacleAvoidanceType", &CrowdAgent::GetObstacleAvoidanceType, &CrowdAgent::SetObstacleAvoidanceType)
        // [Property] NavigationQuality navigationQuality
        .addProperty("navigationQuality", &CrowdAgent::GetNavigationQuality, &CrowdAgent::SetNavigationQuality)
        // [Property] NavigationPushiness navigationPushiness
        .addProperty("navigationPushiness", &CrowdAgent::GetNavigationPushiness, &CrowdAgent::SetNavigationPushiness)
        // [Property(Readonly)] bool inCrowd
        .addProperty("inCrowd", &CrowdAgent::IsInCrowd)
        );
}
}

#endif
