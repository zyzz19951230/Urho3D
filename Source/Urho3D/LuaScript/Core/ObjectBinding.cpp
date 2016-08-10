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

#include "../../Core/Object.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterObject(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Object : RefCounted
	lua["Object"].setClass(UserdataMetatable<Object, RefCounted>()

        // [Method] StringHash GetType() const
		.addFunction("GetType", &Object::GetType)
        // [Method] const String& GetTypeName() const
		.addFunction("GetTypeName", &Object::GetTypeName)
        // [Method] const String& GetCategory() const
		.addFunction("GetCategory", &Object::GetCategory)

		.addOverloadedFunctions("SendEvent",
            // [Method] void SendEvent(StringHash eventType)
			static_cast<void(Object::*)(StringHash)>(&Object::SendEvent),
            // [Method] void SendEvent(StringHash eventType, VariantMap& eventData)
			static_cast<void(Object::*)(StringHash, VariantMap&)>(&Object::SendEvent))

		.addOverloadedFunctions("HasSubscribedToEvent",
            // [Method] bool HasSubscribedToEvent(StringHash eventType) const
			static_cast<bool(Object::*)(StringHash)const>(&Object::HasSubscribedToEvent),
            // [Method] bool HasSubscribedToEvent(Object* sender, StringHash eventType) const
			static_cast<bool(Object::*)(Object*, StringHash)const>(&Object::HasSubscribedToEvent))

        // [Property(ReadOnly)] StringHash type
        .addProperty("type", &Object::GetType)
        // [Property(ReadOnly)] const String& typeName
        .addProperty("typeName", &Object::GetTypeName)
        // [Property(ReadOnly)] const String& category
        .addProperty("category", &Object::GetCategory)
    );
}
}

