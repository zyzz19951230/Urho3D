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

#include "../Core/Context.h"
#include "../IO/File.h"
#include "../IO/PackageFile.h"
#include "../LuaScript/LuaScriptUtils.h"
#include "../Resource/BackgroundLoader.h"
#include "../Resource/Decompress.h"
#include "../Resource/Image.h"
#include "../Resource/JSONFile.h"
#include "../Resource/JSONValue.h"
#include "../Resource/Localization.h"
#include "../Resource/PListFile.h"
#include "../Resource/Resource.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"
#include "../Resource/XMLElement.h"
#include "../Resource/XMLFile.h"

#include <kaguya.hpp>

namespace Urho3D
{

static SharedPtr<Image> ImageGetSubimage(const Image* self, const IntRect& rect)
{
    return SharedPtr<Image>(self->GetSubimage(rect));
}

static void RegisterImage(kaguya::State& lua)
{
    using namespace kaguya;

    // enum CompressedFormat;
    lua["CF_NONE"] = CF_NONE;
    lua["CF_RGBA"] = CF_RGBA;
    lua["CF_DXT1"] = CF_DXT1;
    lua["CF_DXT3"] = CF_DXT3;
    lua["CF_DXT5"] = CF_DXT5;
    lua["CF_ETC1"] = CF_ETC1;
    lua["CF_PVRTC_RGB_2BPP"] = CF_PVRTC_RGB_2BPP;
    lua["CF_PVRTC_RGBA_2BPP"] = CF_PVRTC_RGBA_2BPP;
    lua["CF_PVRTC_RGB_4BPP"] = CF_PVRTC_RGB_4BPP;
    lua["CF_PVRTC_RGBA_4BPP"] = CF_PVRTC_RGBA_4BPP;

    lua["Image"].setClass(UserdataMetatable<Image, Resource>()
        .addStaticFunction("new", &CreateObject<Image>)

        .addOverloadedFunctions("SetSize",
            static_cast<bool(Image::*)(int, int, unsigned)>(&Image::SetSize),
            static_cast<bool(Image::*)(int, int, int, unsigned)>(&Image::SetSize))

        .addOverloadedFunctions("SetPixel",
            static_cast<void(Image::*)(int, int, const Color&)>(&Image::SetPixel),
            static_cast<void(Image::*)(int, int, int, const Color&)>(&Image::SetPixel))

        .addOverloadedFunctions("SetPixelInt",
            static_cast<void(Image::*)(int, int, unsigned)>(&Image::SetPixelInt),
            static_cast<void(Image::*)(int, int, int, unsigned)>(&Image::SetPixelInt))

        .addFunction("FlipHorizontal", &Image::FlipHorizontal)
        .addFunction("FlipVertical", &Image::FlipVertical)
        .addFunction("Resize", &Image::Resize)
        .addFunction("Clear", &Image::Clear)
        .addFunction("ClearInt", &Image::ClearInt)
        .addFunction("SaveBMP", &Image::SaveBMP)
        .addFunction("SavePNG", &Image::SavePNG)
        .addFunction("SaveTGA", &Image::SaveTGA)
        .addFunction("SaveJPG", &Image::SaveJPG)
        .addFunction("IsCubemap", &Image::IsCubemap)
        .addFunction("IsArray", &Image::IsArray)
        .addFunction("IsSRGB", &Image::IsSRGB)

        .addOverloadedFunctions("GetPixel",
            static_cast<Color(Image::*)(int, int) const>(&Image::GetPixel),
            static_cast<Color(Image::*)(int, int, int) const>(&Image::GetPixel))

        .addOverloadedFunctions("GetPixelInt",
            static_cast<unsigned(Image::*)(int, int) const>(&Image::GetPixelInt),
            static_cast<unsigned(Image::*)(int, int, int) const>(&Image::GetPixelInt))

        .addFunction("GetPixelBilinear", &Image::GetPixelBilinear)
        .addFunction("GetPixelTrilinear", &Image::GetPixelTrilinear)
        .addFunction("GetWidth", &Image::GetWidth)
        .addFunction("GetHeight", &Image::GetHeight)
        .addFunction("GetDepth", &Image::GetDepth)
        .addFunction("GetComponents", &Image::GetComponents)

        .addFunction("IsCompressed", &Image::IsCompressed)
        .addFunction("GetCompressedFormat", &Image::GetCompressedFormat)
        .addFunction("GetNumCompressedLevels", &Image::GetNumCompressedLevels)

        .addFunction("GetNextLevel", &Image::GetNextLevel)
        .addFunction("GetNextSibling", &Image::GetNextSibling)
        .addFunction("ConvertToRGBA", &Image::ConvertToRGBA)

        .addFunction("GetCompressedLevel", &Image::GetCompressedLevel)

        .addStaticFunction("GetSubimage", &ImageGetSubimage)

        .addProperty("cubemap", &Image::IsCubemap)
        .addProperty("array", &Image::IsArray)
        .addProperty("SRGB", &Image::IsSRGB)
        .addProperty("width", &Image::GetWidth)
        .addProperty("height", &Image::GetHeight)
        .addProperty("depth", &Image::GetDepth)
        .addProperty("components", &Image::GetComponents)
        .addProperty("data", &Image::GetData, &Image::SetData)
        .addProperty("compressed", &Image::IsCompressed)
        .addProperty("compressedFormat", &Image::GetCompressedFormat)
        .addProperty("numCompressedLevels", &Image::GetNumCompressedLevels)
        .addProperty("nextLevel", &Image::GetNextLevel)
        .addProperty("nextSibling", &Image::GetNextSibling)
    );
}

static bool JSONFileSave(const JSONFile* self, const char* filepath, const String& indentation)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->Save(*file, indentation);
}

