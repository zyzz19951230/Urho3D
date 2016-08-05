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

#include "../../UI/Button.h"
#include "../../UI/DropDownList.h"
#include "../../UI/FileSelector.h"
#include "../../UI/LineEdit.h"
#include "../../UI/ListView.h"
#include "../../UI/Text.h"
#include "../../UI/Window.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterFileSelector(kaguya::State& lua)
{
    using namespace kaguya;

    lua["FileSelectorEntry"].setClass(UserdataMetatable<FileSelectorEntry>()

        .addProperty("name", &FileSelectorEntry::name_)
        .addProperty("directory", &FileSelectorEntry::directory_)
        );

    lua["FileSelector"].setClass(UserdataMetatable<FileSelector, Object>()
        .addStaticFunction("new", &CreateObject<FileSelector>)

        .addFunction("SetDefaultStyle", &FileSelector::SetDefaultStyle)
        .addFunction("SetTitle", &FileSelector::SetTitle)
        .addFunction("SetButtonTexts", &FileSelector::SetButtonTexts)
        .addFunction("SetPath", &FileSelector::SetPath)
        .addFunction("SetFileName", &FileSelector::SetFileName)
        .addFunction("SetFilters", &FileSelector::SetFilters)
        .addFunction("SetDirectoryMode", &FileSelector::SetDirectoryMode)

        .addFunction("UpdateElements", &FileSelector::UpdateElements)

        .addFunction("GetDefaultStyle", &FileSelector::GetDefaultStyle)
        .addFunction("GetWindow", &FileSelector::GetWindow)
        .addFunction("GetTitleText", &FileSelector::GetTitleText)
        .addFunction("GetFileList", &FileSelector::GetFileList)
        .addFunction("GetPathEdit", &FileSelector::GetPathEdit)
        .addFunction("GetFileNameEdit", &FileSelector::GetFileNameEdit)
        .addFunction("GetFilterList", &FileSelector::GetFilterList)
        .addFunction("GetOKButton", &FileSelector::GetOKButton)
        .addFunction("GetCancelButton", &FileSelector::GetCancelButton)
        .addFunction("GetCloseButton", &FileSelector::GetCloseButton)
        .addFunction("GetTitle", &FileSelector::GetTitle)
        .addFunction("GetPath", &FileSelector::GetPath)
        .addFunction("GetFileName", &FileSelector::GetFileName)
        .addFunction("GetFilter", &FileSelector::GetFilter)
        .addFunction("GetFilterIndex", &FileSelector::GetFilterIndex)
        .addFunction("GetDirectoryMode", &FileSelector::GetDirectoryMode)

        .addProperty("defaultStyle", &FileSelector::GetDefaultStyle, &FileSelector::SetDefaultStyle)
        .addProperty("window", &FileSelector::GetWindow)
        .addProperty("titleText", &FileSelector::GetTitleText)
        .addProperty("fileList", &FileSelector::GetFileList)
        .addProperty("pathEdit", &FileSelector::GetPathEdit)
        .addProperty("fileNameEdit", &FileSelector::GetFileNameEdit)
        .addProperty("filterList", &FileSelector::GetFilterList)
        .addProperty("OKButton", &FileSelector::GetOKButton)
        .addProperty("cancelButton", &FileSelector::GetCancelButton)
        .addProperty("closeButton", &FileSelector::GetCloseButton)
        .addProperty("title", &FileSelector::GetTitle, &FileSelector::SetTitle)
        .addProperty("path", &FileSelector::GetPath, &FileSelector::SetPath)
        .addProperty("fileName", &FileSelector::GetFileName, &FileSelector::SetFileName)
        .addProperty("filter", &FileSelector::GetFilter)
        .addProperty("filterIndex", &FileSelector::GetFilterIndex)
        .addProperty("directoryMode", &FileSelector::GetDirectoryMode, &FileSelector::SetDirectoryMode)
        );
}
}

