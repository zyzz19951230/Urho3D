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

    // [Class] CrowdObstacleAvoidanceParams
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

    // [Class] CrowdManager : Component
    lua["CrowdManager"].setClass(UserdataMetatable<CrowdManager, Component>()
        .addStaticFunction("new", &CreateObject<CrowdManager>)

        // [Method] void DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
        .addFunction("DrawDebugGeometry", static_cast<void(CrowdManager::*)(bool)>(&CrowdManager::DrawDebugGeometry))

        // [Method] void SetCrowdTarget(const Vector3& position, Node* node = 0)
        .addFunction("SetCrowdTarget", CrowdManagerSetCrowdTarget())
        // [Method] void SetCrowdVelocity(const Vector3& velocity, Node* node = 0)
        .addFunction("SetCrowdVelocity", CrowdManagerSetCrowdVelocity())
        // [Method] void ResetCrowdTarget(Node* node = 0)
        .addFunction("ResetCrowdTarget", CrowdManagerResetCrowdTarget())

        // [Method] void SetMaxAgents(unsigned maxAgents)
        .addFunction("SetMaxAgents", &CrowdManager::SetMaxAgents)
        // [Method] void SetMaxAgentRadius(float maxAgentRadius)
        .addFunction("SetMaxAgentRadius", &CrowdManager::SetMaxAgentRadius)
        // [Method] void SetNavigationMesh(NavigationMesh* navMesh)
        .addFunction("SetNavigationMesh", &CrowdManager::SetNavigationMesh)
        // [Method] void SetIncludeFlags(unsigned queryFilterType, unsigned short flags)
        .addFunction("SetIncludeFlags", &CrowdManager::SetIncludeFlags)
        // [Method] void SetExcludeFlags(unsigned queryFilterType, unsigned short flags)
        .addFunction("SetExcludeFlags", &CrowdManager::SetExcludeFlags)
        // [Method] void SetAreaCost(unsigned queryFilterType, unsigned areaID, float cost)
        .addFunction("SetAreaCost", &CrowdManager::SetAreaCost)

        // [Method] void SetObstacleAvoidanceParams(unsigned obstacleAvoidanceType, const CrowdObstacleAvoidanceParams& params)
        .addFunction("SetObstacleAvoidanceParams", &CrowdManager::SetObstacleAvoidanceParams)

        // [Method] PODVector<CrowdAgent*> GetAgents(Node* node = 0, bool inCrowdFilter = true) const
        .addFunction("GetAgents", CrowdManagerGetAgents())

        // [Method] Vector3 FindNearestPoint(const Vector3& point, int queryFilterType, dtPolyRef* nearestRef = 0)
        .addFunction("FindNearestPoint", CrowdManagerFindNearestPoint())
        
        // [Method] Vector3 MoveAlongSurface(const Vector3& start, const Vector3& end, int queryFilterType, int maxVisited = 3)
        .addFunction("MoveAlongSurface", CrowdManagerMoveAlongSurface())

        .addStaticFunction("FindPath", &CrowdManagerFindPath)
        
        // [Method] Vector3 GetRandomPoint(int queryFilterType, dtPolyRef* randomRef = 0)
        .addFunction("GetRandomPoint", CrowdManagerGetRandomPoint())
        // [Method] Vector3 GetRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, dtPolyRef* randomRef = 0)
        .addFunction("GetRandomPointInCircle", CrowdManagerGetRandomPointInCircle())

        .addStaticFunction("GetDistanceToWall", &CrowdManagerGetDistanceToWall)        
        .addStaticFunction("Raycast", &CrowdManagerRaycast)

        // [Method] unsigned GetMaxAgents() const
        .addFunction("GetMaxAgents", &CrowdManager::GetMaxAgents)
        // [Method] float GetMaxAgentRadius() const
        .addFunction("GetMaxAgentRadius", &CrowdManager::GetMaxAgentRadius)
        // [Method] NavigationMesh* GetNavigationMesh() const
        .addFunction("GetNavigationMesh", &CrowdManager::GetNavigationMesh)
        // [Method] unsigned GetNumQueryFilterTypes() const
        .addFunction("GetNumQueryFilterTypes", &CrowdManager::GetNumQueryFilterTypes)
        // [Method] unsigned GetNumAreas(unsigned queryFilterType) const
        .addFunction("GetNumAreas", &CrowdManager::GetNumAreas)
        // [Method] unsigned short GetIncludeFlags(unsigned queryFilterType) const
        .addFunction("GetIncludeFlags", &CrowdManager::GetIncludeFlags)
        // [Method] unsigned short GetExcludeFlags(unsigned queryFilterType) const
        .addFunction("GetExcludeFlags", &CrowdManager::GetExcludeFlags)
        // [Method] float GetAreaCost(unsigned queryFilterType, unsigned areaID) const
        .addFunction("GetAreaCost", &CrowdManager::GetAreaCost)
        // [Method] unsigned GetNumObstacleAvoidanceTypes() const
        .addFunction("GetNumObstacleAvoidanceTypes", &CrowdManager::GetNumObstacleAvoidanceTypes)
        // [Method] const CrowdObstacleAvoidanceParams& GetObstacleAvoidanceParams(unsigned obstacleAvoidanceType) const
        .addFunction("GetObstacleAvoidanceParams", &CrowdManager::GetObstacleAvoidanceParams)
        
        // [Property] unsigned maxAgents
        .addProperty("maxAgents", &CrowdManager::GetMaxAgents, &CrowdManager::SetMaxAgents)
        // [Property] float maxAgentRadius
        .addProperty("maxAgentRadius", &CrowdManager::GetMaxAgentRadius, &CrowdManager::SetMaxAgentRadius)
        // [Property] NavigationMesh* navigationMesh
        .addProperty("navigationMesh", &CrowdManager::GetNavigationMesh, &CrowdManager::SetNavigationMesh)
        );
}
}

#endif
