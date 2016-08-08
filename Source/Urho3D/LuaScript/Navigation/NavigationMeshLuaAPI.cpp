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

#include "../../Navigation/NavigationMesh.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <Detour/DetourNavMeshQuery.h>
#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(NavigationMeshFindNearestPoint, NavigationMesh, FindNearestPoint, 1, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NavigationMeshMoveAlongSurface, NavigationMesh, MoveAlongSurface, 2, 5);

static PODVector<Vector3> NavigationMeshFindPath(NavigationMesh* self, const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = 0)
{
    PODVector<Vector3> dest;
    self->FindPath(dest, start, end, extents, filter);
    return dest;
}

KAGUYA_FUNCTION_OVERLOADS(NavigationMeshFindPathOverloads, NavigationMeshFindPath, 3, 5);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(NavigationMeshGetRandomPoint, NavigationMesh, GetRandomPoint, 0, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NavigationMeshGetRandomPointInCircle, NavigationMesh, GetRandomPointInCircle, 2, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NavigationMeshGetDistanceToWall, NavigationMesh, GetDistanceToWall, 2, 6);

static kaguya::standard::tuple<Vector3, Vector3> NavigationMeshRaycast(NavigationMesh* self, const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE)
{
    Vector3 hitNormal;
    Vector3 result = self->Raycast(start, end, extents, 0, &hitNormal);
    return kaguya::standard::make_tuple(result, hitNormal);
}

KAGUYA_FUNCTION_OVERLOADS(NavigationMeshRaycastOverloads, NavigationMeshRaycast, 3, 4);

void RegisterNavigationMesh(kaguya::State& lua)
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

        .addFunction("FindNearestPoint", NavigationMeshFindNearestPoint())
        .addFunction("MoveAlongSurface", NavigationMeshMoveAlongSurface())
        
        .addStaticFunction("FindPath", NavigationMeshFindPathOverloads())

        .addFunction("GetRandomPoint", NavigationMeshGetRandomPoint())
        .addFunction("GetRandomPointInCircle", NavigationMeshGetRandomPointInCircle())
        .addFunction("GetDistanceToWall", NavigationMeshGetDistanceToWall())
        
        .addStaticFunction("Raycast", NavigationMeshRaycastOverloads())

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
}

#endif
