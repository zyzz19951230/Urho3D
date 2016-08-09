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

    // [Class] Geometry : Object
    lua["Geometry"].setClass(UserdataMetatable<Geometry, Object>()
        .addStaticFunction("new", &CreateObject<Geometry>)
        
        // [Method] bool SetNumVertexBuffers(unsigned num)
        .addFunction("SetNumVertexBuffers", &Geometry::SetNumVertexBuffers)
        // [Method] bool SetVertexBuffer(unsigned index, VertexBuffer* buffer)
        .addFunction("SetVertexBuffer", &Geometry::SetVertexBuffer)
        // [Method] void SetIndexBuffer(IndexBuffer* buffer)
        .addFunction("SetIndexBuffer", &Geometry::SetIndexBuffer)

        .addOverloadedFunctions("SetDrawRange", 
            GeometrySetDrawRange0(),
            GeometrySetDrawRange1())

        // [Method] void SetLodDistance(float distance)
        .addFunction("SetLodDistance", &Geometry::SetLodDistance)

        // [Method] unsigned GetNumVertexBuffers() const
        .addFunction("GetNumVertexBuffers", &Geometry::GetNumVertexBuffers)
        // [Method] VertexBuffer* GetVertexBuffer(unsigned index) const
        .addFunction("GetVertexBuffer", &Geometry::GetVertexBuffer)
        // [Method] IndexBuffer* GetIndexBuffer() const
        .addFunction("GetIndexBuffer", &Geometry::GetIndexBuffer)        
        // [Method] PrimitiveType GetPrimitiveType() const
        .addFunction("GetPrimitiveType", &Geometry::GetPrimitiveType)

        // [Method] unsigned GetIndexStart() const
        .addFunction("GetIndexStart", &Geometry::GetIndexStart)
        // [Method] unsigned GetIndexCount() const
        .addFunction("GetIndexCount", &Geometry::GetIndexCount)
        // [Method] unsigned GetVertexStart() const
        .addFunction("GetVertexStart", &Geometry::GetVertexStart)
        // [Method] unsigned GetVertexCount() const
        .addFunction("GetVertexCount", &Geometry::GetVertexCount)
        // [Method] float GetLodDistance() const
        .addFunction("GetLodDistance", &Geometry::GetLodDistance)
        // [Method] bool IsEmpty() const
        .addFunction("IsEmpty", &Geometry::IsEmpty)

        // [Property(ReadOnly)] unsigned numVertexBuffers
        .addProperty("numVertexBuffers", &Geometry::GetNumVertexBuffers)

        // [Property] IndexBuffer* indexBuffer
        .addProperty("indexBuffer", &Geometry::GetIndexBuffer, &Geometry::SetIndexBuffer)
        // [Property(ReadOnly)] PrimitiveType primitiveType
        .addProperty("primitiveType", &Geometry::GetPrimitiveType)
        // [Property(ReadOnly)] unsigned indexStart
        .addProperty("indexStart", &Geometry::GetIndexStart)
        // [Property(ReadOnly)] unsigned indexCount
        .addProperty("indexCount", &Geometry::GetIndexCount)
        // [Property(ReadOnly)] unsigned vertexStart
        .addProperty("vertexStart", &Geometry::GetVertexStart)
        // [Property(ReadOnly)] unsigned vertexCount
        .addProperty("vertexCount", &Geometry::GetVertexCount)
        // [Property] float lodDistance
        .addProperty("lodDistance", &Geometry::GetLodDistance, &Geometry::SetLodDistance)
        // [Property(ReadOnly)] bool empty
        .addProperty("empty", &Geometry::IsEmpty)
    );
}
}

