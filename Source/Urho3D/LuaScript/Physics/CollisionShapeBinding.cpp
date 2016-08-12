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

    // [Enum] ShapeType
    lua["SHAPE_BOX"] = SHAPE_BOX;
    lua["SHAPE_SPHERE"] = SHAPE_SPHERE;
    lua["SHAPE_STATICPLANE"] = SHAPE_STATICPLANE;
    lua["SHAPE_CYLINDER"] = SHAPE_CYLINDER;
    lua["SHAPE_CAPSULE"] = SHAPE_CAPSULE;
    lua["SHAPE_CONE"] = SHAPE_CONE;
    lua["SHAPE_TRIANGLEMESH"] = SHAPE_TRIANGLEMESH;
    lua["SHAPE_CONVEXHULL"] = SHAPE_CONVEXHULL;
    lua["SHAPE_TERRAIN"] = SHAPE_TERRAIN;
    
    // [Class] CollisionShape : Component
    lua["CollisionShape"].setClass(UserdataMetatable<CollisionShape, Component>()
        // [Constructor] CollisionShape()
        .addStaticFunction("new", &CreateObject<CollisionShape>)

        // [Method] void SetBox(const Vector3& size, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY)
        .addFunction("SetBox", CollisionShapeSetBox())
        // [Method] void SetSphere(float diameter, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY)
        .addFunction("SetSphere", CollisionShapeSetSphere())
        // [Method] void SetStaticPlane(const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY)
        .addFunction("SetStaticPlane", CollisionShapeSetStaticPlane())
        // [Method] void SetCylinder(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY)
        .addFunction("SetCylinder", CollisionShapeSetCylinder())
        // [Method] void SetCapsule(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY)
        .addFunction("SetCapsule", CollisionShapeSetCapsule())
        // [Method] void SetCone(float diameter, float height, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY)
        .addFunction("SetCone", CollisionShapeSetCone())
        // [Method] void SetTriangleMesh(Model* model, unsigned lodLevel = 0, const Vector3& scale = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY)
        .addFunction("SetTriangleMesh", CollisionShapeSetTriangleMesh())
        // [Method] void SetCustomTriangleMesh(CustomGeometry* custom, const Vector3& scale = Vector3::ONE, const Vector3& position = Vector3::ZERO,
        .addFunction("SetCustomTriangleMesh", CollisionShapeSetCustomTriangleMesh())
        // [Method] void SetConvexHull(Model* model, unsigned lodLevel = 0, const Vector3& scale = Vector3::ONE, const Vector3& position = Vector3::ZERO, const Quaternion& rotation = Quaternion::IDENTITY)
        .addFunction("SetConvexHull", CollisionShapeSetConvexHull())
        // [Method] void SetCustomConvexHull(CustomGeometry* custom, const Vector3& scale = Vector3::ONE, const Vector3& position = Vector3::ZERO,
        .addFunction("SetCustomConvexHull", CollisionShapeSetCustomConvexHull())
        // [Method] void SetTerrain(unsigned lodLevel = 0)
        .addFunction("SetTerrain", CollisionShapeSetTerrain())

        // [Method] void SetShapeType(ShapeType type)
        .addFunction("SetShapeType", &CollisionShape::SetShapeType)
        // [Method] void SetSize(const Vector3& size)
        .addFunction("SetSize", &CollisionShape::SetSize)
        // [Method] void SetPosition(const Vector3& position)
        .addFunction("SetPosition", &CollisionShape::SetPosition)
        // [Method] void SetRotation(const Quaternion& rotation)
        .addFunction("SetRotation", &CollisionShape::SetRotation)
        // [Method] void SetTransform(const Vector3& position, const Quaternion& rotation)
        .addFunction("SetTransform", &CollisionShape::SetTransform)
        // [Method] void SetMargin(float margin)
        .addFunction("SetMargin", &CollisionShape::SetMargin)
        // [Method] void SetModel(Model* model)
        .addFunction("SetModel", &CollisionShape::SetModel)
        // [Method] void SetLodLevel(unsigned lodLevel)
        .addFunction("SetLodLevel", &CollisionShape::SetLodLevel)

        // [Method] PhysicsWorld* GetPhysicsWorld() const
        .addFunction("GetPhysicsWorld", &CollisionShape::GetPhysicsWorld)
        // [Method] ShapeType GetShapeType() const
        .addFunction("GetShapeType", &CollisionShape::GetShapeType)
        // [Method] const Vector3& GetSize() const
        .addFunction("GetSize", &CollisionShape::GetSize)
        // [Method] const Vector3& GetPosition() const
        .addFunction("GetPosition", &CollisionShape::GetPosition)
        // [Method] const Quaternion& GetRotation() const
        .addFunction("GetRotation", &CollisionShape::GetRotation)
        // [Method] float GetMargin() const
        .addFunction("GetMargin", &CollisionShape::GetMargin)
        // [Method] Model* GetModel() const
        .addFunction("GetModel", &CollisionShape::GetModel)
        // [Method] unsigned GetLodLevel() const
        .addFunction("GetLodLevel", &CollisionShape::GetLodLevel)
        // [Method] BoundingBox GetWorldBoundingBox() const
        .addFunction("GetWorldBoundingBox", &CollisionShape::GetWorldBoundingBox)

        // [Property(Readonly)] PhysicsWorld* physicsWorld
        .addProperty("physicsWorld", &CollisionShape::GetPhysicsWorld)
        // [Property] ShapeType shapeType
        .addProperty("shapeType", &CollisionShape::GetShapeType, &CollisionShape::SetShapeType)
        // [Property] const Vector3& size
        .addProperty("size", &CollisionShape::GetSize, &CollisionShape::SetSize)
        // [Property] const Vector3& position
        .addProperty("position", &CollisionShape::GetPosition, &CollisionShape::SetPosition)
        // [Property] const Quaternion& rotation
        .addProperty("rotation", &CollisionShape::GetRotation, &CollisionShape::SetRotation)
        // [Property] float margin
        .addProperty("margin", &CollisionShape::GetMargin, &CollisionShape::SetMargin)
        // [Property] Model* model
        .addProperty("model", &CollisionShape::GetModel, &CollisionShape::SetModel)
        // [Property] unsigned lodLevel
        .addProperty("lodLevel", &CollisionShape::GetLodLevel, &CollisionShape::SetLodLevel)
        // [Property(Readonly)] BoundingBox worldBoundingBox
        .addProperty("worldBoundingBox", &CollisionShape::GetWorldBoundingBox)
        // [Property(Writeonly)] unsigned terrain
        .addProperty("terrain", &CollisionShape::SetTerrain)
        );
}
}

#endif
