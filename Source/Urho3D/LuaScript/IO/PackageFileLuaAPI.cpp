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
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

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

void RegisterPackageFile(kaguya::State& lua)
{
    using namespace kaguya;
    // [Class] PackageEntry
    lua["PackageEntry"].setClass(UserdataMetatable<PackageEntry>()
        .addProperty("offset", &PackageEntry::offset_)
        .addProperty("size", &PackageEntry::size_)
        .addProperty("checksum", &PackageEntry::checksum_)
        );

    // [Class] PackageFile : Object
    lua["PackageFile"].setClass(UserdataMetatable<PackageFile, Object>()
        .addOverloadedFunctions("new",
            &CreatePackageFile0,
            &CreatePackageFile1,
            &CreatePackageFile2)

        // [Method] bool Open(const String& fileName, unsigned startOffset = 0)
        .addFunction("Open", PackageFileOpen())

        // [Method] bool Exists(const String& fileName) const
        .addFunction("Exists", &PackageFile::Exists)
        // [Method] const PackageEntry* GetEntry(const String& fileName) const
        .addFunction("GetEntry", &PackageFile::GetEntry)
        // [Method] const HashMap<String, PackageEntry>& GetEntries() const
        .addFunction("GetEntries", &PackageFile::GetEntries)
        
        // [Method] const String& GetName() const
        .addFunction("GetName", &PackageFile::GetName)
        // [Method] StringHash GetNameHash() const
        .addFunction("GetNameHash", &PackageFile::GetNameHash)
        // [Method] unsigned GetNumFiles() const
        .addFunction("GetNumFiles", &PackageFile::GetNumFiles)
        // [Method] unsigned GetTotalSize() const
        .addFunction("GetTotalSize", &PackageFile::GetTotalSize)
        // [Method] unsigned GetTotalDataSize() const
        .addFunction("GetTotalDataSize", &PackageFile::GetTotalDataSize)
        // [Method] unsigned GetChecksum() const
        .addFunction("GetChecksum", &PackageFile::GetChecksum)
        // [Method] bool IsCompressed() const
        .addFunction("IsCompressed", &PackageFile::IsCompressed)

        // [Property(ReadOnly)] const String& name
        .addProperty("name", &PackageFile::GetName)
        // [Property(ReadOnly)] StringHash nameHash
        .addProperty("nameHash", &PackageFile::GetNameHash)
        // [Property(ReadOnly)] unsigned numFiles
        .addProperty("numFiles", &PackageFile::GetNumFiles)
        // [Property(ReadOnly)] unsigned totalSize
        .addProperty("totalSize", &PackageFile::GetTotalSize)
        // [Property(ReadOnly)] unsigned totalDataSize
        .addProperty("totalDataSize", &PackageFile::GetTotalDataSize)
        // [Property(ReadOnly)] unsigned checksum
        .addProperty("checksum", &PackageFile::GetChecksum)
        // [Property(ReadOnly)] bool compressed
        .addProperty("compressed", &PackageFile::IsCompressed)
        );
}
}

