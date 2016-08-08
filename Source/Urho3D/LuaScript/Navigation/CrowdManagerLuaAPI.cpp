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
#include "../../Navigation/CrowdManager.h"
#include "../../Navigation/NavigationMesh.h"
#include "../../Scene/Node.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(CrowdManagerSetCrowdTarget, CrowdManager, SetCrowdTarget, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CrowdManagerSetCrowdVelocity, CrowdManager, SetCrowdVelocity, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CrowdManagerResetCrowdTarget, CrowdManager, ResetCrowdTarget, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CrowdManagerGetAgents, CrowdManager, GetAgents, 0, 2);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(CrowdManagerFindNearestPoint, CrowdManager, FindNearestPoint, 2, 3, Vector3(CrowdManager::*)(const Vector3&, int, dtPolyRef*));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(CrowdManagerMoveAlongSurface, CrowdManager, MoveAlongSurface, 3, 4, Vector3(CrowdManager::*)(const Vector3&, const Vector3&, int, int));

static PODVector<Vector3> CrowdManagerFindPath(CrowdManager* self, Vector3& start, const Vector3& end, int queryFilterType)
{
    PODVector<Vector3> dest;
    self->FindPath(dest, start, end, queryFilterType);
    return dest;
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(CrowdManagerGetRandomPoint, CrowdManager, GetRandomPoint, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CrowdManagerGetRandomPointInCircle, CrowdManager, GetRandomPointInCircle, 3, 4);

static kaguya::standard::tuple<float, Vector3, Vector3> CrowdManagerGetDistanceToWall(CrowdManager* self, const Vector3& point, float radius, int queryFilterType)
{
    Vector3 hitPos;
    Vector3 hitNormal;
    float distance = self->GetDistanceToWall(point, radius, queryFilterType, &hitPos, &hitNormal);
    return kaguya::standard::make_tuple(distance, hitPos, hitNormal);
}

static kaguya::standard::tuple<Vector3, Vector3> CrowdManagerRaycast(CrowdManager* self, const Vector3& start, const Vector3& end, int queryFilterType)
{
    Vector3 hitNormal;
    Vector3 result = self->Raycast(start, end, queryFilterType, &hitNormal);
    return kaguya::standard::make_tuple(result, hitNormal);
}

void RegisterCrowdManager(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CrowdObstacleAvoidanceParams"].setClass(UserdataMetatable<CrowdObstacleAvoidanceParams>()

        .addProperty("velBias", &CrowdObstacleAvoidanceParams::velBias)
        .addProperty("weightDesVel", &CrowdObstacleAvoidanceParams::weightDesVel)
        .addProperty("weightCurVel", &CrowdObstacleAvoidanceParams::weightCurVel)
        .addProperty("weightSide", &CrowdObstacleAvoidanceParams::weightSide)
        .addProperty("weightToi", &CrowdObstacleAvoidanceParams::weightToi)
        .addProperty("horizTime", &CrowdObstacleAvoidanceParams::horizTime)
        .addProperty("gridSize", &CrowdObstacleAvoidanceParams::gridSize)
        .addProperty("adaptiveDivs", &CrowdObstacleAvoidanceParams::adaptiveDivs)
        .addProperty("adaptiveRings", &CrowdObstacleAvoidanceParams::adaptiveRings)
        .addProperty("adaptiveDepth", &CrowdObstacleAvoidanceParams::adaptiveDepth)
        );

    lua["CrowdManager"].setClass(UserdataMetatable<CrowdManager, Component>()
        .addStaticFunction("new", &CreateObject<CrowdManager>)

        .addFunction("DrawDebugGeometry", static_cast<void(CrowdManager::*)(bool)>(&CrowdManager::DrawDebugGeometry))

        .addFunction("SetCrowdTarget", CrowdManagerSetCrowdTarget())
        .addFunction("SetCrowdVelocity", CrowdManagerSetCrowdVelocity())
        .addFunction("ResetCrowdTarget", CrowdManagerResetCrowdTarget())

        .addFunction("SetMaxAgents", &CrowdManager::SetMaxAgents)
        .addFunction("SetMaxAgentRadius", &CrowdManager::SetMaxAgentRadius)
        .addFunction("SetNavigationMesh", &CrowdManager::SetNavigationMesh)
        .addFunction("SetIncludeFlags", &CrowdManager::SetIncludeFlags)
        .addFunction("SetExcludeFlags", &CrowdManager::SetExcludeFlags)
        .addFunction("SetAreaCost", &CrowdManager::SetAreaCost)

        .addFunction("SetObstacleAvoidanceParams", &CrowdManager::SetObstacleAvoidanceParams)

        .addFunction("GetAgents", CrowdManagerGetAgents())

        .addFunction("FindNearestPoint", CrowdManagerFindNearestPoint())
        
        .addFunction("MoveAlongSurface", CrowdManagerMoveAlongSurface())

        .addStaticFunction("FindPath", &CrowdManagerFindPath)
        
        .addFunction("GetRandomPoint", CrowdManagerGetRandomPoint())
        .addFunction("GetRandomPointInCircle", CrowdManagerGetRandomPointInCircle())

        .addStaticFunction("GetDistanceToWall", &CrowdManagerGetDistanceToWall)        
        .addStaticFunction("Raycast", &CrowdManagerRaycast)

        .addFunction("GetMaxAgents", &CrowdManager::GetMaxAgents)
        .addFunction("GetMaxAgentRadius", &CrowdManager::GetMaxAgentRadius)
        .addFunction("GetNavigationMesh", &CrowdManager::GetNavigationMesh)
        .addFunction("GetNumQueryFilterTypes", &CrowdManager::GetNumQueryFilterTypes)
        .addFunction("GetNumAreas", &CrowdManager::GetNumAreas)
        .addFunction("GetIncludeFlags", &CrowdManager::GetIncludeFlags)
        .addFunction("GetExcludeFlags", &CrowdManager::GetExcludeFlags)
        .addFunction("GetAreaCost", &CrowdManager::GetAreaCost)
        .addFunction("GetNumObstacleAvoidanceTypes", &CrowdManager::GetNumObstacleAvoidanceTypes)
        .addFunction("GetObstacleAvoidanceParams", &CrowdManager::GetObstacleAvoidanceParams)
        
        .addProperty("maxAgents", &CrowdManager::GetMaxAgents, &CrowdManager::SetMaxAgents)
        .addProperty("maxAgentRadius", &CrowdManager::GetMaxAgentRadius, &CrowdManager::SetMaxAgentRadius)
        .addProperty("navigationMesh", &CrowdManager::GetNavigationMesh, &CrowdManager::SetNavigationMesh)
        );
}
}

#endif
