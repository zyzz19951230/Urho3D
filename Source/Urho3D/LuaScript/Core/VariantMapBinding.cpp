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
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static const Variant& VariantMapGetVariant(const VariantMap& variantMap, StringHash key)
{
    VariantMap::ConstIterator i = variantMap.Find(key);
    if (i == variantMap.End())
        return Variant::EMPTY;

    return i->second_;
}

static void VariantMapSetVariant(VariantMap& variantMap, StringHash key, const Variant& value)
{
    variantMap[key] = value;
}

void RegisterVariantMap(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] VariantMap
    lua["VariantMap"].setClass(UserdataMetatable<VariantMap>()
        // [Constructor] VariantMap()
        .setConstructors<VariantMap()>()

        // [Method] const Variant& __index(StringHash key)
        .addStaticFunction("__index", &VariantMapGetVariant)
        // [Method] void __newindex(StringHash key, const Variant& value)
        .addStaticFunction("__newindex", &VariantMapSetVariant)
        );
}
}

