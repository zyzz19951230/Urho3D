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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/File.h"
#include "../LuaScript/LuaScriptUtils.h"
#include "../UI/BorderImage.h"
#include "../UI/Button.h"
#include "../UI/CheckBox.h"
#include "../UI/Cursor.h"
#include "../UI/DropDownList.h"
#include "../UI/FileSelector.h"
#include "../UI/Font.h"
#include "../UI/LineEdit.h"
#include "../UI/ListView.h"
#include "../UI/Menu.h"
#include "../UI/MessageBox.h"
#include "../UI/ScrollBar.h"
#include "../UI/ScrollView.h"
#include "../UI/Slider.h"
#include "../UI/Sprite.h"
#include "../UI/Text.h"
#include "../UI/Text3D.h"
#include "../UI/ToolTip.h"
#include "../UI/UI.h"
#include "../UI/UIElement.h"
#include "../UI/View3D.h"
#include "../UI/Window.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterBorderImage(kaguya::State& lua)
{
    using namespace kaguya;

    lua["BorderImage"].setClass(UserdataMetatable<BorderImage, UIElement>()
        .addStaticFunction("new", &CreateObject<BorderImage>)

        .addFunction("SetTexture", &BorderImage::SetTexture)
        .addFunction("SetImageRect", &BorderImage::SetImageRect)
        .addFunction("SetFullImageRect", &BorderImage::SetFullImageRect)
        .addFunction("SetBorder", &BorderImage::SetBorder)
        .addFunction("SetImageBorder", &BorderImage::SetImageBorder)

        .addOverloadedFunctions("SetHoverOffset",
            static_cast<void(BorderImage::*)(const IntVector2&)>(&BorderImage::SetHoverOffset),
            static_cast<void(BorderImage::*)(int, int)>(&BorderImage::SetHoverOffset))

        .addFunction("SetBlendMode", &BorderImage::SetBlendMode)
        .addFunction("SetTiled", &BorderImage::SetTiled)

        .addFunction("GetTexture", &BorderImage::GetTexture)
        .addFunction("GetImageRect", &BorderImage::GetImageRect)
        .addFunction("GetBorder", &BorderImage::GetBorder)
        .addFunction("GetImageBorder", &BorderImage::GetImageBorder)
        .addFunction("GetHoverOffset", &BorderImage::GetHoverOffset)
        .addFunction("GetBlendMode", &BorderImage::GetBlendMode)
        .addFunction("IsTiled", &BorderImage::IsTiled)

        .addProperty("texture", &BorderImage::GetTexture, &BorderImage::SetTexture)
        .addProperty("imageRect", &BorderImage::GetImageRect, &BorderImage::SetImageRect)
        .addProperty("border", &BorderImage::GetBorder, &BorderImage::SetBorder)
        .addProperty("imageBorder", &BorderImage::GetImageBorder, &BorderImage::SetImageBorder)
        .addProperty("hoverOffset", &BorderImage::GetHoverOffset, static_cast<void(BorderImage::*)(const IntVector2&)>(&BorderImage::SetHoverOffset))
        .addProperty("blendMode", &BorderImage::GetBlendMode, &BorderImage::SetBlendMode)
        .addProperty("tiled", &BorderImage::IsTiled, &BorderImage::SetTiled)
    );
}

static void RegisterButton(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Button"].setClass(UserdataMetatable<Button, BorderImage>()
        .addStaticFunction("new", &CreateObject<Button>)

        .addOverloadedFunctions("SetPressedOffset",
            static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedOffset),
            static_cast<void(Button::*)(int, int)>(&Button::SetPressedOffset))

        .addOverloadedFunctions("SetPressedChildOffset",
            static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedChildOffset),
            static_cast<void(Button::*)(int, int)>(&Button::SetPressedChildOffset))

        .addFunction("SetRepeat", &Button::SetRepeat)
        .addFunction("SetRepeatDelay", &Button::SetRepeatDelay)
        .addFunction("SetRepeatRate", &Button::SetRepeatRate)

        .addFunction("GetPressedOffset", &Button::GetPressedOffset)
        .addFunction("GetPressedChildOffset", &Button::GetPressedChildOffset)
        .addFunction("GetRepeatDelay", &Button::GetRepeatDelay)
        .addFunction("GetRepeatRate", &Button::GetRepeatRate)
        .addFunction("IsPressed", &Button::IsPressed)

        .addProperty("pressedOffset", &Button::GetPressedOffset, static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedOffset))
        .addProperty("pressedChildOffset", &Button::GetPressedChildOffset, static_cast<void(Button::*)(const IntVector2&)>(&Button::SetPressedChildOffset))
        .addProperty("repeatDelay", &Button::GetRepeatDelay, &Button::SetRepeatDelay)
        .addProperty("repeatRate", &Button::GetRepeatRate, &Button::SetRepeatRate)
        .addProperty("pressed", &Button::IsPressed)
    );
}

static void RegisterCheckBox(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CheckBox"].setClass(UserdataMetatable<CheckBox, BorderImage>()
        .addStaticFunction("new", &CreateObject<CheckBox>)

        .addFunction("SetChecked", &CheckBox::SetChecked)

        .addOverloadedFunctions("SetCheckedOffset",
            static_cast<void(CheckBox::*)(const IntVector2&)>(&CheckBox::SetCheckedOffset),
            static_cast<void(CheckBox::*)(int, int)>(&CheckBox::SetCheckedOffset))

        .addFunction("IsChecked", &CheckBox::IsChecked)
        .addFunction("GetCheckedOffset", &CheckBox::GetCheckedOffset)

        .addProperty("checked", &CheckBox::IsChecked, static_cast<void(CheckBox::*)(const IntVector2&)>(&CheckBox::SetCheckedOffset))
        .addProperty("checkedOffset", &CheckBox::GetCheckedOffset, static_cast<void(CheckBox::*)(const IntVector2&)>(&CheckBox::SetCheckedOffset))
    );
}

static void RegisterCursor(kaguya::State& lua)
{
    using namespace kaguya;

    // enum CursorShape;
    lua["CS_NORMAL"] = CS_NORMAL;
    lua["CS_IBEAM"] = CS_IBEAM;
    lua["CS_CROSS"] = CS_CROSS;
    lua["CS_RESIZEVERTICAL"] = CS_RESIZEVERTICAL;
    lua["CS_RESIZEDIAGONAL_TOPRIGHT"] = CS_RESIZEDIAGONAL_TOPRIGHT;
    lua["CS_RESIZEHORIZONTAL"] = CS_RESIZEHORIZONTAL;
    lua["CS_RESIZEDIAGONAL_TOPLEFT"] = CS_RESIZEDIAGONAL_TOPLEFT;
    lua["CS_RESIZE_ALL"] = CS_RESIZE_ALL;
    lua["CS_ACCEPTDROP"] = CS_ACCEPTDROP;
    lua["CS_REJECTDROP"] = CS_REJECTDROP;
    lua["CS_BUSY"] = CS_BUSY;
    lua["CS_BUSY_ARROW"] = CS_BUSY_ARROW;
    lua["CS_MAX_SHAPES"] = CS_MAX_SHAPES;

    lua["Cursor"].setClass(UserdataMetatable<Cursor, BorderImage>()
        .addStaticFunction("new", &CreateObject<Cursor>)

        .addOverloadedFunctions("DefineShape",
            static_cast<void(Cursor::*)(const String&, Image*, const IntRect&, const IntVector2&)>(&Cursor::DefineShape),
            static_cast<void(Cursor::*)(CursorShape, Image*, const IntRect&, const IntVector2&)>(&Cursor::DefineShape))

        .addOverloadedFunctions("SetShape",
            static_cast<void(Cursor::*)(const String&)>(&Cursor::SetShape),
            static_cast<void(Cursor::*)(CursorShape)>(&Cursor::SetShape))

        .addFunction("SetUseSystemShapes", &Cursor::SetUseSystemShapes)

        .addFunction("GetShape", &Cursor::GetShape)
        .addFunction("GetUseSystemShapes", &Cursor::GetUseSystemShapes)

        .addProperty("shape", &Cursor::GetShape, static_cast<void(Cursor::*)(const String&)>(&Cursor::SetShape))
        .addProperty("useSystemShapes", &Cursor::GetUseSystemShapes, &Cursor::SetUseSystemShapes)
    );
}

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

