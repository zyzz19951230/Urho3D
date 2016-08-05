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

#include "../../IO/Deserializer.h"
#include "../../IO/VectorBuffer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static VectorBuffer DeserializerRead(Deserializer* self, unsigned size)
{
    unsigned char* data = new unsigned char[size];
    self->Read(data, size);
    VectorBuffer buffer(data, size);
    delete[] data;
    return buffer;
}

static VectorBuffer DeserializerReadBuffer(Deserializer* self)
{
    return VectorBuffer(self->ReadBuffer());
}

void RegisterDeserializer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Deserializer"].setClass(UserdataMetatable<Deserializer>()
        .addStaticFunction("Read", &DeserializerRead)

        .addFunction("Seek", &Deserializer::Seek)
        .addFunction("GetName", &Deserializer::GetName)
        .addFunction("GetChecksum", &Deserializer::GetChecksum)
        .addFunction("IsEof", &Deserializer::IsEof)
        .addFunction("GetPosition", &Deserializer::GetPosition)
        .addFunction("GetSize", &Deserializer::GetSize)

        .addFunction("ReadInt", &Deserializer::ReadInt)
        .addFunction("ReadShort", &Deserializer::ReadShort)
        .addFunction("ReadByte", &Deserializer::ReadByte)
        .addFunction("ReadUInt", &Deserializer::ReadUInt)
        .addFunction("ReadUShort", &Deserializer::ReadUShort)
        .addFunction("ReadUByte", &Deserializer::ReadUByte)
        .addFunction("ReadBool", &Deserializer::ReadBool)
        .addFunction("ReadFloat", &Deserializer::ReadFloat)
        .addFunction("ReadDouble", &Deserializer::ReadDouble)
        .addFunction("ReadIntRect", &Deserializer::ReadIntRect)
        .addFunction("ReadIntVector2", &Deserializer::ReadIntVector2)
        .addFunction("ReadRect", &Deserializer::ReadRect)
        .addFunction("ReadVector2", &Deserializer::ReadVector2)
        .addFunction("ReadVector3", &Deserializer::ReadVector3)
        .addFunction("ReadPackedVector3", &Deserializer::ReadPackedVector3)
        .addFunction("ReadVector4", &Deserializer::ReadVector4)
        .addFunction("ReadQuaternion", &Deserializer::ReadQuaternion)
        .addFunction("ReadPackedQuaternion", &Deserializer::ReadPackedQuaternion)
        .addFunction("ReadMatrix3", &Deserializer::ReadMatrix3)
        .addFunction("ReadMatrix3x4", &Deserializer::ReadMatrix3x4)
        .addFunction("ReadMatrix4", &Deserializer::ReadMatrix4)
        .addFunction("ReadColor", &Deserializer::ReadColor)
        .addFunction("ReadBoundingBox", &Deserializer::ReadBoundingBox)
        .addFunction("ReadString", &Deserializer::ReadString)
        .addFunction("ReadFileID", &Deserializer::ReadFileID)
        .addFunction("ReadStringHash", &Deserializer::ReadStringHash)
        
        .addStaticFunction("ReadBuffer", &DeserializerReadBuffer)

        .addFunction("ReadResourceRef", &Deserializer::ReadResourceRef)
        .addFunction("ReadResourceRefList", &Deserializer::ReadResourceRefList)

        .addOverloadedFunctions("ReadVariant",
            static_cast<Variant(Deserializer::*)()>(&Deserializer::ReadVariant),
            static_cast<Variant(Deserializer::*)(VariantType)>(&Deserializer::ReadVariant))

        .addFunction("ReadVariantVector", &Deserializer::ReadVariantVector)
        .addFunction("ReadStringVector", &Deserializer::ReadStringVector)
        .addFunction("ReadVariantMap", &Deserializer::ReadVariantMap)
        .addFunction("ReadVLE", &Deserializer::ReadVLE)
        .addFunction("ReadNetID", &Deserializer::ReadNetID)
        .addFunction("ReadLine", &Deserializer::ReadLine)

        .addProperty("name", &Deserializer::GetName)
        .addProperty("checksum", &Deserializer::GetChecksum)
        .addProperty("eof", &Deserializer::IsEof)
        .addProperty("position", &Deserializer::GetPosition)
        .addProperty("size", &Deserializer::GetSize)
        );
}
}

