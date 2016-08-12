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

    // [Class] XMLElement
    lua["XMLElement"].setClass(UserdataMetatable<XMLElement>()
        // [Constructor] XMLElement()
        .setConstructors<XMLElement(),
        // [Constructor] XMLElement(const XMLElement& element)
        XMLElement(const XMLElement&)>()

        // [Method] XMLElement CreateChild(const String& name)
        .addFunction("CreateChild", static_cast<XMLElement(XMLElement::*)(const String&)>(&XMLElement::CreateChild))

        .addOverloadedFunctions("RemoveChild",
            // [Method] bool RemoveChild(const XMLElement& element)
            static_cast<bool(XMLElement::*)(const XMLElement&)>(&XMLElement::RemoveChild),
            // [Method] bool RemoveChild(const String& name)
            static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::RemoveChild))

        // [Method] bool RemoveChildren(const String& name = String::EMPTY)
        .addFunction("RemoveChildren", XMLElementRemoveChildren())
        // [Method] bool RemoveAttribute(const String& name = String::EMPTY)
        .addFunction("RemoveAttribute", XMLElementRemoveAttribute())

        // [Method] XMLElement SelectSinglePrepared(const XPathQuery& query) const
        .addFunction("SelectSinglePrepared", &XMLElement::SelectSinglePrepared)
        // [Method] XPathResultSet SelectPrepared(const XPathQuery& query) const
        .addFunction("SelectPrepared", &XMLElement::SelectPrepared)

        // [Method] bool SetValue(const String& value)
        .addFunction("SetValue", static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::SetValue))

        .addOverloadedFunctions("SetAttribute",
            // [Method] bool SetAttribute(const String& name, const String& value)
            static_cast<bool(XMLElement::*)(const String&, const String&)>(&XMLElement::SetAttribute),
            // [Method] bool SetAttribute(const String& value)
            static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::SetAttribute))

        // [Method] bool SetBool(const String& name, bool value)
        .addFunction("SetBool", &XMLElement::SetBool)
        // [Method] bool SetBoundingBox(const BoundingBox& value)
        .addFunction("SetBoundingBox", &XMLElement::SetBoundingBox)
        // [Method] bool SetColor(const String& name, const Color& value)
        .addFunction("SetColor", &XMLElement::SetColor)
        // [Method] bool SetFloat(const String& name, float value)
        .addFunction("SetFloat", &XMLElement::SetFloat)
        // [Method] bool SetDouble(const String& name, double value)
        .addFunction("SetDouble", &XMLElement::SetDouble)
        // [Method] bool SetUInt(const String& name, unsigned value)
        .addFunction("SetUInt", &XMLElement::SetUInt)
        // [Method] bool SetInt(const String& name, int value)
        .addFunction("SetInt", &XMLElement::SetInt)
        // [Method] bool SetIntRect(const String& name, const IntRect& value)
        .addFunction("SetIntRect", &XMLElement::SetIntRect)
        // [Method] bool SetIntVector2(const String& name, const IntVector2& value)
        .addFunction("SetIntVector2", &XMLElement::SetIntVector2)
        // [Method] bool SetRect(const String& name, const Rect& value)
        .addFunction("SetRect", &XMLElement::SetRect)
        // [Method] bool SetQuaternion(const String& name, const Quaternion& value)
        .addFunction("SetQuaternion", &XMLElement::SetQuaternion)
        // [Method] bool SetString(const String& name, const String& value)
        .addFunction("SetString", &XMLElement::SetString)
        // [Method] bool SetVariant(const Variant& value)
        .addFunction("SetVariant", &XMLElement::SetVariant)
        // [Method] bool SetVariantValue(const Variant& value)
        .addFunction("SetVariantValue", &XMLElement::SetVariantValue)
        // [Method] bool SetResourceRef(const ResourceRef& value)
        .addFunction("SetResourceRef", &XMLElement::SetResourceRef)
        // [Method] bool SetResourceRefList(const ResourceRefList& value)
        .addFunction("SetResourceRefList", &XMLElement::SetResourceRefList)
        // [Method] bool SetVariantVector(const VariantVector& value)
        .addFunction("SetVariantVector", &XMLElement::SetVariantVector)
        // [Method] bool SetStringVector(const StringVector& value)
        .addFunction("SetStringVector", &XMLElement::SetStringVector)
        // [Method] bool SetVariantMap(const VariantMap& value)
        .addFunction("SetVariantMap", &XMLElement::SetVariantMap)
        // [Method] bool SetVector2(const String& name, const Vector2& value)
        .addFunction("SetVector2", &XMLElement::SetVector2)
        // [Method] bool SetVector3(const String& name, const Vector3& value)
        .addFunction("SetVector3", &XMLElement::SetVector3)
        // [Method] bool SetVector4(const String& name, const Vector4& value)
        .addFunction("SetVector4", &XMLElement::SetVector4)
        // [Method] bool SetVectorVariant(const String& name, const Variant& value)
        .addFunction("SetVectorVariant", &XMLElement::SetVectorVariant)
        // [Method] bool SetMatrix3(const String& name, const Matrix3& value)
        .addFunction("SetMatrix3", &XMLElement::SetMatrix3)
        // [Method] bool SetMatrix3x4(const String& name, const Matrix3x4& value)
        .addFunction("SetMatrix3x4", &XMLElement::SetMatrix3x4)
        // [Method] bool SetMatrix4(const String& name, const Matrix4& value)
        .addFunction("SetMatrix4", &XMLElement::SetMatrix4)

        // [Method] bool IsNull() const
        .addFunction("IsNull", &XMLElement::IsNull)
        // [Method] bool NotNull() const
        .addFunction("NotNull", &XMLElement::NotNull)
        // [Method] String GetName() const
        .addFunction("GetName", &XMLElement::GetName)

        // [Method] bool HasChild(const String& name) const
        .addFunction("HasChild", static_cast<bool(XMLElement::*)(const String&) const>(&XMLElement::HasChild))

        // [Method] XMLElement GetChild(const String& name = String::EMPTY) const
        .addFunction("GetChild", XMLElementGetChild())
        // [Method] XMLElement GetNext(const String& name = String::EMPTY) const
        .addFunction("GetNext", XMLElementGetNext())

        // [Method] XMLElement GetParent() const
        .addFunction("GetParent", &XMLElement::GetParent)
        // [Method] unsigned GetNumAttributes() const
        .addFunction("GetNumAttributes", &XMLElement::GetNumAttributes)
        // [Method] bool HasAttribute(const String& name) const
        .addFunction("HasAttribute", static_cast<bool(XMLElement::*)(const String&) const>(&XMLElement::HasAttribute))

        // [Method] String GetValue() const
        .addFunction("GetValue", &XMLElement::GetValue)

        // [Method] String GetAttribute(const String& name = String::EMPTY) const
        .addFunction("GetAttribute", XMLElementGetAttribute())

        // [Method] String GetAttributeLower(const String& name) const
        .addFunction("GetAttributeLower", static_cast<String(XMLElement::*)(const String&) const>(&XMLElement::GetAttributeLower))
        // [Method] String GetAttributeUpper(const String& name) const
        .addFunction("GetAttributeUpper", static_cast<String(XMLElement::*)(const String&) const>(&XMLElement::GetAttributeUpper))

        // [Method] Vector<String> GetAttributeNames() const
        .addFunction("GetAttributeNames", &XMLElement::GetAttributeNames)
        // [Method] bool GetBool(const String& name) const
        .addFunction("GetBool", &XMLElement::GetBool)

        // [Method] BoundingBox GetBoundingBox() const
        .addFunction("GetBoundingBox", &XMLElement::GetBoundingBox)
        // [Method] Color GetColor(const String& name) const
        .addFunction("GetColor", &XMLElement::GetColor)
        // [Method] float GetFloat(const String& name) const
        .addFunction("GetFloat", &XMLElement::GetFloat)
        // [Method] double GetDouble(const String& name) const
        .addFunction("GetDouble", &XMLElement::GetDouble)
        // [Method] unsigned GetUInt(const String& name) const
        .addFunction("GetUInt", &XMLElement::GetUInt)
        // [Method] int GetInt(const String& name) const
        .addFunction("GetInt", &XMLElement::GetInt)
        // [Method] IntRect GetIntRect(const String& name) const
        .addFunction("GetIntRect", &XMLElement::GetIntRect)
        // [Method] IntVector2 GetIntVector2(const String& name) const
        .addFunction("GetIntVector2", &XMLElement::GetIntVector2)
        // [Method] Rect GetRect(const String& name) const
        .addFunction("GetRect", &XMLElement::GetRect)
        // [Method] Quaternion GetQuaternion(const String& name) const
        .addFunction("GetQuaternion", &XMLElement::GetQuaternion)
        // [Method] Variant GetVariant() const
        .addFunction("GetVariant", &XMLElement::GetVariant)
        // [Method] Variant GetVariantValue(VariantType type) const
        .addFunction("GetVariantValue", &XMLElement::GetVariantValue)
        // [Method] ResourceRef GetResourceRef() const
        .addFunction("GetResourceRef", &XMLElement::GetResourceRef)
        // [Method] ResourceRefList GetResourceRefList() const
        .addFunction("GetResourceRefList", &XMLElement::GetResourceRefList)
        // [Method] VariantVector GetVariantVector() const
        .addFunction("GetVariantVector", &XMLElement::GetVariantVector)
        // [Method] StringVector GetStringVector() const
        .addFunction("GetStringVector", &XMLElement::GetStringVector)
        // [Method] VariantMap GetVariantMap() const
        .addFunction("GetVariantMap", &XMLElement::GetVariantMap)
        // [Method] Vector2 GetVector2(const String& name) const
        .addFunction("GetVector2", &XMLElement::GetVector2)
        // [Method] Vector3 GetVector3(const String& name) const
        .addFunction("GetVector3", &XMLElement::GetVector3)
        // [Method] Vector4 GetVector4(const String& name) const
        .addFunction("GetVector4", &XMLElement::GetVector4)
        // [Method] Vector4 GetVector(const String& name) const
        .addFunction("GetVector", &XMLElement::GetVector)
        // [Method] Variant GetVectorVariant(const String& name) const
        .addFunction("GetVectorVariant", &XMLElement::GetVectorVariant)
        // [Method] Matrix3 GetMatrix3(const String& name) const
        .addFunction("GetMatrix3", &XMLElement::GetMatrix3)
        // [Method] Matrix3x4 GetMatrix3x4(const String& name) const
        .addFunction("GetMatrix3x4", &XMLElement::GetMatrix3x4)
        // [Method] Matrix4 GetMatrix4(const String& name) const
        .addFunction("GetMatrix4", &XMLElement::GetMatrix4)
        // [Method] XMLFile* GetFile() const
        .addFunction("GetFile", &XMLElement::GetFile)

        // [Property(Readonly)] bool null
        .addProperty("null", &XMLElement::IsNull)
        // [Property(Readonly)] String name
        .addProperty("name", &XMLElement::GetName)
        // [Property(Readonly)] XMLElement parent
        .addProperty("parent", &XMLElement::GetParent)
        // [Property(Readonly)] unsigned numAttributes
        .addProperty("numAttributes", &XMLElement::GetNumAttributes)
        // [Property(Readonly)] String value
        .addProperty("value", &XMLElement::GetValue)

        // [StaticConstant] XMLElement EMPTY
        .addStaticField("EMPTY", &XMLElement::EMPTY)
    );

    // [Class] XPathResultSet
    lua["XPathResultSet"].setClass(UserdataMetatable<XPathResultSet>()
        // [Constructor] XPathResultSet()
        .setConstructors<XPathResultSet(),
        // [Constructor] XPathResultSet(const XPathResultSet& rhs)
        XPathResultSet(const XPathResultSet&)>()

        // [Method] XMLElement operator[](unsigned index) const
        .addFunction("__index", &XPathResultSet::operator[])

        // [Method] XMLElement FirstResult()
        .addFunction("FirstResult", &XPathResultSet::FirstResult)
        // [Method] unsigned Size() const
        .addFunction("Size", &XPathResultSet::Size)
        // [Method] bool Empty() const
        .addFunction("Empty", &XPathResultSet::Empty)
    );

    // [Class] XPathQuery
    lua["XPathQuery"].setClass(UserdataMetatable<XPathQuery>()
        // [Constructor] XPathQuery()
        .setConstructors<XPathQuery(),
        // [Constructor] XPathQuery(const String& queryString, const String& variableString = String::EMPTY)
        XPathQuery(const String&, const String&)>()

        // [Method] void Bind()
        .addFunction("Bind", &XPathQuery::Bind)

        .addOverloadedFunctions("SetVariable",
            // [Method] bool SetVariable(const String& name, bool value)
            static_cast<bool(XPathQuery::*)(const String&, bool)>(&XPathQuery::SetVariable),
            // [Method] bool SetVariable(const String& name, float value)
            static_cast<bool(XPathQuery::*)(const String&, float)>(&XPathQuery::SetVariable),
            // [Method] bool SetVariable(const String& name, const String& value)
            static_cast<bool(XPathQuery::*)(const String&, const String&)>(&XPathQuery::SetVariable),
            // [Method] bool SetVariable(const String& name, const XPathResultSet& value)
            static_cast<bool(XPathQuery::*)(const String&, const XPathResultSet&)>(&XPathQuery::SetVariable))

        // [Method] bool SetQuery(const String& queryString, const String& variableString = String::EMPTY, bool bind = true)
        .addFunction("SetQuery", XPathQuerySetQuery())

        // [Method] void Clear()
        .addFunction("Clear", &XPathQuery::Clear)
        // [Method] bool EvaluateToBool(XMLElement element) const
        .addFunction("EvaluateToBool", &XPathQuery::EvaluateToBool)
        // [Method] float EvaluateToFloat(XMLElement element) const
        .addFunction("EvaluateToFloat", &XPathQuery::EvaluateToFloat)
        // [Method] String EvaluateToString(XMLElement element) const
        .addFunction("EvaluateToString", &XPathQuery::EvaluateToString)
        // [Method] XPathResultSet Evaluate(XMLElement element) const
        .addFunction("Evaluate", &XPathQuery::Evaluate)
        // [Method] String GetQuery() const
        .addFunction("GetQuery", &XPathQuery::GetQuery)

        // [Property(Readonly)] String query
        .addProperty("query", &XPathQuery::GetQuery)
    );
}
}

