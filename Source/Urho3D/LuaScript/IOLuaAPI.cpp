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
#include "../IO/Compression.h"
#include "../IO/Deserializer.h"
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/NamedPipe.h"
#include "../IO/PackageFile.h"
#include "../IO/Serializer.h"
#include "../IO/VectorBuffer.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterCompression(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CompressVectorBuffer"] = &CompressVectorBuffer;
    lua["DecompressVectorBuffer"] = &DecompressVectorBuffer;
}

static VectorBuffer DeserializerRead(Deserializer* self, unsigned size)
{
    unsigned char* data = new unsigned char[size];
    self->Read(data, size);
    VectorBuffer buffer(data, size);
    delete[] data;
    return buffer;
}

static VectorBuffer DeserializerReadBuffer(Deserializer* self)
{
    return VectorBuffer(self->ReadBuffer());
}

static void RegisterDeserializer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Deserializer"].setClass(UserdataMetatable<Deserializer>()
        .addStaticFunction("Read", &DeserializerRead)

        .addFunction("Seek", &Deserializer::Seek)
        .addFunction("GetName", &Deserializer::GetName)
        .addFunction("GetChecksum", &Deserializer::GetChecksum)
        .addFunction("IsEof", &Deserializer::IsEof)
        .addFunction("GetPosition", &Deserializer::GetPosition)
        .addFunction("GetSize", &Deserializer::GetSize)

        .addFunction("ReadInt", &Deserializer::ReadInt)
        .addFunction("ReadShort", &Deserializer::ReadShort)
        .addFunction("ReadByte", &Deserializer::ReadByte)
        .addFunction("ReadUInt", &Deserializer::ReadUInt)
        .addFunction("ReadUShort", &Deserializer::ReadUShort)
        .addFunction("ReadUByte", &Deserializer::ReadUByte)
        .addFunction("ReadBool", &Deserializer::ReadBool)
        .addFunction("ReadFloat", &Deserializer::ReadFloat)
        .addFunction("ReadDouble", &Deserializer::ReadDouble)
        .addFunction("ReadIntRect", &Deserializer::ReadIntRect)
        .addFunction("ReadIntVector2", &Deserializer::ReadIntVector2)
        .addFunction("ReadRect", &Deserializer::ReadRect)
        .addFunction("ReadVector2", &Deserializer::ReadVector2)
        .addFunction("ReadVector3", &Deserializer::ReadVector3)
        .addFunction("ReadPackedVector3", &Deserializer::ReadPackedVector3)
        .addFunction("ReadVector4", &Deserializer::ReadVector4)
        .addFunction("ReadQuaternion", &Deserializer::ReadQuaternion)
        .addFunction("ReadPackedQuaternion", &Deserializer::ReadPackedQuaternion)
        .addFunction("ReadMatrix3", &Deserializer::ReadMatrix3)
        .addFunction("ReadMatrix3x4", &Deserializer::ReadMatrix3x4)
        .addFunction("ReadMatrix4", &Deserializer::ReadMatrix4)
        .addFunction("ReadColor", &Deserializer::ReadColor)
        .addFunction("ReadBoundingBox", &Deserializer::ReadBoundingBox)
        .addFunction("ReadString", &Deserializer::ReadString)
        .addFunction("ReadFileID", &Deserializer::ReadFileID)
        .addFunction("ReadStringHash", &Deserializer::ReadStringHash)
        
        .addStaticFunction("ReadBuffer", &DeserializerReadBuffer)

        .addFunction("ReadResourceRef", &Deserializer::ReadResourceRef)
        .addFunction("ReadResourceRefList", &Deserializer::ReadResourceRefList)

        .addOverloadedFunctions("ReadVariant",
            static_cast<Variant(Deserializer::*)()>(&Deserializer::ReadVariant),
            static_cast<Variant(Deserializer::*)(VariantType)>(&Deserializer::ReadVariant))

        .addFunction("ReadVariantVector", &Deserializer::ReadVariantVector)
        .addFunction("ReadStringVector", &Deserializer::ReadStringVector)
        .addFunction("ReadVariantMap", &Deserializer::ReadVariantMap)
        .addFunction("ReadVLE", &Deserializer::ReadVLE)
        .addFunction("ReadNetID", &Deserializer::ReadNetID)
        .addFunction("ReadLine", &Deserializer::ReadLine)

        .addProperty("name", &Deserializer::GetName)
        .addProperty("checksum", &Deserializer::GetChecksum)
        .addProperty("eof", &Deserializer::IsEof)
        .addProperty("position", &Deserializer::GetPosition)
        .addProperty("size", &Deserializer::GetSize)
        );
}

