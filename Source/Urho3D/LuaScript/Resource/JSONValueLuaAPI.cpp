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

#include "../../Core/Context.h"
#include "../../Core/Variant.h"
#include "../../Resource/JSONValue.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void JSONValueSetBool(JSONValue& self, bool value)
{
    self = value;
}

static void JSONValueSetInt(JSONValue& self, int value)
{
    self = value;
}

static void JSONValueSetUInt(JSONValue& self, unsigned value)
{
    self = value;
}

static void JSONValueSetFloat(JSONValue& self, float value)
{
    self = value;
}

static void JSONValueSetDouble(JSONValue& self, double value)
{
    self = value;
}

static void JSONValueSetString(JSONValue& self, const char* value)
{
    self = value;
}

static void JSONValueSetArray(JSONValue& self, const JSONArray& value)
{
    self = value;
}

static void JSONValueSetObject(JSONValue& self, const JSONObject& value)
{
    self = value;
}

void RegisterJSONValue(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] JSONValueType
    // [Variable] JSON_NULL
    lua["JSON_NULL"] = JSON_NULL;
    // [Variable] JSON_BOOL,
    lua["JSON_BOOL"] = JSON_BOOL;
    // [Variable] JSON_NUMBER,
    lua["JSON_NUMBER"] = JSON_NUMBER;
    // [Variable] JSON_STRING,
    lua["JSON_STRING"] = JSON_STRING;
    // [Variable] JSON_ARRAY,
    lua["JSON_ARRAY"] = JSON_ARRAY;
    // [Variable] JSON_OBJECT,
    lua["JSON_OBJECT"] = JSON_OBJECT;

    // [Enum] JSONNumberType
    // [Variable] void SetType(JSONValueType valueType, JSONNumberType numberType
    lua["JSONNT_NAN"] = JSONNT_NAN;
    // [Variable] JSONNT_INT,
    lua["JSONNT_INT"] = JSONNT_INT;
    // [Variable] JSONNT_UINT,
    lua["JSONNT_UINT"] = JSONNT_UINT;
    // [Variable] JSONNT_FLOAT_DOUBLE,
    lua["JSONNT_FLOAT_DOUBLE"] = JSONNT_FLOAT_DOUBLE;

    // [Class] JSONValue
    lua["JSONValue"].setClass(UserdataMetatable<JSONValue>()
        .setConstructors<JSONValue(),
        JSONValue(bool),
        JSONValue(int),
        JSONValue(unsigned),
        JSONValue(float),
        JSONValue(double),
        JSONValue(const char*),
        JSONValue(const JSONValue&)>()

        // [Method] JSONValueType GetValueType() const
        .addFunction("GetValueType", &JSONValue::GetValueType)
        // [Method] JSONNumberType GetNumberType() const
        .addFunction("GetNumberType", &JSONValue::GetNumberType)

        // [Method] bool IsNull() const
        .addFunction("IsNull", &JSONValue::IsNull)
        // [Method] bool IsBool() const
        .addFunction("IsBool", &JSONValue::IsBool)
        // [Method] bool IsNumber() const
        .addFunction("IsNumber", &JSONValue::IsNumber)
        // [Method] bool IsString() const
        .addFunction("IsString", &JSONValue::IsString)
        // [Method] bool IsArray() const
        .addFunction("IsArray", &JSONValue::IsArray)
        // [Method] bool IsObject() const
        .addFunction("IsObject", &JSONValue::IsObject)

        .addStaticFunction("SetBool", &JSONValueSetBool)
        .addStaticFunction("SetInt", &JSONValueSetInt)
        .addStaticFunction("SetUInt", &JSONValueSetUInt)
        .addStaticFunction("SetFloat", &JSONValueSetFloat)
        .addStaticFunction("SetDouble", &JSONValueSetDouble)
        .addStaticFunction("SetString", &JSONValueSetString)
        .addStaticFunction("SetArray", &JSONValueSetArray)
        .addStaticFunction("SetObject", &JSONValueSetObject)

        // [Method] bool GetBool() const
        .addFunction("GetBool", &JSONValue::GetBool)
        // [Method] int GetInt() const
        .addFunction("GetInt", &JSONValue::GetInt)
        // [Method] unsigned GetUInt() const
        .addFunction("GetUInt", &JSONValue::GetUInt)
        // [Method] float GetFloat() const
        .addFunction("GetFloat", &JSONValue::GetFloat)
        // [Method] double GetDouble() const
        .addFunction("GetDouble", &JSONValue::GetDouble)
        // [Method] const char* GetString() const
        .addFunction("GetString", &JSONValue::GetCString)
        // [Method] const JSONArray& GetArray() const
        .addFunction("GetArray", &JSONValue::GetArray)
        // [Method] const JSONObject& GetObject() const
        .addFunction("GetObject", &JSONValue::GetObject)

        .addOverloadedFunctions("__index",
            static_cast<const JSONValue&(JSONValue::*)(unsigned) const>(&JSONValue::operator[]),
            static_cast<const JSONValue&(JSONValue::*)(const String&) const>(&JSONValue::operator[]))

        .addOverloadedFunctions("__newindex",
            static_cast<JSONValue&(JSONValue::*)(unsigned)>(&JSONValue::operator[]),
            static_cast<JSONValue&(JSONValue::*)(const String&)>(&JSONValue::operator[]))

        // [Method] void Push(const JSONValue& value)
        .addFunction("Push", &JSONValue::Push)
        // [Method] void Pop()
        .addFunction("Pop", &JSONValue::Pop)
        // [Method] void Insert(unsigned pos, const JSONValue& value)
        .addFunction("Insert", &JSONValue::Insert)

        .addOverloadedFunctions("Erase",
            static_cast<void(JSONValue::*)(unsigned, unsigned)>(&JSONValue::Erase),
            static_cast<bool(JSONValue::*)(const String&)>(&JSONValue::Erase))

        // [Method] void Resize(unsigned newSize)
        .addFunction("Resize", &JSONValue::Resize)
        // [Method] unsigned Size() const
        .addFunction("Size", &JSONValue::Size)

        // [Method] void Set(const String& key, const JSONValue& value)
        .addFunction("Set", &JSONValue::Set)
        // [Method] const JSONValue& Get(const String& key) const
        .addFunction("Get", &JSONValue::Get)
        // [Method] bool Contains(const String& key) const
        .addFunction("Contains", &JSONValue::Contains)

        // [Method] void Clear()
        .addFunction("Clear", &JSONValue::Clear)

        // [Property(ReadOnly)] JSONValueType valueType
        .addProperty("valueType", &JSONValue::GetValueType)
        // [Property(ReadOnly)] JSONNumberType numberType
        .addProperty("numberType", &JSONValue::GetNumberType)

        // [Property(ReadOnly)] bool isNull
        .addProperty("isNull", &JSONValue::IsNull)
        // [Property(ReadOnly)] bool isBool
        .addProperty("isBool", &JSONValue::IsBool)
        // [Property(ReadOnly)] bool isNumber
        .addProperty("isNumber", &JSONValue::IsNumber)
        // [Property(ReadOnly)] bool isString
        .addProperty("isString", &JSONValue::IsString)
        // [Property(ReadOnly)] bool isArray
        .addProperty("isArray", &JSONValue::IsArray)
        // [Property(ReadOnly)] bool isObject
        .addProperty("isObject", &JSONValue::IsObject)

        .addStaticField("EMPTY", &JSONValue::EMPTY)
    );
}
}

