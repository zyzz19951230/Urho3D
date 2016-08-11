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

#include "../../UI/UI.h"
#include "../../IO/File.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(UISetFocusElement, UI, SetFocusElement, 1, 2);

static SharedPtr<UIElement> UILoadLayout0(UI* self, const String& fileName, XMLFile* styleFile = 0)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return SharedPtr<UIElement>();

    return self->LoadLayout(*file, styleFile);
}

static SharedPtr<UIElement> UILoadLayout1(UI* self, XMLFile* file, XMLFile* styleFile = 0)
{
    return self->LoadLayout(file, styleFile);
}

KAGUYA_FUNCTION_OVERLOADS(UILoadLayoutOverloads0, UILoadLayout0, 2, 3);
KAGUYA_FUNCTION_OVERLOADS(UILoadLayoutOverloads1, UILoadLayout1, 2, 3);

static bool UISaveLayout(UI* self, const String& fileName, UIElement* element)
{
    if (!element)
        return false;
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveLayout(*file, element);
}

static SharedPtr<UIElement> UIGetRoot(const UI* self)
{
    return SharedPtr<UIElement>(self->GetRoot());
}

static SharedPtr<UIElement> UIGetRootModalElement(const UI* self)
{
    return SharedPtr<UIElement>(self->GetRootModalElement());
}

static SharedPtr<UIElement> UIGetElementAt0(UI* self, const IntVector2& position, bool enabledOnly = true)
{
    return SharedPtr<UIElement>(self->GetElementAt(position, enabledOnly));
}

static SharedPtr<UIElement> UIGetElementAt1(UI* self, int x, int y, bool enabledOnly = true)
{
    return SharedPtr<UIElement>(self->GetElementAt(x, y, enabledOnly));
}

KAGUYA_FUNCTION_OVERLOADS(UIGetElementAtOverloads0, UIGetElementAt0, 2, 3);
KAGUYA_FUNCTION_OVERLOADS(UIGetElementAtOverloads1, UIGetElementAt1, 3, 4);

static SharedPtr<UIElement> UIGetFocusElement(const UI* self)
{
    return SharedPtr<UIElement>(self->GetFocusElement());
}

static SharedPtr<UIElement> UIGetFrontElement(const UI* self)
{
    return SharedPtr<UIElement>(self->GetFrontElement());
}

static SharedPtr<UIElement> UIGetDragElement(UI* self, unsigned index)
{
    return SharedPtr<UIElement>(self->GetDragElement(index));
}

