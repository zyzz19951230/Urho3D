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

    lua["Console"].setClass(UserdataMetatable<Console, Object>()

        .addFunction("SetDefaultStyle", &Console::SetDefaultStyle)
        .addFunction("SetVisible", &Console::SetVisible)
        .addFunction("Toggle", &Console::Toggle)
        .addFunction("SetAutoVisibleOnError", &Console::SetAutoVisibleOnError)
        .addFunction("SetCommandInterpreter", &Console::SetCommandInterpreter)
        .addFunction("SetNumBufferedRows", &Console::SetNumBufferedRows)
        .addFunction("SetNumRows", &Console::SetNumRows)
        .addFunction("SetNumHistoryRows", &Console::SetNumHistoryRows)
        .addFunction("SetFocusOnShow", &Console::SetFocusOnShow)
        .addFunction("UpdateElements", &Console::UpdateElements)

        .addFunction("GetDefaultStyle", &Console::GetDefaultStyle)
        .addFunction("GetBackground", &Console::GetBackground)
        .addFunction("GetLineEdit", &Console::GetLineEdit)
        .addFunction("GetCloseButton", &Console::GetCloseButton)
        .addFunction("IsVisible", &Console::IsVisible)
        .addFunction("IsAutoVisibleOnError", &Console::IsAutoVisibleOnError)
        .addFunction("GetCommandInterpreter", &Console::GetCommandInterpreter)
        .addFunction("GetNumBufferedRows", &Console::GetNumBufferedRows)
        .addFunction("GetNumRows", &Console::GetNumRows)
        .addFunction("CopySelectedRows", &Console::CopySelectedRows)
        .addFunction("GetNumHistoryRows", &Console::GetNumHistoryRows)
        .addFunction("GetHistoryPosition", &Console::GetHistoryPosition)
        .addFunction("GetHistoryRow", &Console::GetHistoryRow)
        .addFunction("GetFocusOnShow", &Console::GetFocusOnShow)

        .addProperty("defaultStyle", &Console::GetDefaultStyle, &Console::SetDefaultStyle)
        .addProperty("background", &Console::GetBackground)
        .addProperty("lineEdit", &Console::GetLineEdit)
        .addProperty("closeButton", &Console::GetCloseButton)
        .addProperty("visible", &Console::IsVisible, &Console::SetVisible)
        .addProperty("autoVisibleOnError", &Console::IsAutoVisibleOnError, &Console::SetAutoVisibleOnError)
        .addProperty("commandInterpreter", &Console::GetCommandInterpreter, &Console::SetCommandInterpreter)
        .addProperty("numBufferedRows", &Console::GetNumBufferedRows, &Console::SetNumBufferedRows)
        .addProperty("numRows", &Console::GetNumRows, &Console::SetNumRows)
        .addProperty("numHistoryRows", &Console::GetNumHistoryRows, &Console::SetNumHistoryRows)
        .addProperty("historyPosition", &Console::GetHistoryPosition)
        .addProperty("focusOnShow", &Console::GetFocusOnShow, &Console::SetFocusOnShow)
        );
}
}

