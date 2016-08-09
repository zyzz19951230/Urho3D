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

#include "../../UI/Menu.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static SharedPtr<UIElement> MenuGetPopup(const Menu* self)
{
    return SharedPtr<UIElement>(self->GetPopup());
}

void RegisterMenu(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Menu : Button
    lua["Menu"].setClass(UserdataMetatable<Menu, Button>()
        .addStaticFunction("new", &CreateObject<Menu>)

        // [Method] void SetPopup(UIElement* element)
        .addFunction("SetPopup", &Menu::SetPopup)

        .addOverloadedFunctions("SetPopupOffset",
            static_cast<void(Menu::*)(const IntVector2&)>(&Menu::SetPopupOffset),
            static_cast<void(Menu::*)(int, int)>(&Menu::SetPopupOffset))

        // [Method] void ShowPopup(bool enable)
        .addFunction("ShowPopup", &Menu::ShowPopup)
        // [Method] void SetAccelerator(int key, int qualifiers)
        .addFunction("SetAccelerator", &Menu::SetAccelerator)

        .addStaticFunction("GetPopup", &MenuGetPopup)

        // [Method] const IntVector2& GetPopupOffset() const
        .addFunction("GetPopupOffset", &Menu::GetPopupOffset)
        // [Method] bool GetShowPopup() const
        .addFunction("GetShowPopup", &Menu::GetShowPopup)
        // [Method] int GetAcceleratorKey() const
        .addFunction("GetAcceleratorKey", &Menu::GetAcceleratorKey)
        // [Method] int GetAcceleratorQualifiers() const
        .addFunction("GetAcceleratorQualifiers", &Menu::GetAcceleratorQualifiers)

        .addProperty("popup", &MenuGetPopup)
        // [Property] const IntVector2& popupOffset
        .addProperty("popupOffset", &Menu::GetPopupOffset, static_cast<void(Menu::*)(const IntVector2&)>(&Menu::SetPopupOffset))
        // [Property(ReadOnly)] bool showPopup
        .addProperty("showPopup", &Menu::GetShowPopup)
        // [Property(ReadOnly)] int acceleratorKey
        .addProperty("acceleratorKey", &Menu::GetAcceleratorKey)
        // [Property(ReadOnly)] int acceleratorQualifiers
        .addProperty("acceleratorQualifiers", &Menu::GetAcceleratorQualifiers)
        );
}
}

