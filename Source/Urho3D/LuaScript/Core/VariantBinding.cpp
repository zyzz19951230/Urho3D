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

static Variant VariantFromInt(int value)
{
    return Variant(value);
}

static Variant VariantFromFloat(float value)
{
    return Variant(value);
}

static Variant VariantFromDouble(double value)
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

        // [Method] bool ==(const ResourceRef& rhs) const
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

        // [Method] bool ==(const ResourceRefList& rhs) const
        .addFunction("__eq", &ResourceRefList::operator==)

        // [Field] StringHash type
        .addProperty("type", &ResourceRefList::type_)
    );

    // [Class] Variant
    lua["Variant"].setClass(UserdataMetatable<Variant>()
        .setConstructors<
        // Variant(),
        // Variant(int), 
        // Variant(unsigned),
        // [Constructor] Variant(const StringHash& value)
        Variant(const StringHash&),
        // [Constructor] Variant(bool value)
        Variant(bool),
        // [Constructor] Variant(float value)
        Variant(float),
        // [Constructor] Variant(double value)
        Variant(double),
        // [Constructor] Variant(const Vector2& value)
        Variant(const Vector2&),
        // [Constructor] Variant(const Vector3& value)
        Variant(const Vector3&),
        // [Constructor] Variant(const Vector4& value)
        Variant(const Vector4&),
        // [Constructor] Variant(const Quaternion& value)
        Variant(const Quaternion&),
        // [Constructor] Variant(const Color& value)
        Variant(const Color&),
        // [Constructor] Variant(const String& value)
        Variant(const String&),
        // [Constructor] Variant(const ResourceRef& value)
        Variant(const ResourceRef&),
        // [Constructor] Variant(const ResourceRefList& value)
        Variant(const ResourceRefList&),
        // [Constructor] Variant(const VariantVector& value)
        Variant(const VariantVector&),
        // [Constructor] Variant(const VariantMap& value)
        Variant(const VariantMap&),
        // [Constructor] Variant(const StringVector& value)
        Variant(const StringVector&),
        // [Constructor] Variant(const IntRect& value)
        Variant(const IntRect&),
        // [Constructor] Variant(const IntVector2& value)
        Variant(const IntVector2&),
        // [Constructor] Variant(RefCounted* value)
        Variant(RefCounted*),
        // [Constructor] Variant(const Matrix3& value)
        Variant(const Matrix3&),
        // [Constructor] Variant(const Matrix3x4& value)
        Variant(const Matrix3x4&),
        // [Constructor] Variant(const Matrix4& value)
        Variant(const Matrix4&)> ()

        // [StaticMethod] Variant FromInt(int value)
        .addStaticFunction("FromInt", &VariantFromInt)
        // [StaticMethod] Variant FromFloat(float value)
        .addStaticFunction("FromFloat", &VariantFromFloat)
        // [StaticMethod] Variant FromDouble(double value)
        .addStaticFunction("FromDouble", &VariantFromDouble)

        // [Method] void Clear()
        .addFunction("Clear", &Variant::Clear)

        // [Method] bool ==(const Variant& rhs) const
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

        // [Property(ReadOnly)] VariantType type
        .addProperty("type", &Variant::GetType)
        // [Property(ReadOnly)] String typeName
        .addProperty("typeName", static_cast<String(Variant::*)() const>(&Variant::GetTypeName))
        // [Property(ReadOnly)] bool zero
        .addProperty("zero", &Variant::IsZero)
        // [Property(ReadOnly)] bool empty
        .addProperty("empty", &Variant::IsEmpty)
    );
}
}