static void RegisterJSONFile(kaguya::State& lua)
{
    using namespace kaguya;

    lua["JSONFile"].setClass(UserdataMetatable<JSONFile, Resource>()
        .addStaticFunction("new", &CreateObject<JSONFile>)

        .addStaticFunction("Save", &JSONFileSave)
        .addFunction("FromString", &JSONFile::FromString)
        .addFunction("CreateRoot", static_cast<JSONValue&(JSONFile::*)()>(&JSONFile::GetRoot))
        .addFunction("GetRoot", static_cast<const JSONValue&(JSONFile::*)() const>(&JSONFile::GetRoot))
        .addProperty("root", static_cast<const JSONValue&(JSONFile::*)() const>(&JSONFile::GetRoot))
    );
}

static void RegisterJSONValue(kaguya::State& lua)
{
    using namespace kaguya;

    // enum JSONValueType;
    lua["JSON_NULL"] = JSON_NULL;
    lua["JSON_BOOL"] = JSON_BOOL;
    lua["JSON_NUMBER"] = JSON_NUMBER;
    lua["JSON_STRING"] = JSON_STRING;
    lua["JSON_ARRAY"] = JSON_ARRAY;
    lua["JSON_OBJECT"] = JSON_OBJECT;

    // enum JSONNumberType;
    lua["JSONNT_NAN"] = JSONNT_NAN;
    lua["JSONNT_INT"] = JSONNT_INT;
    lua["JSONNT_UINT"] = JSONNT_UINT;
    lua["JSONNT_FLOAT_DOUBLE"] = JSONNT_FLOAT_DOUBLE;

    lua["JSONValue"].setClass(UserdataMetatable<JSONValue>()
        .setConstructors<JSONValue(),
        JSONValue(bool),
        JSONValue(int),
        JSONValue(unsigned),
        JSONValue(float),
        JSONValue(double),
        JSONValue(const char*),
        JSONValue(const JSONValue&)>()

        .addFunction("GetValueType", &JSONValue::GetValueType)
        .addFunction("GetNumberType", &JSONValue::GetNumberType)

        .addFunction("IsNull", &JSONValue::IsNull)
        .addFunction("IsBool", &JSONValue::IsBool)
        .addFunction("IsNumber", &JSONValue::IsNumber)
        .addFunction("IsString", &JSONValue::IsString)
        .addFunction("IsArray", &JSONValue::IsArray)
        .addFunction("IsObject", &JSONValue::IsObject)

        .addStaticFunction("SetBool", [](JSONValue& jsonValue, bool value) { jsonValue = value; })
        .addStaticFunction("SetInt", [](JSONValue& jsonValue, int value) { jsonValue = value; })
        .addStaticFunction("SetUInt", [](JSONValue& jsonValue, unsigned value) { jsonValue = value; })
        .addStaticFunction("SetFloat", [](JSONValue& jsonValue, float value) { jsonValue = value; })
        .addStaticFunction("SetDouble", [](JSONValue& jsonValue, double value) { jsonValue = value; })
        .addStaticFunction("SetString", [](JSONValue& jsonValue, const char* value) { jsonValue = value; })
        .addStaticFunction("SetArray", [](JSONValue& jsonValue, const JSONArray& value) { jsonValue = value; })
        .addStaticFunction("SetObject", [](JSONValue& jsonValue, const JSONObject& value) { jsonValue = value; })

        .addFunction("GetBool", &JSONValue::GetBool)
        .addFunction("GetInt", &JSONValue::GetInt)
        .addFunction("GetUInt", &JSONValue::GetUInt)
        .addFunction("GetFloat", &JSONValue::GetFloat)
        .addFunction("GetDouble", &JSONValue::GetDouble)
        .addFunction("GetString", &JSONValue::GetCString)
        .addFunction("GetArray", &JSONValue::GetArray)
        .addFunction("GetObject", &JSONValue::GetObject)

        .addOverloadedFunctions("__index",
            static_cast<const JSONValue&(JSONValue::*)(unsigned) const>(&JSONValue::operator[]),
            static_cast<const JSONValue&(JSONValue::*)(const String&) const>(&JSONValue::operator[]))

        .addOverloadedFunctions("__newindex",
            static_cast<JSONValue&(JSONValue::*)(unsigned)>(&JSONValue::operator[]),
            static_cast<JSONValue&(JSONValue::*)(const String&)>(&JSONValue::operator[]))

        .addFunction("Push", &JSONValue::Push)
        .addFunction("Pop", &JSONValue::Pop)
        .addFunction("Insert", &JSONValue::Insert)

        .addOverloadedFunctions("Erase",
            static_cast<void(JSONValue::*)(unsigned, unsigned)>(&JSONValue::Erase),
            static_cast<bool(JSONValue::*)(const String&)>(&JSONValue::Erase))

        .addFunction("Resize", &JSONValue::Resize)
        .addFunction("Size", &JSONValue::Size)

        .addFunction("Set", &JSONValue::Set)
        .addFunction("Get", &JSONValue::Get)
        .addFunction("Contains", &JSONValue::Contains)

        .addFunction("Clear", &JSONValue::Clear)

        .addProperty("valueType", &JSONValue::GetValueType)
        .addProperty("numberType", &JSONValue::GetNumberType)

        .addProperty("isNull", &JSONValue::IsNull)
        .addProperty("isBool", &JSONValue::IsBool)
        .addProperty("isNumber", &JSONValue::IsNumber)
        .addProperty("isString", &JSONValue::IsString)
        .addProperty("isArray", &JSONValue::IsArray)
        .addProperty("isObject", &JSONValue::IsObject)

        .addStaticField("EMPTY", &JSONValue::EMPTY)
    );
}

