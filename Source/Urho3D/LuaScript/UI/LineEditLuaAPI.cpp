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

#include "../../UI/LineEdit.h"
#include "../../UI/Text.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterLineEdit(kaguya::State& lua)
{
    using namespace kaguya;

    lua["LineEdit"].setClass(UserdataMetatable<LineEdit, BorderImage>()
        .addStaticFunction("new", &CreateObject<LineEdit>)

        .addFunction("SetText", &LineEdit::SetText)
        .addFunction("SetCursorPosition", &LineEdit::SetCursorPosition)
        .addFunction("SetCursorBlinkRate", &LineEdit::SetCursorBlinkRate)
        .addFunction("SetMaxLength", &LineEdit::SetMaxLength)
        .addFunction("SetEchoCharacter", &LineEdit::SetEchoCharacter)
        .addFunction("SetCursorMovable", &LineEdit::SetCursorMovable)
        .addFunction("SetTextSelectable", &LineEdit::SetTextSelectable)
        .addFunction("SetTextCopyable", &LineEdit::SetTextCopyable)

        .addFunction("GetText", &LineEdit::GetText)
        .addFunction("GetCursorPosition", &LineEdit::GetCursorPosition)
        .addFunction("GetCursorBlinkRate", &LineEdit::GetCursorBlinkRate)
        .addFunction("GetMaxLength", &LineEdit::GetMaxLength)
        .addFunction("GetEchoCharacter", &LineEdit::GetEchoCharacter)
        .addFunction("IsCursorMovable", &LineEdit::IsCursorMovable)
        .addFunction("IsTextSelectable", &LineEdit::IsTextSelectable)
        .addFunction("IsTextCopyable", &LineEdit::IsTextCopyable)
        .addFunction("GetTextElement", &LineEdit::GetTextElement)
        .addFunction("GetCursor", &LineEdit::GetCursor)

        .addProperty("text", &LineEdit::GetText, &LineEdit::SetText)
        .addProperty("cursorPosition", &LineEdit::GetCursorPosition, &LineEdit::SetCursorPosition)
        .addProperty("cursorBlinkRate", &LineEdit::GetCursorBlinkRate, &LineEdit::SetCursorBlinkRate)
        .addProperty("maxLength", &LineEdit::GetMaxLength, &LineEdit::SetMaxLength)
        .addProperty("echoCharacter", &LineEdit::GetEchoCharacter, &LineEdit::SetEchoCharacter)
        .addProperty("cursorMovable", &LineEdit::IsCursorMovable, &LineEdit::SetCursorMovable)
        .addProperty("textSelectable", &LineEdit::IsTextSelectable, &LineEdit::SetTextSelectable)
        .addProperty("textCopyable", &LineEdit::IsTextCopyable, &LineEdit::SetTextCopyable)
        .addProperty("textElement", &LineEdit::GetTextElement)
        .addProperty("cursor", &LineEdit::GetCursor)
        );
}
}

