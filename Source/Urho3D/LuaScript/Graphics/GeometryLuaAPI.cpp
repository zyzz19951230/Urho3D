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

#include "../../Graphics/Geometry.h"
#include "../../Graphics/IndexBuffer.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(GeometrySetDrawRange0, Geometry, SetDrawRange, 3, 4, bool(Geometry::*)(PrimitiveType, unsigned, unsigned, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(GeometrySetDrawRange1, Geometry, SetDrawRange, 5, 6, bool(Geometry::*)(PrimitiveType, unsigned, unsigned, unsigned, unsigned, bool));

void RegisterGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Geometry"].setClass(UserdataMetatable<Geometry, Object>()
        .addStaticFunction("new", &CreateObject<Geometry>)
        
        .addFunction("SetNumVertexBuffers", &Geometry::SetNumVertexBuffers)
        .addFunction("SetVertexBuffer", &Geometry::SetVertexBuffer)
        .addFunction("SetIndexBuffer", &Geometry::SetIndexBuffer)

        .addOverloadedFunctions("SetDrawRange", 
            GeometrySetDrawRange0(),
            GeometrySetDrawRange1())

        .addFunction("SetLodDistance", &Geometry::SetLodDistance)

        .addFunction("GetNumVertexBuffers", &Geometry::GetNumVertexBuffers)
        .addFunction("GetVertexBuffer", &Geometry::GetVertexBuffer)
        .addFunction("GetIndexBuffer", &Geometry::GetIndexBuffer)        
        .addFunction("GetPrimitiveType", &Geometry::GetPrimitiveType)

        .addFunction("GetIndexStart", &Geometry::GetIndexStart)
        .addFunction("GetIndexCount", &Geometry::GetIndexCount)
        .addFunction("GetVertexStart", &Geometry::GetVertexStart)
        .addFunction("GetVertexCount", &Geometry::GetVertexCount)
        .addFunction("GetLodDistance", &Geometry::GetLodDistance)
        .addFunction("IsEmpty", &Geometry::IsEmpty)

        .addProperty("numVertexBuffers", &Geometry::GetNumVertexBuffers)

        .addProperty("indexBuffer", &Geometry::GetIndexBuffer, &Geometry::SetIndexBuffer)
        .addProperty("primitiveType", &Geometry::GetPrimitiveType)
        .addProperty("indexStart", &Geometry::GetIndexStart)
        .addProperty("indexCount", &Geometry::GetIndexCount)
        .addProperty("vertexStart", &Geometry::GetVertexStart)
        .addProperty("vertexCount", &Geometry::GetVertexCount)
        .addProperty("lodDistance", &Geometry::GetLodDistance, &Geometry::SetLodDistance)
        .addProperty("empty", &Geometry::IsEmpty)
    );
}
}

