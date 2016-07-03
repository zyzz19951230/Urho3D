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
extern Context* globalContext;

static FileSystem* GetFileSystem()
{
    return globalContext->GetSubsystem<FileSystem>();
}

static Log* GetLog()
{
    return globalContext->GetSubsystem<Log>();
}

template<typename class_type, typename base_class_type = void>
void RegisterDeserializer(kaguya::UserdataMetatable<class_type, base_class_type>& deserializer)
{
    using namespace kaguya;

    deserializer.addFunction("Seek", &Deserializer::Seek)
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
        .addProperty("size", &Deserializer::GetSize);
}


template<typename class_type, typename base_class_type = void>
void RegisterSerializer(kaguya::UserdataMetatable<class_type, base_class_type>& serializer)
{
    using namespace kaguya;

    serializer.addFunction("WriteInt", &Serializer::WriteInt)
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
        .addFunction("WriteLine", &Serializer::WriteLine);
}

static void RegisterFile(kaguya::State& lua)
{
    using namespace kaguya;

    // enum FileMode;
    lua["KFILE_READ"] = FILE_READ;
    lua["KFILE_WRITE"] = FILE_WRITE;
    lua["KFILE_READWRITE"] = FILE_READWRITE;

    UserdataMetatable<File, Object> file(false);

    file.addStaticFunction("new", &KCreateObject<File>)
        .addStaticFunction("__gc", &KReleaseObject<File>)

        .addOverloadedFunctions("Open",
            static_cast<bool(File::*)(const String&, FileMode)>(&File::Open),
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
        .addProperty("packaged", &File::IsPackaged);

    RegisterDeserializer(file);
    RegisterSerializer(file);

    lua["KFile"].setClass(file);
}

static void RegisterFileSystem(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KSCAN_FILES"] = SCAN_FILES;
    lua["KSCAN_DIRS"] = SCAN_DIRS;
    lua["KSCAN_HIDDEN"] = SCAN_HIDDEN;

    // GC is disable for subsystem object
    lua["KFileSystem"].setClass(UserdataMetatable<FileSystem, Object>(false)

        .addFunction("SetCurrentDir", &FileSystem::SetCurrentDir)
        .addFunction("CreateDir", &FileSystem::CreateDir)
        .addFunction("SetExecuteConsoleCommands", &FileSystem::SetExecuteConsoleCommands)
        .addFunction("SystemCommand", &FileSystem::SystemCommand)
        .addFunction("SystemRun", &FileSystem::SystemRun)
        .addFunction("SystemCommandAsync", &FileSystem::SystemCommandAsync)
        .addFunction("SystemRunAsync", &FileSystem::SystemRunAsync)
        .addFunction("SystemOpen", &FileSystem::SystemOpen)
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

    lua["KSplitPath"] = function(&SplitPath);
    lua["KGetPath"] = function(&GetPath);
    lua["KGetFileName"] = function(&GetFileName);
    lua["KGetExtension"] = function(&GetExtension);
    lua["KGetFileNameAndExtension"] = function(&GetFileNameAndExtension);
    lua["KReplaceExtension"] = function(&ReplaceExtension);
    lua["KAddTrailingSlash"] = function(&AddTrailingSlash);
    lua["KRemoveTrailingSlash"] = function(&RemoveTrailingSlash);
    lua["KGetParentPath"] = function(&GetParentPath);
    lua["KGetInternalPath"] = function(&GetInternalPath);
    lua["KGetNativePath"] = function(&GetNativePath);
    lua["KGetWideNativePath"] = function(&GetWideNativePath);
    lua["KIsAbsolutePath"] = function(&IsAbsolutePath);
}

static void RegisterIOEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KE_LOGMESSAGE"] = E_LOGMESSAGE;
    lua["KE_ASYNCEXECFINISHED"] = E_ASYNCEXECFINISHED;
}

static void RegisterLog(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KLOG_RAW"] = LOG_RAW;
    lua["KLOG_DEBUG"] = LOG_DEBUG;
    lua["KLOG_INFO"] = LOG_INFO;
    lua["KLOG_WARNING"] = LOG_WARNING;
    lua["KLOG_ERROR"] = LOG_ERROR;
    lua["KLOG_NONE"] = LOG_NONE;

    // GC is disable for subsystem object
    lua["KLog"].setClass(UserdataMetatable<Log, Object>(false)

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
        .addStaticFunction("WriteRaw", &Log::WriteRaw)

        .addProperty("level", &Log::GetLevel, &Log::SetLevel)
        .addProperty("timeStamp", &Log::GetTimeStamp, &Log::SetTimeStamp)
        .addProperty("lastMessage", &Log::GetLastMessage)
        .addProperty("quiet", &Log::IsQuiet, &Log::SetQuiet)
    );
}

static void RegisterPackageFile(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KPackageFile"].setClass(UserdataMetatable<PackageFile, Object>(false)
        .addStaticFunction("new", &KCreateObject<PackageFile>)
        .addStaticFunction("__gc", &KReleaseObject<PackageFile>)

        .addFunction("Open", &PackageFile::Open)
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

    UserdataMetatable<VectorBuffer> vectorBuffer;

    vectorBuffer.setConstructors<VectorBuffer(),
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
        .addProperty("buffer", &VectorBuffer::GetBuffer);

    RegisterDeserializer(vectorBuffer);
    RegisterSerializer(vectorBuffer);

    lua["KVectorBuffer"].setClass(vectorBuffer);
}

void RegisterIOLuaAPI(kaguya::State& lua)
{
    RegisterFile(lua);
    RegisterFileSystem(lua);
    RegisterIOEvents(lua);
    RegisterLog(lua);
    RegisterPackageFile(lua);
    RegisterVectorBuffer(lua);

    lua["kfileSystem"] = GetFileSystem();
    lua["KGetFileSystem"] = GetFileSystem;

    lua["klog"] = GetLog();
    lua["KGetLog"] = GetLog;
}

}
