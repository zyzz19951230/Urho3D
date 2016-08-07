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

#include "../../IO/Serializer.h"
#include "../../IO/VectorBuffer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static unsigned SerializerWrite(Serializer* self, const VectorBuffer& buffer)
{
    return self->Write(buffer.GetData(), buffer.GetSize());
}

static bool SerializerWriteBuffer(Serializer* self, const VectorBuffer& buffer)
{
    return self->WriteBuffer(buffer.GetBuffer());
}

void RegisterSerializer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Serializer"].setClass(UserdataMetatable<Serializer>()
        .addStaticFunction("Write", &SerializerWrite)

        .addFunction("WriteInt", &Serializer::WriteInt)
        .addFunction("WriteInt64", &Serializer::WriteInt64)
        .addFunction("WriteShort", &Serializer::WriteShort)
        .addFunction("WriteByte", &Serializer::WriteByte)
        .addFunction("WriteUInt", &Serializer::WriteUInt)
        .addFunction("WriteUInt64", &Serializer::WriteUInt64)
        .addFunction("WriteUShort", &Serializer::WriteUShort)
        .addFunction("WriteUByte", &Serializer::WriteUByte)
        .addFunction("WriteBool", &Serializer::WriteBool)
        .addFunction("WriteFloat", &Serializer::WriteFloat)
        .addFunction("WriteDouble", &Serializer::WriteDouble)
        .addFunction("WriteIntRect", &Serializer::WriteIntRect)
        .addFunction("WriteIntVector2", &Serializer::WriteIntVector2)
        .addFunction("WriteRect", &Serializer::WriteRect)
        .addFunction("WriteVector2", &Serializer::WriteVector2)
        .addFunction("WriteVector3", &Serializer::WriteVector3)
        .addFunction("WritePackedVector3", &Serializer::WritePackedVector3)
        .addFunction("WriteVector4", &Serializer::WriteVector4)
        .addFunction("WriteQuaternion", &Serializer::WriteQuaternion)
        .addFunction("WritePackedQuaternion", &Serializer::WritePackedQuaternion)
        .addFunction("WriteMatrix3", &Serializer::WriteMatrix3)
        .addFunction("WriteMatrix3x4", &Serializer::WriteMatrix3x4)
        .addFunction("WriteMatrix4", &Serializer::WriteMatrix4)
        .addFunction("WriteColor", &Serializer::WriteColor)
        .addFunction("WriteBoundingBox", &Serializer::WriteBoundingBox)
        .addFunction("WriteString", &Serializer::WriteString)
        .addFunction("WriteFileID", &Serializer::WriteFileID)
        .addFunction("WriteStringHash", &Serializer::WriteStringHash)
        
        .addStaticFunction("WriteBuffer", &SerializerWriteBuffer)

        .addFunction("WriteResourceRef", &Serializer::WriteResourceRef)
        .addFunction("WriteResourceRefList", &Serializer::WriteResourceRefList)
        .addFunction("WriteVariant", &Serializer::WriteVariant)
        .addFunction("WriteVariantData", &Serializer::WriteVariantData)
        .addFunction("WriteVariantVector", &Serializer::WriteVariantVector)
        .addFunction("WriteStringVector", &Serializer::WriteStringVector)
        .addFunction("WriteVariantMap", &Serializer::WriteVariantMap)
        .addFunction("WriteVLE", &Serializer::WriteVLE)
        .addFunction("WriteNetID", &Serializer::WriteNetID)
        .addFunction("WriteLine", &Serializer::WriteLine)
        );
}
}

