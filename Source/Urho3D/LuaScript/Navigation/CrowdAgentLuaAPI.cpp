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

    // enum CrowdAgentRequestedTarget;
    lua["CA_REQUESTEDTARGET_NONE"] = CA_REQUESTEDTARGET_NONE;
    lua["CA_REQUESTEDTARGET_POSITION"] = CA_REQUESTEDTARGET_POSITION;
    lua["CA_REQUESTEDTARGET_VELOCITY"] = CA_REQUESTEDTARGET_VELOCITY;

    // enum CrowdAgentTargetState;
    lua["CA_TARGET_NONE"] = CA_TARGET_NONE;
    lua["CA_TARGET_FAILED"] = CA_TARGET_FAILED;
    lua["CA_TARGET_VALID"] = CA_TARGET_VALID;
    lua["CA_TARGET_REQUESTING"] = CA_TARGET_REQUESTING;
    lua["CA_TARGET_WAITINGFORQUEUE"] = CA_TARGET_WAITINGFORQUEUE;
    lua["CA_TARGET_WAITINGFORPATH"] = CA_TARGET_WAITINGFORPATH;
    lua["CA_TARGET_VELOCITY"] = CA_TARGET_VELOCITY;

    // enum CrowdAgentState;
    lua["CA_STATE_INVALID"] = CA_STATE_INVALID;
    lua["CA_STATE_WALKING"] = CA_STATE_WALKING;
    lua["CA_STATE_OFFMESH"] = CA_STATE_OFFMESH;

    // enum NavigationQuality;
    lua["NAVIGATIONQUALITY_LOW"] = NAVIGATIONQUALITY_LOW;
    lua["NAVIGATIONQUALITY_MEDIUM"] = NAVIGATIONQUALITY_MEDIUM;
    lua["NAVIGATIONQUALITY_HIGH"] = NAVIGATIONQUALITY_HIGH;

    // enum NavigationPushiness;
    lua["NAVIGATIONPUSHINESS_LOW"] = NAVIGATIONPUSHINESS_LOW;
    lua["NAVIGATIONPUSHINESS_MEDIUM"] = NAVIGATIONPUSHINESS_MEDIUM;
    lua["NAVIGATIONPUSHINESS_HIGH"] = NAVIGATIONPUSHINESS_HIGH;

    lua["CrowdAgent"].setClass(UserdataMetatable<CrowdAgent, Component>()
        .addStaticFunction("new", &CreateObject<CrowdAgent>)

        .addFunction("DrawDebugGeometry", static_cast<void(CrowdAgent::*)(bool)>(&CrowdAgent::DrawDebugGeometry))

        .addFunction("SetTargetPosition", &CrowdAgent::SetTargetPosition)
        .addFunction("SetTargetVelocity", &CrowdAgent::SetTargetVelocity)
        .addFunction("ResetTarget", &CrowdAgent::ResetTarget)
        .addFunction("SetUpdateNodePosition", &CrowdAgent::SetUpdateNodePosition)
        .addFunction("SetMaxAccel", &CrowdAgent::SetMaxAccel)
        .addFunction("SetMaxSpeed", &CrowdAgent::SetMaxSpeed)
        .addFunction("SetRadius", &CrowdAgent::SetRadius)
        .addFunction("SetHeight", &CrowdAgent::SetHeight)
        .addFunction("SetQueryFilterType", &CrowdAgent::SetQueryFilterType)
        .addFunction("SetObstacleAvoidanceType", &CrowdAgent::SetObstacleAvoidanceType)
        .addFunction("SetNavigationQuality", &CrowdAgent::SetNavigationQuality)
        .addFunction("SetNavigationPushiness", &CrowdAgent::SetNavigationPushiness)
        
        .addFunction("GetPosition", &CrowdAgent::GetPosition)
        .addFunction("GetDesiredVelocity", &CrowdAgent::GetDesiredVelocity)
        .addFunction("GetActualVelocity", &CrowdAgent::GetActualVelocity)
        .addFunction("GetTargetPosition", &CrowdAgent::GetTargetPosition)
        .addFunction("GetTargetVelocity", &CrowdAgent::GetTargetVelocity)
        .addFunction("GetRequestedTargetType", &CrowdAgent::GetRequestedTargetType)
        .addFunction("GetAgentState", &CrowdAgent::GetAgentState)
        .addFunction("GetTargetState", &CrowdAgent::GetTargetState)
        .addFunction("GetUpdateNodePosition", &CrowdAgent::GetUpdateNodePosition)        

        .addFunction("GetMaxAccel", &CrowdAgent::GetMaxAccel)
        .addFunction("GetMaxSpeed", &CrowdAgent::GetMaxSpeed)
        .addFunction("GetRadius", &CrowdAgent::GetRadius)
        .addFunction("GetHeight", &CrowdAgent::GetHeight)
        .addFunction("GetQueryFilterType", &CrowdAgent::GetQueryFilterType)
        .addFunction("GetObstacleAvoidanceType", &CrowdAgent::GetObstacleAvoidanceType)
        .addFunction("GetNavigationQuality", &CrowdAgent::GetNavigationQuality)
        .addFunction("GetNavigationPushiness", &CrowdAgent::GetNavigationPushiness)
        .addFunction("HasRequestedTarget", &CrowdAgent::HasRequestedTarget)
        .addFunction("HasArrived", &CrowdAgent::HasArrived)
        .addFunction("IsInCrowd", &CrowdAgent::IsInCrowd)

        .addProperty("position", &CrowdAgent::GetPosition)
        .addProperty("desiredVelocity", &CrowdAgent::GetDesiredVelocity)
        .addProperty("actualVelocity", &CrowdAgent::GetActualVelocity)
        .addProperty("targetPosition", &CrowdAgent::GetTargetPosition, &CrowdAgent::SetTargetPosition)
        .addProperty("targetVelocity", &CrowdAgent::GetTargetVelocity, &CrowdAgent::SetTargetVelocity)
        .addProperty("requestedTargetType", &CrowdAgent::GetRequestedTargetType)
        .addProperty("agentState", &CrowdAgent::GetAgentState)
        .addProperty("targetState", &CrowdAgent::GetTargetState)
        .addProperty("updateNodePosition", &CrowdAgent::GetUpdateNodePosition, &CrowdAgent::SetUpdateNodePosition)
        .addProperty("maxAccel", &CrowdAgent::GetMaxAccel, &CrowdAgent::SetMaxAccel)
        .addProperty("maxSpeed", &CrowdAgent::GetMaxSpeed, &CrowdAgent::SetMaxSpeed)
        .addProperty("radius", &CrowdAgent::GetRadius, &CrowdAgent::SetRadius)
        .addProperty("height", &CrowdAgent::GetHeight, &CrowdAgent::SetHeight)
        .addProperty("queryFilterType", &CrowdAgent::GetQueryFilterType, &CrowdAgent::SetQueryFilterType)
        .addProperty("obstacleAvoidanceType", &CrowdAgent::GetObstacleAvoidanceType, &CrowdAgent::SetObstacleAvoidanceType)
        .addProperty("navigationQuality", &CrowdAgent::GetNavigationQuality, &CrowdAgent::SetNavigationQuality)
        .addProperty("navigationPushiness", &CrowdAgent::GetNavigationPushiness, &CrowdAgent::SetNavigationPushiness)
        .addProperty("inCrowd", &CrowdAgent::IsInCrowd)
        );
}
}

#endif
