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

#include "../../IO/VectorBuffer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterVectorBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] VectorBuffer : MultipleBase<Deserializer, Serializer> 
    lua["VectorBuffer"].setClass(UserdataMetatable<VectorBuffer, MultipleBase<Deserializer, Serializer> >()
        .setConstructors<VectorBuffer()>()

        // [Method] void SetData(const PODVector<unsigned char>& data)
        .addFunction("SetData", static_cast<void(VectorBuffer::*)(Deserializer&, unsigned)>(&VectorBuffer::SetData))
        // [Method] void Clear()
        .addFunction("Clear", &VectorBuffer::Clear)
        // [Method] void Resize(unsigned size)
        .addFunction("Resize", &VectorBuffer::Resize)
        
        // [Method] const unsigned char* GetData() const
        .addFunction("GetData", &VectorBuffer::GetData)
        // [Method] unsigned char* GetModifiableData()
        .addFunction("GetModifiableData", &VectorBuffer::GetModifiableData)
        );
}
}

