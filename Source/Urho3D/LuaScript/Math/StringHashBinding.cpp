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

#include "../../Math/StringHash.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterStringHash(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] StringHash
    lua["StringHash"].setClass(UserdataMetatable<StringHash>()
        // [Constructor] StringHash()
        .setConstructors<StringHash(),
        // [Constructor] StringHash(const StringHash& rhs)
        StringHash(const StringHash&),
        // [Constructor] StringHash(unsigned value)
        StringHash(unsigned),
        // [Constructor] StringHash(const char* str)
        StringHash(const char*)>()

        // [Method] StringHash operator +(const StringHash& rhs) const
        .addFunction("__add", &StringHash::operator+)
        // [Method] bool operator ==(const StringHash& rhs) const
        .addFunction("__eq", &StringHash::operator==)

        // [Method] bool operator <(const StringHash& rhs) const
        .addFunction("__less", &StringHash::operator<)

        // [Method] unsigned Value() const
        .addFunction("Value", &StringHash::Value)

        // [Method] String ToString() const
        .addFunction("ToString", &StringHash::ToString)
        // [Method] unsigned ToHash() const
        .addFunction("ToHash", &StringHash::ToHash)

        // [StaticMethod] static unsigned Calculate(const char* str)
        .addStaticFunction("Calculate", &StringHash::Calculate)

        // [Property(Readonly)] unsigned value
        .addProperty("value", &StringHash::Value)

        // [StaticConstant] StringHash ZERO
        .addStaticField("ZERO", &StringHash::ZERO)
        );
}
}

