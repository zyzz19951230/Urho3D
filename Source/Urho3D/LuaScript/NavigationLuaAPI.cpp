 #include "../Navigation/CrowdAgent.h"
 #include "../Navigation/CrowdManager.h"
 #include "../Navigation/DynamicNavigationMesh.h"
 #include "../Navigation/NavArea.h"
 #include "../Navigation/Navigable.h"
 #include "../Navigation/NavigationEvents.h"
 #include "../Navigation/NavigationMesh.h"
 #include "../Navigation/Obstacle.h"
 #include "../Navigation/OffMeshConnection.h"

 #include "../LuaScript/LuaScriptUtils.h"

 #include <kaguya.hpp>

 namespace Urho3D
 {

 static void RegisterCrowdAgent(kaguya::State& lua)
 {
     using namespace kaguya;

     // enum CrowdAgentRequestedTarget;
     lua["KCA_REQUESTEDTARGET_NONE"] = CA_REQUESTEDTARGET_NONE;
     lua["KCA_REQUESTEDTARGET_POSITION"] = CA_REQUESTEDTARGET_POSITION;
     lua["KCA_REQUESTEDTARGET_VELOCITY"] = CA_REQUESTEDTARGET_VELOCITY;

     // enum CrowdAgentTargetState;
     lua["KCA_TARGET_NONE"] = CA_TARGET_NONE;
     lua["KCA_TARGET_FAILED"] = CA_TARGET_FAILED;
     lua["KCA_TARGET_VALID"] = CA_TARGET_VALID;
     lua["KCA_TARGET_REQUESTING"] = CA_TARGET_REQUESTING;
     lua["KCA_TARGET_WAITINGFORQUEUE"] = CA_TARGET_WAITINGFORQUEUE;
     lua["KCA_TARGET_WAITINGFORPATH"] = CA_TARGET_WAITINGFORPATH;
     lua["KCA_TARGET_VELOCITY"] = CA_TARGET_VELOCITY;

     // enum CrowdAgentState;
     lua["KCA_STATE_INVALID"] = CA_STATE_INVALID;
     lua["KCA_STATE_WALKING"] = CA_STATE_WALKING;
     lua["KCA_STATE_OFFMESH"] = CA_STATE_OFFMESH;

     // enum NavigationQuality;
     lua["KNAVIGATIONQUALITY_LOW"] = NAVIGATIONQUALITY_LOW;
     lua["KNAVIGATIONQUALITY_MEDIUM"] = NAVIGATIONQUALITY_MEDIUM;
     lua["KNAVIGATIONQUALITY_HIGH"] = NAVIGATIONQUALITY_HIGH;

     // enum NavigationPushiness;
     lua["KNAVIGATIONPUSHINESS_LOW"] = NAVIGATIONPUSHINESS_LOW;
     lua["KNAVIGATIONPUSHINESS_MEDIUM"] = NAVIGATIONPUSHINESS_MEDIUM;
     lua["KNAVIGATIONPUSHINESS_HIGH"] = NAVIGATIONPUSHINESS_HIGH;

     lua["KCrowdAgent"].setClass(UserdataMetatable<CrowdAgent, Component>(false)
         .addStaticFunction("new", &KCreateObject<CrowdAgent>)
         .addStaticFunction("__gc", &KReleaseObject<CrowdAgent>)

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
         .addFunction("GetAgentCrowdId", &CrowdAgent::GetAgentCrowdId)
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

         .addProperty("type", &CrowdAgent::GetType)
         .addProperty("typeName", &CrowdAgent::GetTypeName)
         .addProperty("typeInfo", &CrowdAgent::GetTypeInfo)
         .addProperty("position", &CrowdAgent::GetPosition)
         .addProperty("desiredVelocity", &CrowdAgent::GetDesiredVelocity)
         .addProperty("actualVelocity", &CrowdAgent::GetActualVelocity)
         .addProperty("targetPosition", &CrowdAgent::GetTargetPosition, &CrowdAgent::SetTargetPosition)
         .addProperty("targetVelocity", &CrowdAgent::GetTargetVelocity, &CrowdAgent::SetTargetVelocity)
         .addProperty("requestedTargetType", &CrowdAgent::GetRequestedTargetType)
         .addProperty("agentState", &CrowdAgent::GetAgentState)
         .addProperty("targetState", &CrowdAgent::GetTargetState)
         .addProperty("updateNodePosition", &CrowdAgent::GetUpdateNodePosition, &CrowdAgent::SetUpdateNodePosition)
         .addProperty("agentCrowdId", &CrowdAgent::GetAgentCrowdId)
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

 static void RegisterCrowdManager(kaguya::State& lua)
 {
     using namespace kaguya;

     lua["KCrowdObstacleAvoidanceParams"].setClass(UserdataMetatable<CrowdObstacleAvoidanceParams>()

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
     lua["KCrowdManager"].setClass(UserdataMetatable<CrowdManager, Component>(false)
         .addStaticFunction("new", &KCreateObject<CrowdManager>)
         .addStaticFunction("__gc", &KReleaseObject<CrowdManager>)

         .addFunction("DrawDebugGeometry", static_cast<void(CrowdManager::*)(bool)>(&CrowdManager::DrawDebugGeometry))

         .addFunction("SetCrowdTarget", &CrowdManager::SetCrowdTarget)
         .addFunction("SetCrowdVelocity", &CrowdManager::SetCrowdVelocity)
         .addFunction("ResetCrowdTarget", &CrowdManager::ResetCrowdTarget)
         .addFunction("SetMaxAgents", &CrowdManager::SetMaxAgents)
         .addFunction("SetMaxAgentRadius", &CrowdManager::SetMaxAgentRadius)
         .addFunction("SetNavigationMesh", &CrowdManager::SetNavigationMesh)
         .addFunction("SetIncludeFlags", &CrowdManager::SetIncludeFlags)
         .addFunction("SetExcludeFlags", &CrowdManager::SetExcludeFlags)
         .addFunction("SetAreaCost", &CrowdManager::SetAreaCost)
         .addFunction("SetObstacleAvoidanceParams", &CrowdManager::SetObstacleAvoidanceParams)
         .addFunction("GetAgents", &CrowdManager::GetAgents)
         .addFunction("FindNearestPoint", &CrowdManager::FindNearestPoint)
         .addFunction("MoveAlongSurface", &CrowdManager::MoveAlongSurface)
         .addFunction("FindPath", &CrowdManager::FindPath)
         .addFunction("GetRandomPoint", &CrowdManager::GetRandomPoint)
         .addFunction("GetRandomPointInCircle", &CrowdManager::GetRandomPointInCircle)
         .addFunction("GetDistanceToWall", &CrowdManager::GetDistanceToWall)
         .addFunction("Raycast", &CrowdManager::Raycast)
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
         .addProperty("numQueryFilterTypes", &CrowdManager::GetNumQueryFilterTypes)
         .addProperty("numObstacleAvoidanceTypes", &CrowdManager::GetNumObstacleAvoidanceTypes)
     );
 }

 static void RegisterDynamicNavigationMesh(kaguya::State& lua)
 {
     using namespace kaguya;

     lua["KDynamicNavigationMesh"].setClass(UserdataMetatable<DynamicNavigationMesh, NavigationMesh>(false)
         .addStaticFunction("new", &KCreateObject<DynamicNavigationMesh>)
         .addStaticFunction("__gc", &KReleaseObject<DynamicNavigationMesh>)

         .addOverloadedFunctions("Build",
             static_cast<bool(DynamicNavigationMesh::*)()>(&DynamicNavigationMesh::Build),
             static_cast<bool(DynamicNavigationMesh::*)(const BoundingBox&)>(&DynamicNavigationMesh::Build))

         .addFunction("DrawDebugGeometry", static_cast<void(DynamicNavigationMesh::*)(bool)>(&DynamicNavigationMesh::DrawDebugGeometry))

         .addFunction("SetMaxObstacles", &DynamicNavigationMesh::SetMaxObstacles)
         .addFunction("SetMaxLayers", &DynamicNavigationMesh::SetMaxLayers)
         .addFunction("GetMaxObstacles", &DynamicNavigationMesh::GetMaxObstacles)
         .addFunction("GetMaxLayers", &DynamicNavigationMesh::GetMaxLayers)
         .addFunction("SetDrawObstacles", &DynamicNavigationMesh::SetDrawObstacles)
         .addFunction("GetDrawObstacles", &DynamicNavigationMesh::GetDrawObstacles)

         .addProperty("maxObstacles", &DynamicNavigationMesh::GetMaxObstacles, &DynamicNavigationMesh::SetMaxObstacles)
         .addProperty("maxLayers", &DynamicNavigationMesh::GetMaxLayers, &DynamicNavigationMesh::SetMaxLayers)
         .addProperty("drawObstacles", &DynamicNavigationMesh::GetDrawObstacles, &DynamicNavigationMesh::SetDrawObstacles)
     );
 }

 static void RegisterNavArea(kaguya::State& lua)
 {
     using namespace kaguya;

     lua["KNavArea"].setClass(UserdataMetatable<NavArea, Component>(false)
         .addStaticFunction("new", &KCreateObject<NavArea>)
         .addStaticFunction("__gc", &KReleaseObject<NavArea>)

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

     lua["KNavigable"].setClass(UserdataMetatable<Navigable, Component>(false)
         .addStaticFunction("new", &KCreateObject<Navigable>)
         .addStaticFunction("__gc", &KReleaseObject<Navigable>)

         .addFunction("SetRecursive", &Navigable::SetRecursive)
         .addFunction("IsRecursive", &Navigable::IsRecursive)

         .addProperty("recursive", &Navigable::IsRecursive, &Navigable::SetRecursive)
     );
 }

 static void RegisterNavigationEvents(kaguya::State& lua)
 {
     using namespace kaguya;

     lua["KE_NAVIGATION_MESH_REBUILT"] = E_NAVIGATION_MESH_REBUILT;
     lua["KE_NAVIGATION_AREA_REBUILT"] = E_NAVIGATION_AREA_REBUILT;
     lua["KE_CROWD_AGENT_FORMATION"] = E_CROWD_AGENT_FORMATION;
     lua["KE_CROWD_AGENT_NODE_FORMATION"] = E_CROWD_AGENT_NODE_FORMATION;
     lua["KE_CROWD_AGENT_REPOSITION"] = E_CROWD_AGENT_REPOSITION;
     lua["KE_CROWD_AGENT_NODE_REPOSITION"] = E_CROWD_AGENT_NODE_REPOSITION;
     lua["KE_CROWD_AGENT_FAILURE"] = E_CROWD_AGENT_FAILURE;
     lua["KE_CROWD_AGENT_NODE_FAILURE"] = E_CROWD_AGENT_NODE_FAILURE;
     lua["KE_CROWD_AGENT_STATE_CHANGED"] = E_CROWD_AGENT_STATE_CHANGED;
     lua["KE_CROWD_AGENT_NODE_STATE_CHANGED"] = E_CROWD_AGENT_NODE_STATE_CHANGED;
     lua["KE_NAVIGATION_OBSTACLE_ADDED"] = E_NAVIGATION_OBSTACLE_ADDED;
     lua["KE_NAVIGATION_OBSTACLE_REMOVED"] = E_NAVIGATION_OBSTACLE_REMOVED;
 }

 static void RegisterNavigationMesh(kaguya::State& lua)
 {
     using namespace kaguya;

     // enum NavmeshPartitionType;
     lua["KNAVMESH_PARTITION_WATERSHED"] = NAVMESH_PARTITION_WATERSHED;
     lua["KNAVMESH_PARTITION_MONOTONE"] = NAVMESH_PARTITION_MONOTONE;

     // enum NavigationPathPointFlag;
     lua["KNAVPATHFLAG_NONE"] = NAVPATHFLAG_NONE;
     lua["KNAVPATHFLAG_START"] = NAVPATHFLAG_START;
     lua["KNAVPATHFLAG_END"] = NAVPATHFLAG_END;
     lua["KNAVPATHFLAG_OFF_MESH"] = NAVPATHFLAG_OFF_MESH;

     lua["KNavigationPathPoint"].setClass(UserdataMetatable<NavigationPathPoint>()

         .addProperty("position", &NavigationPathPoint::position_)
         .addProperty("flag", &NavigationPathPoint::flag_)
         .addProperty("areaID", &NavigationPathPoint::areaID_)
     );

     lua["KNavigationMesh"].setClass(UserdataMetatable<NavigationMesh, Component>(false)
         .addStaticFunction("new", &KCreateObject<NavigationMesh>)
         .addStaticFunction("__gc", &KReleaseObject<NavigationMesh>)

         .addFunction("DrawDebugGeometry", static_cast<void(NavigationMesh::*)(bool)>(&NavigationMesh::DrawDebugGeometry))

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

         .addFunction("FindNearestPoint", &NavigationMesh::FindNearestPoint)
         .addFunction("MoveAlongSurface", &NavigationMesh::MoveAlongSurface)

         /*
		 // TODO:
		 .addOverloadedFunctions("FindPath",
             static_cast<void(NavigationMesh::*)(PODVector<Vector3>&, const Vector3&, const Vector3&, const Vector3&, const dtQueryFilter*)>(&NavigationMesh::FindPath),
             static_cast<void(NavigationMesh::*)(PODVector<NavigationPathPoint>&, const Vector3&, const Vector3&, const Vector3&, const dtQueryFilter*)>(&NavigationMesh::FindPath))
			 */

         .addFunction("GetRandomPoint", &NavigationMesh::GetRandomPoint)
         .addFunction("GetRandomPointInCircle", &NavigationMesh::GetRandomPointInCircle)
         .addFunction("GetDistanceToWall", &NavigationMesh::GetDistanceToWall)
         .addFunction("Raycast", &NavigationMesh::Raycast)
         .addFunction("GetMeshName", &NavigationMesh::GetMeshName)
         .addFunction("SetMeshName", &NavigationMesh::SetMeshName)
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
         .addFunction("SetPartitionType", &NavigationMesh::SetPartitionType)
         .addFunction("GetPartitionType", &NavigationMesh::GetPartitionType)
         .addFunction("SetDrawOffMeshConnections", &NavigationMesh::SetDrawOffMeshConnections)
         .addFunction("GetDrawOffMeshConnections", &NavigationMesh::GetDrawOffMeshConnections)
         .addFunction("SetDrawNavAreas", &NavigationMesh::SetDrawNavAreas)
         .addFunction("GetDrawNavAreas", &NavigationMesh::GetDrawNavAreas)

         .addProperty("meshName", &NavigationMesh::GetMeshName, &NavigationMesh::SetMeshName)
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

     lua["KObstacle"].setClass(UserdataMetatable<Obstacle, Component>(false)
         .addStaticFunction("new", &KCreateObject<Obstacle>)
         .addStaticFunction("__gc", &KReleaseObject<Obstacle>)

         .addFunction("GetHeight", &Obstacle::GetHeight)
         .addFunction("SetHeight", &Obstacle::SetHeight)
         .addFunction("GetRadius", &Obstacle::GetRadius)
         .addFunction("SetRadius", &Obstacle::SetRadius)
         .addFunction("GetObstacleID", &Obstacle::GetObstacleID)

         .addFunction("DrawDebugGeometry", static_cast<void(Obstacle::*)(bool)>(&Obstacle::DrawDebugGeometry))

         .addProperty("height", &Obstacle::GetHeight, &Obstacle::SetHeight)
         .addProperty("radius", &Obstacle::GetRadius, &Obstacle::SetRadius)
         .addProperty("obstacleID", &Obstacle::GetObstacleID)
     );
 }

 static void RegisterOffMeshConnection(kaguya::State& lua)
 {
     using namespace kaguya;

     lua["KOffMeshConnection"].setClass(UserdataMetatable<OffMeshConnection, Component>(false)
         .addStaticFunction("new", &KCreateObject<OffMeshConnection>)
         .addStaticFunction("__gc", &KReleaseObject<OffMeshConnection>)

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
     RegisterNavigationEvents(lua);
     RegisterNavigationMesh(lua);
     RegisterObstacle(lua);
     RegisterOffMeshConnection(lua);
 }
}
