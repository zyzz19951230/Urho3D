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

#include "../../UI/CheckBox.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterCheckBox(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] CheckBox : BorderImage
    lua["CheckBox"].setClass(UserdataMetatable<CheckBox, BorderImage>()
        // [Constructor] CheckBox()
        .addStaticFunction("new", &CreateObject<CheckBox>)

        // [Method] void SetChecked(bool enable)
        .addFunction("SetChecked", &CheckBox::SetChecked)

        .addOverloadedFunctions("SetCheckedOffset",
            // [Method] void SetCheckedOffset(const IntVector2& rect)
            static_cast<void(CheckBox::*)(const IntVector2&)>(&CheckBox::SetCheckedOffset),
            // [Method] void SetCheckedOffset(int x, int y)
            static_cast<void(CheckBox::*)(int, int)>(&CheckBox::SetCheckedOffset))

        // [Method] bool IsChecked() const
        .addFunction("IsChecked", &CheckBox::IsChecked)
        // [Method] const IntVector2& GetCheckedOffset() const
        .addFunction("GetCheckedOffset", &CheckBox::GetCheckedOffset)

        // [Property] bool checked
        .addProperty("checked", &CheckBox::IsChecked, static_cast<void(CheckBox::*)(const IntVector2&)>(&CheckBox::SetCheckedOffset))
        // [Property] const IntVector2& checkedOffset
        .addProperty("checkedOffset", &CheckBox::GetCheckedOffset, static_cast<void(CheckBox::*)(const IntVector2&)>(&CheckBox::SetCheckedOffset))
        );
}
}

