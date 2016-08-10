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

    // [Class] DropDownList : Menu
    lua["DropDownList"].setClass(UserdataMetatable<DropDownList, Menu>()
        // [Constructor] DropDownList()
        .addStaticFunction("new", &CreateObject<DropDownList>)

        // [Method] void AddItem(UIElement* item)
        .addFunction("AddItem", &DropDownList::AddItem)
        // [Method] void InsertItem(unsigned index, UIElement* item)
        .addFunction("InsertItem", &DropDownList::InsertItem)

        .addOverloadedFunctions("RemoveItem",
            // [Method] void RemoveItem(UIElement* item)
            static_cast<void(DropDownList::*)(UIElement*)>(&DropDownList::RemoveItem),
            // [Method] void RemoveItem(unsigned index)
            static_cast<void(DropDownList::*)(unsigned)>(&DropDownList::RemoveItem))

        // [Method] void RemoveAllItems()
        .addFunction("RemoveAllItems", &DropDownList::RemoveAllItems)
        // [Method] void SetSelection(unsigned index)
        .addFunction("SetSelection", &DropDownList::SetSelection)
        // [Method] void SetPlaceholderText(const String& text)
        .addFunction("SetPlaceholderText", &DropDownList::SetPlaceholderText)
        // [Method] void SetResizePopup(bool enable)
        .addFunction("SetResizePopup", &DropDownList::SetResizePopup)

        // [Method] unsigned GetNumItems() const
        .addFunction("GetNumItems", &DropDownList::GetNumItems)

        .addStaticFunction("GetItem", &DropDownListGetItem)

        // [Method] PODVector<UIElement*> GetItems() const
        .addFunction("GetItems", &DropDownList::GetItems)
        // [Method] unsigned GetSelection() const
        .addFunction("GetSelection", &DropDownList::GetSelection)

        .addStaticFunction("GetSelectedItem", &DropDownListGetSelectedItem)

        // [Method] ListView* GetListView() const
        .addFunction("GetListView", &DropDownList::GetListView)

        .addStaticFunction("GetPlaceholder", &DropDownListGetPlaceholder)

        // [Method] const String& GetPlaceholderText() const
        .addFunction("GetPlaceholderText", &DropDownList::GetPlaceholderText)
        // [Method] bool GetResizePopup() const
        .addFunction("GetResizePopup", &DropDownList::GetResizePopup)

        // [Property(ReadOnly)] unsigned numItems
        .addProperty("numItems", &DropDownList::GetNumItems)
        // [Property] unsigned selection
        .addProperty("selection", &DropDownList::GetSelection, &DropDownList::SetSelection)
        .addProperty("selectedItem", &DropDownListGetSelectedItem)
        // [Property(ReadOnly)] ListView* listView
        .addProperty("listView", &DropDownList::GetListView)
        .addProperty("placeholder", &DropDownListGetPlaceholder)
        // [Property] const String& placeholderText
        .addProperty("placeholderText", &DropDownList::GetPlaceholderText, &DropDownList::SetPlaceholderText)
        // [Property] bool resizePopup
        .addProperty("resizePopup", &DropDownList::GetResizePopup, &DropDownList::SetResizePopup)
        );
}
}

