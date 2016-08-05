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

    // enum AsyncLoadState;
    lua["ASYNC_DONE"] = ASYNC_DONE;
    lua["ASYNC_QUEUED"] = ASYNC_QUEUED;
    lua["ASYNC_LOADING"] = ASYNC_LOADING;
    lua["ASYNC_SUCCESS"] = ASYNC_SUCCESS;
    lua["ASYNC_FAIL"] = ASYNC_FAIL;

    lua["Resource"].setClass(UserdataMetatable<Resource, Object>()
        .addStaticFunction("new", &CreateObject<Resource>)

        .addOverloadedFunctions("Load", 
            &ResourceLoad, 
            &Resource::Load)

        .addOverloadedFunctions("Save", 
            &ResourceSave, 
            &Resource::Save)

        .addFunction("SetName", &Resource::SetName)
        .addFunction("SetMemoryUse", &Resource::SetMemoryUse)
        .addFunction("ResetUseTimer", &Resource::ResetUseTimer)
        .addFunction("SetAsyncLoadState", &Resource::SetAsyncLoadState)

        .addFunction("GetName", &Resource::GetName)
        .addFunction("GetNameHash", &Resource::GetNameHash)
        .addFunction("GetMemoryUse", &Resource::GetMemoryUse)
        .addFunction("GetUseTimer", &Resource::GetUseTimer)
        .addFunction("GetAsyncLoadState", &Resource::GetAsyncLoadState)

        .addProperty("name", &Resource::GetName, &Resource::SetName)
        .addProperty("nameHash", &Resource::GetNameHash)
        .addProperty("memoryUse", &Resource::GetMemoryUse, &Resource::SetMemoryUse)
        .addProperty("useTimer", &Resource::GetUseTimer)
        .addProperty("asyncLoadState", &Resource::GetAsyncLoadState, &Resource::SetAsyncLoadState)
    );
}
}