static void RegisterDropDownList(kaguya::State& lua)
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

static void RegisterFileSelector(kaguya::State& lua)
{
    using namespace kaguya;

    lua["FileSelectorEntry"].setClass(UserdataMetatable<FileSelectorEntry>()

    	.addProperty("name", &FileSelectorEntry::name_)
    	.addProperty("directory", &FileSelectorEntry::directory_)
    	);

    lua["FileSelector"].setClass(UserdataMetatable<FileSelector, Object>()
        .addStaticFunction("new", &CreateObject<FileSelector>)

        .addFunction("SetDefaultStyle", &FileSelector::SetDefaultStyle)
        .addFunction("SetTitle", &FileSelector::SetTitle)
        .addFunction("SetButtonTexts", &FileSelector::SetButtonTexts)
        .addFunction("SetPath", &FileSelector::SetPath)
        .addFunction("SetFileName", &FileSelector::SetFileName)
        .addFunction("SetFilters", &FileSelector::SetFilters)
        .addFunction("SetDirectoryMode", &FileSelector::SetDirectoryMode)

		.addFunction("UpdateElements", &FileSelector::UpdateElements)

        .addFunction("GetDefaultStyle", &FileSelector::GetDefaultStyle)
        .addFunction("GetWindow", &FileSelector::GetWindow)
        .addFunction("GetTitleText", &FileSelector::GetTitleText)
        .addFunction("GetFileList", &FileSelector::GetFileList)
        .addFunction("GetPathEdit", &FileSelector::GetPathEdit)
        .addFunction("GetFileNameEdit", &FileSelector::GetFileNameEdit)
        .addFunction("GetFilterList", &FileSelector::GetFilterList)
        .addFunction("GetOKButton", &FileSelector::GetOKButton)
        .addFunction("GetCancelButton", &FileSelector::GetCancelButton)
        .addFunction("GetCloseButton", &FileSelector::GetCloseButton)
        .addFunction("GetTitle", &FileSelector::GetTitle)
        .addFunction("GetPath", &FileSelector::GetPath)
        .addFunction("GetFileName", &FileSelector::GetFileName)
        .addFunction("GetFilter", &FileSelector::GetFilter)
        .addFunction("GetFilterIndex", &FileSelector::GetFilterIndex)
        .addFunction("GetDirectoryMode", &FileSelector::GetDirectoryMode)

        .addProperty("defaultStyle", &FileSelector::GetDefaultStyle, &FileSelector::SetDefaultStyle)
        .addProperty("window", &FileSelector::GetWindow)
        .addProperty("titleText", &FileSelector::GetTitleText)
        .addProperty("fileList", &FileSelector::GetFileList)
        .addProperty("pathEdit", &FileSelector::GetPathEdit)
        .addProperty("fileNameEdit", &FileSelector::GetFileNameEdit)
        .addProperty("filterList", &FileSelector::GetFilterList)
        .addProperty("OKButton", &FileSelector::GetOKButton)
        .addProperty("cancelButton", &FileSelector::GetCancelButton)
        .addProperty("closeButton", &FileSelector::GetCloseButton)
        .addProperty("title", &FileSelector::GetTitle, &FileSelector::SetTitle)
        .addProperty("path", &FileSelector::GetPath, &FileSelector::SetPath)
        .addProperty("fileName", &FileSelector::GetFileName, &FileSelector::SetFileName)
        .addProperty("filter", &FileSelector::GetFilter)
        .addProperty("filterIndex", &FileSelector::GetFilterIndex)
        .addProperty("directoryMode", &FileSelector::GetDirectoryMode, &FileSelector::SetDirectoryMode)
    );
}

static void RegisterFont(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Font"].setClass(UserdataMetatable<Font, Resource>()
        .addStaticFunction("new", &CreateObject<Font>)

        .addFunction("SetAbsoluteGlyphOffset", &Font::SetAbsoluteGlyphOffset)
        .addFunction("SetScaledGlyphOffset", &Font::SetScaledGlyphOffset)

        .addFunction("IsSDFFont", &Font::IsSDFFont)
        .addFunction("GetAbsoluteGlyphOffset", &Font::GetAbsoluteGlyphOffset)
        .addFunction("GetScaledGlyphOffset", &Font::GetScaledGlyphOffset)
        .addFunction("GetTotalGlyphOffset", &Font::GetTotalGlyphOffset)
        
        .addProperty("sdfFont", &Font::IsSDFFont)
        .addProperty("absoluteGlyphOffset", &Font::GetAbsoluteGlyphOffset, &Font::SetAbsoluteGlyphOffset)
        .addProperty("scaledGlyphOffset", &Font::GetScaledGlyphOffset, &Font::SetScaledGlyphOffset)
    );
}

static void RegisterLineEdit(kaguya::State& lua)
{
    using namespace kaguya;

    lua["LineEdit"].setClass(UserdataMetatable<LineEdit, BorderImage>()
        .addStaticFunction("new", &CreateObject<LineEdit>)

        .addFunction("SetText", &LineEdit::SetText)
        .addFunction("SetCursorPosition", &LineEdit::SetCursorPosition)
        .addFunction("SetCursorBlinkRate", &LineEdit::SetCursorBlinkRate)
        .addFunction("SetMaxLength", &LineEdit::SetMaxLength)
        .addFunction("SetEchoCharacter", &LineEdit::SetEchoCharacter)
        .addFunction("SetCursorMovable", &LineEdit::SetCursorMovable)
        .addFunction("SetTextSelectable", &LineEdit::SetTextSelectable)
        .addFunction("SetTextCopyable", &LineEdit::SetTextCopyable)

        .addFunction("GetText", &LineEdit::GetText)
        .addFunction("GetCursorPosition", &LineEdit::GetCursorPosition)
        .addFunction("GetCursorBlinkRate", &LineEdit::GetCursorBlinkRate)
        .addFunction("GetMaxLength", &LineEdit::GetMaxLength)
        .addFunction("GetEchoCharacter", &LineEdit::GetEchoCharacter)
        .addFunction("IsCursorMovable", &LineEdit::IsCursorMovable)
        .addFunction("IsTextSelectable", &LineEdit::IsTextSelectable)
        .addFunction("IsTextCopyable", &LineEdit::IsTextCopyable)
        .addFunction("GetTextElement", &LineEdit::GetTextElement)
        .addFunction("GetCursor", &LineEdit::GetCursor)

        .addProperty("text", &LineEdit::GetText, &LineEdit::SetText)
        .addProperty("cursorPosition", &LineEdit::GetCursorPosition, &LineEdit::SetCursorPosition)
        .addProperty("cursorBlinkRate", &LineEdit::GetCursorBlinkRate, &LineEdit::SetCursorBlinkRate)
        .addProperty("maxLength", &LineEdit::GetMaxLength, &LineEdit::SetMaxLength)
        .addProperty("echoCharacter", &LineEdit::GetEchoCharacter, &LineEdit::SetEchoCharacter)
        .addProperty("cursorMovable", &LineEdit::IsCursorMovable, &LineEdit::SetCursorMovable)
        .addProperty("textSelectable", &LineEdit::IsTextSelectable, &LineEdit::SetTextSelectable)
        .addProperty("textCopyable", &LineEdit::IsTextCopyable, &LineEdit::SetTextCopyable)
        .addProperty("textElement", &LineEdit::GetTextElement)
        .addProperty("cursor", &LineEdit::GetCursor)
    );
}

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

