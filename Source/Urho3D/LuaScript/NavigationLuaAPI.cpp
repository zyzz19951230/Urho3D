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

#include "../Precompiled.h"

#include "../LuaScript/LuaScriptUtils.h"
#include "../Navigation/CrowdAgent.h"
#include "../Navigation/CrowdManager.h"
#include "../Navigation/DynamicNavigationMesh.h"
#include "../Navigation/NavArea.h"
#include "../Navigation/Navigable.h"
#include "../Navigation/NavigationMesh.h"
#include "../Navigation/Obstacle.h"
#include "../Navigation/OffMeshConnection.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterCrowdAgent(kaguya::State& lua)
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

static void CrowdManagerSetCrowdTarget0(CrowdManager* self, const Vector3& position)
{
    self->SetCrowdTarget(position);
}

static void CrowdManagerSetCrowdTarget1(CrowdManager* self, const Vector3& position, Node* node)
{
    self->SetCrowdTarget(position, node);
}

static void CrowdManagerSetCrowdVelocity0(CrowdManager* self, const Vector3& velocity)
{
    self->SetCrowdVelocity(velocity);
}

static void CrowdManagerSetCrowdVelocity1(CrowdManager* self, const Vector3& velocity, Node* node)
{
    self->SetCrowdVelocity(velocity, node);
}

static void CrowdManagerResetCrowdTarget0(CrowdManager* self)
{
    self->ResetCrowdTarget();
}

static void CrowdManagerResetCrowdTarget1(CrowdManager* self, Node* node)
{
    self->ResetCrowdTarget(node);
}

static PODVector<CrowdAgent*> CrowdManagerGetAgents0(const CrowdManager* self)
{
    return self->GetAgents();
}

static PODVector<CrowdAgent*> CrowdManagerGetAgents1(const CrowdManager* self, Node* node)
{
    return self->GetAgents(node);
}

static PODVector<CrowdAgent*> CrowdManagerGetAgents2(const CrowdManager* self, Node* node, bool inCrowdFilter)
{
    return self->GetAgents(node, inCrowdFilter);
}

static Vector3 CrowdManagerFindNearestPoint(CrowdManager* self, const Vector3& point, int queryFilterType)
{
    return self->FindNearestPoint(point, queryFilterType);
}

static Vector3 CrowdManagerMoveAlongSurface0(CrowdManager* self, const Vector3& start, const Vector3& end, int queryFilterType)
{
    return self->MoveAlongSurface(start, end, queryFilterType);
}

static Vector3 CrowdManagerMoveAlongSurface1(CrowdManager* self, const Vector3& start, const Vector3& end, int queryFilterType, int maxVisited)
{
    return self->MoveAlongSurface(start, end, queryFilterType, maxVisited);
}

static PODVector<Vector3> CrowdManagerFindPath(CrowdManager* self, Vector3& start, const Vector3& end, int queryFilterType)
{
    PODVector<Vector3> dest;
    self->FindPath(dest, start, end, queryFilterType);
    return dest;
}

static Vector3 CrowdManagerGetRandomPoint(CrowdManager* self, int queryFilterType)
{
    return self->GetRandomPoint(queryFilterType);
}

static Vector3 CrowdManagerGetRandomPointInCircle(CrowdManager* self, const Vector3& center, float radius, int queryFilterType)
{
    return self->GetRandomPointInCircle(center, radius, queryFilterType);
}

static std::tuple<float, Vector3, Vector3> CrowdManagerGetDistanceToWall(CrowdManager* self, const Vector3& point, float radius, int queryFilterType)
{
    Vector3 hitPos;
    Vector3 hitNormal;
    float distance = self->GetDistanceToWall(point, radius, queryFilterType, &hitPos, &hitNormal);
    return std::make_tuple(distance, hitPos, hitNormal);
}

static std::tuple<Vector3, Vector3> CrowdManagerRaycast(CrowdManager* self, const Vector3& start, const Vector3& end, int queryFilterType)
{
    Vector3 hitNormal;
    Vector3 result = self->Raycast(start, end, queryFilterType, &hitNormal);
    return std::make_tuple(result, hitNormal);
}

