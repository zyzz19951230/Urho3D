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

    // enum JSONValueType;
    lua["JSON_NULL"] = JSON_NULL;
    lua["JSON_BOOL"] = JSON_BOOL;
    lua["JSON_NUMBER"] = JSON_NUMBER;
    lua["JSON_STRING"] = JSON_STRING;
    lua["JSON_ARRAY"] = JSON_ARRAY;
    lua["JSON_OBJECT"] = JSON_OBJECT;

    // enum JSONNumberType;
    lua["JSONNT_NAN"] = JSONNT_NAN;
    lua["JSONNT_INT"] = JSONNT_INT;
    lua["JSONNT_UINT"] = JSONNT_UINT;
    lua["JSONNT_FLOAT_DOUBLE"] = JSONNT_FLOAT_DOUBLE;

    lua["JSONValue"].setClass(UserdataMetatable<JSONValue>()
        .setConstructors<JSONValue(),
        JSONValue(bool),
        JSONValue(int),
        JSONValue(unsigned),
        JSONValue(float),
        JSONValue(double),
        JSONValue(const char*),
        JSONValue(const JSONValue&)>()

        .addFunction("GetValueType", &JSONValue::GetValueType)
        .addFunction("GetNumberType", &JSONValue::GetNumberType)

        .addFunction("IsNull", &JSONValue::IsNull)
        .addFunction("IsBool", &JSONValue::IsBool)
        .addFunction("IsNumber", &JSONValue::IsNumber)
        .addFunction("IsString", &JSONValue::IsString)
        .addFunction("IsArray", &JSONValue::IsArray)
        .addFunction("IsObject", &JSONValue::IsObject)

        .addStaticFunction("SetBool", &JSONValueSetBool)
        .addStaticFunction("SetInt", &JSONValueSetInt)
        .addStaticFunction("SetUInt", &JSONValueSetUInt)
        .addStaticFunction("SetFloat", &JSONValueSetFloat)
        .addStaticFunction("SetDouble", &JSONValueSetDouble)
        .addStaticFunction("SetString", &JSONValueSetString)
        .addStaticFunction("SetArray", &JSONValueSetArray)
        .addStaticFunction("SetObject", &JSONValueSetObject)

        .addFunction("GetBool", &JSONValue::GetBool)
        .addFunction("GetInt", &JSONValue::GetInt)
        .addFunction("GetUInt", &JSONValue::GetUInt)
        .addFunction("GetFloat", &JSONValue::GetFloat)
        .addFunction("GetDouble", &JSONValue::GetDouble)
        .addFunction("GetString", &JSONValue::GetCString)
        .addFunction("GetArray", &JSONValue::GetArray)
        .addFunction("GetObject", &JSONValue::GetObject)

        .addOverloadedFunctions("__index",
            static_cast<const JSONValue&(JSONValue::*)(unsigned) const>(&JSONValue::operator[]),
            static_cast<const JSONValue&(JSONValue::*)(const String&) const>(&JSONValue::operator[]))

        .addOverloadedFunctions("__newindex",
            static_cast<JSONValue&(JSONValue::*)(unsigned)>(&JSONValue::operator[]),
            static_cast<JSONValue&(JSONValue::*)(const String&)>(&JSONValue::operator[]))

        .addFunction("Push", &JSONValue::Push)
        .addFunction("Pop", &JSONValue::Pop)
        .addFunction("Insert", &JSONValue::Insert)

        .addOverloadedFunctions("Erase",
            static_cast<void(JSONValue::*)(unsigned, unsigned)>(&JSONValue::Erase),
            static_cast<bool(JSONValue::*)(const String&)>(&JSONValue::Erase))

        .addFunction("Resize", &JSONValue::Resize)
        .addFunction("Size", &JSONValue::Size)

        .addFunction("Set", &JSONValue::Set)
        .addFunction("Get", &JSONValue::Get)
        .addFunction("Contains", &JSONValue::Contains)

        .addFunction("Clear", &JSONValue::Clear)

        .addProperty("valueType", &JSONValue::GetValueType)
        .addProperty("numberType", &JSONValue::GetNumberType)

        .addProperty("isNull", &JSONValue::IsNull)
        .addProperty("isBool", &JSONValue::IsBool)
        .addProperty("isNumber", &JSONValue::IsNumber)
        .addProperty("isString", &JSONValue::IsString)
        .addProperty("isArray", &JSONValue::IsArray)
        .addProperty("isObject", &JSONValue::IsObject)

        .addStaticField("EMPTY", &JSONValue::EMPTY)
    );
}
}

