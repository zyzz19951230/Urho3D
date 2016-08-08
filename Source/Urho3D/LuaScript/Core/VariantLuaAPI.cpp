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

    // enum VariantType;
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

    lua["ResourceRef"].setClass(UserdataMetatable<ResourceRef>()
        .setConstructors<ResourceRef(),
        ResourceRef(StringHash),
        ResourceRef(StringHash, const String&),
        ResourceRef(const char*, const char*)>()

        .addFunction("__eq", &ResourceRef::operator==)

        .addProperty("type", &ResourceRef::type_)
        .addProperty("name", &ResourceRef::name_)
    );

    lua["ResourceRefList"].setClass(UserdataMetatable<ResourceRefList>()
        .setConstructors<ResourceRefList(),
        ResourceRefList(StringHash)>()

        .addFunction("__eq", &ResourceRefList::operator==)

        .addProperty("type", &ResourceRefList::type_)
    );

    // todo from here:
    lua["Variant"].setClass(UserdataMetatable<Variant>()
        .setConstructors<
        // Variant(),
        // Variant(int), 
        // Variant(unsigned),
        Variant(const StringHash&),
        Variant(bool),
        Variant(float),
        Variant(double),
        Variant(const Vector2&),
        Variant(const Vector3&),
        Variant(const Vector4&),
        Variant(const Quaternion&),
        Variant(const Color&),
        Variant(const char*),
        Variant(const ResourceRef&),
        Variant(const ResourceRefList&),
        Variant(const VariantVector&),
        Variant(const VariantMap&),
        Variant(const StringVector&),
        Variant(const IntRect&),
        Variant(const IntVector2&),
        Variant(RefCounted*),
        Variant(const Matrix3&),
        Variant(const Matrix3x4&),
        Variant(const Matrix4&)> ()

        .addStaticFunction("FromInt", &VariantFromInt)
        .addStaticFunction("FromFloat", &VariantFromFloat)
        .addStaticFunction("FromDouble", &VariantFromDouble)

        .addFunction("Clear", &Variant::Clear)

        .addFunction("__eq", static_cast<bool(Variant::*)(const Variant&) const>(&Variant::operator==))

        .addFunction("GetInt", &Variant::GetInt)
        .addFunction("GetUInt", &Variant::GetUInt)
        .addFunction("GetStringHash", &Variant::GetStringHash)
        .addFunction("GetBool", &Variant::GetBool)
        .addFunction("GetFloat", &Variant::GetFloat)
        .addFunction("GetDouble", &Variant::GetDouble)
        
        .addFunction("GetVector2", &Variant::GetVector2)
        .addFunction("GetVector3", &Variant::GetVector3)
        .addFunction("GetVector4", &Variant::GetVector4)
        .addFunction("GetQuaternion", &Variant::GetQuaternion)
        .addFunction("GetColor", &Variant::GetColor)
        .addFunction("GetString", &Variant::GetString)

        .addFunction("GetRawBuffer", &Variant::GetBuffer)
        .addFunction("GetBuffer", &Variant::GetVectorBuffer)
        .addFunction("GetVoidPtr", &Variant::GetVoidPtr)

        .addFunction("GetResourceRef", &Variant::GetResourceRef)
        .addFunction("GetResourceRefList", &Variant::GetResourceRefList)
        .addFunction("GetVariantVector", &Variant::GetVariantVector)
        .addFunction("GetStringVector", &Variant::GetStringVector)
        .addFunction("GetVariantMap", &Variant::GetVariantMap)
        .addFunction("GetIntRect", &Variant::GetIntRect)
        .addFunction("GetIntVector2", &Variant::GetIntVector2)
        
        .addStaticFunction("GetPtr", &VariantGetPtr)

        .addFunction("GetMatrix3", &Variant::GetMatrix3)
        .addFunction("GetMatrix3x4", &Variant::GetMatrix3x4)
        .addFunction("GetMatrix4", &Variant::GetMatrix4)

        .addFunction("GetType", &Variant::GetType)
        .addFunction("GetTypeName", static_cast<String(Variant::*)() const>(&Variant::GetTypeName))
        .addFunction("ToString", &Variant::ToString)
        .addFunction("IsZero", &Variant::IsZero)
        .addFunction("IsEmpty", &Variant::IsEmpty)

        .addProperty("type", &Variant::GetType)
        .addProperty("typeName", static_cast<String(Variant::*)() const>(&Variant::GetTypeName))
        .addProperty("zero", &Variant::IsZero)
        .addProperty("empty", &Variant::IsEmpty)
    );
}
}