static void RegisterCrowdManager(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CrowdManager"].setClass(UserdataMetatable<CrowdManager, Component>()
        .addStaticFunction("new", &CreateObject<CrowdManager>)

        .addFunction("DrawDebugGeometry", static_cast<void(CrowdManager::*)(bool)>(&CrowdManager::DrawDebugGeometry))

        ADD_OVERLOADED_FUNCTIONS_2(CrowdManager, SetCrowdTarget)
        ADD_OVERLOADED_FUNCTIONS_2(CrowdManager, SetCrowdVelocity)
        ADD_OVERLOADED_FUNCTIONS_2(CrowdManager, ResetCrowdTarget)

        .addFunction("SetMaxAgents", &CrowdManager::SetMaxAgents)
        .addFunction("SetMaxAgentRadius", &CrowdManager::SetMaxAgentRadius)
        .addFunction("SetNavigationMesh", &CrowdManager::SetNavigationMesh)
        .addFunction("SetIncludeFlags", &CrowdManager::SetIncludeFlags)
        .addFunction("SetExcludeFlags", &CrowdManager::SetExcludeFlags)
        .addFunction("SetAreaCost", &CrowdManager::SetAreaCost)

        .addFunction("SetObstacleAvoidanceParams", &CrowdManager::SetObstacleAvoidanceParams)

        ADD_OVERLOADED_FUNCTIONS_2(CrowdManager, GetAgents)        
        .addStaticFunction("FindNearestPoint", &CrowdManagerFindNearestPoint)
        ADD_OVERLOADED_FUNCTIONS_2(CrowdManager, MoveAlongSurface)
        .addStaticFunction("FindPath", &CrowdManagerFindPath)
        .addStaticFunction("GetRandomPoint", &CrowdManagerGetRandomPoint)
        .addStaticFunction("GetRandomPointInCircle", &CrowdManagerGetRandomPointInCircle)
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
        
        .addProperty("maxAgents", &CrowdManager::GetMaxAgents, &CrowdManager::SetMaxAgents)
        .addProperty("maxAgentRadius", &CrowdManager::GetMaxAgentRadius, &CrowdManager::SetMaxAgentRadius)
        .addProperty("navigationMesh", &CrowdManager::GetNavigationMesh, &CrowdManager::SetNavigationMesh)
        );
}

static void RegisterDynamicNavigationMesh(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DynamicNavigationMesh"].setClass(UserdataMetatable<DynamicNavigationMesh, NavigationMesh>()
        .addStaticFunction("new", &CreateObject<DynamicNavigationMesh>)

        .addFunction("SetMaxObstacles", &DynamicNavigationMesh::SetMaxObstacles)
        .addFunction("SetMaxLayers", &DynamicNavigationMesh::SetMaxLayers)
        .addFunction("SetDrawObstacles", &DynamicNavigationMesh::SetDrawObstacles)

        .addFunction("GetDrawObstacles", &DynamicNavigationMesh::GetDrawObstacles)
        .addFunction("GetMaxLayers", &DynamicNavigationMesh::GetMaxLayers)
        .addFunction("GetMaxObstacles", &DynamicNavigationMesh::GetMaxObstacles)

        .addProperty("maxObstacles", &DynamicNavigationMesh::GetMaxObstacles, &DynamicNavigationMesh::SetMaxObstacles)
        .addProperty("maxLayers", &DynamicNavigationMesh::GetMaxLayers, &DynamicNavigationMesh::SetMaxLayers)
        .addProperty("drawObstacles", &DynamicNavigationMesh::GetDrawObstacles, &DynamicNavigationMesh::SetDrawObstacles)
        );
}

static void RegisterNavArea(kaguya::State& lua)
{
    using namespace kaguya;

    lua["NavArea"].setClass(UserdataMetatable<NavArea, Component>()
        .addStaticFunction("new", &CreateObject<NavArea>)

        .addFunction("GetAreaID", &NavArea::GetAreaID)
        .addFunction("SetAreaID", &NavArea::SetAreaID)

        .addFunction("GetBoundingBox", &NavArea::GetBoundingBox)
        .addFunction("SetBoundingBox", &NavArea::SetBoundingBox)

        .addFunction("GetWorldBoundingBox", &NavArea::GetWorldBoundingBox)

        .addProperty("areaID", &NavArea::GetAreaID, &NavArea::SetAreaID)
        .addProperty("boundingBox", &NavArea::GetBoundingBox, &NavArea::SetBoundingBox)
        .addProperty("worldBoundingBox", &NavArea::GetWorldBoundingBox)
        );
}

static void RegisterNavigable(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Navigable"].setClass(UserdataMetatable<Navigable, Component>()
        .addStaticFunction("new", &CreateObject<Navigable>)

        .addFunction("SetRecursive", &Navigable::SetRecursive)
        .addFunction("IsRecursive", &Navigable::IsRecursive)

        .addProperty("recursive", &Navigable::IsRecursive, &Navigable::SetRecursive)
        );
}

static Vector3 NavigationMeshFindNearestPoint0(NavigationMesh* self, const Vector3& point)
{
    return self->FindNearestPoint(point);
}

