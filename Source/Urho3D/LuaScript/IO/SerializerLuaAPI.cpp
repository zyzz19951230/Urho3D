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

    // [Class] Serializer
    lua["Serializer"].setClass(UserdataMetatable<Serializer>()
        .addStaticFunction("Write", &SerializerWrite)

        // [Method] bool WriteInt(int value)
        .addFunction("WriteInt", &Serializer::WriteInt)
        // [Method] bool WriteInt64(long long value)
        .addFunction("WriteInt64", &Serializer::WriteInt64)
        // [Method] bool WriteShort(short value)
        .addFunction("WriteShort", &Serializer::WriteShort)
        // [Method] bool WriteByte(signed char value)
        .addFunction("WriteByte", &Serializer::WriteByte)
        // [Method] bool WriteUInt(unsigned value)
        .addFunction("WriteUInt", &Serializer::WriteUInt)
        // [Method] bool WriteUInt64(unsigned long long value)
        .addFunction("WriteUInt64", &Serializer::WriteUInt64)
        // [Method] bool WriteUShort(unsigned short value)
        .addFunction("WriteUShort", &Serializer::WriteUShort)
        // [Method] bool WriteUByte(unsigned char value)
        .addFunction("WriteUByte", &Serializer::WriteUByte)
        // [Method] bool WriteBool(bool value)
        .addFunction("WriteBool", &Serializer::WriteBool)
        // [Method] bool WriteFloat(float value)
        .addFunction("WriteFloat", &Serializer::WriteFloat)
        // [Method] bool WriteDouble(double value)
        .addFunction("WriteDouble", &Serializer::WriteDouble)
        // [Method] bool WriteIntRect(const IntRect& value)
        .addFunction("WriteIntRect", &Serializer::WriteIntRect)
        // [Method] bool WriteIntVector2(const IntVector2& value)
        .addFunction("WriteIntVector2", &Serializer::WriteIntVector2)
        // [Method] bool WriteRect(const Rect& value)
        .addFunction("WriteRect", &Serializer::WriteRect)
        // [Method] bool WriteVector2(const Vector2& value)
        .addFunction("WriteVector2", &Serializer::WriteVector2)
        // [Method] bool WriteVector3(const Vector3& value)
        .addFunction("WriteVector3", &Serializer::WriteVector3)
        // [Method] bool WritePackedVector3(const Vector3& value, float maxAbsCoord)
        .addFunction("WritePackedVector3", &Serializer::WritePackedVector3)
        // [Method] bool WriteVector4(const Vector4& value)
        .addFunction("WriteVector4", &Serializer::WriteVector4)
        // [Method] bool WriteQuaternion(const Quaternion& value)
        .addFunction("WriteQuaternion", &Serializer::WriteQuaternion)
        // [Method] bool WritePackedQuaternion(const Quaternion& value)
        .addFunction("WritePackedQuaternion", &Serializer::WritePackedQuaternion)
        // [Method] bool WriteMatrix3(const Matrix3& value)
        .addFunction("WriteMatrix3", &Serializer::WriteMatrix3)
        // [Method] bool WriteMatrix3x4(const Matrix3x4& value)
        .addFunction("WriteMatrix3x4", &Serializer::WriteMatrix3x4)
        // [Method] bool WriteMatrix4(const Matrix4& value)
        .addFunction("WriteMatrix4", &Serializer::WriteMatrix4)
        // [Method] bool WriteColor(const Color& value)
        .addFunction("WriteColor", &Serializer::WriteColor)
        // [Method] bool WriteBoundingBox(const BoundingBox& value)
        .addFunction("WriteBoundingBox", &Serializer::WriteBoundingBox)
        // [Method] bool WriteString(const String& value)
        .addFunction("WriteString", &Serializer::WriteString)
        // [Method] bool WriteFileID(const String& value)
        .addFunction("WriteFileID", &Serializer::WriteFileID)
        // [Method] bool WriteStringHash(const StringHash& value)
        .addFunction("WriteStringHash", &Serializer::WriteStringHash)
        
        .addStaticFunction("WriteBuffer", &SerializerWriteBuffer)

        // [Method] bool WriteResourceRef(const ResourceRef& value)
        .addFunction("WriteResourceRef", &Serializer::WriteResourceRef)
        // [Method] bool WriteResourceRefList(const ResourceRefList& value)
        .addFunction("WriteResourceRefList", &Serializer::WriteResourceRefList)
        // [Method] bool WriteVariant(const Variant& value)
        .addFunction("WriteVariant", &Serializer::WriteVariant)
        // [Method] bool WriteVariantData(const Variant& value)
        .addFunction("WriteVariantData", &Serializer::WriteVariantData)
        // [Method] bool WriteVariantVector(const VariantVector& value)
        .addFunction("WriteVariantVector", &Serializer::WriteVariantVector)
        // [Method] bool WriteStringVector(const StringVector& value)
        .addFunction("WriteStringVector", &Serializer::WriteStringVector)
        // [Method] bool WriteVariantMap(const VariantMap& value)
        .addFunction("WriteVariantMap", &Serializer::WriteVariantMap)
        // [Method] bool WriteVLE(unsigned value)
        .addFunction("WriteVLE", &Serializer::WriteVLE)
        // [Method] bool WriteNetID(unsigned value)
        .addFunction("WriteNetID", &Serializer::WriteNetID)
        // [Method] bool WriteLine(const String& value)
        .addFunction("WriteLine", &Serializer::WriteLine)
        );
}
}

