#include "../Core/Context.h"
#include "../IO/Deserializer.h"
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../IO/FileWatcher.h"
#include "../IO/IOEvents.h"
#include "../IO/Log.h"
#include "../IO/MacFileWatcher.h"
#include "../IO/MemoryBuffer.h"
#include "../IO/NamedPipe.h"
#include "../IO/PackageFile.h"
#include "../IO/RWOpsWrapper.h"
#include "../IO/Serializer.h"
#include "../IO/VectorBuffer.h"

#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterDeserializer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Deserializer"].setClass(UserdataMetatable<Deserializer>()
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
        .addFunction("ReadBuffer", &Deserializer::ReadBuffer)
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

static void RegisterSerializer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Serializer"].setClass(UserdataMetatable<Serializer>()
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
        .addFunction("WriteBuffer", &Serializer::WriteBuffer)
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

static bool FileOpen0(File* self, const String& fileName)
{
    return self->Open(fileName);
}

static bool FileOpen1(File* self, const String& fileName, FileMode mode)
{
    return self->Open(fileName, mode);
}

static void RegisterFile(kaguya::State& lua)
{
    using namespace kaguya;

    // enum FileMode;
    lua["FILE_READ"] = FILE_READ;
    lua["FILE_WRITE"] = FILE_WRITE;
    lua["FILE_READWRITE"] = FILE_READWRITE;

    lua["File"].setClass(UserdataMetatable<File, MultipleBase<Object, Deserializer, Serializer>>()
        .addStaticFunction("new", &KCreateObject<File>)

        .addOverloadedFunctions("Open",
            FileOpen0,
            FileOpen1,
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

static int FileSystemSystemCommand0(FileSystem* self, const String& commandLine)
{
    return self->SystemCommand(commandLine);
}

static int FileSystemSystemCommand1(FileSystem* self, const String& commandLine, bool redirectStdOutToLog)
{
    return self->SystemCommand(commandLine, redirectStdOutToLog);
}

static bool FileSystemSystemOpen0(FileSystem* self, const String& fileName)
{
    return self->SystemOpen(fileName);
}

static bool FileSystemSystemOpen1(FileSystem* self, const String& fileName, const String& mode)
{
    return self->SystemOpen(fileName, mode);
}

static void SplitPath0(const String& fullPath, String& pathName, String& fileName, String& extension)
{
    SplitPath(fullPath, pathName, fileName, extension);
}

static void SplitPath1(const String& fullPath, String& pathName, String& fileName, String& extension, bool lowercaseExtension)
{
    SplitPath(fullPath, pathName, fileName, extension, lowercaseExtension);
}

static String GetExtension0(const String& fullPath)
{
    return GetExtension(fullPath);
}

static String GetExtension1(const String& fullPath, bool lowercaseExtension)
{
    return GetExtension(fullPath, lowercaseExtension);
}

static String GetFileNameAndExtension0(const String& fullPath)
{
    return GetFileNameAndExtension(fullPath);
}

static String GetFileNameAndExtension1(const String& fullPath, bool lowercaseExtension)
{
    return GetFileNameAndExtension(fullPath, lowercaseExtension);
}

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

        ADD_OVERLOADED_FUNCTIONS_2(FileSystem, SystemCommand)

        .addFunction("SystemRun", &FileSystem::SystemRun)
        .addFunction("SystemCommandAsync", &FileSystem::SystemCommandAsync)
        .addFunction("SystemRunAsync", &FileSystem::SystemRunAsync)

        ADD_OVERLOADED_FUNCTIONS_2(FileSystem, SystemOpen)

        .addFunction("Copy", &FileSystem::Copy)
        .addFunction("Rename", &FileSystem::Rename)
        .addFunction("Delete", &FileSystem::Delete)
        .addFunction("RegisterPath", &FileSystem::RegisterPath)
        .addFunction("SetLastModifiedTime", &FileSystem::SetLastModifiedTime)
        .addFunction("GetCurrentDir", &FileSystem::GetCurrentDir)
        .addFunction("GetExecuteConsoleCommands", &FileSystem::GetExecuteConsoleCommands)
        .addFunction("HasRegisteredPaths", &FileSystem::HasRegisteredPaths)
        .addFunction("CheckAccess", &FileSystem::CheckAccess)
        .addFunction("GetLastModifiedTime", &FileSystem::GetLastModifiedTime)
        .addFunction("FileExists", &FileSystem::FileExists)
        .addFunction("DirExists", &FileSystem::DirExists)
        .addFunction("ScanDir", &FileSystem::ScanDir)
        .addFunction("GetProgramDir", &FileSystem::GetProgramDir)
        .addFunction("GetUserDocumentsDir", &FileSystem::GetUserDocumentsDir)
        .addFunction("GetAppPreferencesDir", &FileSystem::GetAppPreferencesDir)

        .addProperty("executeConsoleCommands", &FileSystem::GetExecuteConsoleCommands, &FileSystem::SetExecuteConsoleCommands)
        .addProperty("programDir", &FileSystem::GetProgramDir)
        .addProperty("userDocumentsDir", &FileSystem::GetUserDocumentsDir)
        );

    lua["SplitPath"] = overload(&SplitPath0, &SplitPath1);

    lua["GetPath"] = function(&GetPath);
    lua["GetFileName"] = function(&GetFileName);

    lua["GetExtension"] = overload(&GetExtension0, &GetExtension1);

    lua["GetFileNameAndExtension"] = overload(&GetFileNameAndExtension0, &GetFileNameAndExtension1);

    lua["ReplaceExtension"] = function(&ReplaceExtension);
    lua["AddTrailingSlash"] = function(&AddTrailingSlash);
    lua["RemoveTrailingSlash"] = function(&RemoveTrailingSlash);
    lua["GetParentPath"] = function(&GetParentPath);
    lua["GetInternalPath"] = function(&GetInternalPath);
    lua["GetNativePath"] = function(&GetNativePath);
    lua["GetWideNativePath"] = function(&GetWideNativePath);
    lua["IsAbsolutePath"] = function(&IsAbsolutePath);
}

static void RegisterIOEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["E_LOGMESSAGE"] = E_LOGMESSAGE;
    lua["E_ASYNCEXECFINISHED"] = E_ASYNCEXECFINISHED;
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
        .addProperty("lastMessage", &Log::GetLastMessage)
        .addProperty("quiet", &Log::IsQuiet, &Log::SetQuiet)
        );
}

