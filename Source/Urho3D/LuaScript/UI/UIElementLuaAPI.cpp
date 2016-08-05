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

#include "../../UI/UIElement.h"
#include "../../IO/File.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static bool UIElementLoadXML(UIElement* uiElement, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return uiElement->LoadXML(*file);
}

static bool UIElementSaveXML(const UIElement* self, const char* filepath, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return  false;
    return self->SaveXML(*file, indentation);
}

KAGUYA_FUNCTION_OVERLOADS(UIElementSaveXMLOverloads, UIElementSaveXML, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(UIElementSetStyle, UIElement, SetStyle, 1, 2, bool(UIElement::*)(const String&, XMLFile*));
KAGUYA_MEMBER_FUNCTION_OVERLOADS(UIElementSetStyleAuto, UIElement, SetStyleAuto, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(UIElementSetLayout, UIElement, SetLayout, 1, 3);

static SharedPtr<UIElement> UIElementCreateChild(UIElement* self, StringHash type, const String& name = String::EMPTY, unsigned index = M_MAX_UNSIGNED)
{
    return SharedPtr<UIElement>(self->CreateChild(type, name, index));
}

KAGUYA_FUNCTION_OVERLOADS(UIElementCreateChildOverloads, UIElementCreateChild, 2, 4);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(UIElementRemoveChild, UIElement, RemoveChild, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(UIElementSetParent, UIElement, SetParent, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(UIElementAddTags, UIElement, AddTags, 1, 2, void(UIElement::*)(const String&, char));

KAGUYA_MEMBER_FUNCTION_OVERLOADS(UIElementGetDefaultStyle, UIElement, GetDefaultStyle, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(UIElementGetNumChildren, UIElement, GetNumChildren, 0, 1);

static SharedPtr<UIElement> UIElementGetChild0(const UIElement* self, unsigned index)
{
    return SharedPtr<UIElement>(self->GetChild(index));
}

static SharedPtr<UIElement> UIElementGetChild1(const UIElement* self, const String& name, bool recursive = false)
{
    return SharedPtr<UIElement>(self->GetChild(name, recursive));
}

static SharedPtr<UIElement> UIElementGetChild2(const UIElement* self, StringHash key, const Variant& value, bool recursive = false)
{
    return SharedPtr<UIElement>(self->GetChild(key, value, recursive));
}

KAGUYA_FUNCTION_OVERLOADS(UIElementGetChildOverloads1, UIElementGetChild1, 2, 3);
KAGUYA_FUNCTION_OVERLOADS(UIElementGetChildOverloads2, UIElementGetChild2, 3, 4);

static PODVector<UIElement*> UIElementGetChildren(const UIElement* self, bool recursive = false)
{
    PODVector<UIElement*> dest;
    self->GetChildren(dest, recursive);
    return dest;
}

KAGUYA_FUNCTION_OVERLOADS(UIElementGetChildrenOverloads, UIElementGetChildren, 1, 2);

static const PODVector<UIElement*> UIElementGetChildrenWithTag(const UIElement* self, const char* tag, bool recursive = false)
{
    PODVector<UIElement*> dest;
    self->GetChildrenWithTag(dest, tag, recursive);
    return dest;
}

KAGUYA_FUNCTION_OVERLOADS(UIElementGetChildrenWithTagOverloads, UIElementGetChildrenWithTag, 2, 3);

static void UIElementColorSetter(UIElement* self, const Color& color)
{
    self->SetColor(color);
}

static const Color& UIElementColorGetter(const UIElement* self)
{
    return self->GetColor(C_TOPLEFT);
}

static void UIElementDefaultStyleSetter(UIElement* self, XMLFile* style)
{
    self->SetDefaultStyle(style);
}

static XMLFile* UIElementDefaultStyleGetter(const UIElement* self)
{
    return self->GetDefaultStyle(true);
}

void RegisterUIElement(kaguya::State& lua)
{
    using namespace kaguya;

    // enum HorizontalAlignment;
    lua["HA_LEFT"] = HA_LEFT;
    lua["HA_CENTER"] = HA_CENTER;
    lua["HA_RIGHT"] = HA_RIGHT;

    // enum VerticalAlignment;
    lua["VA_TOP"] = VA_TOP;
    lua["VA_CENTER"] = VA_CENTER;
    lua["VA_BOTTOM"] = VA_BOTTOM;

    // enum Corner;
    lua["C_TOPLEFT"] = C_TOPLEFT;
    lua["C_TOPRIGHT"] = C_TOPRIGHT;
    lua["C_BOTTOMLEFT"] = C_BOTTOMLEFT;
    lua["C_BOTTOMRIGHT"] = C_BOTTOMRIGHT;
    lua["MAX_UIELEMENT_CORNERS"] = MAX_UIELEMENT_CORNERS;

    // enum Orientation;
    lua["O_HORIZONTAL"] = O_HORIZONTAL;
    lua["O_VERTICAL"] = O_VERTICAL;

    // enum FocusMode;
    lua["FM_NOTFOCUSABLE"] = FM_NOTFOCUSABLE;
    lua["FM_RESETFOCUS"] = FM_RESETFOCUS;
    lua["FM_FOCUSABLE"] = FM_FOCUSABLE;
    lua["FM_FOCUSABLE_DEFOCUSABLE"] = FM_FOCUSABLE_DEFOCUSABLE;

    // enum LayoutMode;
    lua["LM_FREE"] = LM_FREE;
    lua["LM_HORIZONTAL"] = LM_HORIZONTAL;
    lua["LM_VERTICAL"] = LM_VERTICAL;

    // enum TraversalMode;
    lua["TM_BREADTH_FIRST"] = TM_BREADTH_FIRST;
    lua["TM_DEPTH_FIRST"] = TM_DEPTH_FIRST;

    lua["DD_DISABLED"] = DD_DISABLED;
    lua["DD_SOURCE"] = DD_SOURCE;
    lua["DD_TARGET"] = DD_TARGET;
    lua["DD_SOURCE_AND_TARGET"] = DD_SOURCE_AND_TARGET;

    lua["UIElement"].setClass(UserdataMetatable<UIElement, Animatable>()
        .addStaticFunction("new", &CreateObject<UIElement>)

        .addFunction("ScreenToElement", &UIElement::ScreenToElement)
        .addFunction("ElementToScreen", &UIElement::ElementToScreen)

        .addStaticFunction("LoadXML", UIElementLoadXML)
        .addStaticFunction("SaveXML", UIElementSaveXMLOverloads())

        .addFunction("SetName", &UIElement::SetName)

        .addOverloadedFunctions("SetPosition",
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetPosition),
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetPosition))

        .addOverloadedFunctions("SetSize",
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetSize),
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetSize))

        .addFunction("SetWidth", &UIElement::SetWidth)
        .addFunction("SetHeight", &UIElement::SetHeight)

        .addOverloadedFunctions("SetMinSize",
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetMinSize),
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetMinSize))

        .addFunction("SetMinWidth", &UIElement::SetMinWidth)
        .addFunction("SetMinHeight", &UIElement::SetMinHeight)

        .addOverloadedFunctions("SetMaxSize",
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetMaxSize),
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetMaxSize))

        .addFunction("SetMaxWidth", &UIElement::SetMaxWidth)
        .addFunction("SetMaxHeight", &UIElement::SetMaxHeight)

        .addOverloadedFunctions("SetFixedSize",
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetFixedSize),
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetFixedSize))

        .addFunction("SetFixedWidth", &UIElement::SetFixedWidth)
        .addFunction("SetFixedHeight", &UIElement::SetFixedHeight)
        .addFunction("SetAlignment", &UIElement::SetAlignment)
        .addFunction("SetHorizontalAlignment", &UIElement::SetHorizontalAlignment)
        .addFunction("SetVerticalAlignment", &UIElement::SetVerticalAlignment)
        .addFunction("SetClipBorder", &UIElement::SetClipBorder)

        .addOverloadedFunctions("SetColor",
            static_cast<void(UIElement::*)(const Color&)>(&UIElement::SetColor),
            static_cast<void(UIElement::*)(Corner, const Color&)>(&UIElement::SetColor))

        .addFunction("SetPriority", &UIElement::SetPriority)
        .addFunction("SetOpacity", &UIElement::SetOpacity)
        .addFunction("SetBringToFront", &UIElement::SetBringToFront)
        .addFunction("SetBringToBack", &UIElement::SetBringToBack)
        .addFunction("SetClipChildren", &UIElement::SetClipChildren)
        .addFunction("SetSortChildren", &UIElement::SetSortChildren)
        .addFunction("SetUseDerivedOpacity", &UIElement::SetUseDerivedOpacity)
        .addFunction("SetEnabled", &UIElement::SetEnabled)
        .addFunction("SetDeepEnabled", &UIElement::SetDeepEnabled)
        .addFunction("ResetDeepEnabled", &UIElement::ResetDeepEnabled)
        .addFunction("SetEnabledRecursive", &UIElement::SetEnabledRecursive)
        .addFunction("SetEditable", &UIElement::SetEditable)
        .addFunction("SetFocus", &UIElement::SetFocus)
        .addFunction("SetSelected", &UIElement::SetSelected)
        .addFunction("SetVisible", &UIElement::SetVisible)
        .addFunction("SetFocusMode", &UIElement::SetFocusMode)
        .addFunction("SetDragDropMode", &UIElement::SetDragDropMode)

        .addOverloadedFunctions("SetStyle",
            UIElementSetStyle(),
            static_cast<bool (UIElement::*)(const XMLElement&)>(&UIElement::SetStyle))

        .addFunction("SetStyleAuto", UIElementSetStyleAuto())
        .addFunction("SetDefaultStyle", &UIElement::SetDefaultStyle)
        .addFunction("SetLayout", UIElementSetLayout())

        .addFunction("SetLayoutMode", &UIElement::SetLayoutMode)
        .addFunction("SetLayoutSpacing", &UIElement::SetLayoutSpacing)
        .addFunction("SetLayoutBorder", &UIElement::SetLayoutBorder)
        .addFunction("SetLayoutFlexScale", &UIElement::SetLayoutFlexScale)
        .addFunction("SetIndent", &UIElement::SetIndent)
        .addFunction("SetIndentSpacing", &UIElement::SetIndentSpacing)

        .addFunction("UpdateLayout", &UIElement::UpdateLayout)

        .addFunction("DisableLayoutUpdate", &UIElement::DisableLayoutUpdate)
        .addFunction("EnableLayoutUpdate", &UIElement::EnableLayoutUpdate)
        .addFunction("BringToFront", &UIElement::BringToFront)

        .addStaticFunction("CreateChild", UIElementCreateChildOverloads())

        .addFunction("AddChild", &UIElement::AddChild)
        .addFunction("InsertChild", &UIElement::InsertChild)

        .addFunction("RemoveChild", UIElementRemoveChild())

        .addFunction("RemoveChildAtIndex", &UIElement::RemoveChildAtIndex)
        .addFunction("RemoveAllChildren", &UIElement::RemoveAllChildren)
        .addFunction("Remove", &UIElement::Remove)
        .addFunction("FindChild", &UIElement::FindChild)

        .addFunction("SetParent", UIElementSetParent())

        .addFunction("SetVar", &UIElement::SetVar)
        .addFunction("SetInternal", &UIElement::SetInternal)
        .addFunction("SetTraversalMode", &UIElement::SetTraversalMode)
        .addFunction("SetElementEventSender", &UIElement::SetElementEventSender)
        .addFunction("SetTags", &UIElement::SetTags)
        .addFunction("AddTag", &UIElement::AddTag)

        .addOverloadedFunctions("AddTags",
            UIElementAddTags(),
            static_cast<void(UIElement::*)(const StringVector&)>(&UIElement::AddTags))

        .addFunction("RemoveTag", &UIElement::RemoveTag)
        .addFunction("RemoveAllTags", &UIElement::RemoveAllTags)

        .addFunction("GetName", &UIElement::GetName)
        .addFunction("GetPosition", &UIElement::GetPosition)
        .addFunction("GetSize", &UIElement::GetSize)
        .addFunction("GetWidth", &UIElement::GetWidth)
        .addFunction("GetHeight", &UIElement::GetHeight)
        .addFunction("GetMinSize", &UIElement::GetMinSize)
        .addFunction("GetMinWidth", &UIElement::GetMinWidth)
        .addFunction("GetMinHeight", &UIElement::GetMinHeight)
        .addFunction("GetMaxSize", &UIElement::GetMaxSize)
        .addFunction("GetMaxWidth", &UIElement::GetMaxWidth)
        .addFunction("GetMaxHeight", &UIElement::GetMaxHeight)
        .addFunction("IsFixedSize", &UIElement::IsFixedSize)
        .addFunction("IsFixedWidth", &UIElement::IsFixedWidth)
        .addFunction("IsFixedHeight", &UIElement::IsFixedHeight)
        .addFunction("GetChildOffset", &UIElement::GetChildOffset)
        .addFunction("GetHorizontalAlignment", &UIElement::GetHorizontalAlignment)
        .addFunction("GetVerticalAlignment", &UIElement::GetVerticalAlignment)
        .addFunction("GetClipBorder", &UIElement::GetClipBorder)

        .addOverloadedFunctions("GetColor", &UIElementColorGetter, &UIElement::GetColor)

        .addFunction("GetPriority", &UIElement::GetPriority)
        .addFunction("GetOpacity", &UIElement::GetOpacity)
        .addFunction("GetDerivedOpacity", &UIElement::GetDerivedOpacity)
        .addFunction("GetBringToFront", &UIElement::GetBringToFront)
        .addFunction("GetBringToBack", &UIElement::GetBringToBack)
        .addFunction("GetClipChildren", &UIElement::GetClipChildren)
        .addFunction("GetSortChildren", &UIElement::GetSortChildren)
        .addFunction("GetUseDerivedOpacity", &UIElement::GetUseDerivedOpacity)
        .addFunction("HasFocus", &UIElement::HasFocus)
        .addFunction("IsEnabled", &UIElement::IsEnabled)
        .addFunction("IsEnabledSelf", &UIElement::IsEnabledSelf)
        .addFunction("IsEditable", &UIElement::IsEditable)
        .addFunction("IsSelected", &UIElement::IsSelected)
        .addFunction("IsVisible", &UIElement::IsVisible)
        .addFunction("IsVisibleEffective", &UIElement::IsVisibleEffective)
        .addFunction("IsHovering", &UIElement::IsHovering)
        .addFunction("IsInternal", &UIElement::IsInternal)
        .addFunction("HasColorGradient", &UIElement::HasColorGradient)
        .addFunction("GetFocusMode", &UIElement::GetFocusMode)
        .addFunction("GetDragDropMode", &UIElement::GetDragDropMode)
        .addFunction("GetAppliedStyle", &UIElement::GetAppliedStyle)

        .addFunction("GetDefaultStyle", UIElementGetDefaultStyle())

        .addFunction("GetLayoutMode", &UIElement::GetLayoutMode)
        .addFunction("GetLayoutSpacing", &UIElement::GetLayoutSpacing)
        .addFunction("GetLayoutBorder", &UIElement::GetLayoutBorder)
        .addFunction("GetLayoutFlexScale", &UIElement::GetLayoutFlexScale)

        .addFunction("GetNumChildren", UIElementGetNumChildren())

        .addOverloadedFunctions("GetChild", 
            &UIElementGetChild0, 
            UIElementGetChildOverloads1(), 
            UIElementGetChildOverloads2())

        .addStaticFunction("GetChildren", UIElementGetChildrenOverloads())

        .addFunction("GetParent", &UIElement::GetParent)
        .addFunction("GetRoot", &UIElement::GetRoot)
        .addFunction("GetDerivedColor", &UIElement::GetDerivedColor)
        .addFunction("GetVar", &UIElement::GetVar)
        .addFunction("GetVars", &UIElement::GetVars)
        .addFunction("HasTag", &UIElement::HasTag)
        .addFunction("GetTags", &UIElement::GetTags)

        .addStaticFunction("GetChildrenWithTag", UIElementGetChildrenWithTagOverloads())

        .addFunction("GetDragButtonCombo", &UIElement::GetDragButtonCombo)
        .addFunction("GetDragButtonCount", &UIElement::GetDragButtonCount)
        .addFunction("IsInside", &UIElement::IsInside)
        .addFunction("IsInsideCombined", &UIElement::IsInsideCombined)
        .addFunction("GetCombinedScreenRect", &UIElement::GetCombinedScreenRect)
        .addFunction("SortChildren", &UIElement::SortChildren)
        .addFunction("GetLayoutElementMaxSize", &UIElement::GetLayoutElementMaxSize)
        .addFunction("GetIndent", &UIElement::GetIndent)
        .addFunction("GetIndentSpacing", &UIElement::GetIndentSpacing)
        .addFunction("GetIndentWidth", &UIElement::GetIndentWidth)

        .addProperty("screenPosition", &UIElement::GetScreenPosition)
        .addProperty("name", &UIElement::GetName, &UIElement::SetName)
        .addProperty("position", &UIElement::GetPosition, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetPosition))
        .addProperty("size", &UIElement::GetSize, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetSize))
        .addProperty("width", &UIElement::GetWidth, &UIElement::SetWidth)
        .addProperty("height", &UIElement::GetHeight, &UIElement::SetHeight)
        .addProperty("minSize", &UIElement::GetMinSize, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetMinSize))
        .addProperty("minWidth", &UIElement::GetMinWidth, &UIElement::SetMinWidth)
        .addProperty("minHeight", &UIElement::GetMinHeight, &UIElement::SetMinHeight)
        .addProperty("maxSize", &UIElement::GetMaxSize, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetMaxSize))
        .addProperty("maxWidth", &UIElement::GetMaxWidth, &UIElement::SetMaxWidth)
        .addProperty("maxHeight", &UIElement::GetMaxHeight, &UIElement::SetMaxHeight)
        .addProperty("fixedSize", &UIElement::IsFixedSize, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetFixedSize))
        .addProperty("fixedWidth", &UIElement::IsFixedWidth, &UIElement::SetFixedWidth)
        .addProperty("fixedHeight", &UIElement::IsFixedHeight, &UIElement::SetFixedHeight)
        .addProperty("childOffset", &UIElement::GetChildOffset, &UIElement::SetChildOffset)
        .addProperty("horizontalAlignment", &UIElement::GetHorizontalAlignment, &UIElement::SetHorizontalAlignment)
        .addProperty("verticalAlignment", &UIElement::GetVerticalAlignment, &UIElement::SetVerticalAlignment)
        .addProperty("clipBorder", &UIElement::GetClipBorder, &UIElement::SetClipBorder)
        .addProperty("priority", &UIElement::GetPriority, &UIElement::SetPriority)

        .addProperty("color", &UIElementColorGetter, &UIElementColorSetter)

        .addProperty("opacity", &UIElement::GetOpacity, &UIElement::SetOpacity)
        .addProperty("derivedOpacity", &UIElement::GetDerivedOpacity)
        .addProperty("bringToFront", &UIElement::GetBringToFront, &UIElement::SetBringToFront)
        .addProperty("bringToBack", &UIElement::GetBringToBack, &UIElement::SetBringToBack)
        .addProperty("clipChildren", &UIElement::GetClipChildren, &UIElement::SetClipChildren)
        .addProperty("sortChildren", &UIElement::GetSortChildren, &UIElement::SetSortChildren)
        .addProperty("useDerivedOpacity", &UIElement::GetUseDerivedOpacity, &UIElement::SetUseDerivedOpacity)
        .addProperty("enabled", &UIElement::IsEnabled, &UIElement::SetEnabled)
        .addProperty("enabledSelf", &UIElement::IsEnabledSelf)
        .addProperty("editable", &UIElement::IsEditable, &UIElement::SetEditable)
        .addProperty("selected", &UIElement::IsSelected, &UIElement::SetSelected)
        .addProperty("visible", &UIElement::IsVisible, &UIElement::SetVisible)
        .addProperty("visibleEffective", &UIElement::IsVisibleEffective)
        .addProperty("hovering", &UIElement::IsHovering, &UIElement::SetHovering)
        .addProperty("internal", &UIElement::IsInternal, &UIElement::SetInternal)
        .addProperty("focusMode", &UIElement::GetFocusMode, &UIElement::SetFocusMode)
        .addProperty("dragDropMode", &UIElement::GetDragDropMode, &UIElement::SetDragDropMode)
        .addProperty("appliedStyle", &UIElement::GetAppliedStyle)

        .addProperty("defaultStyle", &UIElementDefaultStyleGetter, &UIElementDefaultStyleSetter)

        .addProperty("layoutMode", &UIElement::GetLayoutMode, &UIElement::SetLayoutMode)
        .addProperty("layoutSpacing", &UIElement::GetLayoutSpacing, &UIElement::SetLayoutSpacing)
        .addProperty("layoutBorder", &UIElement::GetLayoutBorder, &UIElement::SetLayoutBorder)
        .addProperty("layoutFlexScale", &UIElement::GetLayoutFlexScale, &UIElement::SetLayoutFlexScale)
        .addProperty("parent", &UIElement::GetParent)
        .addProperty("root", &UIElement::GetRoot)
        .addProperty("derivedColor", &UIElement::GetDerivedColor)
        .addProperty("dragButtonCombo", &UIElement::GetDragButtonCombo)
        .addProperty("dragButtonCount", &UIElement::GetDragButtonCount)
        .addProperty("combinedScreenRect", &UIElement::GetCombinedScreenRect)
        .addProperty("layoutElementMaxSize", &UIElement::GetLayoutElementMaxSize)
        .addProperty("indent", &UIElement::GetIndent, &UIElement::SetIndent)
        .addProperty("indentSpacing", &UIElement::GetIndentSpacing, &UIElement::SetIndentSpacing)
        .addProperty("indentWidth", &UIElement::GetIndentWidth)
        );
}
}

