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

    lua["DebugRenderer"].setClass(UserdataMetatable<DebugRenderer, Component>()
        .addStaticFunction("new", &CreateObject<DebugRenderer>)
        
        .addFunction("SetView", &DebugRenderer::SetView)

        .addFunction("AddLine", DebugRendererAddLine())
        .addFunction("AddTriangle", DebugRendererAddTriangle())
        .addFunction("AddNode", DebugRendererAddNode())
        
        .addOverloadedFunctions("AddBoundingBox", 
            DebugRendererAddBoundingBox0(),
            DebugRendererAddBoundingBox1())

        .addFunction("AddFrustum", DebugRendererAddFrustum())
        .addFunction("AddPolyhedron", DebugRendererAddPolyhedron())
        .addFunction("AddSphere", DebugRendererAddSphere())
        .addFunction("AddCylinder", DebugRendererAddCylinder())
        .addFunction("AddSkeleton", DebugRendererAddSkeleton())
        .addFunction("AddTriangleMesh", DebugRendererAddTriangleMesh())
        .addFunction("AddCircle", DebugRendererAddCircle())
        .addFunction("AddCross", DebugRendererAddCross())
        .addFunction("AddQuad", DebugRendererAddQuad())

        .addFunction("Render", &DebugRenderer::Render)
        .addFunction("GetView", &DebugRenderer::GetView)
        .addFunction("GetProjection", &DebugRenderer::GetProjection)
        .addFunction("GetFrustum", &DebugRenderer::GetFrustum)
        .addFunction("IsInside", &DebugRenderer::IsInside)

        .addProperty("view", &DebugRenderer::GetView)
        .addProperty("projection", &DebugRenderer::GetProjection)
        .addProperty("frustum", &DebugRenderer::GetFrustum)
    );
}
}