static void RegisterListView(kaguya::State& lua)
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

static SharedPtr<UIElement> MenuGetPopup(const Menu* self)
{
    return SharedPtr<UIElement>(self->GetPopup());
}

static void RegisterMenu(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Menu"].setClass(UserdataMetatable<Menu, Button>()
        .addStaticFunction("new", &CreateObject<Menu>)

        .addFunction("SetPopup", &Menu::SetPopup)

        .addOverloadedFunctions("SetPopupOffset",
            static_cast<void(Menu::*)(const IntVector2&)>(&Menu::SetPopupOffset),
            static_cast<void(Menu::*)(int, int)>(&Menu::SetPopupOffset))

        .addFunction("ShowPopup", &Menu::ShowPopup)
        .addFunction("SetAccelerator", &Menu::SetAccelerator)

        .addStaticFunction("GetPopup", &MenuGetPopup)

        .addFunction("GetPopupOffset", &Menu::GetPopupOffset)
        .addFunction("GetShowPopup", &Menu::GetShowPopup)
        .addFunction("GetAcceleratorKey", &Menu::GetAcceleratorKey)
        .addFunction("GetAcceleratorQualifiers", &Menu::GetAcceleratorQualifiers)

        .addProperty("popup", &MenuGetPopup)
        .addProperty("popupOffset", &Menu::GetPopupOffset, static_cast<void(Menu::*)(const IntVector2&)>(&Menu::SetPopupOffset))
        .addProperty("showPopup", &Menu::GetShowPopup)
        .addProperty("acceleratorKey", &Menu::GetAcceleratorKey)
        .addProperty("acceleratorQualifiers", &Menu::GetAcceleratorQualifiers)
    );
}

static SharedPtr<MessageBox> CreateMessageBox(Context* context, const String& messageString, const String& titleString = "", XMLFile* layoutFile = 0, XMLFile* styleFile = 0)
{
    return SharedPtr<MessageBox>(new MessageBox(globalContext, messageString, titleString, layoutFile, styleFile));
}

KAGUYA_FUNCTION_OVERLOADS(CreateMessageBoxOverloads, CreateMessageBox, 2, 5);

static SharedPtr<UIElement> MessageBoxGetWindow(const MessageBox* self)
{
    return SharedPtr<UIElement>(self->GetWindow());
}

static void RegisterMessageBox(kaguya::State& lua)
{
    using namespace kaguya;

    lua["MessageBox"].setClass(UserdataMetatable<MessageBox, Object>()
        .addStaticFunction("new", CreateMessageBoxOverloads())

        .addFunction("SetTitle", &MessageBox::SetTitle)
        .addFunction("SetMessage", &MessageBox::SetMessage)

        .addFunction("GetTitle", &MessageBox::GetTitle)
        .addFunction("GetMessage", &MessageBox::GetMessage)
        
        .addStaticFunction("GetWindow", &MessageBoxGetWindow)

        .addProperty("title", &MessageBox::GetTitle, &MessageBox::SetTitle)
        .addProperty("message", &MessageBox::GetMessage, &MessageBox::SetMessage)
        .addProperty("window", &MessageBoxGetWindow)
    );
}

static void RegisterScrollBar(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ScrollBar"].setClass(UserdataMetatable<ScrollBar, BorderImage>()
        .addStaticFunction("new", &CreateObject<FileSelector>)

        .addFunction("SetOrientation", &ScrollBar::SetOrientation)
        .addFunction("SetRange", &ScrollBar::SetRange)
        .addFunction("SetValue", &ScrollBar::SetValue)
        .addFunction("ChangeValue", &ScrollBar::ChangeValue)
        .addFunction("SetScrollStep", &ScrollBar::SetScrollStep)
        .addFunction("SetStepFactor", &ScrollBar::SetStepFactor)
        .addFunction("StepBack", &ScrollBar::StepBack)
        .addFunction("StepForward", &ScrollBar::StepForward)

        .addFunction("GetOrientation", &ScrollBar::GetOrientation)
        .addFunction("GetRange", &ScrollBar::GetRange)
        .addFunction("GetValue", &ScrollBar::GetValue)
        .addFunction("GetScrollStep", &ScrollBar::GetScrollStep)
        .addFunction("GetStepFactor", &ScrollBar::GetStepFactor)
        .addFunction("GetEffectiveScrollStep", &ScrollBar::GetEffectiveScrollStep)
        .addFunction("GetBackButton", &ScrollBar::GetBackButton)
        .addFunction("GetForwardButton", &ScrollBar::GetForwardButton)
        .addFunction("GetSlider", &ScrollBar::GetSlider)

        .addProperty("orientation", &ScrollBar::GetOrientation, &ScrollBar::SetOrientation)
        .addProperty("range", &ScrollBar::GetRange, &ScrollBar::SetRange)
        .addProperty("value", &ScrollBar::GetValue, &ScrollBar::SetValue)
        .addProperty("scrollStep", &ScrollBar::GetScrollStep, &ScrollBar::SetScrollStep)
        .addProperty("stepFactor", &ScrollBar::GetStepFactor, &ScrollBar::SetStepFactor)
        .addProperty("effectiveScrollStep", &ScrollBar::GetEffectiveScrollStep)
        .addProperty("backButton", &ScrollBar::GetBackButton)
        .addProperty("forwardButton", &ScrollBar::GetForwardButton)
        .addProperty("slider", &ScrollBar::GetSlider)
    );
}

static void ScrollViewSetContentElement(ScrollView* self, UIElement* contentElement)
{
	self->SetContentElement(contentElement);
}

static SharedPtr<UIElement> ScrollViewGetContentElement(const ScrollView* self)
{
	return SharedPtr<UIElement>(self->GetContentElement());
}