static void RegisterLocalization(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Localization"].setClass(UserdataMetatable<Localization, Object>()

        .addFunction("GetNumLanguages", &Localization::GetNumLanguages)

        .addOverloadedFunctions("GetLanguageIndex",
            static_cast<int(Localization::*)() const>(&Localization::GetLanguageIndex),
            static_cast<int(Localization::*)(const String&)>(&Localization::GetLanguageIndex))

        .addOverloadedFunctions("GetLanguage",
            static_cast<String(Localization::*)()>(&Localization::GetLanguage),
            static_cast<String(Localization::*)(int)>(&Localization::GetLanguage))

        .addOverloadedFunctions("SetLanguage",
            static_cast<void(Localization::*)(int)>(&Localization::SetLanguage),
            static_cast<void(Localization::*)(const String&)>(&Localization::SetLanguage))

        .addFunction("Get", &Localization::Get)
        .addFunction("Reset", &Localization::Reset)
        .addFunction("LoadJSON", &Localization::LoadJSON)
        .addFunction("LoadJSONFile", &Localization::LoadJSONFile)

        .addProperty("numLanguages", &Localization::GetNumLanguages)
    );
}

static void RegisterPListFile(kaguya::State& lua)
{
    using namespace kaguya;

    // enum PListValueType;
    lua["PLVT_NONE"] = PLVT_NONE;
    lua["PLVT_INT"] = PLVT_INT;
    lua["PLVT_BOOL"] = PLVT_BOOL;
    lua["PLVT_FLOAT"] = PLVT_FLOAT;
    lua["PLVT_STRING"] = PLVT_STRING;
    lua["PLVT_VALUEMAP"] = PLVT_VALUEMAP;
    lua["PLVT_VALUEVECTOR"] = PLVT_VALUEVECTOR;

    lua["PListValue"].setClass(UserdataMetatable<PListValue>()
        .setConstructors<PListValue(),
        PListValue(int),
        PListValue(bool),
        PListValue(float),
        PListValue(const String&),
        PListValue(PListValueMap&),
        PListValue(PListValueVector&),
        PListValue(const PListValue&)>()

        .addFunction("SetInt", &PListValue::SetInt)
        .addFunction("SetBool", &PListValue::SetBool)
        .addFunction("SetFloat", &PListValue::SetFloat)
        .addFunction("SetString", &PListValue::SetString)
        .addFunction("SetValueMap", &PListValue::SetValueMap)
        .addFunction("SetValueVector", &PListValue::SetValueVector)

        .addFunction("GetType", &PListValue::GetType)

        .addFunction("GetInt", &PListValue::GetInt)
        .addFunction("GetBool", &PListValue::GetBool)
        .addFunction("GetFloat", &PListValue::GetFloat)
        .addFunction("GetString", &PListValue::GetString)
        .addFunction("GetIntRect", &PListValue::GetIntRect)
        .addFunction("GetIntVector2", &PListValue::GetIntVector2)
        .addFunction("GetValueMap", &PListValue::GetValueMap)
        .addFunction("GetValueVector", &PListValue::GetValueVector)

        .addProperty("type", &PListValue::GetType)
    );

    lua["PListFile"].setClass(UserdataMetatable<PListFile, Resource>()
        .addStaticFunction("new", &CreateObject<PListFile>)

        .addFunction("GetRoot", &PListFile::GetRoot)
        .addProperty("root", &PListFile::GetRoot)
    );
}

