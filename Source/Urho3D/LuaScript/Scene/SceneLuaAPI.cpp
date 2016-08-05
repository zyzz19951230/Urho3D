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
#include "../../IO/PackageFile.h"
#include "../../Scene/Component.h"
#include "../../Scene/Scene.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static bool SceneLoadXML(Scene* scene, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return scene->LoadXML(*file);
}

static bool SceneLoadJSON(Scene* scene, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return scene->LoadJSON(*file);
}

static bool SceneSaveXML(const Scene* scene, const String& fileName, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return scene->SaveXML(*file, indentation);
}

KAGUYA_FUNCTION_OVERLOADS(SceneSaveXMLOverloads, SceneSaveXML, 2, 3);

static bool SceneSaveJSON(const Scene* scene, const String& fileName, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return scene->SaveJSON(*file, indentation);
}

KAGUYA_FUNCTION_OVERLOADS(SceneSaveJSONOverloads, SceneSaveJSON, 2, 3);

static bool SceneLoadAsync(Scene* self, const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return self->LoadAsync(file, mode);
}

KAGUYA_FUNCTION_OVERLOADS(SceneLoadAsyncOverloads, SceneLoadAsync, 2, 3);

static bool SceneLoadAsyncXML(Scene* self, const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return self->LoadAsyncXML(file, mode);
}

KAGUYA_FUNCTION_OVERLOADS(SceneLoadAsyncXMLOverloads, SceneLoadAsyncXML, 2, 3);

static bool SceneLoadAsyncJSON(Scene* self, const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return self->LoadAsyncJSON(file, mode);
}

KAGUYA_FUNCTION_OVERLOADS(SceneLoadAsyncJSONOverloads, SceneLoadAsyncJSON, 2, 3);

static SharedPtr<Node> SceneInstantiate(Scene* self, const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->Instantiate(*file, position, rotation, mode));
}

KAGUYA_FUNCTION_OVERLOADS(SceneInstantiateOverloads, SceneInstantiate, 4, 5);

static SharedPtr<Node> SceneInstantiateXML(Scene* self, const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->InstantiateXML(*file, position, rotation, mode));
}

KAGUYA_FUNCTION_OVERLOADS(SceneInstantiateXMLOverloads, SceneInstantiateXML, 4, 5);

static SharedPtr<Node> SceneInstantiateJSON(Scene* self, const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->InstantiateJSON(*file, position, rotation, mode));
}

KAGUYA_FUNCTION_OVERLOADS(SceneInstantiateJSONOverloads, SceneInstantiateJSON, 4, 5);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(SceneClear, Scene, Clear, 0, 2);

