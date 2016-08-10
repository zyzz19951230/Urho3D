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

    // [Constant] unsigned FIRST_REPLICATED_ID
    lua["FIRST_REPLICATED_ID"] = FIRST_REPLICATED_ID;
    // [Constant] unsigned LAST_REPLICATED_ID
    lua["LAST_REPLICATED_ID"] = LAST_REPLICATED_ID;
    // [Constant] unsigned FIRST_LOCAL_ID
    lua["FIRST_LOCAL_ID"] = FIRST_LOCAL_ID;
    // [Constant] unsigned LAST_LOCAL_ID
    lua["LAST_LOCAL_ID"] = LAST_LOCAL_ID;

    // [Enum] LoadMode
    lua["LOAD_RESOURCES_ONLY"] = LOAD_RESOURCES_ONLY;
    lua["LOAD_SCENE"] = LOAD_SCENE;
    lua["LOAD_SCENE_AND_RESOURCES"] = LOAD_SCENE_AND_RESOURCES;

    // [Class] Scene : Node
    lua["Scene"].setClass(UserdataMetatable<Scene, Node>()
        // [Constructor] Scene()
        .addStaticFunction("new", &CreateObject<Scene>)

        .addOverloadedFunctions("LoadXML", 
            // [Method] bool LoadXML(const String& fileName)
            &SceneLoadXML,
            // [Method] bool LoadXML(Deserializer& source)
            static_cast<bool (Scene::*)(Deserializer&)>(&Scene::LoadXML))
        .addOverloadedFunctions("LoadJSON", 
            // [Method] bool LoadJSON(const String& fileName)
            &SceneLoadJSON,
            // [Method] bool LoadJSON(Deserializer& source)
            static_cast<bool (Scene::*)(Deserializer&)>(&Scene::LoadJSON))
        .addOverloadedFunctions("SaveXML", 
            // [Method] bool SaveXML(const String& fileName, const String& indentation = "\t") const
            SceneSaveXMLOverloads(),
            // [Method] bool SaveXML(Serializer& dest, const String& indentation = "\t") const
            static_cast<bool (Scene::*)(Serializer&, const String&) const>(&Scene::SaveXML))
        .addOverloadedFunctions("SaveJSON", 
            // [Method] bool SaveJSON(const String& fileName, const String& indentation = "\t") const
            SceneSaveJSONOverloads(),
            // [Method] bool SaveJSON(Serializer& dest, const String& indentation = "\t") const
            static_cast<bool (Scene::*)(Serializer&, const String&) const>(&Scene::SaveJSON))

        // [Method] bool LoadAsync(const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
        .addStaticFunction("LoadAsync", SceneLoadAsyncOverloads())
        // [Method] bool LoadAsyncXML(const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
        .addStaticFunction("LoadAsyncXML", SceneLoadAsyncXMLOverloads())
        // [Method] bool LoadAsyncJSON(const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
        .addStaticFunction("LoadAsyncJSON", SceneLoadAsyncJSONOverloads())

        // [Method] void StopAsyncLoading()
        .addFunction("StopAsyncLoading", &Scene::StopAsyncLoading)

        // [Method] SharedPtr<Node> Instantiate(const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
        .addStaticFunction("Instantiate", SceneInstantiateOverloads())
        // [Method] SharedPtr<Node> InstantiateXML(const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
        .addStaticFunction("InstantiateXML", SceneInstantiateXMLOverloads())
        // [Method] SharedPtr<Node> InstantiateJSON(const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
        .addStaticFunction("InstantiateJSON", SceneInstantiateJSONOverloads())

        // [Method] void Clear(bool clearReplicated = true, bool clearLocal = true)
        .addFunction("Clear", SceneClear())

        // [Method] void SetUpdateEnabled(bool enable)
        .addFunction("SetUpdateEnabled", &Scene::SetUpdateEnabled)
        // [Method] void SetTimeScale(float scale)
        .addFunction("SetTimeScale", &Scene::SetTimeScale)
        // [Method] void SetElapsedTime(float time)
        .addFunction("SetElapsedTime", &Scene::SetElapsedTime)
        // [Method] void SetSmoothingConstant(float constant)
        .addFunction("SetSmoothingConstant", &Scene::SetSmoothingConstant)
        // [Method] void SetSnapThreshold(float threshold)
        .addFunction("SetSnapThreshold", &Scene::SetSnapThreshold)
        // [Method] void SetAsyncLoadingMs(int ms)
        .addFunction("SetAsyncLoadingMs", &Scene::SetAsyncLoadingMs)

        // [Method] void AddRequiredPackageFile(PackageFile* package)
        .addFunction("AddRequiredPackageFile", &Scene::AddRequiredPackageFile)
        // [Method] void ClearRequiredPackageFiles()
        .addFunction("ClearRequiredPackageFiles", &Scene::ClearRequiredPackageFiles)

        // [Method] void RegisterVar(const String& name)
        .addFunction("RegisterVar", &Scene::RegisterVar)
        // [Method] void UnregisterVar(const String& name)
        .addFunction("UnregisterVar", &Scene::UnregisterVar)
        // [Method] void UnregisterAllVars()
        .addFunction("UnregisterAllVars", &Scene::UnregisterAllVars)

        // [Method] Node* GetNode(unsigned id) const
        .addFunction("GetNode", &Scene::GetNode)
        .addFunction("GetComponentByID", static_cast<Component* (Scene::*)(unsigned) const>(&Scene::GetComponent))
        // [Method] bool GetNodesWithTag(PODVector<Node*>& dest, const String& tag)  const
        .addFunction("GetNodesWithTag", &Scene::GetNodesWithTag)

        // [Method] bool IsUpdateEnabled() const
        .addFunction("IsUpdateEnabled", &Scene::IsUpdateEnabled)
        // [Method] bool IsAsyncLoading() const
        .addFunction("IsAsyncLoading", &Scene::IsAsyncLoading)
        // [Method] float GetAsyncProgress() const
        .addFunction("GetAsyncProgress", &Scene::GetAsyncProgress)
        // [Method] LoadMode GetAsyncLoadMode() const
        .addFunction("GetAsyncLoadMode", &Scene::GetAsyncLoadMode)
        // [Method] const String& GetFileName() const
        .addFunction("GetFileName", &Scene::GetFileName)
        // [Method] unsigned GetChecksum() const
        .addFunction("GetChecksum", &Scene::GetChecksum)
        // [Method] float GetTimeScale() const
        .addFunction("GetTimeScale", &Scene::GetTimeScale)
        // [Method] float GetElapsedTime() const
        .addFunction("GetElapsedTime", &Scene::GetElapsedTime)
        // [Method] float GetSmoothingConstant() const
        .addFunction("GetSmoothingConstant", &Scene::GetSmoothingConstant)
        // [Method] float GetSnapThreshold() const
        .addFunction("GetSnapThreshold", &Scene::GetSnapThreshold)
        // [Method] int GetAsyncLoadingMs() const
        .addFunction("GetAsyncLoadingMs", &Scene::GetAsyncLoadingMs)

        // [Method] const Vector<SharedPtr<PackageFile> >& GetRequiredPackageFiles() const
        .addFunction("GetRequiredPackageFiles", &Scene::GetRequiredPackageFiles)

        // [Property] bool updateEnabled
        .addProperty("updateEnabled", &Scene::IsUpdateEnabled, &Scene::SetUpdateEnabled)
        // [Property(Readonly)] bool asyncLoading
        .addProperty("asyncLoading", &Scene::IsAsyncLoading)
        // [Property(Readonly)] float asyncProgress
        .addProperty("asyncProgress", &Scene::GetAsyncProgress)
        // [Property(Readonly)] LoadMode asyncLoadMode
        .addProperty("asyncLoadMode", &Scene::GetAsyncLoadMode)
        // [Property(Readonly)] const String& fileName
        .addProperty("fileName", &Scene::GetFileName)
        // [Property(Readonly)] unsigned checksum
        .addProperty("checksum", &Scene::GetChecksum)
        // [Property] float timeScale
        .addProperty("timeScale", &Scene::GetTimeScale, &Scene::SetTimeScale)
        // [Property] float elapsedTime
        .addProperty("elapsedTime", &Scene::GetElapsedTime, &Scene::SetElapsedTime)
        // [Property] float smoothingConstant
        .addProperty("smoothingConstant", &Scene::GetSmoothingConstant, &Scene::SetSmoothingConstant)
        // [Property] float snapThreshold
        .addProperty("snapThreshold", &Scene::GetSnapThreshold, &Scene::SetSnapThreshold)
        // [Property] int asyncLoadingMs
        .addProperty("asyncLoadingMs", &Scene::GetAsyncLoadingMs, &Scene::SetAsyncLoadingMs)
        );
}
}

