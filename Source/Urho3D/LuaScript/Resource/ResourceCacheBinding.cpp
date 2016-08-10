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

    // [Constant] bool AddResourceDir(String& pathName, unsigned priority
    lua["PRIORITY_LAST"] = PRIORITY_LAST;

    // [Enum] ResourceRequest
    lua["RESOURCE_CHECKEXISTS"] = RESOURCE_CHECKEXISTS;
    lua["RESOURCE_GETFILE"] = RESOURCE_GETFILE;

    // [Class] ResourceCache : Object
    lua["ResourceCache"].setClass(UserdataMetatable<ResourceCache, Object>()

        // [Method] bool AddResourceDir(const String& pathName, unsigned priority = PRIORITY_LAST)
        .addFunction("AddResourceDir", ResourceCacheAddResourceDir())
        
        .addOverloadedFunctions("AddPackageFile", 
            // [Method] bool AddPackageFile(PackageFile* package, unsigned priority = PRIORITY_LAST)
            ResourceCacheAddPackageFile0(), 
            // [Method] bool AddPackageFile(const String& fileName, unsigned priority = PRIORITY_LAST)
            ResourceCacheAddPackageFile1())

        // [Method] bool AddManualResource(Resource* resource)
        .addFunction("AddManualResource", &ResourceCache::AddManualResource)
        // [Method] void RemoveResourceDir(const String& pathName)
        .addFunction("RemoveResourceDir", &ResourceCache::RemoveResourceDir)

        .addOverloadedFunctions("RemovePackageFile",
            // [Method] void RemovePackageFile(PackageFile* package, bool releaseResources = true, bool forceRelease = false)
            ResourceCacheRemovePackageFile0(),
            // [Method] void RemovePackageFile(const String& fileName, bool releaseResources = true, bool forceRelease = false)
            ResourceCacheRemovePackageFile1())

        // [Method] void ReleaseResource(StringHash type, const String& name, bool force = false)
        .addFunction("ReleaseResource", ResourceCacheReleaseResource())
        
        .addOverloadedFunctions("ReleaseResources",
            // [Method] void ReleaseResources(StringHash type, bool force = false)
            ResourceCacheReleaseResources0(),
            // [Method] void ReleaseResources(StringHash type, const String& partialName, bool force = false)
            ResourceCacheReleaseResources1(),
            // [Method] void ReleaseResources(const String& partialName, bool force = false)
            ResourceCacheReleaseResources2())

        // [Method] void ReleaseAllResources(bool force = false)
        .addFunction("ReleaseAllResources", ResourceCacheReleaseAllResources())

        // [Method] bool ReloadResource(Resource* resource)
        .addFunction("ReloadResource", &ResourceCache::ReloadResource)
        // [Method] void ReloadResourceWithDependencies(const String& fileName)
        .addFunction("ReloadResourceWithDependencies", &ResourceCache::ReloadResourceWithDependencies)
        // [Method] void SetMemoryBudget(StringHash type, unsigned long long budget)
        .addFunction("SetMemoryBudget", &ResourceCache::SetMemoryBudget)
        // [Method] void SetAutoReloadResources(bool enable)
        .addFunction("SetAutoReloadResources", &ResourceCache::SetAutoReloadResources)
        // [Method] void SetReturnFailedResources(bool enable)
        .addFunction("SetReturnFailedResources", &ResourceCache::SetReturnFailedResources)
        // [Method] void SetSearchPackagesFirst(bool value)
        .addFunction("SetSearchPackagesFirst", &ResourceCache::SetSearchPackagesFirst)
        // [Method] void SetFinishBackgroundResourcesMs(int ms)
        .addFunction("SetFinishBackgroundResourcesMs", &ResourceCache::SetFinishBackgroundResourcesMs)

        // [Method] SharedPtr<File> GetFile(const String& name, bool sendEventOnFailure = true)
        .addFunction("GetFile", ResourceCacheGetFile())

        // [Method] SharedPtr<Resource> GetResource(StringHash type, const String& name, bool sendEventOnFailure = true)
        .addStaticFunction("GetResource", ResourceCacheGetResourceOverloads())
        // [Method] SharedPtr<Resource> GetTempResource(StringHash type, const String& name, bool sendEventOnFailure = true)
        .addStaticFunction("GetTempResource", ResourceCacheGetTempResourceOverloads())

        // [Method] PODVector<Resource*> GetResources(StringHash type)
        .addStaticFunction("GetResources", &ResourceCacheGetResources)
        // [Method] SharedPtr<Resource> GetExistingResource(StringHash type, const String& name)
        .addStaticFunction("GetExistingResource", &ResourceCacheGetExistingResource)

        // [Method] const Vector<String>& GetResourceDirs() const
        .addFunction("GetResourceDirs", &ResourceCache::GetResourceDirs)
        // [Method] const Vector<SharedPtr<PackageFile> >& GetPackageFiles() const
        .addFunction("GetPackageFiles", &ResourceCache::GetPackageFiles)

        // [Method] bool Exists(const String& name) const
        .addFunction("Exists", &ResourceCache::Exists)
        // [Method] unsigned long long GetMemoryBudget(StringHash type) const
        .addFunction("GetMemoryBudget", &ResourceCache::GetMemoryBudget)
        // [Method] unsigned long long GetMemoryUse(StringHash type) const
        .addFunction("GetMemoryUse", &ResourceCache::GetMemoryUse)
        // [Method] unsigned long long GetTotalMemoryUse() const
        .addFunction("GetTotalMemoryUse", &ResourceCache::GetTotalMemoryUse)
        // [Method] String GetResourceFileName(const String& name) const
        .addFunction("GetResourceFileName", &ResourceCache::GetResourceFileName)

        // [Method] bool GetAutoReloadResources() const
        .addFunction("GetAutoReloadResources", &ResourceCache::GetAutoReloadResources)
        // [Method] bool GetReturnFailedResources() const
        .addFunction("GetReturnFailedResources", &ResourceCache::GetReturnFailedResources)
        // [Method] bool GetSearchPackagesFirst() const
        .addFunction("GetSearchPackagesFirst", &ResourceCache::GetSearchPackagesFirst)
        // [Method] String GetPreferredResourceDir(const String& path) const
        .addFunction("GetPreferredResourceDir", &ResourceCache::GetPreferredResourceDir)
        // [Method] String SanitateResourceName(const String& name) const
        .addFunction("SanitateResourceName", &ResourceCache::SanitateResourceName)

        // [Method] String SanitateResourceDirName(const String& name) const
        .addFunction("SanitateResourceDirName", &ResourceCache::SanitateResourceDirName)
        // [Method] void StoreResourceDependency(Resource* resource, const String& dependency)
        .addFunction("StoreResourceDependency", &ResourceCache::StoreResourceDependency)
        // [Method] void ResetDependencies(Resource* resource)
        .addFunction("ResetDependencies", &ResourceCache::ResetDependencies)
        // [Method] String PrintMemoryUsage() const
        .addFunction("PrintMemoryUsage", &ResourceCache::PrintMemoryUsage)

        // [Property(Readonly)] unsigned long long totalMemoryUse
        .addProperty("totalMemoryUse", &ResourceCache::GetTotalMemoryUse)
        // [Property] bool autoReloadResources
        .addProperty("autoReloadResources", &ResourceCache::GetAutoReloadResources, &ResourceCache::SetAutoReloadResources)
        // [Property] bool returnFailedResources
        .addProperty("returnFailedResources", &ResourceCache::GetReturnFailedResources, &ResourceCache::SetReturnFailedResources)
        // [Property] bool searchPackagesFirst
        .addProperty("searchPackagesFirst", &ResourceCache::GetSearchPackagesFirst, &ResourceCache::SetSearchPackagesFirst)
    );
}
}

