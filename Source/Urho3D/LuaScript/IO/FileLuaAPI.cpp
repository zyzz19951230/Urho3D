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
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

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

void RegisterFile(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] FileMode
    // [Constant] File(Context* context, String& fileName, FileMode mode
    lua["FILE_READ"] = FILE_READ;
    // [Variable] FILE_WRITE,
    lua["FILE_WRITE"] = FILE_WRITE;
    // [Variable] FILE_READWRITE
    lua["FILE_READWRITE"] = FILE_READWRITE;

    // [Class] File : MultipleBase<Object, Deserializer, Serializer> 
    lua["File"].setClass(UserdataMetatable<File, MultipleBase<Object, Deserializer, Serializer> >()
        .addOverloadedFunctions("new", 
            &CreateFile0, 
            &CreateFile1,
            &CreateFile2,
            &CreateFile3)

        .addOverloadedFunctions("Open",
            FileOpen(),
            static_cast<bool(File::*)(PackageFile*, const String&)>(&File::Open))

        // [Method] void Close()
        .addFunction("Close", &File::Close)
        // [Method] void Flush()
        .addFunction("Flush", &File::Flush)
        // [Method] void SetName(const String& name)
        .addFunction("SetName", &File::SetName)

        // [Method] FileMode GetMode() const
        .addFunction("GetMode", &File::GetMode)
        // [Method] bool IsOpen() const
        .addFunction("IsOpen", &File::IsOpen)
        // [Method] void* GetHandle() const
        .addFunction("GetHandle", &File::GetHandle)
        // [Method] bool IsPackaged() const
        .addFunction("IsPackaged", &File::IsPackaged)

        // [Property(ReadOnly)] FileMode mode
        .addProperty("mode", &File::GetMode)
        // [Property(ReadOnly)] bool open
        .addProperty("open", &File::IsOpen)
        // [Property(ReadOnly)] void* handle
        .addProperty("handle", &File::GetHandle)
        // [Property(ReadOnly)] bool packaged
        .addProperty("packaged", &File::IsPackaged)
        );
}
}