static void RegisterScrollView(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ScrollView"].setClass(UserdataMetatable<ScrollView, UIElement>()
        .addStaticFunction("new", &CreateObject<ScrollView>)

        .addFunction("SetContentElement", &ScrollView::SetContentElement)

        .addOverloadedFunctions("SetViewPosition",
            static_cast<void(ScrollView::*)(const IntVector2&)>(&ScrollView::SetViewPosition),
            static_cast<void(ScrollView::*)(int, int)>(&ScrollView::SetViewPosition))

        .addFunction("SetScrollBarsVisible", &ScrollView::SetScrollBarsVisible)
        .addFunction("SetScrollBarsAutoVisible", &ScrollView::SetScrollBarsAutoVisible)
        .addFunction("SetScrollStep", &ScrollView::SetScrollStep)
        .addFunction("SetPageStep", &ScrollView::SetPageStep)
        .addFunction("SetScrollDeceleration", &ScrollView::SetScrollDeceleration)
        .addFunction("SetScrollSnapEpsilon", &ScrollView::SetScrollSnapEpsilon)
        .addFunction("SetAutoDisableChildren", &ScrollView::SetAutoDisableChildren)
        .addFunction("SetAutoDisableThreshold", &ScrollView::SetAutoDisableThreshold)

        .addFunction("GetViewPosition", &ScrollView::GetViewPosition)
        
        .addStaticFunction("GetContentElement", &ScrollViewGetContentElement)

        .addFunction("GetHorizontalScrollBar", &ScrollView::GetHorizontalScrollBar)
        .addFunction("GetVerticalScrollBar", &ScrollView::GetVerticalScrollBar)
        .addFunction("GetScrollPanel", &ScrollView::GetScrollPanel)
        .addFunction("GetScrollBarsAutoVisible", &ScrollView::GetScrollBarsAutoVisible)
        .addFunction("GetScrollStep", &ScrollView::GetScrollStep)
        .addFunction("GetPageStep", &ScrollView::GetPageStep)
        .addFunction("GetScrollDeceleration", &ScrollView::GetScrollDeceleration)
        .addFunction("GetScrollSnapEpsilon", &ScrollView::GetScrollSnapEpsilon)
        .addFunction("GetAutoDisableChildren", &ScrollView::GetAutoDisableChildren)
        .addFunction("GetAutoDisableThreshold", &ScrollView::GetAutoDisableThreshold)

        .addProperty("viewPosition", &ScrollView::GetViewPosition, static_cast<void(ScrollView::*)(const IntVector2&)>(&ScrollView::SetViewPosition))
        
        .addProperty("contentElement", &ScrollViewGetContentElement, &ScrollViewSetContentElement)

        .addProperty("horizontalScrollBar", &ScrollView::GetHorizontalScrollBar)
        .addProperty("verticalScrollBar", &ScrollView::GetVerticalScrollBar)
        .addProperty("scrollPanel", &ScrollView::GetScrollPanel)
        .addProperty("scrollBarsAutoVisible", &ScrollView::GetScrollBarsAutoVisible, &ScrollView::SetScrollBarsAutoVisible)
        .addProperty("scrollStep", &ScrollView::GetScrollStep, &ScrollView::SetScrollStep)
        .addProperty("pageStep", &ScrollView::GetPageStep, &ScrollView::SetPageStep)
        .addProperty("scrollDeceleration", &ScrollView::GetScrollDeceleration, &ScrollView::SetScrollDeceleration)
        .addProperty("scrollSnapEpsilon", &ScrollView::GetScrollSnapEpsilon, &ScrollView::SetScrollSnapEpsilon)
    );
}

static void RegisterSlider(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Slider"].setClass(UserdataMetatable<Slider, BorderImage>()
        .addStaticFunction("new", &CreateObject<Slider>)

        .addFunction("SetOrientation", &Slider::SetOrientation)
        .addFunction("SetRange", &Slider::SetRange)
        .addFunction("SetValue", &Slider::SetValue)
        .addFunction("ChangeValue", &Slider::ChangeValue)
        .addFunction("SetRepeatRate", &Slider::SetRepeatRate)

        .addFunction("GetOrientation", &Slider::GetOrientation)
        .addFunction("GetRange", &Slider::GetRange)
        .addFunction("GetValue", &Slider::GetValue)
        .addFunction("GetKnob", &Slider::GetKnob)
        .addFunction("GetRepeatRate", &Slider::GetRepeatRate)

        .addProperty("orientation", &Slider::GetOrientation, &Slider::SetOrientation)
        .addProperty("range", &Slider::GetRange, &Slider::SetRange)
        .addProperty("value", &Slider::GetValue, &Slider::SetValue)
        .addProperty("knob", &Slider::GetKnob)
        .addProperty("repeatRate", &Slider::GetRepeatRate, &Slider::SetRepeatRate)
    );
}

static void RegisterSprite(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Sprite"].setClass(UserdataMetatable<Sprite, UIElement>()
        .addStaticFunction("new", &CreateObject<Sprite>)

        .addOverloadedFunctions("SetPosition",
            static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetPosition),
            static_cast<void(Sprite::*)(float, float)>(&Sprite::SetPosition))

        .addOverloadedFunctions("SetHotSpot",
            static_cast<void(Sprite::*)(const IntVector2&)>(&Sprite::SetHotSpot),
            static_cast<void(Sprite::*)(int, int)>(&Sprite::SetHotSpot))

        .addOverloadedFunctions("SetScale",
            static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetScale),
            static_cast<void(Sprite::*)(float, float)>(&Sprite::SetScale),
            static_cast<void(Sprite::*)(float)>(&Sprite::SetScale))

        .addFunction("SetRotation", &Sprite::SetRotation)
        .addFunction("SetTexture", &Sprite::SetTexture)
        .addFunction("SetImageRect", &Sprite::SetImageRect)
        .addFunction("SetFullImageRect", &Sprite::SetFullImageRect)
        .addFunction("SetBlendMode", &Sprite::SetBlendMode)

        .addFunction("GetPosition", &Sprite::GetPosition)
        .addFunction("GetHotSpot", &Sprite::GetHotSpot)
        .addFunction("GetScale", &Sprite::GetScale)
        .addFunction("GetRotation", &Sprite::GetRotation)
        .addFunction("GetTexture", &Sprite::GetTexture)
        .addFunction("GetImageRect", &Sprite::GetImageRect)
        .addFunction("GetBlendMode", &Sprite::GetBlendMode)

        .addFunction("GetTransform", &Sprite::GetTransform)

        .addProperty("position", &Sprite::GetPosition, static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetPosition))
        .addProperty("hotSpot", &Sprite::GetHotSpot, static_cast<void(Sprite::*)(const IntVector2&)>(&Sprite::SetHotSpot))
        .addProperty("scale", &Sprite::GetScale, static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetScale))
        .addProperty("rotation", &Sprite::GetRotation, &Sprite::SetRotation)
        .addProperty("texture", &Sprite::GetTexture, &Sprite::SetTexture)
        .addProperty("imageRect", &Sprite::GetImageRect, &Sprite::SetImageRect)
        .addProperty("blendMode", &Sprite::GetBlendMode, &Sprite::SetBlendMode)

        .addProperty("transform", &Sprite::GetTransform)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(TextSetFont0, Text, SetFont, 1, 2, bool(Text::*)(const String&, int));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(TextSetFont1, Text, SetFont, 1, 2, bool(Text::*)(Font*, int));
KAGUYA_MEMBER_FUNCTION_OVERLOADS(TextSetSelection, Text, SetSelection, 1, 2);