static bool ResourceLoad(Resource* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->Load(*file);
}

static bool ResourceSave(const Resource* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->Save(*file);
}

static void RegisterResource(kaguya::State& lua)
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

        .addStaticFunction("Load", &ResourceLoad)
        .addStaticFunction("Save", &ResourceSave)

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

static bool ResourceCacheAddResourceDir0(ResourceCache* self, const String& pathName)
{
    return self->AddResourceDir(pathName);
}

static bool ResourceCacheAddResourceDir1(ResourceCache* self, const String& pathName, unsigned int priority)
{
    return self->AddResourceDir(pathName, priority);
}

static bool ResourceCacheAddPackageFile0(ResourceCache* self, PackageFile* package)
{
    return self->AddPackageFile(package);
}

static bool ResourceCacheAddPackageFile1(ResourceCache* self, PackageFile* package, unsigned int priority)
{
    return self->AddPackageFile(package, priority);
}

static bool ResourceCacheAddPackageFile2(ResourceCache* self, const String& fileName)
{
    return self->AddPackageFile(fileName);
}

static bool ResourceCacheAddPackageFile3(ResourceCache* self, const String& fileName, unsigned int priority)
{
    return self->AddPackageFile(fileName, priority);
}

static void ResourceCacheRemovePackageFile0(ResourceCache* self, PackageFile* package)
{
    self->RemovePackageFile(package);
}

static void ResourceCacheRemovePackageFile1(ResourceCache* self, PackageFile* package, bool releaseResources)
{
    self->RemovePackageFile(package, releaseResources);
}

static void ResourceCacheRemovePackageFile2(ResourceCache* self, PackageFile* package, bool releaseResources, bool forceRelease)
{
    self->RemovePackageFile(package, releaseResources, forceRelease);
}

static void ResourceCacheRemovePackageFile3(ResourceCache* self, const String& fileName)
{
    self->RemovePackageFile(fileName);
}

static void ResourceCacheRemovePackageFile4(ResourceCache* self, const String& fileName, bool releaseResources)
{
    self->RemovePackageFile(fileName, releaseResources);
}

static void ResourceCacheRemovePackageFile5(ResourceCache* self, const String& fileName, bool releaseResources, bool forceRelease)
{
    self->RemovePackageFile(fileName, releaseResources, forceRelease);
}

static void ResourceCacheReleaseResource0(ResourceCache* self, const char* type, const String& name)
{
    self->ReleaseResource(StringHash(type), name);
}

static void ResourceCacheReleaseResource1(ResourceCache* self, const char* type, const String& name, bool force)
{
    self->ReleaseResource(StringHash(type), name, force);
}

static void ResourceCacheReleaseResources0(ResourceCache* self, const char* type)
{
    self->ReleaseResources(StringHash(type));
}

static void ResourceCacheReleaseResources1(ResourceCache* self, const char* type, bool force)
{
    self->ReleaseResources(StringHash(type), force);
}