static unsigned SerializerWrite(Serializer* self, const VectorBuffer& buffer)
{
    return self->Write(buffer.GetData(), buffer.GetSize());
}

static bool SerializerWriteBuffer(Serializer* self, const VectorBuffer& buffer)
{
    return self->WriteBuffer(buffer.GetBuffer());
}

static void RegisterSerializer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Serializer"].setClass(UserdataMetatable<Serializer>()
        .addStaticFunction("Write", &SerializerWrite)

        .addFunction("WriteInt", &Serializer::WriteInt)
        .addFunction("WriteShort", &Serializer::WriteShort)
        .addFunction("WriteByte", &Serializer::WriteByte)
        .addFunction("WriteUInt", &Serializer::WriteUInt)
        .addFunction("WriteUShort", &Serializer::WriteUShort)
        .addFunction("WriteUByte", &Serializer::WriteUByte)
        .addFunction("WriteBool", &Serializer::WriteBool)
        .addFunction("WriteFloat", &Serializer::WriteFloat)
        .addFunction("WriteDouble", &Serializer::WriteDouble)
        .addFunction("WriteIntRect", &Serializer::WriteIntRect)
        .addFunction("WriteIntVector2", &Serializer::WriteIntVector2)
        .addFunction("WriteRect", &Serializer::WriteRect)
        .addFunction("WriteVector2", &Serializer::WriteVector2)
        .addFunction("WriteVector3", &Serializer::WriteVector3)
        .addFunction("WritePackedVector3", &Serializer::WritePackedVector3)
        .addFunction("WriteVector4", &Serializer::WriteVector4)
        .addFunction("WriteQuaternion", &Serializer::WriteQuaternion)
        .addFunction("WritePackedQuaternion", &Serializer::WritePackedQuaternion)
        .addFunction("WriteMatrix3", &Serializer::WriteMatrix3)
        .addFunction("WriteMatrix3x4", &Serializer::WriteMatrix3x4)
        .addFunction("WriteMatrix4", &Serializer::WriteMatrix4)
        .addFunction("WriteColor", &Serializer::WriteColor)
        .addFunction("WriteBoundingBox", &Serializer::WriteBoundingBox)
        .addFunction("WriteString", &Serializer::WriteString)
        .addFunction("WriteFileID", &Serializer::WriteFileID)
        .addFunction("WriteStringHash", &Serializer::WriteStringHash)
        
        .addStaticFunction("WriteBuffer", &SerializerWriteBuffer)

        .addFunction("WriteResourceRef", &Serializer::WriteResourceRef)
        .addFunction("WriteResourceRefList", &Serializer::WriteResourceRefList)
        .addFunction("WriteVariant", &Serializer::WriteVariant)
        .addFunction("WriteVariantData", &Serializer::WriteVariantData)
        .addFunction("WriteVariantVector", &Serializer::WriteVariantVector)
        .addFunction("WriteStringVector", &Serializer::WriteStringVector)
        .addFunction("WriteVariantMap", &Serializer::WriteVariantMap)
        .addFunction("WriteVLE", &Serializer::WriteVLE)
        .addFunction("WriteNetID", &Serializer::WriteNetID)
        .addFunction("WriteLine", &Serializer::WriteLine)
        );
}