static void RegisterText(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DEFAULT_FONT_SIZE"] = DEFAULT_FONT_SIZE;

    // enum TextEffect;
    lua["TE_NONE"] = TE_NONE;
    lua["TE_SHADOW"] = TE_SHADOW;
    lua["TE_STROKE"] = TE_STROKE;

    lua["Text"].setClass(UserdataMetatable<Text, UIElement>()
        .addStaticFunction("new", &CreateObject<Text>)

        .addOverloadedFunctions("SetFont", TextSetFont0(), TextSetFont1())

        .addFunction("SetText", &Text::SetText)
        .addFunction("SetTextAlignment", &Text::SetTextAlignment)
        .addFunction("SetRowSpacing", &Text::SetRowSpacing)
        .addFunction("SetWordwrap", &Text::SetWordwrap)
        .addFunction("SetAutoLocalizable", &Text::SetAutoLocalizable)

        .addFunction("SetSelection", TextSetSelection())

        .addFunction("ClearSelection", &Text::ClearSelection)
        .addFunction("SetSelectionColor", &Text::SetSelectionColor)
        .addFunction("SetHoverColor", &Text::SetHoverColor)
        .addFunction("SetTextEffect", &Text::SetTextEffect)
        .addFunction("SetEffectShadowOffset", &Text::SetEffectShadowOffset)
        .addFunction("SetEffectStrokeThickness", &Text::SetEffectStrokeThickness)
        .addFunction("SetEffectRoundStroke", &Text::SetEffectRoundStroke)
        .addFunction("SetEffectColor", &Text::SetEffectColor)

        .addFunction("GetFont", &Text::GetFont)
        .addFunction("GetFontSize", &Text::GetFontSize)
        .addFunction("GetText", &Text::GetText)
        .addFunction("GetTextAlignment", &Text::GetTextAlignment)
        .addFunction("GetRowSpacing", &Text::GetRowSpacing)
        .addFunction("GetWordwrap", &Text::GetWordwrap)
        .addFunction("GetAutoLocalizable", &Text::GetAutoLocalizable)
        .addFunction("GetSelectionStart", &Text::GetSelectionStart)
        .addFunction("GetSelectionLength", &Text::GetSelectionLength)
        .addFunction("GetSelectionColor", &Text::GetSelectionColor)
        .addFunction("GetHoverColor", &Text::GetHoverColor)
        .addFunction("GetTextEffect", &Text::GetTextEffect)
        .addFunction("GetEffectShadowOffset", &Text::GetEffectShadowOffset)
        .addFunction("GetEffectStrokeThickness", &Text::GetEffectStrokeThickness)
        .addFunction("GetEffectRoundStroke", &Text::GetEffectRoundStroke)
        .addFunction("GetEffectColor", &Text::GetEffectColor)
        .addFunction("GetRowHeight", &Text::GetRowHeight)
        .addFunction("GetNumRows", &Text::GetNumRows)
        .addFunction("GetNumChars", &Text::GetNumChars)
        .addFunction("GetRowWidth", &Text::GetRowWidth)
        .addFunction("GetCharPosition", &Text::GetCharPosition)
        .addFunction("GetCharSize", &Text::GetCharSize)

        .addFunction("SetEffectDepthBias", &Text::SetEffectDepthBias)
        .addFunction("GetEffectDepthBias", &Text::GetEffectDepthBias)

        .addProperty("font", &Text::GetFont)
        .addProperty("fontSize", &Text::GetFontSize)
        .addProperty("text", &Text::GetText, &Text::SetText)
        .addProperty("textAlignment", &Text::GetTextAlignment, &Text::SetTextAlignment)
        .addProperty("rowSpacing", &Text::GetRowSpacing, &Text::SetRowSpacing)
        .addProperty("wordwrap", &Text::GetWordwrap, &Text::SetWordwrap)
        .addProperty("autoLocalizable", &Text::GetAutoLocalizable, &Text::SetAutoLocalizable)
        .addProperty("selectionStart", &Text::GetSelectionStart)
        .addProperty("selectionLength", &Text::GetSelectionLength)
        .addProperty("selectionColor", &Text::GetSelectionColor, &Text::SetSelectionColor)
        .addProperty("hoverColor", &Text::GetHoverColor, &Text::SetHoverColor)
        .addProperty("textEffect", &Text::GetTextEffect, &Text::SetTextEffect)
        .addProperty("effectShadowOffset", &Text::GetEffectShadowOffset, &Text::SetEffectShadowOffset)
        .addProperty("effectStrokeThickness", &Text::GetEffectStrokeThickness, &Text::SetEffectStrokeThickness)
        .addProperty("effectRoundStroke", &Text::GetEffectRoundStroke, &Text::SetEffectRoundStroke)
        .addProperty("effectColor", &Text::GetEffectColor, &Text::SetEffectColor)
        .addProperty("rowHeight", &Text::GetRowHeight)
        .addProperty("numRows", &Text::GetNumRows)
        .addProperty("numChars", &Text::GetNumChars)
        .addProperty("effectDepthBias", &Text::GetEffectDepthBias, &Text::SetEffectDepthBias)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Text3DSetFont0, Text3D, SetFont, 1, 2, bool(Text3D::*)(const String&, int));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Text3DSetFont1, Text3D, SetFont, 1, 2, bool(Text3D::*)(Font*, int));

static void Text3DSetColor(Text3D* self, const Color& color)
{
	self->SetColor(color);
}

static const Color& Text3DGetColor(const Text3D* self)
{
	return self->GetColor(C_TOPLEFT);
}