static Vector3 NavigationMeshFindNearestPoint1(NavigationMesh* self, const Vector3& point, const Vector3& extents)
{
    return self->FindNearestPoint(point, extents);
}

static Vector3 NavigationMeshMoveAlongSurface0(NavigationMesh* self, const Vector3& start, const Vector3& end)
{
    return self->MoveAlongSurface(start, end);
}

static Vector3 NavigationMeshMoveAlongSurface1(NavigationMesh* self, const Vector3& start, const Vector3& end, const Vector3& extents)
{
    return self->MoveAlongSurface(start, end, extents);
}

static Vector3 NavigationMeshMoveAlongSurface2(NavigationMesh* self, const Vector3& start, const Vector3& end, const Vector3& extents, int maxVisited)
{
    return self->MoveAlongSurface(start, end, extents, maxVisited);
}

static PODVector<Vector3> NavigationMeshFindPath0(NavigationMesh* self, const Vector3& start, const Vector3& end)
{
    PODVector<Vector3> dest;
    self->FindPath(dest, start, end);
    return dest;
}

static PODVector<Vector3> NavigationMeshFindPath1(NavigationMesh* self, const Vector3& start, const Vector3& end, const Vector3& extents)
{
    PODVector<Vector3> dest;
    self->FindPath(dest, start, end, extents);
    return dest;
}

static Vector3 NavigationMeshGetRandomPoint(NavigationMesh* self)
{
    return self->GetRandomPoint();
}

static Vector3 NavigationMeshGetRandomPointInCircle0(NavigationMesh* self, const Vector3& center, float radius)
{
    return self->GetRandomPointInCircle(center, radius);
}

static Vector3 NavigationMeshGetRandomPointInCircle1(NavigationMesh* self, const Vector3& center, float radius, const Vector3& extents)
{
    return self->GetRandomPointInCircle(center, radius, extents);
}

static float NavigationMeshGetDistanceToWall0(NavigationMesh* self, const Vector3& point, float radius)
{
    return self->GetDistanceToWall(point, radius);
}

static float NavigationMeshGetDistanceToWall1(NavigationMesh* self, const Vector3& point, float radius, const Vector3& extents)
{
    return self->GetDistanceToWall(point, radius, extents);
}

static Vector3 NavigationMeshRaycast0(NavigationMesh* self, const Vector3& start, const Vector3& end)
{
    return self->Raycast(start, end);
}

static Vector3 NavigationMeshRaycast1(NavigationMesh* self, const Vector3& start, const Vector3& end, const Vector3& extents)
{
    return self->Raycast(start, end, extents);
}

