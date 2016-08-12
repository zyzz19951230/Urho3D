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

    // [Enum] NavmeshPartitionType
    lua["NAVMESH_PARTITION_WATERSHED"] = NAVMESH_PARTITION_WATERSHED;
    lua["NAVMESH_PARTITION_MONOTONE"] = NAVMESH_PARTITION_MONOTONE;

    // [Class] NavigationGeometryInfo
    lua["NavigationGeometryInfo"].setClass(UserdataMetatable<NavigationGeometryInfo>()
        
        // [Field] Component* component
        .addProperty("component", &NavigationGeometryInfo::component_)
        // [Field] unsigned lodLevel
        .addProperty("lodLevel", &NavigationGeometryInfo::lodLevel_)
        // [Field] Matrix3x4 transform
        .addProperty("transform", &NavigationGeometryInfo::transform_)
        // [Field] BoundingBox boundingBox
        .addProperty("boundingBox", &NavigationGeometryInfo::boundingBox_)
        );

    // [Class] NavigationMesh : Component
    lua["NavigationMesh"].setClass(UserdataMetatable<NavigationMesh, Component>()
        // [Constructor] NavigationMesh()
        .addStaticFunction("new", &CreateObject<NavigationMesh>)

        // [Method] void SetTileSize(int size)
        .addFunction("SetTileSize", &NavigationMesh::SetTileSize)
        // [Method] void SetCellSize(float size)
        .addFunction("SetCellSize", &NavigationMesh::SetCellSize)
        // [Method] void SetCellHeight(float height)
        .addFunction("SetCellHeight", &NavigationMesh::SetCellHeight)
        // [Method] void SetAgentHeight(float height)
        .addFunction("SetAgentHeight", &NavigationMesh::SetAgentHeight)
        // [Method] void SetAgentRadius(float radius)
        .addFunction("SetAgentRadius", &NavigationMesh::SetAgentRadius)
        // [Method] void SetAgentMaxClimb(float maxClimb)
        .addFunction("SetAgentMaxClimb", &NavigationMesh::SetAgentMaxClimb)
        // [Method] void SetAgentMaxSlope(float maxSlope)
        .addFunction("SetAgentMaxSlope", &NavigationMesh::SetAgentMaxSlope)
        // [Method] void SetRegionMinSize(float size)
        .addFunction("SetRegionMinSize", &NavigationMesh::SetRegionMinSize)
        // [Method] void SetRegionMergeSize(float size)
        .addFunction("SetRegionMergeSize", &NavigationMesh::SetRegionMergeSize)
        // [Method] void SetEdgeMaxLength(float length)
        .addFunction("SetEdgeMaxLength", &NavigationMesh::SetEdgeMaxLength)
        // [Method] void SetEdgeMaxError(float error)
        .addFunction("SetEdgeMaxError", &NavigationMesh::SetEdgeMaxError)
        // [Method] void SetDetailSampleDistance(float distance)
        .addFunction("SetDetailSampleDistance", &NavigationMesh::SetDetailSampleDistance)
        // [Method] void SetDetailSampleMaxError(float error)
        .addFunction("SetDetailSampleMaxError", &NavigationMesh::SetDetailSampleMaxError)
        // [Method] void SetPadding(const Vector3& padding)
        .addFunction("SetPadding", &NavigationMesh::SetPadding)
        // [Method] void SetAreaCost(unsigned areaID, float cost)
        .addFunction("SetAreaCost", &NavigationMesh::SetAreaCost)

        .addOverloadedFunctions("Build",
            // [Method] bool Build()
            static_cast<bool(NavigationMesh::*)()>(&NavigationMesh::Build),
            // [Method] bool Build(const BoundingBox& boundingBox)
            static_cast<bool(NavigationMesh::*)(const BoundingBox&)>(&NavigationMesh::Build))

        // [Method] void SetPartitionType(NavmeshPartitionType aType)
        .addFunction("SetPartitionType", &NavigationMesh::SetPartitionType)
        // [Method] void SetDrawOffMeshConnections(bool enable)
        .addFunction("SetDrawOffMeshConnections", &NavigationMesh::SetDrawOffMeshConnections)
        // [Method] void SetDrawNavAreas(bool enable)
        .addFunction("SetDrawNavAreas", &NavigationMesh::SetDrawNavAreas)

        .addFunction("FindNearestPoint", NavigationMeshFindNearestPoint())
        // [Method] Vector3 MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, int maxVisited = 3,
        .addFunction("MoveAlongSurface", NavigationMeshMoveAlongSurface())
        
        // [Method] PODVector<Vector3> FindPath(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = 0)
        .addStaticFunction("FindPath", NavigationMeshFindPathOverloads())

        // [Method] Vector3 GetRandomPoint(const dtQueryFilter* filter = 0, dtPolyRef* randomRef = 0)
        .addFunction("GetRandomPoint", NavigationMeshGetRandomPoint())
        // [Method] Vector3 GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = 0, dtPolyRef* randomRef = 0);
        .addFunction("GetRandomPointInCircle", NavigationMeshGetRandomPointInCircle())
        // [Method] float GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = 0, Vector3* hitPos = 0, Vector3* hitNormal = 0)
        .addFunction("GetDistanceToWall", NavigationMeshGetDistanceToWall())
        
        // [Method] tuple<Vector3, Vector3> Raycast(NavigationMesh* self, const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE)
        .addStaticFunction("Raycast", NavigationMeshRaycastOverloads())

        // [Method] void DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
        .addFunction("DrawDebugGeometry", static_cast<void (NavigationMesh::*)(bool)>(&NavigationMesh::DrawDebugGeometry))

        // [Method] int GetTileSize() const
        .addFunction("GetTileSize", &NavigationMesh::GetTileSize)
        // [Method] float GetCellSize() const
        .addFunction("GetCellSize", &NavigationMesh::GetCellSize)
        // [Method] float GetCellHeight() const
        .addFunction("GetCellHeight", &NavigationMesh::GetCellHeight)
        // [Method] float GetAgentHeight() const
        .addFunction("GetAgentHeight", &NavigationMesh::GetAgentHeight)
        // [Method] float GetAgentRadius() const
        .addFunction("GetAgentRadius", &NavigationMesh::GetAgentRadius)
        // [Method] float GetAgentMaxClimb() const
        .addFunction("GetAgentMaxClimb", &NavigationMesh::GetAgentMaxClimb)
        // [Method] float GetAgentMaxSlope() const
        .addFunction("GetAgentMaxSlope", &NavigationMesh::GetAgentMaxSlope)
        // [Method] float GetRegionMinSize() const
        .addFunction("GetRegionMinSize", &NavigationMesh::GetRegionMinSize)
        // [Method] float GetRegionMergeSize() const
        .addFunction("GetRegionMergeSize", &NavigationMesh::GetRegionMergeSize)
        // [Method] float GetEdgeMaxLength() const
        .addFunction("GetEdgeMaxLength", &NavigationMesh::GetEdgeMaxLength)
        // [Method] float GetEdgeMaxError() const
        .addFunction("GetEdgeMaxError", &NavigationMesh::GetEdgeMaxError)
        // [Method] float GetDetailSampleDistance() const
        .addFunction("GetDetailSampleDistance", &NavigationMesh::GetDetailSampleDistance)
        // [Method] float GetDetailSampleMaxError() const
        .addFunction("GetDetailSampleMaxError", &NavigationMesh::GetDetailSampleMaxError)
        // [Method] const Vector3& GetPadding() const
        .addFunction("GetPadding", &NavigationMesh::GetPadding)
        // [Method] float GetAreaCost(unsigned areaID) const
        .addFunction("GetAreaCost", &NavigationMesh::GetAreaCost)
        // [Method] bool IsInitialized() const
        .addFunction("IsInitialized", &NavigationMesh::IsInitialized)
        // [Method] const BoundingBox& GetBoundingBox() const
        .addFunction("GetBoundingBox", &NavigationMesh::GetBoundingBox)
        // [Method] BoundingBox GetWorldBoundingBox() const
        .addFunction("GetWorldBoundingBox", &NavigationMesh::GetWorldBoundingBox)
        // [Method] IntVector2 GetNumTiles() const
        .addFunction("GetNumTiles", &NavigationMesh::GetNumTiles)
        // [Method] NavmeshPartitionType GetPartitionType() const
        .addFunction("GetPartitionType", &NavigationMesh::GetPartitionType)
        // [Method] bool GetDrawOffMeshConnections() const
        .addFunction("GetDrawOffMeshConnections", &NavigationMesh::GetDrawOffMeshConnections)
        // [Method] bool GetDrawNavAreas() const
        .addFunction("GetDrawNavAreas", &NavigationMesh::GetDrawNavAreas)

        // [Property] int tileSize
        .addProperty("tileSize", &NavigationMesh::GetTileSize, &NavigationMesh::SetTileSize)
        // [Property] float cellSize
        .addProperty("cellSize", &NavigationMesh::GetCellSize, &NavigationMesh::SetCellSize)
        // [Property] float cellHeight
        .addProperty("cellHeight", &NavigationMesh::GetCellHeight, &NavigationMesh::SetCellHeight)
        // [Property] float agentHeight
        .addProperty("agentHeight", &NavigationMesh::GetAgentHeight, &NavigationMesh::SetAgentHeight)
        // [Property] float agentRadius
        .addProperty("agentRadius", &NavigationMesh::GetAgentRadius, &NavigationMesh::SetAgentRadius)
        // [Property] float agentMaxClimb
        .addProperty("agentMaxClimb", &NavigationMesh::GetAgentMaxClimb, &NavigationMesh::SetAgentMaxClimb)
        // [Property] float agentMaxSlope
        .addProperty("agentMaxSlope", &NavigationMesh::GetAgentMaxSlope, &NavigationMesh::SetAgentMaxSlope)
        // [Property] float regionMinSize
        .addProperty("regionMinSize", &NavigationMesh::GetRegionMinSize, &NavigationMesh::SetRegionMinSize)
        // [Property] float regionMergeSize
        .addProperty("regionMergeSize", &NavigationMesh::GetRegionMergeSize, &NavigationMesh::SetRegionMergeSize)
        // [Property] float edgeMaxLength
        .addProperty("edgeMaxLength", &NavigationMesh::GetEdgeMaxLength, &NavigationMesh::SetEdgeMaxLength)
        // [Property] float edgeMaxError
        .addProperty("edgeMaxError", &NavigationMesh::GetEdgeMaxError, &NavigationMesh::SetEdgeMaxError)
        // [Property] float detailSampleDistance
        .addProperty("detailSampleDistance", &NavigationMesh::GetDetailSampleDistance, &NavigationMesh::SetDetailSampleDistance)
        // [Property] float detailSampleMaxError
        .addProperty("detailSampleMaxError", &NavigationMesh::GetDetailSampleMaxError, &NavigationMesh::SetDetailSampleMaxError)
        // [Property] const Vector3& padding
        .addProperty("padding", &NavigationMesh::GetPadding, &NavigationMesh::SetPadding)
        // [Property(Readonly)] bool initialized
        .addProperty("initialized", &NavigationMesh::IsInitialized)
        // [Property(Readonly)] const BoundingBox& boundingBox
        .addProperty("boundingBox", &NavigationMesh::GetBoundingBox)
        // [Property(Readonly)] BoundingBox worldBoundingBox
        .addProperty("worldBoundingBox", &NavigationMesh::GetWorldBoundingBox)
        // [Property(Readonly)] IntVector2 numTiles
        .addProperty("numTiles", &NavigationMesh::GetNumTiles)
        // [Property] NavmeshPartitionType partitionType
        .addProperty("partitionType", &NavigationMesh::GetPartitionType, &NavigationMesh::SetPartitionType)
        // [Property] bool drawOffMeshConnections
        .addProperty("drawOffMeshConnections", &NavigationMesh::GetDrawOffMeshConnections, &NavigationMesh::SetDrawOffMeshConnections)
        // [Property] bool drawNavAreas
        .addProperty("drawNavAreas", &NavigationMesh::GetDrawNavAreas, &NavigationMesh::SetDrawNavAreas)
        );
}
}

#endif
