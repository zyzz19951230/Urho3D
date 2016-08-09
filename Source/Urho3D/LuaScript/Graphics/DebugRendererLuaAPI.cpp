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

#include "../../Precompiled.h"

#include "../../Graphics/DebugRenderer.h"
#include "../../Graphics/Camera.h"
#include "../../Graphics/Skeleton.h"
#include "../../Math/Polyhedron.h"
#include "../../Scene/Node.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(DebugRendererAddLine, DebugRenderer, AddLine, 3, 4, void(DebugRenderer::*)(const Vector3&, const Vector3&, const Color&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(DebugRendererAddTriangle, DebugRenderer, AddTriangle, 4, 5, void(DebugRenderer::*)(const Vector3&, const Vector3&, const Vector3&, const Color&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddNode, DebugRenderer, AddNode, 1, 3);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(DebugRendererAddBoundingBox0, DebugRenderer, AddBoundingBox, 2, 3, void(DebugRenderer::*)(const BoundingBox&, const Color&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(DebugRendererAddBoundingBox1, DebugRenderer, AddBoundingBox, 3, 4, void(DebugRenderer::*)(const BoundingBox&, const Matrix3x4&, const Color&, bool));

KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddFrustum, DebugRenderer, AddFrustum, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddPolyhedron, DebugRenderer, AddPolyhedron, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddSphere, DebugRenderer, AddSphere, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddCylinder, DebugRenderer, AddCylinder, 4, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddSkeleton, DebugRenderer, AddSkeleton, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddTriangleMesh, DebugRenderer, AddTriangleMesh, 8, 9);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddCircle, DebugRenderer, AddCircle, 4, 6);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddCross, DebugRenderer, AddCross, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(DebugRendererAddQuad, DebugRenderer, AddQuad, 4, 5);

void RegisterDebugRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] DebugRenderer : Component
    lua["DebugRenderer"].setClass(UserdataMetatable<DebugRenderer, Component>()
        .addStaticFunction("new", &CreateObject<DebugRenderer>)
        
        // [Method] void SetView(Camera* camera)
        .addFunction("SetView", &DebugRenderer::SetView)

        // [Method] void AddLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest = true)
        .addFunction("AddLine", DebugRendererAddLine())
        // [Method] void AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Color& color, bool depthTest = true)
        .addFunction("AddTriangle", DebugRendererAddTriangle())
        // [Method] void AddNode(Node* node, float scale = 1.0f, bool depthTest = true)
        .addFunction("AddNode", DebugRendererAddNode())
        
        .addOverloadedFunctions("AddBoundingBox", 
            DebugRendererAddBoundingBox0(),
            DebugRendererAddBoundingBox1())

        // [Method] void AddFrustum(const Frustum& frustum, const Color& color, bool depthTest = true)
        .addFunction("AddFrustum", DebugRendererAddFrustum())
        // [Method] void AddPolyhedron(const Polyhedron& poly, const Color& color, bool depthTest = true)
        .addFunction("AddPolyhedron", DebugRendererAddPolyhedron())
        // [Method] void AddSphere(const Sphere& sphere, const Color& color, bool depthTest = true)
        .addFunction("AddSphere", DebugRendererAddSphere())
        // [Method] void AddCylinder(const Vector3& position, float radius, float height, const Color& color, bool depthTest = true)
        .addFunction("AddCylinder", DebugRendererAddCylinder())
        // [Method] void AddSkeleton(const Skeleton& skeleton, const Color& color, bool depthTest = true)
        .addFunction("AddSkeleton", DebugRendererAddSkeleton())
        .addFunction("AddTriangleMesh", DebugRendererAddTriangleMesh())
        // [Method] void AddCircle(const Vector3& center, const Vector3& normal, float radius, const Color& color, int steps = 64, bool depthTest = true)
        .addFunction("AddCircle", DebugRendererAddCircle())
        // [Method] void AddCross(const Vector3& center, float size, const Color& color, bool depthTest = true)
        .addFunction("AddCross", DebugRendererAddCross())
        // [Method] void AddQuad(const Vector3& center, float width, float height, const Color& color, bool depthTest = true)
        .addFunction("AddQuad", DebugRendererAddQuad())

        // [Method] void Render()
        .addFunction("Render", &DebugRenderer::Render)
        // [Method] const Matrix3x4& GetView() const
        .addFunction("GetView", &DebugRenderer::GetView)
        // [Method] const Matrix4& GetProjection() const
        .addFunction("GetProjection", &DebugRenderer::GetProjection)
        // [Method] const Frustum& GetFrustum() const
        .addFunction("GetFrustum", &DebugRenderer::GetFrustum)
        // [Method] bool IsInside(const BoundingBox& box) const
        .addFunction("IsInside", &DebugRenderer::IsInside)

        // [Property(ReadOnly)] const Matrix3x4& view
        .addProperty("view", &DebugRenderer::GetView)
        // [Property(ReadOnly)] const Matrix4& projection
        .addProperty("projection", &DebugRenderer::GetProjection)
        // [Property(ReadOnly)] const Frustum& frustum
        .addProperty("frustum", &DebugRenderer::GetFrustum)
    );
}
}