static void RegisterNavigationMesh(kaguya::State& lua)
{
    using namespace kaguya;

    // enum NavmeshPartitionType;
    lua["NAVMESH_PARTITION_WATERSHED"] = NAVMESH_PARTITION_WATERSHED;
    lua["NAVMESH_PARTITION_MONOTONE"] = NAVMESH_PARTITION_MONOTONE;

    lua["NavigationGeometryInfo"].setClass(UserdataMetatable<NavigationGeometryInfo>()
        .addProperty("component",&NavigationGeometryInfo::component_)
        .addProperty("lodLevel", &NavigationGeometryInfo::lodLevel_)
        .addProperty("transform", &NavigationGeometryInfo::transform_)
        .addProperty("boundingBox", &NavigationGeometryInfo::boundingBox_)
        );

    lua["NavigationMesh"].setClass(UserdataMetatable<NavigationMesh, Component>()
        .addStaticFunction("new", &CreateObject<NavigationMesh>)

        .addFunction("SetTileSize", &NavigationMesh::SetTileSize)
        .addFunction("SetCellSize", &NavigationMesh::SetCellSize)
        .addFunction("SetCellHeight", &NavigationMesh::SetCellHeight)
        .addFunction("SetAgentHeight", &NavigationMesh::SetAgentHeight)
        .addFunction("SetAgentRadius", &NavigationMesh::SetAgentRadius)
        .addFunction("SetAgentMaxClimb", &NavigationMesh::SetAgentMaxClimb)
        .addFunction("SetAgentMaxSlope", &NavigationMesh::SetAgentMaxSlope)
        .addFunction("SetRegionMinSize", &NavigationMesh::SetRegionMinSize)
        .addFunction("SetRegionMergeSize", &NavigationMesh::SetRegionMergeSize)
        .addFunction("SetEdgeMaxLength", &NavigationMesh::SetEdgeMaxLength)
        .addFunction("SetEdgeMaxError", &NavigationMesh::SetEdgeMaxError)
        .addFunction("SetDetailSampleDistance", &NavigationMesh::SetDetailSampleDistance)
        .addFunction("SetDetailSampleMaxError", &NavigationMesh::SetDetailSampleMaxError)
        .addFunction("SetPadding", &NavigationMesh::SetPadding)
        .addFunction("SetAreaCost", &NavigationMesh::SetAreaCost)

        .addOverloadedFunctions("Build",
            static_cast<bool(NavigationMesh::*)()>(&NavigationMesh::Build),
            static_cast<bool(NavigationMesh::*)(const BoundingBox&)>(&NavigationMesh::Build))

        .addFunction("SetPartitionType", &NavigationMesh::SetPartitionType)
        .addFunction("SetDrawOffMeshConnections", &NavigationMesh::SetDrawOffMeshConnections)
        .addFunction("SetDrawNavAreas", &NavigationMesh::SetDrawNavAreas)

        ADD_OVERLOADED_FUNCTIONS_2(NavigationMesh, FindNearestPoint)
        ADD_OVERLOADED_FUNCTIONS_3(NavigationMesh, MoveAlongSurface)
        ADD_OVERLOADED_FUNCTIONS_2(NavigationMesh, FindPath)

        .addStaticFunction("GetRandomPoint", &NavigationMeshGetRandomPoint)

        ADD_OVERLOADED_FUNCTIONS_2(NavigationMesh, GetRandomPointInCircle)
        ADD_OVERLOADED_FUNCTIONS_2(NavigationMesh, GetDistanceToWall)
        ADD_OVERLOADED_FUNCTIONS_2(NavigationMesh, Raycast)

        .addFunction("DrawDebugGeometry", static_cast<void (NavigationMesh::*)(bool)>(&NavigationMesh::DrawDebugGeometry))

        .addFunction("GetTileSize", &NavigationMesh::GetTileSize)
        .addFunction("GetCellSize", &NavigationMesh::GetCellSize)
        .addFunction("GetCellHeight", &NavigationMesh::GetCellHeight)
        .addFunction("GetAgentHeight", &NavigationMesh::GetAgentHeight)
        .addFunction("GetAgentRadius", &NavigationMesh::GetAgentRadius)
        .addFunction("GetAgentMaxClimb", &NavigationMesh::GetAgentMaxClimb)
        .addFunction("GetAgentMaxSlope", &NavigationMesh::GetAgentMaxSlope)
        .addFunction("GetRegionMinSize", &NavigationMesh::GetRegionMinSize)
        .addFunction("GetRegionMergeSize", &NavigationMesh::GetRegionMergeSize)
        .addFunction("GetEdgeMaxLength", &NavigationMesh::GetEdgeMaxLength)
        .addFunction("GetEdgeMaxError", &NavigationMesh::GetEdgeMaxError)
        .addFunction("GetDetailSampleDistance", &NavigationMesh::GetDetailSampleDistance)
        .addFunction("GetDetailSampleMaxError", &NavigationMesh::GetDetailSampleMaxError)
        .addFunction("GetPadding", &NavigationMesh::GetPadding)
        .addFunction("GetAreaCost", &NavigationMesh::GetAreaCost)
        .addFunction("IsInitialized", &NavigationMesh::IsInitialized)
        .addFunction("GetBoundingBox", &NavigationMesh::GetBoundingBox)
        .addFunction("GetWorldBoundingBox", &NavigationMesh::GetWorldBoundingBox)
        .addFunction("GetNumTiles", &NavigationMesh::GetNumTiles)
        .addFunction("GetPartitionType", &NavigationMesh::GetPartitionType)
        .addFunction("GetDrawOffMeshConnections", &NavigationMesh::GetDrawOffMeshConnections)
        .addFunction("GetDrawNavAreas", &NavigationMesh::GetDrawNavAreas)

        .addProperty("tileSize", &NavigationMesh::GetTileSize, &NavigationMesh::SetTileSize)
        .addProperty("cellSize", &NavigationMesh::GetCellSize, &NavigationMesh::SetCellSize)
        .addProperty("cellHeight", &NavigationMesh::GetCellHeight, &NavigationMesh::SetCellHeight)
        .addProperty("agentHeight", &NavigationMesh::GetAgentHeight, &NavigationMesh::SetAgentHeight)
        .addProperty("agentRadius", &NavigationMesh::GetAgentRadius, &NavigationMesh::SetAgentRadius)
        .addProperty("agentMaxClimb", &NavigationMesh::GetAgentMaxClimb, &NavigationMesh::SetAgentMaxClimb)
        .addProperty("agentMaxSlope", &NavigationMesh::GetAgentMaxSlope, &NavigationMesh::SetAgentMaxSlope)
        .addProperty("regionMinSize", &NavigationMesh::GetRegionMinSize, &NavigationMesh::SetRegionMinSize)
        .addProperty("regionMergeSize", &NavigationMesh::GetRegionMergeSize, &NavigationMesh::SetRegionMergeSize)
        .addProperty("edgeMaxLength", &NavigationMesh::GetEdgeMaxLength, &NavigationMesh::SetEdgeMaxLength)
        .addProperty("edgeMaxError", &NavigationMesh::GetEdgeMaxError, &NavigationMesh::SetEdgeMaxError)
        .addProperty("detailSampleDistance", &NavigationMesh::GetDetailSampleDistance, &NavigationMesh::SetDetailSampleDistance)
        .addProperty("detailSampleMaxError", &NavigationMesh::GetDetailSampleMaxError, &NavigationMesh::SetDetailSampleMaxError)
        .addProperty("padding", &NavigationMesh::GetPadding, &NavigationMesh::SetPadding)
        .addProperty("initialized", &NavigationMesh::IsInitialized)
        .addProperty("boundingBox", &NavigationMesh::GetBoundingBox)
        .addProperty("worldBoundingBox", &NavigationMesh::GetWorldBoundingBox)
        .addProperty("numTiles", &NavigationMesh::GetNumTiles)
        .addProperty("partitionType", &NavigationMesh::GetPartitionType, &NavigationMesh::SetPartitionType)
        .addProperty("drawOffMeshConnections", &NavigationMesh::GetDrawOffMeshConnections, &NavigationMesh::SetDrawOffMeshConnections)
        .addProperty("drawNavAreas", &NavigationMesh::GetDrawNavAreas, &NavigationMesh::SetDrawNavAreas)
        );
}