static void ResourceCacheReleaseResources2(ResourceCache* self, const char* type, const String& partialName)
{
    self->ReleaseResources(StringHash(type), partialName);
}

static void ResourceCacheReleaseResources3(ResourceCache* self, const char* type, const String& partialName, bool force)
{
    self->ReleaseResources(StringHash(type), partialName, force);
}

static void ResourceCacheReleaseAllResources0(ResourceCache* self)
{
    self->ReleaseAllResources();
}

static void ResourceCacheReleaseAllResources1(ResourceCache* self, bool force)
{
    self->ReleaseAllResources(force);
}

static SharedPtr<File> ResourceCacheGetFile0(ResourceCache* self, const String& name)
{
    return self->GetFile(name);
}

static SharedPtr<File> ResourceCacheGetFile1(ResourceCache* self, const String& name, bool sendEventOnFailure)
{
    return self->GetFile(name, sendEventOnFailure);
}

static SharedPtr<Resource> ResourceCacheGetResource0(ResourceCache* cache, const char* type, const char* name)
{
    return SharedPtr<Resource>(cache->GetResource(StringHash(type), String(name)));
}

static SharedPtr<Resource> ResourceCacheGetResource1(ResourceCache* cache, const char* type, const char* name, bool sendEventOnFailure)
{
    return SharedPtr<Resource>(cache->GetResource(StringHash(type), String(name), sendEventOnFailure));
}

static SharedPtr<Resource> ResourceCacheGetTempResource0(ResourceCache* cache, const char* type, const char* name)
{
    return SharedPtr<Resource>(cache->GetTempResource(StringHash(type), String(name)));
}

static SharedPtr<Resource> ResourceCacheGetTempResource1(ResourceCache* cache, const char* type, const char* name, bool sendEventOnFailure)
{
    return SharedPtr<Resource>(cache->GetTempResource(StringHash(type), String(name), sendEventOnFailure));
}

static PODVector<Resource*> ResourceCacheGetResources(const ResourceCache* self, const char* type)
{
    PODVector<Resource*> dest;
    self->GetResources(dest, StringHash(type));
    return dest;
}

static SharedPtr<Resource> ResourceCacheGetExistingResource(ResourceCache* cache, const char* type, const char* name)
{
    return SharedPtr<Resource>(cache->GetExistingResource(StringHash(type), String(name)));
}

