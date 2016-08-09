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

#include "../../Graphics/IndexBuffer.h"
#include "../../IO/VectorBuffer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static SharedPtr<IndexBuffer> CreateIndexBuffer(bool forceHeadless = false)
{
    return SharedPtr<IndexBuffer>(new IndexBuffer(globalContext, forceHeadless));
}

KAGUYA_FUNCTION_OVERLOADS(CreateIndexBufferOverloads, CreateIndexBuffer, 0, 1);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(IndexBufferSetSize, IndexBuffer, SetSize, 2, 3);

static bool IndexBufferSetData(IndexBuffer* self, VectorBuffer& src)
{
    // Make sure there is enough data
    if (self->GetIndexCount() && src.GetSize() >= self->GetIndexCount() * self->GetIndexSize())
        return self->SetData(&src.GetBuffer()[0]);
    else
        return false;
}

static VectorBuffer IndexBufferGetData(IndexBuffer* self)
{
    VectorBuffer ret;
    
    void* data = self->Lock(0, self->GetIndexCount(), false);
    if (data)
    {
        ret.Write(data, self->GetIndexCount() * self->GetIndexSize());
        ret.Seek(0);
        self->Unlock();
    }

    return ret;
}

void RegisterIndexBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] IndexBuffer : Object
    lua["IndexBuffer"].setClass(UserdataMetatable<IndexBuffer, Object>()
        .addStaticFunction("new", 
            CreateIndexBufferOverloads())
        
        // [Method] void SetShadowed(bool enable)
        .addFunction("SetShadowed", &IndexBuffer::SetShadowed)
        
        // [Method] bool SetSize(unsigned indexCount, bool largeIndices, bool dynamic = false)
        .addFunction("SetSize", IndexBufferSetSize())
        
        .addStaticFunction("SetData", &IndexBufferSetData)
        .addStaticFunction("GetData", &IndexBufferGetData)

        // [Method] bool IsShadowed() const
        .addFunction("IsShadowed", &IndexBuffer::IsShadowed)
        // [Method] bool IsDynamic() const
        .addFunction("IsDynamic", &IndexBuffer::IsDynamic)
        // [Method] unsigned GetIndexCount() const
        .addFunction("GetIndexCount", &IndexBuffer::GetIndexCount)
        // [Method] unsigned GetIndexSize() const
        .addFunction("GetIndexSize", &IndexBuffer::GetIndexSize)
                
        // [Property] bool shadowed
        .addProperty("shadowed", &IndexBuffer::IsShadowed, &IndexBuffer::SetShadowed)
        // [Property(ReadOnly)] bool dynamic
        .addProperty("dynamic", &IndexBuffer::IsDynamic)
        // [Property(ReadOnly)] unsigned indexCount
        .addProperty("indexCount", &IndexBuffer::GetIndexCount)
        // [Property(ReadOnly)] unsigned indexSize
        .addProperty("indexSize", &IndexBuffer::GetIndexSize)
    );
}
}

