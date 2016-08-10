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

static bool UIElementLoadXML(UIElement* uiElement, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return uiElement->LoadXML(*file);
}

static bool UIElementSaveXML(const UIElement* self, const String& fileName, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
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

static PODVector<UIElement*> UIElementGetChildrenWithTag(const UIElement* self, const char* tag, bool recursive = false)
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

    // [Enum] HorizontalAlignment
    lua["HA_LEFT"] = HA_LEFT;
    lua["HA_CENTER"] = HA_CENTER;
    lua["HA_RIGHT"] = HA_RIGHT;

    // [Enum] VerticalAlignment
    lua["VA_TOP"] = VA_TOP;
    lua["VA_CENTER"] = VA_CENTER;
    lua["VA_BOTTOM"] = VA_BOTTOM;

    // [Enum] Corner
    lua["C_TOPLEFT"] = C_TOPLEFT;
    lua["C_TOPRIGHT"] = C_TOPRIGHT;
    lua["C_BOTTOMLEFT"] = C_BOTTOMLEFT;
    lua["C_BOTTOMRIGHT"] = C_BOTTOMRIGHT;
    lua["MAX_UIELEMENT_CORNERS"] = MAX_UIELEMENT_CORNERS;

    // [Enum] Orientation
    lua["O_HORIZONTAL"] = O_HORIZONTAL;
    lua["O_VERTICAL"] = O_VERTICAL;

    // [Enum] FocusMode
    lua["FM_NOTFOCUSABLE"] = FM_NOTFOCUSABLE;
    lua["FM_RESETFOCUS"] = FM_RESETFOCUS;
    lua["FM_FOCUSABLE"] = FM_FOCUSABLE;
    lua["FM_FOCUSABLE_DEFOCUSABLE"] = FM_FOCUSABLE_DEFOCUSABLE;

    // [Enum] LayoutMode
    lua["LM_FREE"] = LM_FREE;
    lua["LM_HORIZONTAL"] = LM_HORIZONTAL;
    lua["LM_VERTICAL"] = LM_VERTICAL;

    // [Enum] TraversalMode
    lua["TM_BREADTH_FIRST"] = TM_BREADTH_FIRST;
    lua["TM_DEPTH_FIRST"] = TM_DEPTH_FIRST;

    // [Constant] unsigned DD_DISABLED
    lua["DD_DISABLED"] = DD_DISABLED;
    // [Constant] unsigned DD_SOURCE
    lua["DD_SOURCE"] = DD_SOURCE;
    // [Constant] unsigned DD_TARGET
    lua["DD_TARGET"] = DD_TARGET;
    // [Constant] unsigned DD_SOURCE_AND_TARGET
    lua["DD_SOURCE_AND_TARGET"] = DD_SOURCE_AND_TARGET;

    // [Class] UIElement : Animatable
    lua["UIElement"].setClass(UserdataMetatable<UIElement, Animatable>()
        // [Constructor] UIElement()
        .addStaticFunction("new", &CreateObject<UIElement>)

        // [Method] IntVector2 ScreenToElement(const IntVector2& screenPosition)
        .addFunction("ScreenToElement", &UIElement::ScreenToElement)
        // [Method] IntVector2 ElementToScreen(const IntVector2& position)
        .addFunction("ElementToScreen", &UIElement::ElementToScreen)

        // [Method] bool LoadXML(const String& fileName)
        .addStaticFunction("LoadXML", UIElementLoadXML)
        // [Method] bool SaveXML(const String& fileName, const String& indentation = "\t") const
        .addStaticFunction("SaveXML", UIElementSaveXMLOverloads())

        // [Method] void SetName(const String& name)
        .addFunction("SetName", &UIElement::SetName)

        .addOverloadedFunctions("SetPosition",
            // [Method] void SetPosition(const IntVector2& position)
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetPosition),
            // [Method] void SetPosition(int x, int y)
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetPosition))

        .addOverloadedFunctions("SetSize",
            // [Method] void SetSize(const IntVector2& size)
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetSize),
            // [Method] void SetSize(int width, int height)
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetSize))

        // [Method] void SetWidth(int width)
        .addFunction("SetWidth", &UIElement::SetWidth)
        // [Method] void SetHeight(int height)
        .addFunction("SetHeight", &UIElement::SetHeight)

        .addOverloadedFunctions("SetMinSize",
            // [Method] void SetMinSize(const IntVector2& minSize)
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetMinSize),
            // [Method] void SetMinSize(int width, int height)
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetMinSize))

        // [Method] void SetMinWidth(int width)
        .addFunction("SetMinWidth", &UIElement::SetMinWidth)
        // [Method] void SetMinHeight(int height)
        .addFunction("SetMinHeight", &UIElement::SetMinHeight)

        .addOverloadedFunctions("SetMaxSize",
            // [Method] void SetMaxSize(const IntVector2& maxSize)
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetMaxSize),
            // [Method] void SetMaxSize(int width, int height)
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetMaxSize))

        // [Method] void SetMaxWidth(int width)
        .addFunction("SetMaxWidth", &UIElement::SetMaxWidth)
        // [Method] void SetMaxHeight(int height)
        .addFunction("SetMaxHeight", &UIElement::SetMaxHeight)

        .addOverloadedFunctions("SetFixedSize",
            // [Method] void SetFixedSize(const IntVector2& size)
            static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetFixedSize),
            // [Method] void SetFixedSize(int width, int height)
            static_cast<void(UIElement::*)(int, int)>(&UIElement::SetFixedSize))

        // [Method] void SetFixedWidth(int width)
        .addFunction("SetFixedWidth", &UIElement::SetFixedWidth)
        // [Method] void SetFixedHeight(int height)
        .addFunction("SetFixedHeight", &UIElement::SetFixedHeight)
        // [Method] void SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign)
        .addFunction("SetAlignment", &UIElement::SetAlignment)
        // [Method] void SetHorizontalAlignment(HorizontalAlignment align)
        .addFunction("SetHorizontalAlignment", &UIElement::SetHorizontalAlignment)
        // [Method] void SetVerticalAlignment(VerticalAlignment align)
        .addFunction("SetVerticalAlignment", &UIElement::SetVerticalAlignment)
        // [Method] void SetClipBorder(const IntRect& rect)
        .addFunction("SetClipBorder", &UIElement::SetClipBorder)

        .addOverloadedFunctions("SetColor",
            // [Method] void SetColor(const Color& color)
            static_cast<void(UIElement::*)(const Color&)>(&UIElement::SetColor),
            // [Method] void SetColor(Corner corner, const Color& color)
            static_cast<void(UIElement::*)(Corner, const Color&)>(&UIElement::SetColor))

        // [Method] void SetPriority(int priority)
        .addFunction("SetPriority", &UIElement::SetPriority)
        // [Method] void SetOpacity(float opacity)
        .addFunction("SetOpacity", &UIElement::SetOpacity)
        // [Method] void SetBringToFront(bool enable)
        .addFunction("SetBringToFront", &UIElement::SetBringToFront)
        // [Method] void SetBringToBack(bool enable)
        .addFunction("SetBringToBack", &UIElement::SetBringToBack)
        // [Method] void SetClipChildren(bool enable)
        .addFunction("SetClipChildren", &UIElement::SetClipChildren)
        // [Method] void SetSortChildren(bool enable)
        .addFunction("SetSortChildren", &UIElement::SetSortChildren)
        // [Method] void SetUseDerivedOpacity(bool enable)
        .addFunction("SetUseDerivedOpacity", &UIElement::SetUseDerivedOpacity)
        // [Method] void SetEnabled(bool enable)
        .addFunction("SetEnabled", &UIElement::SetEnabled)
        // [Method] void SetDeepEnabled(bool enable)
        .addFunction("SetDeepEnabled", &UIElement::SetDeepEnabled)
        // [Method] void ResetDeepEnabled()
        .addFunction("ResetDeepEnabled", &UIElement::ResetDeepEnabled)
        // [Method] void SetEnabledRecursive(bool enable)
        .addFunction("SetEnabledRecursive", &UIElement::SetEnabledRecursive)
        // [Method] void SetEditable(bool enable)
        .addFunction("SetEditable", &UIElement::SetEditable)
        // [Method] void SetFocus(bool enable)
        .addFunction("SetFocus", &UIElement::SetFocus)
        // [Method] void SetSelected(bool enable)
        .addFunction("SetSelected", &UIElement::SetSelected)
        // [Method] void SetVisible(bool enable)
        .addFunction("SetVisible", &UIElement::SetVisible)
        // [Method] void SetFocusMode(FocusMode mode)
        .addFunction("SetFocusMode", &UIElement::SetFocusMode)
        // [Method] void SetDragDropMode(unsigned mode)
        .addFunction("SetDragDropMode", &UIElement::SetDragDropMode)

        .addOverloadedFunctions("SetStyle",
            // [Method] bool SetStyle(const String& styleName, XMLFile* file = 0)
            UIElementSetStyle(),
            // [Method] bool SetStyle(const XMLElement& element)
            static_cast<bool (UIElement::*)(const XMLElement&)>(&UIElement::SetStyle))

        // [Method] bool SetStyleAuto(XMLFile* file = 0)
        .addFunction("SetStyleAuto", UIElementSetStyleAuto())
        // [Method] void SetDefaultStyle(XMLFile* style)
        .addFunction("SetDefaultStyle", &UIElement::SetDefaultStyle)
        // [Method] void SetLayout(LayoutMode mode, int spacing = 0, const IntRect& border = IntRect::ZERO)
        .addFunction("SetLayout", UIElementSetLayout())

        // [Method] void SetLayoutMode(LayoutMode mode)
        .addFunction("SetLayoutMode", &UIElement::SetLayoutMode)
        // [Method] void SetLayoutSpacing(int spacing)
        .addFunction("SetLayoutSpacing", &UIElement::SetLayoutSpacing)
        // [Method] void SetLayoutBorder(const IntRect& border)
        .addFunction("SetLayoutBorder", &UIElement::SetLayoutBorder)
        // [Method] void SetLayoutFlexScale(const Vector2& scale)
        .addFunction("SetLayoutFlexScale", &UIElement::SetLayoutFlexScale)
        // [Method] void SetIndent(int indent)
        .addFunction("SetIndent", &UIElement::SetIndent)
        // [Method] void SetIndentSpacing(int indentSpacing)
        .addFunction("SetIndentSpacing", &UIElement::SetIndentSpacing)

        // [Method] void UpdateLayout()
        .addFunction("UpdateLayout", &UIElement::UpdateLayout)

        // [Method] void DisableLayoutUpdate()
        .addFunction("DisableLayoutUpdate", &UIElement::DisableLayoutUpdate)
        // [Method] void EnableLayoutUpdate()
        .addFunction("EnableLayoutUpdate", &UIElement::EnableLayoutUpdate)
        // [Method] void BringToFront()
        .addFunction("BringToFront", &UIElement::BringToFront)

        // [Method] SharedPtr<UIElement> CreateChild(StringHash type, const String& name = String::EMPTY, unsigned index = M_MAX_UNSIGNED)
        .addStaticFunction("CreateChild", UIElementCreateChildOverloads())

        // [Method] void AddChild(UIElement* element)
        .addFunction("AddChild", &UIElement::AddChild)
        // [Method] void InsertChild(unsigned index, UIElement* element)
        .addFunction("InsertChild", &UIElement::InsertChild)

        // [Method] void RemoveChild(UIElement* element, unsigned index = 0)
        .addFunction("RemoveChild", UIElementRemoveChild())

        // [Method] void RemoveChildAtIndex(unsigned index)
        .addFunction("RemoveChildAtIndex", &UIElement::RemoveChildAtIndex)
        // [Method] void RemoveAllChildren()
        .addFunction("RemoveAllChildren", &UIElement::RemoveAllChildren)
        // [Method] void Remove()
        .addFunction("Remove", &UIElement::Remove)
        // [Method] unsigned FindChild(UIElement* element) const
        .addFunction("FindChild", &UIElement::FindChild)

        // [Method] void SetParent(UIElement* parent, unsigned index = M_MAX_UNSIGNED)
        .addFunction("SetParent", UIElementSetParent())

        // [Method] void SetVar(StringHash key, const Variant& value)
        .addFunction("SetVar", &UIElement::SetVar)
        // [Method] void SetInternal(bool enable)
        .addFunction("SetInternal", &UIElement::SetInternal)
        // [Method] void SetTraversalMode(TraversalMode traversalMode)
        .addFunction("SetTraversalMode", &UIElement::SetTraversalMode)
        // [Method] void SetElementEventSender(bool flag)
        .addFunction("SetElementEventSender", &UIElement::SetElementEventSender)
        // [Method] void SetTags(const StringVector& tags)
        .addFunction("SetTags", &UIElement::SetTags)
        // [Method] void AddTag(const String& tag)
        .addFunction("AddTag", &UIElement::AddTag)

        .addOverloadedFunctions("AddTags",
            // [Method] void AddTags(const String& tags, char separator = ';')
            UIElementAddTags(),
            // [Method] void AddTags(const StringVector& tags)
            static_cast<void(UIElement::*)(const StringVector&)>(&UIElement::AddTags))

        // [Method] bool RemoveTag(const String& tag)
        .addFunction("RemoveTag", &UIElement::RemoveTag)
        // [Method] void RemoveAllTags()
        .addFunction("RemoveAllTags", &UIElement::RemoveAllTags)

        // [Method] const String& GetName() const
        .addFunction("GetName", &UIElement::GetName)
        // [Method] const IntVector2& GetPosition() const
        .addFunction("GetPosition", &UIElement::GetPosition)
        // [Method] const IntVector2& GetSize() const
        .addFunction("GetSize", &UIElement::GetSize)
        // [Method] int GetWidth() const
        .addFunction("GetWidth", &UIElement::GetWidth)
        // [Method] int GetHeight() const
        .addFunction("GetHeight", &UIElement::GetHeight)
        // [Method] const IntVector2& GetMinSize() const
        .addFunction("GetMinSize", &UIElement::GetMinSize)
        // [Method] int GetMinWidth() const
        .addFunction("GetMinWidth", &UIElement::GetMinWidth)
        // [Method] int GetMinHeight() const
        .addFunction("GetMinHeight", &UIElement::GetMinHeight)
        // [Method] const IntVector2& GetMaxSize() const
        .addFunction("GetMaxSize", &UIElement::GetMaxSize)
        // [Method] int GetMaxWidth() const
        .addFunction("GetMaxWidth", &UIElement::GetMaxWidth)
        // [Method] int GetMaxHeight() const
        .addFunction("GetMaxHeight", &UIElement::GetMaxHeight)
        // [Method] bool IsFixedSize() const
        .addFunction("IsFixedSize", &UIElement::IsFixedSize)
        // [Method] bool IsFixedWidth() const
        .addFunction("IsFixedWidth", &UIElement::IsFixedWidth)
        // [Method] bool IsFixedHeight() const
        .addFunction("IsFixedHeight", &UIElement::IsFixedHeight)
        // [Method] const IntVector2& GetChildOffset() const
        .addFunction("GetChildOffset", &UIElement::GetChildOffset)
        // [Method] HorizontalAlignment GetHorizontalAlignment() const
        .addFunction("GetHorizontalAlignment", &UIElement::GetHorizontalAlignment)
        // [Method] VerticalAlignment GetVerticalAlignment() const
        .addFunction("GetVerticalAlignment", &UIElement::GetVerticalAlignment)
        // [Method] const IntRect& GetClipBorder() const
        .addFunction("GetClipBorder", &UIElement::GetClipBorder)

        .addOverloadedFunctions("GetColor", 
            // [Method] const Color& GetColor() const
            &UIElementColorGetter, 
            // [Method] const Color& GetColor(Corner corner) const
            &UIElement::GetColor)

        // [Method] int GetPriority() const
        .addFunction("GetPriority", &UIElement::GetPriority)
        // [Method] float GetOpacity() const
        .addFunction("GetOpacity", &UIElement::GetOpacity)
        // [Method] float GetDerivedOpacity() const
        .addFunction("GetDerivedOpacity", &UIElement::GetDerivedOpacity)
        // [Method] bool GetBringToFront() const
        .addFunction("GetBringToFront", &UIElement::GetBringToFront)
        // [Method] bool GetBringToBack() const
        .addFunction("GetBringToBack", &UIElement::GetBringToBack)
        // [Method] bool GetClipChildren() const
        .addFunction("GetClipChildren", &UIElement::GetClipChildren)
        // [Method] bool GetSortChildren() const
        .addFunction("GetSortChildren", &UIElement::GetSortChildren)
        // [Method] bool GetUseDerivedOpacity() const
        .addFunction("GetUseDerivedOpacity", &UIElement::GetUseDerivedOpacity)
        // [Method] bool HasFocus() const
        .addFunction("HasFocus", &UIElement::HasFocus)
        // [Method] bool IsEnabled() const
        .addFunction("IsEnabled", &UIElement::IsEnabled)
        // [Method] bool IsEnabledSelf() const
        .addFunction("IsEnabledSelf", &UIElement::IsEnabledSelf)
        // [Method] bool IsEditable() const
        .addFunction("IsEditable", &UIElement::IsEditable)
        // [Method] bool IsSelected() const
        .addFunction("IsSelected", &UIElement::IsSelected)
        // [Method] bool IsVisible() const
        .addFunction("IsVisible", &UIElement::IsVisible)
        // [Method] bool IsVisibleEffective() const
        .addFunction("IsVisibleEffective", &UIElement::IsVisibleEffective)
        // [Method] bool IsHovering() const
        .addFunction("IsHovering", &UIElement::IsHovering)
        // [Method] bool IsInternal() const
        .addFunction("IsInternal", &UIElement::IsInternal)
        // [Method] bool HasColorGradient() const
        .addFunction("HasColorGradient", &UIElement::HasColorGradient)
        // [Method] FocusMode GetFocusMode() const
        .addFunction("GetFocusMode", &UIElement::GetFocusMode)
        // [Method] unsigned GetDragDropMode() const
        .addFunction("GetDragDropMode", &UIElement::GetDragDropMode)
        // [Method] const String& GetAppliedStyle() const
        .addFunction("GetAppliedStyle", &UIElement::GetAppliedStyle)

        // [Method] XMLFile* GetDefaultStyle(bool recursiveUp = true) const
        .addFunction("GetDefaultStyle", UIElementGetDefaultStyle())

        // [Method] LayoutMode GetLayoutMode() const
        .addFunction("GetLayoutMode", &UIElement::GetLayoutMode)
        // [Method] int GetLayoutSpacing() const
        .addFunction("GetLayoutSpacing", &UIElement::GetLayoutSpacing)
        // [Method] const IntRect& GetLayoutBorder() const
        .addFunction("GetLayoutBorder", &UIElement::GetLayoutBorder)
        // [Method] const Vector2& GetLayoutFlexScale() const
        .addFunction("GetLayoutFlexScale", &UIElement::GetLayoutFlexScale)

        // [Method] unsigned GetNumChildren(bool recursive = false) const
        .addFunction("GetNumChildren", UIElementGetNumChildren())

        .addOverloadedFunctions("GetChild", 
            // [Method] UIElement* GetChild(unsigned index) const
            &UIElementGetChild0, 
            // [Method] SharedPtr<UIElement> GetChild(const String& name, bool recursive = false) const
            UIElementGetChildOverloads1(), 
            // [Method] SharedPtr<UIElement> GetChild(const StringHash& key, const Variant& value = Variant::EMPTY, bool recursive = false) const
            UIElementGetChildOverloads2())

        // [Method] PODVector<UIElement*> GetChildren(const UIElement* self, bool recursive = false)
        .addStaticFunction("GetChildren", UIElementGetChildrenOverloads())

        // [Method] UIElement* GetParent() const
        .addFunction("GetParent", &UIElement::GetParent)
        // [Method] UIElement* GetRoot() const
        .addFunction("GetRoot", &UIElement::GetRoot)
        // [Method] const Color& GetDerivedColor() const
        .addFunction("GetDerivedColor", &UIElement::GetDerivedColor)
        // [Method] const Variant& GetVar(const StringHash& key) const
        .addFunction("GetVar", &UIElement::GetVar)
        // [Method] const VariantMap& GetVars() const
        .addFunction("GetVars", &UIElement::GetVars)
        // [Method] bool HasTag(const String& tag) const
        .addFunction("HasTag", &UIElement::HasTag)
        // [Method] const StringVector& GetTags() const
        .addFunction("GetTags", &UIElement::GetTags)

        // [Method] PODVector<UIElement*> GetChildrenWithTag(const char* tag, bool recursive = false) const
        .addStaticFunction("GetChildrenWithTag", UIElementGetChildrenWithTagOverloads())

        // [Method] int GetDragButtonCombo() const
        .addFunction("GetDragButtonCombo", &UIElement::GetDragButtonCombo)
        // [Method] unsigned GetDragButtonCount() const
        .addFunction("GetDragButtonCount", &UIElement::GetDragButtonCount)
        // [Method] bool IsInside(IntVector2 position, bool isScreen)
        .addFunction("IsInside", &UIElement::IsInside)
        // [Method] bool IsInsideCombined(IntVector2 position, bool isScreen)
        .addFunction("IsInsideCombined", &UIElement::IsInsideCombined)
        // [Method] IntRect GetCombinedScreenRect()
        .addFunction("GetCombinedScreenRect", &UIElement::GetCombinedScreenRect)
        // [Method] void SortChildren()
        .addFunction("SortChildren", &UIElement::SortChildren)
        // [Method] int GetLayoutElementMaxSize() const
        .addFunction("GetLayoutElementMaxSize", &UIElement::GetLayoutElementMaxSize)
        // [Method] int GetIndent() const
        .addFunction("GetIndent", &UIElement::GetIndent)
        // [Method] int GetIndentSpacing() const
        .addFunction("GetIndentSpacing", &UIElement::GetIndentSpacing)
        // [Method] int GetIndentWidth() const
        .addFunction("GetIndentWidth", &UIElement::GetIndentWidth)

        // [Property(Readonly)] const IntVector2& screenPosition
        .addProperty("screenPosition", &UIElement::GetScreenPosition)
        // [Property] const String& name
        .addProperty("name", &UIElement::GetName, &UIElement::SetName)
        // [Property] const IntVector2& position
        .addProperty("position", &UIElement::GetPosition, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetPosition))
        // [Property] const IntVector2& size
        .addProperty("size", &UIElement::GetSize, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetSize))
        // [Property] int width
        .addProperty("width", &UIElement::GetWidth, &UIElement::SetWidth)
        // [Property] int height
        .addProperty("height", &UIElement::GetHeight, &UIElement::SetHeight)
        // [Property] const IntVector2& minSize
        .addProperty("minSize", &UIElement::GetMinSize, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetMinSize))
        // [Property] int minWidth
        .addProperty("minWidth", &UIElement::GetMinWidth, &UIElement::SetMinWidth)
        // [Property] int minHeight
        .addProperty("minHeight", &UIElement::GetMinHeight, &UIElement::SetMinHeight)
        // [Property] const IntVector2& maxSize
        .addProperty("maxSize", &UIElement::GetMaxSize, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetMaxSize))
        // [Property] int maxWidth
        .addProperty("maxWidth", &UIElement::GetMaxWidth, &UIElement::SetMaxWidth)
        // [Property] int maxHeight
        .addProperty("maxHeight", &UIElement::GetMaxHeight, &UIElement::SetMaxHeight)
        // [Property] bool fixedSize
        .addProperty("fixedSize", &UIElement::IsFixedSize, static_cast<void(UIElement::*)(const IntVector2&)>(&UIElement::SetFixedSize))
        // [Property] bool fixedWidth
        .addProperty("fixedWidth", &UIElement::IsFixedWidth, &UIElement::SetFixedWidth)
        // [Property] bool fixedHeight
        .addProperty("fixedHeight", &UIElement::IsFixedHeight, &UIElement::SetFixedHeight)
        // [Property] const IntVector2& childOffset
        .addProperty("childOffset", &UIElement::GetChildOffset, &UIElement::SetChildOffset)
        // [Property] HorizontalAlignment horizontalAlignment
        .addProperty("horizontalAlignment", &UIElement::GetHorizontalAlignment, &UIElement::SetHorizontalAlignment)
        // [Property] VerticalAlignment verticalAlignment
        .addProperty("verticalAlignment", &UIElement::GetVerticalAlignment, &UIElement::SetVerticalAlignment)
        // [Property] const IntRect& clipBorder
        .addProperty("clipBorder", &UIElement::GetClipBorder, &UIElement::SetClipBorder)
        // [Property] int priority
        .addProperty("priority", &UIElement::GetPriority, &UIElement::SetPriority)

        // [Property] Color color
        .addProperty("color", &UIElementColorGetter, &UIElementColorSetter)

        // [Property] float opacity
        .addProperty("opacity", &UIElement::GetOpacity, &UIElement::SetOpacity)
        // [Property(Readonly)] float derivedOpacity
        .addProperty("derivedOpacity", &UIElement::GetDerivedOpacity)
        // [Property] bool bringToFront
        .addProperty("bringToFront", &UIElement::GetBringToFront, &UIElement::SetBringToFront)
        // [Property] bool bringToBack
        .addProperty("bringToBack", &UIElement::GetBringToBack, &UIElement::SetBringToBack)
        // [Property] bool clipChildren
        .addProperty("clipChildren", &UIElement::GetClipChildren, &UIElement::SetClipChildren)
        // [Property] bool sortChildren
        .addProperty("sortChildren", &UIElement::GetSortChildren, &UIElement::SetSortChildren)
        // [Property] bool useDerivedOpacity
        .addProperty("useDerivedOpacity", &UIElement::GetUseDerivedOpacity, &UIElement::SetUseDerivedOpacity)
        // [Property] bool enabled
        .addProperty("enabled", &UIElement::IsEnabled, &UIElement::SetEnabled)
        // [Property(Readonly)] bool enabledSelf
        .addProperty("enabledSelf", &UIElement::IsEnabledSelf)
        // [Property] bool editable
        .addProperty("editable", &UIElement::IsEditable, &UIElement::SetEditable)
        // [Property] bool selected
        .addProperty("selected", &UIElement::IsSelected, &UIElement::SetSelected)
        // [Property] bool visible
        .addProperty("visible", &UIElement::IsVisible, &UIElement::SetVisible)
        // [Property(Readonly)] bool visibleEffective
        .addProperty("visibleEffective", &UIElement::IsVisibleEffective)
        // [Property] bool hovering
        .addProperty("hovering", &UIElement::IsHovering, &UIElement::SetHovering)
        // [Property] bool internal
        .addProperty("internal", &UIElement::IsInternal, &UIElement::SetInternal)
        // [Property] FocusMode focusMode
        .addProperty("focusMode", &UIElement::GetFocusMode, &UIElement::SetFocusMode)
        // [Property] unsigned dragDropMode
        .addProperty("dragDropMode", &UIElement::GetDragDropMode, &UIElement::SetDragDropMode)
        // [Property(Readonly)] const String& appliedStyle
        .addProperty("appliedStyle", &UIElement::GetAppliedStyle)

        // [Property] XMLFile* defaultStyle
        .addProperty("defaultStyle", &UIElementDefaultStyleGetter, &UIElementDefaultStyleSetter)

        // [Property] LayoutMode layoutMode
        .addProperty("layoutMode", &UIElement::GetLayoutMode, &UIElement::SetLayoutMode)
        // [Property] int layoutSpacing
        .addProperty("layoutSpacing", &UIElement::GetLayoutSpacing, &UIElement::SetLayoutSpacing)
        // [Property] const IntRect& layoutBorder
        .addProperty("layoutBorder", &UIElement::GetLayoutBorder, &UIElement::SetLayoutBorder)
        // [Property] const Vector2& layoutFlexScale
        .addProperty("layoutFlexScale", &UIElement::GetLayoutFlexScale, &UIElement::SetLayoutFlexScale)
        // [Property(Readonly)] UIElement* parent
        .addProperty("parent", &UIElement::GetParent)
        // [Property(Readonly)] UIElement* root
        .addProperty("root", &UIElement::GetRoot)
        // [Property(Readonly)] const Color& derivedColor
        .addProperty("derivedColor", &UIElement::GetDerivedColor)
        // [Property(Readonly)] int dragButtonCombo
        .addProperty("dragButtonCombo", &UIElement::GetDragButtonCombo)
        // [Property(Readonly)] unsigned dragButtonCount
        .addProperty("dragButtonCount", &UIElement::GetDragButtonCount)
        // [Property(Readonly)] IntRect combinedScreenRect
        .addProperty("combinedScreenRect", &UIElement::GetCombinedScreenRect)
        // [Property(Readonly)] int layoutElementMaxSize
        .addProperty("layoutElementMaxSize", &UIElement::GetLayoutElementMaxSize)
        // [Property] int indent
        .addProperty("indent", &UIElement::GetIndent, &UIElement::SetIndent)
        // [Property] int indentSpacing
        .addProperty("indentSpacing", &UIElement::GetIndentSpacing, &UIElement::SetIndentSpacing)
        // [Property(Readonly)] int indentWidth
        .addProperty("indentWidth", &UIElement::GetIndentWidth)
        );
}
}