static void RegisterResourceCache(kaguya::State& lua)
{
    using namespace kaguya;

    lua["PRIORITY_LAST"] = PRIORITY_LAST;

    // enum ResourceRequest;
    lua["RESOURCE_CHECKEXISTS"] = RESOURCE_CHECKEXISTS;
    lua["RESOURCE_GETFILE"] = RESOURCE_GETFILE;

    lua["ResourceCache"].setClass(UserdataMetatable<ResourceCache, Object>()

        ADD_OVERLOADED_FUNCTIONS_2(ResourceCache, AddResourceDir)
        ADD_OVERLOADED_FUNCTIONS_4(ResourceCache, AddPackageFile)

        .addFunction("AddManualResource", &ResourceCache::AddManualResource)
        .addFunction("RemoveResourceDir", &ResourceCache::RemoveResourceDir)

        ADD_OVERLOADED_FUNCTIONS_6(ResourceCache, RemovePackageFile)
        ADD_OVERLOADED_FUNCTIONS_2(ResourceCache, ReleaseResource)
        ADD_OVERLOADED_FUNCTIONS_4(ResourceCache, ReleaseResources)
        ADD_OVERLOADED_FUNCTIONS_2(ResourceCache, ReleaseAllResources)

        .addFunction("ReloadResource", &ResourceCache::ReloadResource)
        .addFunction("ReloadResourceWithDependencies", &ResourceCache::ReloadResourceWithDependencies)
        .addFunction("SetMemoryBudget", &ResourceCache::SetMemoryBudget)
        .addFunction("SetAutoReloadResources", &ResourceCache::SetAutoReloadResources)
        .addFunction("SetReturnFailedResources", &ResourceCache::SetReturnFailedResources)
        .addFunction("SetSearchPackagesFirst", &ResourceCache::SetSearchPackagesFirst)
        .addFunction("SetFinishBackgroundResourcesMs", &ResourceCache::SetFinishBackgroundResourcesMs)

        ADD_OVERLOADED_FUNCTIONS_2(ResourceCache, GetFile)
        ADD_OVERLOADED_FUNCTIONS_2(ResourceCache, GetResource)
        ADD_OVERLOADED_FUNCTIONS_2(ResourceCache, GetTempResource)

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

static void RegisterResourceEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["E_RELOADSTARTED"] = E_RELOADSTARTED;
    lua["E_RELOADFINISHED"] = E_RELOADFINISHED;
    lua["E_RELOADFAILED"] = E_RELOADFAILED;
    lua["E_FILECHANGED"] = E_FILECHANGED;
    lua["E_LOADFAILED"] = E_LOADFAILED;
    lua["E_RESOURCENOTFOUND"] = E_RESOURCENOTFOUND;
    lua["E_UNKNOWNRESOURCETYPE"] = E_UNKNOWNRESOURCETYPE;
    lua["E_RESOURCEBACKGROUNDLOADED"] = E_RESOURCEBACKGROUNDLOADED;
    lua["E_CHANGELANGUAGE"] = E_CHANGELANGUAGE;
}

static bool XMLElementRemoveChildren0(XMLElement* self)
{
    return self->RemoveChildren();
}

static bool XMLElementRemoveChildren1(XMLElement* self, const String& name)
{
    return self->RemoveChildren(name);
}

static bool XMLElementRemoveAttribute0(XMLElement* self)
{
    return self->RemoveAttribute();
}

static bool XMLElementRemoveAttribute1(XMLElement* self, const String& name)
{
    return self->RemoveAttribute(name);
}

static XMLElement XMLElementGetChild0(const XMLElement* self)
{
    return self->GetChild();
}

static XMLElement XMLElementGetChild1(const XMLElement* self, const String& name)
{
    return self->GetChild(name);
}

static XMLElement XMLElementGetNext0(const XMLElement* self)
{
    return self->GetNext();
}

static XMLElement XMLElementGetNext1(const XMLElement* self, const String& name)
{
    return self->GetNext(name);
}

static String XMLElementGetAttribute0(const XMLElement* self)
{
    return self->GetAttribute();
}

static String XMLElementGetAttribute1(const XMLElement* self, const String& name)
{
    return self->GetAttribute(name);
}

static bool XPathQuerySetQuery0(XPathQuery* self, const String& queryString)
{
    return self->SetQuery(queryString);
}

static bool XPathQuerySetQuery1(XPathQuery* self, const String& queryString, const String& variableString)
{
    return self->SetQuery(queryString, variableString);
}

static bool XPathQuerySetQuery2(XPathQuery* self, const String& queryString, const String& variableString, bool bind)
{
    return self->SetQuery(queryString, variableString, bind);
}

static void RegisterXMLElement(kaguya::State& lua)
{
    using namespace kaguya;

    lua["XMLElement"].setClass(UserdataMetatable<XMLElement>()
        .setConstructors<XMLElement(),
        XMLElement(const XMLElement&)>()

        .addFunction("CreateChild", static_cast<XMLElement(XMLElement::*)(const String&)>(&XMLElement::CreateChild))

        .addOverloadedFunctions("RemoveChild",
            static_cast<bool(XMLElement::*)(const XMLElement&)>(&XMLElement::RemoveChild),
            static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::RemoveChild))

        ADD_OVERLOADED_FUNCTIONS_2(XMLElement, RemoveChildren)
        ADD_OVERLOADED_FUNCTIONS_2(XMLElement, RemoveAttribute)

        .addFunction("SelectSinglePrepared", &XMLElement::SelectSinglePrepared)
        .addFunction("SelectPrepared", &XMLElement::SelectPrepared)

        .addFunction("SetValue", static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::SetValue))

        .addOverloadedFunctions("SetAttribute",
            static_cast<bool(XMLElement::*)(const String&, const String&)>(&XMLElement::SetAttribute),
            static_cast<bool(XMLElement::*)(const String&)>(&XMLElement::SetAttribute))

        .addFunction("SetBool", &XMLElement::SetBool)
        .addFunction("SetBoundingBox", &XMLElement::SetBoundingBox)
        .addFunction("SetColor", &XMLElement::SetColor)
        .addFunction("SetFloat", &XMLElement::SetFloat)
        .addFunction("SetDouble", &XMLElement::SetDouble)
        .addFunction("SetUInt", &XMLElement::SetUInt)
        .addFunction("SetInt", &XMLElement::SetInt)
        .addFunction("SetIntRect", &XMLElement::SetIntRect)
        .addFunction("SetIntVector2", &XMLElement::SetIntVector2)
        .addFunction("SetRect", &XMLElement::SetRect)
        .addFunction("SetQuaternion", &XMLElement::SetQuaternion)
        .addFunction("SetString", &XMLElement::SetString)
        .addFunction("SetVariant", &XMLElement::SetVariant)
        .addFunction("SetVariantValue", &XMLElement::SetVariantValue)
        .addFunction("SetResourceRef", &XMLElement::SetResourceRef)
        .addFunction("SetResourceRefList", &XMLElement::SetResourceRefList)
        .addFunction("SetVariantVector", &XMLElement::SetVariantVector)
        .addFunction("SetStringVector", &XMLElement::SetStringVector)
        .addFunction("SetVariantMap", &XMLElement::SetVariantMap)
        .addFunction("SetVector2", &XMLElement::SetVector2)
        .addFunction("SetVector3", &XMLElement::SetVector3)
        .addFunction("SetVector4", &XMLElement::SetVector4)
        .addFunction("SetVectorVariant", &XMLElement::SetVectorVariant)
        .addFunction("SetMatrix3", &XMLElement::SetMatrix3)
        .addFunction("SetMatrix3x4", &XMLElement::SetMatrix3x4)
        .addFunction("SetMatrix4", &XMLElement::SetMatrix4)

        .addFunction("IsNull", &XMLElement::IsNull)
        .addFunction("NotNull", &XMLElement::NotNull)
        .addFunction("GetName", &XMLElement::GetName)

        .addFunction("HasChild", static_cast<bool(XMLElement::*)(const String&) const>(&XMLElement::HasChild))

        ADD_OVERLOADED_FUNCTIONS_2(XMLElement, GetChild)
        ADD_OVERLOADED_FUNCTIONS_2(XMLElement, GetNext)

        .addFunction("GetParent", &XMLElement::GetParent)
        .addFunction("GetNumAttributes", &XMLElement::GetNumAttributes)
        .addFunction("HasAttribute", static_cast<bool(XMLElement::*)(const String&) const>(&XMLElement::HasAttribute))

        .addFunction("GetValue", &XMLElement::GetValue)

        ADD_OVERLOADED_FUNCTIONS_2(XMLElement, GetAttribute)

        .addFunction("GetAttributeLower", static_cast<String(XMLElement::*)(const String&) const>(&XMLElement::GetAttributeLower))
        .addFunction("GetAttributeUpper", static_cast<String(XMLElement::*)(const String&) const>(&XMLElement::GetAttributeUpper))

        .addFunction("GetAttributeNames", &XMLElement::GetAttributeNames)
        .addFunction("GetBool", &XMLElement::GetBool)

        .addFunction("GetBoundingBox", &XMLElement::GetBoundingBox)
        .addFunction("GetColor", &XMLElement::GetColor)
        .addFunction("GetFloat", &XMLElement::GetFloat)
        .addFunction("GetDouble", &XMLElement::GetDouble)
        .addFunction("GetUInt", &XMLElement::GetUInt)
        .addFunction("GetInt", &XMLElement::GetInt)
        .addFunction("GetIntRect", &XMLElement::GetIntRect)
        .addFunction("GetIntVector2", &XMLElement::GetIntVector2)
        .addFunction("GetRect", &XMLElement::GetRect)
        .addFunction("GetQuaternion", &XMLElement::GetQuaternion)
        .addFunction("GetVariant", &XMLElement::GetVariant)
        .addFunction("GetVariantValue", &XMLElement::GetVariantValue)
        .addFunction("GetResourceRef", &XMLElement::GetResourceRef)
        .addFunction("GetResourceRefList", &XMLElement::GetResourceRefList)
        .addFunction("GetVariantVector", &XMLElement::GetVariantVector)
        .addFunction("GetStringVector", &XMLElement::GetStringVector)
        .addFunction("GetVariantMap", &XMLElement::GetVariantMap)
        .addFunction("GetVector2", &XMLElement::GetVector2)
        .addFunction("GetVector3", &XMLElement::GetVector3)
        .addFunction("GetVector4", &XMLElement::GetVector4)
        .addFunction("GetVector", &XMLElement::GetVector)
        .addFunction("GetVectorVariant", &XMLElement::GetVectorVariant)
        .addFunction("GetMatrix3", &XMLElement::GetMatrix3)
        .addFunction("GetMatrix3x4", &XMLElement::GetMatrix3x4)
        .addFunction("GetMatrix4", &XMLElement::GetMatrix4)
        .addFunction("GetFile", &XMLElement::GetFile)

        .addProperty("null", &XMLElement::IsNull)
        .addProperty("name", &XMLElement::GetName)
        .addProperty("parent", &XMLElement::GetParent)
        .addProperty("numAttributes", &XMLElement::GetNumAttributes)
        .addProperty("value", &XMLElement::GetValue)

        .addStaticField("EMPTY", &XMLElement::EMPTY)
    );

    lua["XPathResultSet"].setClass(UserdataMetatable<XPathResultSet>()
        .setConstructors<XPathResultSet(),
        XPathResultSet(const XPathResultSet&)>()

        .addFunction("__index", &XPathResultSet::operator[])

        .addFunction("FirstResult", &XPathResultSet::FirstResult)
        .addFunction("Size", &XPathResultSet::Size)
        .addFunction("Empty", &XPathResultSet::Empty)
    );

    lua["XPathQuery"].setClass(UserdataMetatable<XPathQuery>()
        .setConstructors<XPathQuery(),
        XPathQuery(const String&, const String&)>()

        .addFunction("Bind", &XPathQuery::Bind)

        .addOverloadedFunctions("SetVariable",
            static_cast<bool(XPathQuery::*)(const String&, bool)>(&XPathQuery::SetVariable),
            static_cast<bool(XPathQuery::*)(const String&, float)>(&XPathQuery::SetVariable),
            static_cast<bool(XPathQuery::*)(const char*, const char*)>(&XPathQuery::SetVariable),
            static_cast<bool(XPathQuery::*)(const String&, const XPathResultSet&)>(&XPathQuery::SetVariable))

        ADD_OVERLOADED_FUNCTIONS_3(XPathQuery, SetQuery)

        .addFunction("Clear", &XPathQuery::Clear)
        .addFunction("EvaluateToBool", &XPathQuery::EvaluateToBool)
        .addFunction("EvaluateToFloat", &XPathQuery::EvaluateToFloat)
        .addFunction("EvaluateToString", &XPathQuery::EvaluateToString)
        .addFunction("Evaluate", &XPathQuery::Evaluate)
        .addFunction("GetQuery", &XPathQuery::GetQuery)

        .addProperty("query", &XPathQuery::GetQuery)
    );
}

