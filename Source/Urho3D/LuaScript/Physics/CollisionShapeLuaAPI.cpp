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

#ifdef URHO3D_PHYSICS

#include "../../Precompiled.h"

#include "../../Graphics/CustomGeometry.h"
#include "../../Graphics/Model.h"
#include "../../Physics/CollisionShape.h"
#include "../../Physics/PhysicsWorld.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetBox, CollisionShape, SetBox, 1, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetSphere, CollisionShape, SetSphere, 1, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetStaticPlane, CollisionShape, SetStaticPlane, 0, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCylinder, CollisionShape, SetCylinder, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCapsule, CollisionShape, SetCapsule, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCone, CollisionShape, SetCone, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetTriangleMesh, CollisionShape, SetTriangleMesh, 1, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCustomTriangleMesh, CollisionShape, SetCustomTriangleMesh, 1, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetConvexHull, CollisionShape, SetConvexHull, 1, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetCustomConvexHull, CollisionShape, SetCustomConvexHull, 1, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(CollisionShapeSetTerrain, CollisionShape, SetTerrain, 0, 1);

void RegisterCollisionShape(kaguya::State& lua)
{
    using namespace kaguya;

    // enum ShapeType;
    lua["SHAPE_BOX"] = SHAPE_BOX;
    lua["SHAPE_SPHERE"] = SHAPE_SPHERE;
    lua["SHAPE_STATICPLANE"] = SHAPE_STATICPLANE;
    lua["SHAPE_CYLINDER"] = SHAPE_CYLINDER;
    lua["SHAPE_CAPSULE"] = SHAPE_CAPSULE;
    lua["SHAPE_CONE"] = SHAPE_CONE;
    lua["SHAPE_TRIANGLEMESH"] = SHAPE_TRIANGLEMESH;
    lua["SHAPE_CONVEXHULL"] = SHAPE_CONVEXHULL;
    lua["SHAPE_TERRAIN"] = SHAPE_TERRAIN;
    
    lua["CollisionShape"].setClass(UserdataMetatable<CollisionShape, Component>()
        .addStaticFunction("new", &CreateObject<CollisionShape>)

        .addFunction("SetBox", CollisionShapeSetBox())
        .addFunction("SetSphere", CollisionShapeSetSphere())
        .addFunction("SetStaticPlane", CollisionShapeSetStaticPlane())
        .addFunction("SetCylinder", CollisionShapeSetCylinder())
        .addFunction("SetCapsule", CollisionShapeSetCapsule())
        .addFunction("SetCone", CollisionShapeSetCone())
        .addFunction("SetTriangleMesh", CollisionShapeSetTriangleMesh())
        .addFunction("SetCustomTriangleMesh", CollisionShapeSetCustomTriangleMesh())
        .addFunction("SetConvexHull", CollisionShapeSetConvexHull())
        .addFunction("SetCustomConvexHull", CollisionShapeSetCustomConvexHull())
        .addFunction("SetTerrain", CollisionShapeSetTerrain())

        .addFunction("SetShapeType", &CollisionShape::SetShapeType)
        .addFunction("SetSize", &CollisionShape::SetSize)
        .addFunction("SetPosition", &CollisionShape::SetPosition)
        .addFunction("SetRotation", &CollisionShape::SetRotation)
        .addFunction("SetTransform", &CollisionShape::SetTransform)
        .addFunction("SetMargin", &CollisionShape::SetMargin)
        .addFunction("SetModel", &CollisionShape::SetModel)
        .addFunction("SetLodLevel", &CollisionShape::SetLodLevel)

        .addFunction("GetPhysicsWorld", &CollisionShape::GetPhysicsWorld)
        .addFunction("GetShapeType", &CollisionShape::GetShapeType)
        .addFunction("GetSize", &CollisionShape::GetSize)
        .addFunction("GetPosition", &CollisionShape::GetPosition)
        .addFunction("GetRotation", &CollisionShape::GetRotation)
        .addFunction("GetMargin", &CollisionShape::GetMargin)
        .addFunction("GetModel", &CollisionShape::GetModel)
        .addFunction("GetLodLevel", &CollisionShape::GetLodLevel)
        .addFunction("GetWorldBoundingBox", &CollisionShape::GetWorldBoundingBox)

        .addProperty("physicsWorld", &CollisionShape::GetPhysicsWorld)
        .addProperty("shapeType", &CollisionShape::GetShapeType, &CollisionShape::SetShapeType)
        .addProperty("size", &CollisionShape::GetSize, &CollisionShape::SetSize)
        .addProperty("position", &CollisionShape::GetPosition, &CollisionShape::SetPosition)
        .addProperty("rotation", &CollisionShape::GetRotation, &CollisionShape::SetRotation)
        .addProperty("margin", &CollisionShape::GetMargin, &CollisionShape::SetMargin)
        .addProperty("model", &CollisionShape::GetModel, &CollisionShape::SetModel)
        .addProperty("lodLevel", &CollisionShape::GetLodLevel, &CollisionShape::SetLodLevel)
        .addProperty("worldBoundingBox", &CollisionShape::GetWorldBoundingBox)
        .addProperty("terrain", &CollisionShape::SetTerrain)
        );
}
}

#endif