static void RegisterText3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Text3D"].setClass(UserdataMetatable<Text3D, Drawable>()
        .addStaticFunction("new", &CreateObject<Text3D>)

		.addOverloadedFunctions("SetFont", Text3DSetFont0(), Text3DSetFont1())

        .addFunction("SetMaterial", &Text3D::SetMaterial)
        .addFunction("SetText", &Text3D::SetText)
        .addFunction("SetAlignment", &Text3D::SetAlignment)
        .addFunction("SetHorizontalAlignment", &Text3D::SetHorizontalAlignment)
        .addFunction("SetVerticalAlignment", &Text3D::SetVerticalAlignment)
        .addFunction("SetTextAlignment", &Text3D::SetTextAlignment)
        .addFunction("SetRowSpacing", &Text3D::SetRowSpacing)
        .addFunction("SetWordwrap", &Text3D::SetWordwrap)
        .addFunction("SetTextEffect", &Text3D::SetTextEffect)
        .addFunction("SetEffectShadowOffset", &Text3D::SetEffectShadowOffset)
        .addFunction("SetEffectStrokeThickness", &Text3D::SetEffectStrokeThickness)
        .addFunction("SetEffectRoundStroke", &Text3D::SetEffectRoundStroke)
        .addFunction("SetEffectColor", &Text3D::SetEffectColor)
        .addFunction("SetEffectDepthBias", &Text3D::SetEffectDepthBias)
        .addFunction("SetWidth", &Text3D::SetWidth)

        .addOverloadedFunctions("SetColor",
            static_cast<void(Text3D::*)(const Color&)>(&Text3D::SetColor),
            static_cast<void(Text3D::*)(Corner, const Color&)>(&Text3D::SetColor))

        .addFunction("SetOpacity", &Text3D::SetOpacity)
        .addFunction("SetFixedScreenSize", &Text3D::SetFixedScreenSize)
        .addFunction("SetFaceCameraMode", &Text3D::SetFaceCameraMode)

        .addFunction("GetFont", &Text3D::GetFont)
        .addFunction("GetFontSize", &Text3D::GetFontSize)
        .addFunction("GetMaterial", &Text3D::GetMaterial)
        .addFunction("GetText", &Text3D::GetText)
        .addFunction("GetTextAlignment", &Text3D::GetTextAlignment)
        .addFunction("GetHorizontalAlignment", &Text3D::GetHorizontalAlignment)
        .addFunction("GetVerticalAlignment", &Text3D::GetVerticalAlignment)
        .addFunction("GetRowSpacing", &Text3D::GetRowSpacing)
        .addFunction("GetWordwrap", &Text3D::GetWordwrap)
        .addFunction("GetTextEffect", &Text3D::GetTextEffect)
        .addFunction("GetEffectShadowOffset", &Text3D::GetEffectShadowOffset)
        .addFunction("GetEffectStrokeThickness", &Text3D::GetEffectStrokeThickness)
        .addFunction("GetEffectRoundStroke", &Text3D::GetEffectRoundStroke)
        .addFunction("GetEffectColor", &Text3D::GetEffectColor)
        .addFunction("GetEffectDepthBias", &Text3D::GetEffectDepthBias)
        .addFunction("GetWidth", &Text3D::GetWidth)
        .addFunction("GetRowHeight", &Text3D::GetRowHeight)
        .addFunction("GetNumRows", &Text3D::GetNumRows)
        .addFunction("GetNumChars", &Text3D::GetNumChars)
        .addFunction("GetRowWidth", &Text3D::GetRowWidth)
        .addFunction("GetCharPosition", &Text3D::GetCharPosition)
        .addFunction("GetCharSize", &Text3D::GetCharSize)

        .addOverloadedFunctions("GetColor", &Text3DGetColor, &Text3D::GetColor)

        .addFunction("GetOpacity", &Text3D::GetOpacity)
        .addFunction("IsFixedScreenSize", &Text3D::IsFixedScreenSize)
        .addFunction("GetFaceCameraMode", &Text3D::GetFaceCameraMode)

        .addProperty("font", &Text3D::GetFont)
        .addProperty("fontSize", &Text3D::GetFontSize)
        .addProperty("material", &Text3D::GetMaterial, &Text3D::SetMaterial)
        .addProperty("text", &Text3D::GetText, &Text3D::SetText)
        .addProperty("textAlignment", &Text3D::GetTextAlignment, &Text3D::SetTextAlignment)
        .addProperty("horizontalAlignment", &Text3D::GetHorizontalAlignment, &Text3D::SetHorizontalAlignment)
        .addProperty("verticalAlignment", &Text3D::GetVerticalAlignment, &Text3D::SetVerticalAlignment)
        .addProperty("rowSpacing", &Text3D::GetRowSpacing, &Text3D::SetRowSpacing)
        .addProperty("wordwrap", &Text3D::GetWordwrap, &Text3D::SetWordwrap)
        .addProperty("textEffect", &Text3D::GetTextEffect, &Text3D::SetTextEffect)
        .addProperty("effectShadowOffset", &Text3D::GetEffectShadowOffset, &Text3D::SetEffectShadowOffset)
        .addProperty("effectStrokeThickness", &Text3D::GetEffectStrokeThickness, &Text3D::SetEffectStrokeThickness)
        .addProperty("effectRoundStroke", &Text3D::GetEffectRoundStroke, &Text3D::SetEffectRoundStroke)
        .addProperty("effectColor", &Text3D::GetEffectColor, &Text3D::SetEffectColor)
        .addProperty("effectDepthBias", &Text3D::GetEffectDepthBias, &Text3D::SetEffectDepthBias)
        .addProperty("width", &Text3D::GetWidth, &Text3D::SetWidth)
        .addProperty("rowHeight", &Text3D::GetRowHeight)
        .addProperty("numRows", &Text3D::GetNumRows)
        .addProperty("numChars", &Text3D::GetNumChars)
		.addProperty("color", &Text3DGetColor, &Text3DSetColor)
        .addProperty("opacity", &Text3D::GetOpacity, &Text3D::SetOpacity)
        .addProperty("fixedScreenSize", &Text3D::IsFixedScreenSize, &Text3D::SetFixedScreenSize)
        .addProperty("faceCameraMode", &Text3D::GetFaceCameraMode, &Text3D::SetFaceCameraMode)
    );
}

static void RegisterToolTip(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ToolTip"].setClass(UserdataMetatable<ToolTip, UIElement>()
        .addStaticFunction("new", &CreateObject<ToolTip>)

        .addFunction("SetDelay", &ToolTip::SetDelay)
        .addFunction("GetDelay", &ToolTip::GetDelay)

        .addProperty("delay", &ToolTip::GetDelay, &ToolTip::SetDelay)
    );
}

static void UISetFocusElement0(UI* self, UIElement* element)
{
    self->SetFocusElement(element);
}

static void UISetFocusElement1(UI* self, UIElement* element, bool byKey)
{
    self->SetFocusElement(element, byKey);
}

static SharedPtr<UIElement> UILoadLayout0(UI* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<UIElement>();

    return self->LoadLayout(*file);
}

static SharedPtr<UIElement> UILoadLayout1(UI* self, const char* filepath, XMLFile* styleFile)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<UIElement>();

    return self->LoadLayout(*file, styleFile);
}

static SharedPtr<UIElement> UILoadLayout2(UI* self, XMLFile* file)
{
    return self->LoadLayout(file);
}

static SharedPtr<UIElement> UILoadLayout3(UI* self, XMLFile* file, XMLFile* styleFile)
{
    return self->LoadLayout(file, styleFile);
}

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

static SharedPtr<UIElement> UIGetElementAt0(UI* self, const IntVector2& position)
{
    return SharedPtr<UIElement>(self->GetElementAt(position));
}

static SharedPtr<UIElement> UIGetElementAt1(UI* self, const IntVector2& position, bool enabledOnly)
{
    return SharedPtr<UIElement>(self->GetElementAt(position, enabledOnly));
}

static SharedPtr<UIElement> UIGetElementAt2(UI* self, int x, int y)
{
    return SharedPtr<UIElement>(self->GetElementAt(x, y));
}

static SharedPtr<UIElement> UIGetElementAt3(UI* self, int x, int y, bool enabledOnly)
{
    return SharedPtr<UIElement>(self->GetElementAt(x, y, enabledOnly));
}

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