static SharedPtr<File> CreateFile0()
{
    return SharedPtr<File>(new File(globalContext));
}

static SharedPtr<File> CreateFile1(const String& fileName)
{
    return SharedPtr<File>(new File(globalContext, fileName));
}

static SharedPtr<File> CreateFile2(const String& fileName, FileMode mode)
{
    return SharedPtr<File>(new File(globalContext, fileName, mode));
}

static SharedPtr<File> CreateFile3(PackageFile* package, const String& fileName)
{
    return SharedPtr<File>(new File(globalContext, package, fileName));
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(FileOpen, File, Open, 1, 2, bool(File::*)(const String&, FileMode));

static void RegisterFile(kaguya::State& lua)
{
    using namespace kaguya;

    // enum FileMode;
    lua["FILE_READ"] = FILE_READ;
    lua["FILE_WRITE"] = FILE_WRITE;
    lua["FILE_READWRITE"] = FILE_READWRITE;

    lua["File"].setClass(UserdataMetatable<File, MultipleBase<Object, Deserializer, Serializer>>()
        .addOverloadedFunctions("new", 
            &CreateFile0, 
            &CreateFile1,
            &CreateFile2,
            &CreateFile3)

        .addOverloadedFunctions("Open",
            FileOpen(),
            static_cast<bool(File::*)(PackageFile*, const String&)>(&File::Open))

        .addFunction("Close", &File::Close)
        .addFunction("Flush", &File::Flush)
        .addFunction("SetName", &File::SetName)

        .addFunction("GetMode", &File::GetMode)
        .addFunction("IsOpen", &File::IsOpen)
        .addFunction("GetHandle", &File::GetHandle)
        .addFunction("IsPackaged", &File::IsPackaged)

        .addProperty("mode", &File::GetMode)
        .addProperty("open", &File::IsOpen)
        .addProperty("handle", &File::GetHandle)
        .addProperty("packaged", &File::IsPackaged)
        );
}

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

static void RegisterFileSystem(kaguya::State& lua)
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

static void LogWriteRaw0(Log* self, const String& message)
{
    self->WriteRaw(message);
}

static void LogWriteRaw1(Log* self, const String& message, bool error)
{
    self->WriteRaw(message, error);
}

static void RegisterLog(kaguya::State& lua)
{
    using namespace kaguya;

    lua["LOG_RAW"] = LOG_RAW;
    lua["LOG_DEBUG"] = LOG_DEBUG;
    lua["LOG_INFO"] = LOG_INFO;
    lua["LOG_WARNING"] = LOG_WARNING;
    lua["LOG_ERROR"] = LOG_ERROR;
    lua["LOG_NONE"] = LOG_NONE;

    lua["Log"].setClass(UserdataMetatable<Log, Object>()

        .addFunction("Open", &Log::Open)
        .addFunction("Close", &Log::Close)

        .addFunction("SetLevel", &Log::SetLevel)
        .addFunction("SetTimeStamp", &Log::SetTimeStamp)
        .addFunction("SetQuiet", &Log::SetQuiet)

        .addFunction("GetLevel", &Log::GetLevel)
        .addFunction("GetTimeStamp", &Log::GetTimeStamp)
        .addFunction("GetLastMessage", &Log::GetLastMessage)
        .addFunction("IsQuiet", &Log::IsQuiet)

        .addStaticFunction("Write", &Log::Write)
        ADD_OVERLOADED_FUNCTIONS_2(Log, WriteRaw)

        .addProperty("level", &Log::GetLevel, &Log::SetLevel)
        .addProperty("timeStamp", &Log::GetTimeStamp, &Log::SetTimeStamp)
        .addProperty("quiet", &Log::IsQuiet, &Log::SetQuiet)
        );
}

static void RegisterNamedPipe(kaguya::State& lua)
{
    using namespace kaguya;

    lua["NamedPipe"].setClass(UserdataMetatable<NamedPipe, MultipleBase<Object, Deserializer, Serializer>>()
        
        .addFunction("Open", &NamedPipe::Open)
        .addFunction("Close", &NamedPipe::Close)
        .addFunction("IsOpen", &NamedPipe::IsOpen)
        );
}

static SharedPtr<PackageFile> CreatePackageFile0()
{
    return SharedPtr<PackageFile>(new PackageFile(globalContext));
}

static SharedPtr<PackageFile> CreatePackageFile1(const String& fileName)
{
    return SharedPtr<PackageFile>(new PackageFile(globalContext, fileName));
}

static SharedPtr<PackageFile> CreatePackageFile2(const String& fileName, unsigned startOffset)
{
    return SharedPtr<PackageFile>(new PackageFile(globalContext, fileName, startOffset));
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(PackageFileOpen, PackageFile, Open, 1, 2);

static void RegisterPackageFile(kaguya::State& lua)
{
    using namespace kaguya;
    lua["PackageEntry"].setClass(UserdataMetatable<PackageEntry>()
        .addProperty("offset", &PackageEntry::offset_)
        .addProperty("size", &PackageEntry::size_)
        .addProperty("checksum", &PackageEntry::checksum_)
        );

    lua["PackageFile"].setClass(UserdataMetatable<PackageFile, Object>()
        .addOverloadedFunctions("new",
            &CreatePackageFile0,
            &CreatePackageFile1,
            &CreatePackageFile2)

        .addFunction("Open", PackageFileOpen())

        .addFunction("Exists", &PackageFile::Exists)
        .addFunction("GetEntry", &PackageFile::GetEntry)
        .addFunction("GetEntries", &PackageFile::GetEntries)
        
        .addFunction("GetName", &PackageFile::GetName)
        .addFunction("GetNameHash", &PackageFile::GetNameHash)
        .addFunction("GetNumFiles", &PackageFile::GetNumFiles)
        .addFunction("GetTotalSize", &PackageFile::GetTotalSize)
        .addFunction("GetTotalDataSize", &PackageFile::GetTotalDataSize)
        .addFunction("GetChecksum", &PackageFile::GetChecksum)
        .addFunction("IsCompressed", &PackageFile::IsCompressed)

        .addProperty("name", &PackageFile::GetName)
        .addProperty("nameHash", &PackageFile::GetNameHash)
        .addProperty("numFiles", &PackageFile::GetNumFiles)
        .addProperty("totalSize", &PackageFile::GetTotalSize)
        .addProperty("totalDataSize", &PackageFile::GetTotalDataSize)
        .addProperty("checksum", &PackageFile::GetChecksum)
        .addProperty("compressed", &PackageFile::IsCompressed)
        );
}

static void RegisterVectorBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["VectorBuffer"].setClass(UserdataMetatable<VectorBuffer, MultipleBase<Deserializer, Serializer>>()
        .setConstructors<VectorBuffer(),
        VectorBuffer(Deserializer&, unsigned)>()

        .addFunction("SetData", static_cast<void(VectorBuffer::*)(Deserializer&, unsigned)>(&VectorBuffer::SetData))
        .addFunction("Clear", &VectorBuffer::Clear)
        .addFunction("Resize", &VectorBuffer::Resize)
        
        .addFunction("GetData", &VectorBuffer::GetData)
        .addFunction("GetModifiableData", &VectorBuffer::GetModifiableData)
        );
}

void RegisterIOLuaAPI(kaguya::State& lua)
{
    RegisterCompression(lua);
    RegisterDeserializer(lua);
    RegisterSerializer(lua);
    RegisterFile(lua);
    RegisterFileSystem(lua);
    RegisterLog(lua);
    RegisterNamedPipe(lua);
    RegisterPackageFile(lua);
    RegisterVectorBuffer(lua);

    lua["fileSystem"] = GetSubsystem<FileSystem>();
    lua["GetFileSystem"] = GetSubsystem<FileSystem>;

    lua["log"] = GetSubsystem<Log>();
    lua["GetLog"] = GetSubsystem<Log>;
}

}