static bool PackageFileOpen0(PackageFile* self, const String& fileName)
{
    return self->Open(fileName);
}

static bool PackageFileOpen1(PackageFile* self, const String& fileName, unsigned int startOffset)
{
    return self->Open(fileName, startOffset);
}

static void RegisterPackageFile(kaguya::State& lua)
{
    using namespace kaguya;

    lua["PackageFile"].setClass(UserdataMetatable<PackageFile, Object>()
        .addStaticFunction("new", &KCreateObject<PackageFile>)

        ADD_OVERLOADED_FUNCTIONS_2(PackageFile, Open)

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
        .addFunction("GetEntryNames", &PackageFile::GetEntryNames)

        .addProperty("entries", &PackageFile::GetEntries)
        .addProperty("name", &PackageFile::GetName)
        .addProperty("nameHash", &PackageFile::GetNameHash)
        .addProperty("numFiles", &PackageFile::GetNumFiles)
        .addProperty("totalSize", &PackageFile::GetTotalSize)
        .addProperty("totalDataSize", &PackageFile::GetTotalDataSize)
        .addProperty("checksum", &PackageFile::GetChecksum)
        .addProperty("compressed", &PackageFile::IsCompressed)
        .addProperty("entryNames", &PackageFile::GetEntryNames)
        );
}

static void RegisterVectorBuffer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["VectorBuffer"].setClass(UserdataMetatable<VectorBuffer, MultipleBase<Deserializer, Serializer>>()
        .setConstructors<VectorBuffer(),
        VectorBuffer(const PODVector<unsigned char>&),
        VectorBuffer(const void*, unsigned),
        VectorBuffer(Deserializer&, unsigned)>()

        .addOverloadedFunctions("SetData",
            static_cast<void(VectorBuffer::*)(const PODVector<unsigned char>&)>(&VectorBuffer::SetData),
            static_cast<void(VectorBuffer::*)(const void*, unsigned)>(&VectorBuffer::SetData),
            static_cast<void(VectorBuffer::*)(Deserializer&, unsigned)>(&VectorBuffer::SetData))

        .addFunction("Clear", &VectorBuffer::Clear)
        .addFunction("Resize", &VectorBuffer::Resize)
        .addFunction("GetData", &VectorBuffer::GetData)
        .addFunction("GetModifiableData", &VectorBuffer::GetModifiableData)
        .addFunction("GetBuffer", &VectorBuffer::GetBuffer)

        .addProperty("data", &VectorBuffer::GetData)
        .addProperty("modifiableData", &VectorBuffer::GetModifiableData)
        .addProperty("buffer", &VectorBuffer::GetBuffer)
        );
}

void RegisterIOLuaAPI(kaguya::State& lua)
{
    RegisterDeserializer(lua);
    RegisterDeserializer(lua);
    RegisterFile(lua);
    RegisterFileSystem(lua);
    RegisterIOEvents(lua);
    RegisterLog(lua);
    RegisterPackageFile(lua);
    RegisterVectorBuffer(lua);

    lua["fileSystem"] = KGetSubsystem<FileSystem>();
    lua["GetFileSystem"] = KGetSubsystem<FileSystem>;

    lua["log"] = KGetSubsystem<Log>();
    lua["GetLog"] = KGetSubsystem<Log>;
}

}
