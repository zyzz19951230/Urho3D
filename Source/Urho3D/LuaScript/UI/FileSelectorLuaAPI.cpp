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

    // [Class] FileSelectorEntry
    lua["FileSelectorEntry"].setClass(UserdataMetatable<FileSelectorEntry>()

        .addProperty("name", &FileSelectorEntry::name_)
        .addProperty("directory", &FileSelectorEntry::directory_)
        );

    // [Class] FileSelector : Object
    lua["FileSelector"].setClass(UserdataMetatable<FileSelector, Object>()
        .addStaticFunction("new", &CreateObject<FileSelector>)

        // [Method] void SetDefaultStyle(XMLFile* style)
        .addFunction("SetDefaultStyle", &FileSelector::SetDefaultStyle)
        // [Method] void SetTitle(const String& text)
        .addFunction("SetTitle", &FileSelector::SetTitle)
        // [Method] void SetButtonTexts(const String& okText, const String& cancelText)
        .addFunction("SetButtonTexts", &FileSelector::SetButtonTexts)
        // [Method] void SetPath(const String& path)
        .addFunction("SetPath", &FileSelector::SetPath)
        // [Method] void SetFileName(const String& fileName)
        .addFunction("SetFileName", &FileSelector::SetFileName)
        // [Method] void SetFilters(const Vector<String>& filters, unsigned defaultIndex)
        .addFunction("SetFilters", &FileSelector::SetFilters)
        // [Method] void SetDirectoryMode(bool enable)
        .addFunction("SetDirectoryMode", &FileSelector::SetDirectoryMode)

        // [Method] void UpdateElements()
        .addFunction("UpdateElements", &FileSelector::UpdateElements)

        // [Method] XMLFile* GetDefaultStyle() const
        .addFunction("GetDefaultStyle", &FileSelector::GetDefaultStyle)
        // [Method] Window* GetWindow() const
        .addFunction("GetWindow", &FileSelector::GetWindow)
        // [Method] Text* GetTitleText() const
        .addFunction("GetTitleText", &FileSelector::GetTitleText)
        // [Method] ListView* GetFileList() const
        .addFunction("GetFileList", &FileSelector::GetFileList)
        // [Method] LineEdit* GetPathEdit() const
        .addFunction("GetPathEdit", &FileSelector::GetPathEdit)
        // [Method] LineEdit* GetFileNameEdit() const
        .addFunction("GetFileNameEdit", &FileSelector::GetFileNameEdit)
        // [Method] DropDownList* GetFilterList() const
        .addFunction("GetFilterList", &FileSelector::GetFilterList)
        // [Method] Button* GetOKButton() const
        .addFunction("GetOKButton", &FileSelector::GetOKButton)
        // [Method] Button* GetCancelButton() const
        .addFunction("GetCancelButton", &FileSelector::GetCancelButton)
        // [Method] Button* GetCloseButton() const
        .addFunction("GetCloseButton", &FileSelector::GetCloseButton)
        // [Method] const String& GetTitle() const
        .addFunction("GetTitle", &FileSelector::GetTitle)
        // [Method] const String& GetPath() const
        .addFunction("GetPath", &FileSelector::GetPath)
        // [Method] const String& GetFileName() const
        .addFunction("GetFileName", &FileSelector::GetFileName)
        // [Method] const String& GetFilter() const
        .addFunction("GetFilter", &FileSelector::GetFilter)
        // [Method] unsigned GetFilterIndex() const
        .addFunction("GetFilterIndex", &FileSelector::GetFilterIndex)
        // [Method] bool GetDirectoryMode() const
        .addFunction("GetDirectoryMode", &FileSelector::GetDirectoryMode)

        // [Property] XMLFile* defaultStyle
        .addProperty("defaultStyle", &FileSelector::GetDefaultStyle, &FileSelector::SetDefaultStyle)
        // [Property(ReadOnly)] Window* window
        .addProperty("window", &FileSelector::GetWindow)
        // [Property(ReadOnly)] Text* titleText
        .addProperty("titleText", &FileSelector::GetTitleText)
        // [Property(ReadOnly)] ListView* fileList
        .addProperty("fileList", &FileSelector::GetFileList)
        // [Property(ReadOnly)] LineEdit* pathEdit
        .addProperty("pathEdit", &FileSelector::GetPathEdit)
        // [Property(ReadOnly)] LineEdit* fileNameEdit
        .addProperty("fileNameEdit", &FileSelector::GetFileNameEdit)
        // [Property(ReadOnly)] DropDownList* filterList
        .addProperty("filterList", &FileSelector::GetFilterList)
        // [Property(ReadOnly)] Button* OKButton
        .addProperty("OKButton", &FileSelector::GetOKButton)
        // [Property(ReadOnly)] Button* cancelButton
        .addProperty("cancelButton", &FileSelector::GetCancelButton)
        // [Property(ReadOnly)] Button* closeButton
        .addProperty("closeButton", &FileSelector::GetCloseButton)
        // [Property] const String& title
        .addProperty("title", &FileSelector::GetTitle, &FileSelector::SetTitle)
        // [Property] const String& path
        .addProperty("path", &FileSelector::GetPath, &FileSelector::SetPath)
        // [Property] const String& fileName
        .addProperty("fileName", &FileSelector::GetFileName, &FileSelector::SetFileName)
        // [Property(ReadOnly)] const String& filter
        .addProperty("filter", &FileSelector::GetFilter)
        // [Property(ReadOnly)] unsigned filterIndex
        .addProperty("filterIndex", &FileSelector::GetFilterIndex)
        // [Property] bool directoryMode
        .addProperty("directoryMode", &FileSelector::GetDirectoryMode, &FileSelector::SetDirectoryMode)
        );
}
}

