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

    // [Class] Deserializer
    lua["Deserializer"].setClass(UserdataMetatable<Deserializer>()
        // [Method] VectorBuffer Read(unsigned size)
        .addStaticFunction("Read", &DeserializerRead)

        // [Method] unsigned Seek(unsigned position)
        .addFunction("Seek", &Deserializer::Seek)
        // [Method] const String& GetName() const
        .addFunction("GetName", &Deserializer::GetName)
        // [Method] unsigned GetChecksum()
        .addFunction("GetChecksum", &Deserializer::GetChecksum)
        // [Method] bool IsEof() const
        .addFunction("IsEof", &Deserializer::IsEof)
        // [Method] unsigned GetPosition() const
        .addFunction("GetPosition", &Deserializer::GetPosition)
        // [Method] unsigned GetSize() const
        .addFunction("GetSize", &Deserializer::GetSize)

        // [Method] int ReadInt()
        .addFunction("ReadInt", &Deserializer::ReadInt)
        // [Method] long long ReadInt64()
        .addFunction("ReadInt64", &Deserializer::ReadInt64)
        // [Method] short ReadShort()
        .addFunction("ReadShort", &Deserializer::ReadShort)
        // [Method] signed char ReadByte()
        .addFunction("ReadByte", &Deserializer::ReadByte)
        // [Method] unsigned ReadUInt()
        .addFunction("ReadUInt", &Deserializer::ReadUInt)
        // [Method] unsigned long long ReadUInt64()
        .addFunction("ReadUInt64", &Deserializer::ReadUInt64)
        // [Method] unsigned short ReadUShort()
        .addFunction("ReadUShort", &Deserializer::ReadUShort)
        // [Method] unsigned char ReadUByte()
        .addFunction("ReadUByte", &Deserializer::ReadUByte)
        // [Method] bool ReadBool()
        .addFunction("ReadBool", &Deserializer::ReadBool)
        // [Method] float ReadFloat()
        .addFunction("ReadFloat", &Deserializer::ReadFloat)
        // [Method] double ReadDouble()
        .addFunction("ReadDouble", &Deserializer::ReadDouble)
        // [Method] IntRect ReadIntRect()
        .addFunction("ReadIntRect", &Deserializer::ReadIntRect)
        // [Method] IntVector2 ReadIntVector2()
        .addFunction("ReadIntVector2", &Deserializer::ReadIntVector2)
        // [Method] Rect ReadRect()
        .addFunction("ReadRect", &Deserializer::ReadRect)
        // [Method] Vector2 ReadVector2()
        .addFunction("ReadVector2", &Deserializer::ReadVector2)
        // [Method] Vector3 ReadVector3()
        .addFunction("ReadVector3", &Deserializer::ReadVector3)
        // [Method] Vector3 ReadPackedVector3(float maxAbsCoord)
        .addFunction("ReadPackedVector3", &Deserializer::ReadPackedVector3)
        // [Method] Vector4 ReadVector4()
        .addFunction("ReadVector4", &Deserializer::ReadVector4)
        // [Method] Quaternion ReadQuaternion()
        .addFunction("ReadQuaternion", &Deserializer::ReadQuaternion)
        // [Method] Quaternion ReadPackedQuaternion()
        .addFunction("ReadPackedQuaternion", &Deserializer::ReadPackedQuaternion)
        // [Method] Matrix3 ReadMatrix3()
        .addFunction("ReadMatrix3", &Deserializer::ReadMatrix3)
        // [Method] Matrix3x4 ReadMatrix3x4()
        .addFunction("ReadMatrix3x4", &Deserializer::ReadMatrix3x4)
        // [Method] Matrix4 ReadMatrix4()
        .addFunction("ReadMatrix4", &Deserializer::ReadMatrix4)
        // [Method] Color ReadColor()
        .addFunction("ReadColor", &Deserializer::ReadColor)
        // [Method] BoundingBox ReadBoundingBox()
        .addFunction("ReadBoundingBox", &Deserializer::ReadBoundingBox)
        // [Method] String ReadString()
        .addFunction("ReadString", &Deserializer::ReadString)
        // [Method] String ReadFileID()
        .addFunction("ReadFileID", &Deserializer::ReadFileID)
        // [Method] StringHash ReadStringHash()
        .addFunction("ReadStringHash", &Deserializer::ReadStringHash)
        
        .addStaticFunction("ReadBuffer", &DeserializerReadBuffer)

        // [Method] ResourceRef ReadResourceRef()
        .addFunction("ReadResourceRef", &Deserializer::ReadResourceRef)
        // [Method] ResourceRefList ReadResourceRefList()
        .addFunction("ReadResourceRefList", &Deserializer::ReadResourceRefList)

        .addOverloadedFunctions("ReadVariant",
            // [Method] Variant ReadVariant()
            static_cast<Variant(Deserializer::*)()>(&Deserializer::ReadVariant),
            // [Method] Variant ReadVariant(VariantType variantType)
            static_cast<Variant(Deserializer::*)(VariantType)>(&Deserializer::ReadVariant))

        // [Method] VariantVector ReadVariantVector()
        .addFunction("ReadVariantVector", &Deserializer::ReadVariantVector)
        // [Method] StringVector ReadStringVector()
        .addFunction("ReadStringVector", &Deserializer::ReadStringVector)
        // [Method] VariantMap ReadVariantMap()
        .addFunction("ReadVariantMap", &Deserializer::ReadVariantMap)
        // [Method] unsigned ReadVLE()
        .addFunction("ReadVLE", &Deserializer::ReadVLE)
        // [Method] unsigned ReadNetID()
        .addFunction("ReadNetID", &Deserializer::ReadNetID)
        // [Method] String ReadLine()
        .addFunction("ReadLine", &Deserializer::ReadLine)

        // [Property(ReadOnly)] const String& name
        .addProperty("name", &Deserializer::GetName)
        // [Property(ReadOnly)] unsigned checksum
        .addProperty("checksum", &Deserializer::GetChecksum)
        // [Property(ReadOnly)] bool eof
        .addProperty("eof", &Deserializer::IsEof)
        // [Property(ReadOnly)] unsigned position
        .addProperty("position", &Deserializer::GetPosition)
        // [Property(ReadOnly)] unsigned size
        .addProperty("size", &Deserializer::GetSize)
        );
}
}

