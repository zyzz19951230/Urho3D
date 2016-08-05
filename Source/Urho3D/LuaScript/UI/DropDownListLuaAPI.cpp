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

#include "../../UI/DropDownList.h"
#include "../../UI/ListView.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static SharedPtr<UIElement> DropDownListGetItem(const DropDownList* self, unsigned index)
{
    return SharedPtr<UIElement>(self->GetItem(index));
}

static SharedPtr<UIElement> DropDownListGetSelectedItem(const DropDownList* self)
{
    return SharedPtr<UIElement>(self->GetSelectedItem());
}

static SharedPtr<UIElement> DropDownListGetPlaceholder(const DropDownList* self)
{
    return SharedPtr<UIElement>(self->GetPlaceholder());
}

void RegisterDropDownList(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DropDownList"].setClass(UserdataMetatable<DropDownList, Menu>()
        .addStaticFunction("new", &CreateObject<DropDownList>)

        .addFunction("AddItem", &DropDownList::AddItem)
        .addFunction("InsertItem", &DropDownList::InsertItem)

        .addOverloadedFunctions("RemoveItem",
            static_cast<void(DropDownList::*)(UIElement*)>(&DropDownList::RemoveItem),
            static_cast<void(DropDownList::*)(unsigned)>(&DropDownList::RemoveItem))

        .addFunction("RemoveAllItems", &DropDownList::RemoveAllItems)
        .addFunction("SetSelection", &DropDownList::SetSelection)
        .addFunction("SetPlaceholderText", &DropDownList::SetPlaceholderText)
        .addFunction("SetResizePopup", &DropDownList::SetResizePopup)

        .addFunction("GetNumItems", &DropDownList::GetNumItems)

        .addStaticFunction("GetItem", &DropDownListGetItem)

        .addFunction("GetItems", &DropDownList::GetItems)
        .addFunction("GetSelection", &DropDownList::GetSelection)

        .addStaticFunction("GetSelectedItem", &DropDownListGetSelectedItem)

        .addFunction("GetListView", &DropDownList::GetListView)

        .addStaticFunction("GetPlaceholder", &DropDownListGetPlaceholder)

        .addFunction("GetPlaceholderText", &DropDownList::GetPlaceholderText)
        .addFunction("GetResizePopup", &DropDownList::GetResizePopup)

        .addProperty("numItems", &DropDownList::GetNumItems)
        .addProperty("selection", &DropDownList::GetSelection, &DropDownList::SetSelection)
        .addProperty("selectedItem", &DropDownListGetSelectedItem)
        .addProperty("listView", &DropDownList::GetListView)
        .addProperty("placeholder", &DropDownListGetPlaceholder)
        .addProperty("placeholderText", &DropDownList::GetPlaceholderText, &DropDownList::SetPlaceholderText)
        .addProperty("resizePopup", &DropDownList::GetResizePopup, &DropDownList::SetResizePopup)
        );
}
}