static void RegisterUI(kaguya::State& lua)
{
    using namespace kaguya;

    lua["UI"].setClass(UserdataMetatable<UI, Object>()

        .addFunction("SetCursor", &UI::SetCursor)

        ADD_OVERLOADED_FUNCTIONS_2(UI, SetFocusElement)

        .addFunction("SetModalElement", &UI::SetModalElement)
        .addFunction("Clear", &UI::Clear)

        .addFunction("DebugDraw", &UI::DebugDraw)

        ADD_OVERLOADED_FUNCTIONS_4(UI, LoadLayout)

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

        ADD_OVERLOADED_FUNCTIONS_4(UI, GetElementAt)

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

static bool UIElementLoadXML(UIElement* uiElement, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return uiElement->LoadXML(*file);
}

static bool UIElementSaveXML0(const UIElement* uiElement, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return  false;
    return uiElement->SaveXML(*file);
}

static bool UIElementSaveXML1(const UIElement* uiElement, const char* filepath, const String& indentation)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return  false;
    return uiElement->SaveXML(*file, indentation);
}

static bool UIElementSetStyle0(UIElement* self, const String& styleName)
{
    return self->SetStyle(styleName);
}

static bool UIElementSetStyle1(UIElement* self, const String& styleName, XMLFile* file)
{
    return self->SetStyle(styleName, file);
}

static bool UIElementSetStyleAuto0(UIElement* self)
{
    return self->SetStyleAuto();
}

static bool UIElementSetStyleAuto1(UIElement* self, XMLFile* file)
{
    return self->SetStyleAuto(file);
}

static void UIElementSetLayout0(UIElement* self, LayoutMode mode)
{
    self->SetLayout(mode);
}

static void UIElementSetLayout1(UIElement* self, LayoutMode mode, int spacing)
{
    self->SetLayout(mode, spacing);
}

static void UIElementSetLayout2(UIElement* self, LayoutMode mode, int spacing, const IntRect& border)
{
    self->SetLayout(mode, spacing, border);
}

static SharedPtr<UIElement> UIElementCreateChild0(UIElement* self, const char* type)
{
    return SharedPtr<UIElement>(self->CreateChild(StringHash(type)));
}

static SharedPtr<UIElement> UIElementCreateChild1(UIElement* self, const char* type, const String& name)
{
    return SharedPtr<UIElement>(self->CreateChild(StringHash(type), name));
}

static SharedPtr<UIElement> UIElementCreateChild2(UIElement* self, const char* type, const String& name, unsigned index)
{
    return SharedPtr<UIElement>(self->CreateChild(StringHash(type), name, index));
}

static void UIElementRemoveChild0(UIElement* self, UIElement* element)
{
    self->RemoveChild(element);
}

static void UIElementRemoveChild1(UIElement* self, UIElement* element, unsigned int index)
{
    self->RemoveChild(element, index);
}

static void UIElementSetParent0(UIElement* self, UIElement* parent)
{
    self->SetParent(parent);
}

static void UIElementSetParent1(UIElement* self, UIElement* parent, unsigned int index)
{
    self->SetParent(parent, index);
}

static void UIElementAddTags0(UIElement* self, const String& tags)
{
    self->AddTags(tags);
}

static void UIElementAddTags1(UIElement* self, const String& tags, char separator)
{
    self->AddTags(tags, separator);
}

static void UIElementSetColor(UIElement* self, const Color& color)
{
	self->SetColor(color);
}

static const Color& UIElementGetColor(const UIElement* self)
{
	return self->GetColor(C_TOPLEFT);
}

static XMLFile* UIElementGetDefaultStyle0(const UIElement* self)
{
    return self->GetDefaultStyle();
}

static XMLFile* UIElementGetDefaultStyle1(const UIElement* self, bool recursiveUp)
{
    return self->GetDefaultStyle(recursiveUp);
}

static unsigned int UIElementGetNumChildren0(const UIElement* self)
{
    return self->GetNumChildren();
}

static unsigned int UIElementGetNumChildren1(const UIElement* self, bool recursive)
{
    return self->GetNumChildren(recursive);
}

static SharedPtr<UIElement> UIElementGetChild0(const UIElement* self, unsigned index)
{
    return SharedPtr<UIElement>(self->GetChild(index));
}

static SharedPtr<UIElement> UIElementGetChild1(const UIElement* self, const String& name)
{
    return SharedPtr<UIElement>(self->GetChild(name));
}

static SharedPtr<UIElement> UIElementGetChild2(const UIElement* self, const String& name, bool recursive)
{
    return SharedPtr<UIElement>(self->GetChild(name, recursive));
}

static SharedPtr<UIElement> UIElementGetChild3(const UIElement* self, const char* key, const Variant& value)
{
    return SharedPtr<UIElement>(self->GetChild(StringHash(key), value));
}

static SharedPtr<UIElement> UIElementGetChild4(const UIElement* self, const char* key, const Variant& value, bool recursive)
{
    return SharedPtr<UIElement>(self->GetChild(StringHash(key), value, recursive));
}

static PODVector<UIElement*> UIElementGetChildren0(const UIElement* self)
{
    PODVector<UIElement*> dest;
    self->GetChildren(dest);
    return dest;
}

static PODVector<UIElement*> UIElementGetChildren1(const UIElement* self, bool recursive)
{
    PODVector<UIElement*> dest;
    self->GetChildren(dest, recursive);
    return dest;
}

static const PODVector<UIElement*> UIElementGetChildrenWithTag0(const UIElement* element, const char* tag)
{
    PODVector<UIElement*> dest;
    element->GetChildrenWithTag(dest, tag);
    return dest;
}

static const PODVector<UIElement*> UIElementGetChildrenWithTag1(const UIElement* element, const char* tag, bool recursive)
{
    PODVector<UIElement*> dest;
    element->GetChildrenWithTag(dest, tag, recursive);
    return dest;
}

static void UIElementSetDefaultStyle(UIElement* self, XMLFile* style)
{
	self->SetDefaultStyle(style);
}

static XMLFile* UIElementGetDefaultStyle(const UIElement* self)
{
	return self->GetDefaultStyle(true);
}

static void RegisterUIElement(kaguya::State& lua)
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
        ADD_OVERLOADED_FUNCTIONS_2(UIElement, SaveXML)

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
            &UIElementSetStyle0,
            &UIElementSetStyle1,
            static_cast<bool (UIElement::*)(const XMLElement&)>(&UIElement::SetStyle))

        ADD_OVERLOADED_FUNCTIONS_2(UIElement, SetStyleAuto)

        .addFunction("SetDefaultStyle", &UIElement::SetDefaultStyle)

        ADD_OVERLOADED_FUNCTIONS_3(UIElement, SetLayout)

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

        ADD_OVERLOADED_FUNCTIONS_3(UIElement, CreateChild)

        .addFunction("AddChild", &UIElement::AddChild)
        .addFunction("InsertChild", &UIElement::InsertChild)

        ADD_OVERLOADED_FUNCTIONS_2(UIElement, RemoveChild)

        .addFunction("RemoveChildAtIndex", &UIElement::RemoveChildAtIndex)
        .addFunction("RemoveAllChildren", &UIElement::RemoveAllChildren)
        .addFunction("Remove", &UIElement::Remove)
        .addFunction("FindChild", &UIElement::FindChild)

        ADD_OVERLOADED_FUNCTIONS_2(UIElement, SetParent)

        .addFunction("SetVar", &UIElement::SetVar)
        .addFunction("SetInternal", &UIElement::SetInternal)
        .addFunction("SetTraversalMode", &UIElement::SetTraversalMode)
        .addFunction("SetElementEventSender", &UIElement::SetElementEventSender)
        .addFunction("SetTags", &UIElement::SetTags)
		.addFunction("AddTag", &UIElement::AddTag)

        .addOverloadedFunctions("AddTags",
            &UIElementAddTags0,
            &UIElementAddTags1,
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
        
		.addOverloadedFunctions("GetColor", &UIElementGetColor, &UIElement::GetColor)

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

        ADD_OVERLOADED_FUNCTIONS_2(UIElement, GetDefaultStyle)

        .addFunction("GetLayoutMode", &UIElement::GetLayoutMode)
        .addFunction("GetLayoutSpacing", &UIElement::GetLayoutSpacing)
        .addFunction("GetLayoutBorder", &UIElement::GetLayoutBorder)
        .addFunction("GetLayoutFlexScale", &UIElement::GetLayoutFlexScale)

        ADD_OVERLOADED_FUNCTIONS_2(UIElement, GetNumChildren)
        ADD_OVERLOADED_FUNCTIONS_5(UIElement, GetChild)
        ADD_OVERLOADED_FUNCTIONS_2(UIElement, GetChildren)

        .addFunction("GetParent", &UIElement::GetParent)
        .addFunction("GetRoot", &UIElement::GetRoot)
        .addFunction("GetDerivedColor", &UIElement::GetDerivedColor)
        .addFunction("GetVar", &UIElement::GetVar)
        .addFunction("GetVars", &UIElement::GetVars)
        .addFunction("HasTag", &UIElement::HasTag)
        .addFunction("GetTags", &UIElement::GetTags)

        ADD_OVERLOADED_FUNCTIONS_2(UIElement, GetChildrenWithTag)

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
		
			.addProperty("color", &UIElementGetColor, &UIElementSetColor)

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
        
		.addProperty("defaultStyle", &UIElementGetDefaultStyle, &UIElementSetDefaultStyle)

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

static void View3DSetView0(View3D* self, Scene* scene, Camera* camera)
{
    self->SetView(scene, camera);
}

static void View3DSetView1(View3D* self, Scene* scene, Camera* camera, bool ownScene)
{
    self->SetView(scene, camera, ownScene);
}

static void RegisterView3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["View3D"].setClass(UserdataMetatable<View3D, Window>()
        .addStaticFunction("new", &CreateObject<View3D>)

        ADD_OVERLOADED_FUNCTIONS_2(View3D, SetView)

        .addFunction("SetFormat", &View3D::SetFormat)
        .addFunction("SetAutoUpdate", &View3D::SetAutoUpdate)
        .addFunction("QueueUpdate", &View3D::QueueUpdate)

        .addFunction("GetFormat", &View3D::GetFormat)
        .addFunction("GetAutoUpdate", &View3D::GetAutoUpdate)
        .addFunction("GetScene", &View3D::GetScene)
        .addFunction("GetCameraNode", &View3D::GetCameraNode)
        .addFunction("GetRenderTexture", &View3D::GetRenderTexture)
        .addFunction("GetDepthTexture", &View3D::GetDepthTexture)
        .addFunction("GetViewport", &View3D::GetViewport)

        .addProperty("format", &View3D::GetFormat, &View3D::SetFormat)
        .addProperty("autoUpdate", &View3D::GetAutoUpdate, &View3D::SetAutoUpdate)
    );
}

