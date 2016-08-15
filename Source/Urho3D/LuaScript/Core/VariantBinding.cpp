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

#include "../../Core/Variant.h"
#include "../../IO/VectorBuffer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static Variant IntToVariant(int value)
{
    return Variant(value);
}

static Variant UIntToVariant(unsigned value)
{
    return Variant(value);
}

static Variant StringHashToVariant(const StringHash& value)
{
    return Variant(value);
}

static Variant BoolToVariant(bool value)
{
    return Variant(value);
}

static Variant FloatToVariant(float value)
{
    return Variant(value);
}

static Variant DoubleToVariant(double value)
{
    return Variant(value);
}

static Variant Vector2ToVariant0(float x, float y)
{
    return Variant(Vector2(x, y));
}

static Variant Vector2ToVariant1(const Vector2& value)
{
    return Variant(value);
}

static Variant Vector3ToVariant0(float x, float y, float z)
{
    return Variant(Vector3(x, y, z));
}

static Variant Vector3ToVariant1(const Vector3& value)
{
    return Variant(value);
}

static Variant Vector4ToVariant0(float x, float y, float z, float w)
{
    return Variant(Vector4(x, y, z, w));
}

static Variant Vector4ToVariant1(const Vector4& value)
{
    return Variant(value);
}

static Variant QuaternionToVariant0(float w, float x, float y, float z)
{
    return Variant(Quaternion(w, x, y, z));
}

static Variant QuaternionToVariant1(const Quaternion& value)
{
    return Variant(value);
}

static Variant ColorToVariant0(float r, float g, float b)
{
    return Variant(Color(r, g, b));
}

static Variant ColorToVariant1(float r, float g, float b, float a)
{
    return Variant(Color(r, g, b, a));
}

static Variant ColorToVariant2(const Color& value)
{
    return Variant(value);
}

static Variant StringToVariant(const String& value)
{
    return Variant(value);
}

static Variant VectorBufferToVariant(const VectorBuffer& value)
{
    return Variant(value);
}

static Variant ResourceRefToVariant(const ResourceRef& value)
{
    return Variant(value);
}

static Variant ResourceRefListToVariant(const ResourceRefList& value)
{
    return Variant(value);
}

static Variant VariantVectorToVariant(const VariantVector& value)
{
    return Variant(value);
}

static Variant VariantMapToVariant(const VariantMap& value)
{
    return Variant(value);
}

static Variant StringVectorToVariant(const StringVector& value)
{
    return Variant(value);
}

static Variant IntRectToVariant0(int left, int top, int right, int bottom)
{
    return Variant(IntRect(left, top, right, bottom));
}

static Variant IntRectToVariant1(const IntRect& value)
{
    return Variant(value);
}

static Variant IntVector2ToVariant0(int x, int y)
{
    return Variant(IntVector2(x, y));
}

static Variant IntVector2ToVariant1(const IntVector2& value)
{
    return Variant(value);
}

static Variant PtrToVariant(RefCounted* value)
{
    return Variant(value);
}

static Variant Matrix3ToVariant0(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
    return Variant(Matrix3(v00, v01, v02, v10, v11, v12, v20, v21, v22));
}

static Variant Matrix3ToVariant1(const Matrix3& value)
{
    return Variant(value);
}

static Variant Matrix3x4ToVariant(const Matrix3x4& value)
{
    return Variant(value);
}

static Variant Matrix4ToVariant(const Matrix4& value)
{
    return Variant(value);
}

static SharedPtr<RefCounted> VariantGetPtr(const Variant* self)
{
    return SharedPtr<RefCounted>(self->GetPtr());
}

