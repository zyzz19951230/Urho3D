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
#include "../../Resource/JSONFile.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static bool JSONFileSave(const JSONFile* self, const String& fileName, const String& indentation)
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->Save(*file, indentation);
}

void RegisterJSONFile(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] JSONFile : Resource
    lua["JSONFile"].setClass(UserdataMetatable<JSONFile, Resource>()
        // [Method] JSONFile()
        .addStaticFunction("new", &CreateObject<JSONFile>)

        // [Method] bool Save(const String& fileName, const String& indentation) const
        .addStaticFunction("Save", &JSONFileSave)
        // [Method] bool FromString(const String& source)
        .addFunction("FromString", &JSONFile::FromString)
        // [Method] JSONValue& CreateRoot()
        .addFunction("CreateRoot", static_cast<JSONValue&(JSONFile::*)()>(&JSONFile::GetRoot))
        // [Method] JSONValue& GetRoot() const
        .addFunction("GetRoot", static_cast<const JSONValue&(JSONFile::*)() const>(&JSONFile::GetRoot))

        // [Property] JSONValue& root
        .addProperty("root", static_cast<const JSONValue&(JSONFile::*)() const>(&JSONFile::GetRoot))
    );
}
}

