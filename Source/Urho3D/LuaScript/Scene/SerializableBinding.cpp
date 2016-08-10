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

#include "../../IO/File.h"
#include "../../Resource/JSONValue.h"
#include "../../Resource/XMLElement.h"
#include "../../Scene/Serializable.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static bool SerializableLoad0(Serializable* self, const String& fileName, bool setInstanceDefault = false)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    return self->Load(*file, setInstanceDefault);
}

KAGUYA_FUNCTION_OVERLOADS(SerializableLoadOverloads0, SerializableLoad0, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(SerializableLoad1, Serializable, Load, 1, 2);

static bool SerializableSave(const Serializable* self, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    return self->Save(*file);
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(SerializableLoadXML, Serializable, LoadXML, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(SerializableLoadJSON, Serializable, LoadJSON, 1, 2);

void RegisterSerializable(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Serializable : Object
    lua["Serializable"].setClass(UserdataMetatable<Serializable, Object>()

        .addOverloadedFunctions("Load", 
            // [Method] bool Load(const String& fileName, bool setInstanceDefault = false)
            SerializableLoadOverloads0(),
            // [Method] bool Load(Deserializer& source, bool setInstanceDefault = false)
            SerializableLoad1())

        .addOverloadedFunctions("Save", 
            // [Method] bool Save(const String& fileName)
            &SerializableSave, 
            // [Method] bool Save(Serializer& dest) const
            &Serializable::Save)

        // [Method] bool LoadXML(const XMLElement& source, bool setInstanceDefault = false)
        .addFunction("LoadXML", SerializableLoadXML())
        // [Method] bool SaveXML(XMLElement& dest) const
        .addFunction("SaveXML", &Serializable::SaveXML)

        // [Method] bool LoadJSON(const JSONValue& source, bool setInstanceDefault = false)
        .addFunction("LoadJSON", SerializableLoadJSON())
        // [Method] bool SaveJSON(JSONValue& dest) const
        .addFunction("SaveJSON", &Serializable::SaveJSON)

        .addOverloadedFunctions("SetAttribute",
            // [Method] bool SetAttribute(unsigned index, const Variant& value)
            static_cast<bool(Serializable::*)(unsigned, const Variant&)>(&Serializable::SetAttribute),
            // [Method] bool SetAttribute(const String& name, const Variant& value)
            static_cast<bool(Serializable::*)(const String&, const Variant&)>(&Serializable::SetAttribute))

        .addOverloadedFunctions("GetAttribute",
            // [Method] Variant GetAttribute(unsigned index) const
            static_cast<Variant(Serializable::*)(unsigned) const>(&Serializable::GetAttribute),
            // [Method] Variant GetAttribute(const String& name) const
            static_cast<Variant(Serializable::*)(const String&) const>(&Serializable::GetAttribute))

        .addOverloadedFunctions("GetAttributeDefault",
            // [Method] Variant GetAttributeDefault(unsigned index) const
            static_cast<Variant(Serializable::*)(unsigned) const>(&Serializable::GetAttributeDefault),
            // [Method] Variant GetAttributeDefault(const String& name) const
            static_cast<Variant(Serializable::*)(const String&) const>(&Serializable::GetAttributeDefault))

        // [Method] unsigned GetNumAttributes() const
        .addFunction("GetNumAttributes", &Serializable::GetNumAttributes)
        // [Method] unsigned GetNumNetworkAttributes() const
        .addFunction("GetNumNetworkAttributes", &Serializable::GetNumNetworkAttributes)
        );
}
}

