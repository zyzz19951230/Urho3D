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

#include "../../Core/Object.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../IO/VectorBuffer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferSetSize0, VertexBuffer, SetSize, 2, 3, bool(VertexBuffer::*)(unsigned, const PODVector<VertexElement>&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferSetSize1, VertexBuffer, SetSize, 2, 3, bool(VertexBuffer::*)(unsigned, unsigned, bool));

static bool VertexBufferSetData(VertexBuffer* self, VectorBuffer& src)
{
    // Make sure there is enough data
    if (self->GetVertexCount() && src.GetSize() >= self->GetVertexCount() * self->GetVertexSize())
        return self->SetData(&src.GetBuffer()[0]);
    else
        return false;
}

static VectorBuffer VertexBufferGetData(VertexBuffer* self)
{
    VectorBuffer ret;

    void* data = self->Lock(0, self->GetVertexCount(), false);
    if (data)
    {
        ret.Write(data, self->GetVertexCount() * self->GetVertexSize());
        ret.Seek(0);
        self->Unlock();
    }

    return ret;
}

static SharedPtr<VertexBuffer> CreateVertexBuffer(bool forceHeadless = false)
{
    return SharedPtr<VertexBuffer>(new VertexBuffer(globalContext, forceHeadless));
}

KAGUYA_FUNCTION_OVERLOADS(CreateVertexBufferOverloads, CreateVertexBuffer, 0, 1);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(VertexBufferSetDataRange, VertexBuffer, SetDataRange, 3, 4);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferGetElement0, VertexBuffer, GetElement, 1, 2, const VertexElement*(VertexBuffer::*)(VertexElementSemantic, unsigned char)const);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferGetElement1, VertexBuffer, GetElement, 2, 3, const VertexElement*(VertexBuffer::*)(VertexElementType, VertexElementSemantic, unsigned char)const);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferHasElement0, VertexBuffer, HasElement, 1, 2, bool(VertexBuffer::*)(VertexElementSemantic, unsigned char)const);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(VertexBufferHasElement1, VertexBuffer, HasElement, 2, 3, bool(VertexBuffer::*)(VertexElementType, VertexElementSemantic, unsigned char)const);

void RegisterVertexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] VertexBuffer : GPUObject
    lua["VertexBuffer"].setClass(UserdataMetatable<VertexBuffer, GPUObject>()
        .addStaticFunction("new", 
            CreateVertexBufferOverloads())

        // [Method] void SetShadowed(bool enable)
        .addFunction("SetShadowed", &VertexBuffer::SetShadowed)

        .addOverloadedFunctions("SetSize", 
            VertexBufferSetSize0(), 
            VertexBufferSetSize1())

        .addStaticFunction("SetData", &VertexBufferSetData)
        .addStaticFunction("GetData", &VertexBufferGetData)

        // [Method] bool SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false)
        .addFunction("SetDataRange", VertexBufferSetDataRange())

        // [Method] bool IsShadowed() const
        .addFunction("IsShadowed", &VertexBuffer::IsShadowed)
        // [Method] bool IsDynamic() const
        .addFunction("IsDynamic", &VertexBuffer::IsDynamic)
        // [Method] unsigned GetVertexCount() const
        .addFunction("GetVertexCount", &VertexBuffer::GetVertexCount)
        // [Method] unsigned GetVertexSize() const
        .addFunction("GetVertexSize", static_cast<unsigned(VertexBuffer::*)()const>(&VertexBuffer::GetVertexSize))

        .addOverloadedFunctions("GetElement",
            VertexBufferGetElement0(),
            VertexBufferGetElement1())

        .addOverloadedFunctions("HasElement",
            VertexBufferHasElement0(),
            VertexBufferHasElement1())

        // [Method] unsigned GetElementMask() const
        .addFunction("GetElementMask", &VertexBuffer::GetElementMask)

        // [Property] bool shadowed
        .addProperty("shadowed", &VertexBuffer::IsShadowed, &VertexBuffer::SetShadowed)
        // [Property(ReadOnly)] bool dynamic
        .addProperty("dynamic", &VertexBuffer::IsDynamic)
        // [Property(ReadOnly)] unsigned vertexCount
        .addProperty("vertexCount", &VertexBuffer::GetVertexCount)
        .addProperty("vertexSize", static_cast<unsigned(VertexBuffer::*)()const>(&VertexBuffer::GetVertexSize))
        // [Property(ReadOnly)] unsigned elementMask
        .addProperty("elementMask", &VertexBuffer::GetElementMask)
    );
}
}

