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

    // [Class] LineEdit : BorderImage
    lua["LineEdit"].setClass(UserdataMetatable<LineEdit, BorderImage>()
        // [Constructor] LineEdit()
        .addStaticFunction("new", &CreateObject<LineEdit>)

        // [Method] void SetText(const String& text)
        .addFunction("SetText", &LineEdit::SetText)
        // [Method] void SetCursorPosition(unsigned position)
        .addFunction("SetCursorPosition", &LineEdit::SetCursorPosition)
        // [Method] void SetCursorBlinkRate(float rate)
        .addFunction("SetCursorBlinkRate", &LineEdit::SetCursorBlinkRate)
        // [Method] void SetMaxLength(unsigned length)
        .addFunction("SetMaxLength", &LineEdit::SetMaxLength)
        // [Method] void SetEchoCharacter(unsigned c)
        .addFunction("SetEchoCharacter", &LineEdit::SetEchoCharacter)
        // [Method] void SetCursorMovable(bool enable)
        .addFunction("SetCursorMovable", &LineEdit::SetCursorMovable)
        // [Method] void SetTextSelectable(bool enable)
        .addFunction("SetTextSelectable", &LineEdit::SetTextSelectable)
        // [Method] void SetTextCopyable(bool enable)
        .addFunction("SetTextCopyable", &LineEdit::SetTextCopyable)

        // [Method] const String& GetText() const
        .addFunction("GetText", &LineEdit::GetText)
        // [Method] unsigned GetCursorPosition() const
        .addFunction("GetCursorPosition", &LineEdit::GetCursorPosition)
        // [Method] float GetCursorBlinkRate() const
        .addFunction("GetCursorBlinkRate", &LineEdit::GetCursorBlinkRate)
        // [Method] unsigned GetMaxLength() const
        .addFunction("GetMaxLength", &LineEdit::GetMaxLength)
        // [Method] unsigned GetEchoCharacter() const
        .addFunction("GetEchoCharacter", &LineEdit::GetEchoCharacter)
        // [Method] bool IsCursorMovable() const
        .addFunction("IsCursorMovable", &LineEdit::IsCursorMovable)
        // [Method] bool IsTextSelectable() const
        .addFunction("IsTextSelectable", &LineEdit::IsTextSelectable)
        // [Method] bool IsTextCopyable() const
        .addFunction("IsTextCopyable", &LineEdit::IsTextCopyable)
        // [Method] Text* GetTextElement() const
        .addFunction("GetTextElement", &LineEdit::GetTextElement)
        // [Method] BorderImage* GetCursor() const
        .addFunction("GetCursor", &LineEdit::GetCursor)

        // [Property] const String& text
        .addProperty("text", &LineEdit::GetText, &LineEdit::SetText)
        // [Property] unsigned cursorPosition
        .addProperty("cursorPosition", &LineEdit::GetCursorPosition, &LineEdit::SetCursorPosition)
        // [Property] float cursorBlinkRate
        .addProperty("cursorBlinkRate", &LineEdit::GetCursorBlinkRate, &LineEdit::SetCursorBlinkRate)
        // [Property] unsigned maxLength
        .addProperty("maxLength", &LineEdit::GetMaxLength, &LineEdit::SetMaxLength)
        // [Property] unsigned echoCharacter
        .addProperty("echoCharacter", &LineEdit::GetEchoCharacter, &LineEdit::SetEchoCharacter)
        // [Property] bool cursorMovable
        .addProperty("cursorMovable", &LineEdit::IsCursorMovable, &LineEdit::SetCursorMovable)
        // [Property] bool textSelectable
        .addProperty("textSelectable", &LineEdit::IsTextSelectable, &LineEdit::SetTextSelectable)
        // [Property] bool textCopyable
        .addProperty("textCopyable", &LineEdit::IsTextCopyable, &LineEdit::SetTextCopyable)
        // [Property(ReadOnly)] Text* textElement
        .addProperty("textElement", &LineEdit::GetTextElement)
        // [Property(ReadOnly)] BorderImage* cursor
        .addProperty("cursor", &LineEdit::GetCursor)
        );
}
}

