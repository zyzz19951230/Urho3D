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

#include "../../UI/ListView.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{


KAGUYA_MEMBER_FUNCTION_OVERLOADS(ListViewInsertItem, ListView, InsertItem, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ListViewRemoveItem, ListView, RemoveItem, 1, 2, void(ListView::*)(UIElement*, unsigned));
KAGUYA_MEMBER_FUNCTION_OVERLOADS(ListViewChangeSelection, ListView, ChangeSelection, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(ListViewExpand, ListView, Expand, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(ListViewToggleExpand, ListView, ToggleExpand, 1, 2);

static SharedPtr<UIElement> ListViewGetItem(const ListView* self, unsigned index)
{
    return SharedPtr<UIElement>(self->GetItem(index));
}

static SharedPtr<UIElement> ListViewGetSelectedItem(const ListView* self)
{
    return SharedPtr<UIElement>(self->GetSelectedItem());
}

void RegisterListView(kaguya::State& lua)
{
    using namespace kaguya;

    // enum HighlightMode;
    lua["HM_NEVER"] = HM_NEVER;
    lua["HM_FOCUS"] = HM_FOCUS;
    lua["HM_ALWAYS"] = HM_ALWAYS;

    lua["ListView"].setClass(UserdataMetatable<ListView, ScrollView>()
        .addStaticFunction("new", &CreateObject<ListView>)

        .addFunction("AddItem", &ListView::AddItem)

        .addFunction("InsertItem", ListViewInsertItem())

        .addOverloadedFunctions("RemoveItem",
            ListViewRemoveItem(),
            static_cast<void (ListView::*)(unsigned)>(&ListView::RemoveItem))

        .addFunction("RemoveAllItems", &ListView::RemoveAllItems)
        .addFunction("SetSelection", &ListView::SetSelection)
        .addFunction("SetSelections", &ListView::SetSelections)

        .addFunction("AddSelection", &ListView::AddSelection)
        .addFunction("RemoveSelection", &ListView::RemoveSelection)
        .addFunction("ToggleSelection", &ListView::ToggleSelection)

        .addFunction("ChangeSelection", ListViewChangeSelection())

        .addFunction("ClearSelection", &ListView::ClearSelection)
        .addFunction("SetHighlightMode", &ListView::SetHighlightMode)
        .addFunction("SetMultiselect", &ListView::SetMultiselect)
        .addFunction("SetHierarchyMode", &ListView::SetHierarchyMode)
        .addFunction("SetBaseIndent", &ListView::SetBaseIndent)
        .addFunction("SetClearSelectionOnDefocus", &ListView::SetClearSelectionOnDefocus)
        .addFunction("SetSelectOnClickEnd", &ListView::SetSelectOnClickEnd)

        .addFunction("Expand", ListViewExpand())
        .addFunction("ToggleExpand", ListViewToggleExpand())

        .addFunction("GetNumItems", &ListView::GetNumItems)
        .addStaticFunction("GetItem", &ListViewGetItem)

        .addFunction("GetItems", &ListView::GetItems)

        .addFunction("FindItem", &ListView::FindItem)
        .addFunction("GetSelection", &ListView::GetSelection)
        .addFunction("GetSelections", &ListView::GetSelectedItems)
        .addFunction("CopySelectedItemsToClipboard", &ListView::CopySelectedItemsToClipboard)

        .addStaticFunction("GetSelectedItem", &ListViewGetSelectedItem)

        .addFunction("GetSelectedItems", &ListView::GetSelectedItems)

        .addFunction("IsSelected", &ListView::IsSelected)
        .addFunction("IsExpanded", &ListView::IsExpanded)
        .addFunction("GetHighlightMode", &ListView::GetHighlightMode)
        .addFunction("GetMultiselect", &ListView::GetMultiselect)
        .addFunction("GetClearSelectionOnDefocus", &ListView::GetClearSelectionOnDefocus)
        .addFunction("GetSelectOnClickEnd", &ListView::GetSelectOnClickEnd)
        .addFunction("GetHierarchyMode", &ListView::GetHierarchyMode)
        .addFunction("GetBaseIndent", &ListView::GetBaseIndent)

        .addProperty("numItems", &ListView::GetNumItems)
        .addProperty("selection", &ListView::GetSelection, &ListView::SetSelection)
        .addProperty("selectedItem", &ListViewGetSelectedItem)
        .addProperty("highlightMode", &ListView::GetHighlightMode, &ListView::SetHighlightMode)
        .addProperty("multiselect", &ListView::GetMultiselect, &ListView::SetMultiselect)
        .addProperty("clearSelectionOnDefocus", &ListView::GetClearSelectionOnDefocus, &ListView::SetClearSelectionOnDefocus)
        .addProperty("selectOnClickEnd", &ListView::GetSelectOnClickEnd, &ListView::SetSelectOnClickEnd)
        .addProperty("hierarchyMode", &ListView::GetHierarchyMode, &ListView::SetHierarchyMode)
        .addProperty("baseIndent", &ListView::GetBaseIndent, &ListView::SetBaseIndent)
        );
}
}