static void RegisterWindow(kaguya::State& lua)
{
    using namespace kaguya;

    // enum WindowDragMode;
    lua["DRAG_NONE"] = DRAG_NONE;
    lua["DRAG_MOVE"] = DRAG_MOVE;
    lua["DRAG_RESIZE_TOPLEFT"] = DRAG_RESIZE_TOPLEFT;
    lua["DRAG_RESIZE_TOP"] = DRAG_RESIZE_TOP;
    lua["DRAG_RESIZE_TOPRIGHT"] = DRAG_RESIZE_TOPRIGHT;
    lua["DRAG_RESIZE_RIGHT"] = DRAG_RESIZE_RIGHT;
    lua["DRAG_RESIZE_BOTTOMRIGHT"] = DRAG_RESIZE_BOTTOMRIGHT;
    lua["DRAG_RESIZE_BOTTOM"] = DRAG_RESIZE_BOTTOM;
    lua["DRAG_RESIZE_BOTTOMLEFT"] = DRAG_RESIZE_BOTTOMLEFT;
    lua["DRAG_RESIZE_LEFT"] = DRAG_RESIZE_LEFT;

    lua["Window"].setClass(UserdataMetatable<Window, BorderImage>()
        .addStaticFunction("new", &CreateObject<Window>)

        .addFunction("SetMovable", &Window::SetMovable)
        .addFunction("SetResizable", &Window::SetResizable)
        .addFunction("SetFixedWidthResizing", &Window::SetFixedWidthResizing)
        .addFunction("SetFixedHeightResizing", &Window::SetFixedHeightResizing)
        .addFunction("SetResizeBorder", &Window::SetResizeBorder)
        .addFunction("SetModal", &Window::SetModal)
        .addFunction("SetModalShadeColor", &Window::SetModalShadeColor)
        .addFunction("SetModalFrameColor", &Window::SetModalFrameColor)
        .addFunction("SetModalFrameSize", &Window::SetModalFrameSize)
        .addFunction("SetModalAutoDismiss", &Window::SetModalAutoDismiss)

        .addFunction("IsMovable", &Window::IsMovable)
        .addFunction("IsResizable", &Window::IsResizable)
        .addFunction("GetFixedWidthResizing", &Window::GetFixedWidthResizing)
        .addFunction("GetFixedHeightResizing", &Window::GetFixedHeightResizing)
        .addFunction("GetResizeBorder", &Window::GetResizeBorder)
        .addFunction("IsModal", &Window::IsModal)
        .addFunction("GetModalShadeColor", &Window::GetModalShadeColor)
        .addFunction("GetModalFrameColor", &Window::GetModalFrameColor)
        .addFunction("GetModalFrameSize", &Window::GetModalFrameSize)
        .addFunction("GetModalAutoDismiss", &Window::GetModalAutoDismiss)

        .addProperty("movable", &Window::IsMovable, &Window::SetMovable)
        .addProperty("resizable", &Window::IsResizable, &Window::SetResizable)
        .addProperty("fixedWidthResizing", &Window::GetFixedWidthResizing, &Window::SetFixedWidthResizing)
        .addProperty("fixedHeightResizing", &Window::GetFixedHeightResizing, &Window::SetFixedHeightResizing)
        .addProperty("resizeBorder", &Window::GetResizeBorder, &Window::SetResizeBorder)
        .addProperty("modal", &Window::IsModal, &Window::SetModal)
        .addProperty("modalShadeColor", &Window::GetModalShadeColor, &Window::SetModalShadeColor)
        .addProperty("modalFrameColor", &Window::GetModalFrameColor, &Window::SetModalFrameColor)
        .addProperty("modalFrameSize", &Window::GetModalFrameSize, &Window::SetModalFrameSize)
        .addProperty("modalAutoDismiss", &Window::GetModalAutoDismiss, &Window::SetModalAutoDismiss)
    );
}

void RegisterUILuaAPI(kaguya::State& lua)
{
    RegisterUIElement(lua);

    RegisterBorderImage(lua);
    RegisterButton(lua);
    RegisterCheckBox(lua);
    RegisterCursor(lua);

    RegisterMenu(lua);
    RegisterDropDownList(lua);
    RegisterFileSelector(lua);

    RegisterFont(lua);
    RegisterLineEdit(lua);

    RegisterScrollView(lua);
    RegisterListView(lua);

    RegisterMessageBox(lua);
    RegisterScrollBar(lua);

    RegisterSlider(lua);
    RegisterSprite(lua);
    RegisterText(lua);
    RegisterText3D(lua);
    RegisterToolTip(lua);
    RegisterUI(lua);

    RegisterWindow(lua);
    RegisterView3D(lua);

    lua["ui"] = GetSubsystem<UI>();
    lua["GetUI"] = GetSubsystem<UI>;
}
}