static XMLElement XMLFileGetRoot0(XMLFile* self)
{
    return self->GetRoot();
}

static XMLElement XMLFileGetRoot1(XMLFile* self, const String& name)
{
    return self->GetRoot(name);
}

static String XMLFileToString0(const XMLFile* self)
{
    return self->ToString();
}

static String XMLFileToString1(const XMLFile* self, const String& indentation)
{
    return self->ToString(indentation);
}

static void RegisterXMLFile(kaguya::State& lua)
{
    using namespace kaguya;

    lua["XMLFile"].setClass(UserdataMetatable<XMLFile, Resource>()
        .addStaticFunction("new", &CreateObject<XMLFile>)

        .addFunction("FromString", &XMLFile::FromString)
        .addFunction("CreateRoot", &XMLFile::CreateRoot)

        ADD_OVERLOADED_FUNCTIONS_2(XMLFile, GetRoot)
        ADD_OVERLOADED_FUNCTIONS_2(XMLFile, ToString)

        .addOverloadedFunctions("Patch",
            static_cast<void(XMLFile::*)(XMLFile*)>(&XMLFile::Patch),
            static_cast<void(XMLFile::*)(XMLElement)>(&XMLFile::Patch))
    );
}

void RegisterResourceLuaAPI(kaguya::State& lua)
{
    RegisterResource(lua);

    RegisterImage(lua);
    RegisterJSONFile(lua);
    RegisterJSONValue(lua);
    RegisterLocalization(lua);
    RegisterPListFile(lua);
    RegisterResourceCache(lua);
    RegisterResourceEvents(lua);
    RegisterXMLElement(lua);
    RegisterXMLFile(lua);

    lua["cache"] = GetSubsystem<ResourceCache>();
    lua["GetCache"] = GetSubsystem<ResourceCache>;

    lua["localization"] = GetSubsystem<Localization>();
    lua["GetLocalization"] = GetSubsystem<Localization>;

    kaguya::LuaTable metatable = lua["__CALLABLE__"];

    lua["JSONValue"].setMetatable(metatable);
    lua["PListValue"].setMetatable(metatable);
    lua["XMLElement"].setMetatable(metatable);
    lua["XPathResultSet"].setMetatable(metatable);
    lua["XPathQuery"].setMetatable(metatable);
}
}
