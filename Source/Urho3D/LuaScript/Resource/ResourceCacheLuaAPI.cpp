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

#include "../../IO/PackageFile.h"
#include "../../Resource/ResourceCache.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ResourceCacheAddResourceDir, ResourceCache, AddResourceDir, 1, 2);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ResourceCacheAddPackageFile0, ResourceCache, AddPackageFile, 1, 2, bool(ResourceCache::*)(PackageFile*, unsigned));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ResourceCacheAddPackageFile1, ResourceCache, AddPackageFile, 1, 2, bool(ResourceCache::*)(const String&, unsigned));

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ResourceCacheRemovePackageFile0, ResourceCache, RemovePackageFile, 1, 3, void(ResourceCache::*)(PackageFile*, bool, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ResourceCacheRemovePackageFile1, ResourceCache, RemovePackageFile, 1, 3, void(ResourceCache::*)(const String&, bool, bool));

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ResourceCacheReleaseResource, ResourceCache, ReleaseResource, 2, 3, void(ResourceCache::*)(StringHash, const String&, bool));

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ResourceCacheReleaseResources0, ResourceCache, ReleaseResources, 1, 2, void(ResourceCache::*)(StringHash, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ResourceCacheReleaseResources1, ResourceCache, ReleaseResources, 2, 3, void(ResourceCache::*)(StringHash, const String&, bool));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ResourceCacheReleaseResources2, ResourceCache, ReleaseResources, 1, 2, void(ResourceCache::*)(const String&, bool));

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ResourceCacheReleaseAllResources, ResourceCache, ReleaseAllResources, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(ResourceCacheGetFile, ResourceCache, GetFile, 1, 2);

static SharedPtr<Resource> ResourceCacheGetResource(ResourceCache* cache, StringHash type, const String& name, bool sendEventOnFailure = true)
{
    return SharedPtr<Resource>(cache->GetResource(type, name, sendEventOnFailure));
}

KAGUYA_FUNCTION_OVERLOADS(ResourceCacheGetResourceOverloads, ResourceCacheGetResource, 3, 4);

static SharedPtr<Resource> ResourceCacheGetTempResource(ResourceCache* cache, StringHash type, const String& name, bool sendEventOnFailure = true)
{
    return SharedPtr<Resource>(cache->GetTempResource(type, name, sendEventOnFailure));
}

KAGUYA_FUNCTION_OVERLOADS(ResourceCacheGetTempResourceOverloads, ResourceCacheGetTempResource, 3, 4);

static PODVector<Resource*> ResourceCacheGetResources(const ResourceCache* self, StringHash type)
{
    PODVector<Resource*> dest;
    self->GetResources(dest, type);
    return dest;
}

static SharedPtr<Resource> ResourceCacheGetExistingResource(ResourceCache* cache, StringHash type, const String& name)
{
    return SharedPtr<Resource>(cache->GetExistingResource(type, name));
}

void RegisterResourceCache(kaguya::State& lua)
{
    using namespace kaguya;

    lua["PRIORITY_LAST"] = PRIORITY_LAST;

    // enum ResourceRequest;
    lua["RESOURCE_CHECKEXISTS"] = RESOURCE_CHECKEXISTS;
    lua["RESOURCE_GETFILE"] = RESOURCE_GETFILE;

    lua["ResourceCache"].setClass(UserdataMetatable<ResourceCache, Object>()

        .addFunction("AddResourceDir", ResourceCacheAddResourceDir())
        
        .addOverloadedFunctions("AddPackageFile", 
            ResourceCacheAddPackageFile0(), 
            ResourceCacheAddPackageFile1())

        .addFunction("AddManualResource", &ResourceCache::AddManualResource)
        .addFunction("RemoveResourceDir", &ResourceCache::RemoveResourceDir)

        .addOverloadedFunctions("RemovePackageFile",
            ResourceCacheRemovePackageFile0(),
            ResourceCacheRemovePackageFile1())

        .addFunction("ReleaseResource", ResourceCacheReleaseResource())
        
        .addOverloadedFunctions("ReleaseResources",
            ResourceCacheReleaseResources0(),
            ResourceCacheReleaseResources1(),
            ResourceCacheReleaseResources2())

        .addFunction("ReleaseAllResources", ResourceCacheReleaseAllResources())

        .addFunction("ReloadResource", &ResourceCache::ReloadResource)
        .addFunction("ReloadResourceWithDependencies", &ResourceCache::ReloadResourceWithDependencies)
        .addFunction("SetMemoryBudget", &ResourceCache::SetMemoryBudget)
        .addFunction("SetAutoReloadResources", &ResourceCache::SetAutoReloadResources)
        .addFunction("SetReturnFailedResources", &ResourceCache::SetReturnFailedResources)
        .addFunction("SetSearchPackagesFirst", &ResourceCache::SetSearchPackagesFirst)
        .addFunction("SetFinishBackgroundResourcesMs", &ResourceCache::SetFinishBackgroundResourcesMs)

        .addFunction("GetFile", ResourceCacheGetFile())

        .addStaticFunction("GetResource", ResourceCacheGetResourceOverloads())
        .addStaticFunction("GetTempResource", ResourceCacheGetTempResourceOverloads())

        .addStaticFunction("GetResources", &ResourceCacheGetResources)
        .addStaticFunction("GetExistingResource", &ResourceCacheGetExistingResource)

        .addFunction("GetResourceDirs", &ResourceCache::GetResourceDirs)
        .addFunction("GetPackageFiles", &ResourceCache::GetPackageFiles)

        .addFunction("Exists", &ResourceCache::Exists)
        .addFunction("GetMemoryBudget", &ResourceCache::GetMemoryBudget)
        .addFunction("GetMemoryUse", &ResourceCache::GetMemoryUse)
        .addFunction("GetTotalMemoryUse", &ResourceCache::GetTotalMemoryUse)
        .addFunction("GetResourceFileName", &ResourceCache::GetResourceFileName)

        .addFunction("GetAutoReloadResources", &ResourceCache::GetAutoReloadResources)
        .addFunction("GetReturnFailedResources", &ResourceCache::GetReturnFailedResources)
        .addFunction("GetSearchPackagesFirst", &ResourceCache::GetSearchPackagesFirst)
        .addFunction("GetPreferredResourceDir", &ResourceCache::GetPreferredResourceDir)
        .addFunction("SanitateResourceName", &ResourceCache::SanitateResourceName)

        .addFunction("SanitateResourceDirName", &ResourceCache::SanitateResourceDirName)
        .addFunction("StoreResourceDependency", &ResourceCache::StoreResourceDependency)
        .addFunction("ResetDependencies", &ResourceCache::ResetDependencies)
        .addFunction("PrintMemoryUsage", &ResourceCache::PrintMemoryUsage)

        .addProperty("totalMemoryUse", &ResourceCache::GetTotalMemoryUse)
        .addProperty("autoReloadResources", &ResourceCache::GetAutoReloadResources, &ResourceCache::SetAutoReloadResources)
        .addProperty("returnFailedResources", &ResourceCache::GetReturnFailedResources, &ResourceCache::SetReturnFailedResources)
        .addProperty("searchPackagesFirst", &ResourceCache::GetSearchPackagesFirst, &ResourceCache::SetSearchPackagesFirst)
    );
}
}