static void RegisterObstacle(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Obstacle"].setClass(UserdataMetatable<Obstacle, Component>()
        .addStaticFunction("new", &CreateObject<Obstacle>)

        .addFunction("GetHeight", &Obstacle::GetHeight)
        .addFunction("SetHeight", &Obstacle::SetHeight)

        .addFunction("GetRadius", &Obstacle::GetRadius)
        .addFunction("SetRadius", &Obstacle::SetRadius)

        .addProperty("height", &Obstacle::GetHeight, &Obstacle::SetHeight)
        .addProperty("radius", &Obstacle::GetRadius, &Obstacle::SetRadius)
        );
}

static void RegisterOffMeshConnection(kaguya::State& lua)
{
    using namespace kaguya;

    lua["OffMeshConnection"].setClass(UserdataMetatable<OffMeshConnection, Component>()
        .addStaticFunction("new", &CreateObject<OffMeshConnection>)

        .addFunction("SetEndPoint", &OffMeshConnection::SetEndPoint)
        .addFunction("SetRadius", &OffMeshConnection::SetRadius)
        .addFunction("SetBidirectional", &OffMeshConnection::SetBidirectional)
        .addFunction("SetMask", &OffMeshConnection::SetMask)
        .addFunction("SetAreaID", &OffMeshConnection::SetAreaID)
        
        .addFunction("GetEndPoint", &OffMeshConnection::GetEndPoint)
        .addFunction("GetRadius", &OffMeshConnection::GetRadius)
        .addFunction("IsBidirectional", &OffMeshConnection::IsBidirectional)
        .addFunction("GetMask", &OffMeshConnection::GetMask)
        .addFunction("GetAreaID", &OffMeshConnection::GetAreaID)

        .addProperty("endPoint", &OffMeshConnection::GetEndPoint, &OffMeshConnection::SetEndPoint)
        .addProperty("radius", &OffMeshConnection::GetRadius, &OffMeshConnection::SetRadius)
        .addProperty("bidirectional", &OffMeshConnection::IsBidirectional, &OffMeshConnection::SetBidirectional)
        .addProperty("mask", &OffMeshConnection::GetMask, &OffMeshConnection::SetMask)
        .addProperty("areaID", &OffMeshConnection::GetAreaID, &OffMeshConnection::SetAreaID)
        );
}

void RegisterNavigationLuaAPI(kaguya::State& lua)
{
    RegisterCrowdAgent(lua);
    RegisterCrowdManager(lua);
    RegisterDynamicNavigationMesh(lua);
    RegisterNavArea(lua);
    RegisterNavigable(lua);
    RegisterNavigationMesh(lua);
    RegisterObstacle(lua);
    RegisterOffMeshConnection(lua);
}
}