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

#include "../../Engine/Console.h"
#include "../../Resource/XMLFile.h"
#include "../../UI/BorderImage.h"
#include "../../UI/Button.h"
#include "../../UI/LineEdit.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConsole(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Console : Object
    lua["Console"].setClass(UserdataMetatable<Console, Object>()

        // [Method] void SetDefaultStyle(XMLFile* style)
        .addFunction("SetDefaultStyle", &Console::SetDefaultStyle)
        // [Method] void SetVisible(bool enable)
        .addFunction("SetVisible", &Console::SetVisible)
        // [Method] void Toggle()
        .addFunction("Toggle", &Console::Toggle)
        // [Method] void SetAutoVisibleOnError(bool enable)
        .addFunction("SetAutoVisibleOnError", &Console::SetAutoVisibleOnError)
        // [Method] void SetCommandInterpreter(const String& interpreter)
        .addFunction("SetCommandInterpreter", &Console::SetCommandInterpreter)
        // [Method] void SetNumBufferedRows(unsigned rows)
        .addFunction("SetNumBufferedRows", &Console::SetNumBufferedRows)
        // [Method] void SetNumRows(unsigned rows)
        .addFunction("SetNumRows", &Console::SetNumRows)
        // [Method] void SetNumHistoryRows(unsigned rows)
        .addFunction("SetNumHistoryRows", &Console::SetNumHistoryRows)
        // [Method] void SetFocusOnShow(bool enable)
        .addFunction("SetFocusOnShow", &Console::SetFocusOnShow)
        // [Method] void UpdateElements()
        .addFunction("UpdateElements", &Console::UpdateElements)

        // [Method] XMLFile* GetDefaultStyle() const
        .addFunction("GetDefaultStyle", &Console::GetDefaultStyle)
        // [Method] BorderImage* GetBackground() const
        .addFunction("GetBackground", &Console::GetBackground)
        // [Method] LineEdit* GetLineEdit() const
        .addFunction("GetLineEdit", &Console::GetLineEdit)
        // [Method] Button* GetCloseButton() const
        .addFunction("GetCloseButton", &Console::GetCloseButton)
        // [Method] bool IsVisible() const
        .addFunction("IsVisible", &Console::IsVisible)
        // [Method] bool IsAutoVisibleOnError() const
        .addFunction("IsAutoVisibleOnError", &Console::IsAutoVisibleOnError)
        // [Method] const String& GetCommandInterpreter() const
        .addFunction("GetCommandInterpreter", &Console::GetCommandInterpreter)
        // [Method] unsigned GetNumBufferedRows() const
        .addFunction("GetNumBufferedRows", &Console::GetNumBufferedRows)
        // [Method] unsigned GetNumRows() const
        .addFunction("GetNumRows", &Console::GetNumRows)
        // [Method] void CopySelectedRows() const
        .addFunction("CopySelectedRows", &Console::CopySelectedRows)
        // [Method] unsigned GetNumHistoryRows() const
        .addFunction("GetNumHistoryRows", &Console::GetNumHistoryRows)
        // [Method] unsigned GetHistoryPosition() const
        .addFunction("GetHistoryPosition", &Console::GetHistoryPosition)
        // [Method] const String& GetHistoryRow(unsigned index) const
        .addFunction("GetHistoryRow", &Console::GetHistoryRow)
        // [Method] bool GetFocusOnShow() const
        .addFunction("GetFocusOnShow", &Console::GetFocusOnShow)

        // [Property] XMLFile* defaultStyle
        .addProperty("defaultStyle", &Console::GetDefaultStyle, &Console::SetDefaultStyle)
        // [Property(Readonly)] BorderImage* background
        .addProperty("background", &Console::GetBackground)
        // [Property(Readonly)] LineEdit* lineEdit
        .addProperty("lineEdit", &Console::GetLineEdit)
        // [Property(Readonly)] Button* closeButton
        .addProperty("closeButton", &Console::GetCloseButton)
        // [Property] bool visible
        .addProperty("visible", &Console::IsVisible, &Console::SetVisible)
        // [Property] bool autoVisibleOnError
        .addProperty("autoVisibleOnError", &Console::IsAutoVisibleOnError, &Console::SetAutoVisibleOnError)
        // [Property] const String& commandInterpreter
        .addProperty("commandInterpreter", &Console::GetCommandInterpreter, &Console::SetCommandInterpreter)
        // [Property] unsigned numBufferedRows
        .addProperty("numBufferedRows", &Console::GetNumBufferedRows, &Console::SetNumBufferedRows)
        // [Property] unsigned numRows
        .addProperty("numRows", &Console::GetNumRows, &Console::SetNumRows)
        // [Property] unsigned numHistoryRows
        .addProperty("numHistoryRows", &Console::GetNumHistoryRows, &Console::SetNumHistoryRows)
        // [Property(Readonly)] unsigned historyPosition
        .addProperty("historyPosition", &Console::GetHistoryPosition)
        // [Property] bool focusOnShow
        .addProperty("focusOnShow", &Console::GetFocusOnShow, &Console::SetFocusOnShow)
        );
}
}

