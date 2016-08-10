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
#include "../../Resource/Resource.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static bool ResourceLoad(Resource* self, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return self->Load(*file);
}

static bool ResourceSave(const Resource* self, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->Save(*file);
}

void RegisterResource(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] AsyncLoadState
    lua["ASYNC_DONE"] = ASYNC_DONE;
    lua["ASYNC_QUEUED"] = ASYNC_QUEUED;
    lua["ASYNC_LOADING"] = ASYNC_LOADING;
    lua["ASYNC_SUCCESS"] = ASYNC_SUCCESS;
    lua["ASYNC_FAIL"] = ASYNC_FAIL;

    // [Class] Resource : Object
    lua["Resource"].setClass(UserdataMetatable<Resource, Object>()
        // [Constructor] Resource()
        .addStaticFunction("new", &CreateObject<Resource>)

        .addOverloadedFunctions("Load", 
            // [Method] bool Load(const String& fileName)
            &ResourceLoad, 
            // [Method] bool Load(Deserializer& source)
            &Resource::Load)

        .addOverloadedFunctions("Save", 
            // [Method] bool Save(const String& fileName) const
            &ResourceSave, 
            // [Method] bool Save(Serializer& dest) const
            &Resource::Save)

        // [Method] void SetName(const String& name)
        .addFunction("SetName", &Resource::SetName)
        // [Method] void SetMemoryUse(unsigned size)
        .addFunction("SetMemoryUse", &Resource::SetMemoryUse)
        // [Method] void ResetUseTimer()
        .addFunction("ResetUseTimer", &Resource::ResetUseTimer)
        // [Method] void SetAsyncLoadState(AsyncLoadState newState)
        .addFunction("SetAsyncLoadState", &Resource::SetAsyncLoadState)

        // [Method] const String& GetName() const
        .addFunction("GetName", &Resource::GetName)
        // [Method] StringHash GetNameHash() const
        .addFunction("GetNameHash", &Resource::GetNameHash)
        // [Method] unsigned GetMemoryUse() const
        .addFunction("GetMemoryUse", &Resource::GetMemoryUse)
        // [Method] unsigned GetUseTimer()
        .addFunction("GetUseTimer", &Resource::GetUseTimer)
        // [Method] AsyncLoadState GetAsyncLoadState() const
        .addFunction("GetAsyncLoadState", &Resource::GetAsyncLoadState)

        // [Property] const String& name
        .addProperty("name", &Resource::GetName, &Resource::SetName)
        // [Property(Readonly)] StringHash nameHash
        .addProperty("nameHash", &Resource::GetNameHash)
        // [Property] unsigned memoryUse
        .addProperty("memoryUse", &Resource::GetMemoryUse, &Resource::SetMemoryUse)
        // [Property(Readonly)] unsigned useTimer
        .addProperty("useTimer", &Resource::GetUseTimer)
        // [Property] AsyncLoadState asyncLoadState
        .addProperty("asyncLoadState", &Resource::GetAsyncLoadState, &Resource::SetAsyncLoadState)
    );
}
}

