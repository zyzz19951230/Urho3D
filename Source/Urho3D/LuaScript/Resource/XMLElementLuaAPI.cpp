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

#include "../../Resource/XMLElement.h"
#include "../../Resource/XMLFile.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(XMLElementRemoveChildren, XMLElement, RemoveChildren, 0, 1, bool(XMLElement::*)(const String&));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(XMLElementRemoveAttribute, XMLElement, RemoveAttribute, 0, 1, bool(XMLElement::*)(const String&));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(XMLElementGetChild, XMLElement, GetChild, 0, 1, XMLElement(XMLElement::*)(const String&)const);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(XMLElementGetNext, XMLElement, GetNext, 0, 1, XMLElement(XMLElement::*)(const String&)const);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(XMLElementGetAttribute, XMLElement, GetAttribute, 0, 1, String(XMLElement::*)(const String&)const);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(XPathQuerySetQuery, XPathQuery, SetQuery, 1, 3);

void RegisterXMLElement(kaguya::State& lua)
{
    using namespace kaguya;

    lua["XMLElement"].setClass(UserdataMetatable<XMLElement>()
        .setConstructors<XMLElement(),
        XMLElement(const XMLElement&)>()

        .addFunction("CreateChild", static_cast<XMLElement(XMLElement::*)(const String&)>(&XMLElement::CreateChild))

        .addOverloadedFunctions("RemoveChild",
            static_cast<bool(XMLElement::*)(const XMLElement&)>(&XMLElement::RemoveChild),
            static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::RemoveChild))

        .addFunction("RemoveChildren", XMLElementRemoveChildren())
        .addFunction("RemoveAttribute", XMLElementRemoveAttribute())

        .addFunction("SelectSinglePrepared", &XMLElement::SelectSinglePrepared)
        .addFunction("SelectPrepared", &XMLElement::SelectPrepared)

        .addFunction("SetValue", static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::SetValue))

        .addOverloadedFunctions("SetAttribute",
            static_cast<bool(XMLElement::*)(const String&, const String&)>(&XMLElement::SetAttribute),
            static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::SetAttribute))

        .addFunction("SetBool", &XMLElement::SetBool)
        .addFunction("SetBoundingBox", &XMLElement::SetBoundingBox)
        .addFunction("SetColor", &XMLElement::SetColor)
        .addFunction("SetFloat", &XMLElement::SetFloat)
        .addFunction("SetDouble", &XMLElement::SetDouble)
        .addFunction("SetUInt", &XMLElement::SetUInt)
        .addFunction("SetInt", &XMLElement::SetInt)
        .addFunction("SetIntRect", &XMLElement::SetIntRect)
        .addFunction("SetIntVector2", &XMLElement::SetIntVector2)
        .addFunction("SetRect", &XMLElement::SetRect)
        .addFunction("SetQuaternion", &XMLElement::SetQuaternion)
        .addFunction("SetString", &XMLElement::SetString)
        .addFunction("SetVariant", &XMLElement::SetVariant)
        .addFunction("SetVariantValue", &XMLElement::SetVariantValue)
        .addFunction("SetResourceRef", &XMLElement::SetResourceRef)
        .addFunction("SetResourceRefList", &XMLElement::SetResourceRefList)
        .addFunction("SetVariantVector", &XMLElement::SetVariantVector)
        .addFunction("SetStringVector", &XMLElement::SetStringVector)
        .addFunction("SetVariantMap", &XMLElement::SetVariantMap)
        .addFunction("SetVector2", &XMLElement::SetVector2)
        .addFunction("SetVector3", &XMLElement::SetVector3)
        .addFunction("SetVector4", &XMLElement::SetVector4)
        .addFunction("SetVectorVariant", &XMLElement::SetVectorVariant)
        .addFunction("SetMatrix3", &XMLElement::SetMatrix3)
        .addFunction("SetMatrix3x4", &XMLElement::SetMatrix3x4)
        .addFunction("SetMatrix4", &XMLElement::SetMatrix4)

        .addFunction("IsNull", &XMLElement::IsNull)
        .addFunction("NotNull", &XMLElement::NotNull)
        .addFunction("GetName", &XMLElement::GetName)

        .addFunction("HasChild", static_cast<bool(XMLElement::*)(const String&) const>(&XMLElement::HasChild))

        .addFunction("GetChild", XMLElementGetChild())
        .addFunction("GetNext", XMLElementGetNext())

        .addFunction("GetParent", &XMLElement::GetParent)
        .addFunction("GetNumAttributes", &XMLElement::GetNumAttributes)
        .addFunction("HasAttribute", static_cast<bool(XMLElement::*)(const String&) const>(&XMLElement::HasAttribute))

        .addFunction("GetValue", &XMLElement::GetValue)

        .addFunction("GetAttribute", XMLElementGetAttribute())

        .addFunction("GetAttributeLower", static_cast<String(XMLElement::*)(const String&) const>(&XMLElement::GetAttributeLower))
        .addFunction("GetAttributeUpper", static_cast<String(XMLElement::*)(const String&) const>(&XMLElement::GetAttributeUpper))

        .addFunction("GetAttributeNames", &XMLElement::GetAttributeNames)
        .addFunction("GetBool", &XMLElement::GetBool)

        .addFunction("GetBoundingBox", &XMLElement::GetBoundingBox)
        .addFunction("GetColor", &XMLElement::GetColor)
        .addFunction("GetFloat", &XMLElement::GetFloat)
        .addFunction("GetDouble", &XMLElement::GetDouble)
        .addFunction("GetUInt", &XMLElement::GetUInt)
        .addFunction("GetInt", &XMLElement::GetInt)
        .addFunction("GetIntRect", &XMLElement::GetIntRect)
        .addFunction("GetIntVector2", &XMLElement::GetIntVector2)
        .addFunction("GetRect", &XMLElement::GetRect)
        .addFunction("GetQuaternion", &XMLElement::GetQuaternion)
        .addFunction("GetVariant", &XMLElement::GetVariant)
        .addFunction("GetVariantValue", &XMLElement::GetVariantValue)
        .addFunction("GetResourceRef", &XMLElement::GetResourceRef)
        .addFunction("GetResourceRefList", &XMLElement::GetResourceRefList)
        .addFunction("GetVariantVector", &XMLElement::GetVariantVector)
        .addFunction("GetStringVector", &XMLElement::GetStringVector)
        .addFunction("GetVariantMap", &XMLElement::GetVariantMap)
        .addFunction("GetVector2", &XMLElement::GetVector2)
        .addFunction("GetVector3", &XMLElement::GetVector3)
        .addFunction("GetVector4", &XMLElement::GetVector4)
        .addFunction("GetVector", &XMLElement::GetVector)
        .addFunction("GetVectorVariant", &XMLElement::GetVectorVariant)
        .addFunction("GetMatrix3", &XMLElement::GetMatrix3)
        .addFunction("GetMatrix3x4", &XMLElement::GetMatrix3x4)
        .addFunction("GetMatrix4", &XMLElement::GetMatrix4)
        .addFunction("GetFile", &XMLElement::GetFile)

        .addProperty("null", &XMLElement::IsNull)
        .addProperty("name", &XMLElement::GetName)
        .addProperty("parent", &XMLElement::GetParent)
        .addProperty("numAttributes", &XMLElement::GetNumAttributes)
        .addProperty("value", &XMLElement::GetValue)

        .addStaticField("EMPTY", &XMLElement::EMPTY)
    );

    lua["XPathResultSet"].setClass(UserdataMetatable<XPathResultSet>()
        .setConstructors<XPathResultSet(),
        XPathResultSet(const XPathResultSet&)>()

        .addFunction("__index", &XPathResultSet::operator[])

        .addFunction("FirstResult", &XPathResultSet::FirstResult)
        .addFunction("Size", &XPathResultSet::Size)
        .addFunction("Empty", &XPathResultSet::Empty)
    );

    lua["XPathQuery"].setClass(UserdataMetatable<XPathQuery>()
        .setConstructors<XPathQuery(),
        XPathQuery(const String&, const String&)>()

        .addFunction("Bind", &XPathQuery::Bind)

        .addOverloadedFunctions("SetVariable",
            static_cast<bool(XPathQuery::*)(const String&, bool)>(&XPathQuery::SetVariable),
            static_cast<bool(XPathQuery::*)(const String&, float)>(&XPathQuery::SetVariable),
            static_cast<bool(XPathQuery::*)(const char*, const char*)>(&XPathQuery::SetVariable),
            static_cast<bool(XPathQuery::*)(const String&, const XPathResultSet&)>(&XPathQuery::SetVariable))

        .addFunction("SetQuery", XPathQuerySetQuery())

        .addFunction("Clear", &XPathQuery::Clear)
        .addFunction("EvaluateToBool", &XPathQuery::EvaluateToBool)
        .addFunction("EvaluateToFloat", &XPathQuery::EvaluateToFloat)
        .addFunction("EvaluateToString", &XPathQuery::EvaluateToString)
        .addFunction("Evaluate", &XPathQuery::Evaluate)
        .addFunction("GetQuery", &XPathQuery::GetQuery)

        .addProperty("query", &XPathQuery::GetQuery)
    );
}
}

