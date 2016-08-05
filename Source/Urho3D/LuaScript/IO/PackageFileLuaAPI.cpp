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
}

