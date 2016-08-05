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

#include "../Precompiled.h"

#include "../Resource/Localization.h"
#include "../Resource/ResourceCache.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern void RegisterResource(kaguya::State& lua);
extern void RegisterImage(kaguya::State& lua);
extern void RegisterJSONFile(kaguya::State& lua);
extern void RegisterJSONValue(kaguya::State& lua);
extern void RegisterLocalization(kaguya::State& lua);
extern void RegisterPListFile(kaguya::State& lua);
extern void RegisterResourceCache(kaguya::State& lua);
extern void RegisterResourceEvents(kaguya::State& lua);
extern void RegisterXMLElement(kaguya::State& lua);
extern void RegisterXMLFile(kaguya::State& lua);

void RegisterResourceLuaAPI(kaguya::State& lua)
{
    RegisterResource(lua);

    RegisterImage(lua);
    RegisterJSONFile(lua);
    RegisterJSONValue(lua);
    RegisterLocalization(lua);
    // RegisterPListFile(lua);
    RegisterResourceCache(lua);
    RegisterResourceEvents(lua);
    RegisterXMLElement(lua);
    RegisterXMLFile(lua);

    lua["cache"] = GetSubsystem<ResourceCache>();
    lua["GetCache"] = GetSubsystem<ResourceCache>;

    lua["localization"] = GetSubsystem<Localization>();
    lua["GetLocalization"] = GetSubsystem<Localization>;
}
}
