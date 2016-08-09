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

#include "../../Core/StringUtils.h"
#include "../../IO/FileSystem.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(FileSystemSystemCommand, FileSystem, SystemCommand, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(FileSystemSystemOpen, FileSystem, SystemOpen, 1, 2);

static Vector<String> FileSystemScanDir(const FileSystem* self, const String& pathName, const String& filter, unsigned flags, bool recursive)
{
    Vector<String> result;
    self->ScanDir(result, pathName, filter, flags, recursive);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(GetExtensionOverloads, GetExtension, 1, 2);
KAGUYA_FUNCTION_OVERLOADS(GetFileNameAndExtensionOverloads, GetFileNameAndExtension, 1, 2);

void RegisterFileSystem(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] unsigned SCAN_FILES
    lua["SCAN_FILES"] = SCAN_FILES;
    // [Constant] unsigned SCAN_DIRS
    lua["SCAN_DIRS"] = SCAN_DIRS;
    // [Constant] unsigned SCAN_HIDDEN
    lua["SCAN_HIDDEN"] = SCAN_HIDDEN;

    // [Class] FileSystem : Object
    lua["FileSystem"].setClass(UserdataMetatable<FileSystem, Object>()

        // [Method] bool SetCurrentDir(const String& pathName)
        .addFunction("SetCurrentDir", &FileSystem::SetCurrentDir)
        // [Method] bool CreateDir(const String& pathName)
        .addFunction("CreateDir", &FileSystem::CreateDir)
        // [Method] void SetExecuteConsoleCommands(bool enable)
        .addFunction("SetExecuteConsoleCommands", &FileSystem::SetExecuteConsoleCommands)

        // [Method] int SystemCommand(const String& commandLine, bool redirectStdOutToLog = false)
        .addFunction("SystemCommand", FileSystemSystemCommand())

        // [Method] int SystemRun(const String& fileName, const Vector<String>& arguments)
        .addFunction("SystemRun", &FileSystem::SystemRun)
        // [Method] unsigned SystemCommandAsync(const String& commandLine)
        .addFunction("SystemCommandAsync", &FileSystem::SystemCommandAsync)
        // [Method] unsigned SystemRunAsync(const String& fileName, const Vector<String>& arguments)
        .addFunction("SystemRunAsync", &FileSystem::SystemRunAsync)

        // [Method] bool SystemOpen(const String& fileName, const String& mode = String::EMPTY)
        .addFunction("SystemOpen", FileSystemSystemOpen())

        // [Method] bool Copy(const String& srcFileName, const String& destFileName)
        .addFunction("Copy", &FileSystem::Copy)
        // [Method] bool Rename(const String& srcFileName, const String& destFileName)
        .addFunction("Rename", &FileSystem::Rename)
        // [Method] bool Delete(const String& fileName)
        .addFunction("Delete", &FileSystem::Delete)
        
        // [Method] bool SetLastModifiedTime(const String& fileName, unsigned newTime)
        .addFunction("SetLastModifiedTime", &FileSystem::SetLastModifiedTime)
        // [Method] String GetCurrentDir() const
        .addFunction("GetCurrentDir", &FileSystem::GetCurrentDir)
        // [Method] bool GetExecuteConsoleCommands() const
        .addFunction("GetExecuteConsoleCommands", &FileSystem::GetExecuteConsoleCommands)
        // [Method] bool HasRegisteredPaths() const
        .addFunction("HasRegisteredPaths", &FileSystem::HasRegisteredPaths)
        // [Method] bool CheckAccess(const String& pathName) const
        .addFunction("CheckAccess", &FileSystem::CheckAccess)
        // [Method] unsigned GetLastModifiedTime(const String& fileName) const
        .addFunction("GetLastModifiedTime", &FileSystem::GetLastModifiedTime)
        
        // [Method] bool FileExists(const String& fileName) const
        .addFunction("FileExists", &FileSystem::FileExists)
        // [Method] bool DirExists(const String& pathName) const
        .addFunction("DirExists", &FileSystem::DirExists)
        
        .addStaticFunction("ScanDir", &FileSystemScanDir)

        // [Method] String GetProgramDir() const
        .addFunction("GetProgramDir", &FileSystem::GetProgramDir)
        // [Method] String GetUserDocumentsDir() const
        .addFunction("GetUserDocumentsDir", &FileSystem::GetUserDocumentsDir)
        // [Method] String GetAppPreferencesDir(const String& org, const String& app) const
        .addFunction("GetAppPreferencesDir", &FileSystem::GetAppPreferencesDir)
        );

    // [Function] URHO3D_API String GetPath(const String& fullPath)
    lua["GetPath"] = function(&GetPath);
    // [Function] URHO3D_API String GetFileName(const String& fullPath)
    lua["GetFileName"] = function(&GetFileName);
    
    lua["GetExtension"] = GetExtensionOverloads();
    lua["GetFileNameAndExtension"] = GetFileNameAndExtensionOverloads();

    // [Function] URHO3D_API String ReplaceExtension(const String& fullPath, const String& newExtension)
    lua["ReplaceExtension"] = function(&ReplaceExtension);
    // [Function] URHO3D_API String AddTrailingSlash(const String& pathName)
    lua["AddTrailingSlash"] = function(&AddTrailingSlash);
    // [Function] URHO3D_API String RemoveTrailingSlash(const String& pathName)
    lua["RemoveTrailingSlash"] = function(&RemoveTrailingSlash);
    // [Function] URHO3D_API String GetParentPath(const String& pathName)
    lua["GetParentPath"] = function(&GetParentPath);
    // [Function] URHO3D_API String GetInternalPath(const String& pathName)
    lua["GetInternalPath"] = function(&GetInternalPath);
    // [Function] URHO3D_API String GetNativePath(const String& pathName)
    lua["GetNativePath"] = function(&GetNativePath);

    // [Function] URHO3D_API bool IsAbsolutePath(const String& pathName)
    lua["IsAbsolutePath"] = function(&IsAbsolutePath);
    lua["GetFileSizeString"] = function(&GetFileSizeString);
}
}