void RegisterUI(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] UI : Object
    lua["UI"].setClass(UserdataMetatable<UI, Object>()

        // [Method] void SetCursor(Cursor* cursor)
        .addFunction("SetCursor", &UI::SetCursor)

        // [Method] void SetFocusElement(UIElement* element, bool byKey = false)
        .addFunction("SetFocusElement", UISetFocusElement())

        // [Method] bool SetModalElement(UIElement* modalElement, bool enable)
        .addFunction("SetModalElement", &UI::SetModalElement)
        // [Method] void Clear()
        .addFunction("Clear", &UI::Clear)

        // [Method] void DebugDraw(UIElement* element)
        .addFunction("DebugDraw", &UI::DebugDraw)

        .addOverloadedFunctions("LoadLayout", 
            // [Method] SharedPtr<UIElement> LoadLayout(const String& fileName, XMLFile* styleFile = 0)
            UILoadLayoutOverloads0(), 
            // [Method] SharedPtr<UIElement> LoadLayout(XMLFile* file, XMLFile* styleFile = 0)
            UILoadLayoutOverloads1())

        // [Method] bool SaveLayout(const String& fileName, UIElement* element)
        .addStaticFunction("SaveLayout", &UISaveLayout)

        // [Method] void SetClipboardText(const String& text)
        .addFunction("SetClipboardText", &UI::SetClipboardText)
        // [Method] void SetDoubleClickInterval(float interval)
        .addFunction("SetDoubleClickInterval", &UI::SetDoubleClickInterval)
        // [Method] void SetDragBeginInterval(float interval)
        .addFunction("SetDragBeginInterval", &UI::SetDragBeginInterval)
        // [Method] void SetDragBeginDistance(int pixels)
        .addFunction("SetDragBeginDistance", &UI::SetDragBeginDistance)
        // [Method] void SetDefaultToolTipDelay(float delay)
        .addFunction("SetDefaultToolTipDelay", &UI::SetDefaultToolTipDelay)
        // [Method] void SetMaxFontTextureSize(int size)
        .addFunction("SetMaxFontTextureSize", &UI::SetMaxFontTextureSize)
        // [Method] void SetNonFocusedMouseWheel(bool nonFocusedMouseWheel)
        .addFunction("SetNonFocusedMouseWheel", &UI::SetNonFocusedMouseWheel)
        // [Method] void SetUseSystemClipboard(bool enable)
        .addFunction("SetUseSystemClipboard", &UI::SetUseSystemClipboard)
        // [Method] void SetUseScreenKeyboard(bool enable)
        .addFunction("SetUseScreenKeyboard", &UI::SetUseScreenKeyboard)
        // [Method] void SetUseMutableGlyphs(bool enable)
        .addFunction("SetUseMutableGlyphs", &UI::SetUseMutableGlyphs)
        // [Method] void SetForceAutoHint(bool enable)
        .addFunction("SetForceAutoHint", &UI::SetForceAutoHint)
        // [Method] void SetScale(float scale)
        .addFunction("SetScale", &UI::SetScale)
        // [Method] void SetWidth(float size)
        .addFunction("SetWidth", &UI::SetWidth)
        // [Method] void SetHeight(float size)
        .addFunction("SetHeight", &UI::SetHeight)

        // [Method] SharedPtr<UIElement> GetRoot() const
        .addStaticFunction("GetRoot", &UIGetRoot)
        // [Method] SharedPtr<UIElement> GetRootModalElement() const
        .addStaticFunction("GetRootModalElement", &UIGetRootModalElement)
        // [Method] Cursor* GetCursor() const
        .addFunction("GetCursor", &UI::GetCursor)
        // [Method] IntVector2 GetCursorPosition() const
        .addFunction("GetCursorPosition", &UI::GetCursorPosition)

        .addOverloadedFunctions("GetElementAt", 
            // [Method] 
            UIGetElementAtOverloads0(), 
            // [Method] 
            UIGetElementAtOverloads1())

        // [Method] SharedPtr<UIElement> GetFocusElement() const
        .addStaticFunction("GetFocusElement", &UIGetFocusElement)
        // [Method] SharedPtr<UIElement> GetFrontElement() const
        .addStaticFunction("GetFrontElement", &UIGetFrontElement)

        // [Method] unsigned GetNumDragElements() const
        .addFunction("GetNumDragElements", &UI::GetNumDragElements)
        // [Method] SharedPtr<UIElement> GetDragElement(unsigned index)
        .addStaticFunction("GetDragElement", &UIGetDragElement)

        // [Method] const String& GetClipboardText() const
        .addFunction("GetClipboardText", &UI::GetClipboardText)
        // [Method] float GetDoubleClickInterval() const
        .addFunction("GetDoubleClickInterval", &UI::GetDoubleClickInterval)
        // [Method] float GetDragBeginInterval() const
        .addFunction("GetDragBeginInterval", &UI::GetDragBeginInterval)
        // [Method] int GetDragBeginDistance() const
        .addFunction("GetDragBeginDistance", &UI::GetDragBeginDistance)
        // [Method] float GetDefaultToolTipDelay() const
        .addFunction("GetDefaultToolTipDelay", &UI::GetDefaultToolTipDelay)
        // [Method] int GetMaxFontTextureSize() const
        .addFunction("GetMaxFontTextureSize", &UI::GetMaxFontTextureSize)
        // [Method] bool IsNonFocusedMouseWheel() const
        .addFunction("IsNonFocusedMouseWheel", &UI::IsNonFocusedMouseWheel)
        // [Method] bool GetUseSystemClipboard() const
        .addFunction("GetUseSystemClipboard", &UI::GetUseSystemClipboard)
        // [Method] bool GetUseScreenKeyboard() const
        .addFunction("GetUseScreenKeyboard", &UI::GetUseScreenKeyboard)
        // [Method] bool GetUseMutableGlyphs() const
        .addFunction("GetUseMutableGlyphs", &UI::GetUseMutableGlyphs)
        // [Method] bool GetForceAutoHint() const
        .addFunction("GetForceAutoHint", &UI::GetForceAutoHint)
        // [Method] bool HasModalElement() const
        .addFunction("HasModalElement", &UI::HasModalElement)
        // [Method] bool IsDragging() const
        .addFunction("IsDragging", &UI::IsDragging)
        // [Method] float GetScale() const
        .addFunction("GetScale", &UI::GetScale)

        // [Property(Readonly)] SharedPtr<UIElement> root
        .addProperty("root", &UIGetRoot)
        // [Property(Readonly)] SharedPtr<UIElement> rootModalElement
        .addProperty("rootModalElement", &UIGetRootModalElement)
        // [Property] Cursor* cursor
        .addProperty("cursor", &UI::GetCursor, &UI::SetCursor)
        // [Property(Readonly)] IntVector2 cursorPosition
        .addProperty("cursorPosition", &UI::GetCursorPosition)
        // [Property(Readonly)] SharedPtr<UIElement> focusElement
        .addProperty("focusElement", &UIGetFocusElement)
        // [Property(Readonly)] SharedPtr<UIElement> frontElement
        .addProperty("frontElement", &UIGetFrontElement)

        // [Property(Readonly)] unsigned numDragElements
        .addProperty("numDragElements", &UI::GetNumDragElements)

        // [Property] const String& clipboardText
        .addProperty("clipboardText", &UI::GetClipboardText, &UI::SetClipboardText)
        // [Property] float doubleClickInterval
        .addProperty("doubleClickInterval", &UI::GetDoubleClickInterval, &UI::SetDoubleClickInterval)
        // [Property] float dragBeginInterval
        .addProperty("dragBeginInterval", &UI::GetDragBeginInterval, &UI::SetDragBeginInterval)
        // [Property] int dragBeginDistance
        .addProperty("dragBeginDistance", &UI::GetDragBeginDistance, &UI::SetDragBeginDistance)
        // [Property] float defaultToolTipDelay
        .addProperty("defaultToolTipDelay", &UI::GetDefaultToolTipDelay, &UI::SetDefaultToolTipDelay)
        // [Property] int maxFontTextureSize
        .addProperty("maxFontTextureSize", &UI::GetMaxFontTextureSize, &UI::SetMaxFontTextureSize)
        // [Property] bool nonFocusedMouseWheel
        .addProperty("nonFocusedMouseWheel", &UI::IsNonFocusedMouseWheel, &UI::SetNonFocusedMouseWheel)
        // [Property] bool useSystemClipboard
        .addProperty("useSystemClipboard", &UI::GetUseSystemClipboard, &UI::SetUseSystemClipboard)
        // [Property] bool useScreenKeyboard
        .addProperty("useScreenKeyboard", &UI::GetUseScreenKeyboard, &UI::SetUseScreenKeyboard)
        // [Property] bool useMutableGlyphs
        .addProperty("useMutableGlyphs", &UI::GetUseMutableGlyphs, &UI::SetUseMutableGlyphs)
        // [Property] bool forceAutoHint
        .addProperty("forceAutoHint", &UI::GetForceAutoHint, &UI::SetForceAutoHint)
        // [Property(Readonly)] bool hasModalElement
        .addProperty("hasModalElement", &UI::HasModalElement)
        // [Property(Readonly)] bool dragging
        .addProperty("dragging", &UI::IsDragging)
        // [Property] float scale
        .addProperty("scale", &UI::GetScale, &UI::SetScale)
        );

    // [Variable] UI* ui
    lua["ui"] = GetSubsystem<UI>();
    // [Function] UI* GetUI()
    lua["GetUI"] = static_cast<UI*(*)()>(&GetSubsystem<UI>);
}
}