void RegisterVariant(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] VariantType
    lua["VAR_NONE"] = VAR_NONE;
    lua["VAR_INT"] = VAR_INT;
    lua["VAR_BOOL"] = VAR_BOOL;
    lua["VAR_FLOAT"] = VAR_FLOAT;
    lua["VAR_VECTOR2"] = VAR_VECTOR2;
    lua["VAR_VECTOR3"] = VAR_VECTOR3;
    lua["VAR_VECTOR4"] = VAR_VECTOR4;
    lua["VAR_QUATERNION"] = VAR_QUATERNION;
    lua["VAR_COLOR"] = VAR_COLOR;
    lua["VAR_STRING"] = VAR_STRING;
    lua["VAR_BUFFER"] = VAR_BUFFER;
    lua["VAR_VOIDPTR"] = VAR_VOIDPTR;
    lua["VAR_RESOURCEREF"] = VAR_RESOURCEREF;
    lua["VAR_RESOURCEREFLIST"] = VAR_RESOURCEREFLIST;
    lua["VAR_VARIANTVECTOR"] = VAR_VARIANTVECTOR;
    lua["VAR_VARIANTMAP"] = VAR_VARIANTMAP;
    lua["VAR_INTRECT"] = VAR_INTRECT;
    lua["VAR_INTVECTOR2"] = VAR_INTVECTOR2;
    lua["VAR_PTR"] = VAR_PTR;
    lua["VAR_MATRIX3"] = VAR_MATRIX3;
    lua["VAR_MATRIX3X4"] = VAR_MATRIX3X4;
    lua["VAR_MATRIX4"] = VAR_MATRIX4;
    lua["VAR_DOUBLE"] = VAR_DOUBLE;
    lua["VAR_STRINGVECTOR"] = VAR_STRINGVECTOR;
    lua["MAX_VAR_TYPES"] = MAX_VAR_TYPES;

    // [Class] ResourceRef
    lua["ResourceRef"].setClass(UserdataMetatable<ResourceRef>()
        // [Constructor] ResourceRef()
        .setConstructors<ResourceRef(),
        // [Constructor] ResourceRef(StringHash type)
        ResourceRef(StringHash),
        // [Constructor] ResourceRef(StringHash type, const String& name)
        ResourceRef(StringHash, const String&),
        // [Constructor] ResourceRef(const char* type, const char* name)
        ResourceRef(const char*, const char*)>()

        // [Method] bool operator==(const ResourceRef& rhs) const
        .addFunction("__eq", &ResourceRef::operator==)

        // [Field] StringHash type
        .addProperty("type", &ResourceRef::type_)
        // [Field] String name
        .addProperty("name", &ResourceRef::name_)
        );

    // [Class] ResourceRefList
    lua["ResourceRefList"].setClass(UserdataMetatable<ResourceRefList>()
        // [Constructor] ResourceRefList()
        .setConstructors<ResourceRefList(),
        // [Constructor] ResourceRefList(StringHash type)
        ResourceRefList(StringHash)>()

        // [Method] bool operator==(const ResourceRefList& rhs) const
        .addFunction("__eq", &ResourceRefList::operator==)

        // [Field] StringHash type
        .addProperty("type", &ResourceRefList::type_)
        );

    // [Class] Variant
    lua["Variant"].setClass(UserdataMetatable<Variant>()
        // [Constructor] Variant()
        .setConstructors<Variant(),
        // [Constructor] Variant(const Variant& rhs)
        Variant(const Variant&)>()

        // [Method] void Clear()
        .addFunction("Clear", &Variant::Clear)

        // [Method] bool operator==(const Variant& rhs) const
        .addFunction("__eq", static_cast<bool(Variant::*)(const Variant&) const>(&Variant::operator==))

        // [Method] int GetInt() const
        .addFunction("GetInt", &Variant::GetInt)
        // [Method] unsigned GetUInt() const
        .addFunction("GetUInt", &Variant::GetUInt)
        // [Method] StringHash GetStringHash() const
        .addFunction("GetStringHash", &Variant::GetStringHash)
        // [Method] bool GetBool() const
        .addFunction("GetBool", &Variant::GetBool)
        // [Method] float GetFloat() const
        .addFunction("GetFloat", &Variant::GetFloat)
        // [Method] double GetDouble() const
        .addFunction("GetDouble", &Variant::GetDouble)

        // [Method] const Vector2& GetVector2() const
        .addFunction("GetVector2", &Variant::GetVector2)
        // [Method] const Vector3& GetVector3() const
        .addFunction("GetVector3", &Variant::GetVector3)
        // [Method] const Vector4& GetVector4() const
        .addFunction("GetVector4", &Variant::GetVector4)
        // [Method] const Quaternion& GetQuaternion() const
        .addFunction("GetQuaternion", &Variant::GetQuaternion)
        // [Method] const Color& GetColor() const
        .addFunction("GetColor", &Variant::GetColor)
        // [Method] const String& GetString() const
        .addFunction("GetString", &Variant::GetString)

        // [Method] const PODVector<unsigned char>& GetRawBuffer() const
        .addFunction("GetRawBuffer", &Variant::GetBuffer)
        // [Method] VectorBuffer GetBuffer() const
        .addFunction("GetBuffer", &Variant::GetVectorBuffer)
        // [Method] void* GetVoidPtr() const
        .addFunction("GetVoidPtr", &Variant::GetVoidPtr)

        // [Method] const ResourceRef& GetResourceRef() const
        .addFunction("GetResourceRef", &Variant::GetResourceRef)
        // [Method] const ResourceRefList& GetResourceRefList() const
        .addFunction("GetResourceRefList", &Variant::GetResourceRefList)
        // [Method] const VariantVector& GetVariantVector() const
        .addFunction("GetVariantVector", &Variant::GetVariantVector)
        // [Method] const StringVector& GetStringVector() const
        .addFunction("GetStringVector", &Variant::GetStringVector)
        // [Method] const VariantMap& GetVariantMap() const
        .addFunction("GetVariantMap", &Variant::GetVariantMap)
        // [Method] const IntRect& GetIntRect() const
        .addFunction("GetIntRect", &Variant::GetIntRect)
        // [Method] const IntVector2& GetIntVector2() const
        .addFunction("GetIntVector2", &Variant::GetIntVector2)

        // [Method] SharedPtr<RefCounted> GetPtr() const
        .addStaticFunction("GetPtr", &VariantGetPtr)

        // [Method] const Matrix3& GetMatrix3() const
        .addFunction("GetMatrix3", &Variant::GetMatrix3)
        // [Method] const Matrix3x4& GetMatrix3x4() const
        .addFunction("GetMatrix3x4", &Variant::GetMatrix3x4)
        // [Method] const Matrix4& GetMatrix4() const
        .addFunction("GetMatrix4", &Variant::GetMatrix4)

        // [Method] VariantType GetType() const
        .addFunction("GetType", &Variant::GetType)
        // [Method] String GetTypeName() const
        .addFunction("GetTypeName", static_cast<String(Variant::*)() const>(&Variant::GetTypeName))
        // [Method] String ToString() const
        .addFunction("ToString", &Variant::ToString)
        // [Method] bool IsZero() const
        .addFunction("IsZero", &Variant::IsZero)
        // [Method] bool IsEmpty() const
        .addFunction("IsEmpty", &Variant::IsEmpty)

        // [Property(Readonly)] VariantType type
        .addProperty("type", &Variant::GetType)
        // [Property(Readonly)] String typeName
        .addProperty("typeName", static_cast<String(Variant::*)() const>(&Variant::GetTypeName))
        // [Property(Readonly)] bool zero
        .addProperty("zero", &Variant::IsZero)
        // [Property(Readonly)] bool empty
        .addProperty("empty", &Variant::IsEmpty)
        );

        // [Function] Variant IntToVariant(int value)
        lua["IntToVariant"] = function(IntToVariant);
        // [Function] Variant UIntToVariant(unsigned value)
        lua["UIntToVariant"] = function(UIntToVariant);
        // [Function] Variant StringHashToVariant(const StringHash& value)
        lua["StringHashToVariant"] = function(StringHashToVariant);
        // [Function] Variant BoolToVariant(bool value)
        lua["BoolToVariant"] = function(BoolToVariant);
        // [Function] Variant FloatToVariant(float value)
        lua["FloatToVariant"] = function(FloatToVariant);
        // [Function] Variant DoubleToVariant(double value)
        lua["DoubleToVariant"] = function(DoubleToVariant);
        
        // [Function] Variant Vector2ToVariant0(float x, float y)
        // [Function] Variant Vector2ToVariant1(const Vector2& value)
        lua["Vector2ToVariant1"] = overload(Vector2ToVariant0, Vector2ToVariant1);

        // [Function] Variant Vector3ToVariant0(float x, float y, float z)
        // [Function] Variant Vector3ToVariant1(const Vector3& value)
        lua["Vector3ToVariant1"] = overload(Vector3ToVariant0, Vector3ToVariant1);
        
        // [Function] Variant Vector4ToVariant0(float x, float y, float z, float w)
        // [Function] Variant Vector4ToVariant1(const Vector4& value)
        lua["Vector4ToVariant1"] = overload(Vector4ToVariant0, Vector4ToVariant1);

        // [Function] Variant QuaternionToVariant0(float w, float x, float y, float z)
        // [Function] Variant QuaternionToVariant1(const Quaternion& value)
        lua["QuaternionToVariant1"] = overload(QuaternionToVariant0, QuaternionToVariant1);

        // [Function] Variant ColorToVariant0(float r, float g, float b)
        // [Function] Variant ColorToVariant1(float r, float g, float b, float a)
        // [Function] Variant ColorToVariant2(const Color& value)
        lua["ColorToVariant1"] = overload(ColorToVariant0, ColorToVariant1, ColorToVariant2);

        // [Function] Variant StringToVariant(const String& value)
        lua["StringToVariant"] = function(StringToVariant);
        // [Function] Variant VectorBufferToVariant(const VectorBuffer& value)
        lua["VectorBufferToVariant"] = function(VectorBufferToVariant);
        // [Function] Variant ResourceRefToVariant(const ResourceRef& value)
        lua["ResourceRefToVariant"] = function(ResourceRefToVariant);
        // [Function] Variant ResourceRefListToVariant(const ResourceRefList& value)
        lua["ResourceRefListToVariant"] = function(ResourceRefListToVariant);
        // [Function] Variant VariantVectorToVariant(const VariantVector& value)
        lua["VariantVectorToVariant"] = function(VariantVectorToVariant);
        // [Function] Variant VariantMapToVariant(const VariantMap& value)
        lua["VariantMapToVariant"] = function(VariantMapToVariant);
        // [Function] Variant StringVectorToVariant(const StringVector& value)
        lua["StringVectorToVariant"] = function(StringVectorToVariant);
        // [Function] Variant IntRectToVariant0(int left, int top, int right, int bottom)
        lua["IntRectToVariant0"] = function(IntRectToVariant0);
        // [Function] Variant IntRectToVariant1(const IntRect& value)
        lua["IntRectToVariant1"] = function(IntRectToVariant1);
        // [Function] Variant IntVector2ToVariant0(int x, int y)
        lua["IntVector2ToVariant0"] = function(IntVector2ToVariant0);
        // [Function] Variant IntVector2ToVariant1(const IntVector2& value)
        lua["IntVector2ToVariant1"] = function(IntVector2ToVariant1);
        // [Function] Variant PtrToVariant(RefCounted* value)
        lua["PtrToVariant"] = function(PtrToVariant);
        
        // [Function] Variant Matrix3ToVariant0(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
        // [Function] Variant Matrix3ToVariant1(const Matrix3& value)
        lua["Matrix3ToVariant1"] = overload(Matrix3ToVariant0, Matrix3ToVariant1);

        // [Function] Variant Matrix3x4ToVariant(const Matrix3x4& value)
        lua["Matrix3x4ToVariant"] = function(Matrix3x4ToVariant);
        // [Function] Variant Matrix4ToVariant(const Matrix4& value)
        lua["Matrix4ToVariant"] = function(Matrix4ToVariant);
}
}

