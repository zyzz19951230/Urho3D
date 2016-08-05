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

    lua["SCAN_FILES"] = SCAN_FILES;
    lua["SCAN_DIRS"] = SCAN_DIRS;
    lua["SCAN_HIDDEN"] = SCAN_HIDDEN;

    lua["FileSystem"].setClass(UserdataMetatable<FileSystem, Object>()

        .addFunction("SetCurrentDir", &FileSystem::SetCurrentDir)
        .addFunction("CreateDir", &FileSystem::CreateDir)
        .addFunction("SetExecuteConsoleCommands", &FileSystem::SetExecuteConsoleCommands)

        .addFunction("SystemCommand", FileSystemSystemCommand())

        .addFunction("SystemRun", &FileSystem::SystemRun)
        .addFunction("SystemCommandAsync", &FileSystem::SystemCommandAsync)
        .addFunction("SystemRunAsync", &FileSystem::SystemRunAsync)

        .addFunction("SystemOpen", FileSystemSystemOpen())

        .addFunction("Copy", &FileSystem::Copy)
        .addFunction("Rename", &FileSystem::Rename)
        .addFunction("Delete", &FileSystem::Delete)
        
        .addFunction("SetLastModifiedTime", &FileSystem::SetLastModifiedTime)
        .addFunction("GetCurrentDir", &FileSystem::GetCurrentDir)
        .addFunction("GetExecuteConsoleCommands", &FileSystem::GetExecuteConsoleCommands)
        .addFunction("HasRegisteredPaths", &FileSystem::HasRegisteredPaths)
        .addFunction("CheckAccess", &FileSystem::CheckAccess)
        .addFunction("GetLastModifiedTime", &FileSystem::GetLastModifiedTime)
        
        .addFunction("FileExists", &FileSystem::FileExists)
        .addFunction("DirExists", &FileSystem::DirExists)
        
        .addStaticFunction("ScanDir", &FileSystemScanDir)

        .addFunction("GetProgramDir", &FileSystem::GetProgramDir)
        .addFunction("GetUserDocumentsDir", &FileSystem::GetUserDocumentsDir)
        .addFunction("GetAppPreferencesDir", &FileSystem::GetAppPreferencesDir)
        );

    lua["GetPath"] = function(&GetPath);
    lua["GetFileName"] = function(&GetFileName);
    
    lua["GetExtension"] = GetExtensionOverloads();
    lua["GetFileNameAndExtension"] = GetFileNameAndExtensionOverloads();

    lua["ReplaceExtension"] = function(&ReplaceExtension);
    lua["AddTrailingSlash"] = function(&AddTrailingSlash);
    lua["RemoveTrailingSlash"] = function(&RemoveTrailingSlash);
    lua["GetParentPath"] = function(&GetParentPath);
    lua["GetInternalPath"] = function(&GetInternalPath);
    lua["GetNativePath"] = function(&GetNativePath);

    lua["IsAbsolutePath"] = function(&IsAbsolutePath);
    lua["GetFileSizeString"] = function(&GetFileSizeString);
}
}