void RegisterScene(kaguya::State& lua)
{
    using namespace kaguya;

    lua["FIRST_REPLICATED_ID"] = FIRST_REPLICATED_ID;
    lua["LAST_REPLICATED_ID"] = LAST_REPLICATED_ID;
    lua["FIRST_LOCAL_ID"] = FIRST_LOCAL_ID;
    lua["LAST_LOCAL_ID"] = LAST_LOCAL_ID;

    // enum LoadMode;
    lua["LOAD_RESOURCES_ONLY"] = LOAD_RESOURCES_ONLY;
    lua["LOAD_SCENE"] = LOAD_SCENE;
    lua["LOAD_SCENE_AND_RESOURCES"] = LOAD_SCENE_AND_RESOURCES;

    lua["Scene"].setClass(UserdataMetatable<Scene, Node>()
        .addStaticFunction("new", &CreateObject<Scene>)

        .addOverloadedFunctions("LoadXML", &SceneLoadXML,
            static_cast<bool (Scene::*)(Deserializer&)>(&Scene::LoadXML))
        .addOverloadedFunctions("LoadJSON", &SceneLoadJSON,
            static_cast<bool (Scene::*)(Deserializer&)>(&Scene::LoadJSON))
        .addOverloadedFunctions("SaveXML", SceneSaveXMLOverloads(),
            static_cast<bool (Scene::*)(Serializer&, const String&) const>(&Scene::SaveXML))
        .addOverloadedFunctions("SaveJSON", SceneSaveJSONOverloads(),
            static_cast<bool (Scene::*)(Serializer&, const String&) const>(&Scene::SaveJSON))

        .addStaticFunction("LoadAsync", SceneLoadAsyncOverloads())
        .addStaticFunction("LoadAsyncXML", SceneLoadAsyncXMLOverloads())
        .addStaticFunction("LoadAsyncJSON", SceneLoadAsyncJSONOverloads())

        .addFunction("StopAsyncLoading", &Scene::StopAsyncLoading)

        .addStaticFunction("Instantiate", SceneInstantiateOverloads())
        .addStaticFunction("InstantiateXML", SceneInstantiateXMLOverloads())
        .addStaticFunction("InstantiateJSON", SceneInstantiateJSONOverloads())

        .addFunction("Clear", SceneClear())

        .addFunction("SetUpdateEnabled", &Scene::SetUpdateEnabled)
        .addFunction("SetTimeScale", &Scene::SetTimeScale)
        .addFunction("SetElapsedTime", &Scene::SetElapsedTime)
        .addFunction("SetSmoothingConstant", &Scene::SetSmoothingConstant)
        .addFunction("SetSnapThreshold", &Scene::SetSnapThreshold)
        .addFunction("SetAsyncLoadingMs", &Scene::SetAsyncLoadingMs)

        .addFunction("AddRequiredPackageFile", &Scene::AddRequiredPackageFile)
        .addFunction("ClearRequiredPackageFiles", &Scene::ClearRequiredPackageFiles)

        .addFunction("RegisterVar", &Scene::RegisterVar)
        .addFunction("UnregisterVar", &Scene::UnregisterVar)
        .addFunction("UnregisterAllVars", &Scene::UnregisterAllVars)

        .addFunction("GetNode", &Scene::GetNode)
        .addFunction("GetComponentByID", static_cast<Component* (Scene::*)(unsigned) const>(&Scene::GetComponent))
        .addFunction("GetNodesWithTag", &Scene::GetNodesWithTag)

        .addFunction("IsUpdateEnabled", &Scene::IsUpdateEnabled)
        .addFunction("IsAsyncLoading", &Scene::IsAsyncLoading)
        .addFunction("GetAsyncProgress", &Scene::GetAsyncProgress)
        .addFunction("GetAsyncLoadMode", &Scene::GetAsyncLoadMode)
        .addFunction("GetFileName", &Scene::GetFileName)
        .addFunction("GetChecksum", &Scene::GetChecksum)
        .addFunction("GetTimeScale", &Scene::GetTimeScale)
        .addFunction("GetElapsedTime", &Scene::GetElapsedTime)
        .addFunction("GetSmoothingConstant", &Scene::GetSmoothingConstant)
        .addFunction("GetSnapThreshold", &Scene::GetSnapThreshold)
        .addFunction("GetAsyncLoadingMs", &Scene::GetAsyncLoadingMs)

        .addFunction("GetRequiredPackageFiles", &Scene::GetRequiredPackageFiles)

        .addProperty("updateEnabled", &Scene::IsUpdateEnabled, &Scene::SetUpdateEnabled)
        .addProperty("asyncLoading", &Scene::IsAsyncLoading)
        .addProperty("asyncProgress", &Scene::GetAsyncProgress)
        .addProperty("asyncLoadMode", &Scene::GetAsyncLoadMode)
        .addProperty("fileName", &Scene::GetFileName)
        .addProperty("checksum", &Scene::GetChecksum)
        .addProperty("timeScale", &Scene::GetTimeScale, &Scene::SetTimeScale)
        .addProperty("elapsedTime", &Scene::GetElapsedTime, &Scene::SetElapsedTime)
        .addProperty("smoothingConstant", &Scene::GetSmoothingConstant, &Scene::SetSmoothingConstant)
        .addProperty("snapThreshold", &Scene::GetSnapThreshold, &Scene::SetSnapThreshold)
        .addProperty("asyncLoadingMs", &Scene::GetAsyncLoadingMs, &Scene::SetAsyncLoadingMs)
        );
}
}

