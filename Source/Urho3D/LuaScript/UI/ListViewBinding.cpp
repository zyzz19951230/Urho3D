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

    // [Enum] HighlightMode
    lua["HM_NEVER"] = HM_NEVER;
    lua["HM_FOCUS"] = HM_FOCUS;
    lua["HM_ALWAYS"] = HM_ALWAYS;

    // [Class] ListView : ScrollView
    lua["ListView"].setClass(UserdataMetatable<ListView, ScrollView>()
        // [Constructor] ListView()
        .addStaticFunction("new", &CreateObject<ListView>)

        // [Method] void AddItem(UIElement* item)
        .addFunction("AddItem", &ListView::AddItem)

        // [Method] void InsertItem(unsigned index, UIElement* item, UIElement* parentItem = 0)
        .addFunction("InsertItem", ListViewInsertItem())

        .addOverloadedFunctions("RemoveItem",
            // [Method] void RemoveItem(UIElement* item, unsigned index = 0)
            ListViewRemoveItem(),
            // [Method] void RemoveItem(unsigned index)
            static_cast<void (ListView::*)(unsigned)>(&ListView::RemoveItem))

        // [Method] void RemoveAllItems()
        .addFunction("RemoveAllItems", &ListView::RemoveAllItems)
        // [Method] void SetSelection(unsigned index)
        .addFunction("SetSelection", &ListView::SetSelection)
        // [Method] void SetSelections(const PODVector<unsigned>& indices)
        .addFunction("SetSelections", &ListView::SetSelections)

        // [Method] void AddSelection(unsigned index)
        .addFunction("AddSelection", &ListView::AddSelection)
        // [Method] void RemoveSelection(unsigned index)
        .addFunction("RemoveSelection", &ListView::RemoveSelection)
        // [Method] void ToggleSelection(unsigned index)
        .addFunction("ToggleSelection", &ListView::ToggleSelection)

        // [Method] void ChangeSelection(int delta, bool additive = false)
        .addFunction("ChangeSelection", ListViewChangeSelection())

        // [Method] void ClearSelection()
        .addFunction("ClearSelection", &ListView::ClearSelection)
        // [Method] void SetHighlightMode(HighlightMode mode)
        .addFunction("SetHighlightMode", &ListView::SetHighlightMode)
        // [Method] void SetMultiselect(bool enable)
        .addFunction("SetMultiselect", &ListView::SetMultiselect)
        // [Method] void SetHierarchyMode(bool enable)
        .addFunction("SetHierarchyMode", &ListView::SetHierarchyMode)
        // [Method] void SetBaseIndent(int baseIndent)
        .addFunction("SetBaseIndent", &ListView::SetBaseIndent)
        // [Method] void SetClearSelectionOnDefocus(bool enable)
        .addFunction("SetClearSelectionOnDefocus", &ListView::SetClearSelectionOnDefocus)
        // [Method] void SetSelectOnClickEnd(bool enable)
        .addFunction("SetSelectOnClickEnd", &ListView::SetSelectOnClickEnd)

        // [Method] void Expand(unsigned index, bool enable, bool recursive = false)
        .addFunction("Expand", ListViewExpand())
        // [Method] void ToggleExpand(unsigned index, bool recursive = false)
        .addFunction("ToggleExpand", ListViewToggleExpand())

        // [Method] unsigned GetNumItems() const
        .addFunction("GetNumItems", &ListView::GetNumItems)
        .addStaticFunction("GetItem", &ListViewGetItem)

        // [Method] PODVector<UIElement*> GetItems() const
        .addFunction("GetItems", &ListView::GetItems)

        // [Method] unsigned FindItem(UIElement* item) const
        .addFunction("FindItem", &ListView::FindItem)
        // [Method] unsigned GetSelection() const
        .addFunction("GetSelection", &ListView::GetSelection)
        // [Method] PODVector<UIElement*> GetSelections() const
        .addFunction("GetSelections", &ListView::GetSelectedItems)
        // [Method] void CopySelectedItemsToClipboard() const
        .addFunction("CopySelectedItemsToClipboard", &ListView::CopySelectedItemsToClipboard)

        .addStaticFunction("GetSelectedItem", &ListViewGetSelectedItem)

        // [Method] PODVector<UIElement*> GetSelectedItems() const
        .addFunction("GetSelectedItems", &ListView::GetSelectedItems)

        // [Method] bool IsSelected(unsigned index) const
        .addFunction("IsSelected", &ListView::IsSelected)
        // [Method] bool IsExpanded(unsigned index) const
        .addFunction("IsExpanded", &ListView::IsExpanded)
        // [Method] HighlightMode GetHighlightMode() const
        .addFunction("GetHighlightMode", &ListView::GetHighlightMode)
        // [Method] bool GetMultiselect() const
        .addFunction("GetMultiselect", &ListView::GetMultiselect)
        // [Method] bool GetClearSelectionOnDefocus() const
        .addFunction("GetClearSelectionOnDefocus", &ListView::GetClearSelectionOnDefocus)
        // [Method] bool GetSelectOnClickEnd() const
        .addFunction("GetSelectOnClickEnd", &ListView::GetSelectOnClickEnd)
        // [Method] bool GetHierarchyMode() const
        .addFunction("GetHierarchyMode", &ListView::GetHierarchyMode)
        // [Method] int GetBaseIndent() const
        .addFunction("GetBaseIndent", &ListView::GetBaseIndent)

        // [Property(Readonly)] unsigned numItems
        .addProperty("numItems", &ListView::GetNumItems)
        // [Property] unsigned selection
        .addProperty("selection", &ListView::GetSelection, &ListView::SetSelection)
        .addProperty("selectedItem", &ListViewGetSelectedItem)
        // [Property] HighlightMode highlightMode
        .addProperty("highlightMode", &ListView::GetHighlightMode, &ListView::SetHighlightMode)
        // [Property] bool multiselect
        .addProperty("multiselect", &ListView::GetMultiselect, &ListView::SetMultiselect)
        // [Property] bool clearSelectionOnDefocus
        .addProperty("clearSelectionOnDefocus", &ListView::GetClearSelectionOnDefocus, &ListView::SetClearSelectionOnDefocus)
        // [Property] bool selectOnClickEnd
        .addProperty("selectOnClickEnd", &ListView::GetSelectOnClickEnd, &ListView::SetSelectOnClickEnd)
        // [Property] bool hierarchyMode
        .addProperty("hierarchyMode", &ListView::GetHierarchyMode, &ListView::SetHierarchyMode)
        // [Property] int baseIndent
        .addProperty("baseIndent", &ListView::GetBaseIndent, &ListView::SetBaseIndent)
        );
}
}

