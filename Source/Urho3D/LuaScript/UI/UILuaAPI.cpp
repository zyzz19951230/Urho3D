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

static SharedPtr<UIElement> UILoadLayout0(UI* self, const char* filepath, XMLFile* styleFile = 0)
{
    SharedPtr<File> file(new File(globalContext, filepath));
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

static bool UISaveLayout(UI* self, const char* filepath, UIElement* element)
{
    if (!element)
        return false;
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
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

    lua["UI"].setClass(UserdataMetatable<UI, Object>()

        .addFunction("SetCursor", &UI::SetCursor)

        .addFunction("SetFocusElement", UISetFocusElement())

        .addFunction("SetModalElement", &UI::SetModalElement)
        .addFunction("Clear", &UI::Clear)

        .addFunction("DebugDraw", &UI::DebugDraw)

        .addOverloadedFunctions("LoadLayout", UILoadLayoutOverloads0(), UILoadLayoutOverloads1())

        .addStaticFunction("SaveLayout", &UISaveLayout)

        .addFunction("SetClipboardText", &UI::SetClipboardText)
        .addFunction("SetDoubleClickInterval", &UI::SetDoubleClickInterval)
        .addFunction("SetDragBeginInterval", &UI::SetDragBeginInterval)
        .addFunction("SetDragBeginDistance", &UI::SetDragBeginDistance)
        .addFunction("SetDefaultToolTipDelay", &UI::SetDefaultToolTipDelay)
        .addFunction("SetMaxFontTextureSize", &UI::SetMaxFontTextureSize)
        .addFunction("SetNonFocusedMouseWheel", &UI::SetNonFocusedMouseWheel)
        .addFunction("SetUseSystemClipboard", &UI::SetUseSystemClipboard)
        .addFunction("SetUseScreenKeyboard", &UI::SetUseScreenKeyboard)
        .addFunction("SetUseMutableGlyphs", &UI::SetUseMutableGlyphs)
        .addFunction("SetForceAutoHint", &UI::SetForceAutoHint)
        .addFunction("SetScale", &UI::SetScale)
        .addFunction("SetWidth", &UI::SetWidth)
        .addFunction("SetHeight", &UI::SetHeight)

        .addStaticFunction("GetRoot", &UIGetRoot)
        .addStaticFunction("GetRootModalElement", &UIGetRootModalElement)
        .addFunction("GetCursor", &UI::GetCursor)
        .addFunction("GetCursorPosition", &UI::GetCursorPosition)

        .addOverloadedFunctions("GetElementAt", UIGetElementAtOverloads0(), UIGetElementAtOverloads1())

        .addStaticFunction("GetFocusElement", &UIGetFocusElement)
        .addStaticFunction("GetFrontElement", &UIGetFrontElement)

        .addFunction("GetNumDragElements", &UI::GetNumDragElements)
        .addStaticFunction("GetDragElement", &UIGetDragElement)

        .addFunction("GetClipboardText", &UI::GetClipboardText)
        .addFunction("GetDoubleClickInterval", &UI::GetDoubleClickInterval)
        .addFunction("GetDragBeginInterval", &UI::GetDragBeginInterval)
        .addFunction("GetDragBeginDistance", &UI::GetDragBeginDistance)
        .addFunction("GetDefaultToolTipDelay", &UI::GetDefaultToolTipDelay)
        .addFunction("GetMaxFontTextureSize", &UI::GetMaxFontTextureSize)
        .addFunction("IsNonFocusedMouseWheel", &UI::IsNonFocusedMouseWheel)
        .addFunction("GetUseSystemClipboard", &UI::GetUseSystemClipboard)
        .addFunction("GetUseScreenKeyboard", &UI::GetUseScreenKeyboard)
        .addFunction("GetUseMutableGlyphs", &UI::GetUseMutableGlyphs)
        .addFunction("GetForceAutoHint", &UI::GetForceAutoHint)
        .addFunction("HasModalElement", &UI::HasModalElement)
        .addFunction("IsDragging", &UI::IsDragging)
        .addFunction("GetScale", &UI::GetScale)

        .addProperty("root", &UIGetRoot)
        .addProperty("rootModalElement", &UIGetRootModalElement)
        .addProperty("cursor", &UI::GetCursor, &UI::SetCursor)
        .addProperty("cursorPosition", &UI::GetCursorPosition)
        .addProperty("focusElement", &UIGetFocusElement)
        .addProperty("frontElement", &UIGetFrontElement)

        .addProperty("numDragElements", &UI::GetNumDragElements)

        .addProperty("clipboardText", &UI::GetClipboardText, &UI::SetClipboardText)
        .addProperty("doubleClickInterval", &UI::GetDoubleClickInterval, &UI::SetDoubleClickInterval)
        .addProperty("dragBeginInterval", &UI::GetDragBeginInterval, &UI::SetDragBeginInterval)
        .addProperty("dragBeginDistance", &UI::GetDragBeginDistance, &UI::SetDragBeginDistance)
        .addProperty("defaultToolTipDelay", &UI::GetDefaultToolTipDelay, &UI::SetDefaultToolTipDelay)
        .addProperty("maxFontTextureSize", &UI::GetMaxFontTextureSize, &UI::SetMaxFontTextureSize)
        .addProperty("nonFocusedMouseWheel", &UI::IsNonFocusedMouseWheel, &UI::SetNonFocusedMouseWheel)
        .addProperty("useSystemClipboard", &UI::GetUseSystemClipboard, &UI::SetUseSystemClipboard)
        .addProperty("useScreenKeyboard", &UI::GetUseScreenKeyboard, &UI::SetUseScreenKeyboard)
        .addProperty("useMutableGlyphs", &UI::GetUseMutableGlyphs, &UI::SetUseMutableGlyphs)
        .addProperty("forceAutoHint", &UI::GetForceAutoHint, &UI::SetForceAutoHint)
        .addProperty("hasModalElement", &UI::HasModalElement)
        .addProperty("dragging", &UI::IsDragging)
        .addProperty("scale", &UI::GetScale, &UI::SetScale)
        );
}
}

