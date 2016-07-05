#include "../Core/Context.h"
#include "../IO/File.h"
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
#include "../UI/UIEvents.h"
#include "../UI/View3D.h"
#include "../UI/Window.h"

#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterBorderImage(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KBorderImage"].setClass(UserdataMetatable<BorderImage, UIElement>()
        .addStaticFunction("new", &KCreateObject<BorderImage>)
        
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
        .addProperty("hoverOffset", &BorderImage::GetHoverOffset)
        .addProperty("blendMode", &BorderImage::GetBlendMode, &BorderImage::SetBlendMode)
        .addProperty("tiled", &BorderImage::IsTiled, &BorderImage::SetTiled)
    );
}

static void RegisterButton(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KButton"].setClass(UserdataMetatable<Button, BorderImage>()
        .addStaticFunction("new", &KCreateObject<Button>)
        
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

        .addProperty("pressedOffset", &Button::GetPressedOffset)
        .addProperty("pressedChildOffset", &Button::GetPressedChildOffset)
        .addProperty("repeatDelay", &Button::GetRepeatDelay, &Button::SetRepeatDelay)
        .addProperty("repeatRate", &Button::GetRepeatRate, &Button::SetRepeatRate)
        .addProperty("pressed", &Button::IsPressed)
    );
}

static void RegisterCheckBox(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KCheckBox"].setClass(UserdataMetatable<CheckBox, BorderImage>()
        .addStaticFunction("new", &KCreateObject<CheckBox>)
        
        .addFunction("SetChecked", &CheckBox::SetChecked)

        .addOverloadedFunctions("SetCheckedOffset",
            static_cast<void(CheckBox::*)(const IntVector2&)>(&CheckBox::SetCheckedOffset),
            static_cast<void(CheckBox::*)(int, int)>(&CheckBox::SetCheckedOffset))

        .addFunction("IsChecked", &CheckBox::IsChecked)
        .addFunction("GetCheckedOffset", &CheckBox::GetCheckedOffset)

        .addProperty("checked", &CheckBox::IsChecked, &CheckBox::SetChecked)
        .addProperty("checkedOffset", &CheckBox::GetCheckedOffset)
    );
}

static void RegisterCursor(kaguya::State& lua)
{
    using namespace kaguya;

    // enum CursorShape;
    lua["KCS_NORMAL"] = CS_NORMAL;
    lua["KCS_IBEAM"] = CS_IBEAM;
    lua["KCS_CROSS"] = CS_CROSS;
    lua["KCS_RESIZEVERTICAL"] = CS_RESIZEVERTICAL;
    lua["KCS_RESIZEDIAGONAL_TOPRIGHT"] = CS_RESIZEDIAGONAL_TOPRIGHT;
    lua["KCS_RESIZEHORIZONTAL"] = CS_RESIZEHORIZONTAL;
    lua["KCS_RESIZEDIAGONAL_TOPLEFT"] = CS_RESIZEDIAGONAL_TOPLEFT;
    lua["KCS_RESIZE_ALL"] = CS_RESIZE_ALL;
    lua["KCS_ACCEPTDROP"] = CS_ACCEPTDROP;
    lua["KCS_REJECTDROP"] = CS_REJECTDROP;
    lua["KCS_BUSY"] = CS_BUSY;
    lua["KCS_BUSY_ARROW"] = CS_BUSY_ARROW;
    lua["KCS_MAX_SHAPES"] = CS_MAX_SHAPES;

    /*
    lua["KCursorShapeInfo"].setClass(UserdataMetatable<CursorShapeInfo>()
            .setConstructors<CursorShapeInfo(), CursorShapeInfo(int)>()

            .addProperty("image", &CursorShapeInfo::image_)
            .addProperty("texture", &CursorShapeInfo::texture_)
            .addProperty("imageRect", &CursorShapeInfo::imageRect_)
            .addProperty("hotSpot", &CursorShapeInfo::hotSpot_)
        );
        */

    lua["KCursor"].setClass(UserdataMetatable<Cursor, BorderImage>()
        .addStaticFunction("new", &KCreateObject<Cursor>)
        
        .addOverloadedFunctions("DefineShape",
            static_cast<void(Cursor::*)(const String&, Image*, const IntRect&, const IntVector2&)>(&Cursor::DefineShape),
            static_cast<void(Cursor::*)(CursorShape, Image*, const IntRect&, const IntVector2&)>(&Cursor::DefineShape))

        .addOverloadedFunctions("SetShape",
            static_cast<void(Cursor::*)(const String&)>(&Cursor::SetShape),
            static_cast<void(Cursor::*)(CursorShape)>(&Cursor::SetShape))

        .addFunction("SetUseSystemShapes", &Cursor::SetUseSystemShapes)
        
        .addFunction("GetShape", &Cursor::GetShape)
        .addFunction("GetUseSystemShapes", &Cursor::GetUseSystemShapes)
        
        .addProperty("shape", &Cursor::GetShape)
        .addProperty("useSystemShapes", &Cursor::GetUseSystemShapes, &Cursor::SetUseSystemShapes)
    );
}

static void RegisterDropDownList(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDropDownList"].setClass(UserdataMetatable<DropDownList, Menu>()
        .addStaticFunction("new", &KCreateObject<DropDownList>)
        
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
        .addFunction("GetItem", &DropDownList::GetItem)
        
        // .addFunction("GetItems", &DropDownList::GetItems)

        .addFunction("GetSelection", &DropDownList::GetSelection)
        .addFunction("GetSelectedItem", &DropDownList::GetSelectedItem)
        .addFunction("GetListView", &DropDownList::GetListView)
        .addFunction("GetPlaceholder", &DropDownList::GetPlaceholder)
        .addFunction("GetPlaceholderText", &DropDownList::GetPlaceholderText)
        .addFunction("GetResizePopup", &DropDownList::GetResizePopup)

        .addProperty("numItems", &DropDownList::GetNumItems)
        // .addProperty("items", &DropDownList::GetItems)
        .addProperty("selection", &DropDownList::GetSelection, &DropDownList::SetSelection)
        .addProperty("selectedItem", &DropDownList::GetSelectedItem)
        .addProperty("listView", &DropDownList::GetListView)
        .addProperty("placeholder", &DropDownList::GetPlaceholder)
        .addProperty("placeholderText", &DropDownList::GetPlaceholderText, &DropDownList::SetPlaceholderText)
        .addProperty("resizePopup", &DropDownList::GetResizePopup, &DropDownList::SetResizePopup)
    );
}

static void RegisterFileSelector(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KFileSelector"].setClass(UserdataMetatable<FileSelector, Object>()
        .addStaticFunction("new", &KCreateObject<FileSelector>)
        
        .addFunction("SetDefaultStyle", &FileSelector::SetDefaultStyle)
        .addFunction("SetTitle", &FileSelector::SetTitle)
        .addFunction("SetButtonTexts", &FileSelector::SetButtonTexts)
        .addFunction("SetPath", &FileSelector::SetPath)
        .addFunction("SetFileName", &FileSelector::SetFileName)
        .addFunction("SetFilters", &FileSelector::SetFilters)
        .addFunction("SetDirectoryMode", &FileSelector::SetDirectoryMode)
        
        // .addFunction("UpdateElements", &FileSelector::UpdateElements)

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
        .addProperty("oKButton", &FileSelector::GetOKButton)
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

    // lua["KFONT_TEXTURE_MIN_SIZE"] = FONT_TEXTURE_MIN_SIZE;
    // lua["KFONT_DPI"] = FONT_DPI;

    // enum FONT_TYPE;
    lua["KFONT_NONE"] = FONT_NONE;
    lua["KFONT_FREETYPE"] = FONT_FREETYPE;
    lua["KFONT_BITMAP"] = FONT_BITMAP;
    lua["KMAX_FONT_TYPES"] = MAX_FONT_TYPES;

    lua["KFont"].setClass(UserdataMetatable<Font, Resource>()
        .addStaticFunction("new", &KCreateObject<Font>)

        .addFunction("GetFace", &Font::GetFace)
        .addFunction("IsSDFFont", &Font::IsSDFFont)
        
        // .addFunction("GetAbsoluteGlyphOffset", &Font::GetAbsoluteGlyphOffset)
        // .addFunction("GetScaledGlyphOffset", &Font::GetScaledGlyphOffset)
        // .addFunction("GetTotalGlyphOffset", &Font::GetTotalGlyphOffset)
        // .addFunction("ReleaseFaces", &Font::ReleaseFaces)

        .addProperty("sdfFont", &Font::IsSDFFont)
    );
}

static void RegisterLineEdit(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KLineEdit"].setClass(UserdataMetatable<LineEdit, BorderImage>()
        .addStaticFunction("new", &KCreateObject<LineEdit>)
        
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

static void RegisterListView(kaguya::State& lua)
{
    using namespace kaguya;

    // enum HighlightMode;
    lua["KHM_NEVER"] = HM_NEVER;
    lua["KHM_FOCUS"] = HM_FOCUS;
    lua["KHM_ALWAYS"] = HM_ALWAYS;

    lua["KListView"].setClass(UserdataMetatable<ListView, ScrollView>()
        .addStaticFunction("new", &KCreateObject<ListView>)
        
        .addFunction("AddItem", &ListView::AddItem)
        .addFunction("InsertItem", &ListView::InsertItem)

        .addOverloadedFunctions("RemoveItem",
            static_cast<void(ListView::*)(UIElement*, unsigned)>(&ListView::RemoveItem),
            static_cast<void(ListView::*)(unsigned)>(&ListView::RemoveItem))

        .addFunction("RemoveAllItems", &ListView::RemoveAllItems)
        .addFunction("SetSelection", &ListView::SetSelection)
        
        // .addFunction("SetSelections", &ListView::SetSelections)

        .addFunction("AddSelection", &ListView::AddSelection)
        .addFunction("RemoveSelection", &ListView::RemoveSelection)
        .addFunction("ToggleSelection", &ListView::ToggleSelection)
        .addFunction("ChangeSelection", &ListView::ChangeSelection)
        .addFunction("ClearSelection", &ListView::ClearSelection)
        .addFunction("SetHighlightMode", &ListView::SetHighlightMode)
        .addFunction("SetMultiselect", &ListView::SetMultiselect)
        .addFunction("SetHierarchyMode", &ListView::SetHierarchyMode)
        .addFunction("SetBaseIndent", &ListView::SetBaseIndent)
        .addFunction("SetClearSelectionOnDefocus", &ListView::SetClearSelectionOnDefocus)
        .addFunction("SetSelectOnClickEnd", &ListView::SetSelectOnClickEnd)
        .addFunction("Expand", &ListView::Expand)
        .addFunction("ToggleExpand", &ListView::ToggleExpand)

        .addFunction("GetNumItems", &ListView::GetNumItems)
        .addFunction("GetItem", &ListView::GetItem)
        
        // .addFunction("GetItems", &ListView::GetItems)

        .addFunction("FindItem", &ListView::FindItem)
        .addFunction("GetSelection", &ListView::GetSelection)
        
        // .addFunction("GetSelections", &ListView::GetSelections)

        .addFunction("CopySelectedItemsToClipboard", &ListView::CopySelectedItemsToClipboard)
        .addFunction("GetSelectedItem", &ListView::GetSelectedItem)
        .addFunction("GetSelectedItems", &ListView::GetSelectedItems)
        .addFunction("IsSelected", &ListView::IsSelected)
        .addFunction("IsExpanded", &ListView::IsExpanded)
        .addFunction("GetHighlightMode", &ListView::GetHighlightMode)
        .addFunction("GetMultiselect", &ListView::GetMultiselect)
        .addFunction("GetClearSelectionOnDefocus", &ListView::GetClearSelectionOnDefocus)
        .addFunction("GetSelectOnClickEnd", &ListView::GetSelectOnClickEnd)
        .addFunction("GetHierarchyMode", &ListView::GetHierarchyMode)
        .addFunction("GetBaseIndent", &ListView::GetBaseIndent)

        .addOverloadedFunctions("EnsureItemVisibility",
            static_cast<void(ListView::*)(unsigned)>(&ListView::EnsureItemVisibility),
            static_cast<void(ListView::*)(UIElement*)>(&ListView::EnsureItemVisibility))


        .addProperty("numItems", &ListView::GetNumItems)
        // .addProperty("items", &ListView::GetItems)
        .addProperty("selection", &ListView::GetSelection, &ListView::SetSelection)
        .addProperty("selections", &ListView::GetSelections, &ListView::SetSelections)
        .addProperty("selectedItem", &ListView::GetSelectedItem)
        .addProperty("selectedItems", &ListView::GetSelectedItems)
        .addProperty("highlightMode", &ListView::GetHighlightMode, &ListView::SetHighlightMode)
        .addProperty("multiselect", &ListView::GetMultiselect, &ListView::SetMultiselect)
        .addProperty("clearSelectionOnDefocus", &ListView::GetClearSelectionOnDefocus, &ListView::SetClearSelectionOnDefocus)
        .addProperty("selectOnClickEnd", &ListView::GetSelectOnClickEnd, &ListView::SetSelectOnClickEnd)
        .addProperty("hierarchyMode", &ListView::GetHierarchyMode, &ListView::SetHierarchyMode)
        .addProperty("baseIndent", &ListView::GetBaseIndent, &ListView::SetBaseIndent)
    );
}

static void RegisterMenu(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KMenu"].setClass(UserdataMetatable<Menu, Button>()
        .addStaticFunction("new", &KCreateObject<Menu>)
        
        .addFunction("SetPopup", &Menu::SetPopup)

        .addOverloadedFunctions("SetPopupOffset",
            static_cast<void(Menu::*)(const IntVector2&)>(&Menu::SetPopupOffset),
            static_cast<void(Menu::*)(int, int)>(&Menu::SetPopupOffset))

        .addFunction("ShowPopup", &Menu::ShowPopup)
        .addFunction("SetAccelerator", &Menu::SetAccelerator)

        .addFunction("GetPopup", &Menu::GetPopup)
        .addFunction("GetPopupOffset", &Menu::GetPopupOffset)
        .addFunction("GetShowPopup", &Menu::GetShowPopup)
        .addFunction("GetAcceleratorKey", &Menu::GetAcceleratorKey)
        .addFunction("GetAcceleratorQualifiers", &Menu::GetAcceleratorQualifiers)

        .addProperty("popup", &Menu::GetPopup, &Menu::SetPopup)
        .addProperty("popupOffset", &Menu::GetPopupOffset)
        .addProperty("showPopup", &Menu::GetShowPopup)
        .addProperty("acceleratorKey", &Menu::GetAcceleratorKey)
        .addProperty("acceleratorQualifiers", &Menu::GetAcceleratorQualifiers)
    );
}

static void RegisterMessageBox(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KMessageBox"].setClass(UserdataMetatable<MessageBox, Object>()
        .addStaticFunction("new", &KCreateObject<MessageBox>)
        
        .addFunction("SetTitle", &MessageBox::SetTitle)
        .addFunction("SetMessage", &MessageBox::SetMessage)
        
        .addFunction("GetTitle", &MessageBox::GetTitle)
        .addFunction("GetMessage", &MessageBox::GetMessage)
        
        .addFunction("GetWindow", &MessageBox::GetWindow)

        .addProperty("title", &MessageBox::GetTitle, &MessageBox::SetTitle)
        .addProperty("message", &MessageBox::GetMessage, &MessageBox::SetMessage)
        .addProperty("window", &MessageBox::GetWindow)
    );
}

static void RegisterScrollBar(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KScrollBar"].setClass(UserdataMetatable<ScrollBar, BorderImage>()
        .addStaticFunction("new", &KCreateObject<FileSelector>)
        
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

static void RegisterScrollView(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KScrollView"].setClass(UserdataMetatable<ScrollView, UIElement>()
        .addStaticFunction("new", &KCreateObject<ScrollView>)
        
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
        .addFunction("GetContentElement", &ScrollView::GetContentElement)
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

        .addProperty("viewPosition", &ScrollView::GetViewPosition)
        .addProperty("contentElement", &ScrollView::GetContentElement, &ScrollView::SetContentElement)
        .addProperty("horizontalScrollBar", &ScrollView::GetHorizontalScrollBar)
        .addProperty("verticalScrollBar", &ScrollView::GetVerticalScrollBar)
        .addProperty("scrollPanel", &ScrollView::GetScrollPanel)
        .addProperty("scrollBarsAutoVisible", &ScrollView::GetScrollBarsAutoVisible, &ScrollView::SetScrollBarsAutoVisible)
        .addProperty("scrollStep", &ScrollView::GetScrollStep, &ScrollView::SetScrollStep)
        .addProperty("pageStep", &ScrollView::GetPageStep, &ScrollView::SetPageStep)
        .addProperty("scrollDeceleration", &ScrollView::GetScrollDeceleration, &ScrollView::SetScrollDeceleration)
        .addProperty("scrollSnapEpsilon", &ScrollView::GetScrollSnapEpsilon, &ScrollView::SetScrollSnapEpsilon)
        .addProperty("autoDisableChildren", &ScrollView::GetAutoDisableChildren, &ScrollView::SetAutoDisableChildren)
        .addProperty("autoDisableThreshold", &ScrollView::GetAutoDisableThreshold, &ScrollView::SetAutoDisableThreshold)
    );
}

static void RegisterSlider(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KSlider"].setClass(UserdataMetatable<Slider, BorderImage>()
        .addStaticFunction("new", &KCreateObject<Slider>)
        
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

    lua["KSprite"].setClass(UserdataMetatable<Sprite, UIElement>()
        .addStaticFunction("new", &KCreateObject<Sprite>)
        
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

        .addProperty("screenPosition", &Sprite::GetScreenPosition)
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

static void RegisterText(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KDEFAULT_FONT_SIZE"] = DEFAULT_FONT_SIZE;

    // enum TextEffect;
    lua["KTE_NONE"] = TE_NONE;
    lua["KTE_SHADOW"] = TE_SHADOW;
    lua["KTE_STROKE"] = TE_STROKE;

    lua["KText"].setClass(UserdataMetatable<Text, UIElement>()
        .addStaticFunction("new", &KCreateObject<Text>)
        
        .addOverloadedFunctions("SetFont",
            static_cast<bool(Text::*)(const String&, int)>(&Text::SetFont),
            static_cast<bool(Text::*)(Font*, int)>(&Text::SetFont))

        .addFunction("SetText", &Text::SetText)
        .addFunction("SetTextAlignment", &Text::SetTextAlignment)
        .addFunction("SetRowSpacing", &Text::SetRowSpacing)
        .addFunction("SetWordwrap", &Text::SetWordwrap)
        .addFunction("SetAutoLocalizable", &Text::SetAutoLocalizable)
        .addFunction("SetSelection", &Text::SetSelection)
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

static void RegisterText3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KText3D"].setClass(UserdataMetatable<Text3D, Drawable>()
        .addStaticFunction("new", &KCreateObject<Text3D>)
        
        .addOverloadedFunctions("SetFont",
            static_cast<bool(Text3D::*)(const String&, int)>(&Text3D::SetFont),
            static_cast<bool(Text3D::*)(Font*, int)>(&Text3D::SetFont))

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
        .addFunction("GetColor", &Text3D::GetColor)
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
        .addProperty("opacity", &Text3D::GetOpacity, &Text3D::SetOpacity)
        .addProperty("fixedScreenSize", &Text3D::IsFixedScreenSize, &Text3D::SetFixedScreenSize)
        .addProperty("faceCameraMode", &Text3D::GetFaceCameraMode, &Text3D::SetFaceCameraMode)
    );
}

static void RegisterToolTip(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KToolTip"].setClass(UserdataMetatable<ToolTip, UIElement>()
        .addStaticFunction("new", &KCreateObject<ToolTip>)
        
        .addFunction("SetDelay", &ToolTip::SetDelay)
        .addFunction("GetDelay", &ToolTip::GetDelay)

        .addProperty("delay", &ToolTip::GetDelay, &ToolTip::SetDelay)
    );
}

static SharedPtr<UIElement> UILoadLayout(UI* ui, const char* filepath, XMLFile* styleFile = 0)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<UIElement>();

    return ui->LoadLayout(*file, styleFile);
}

static bool UISaveLayout(UI* ui, const char* filepath, UIElement* element)
{
    if (!element)
        return false;

    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    return ui->SaveLayout(*file, element);
}

static void RegisterUI(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KUI"].setClass(UserdataMetatable<UI, Object>()

        .addFunction("SetCursor", &UI::SetCursor)
        .addFunction("SetFocusElement", &UI::SetFocusElement)
        .addFunction("SetModalElement", &UI::SetModalElement)
        .addFunction("Clear", &UI::Clear)

        .addStaticFunction("LoadLayout", &UILoadLayout)
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

        .addFunction("GetRoot", &UI::GetRoot)
        .addFunction("GetRootModalElement", &UI::GetRootModalElement)
        .addFunction("GetCursor", &UI::GetCursor)
        .addFunction("GetCursorPosition", &UI::GetCursorPosition)

        .addOverloadedFunctions("GetElementAt",
            static_cast<UIElement*(UI::*)(const IntVector2&, bool)>(&UI::GetElementAt),
            static_cast<UIElement*(UI::*)(int, int, bool)>(&UI::GetElementAt))

        .addFunction("GetFocusElement", &UI::GetFocusElement)
        .addFunction("GetFrontElement", &UI::GetFrontElement)
        
        // .addFunction("GetDragElements", &UI::GetDragElements)

        .addFunction("GetNumDragElements", &UI::GetNumDragElements)
        .addFunction("GetDragElement", &UI::GetDragElement)
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

        .addProperty("root", &UI::GetRoot)
        .addProperty("rootModalElement", &UI::GetRootModalElement)
        .addProperty("cursor", &UI::GetCursor, &UI::SetCursor)
        .addProperty("cursorPosition", &UI::GetCursorPosition)
        .addProperty("focusElement", &UI::GetFocusElement)
        .addProperty("frontElement", &UI::GetFrontElement)
        
        // .addProperty("dragElements", &UI::GetDragElements)

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
        .addProperty("dragging", &UI::IsDragging)
        .addProperty("scale", &UI::GetScale, &UI::SetScale)
        .addProperty("width", &UI::SetWidth)
        .addProperty("height", &UI::SetHeight)
    );
}

static bool UIElementLoadXML(UIElement* uiElement, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return uiElement->LoadXML(*file);
}

static bool UIElementSaveXML(const UIElement* uiElement, const char* filepath, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    return uiElement->SaveXML(*file, indentation);
}

static SharedPtr<UIElement> UIElementCreateChild(UIElement* uiElement, const char* type, const String& name = String::EMPTY, unsigned index = M_MAX_UNSIGNED)
{
    return SharedPtr<UIElement>(uiElement->CreateChild(StringHash(type), name, index));
}

static const Color& UIElementGetColor(const UIElement* uiElement)
{
    return uiElement->GetColor(C_TOPLEFT);
}

static void RegisterUIElement(kaguya::State& lua)
{
    using namespace kaguya;

    // enum HorizontalAlignment;
    lua["KHA_LEFT"] = HA_LEFT;
    lua["KHA_CENTER"] = HA_CENTER;
    lua["KHA_RIGHT"] = HA_RIGHT;

    // enum VerticalAlignment;
    lua["KVA_TOP"] = VA_TOP;
    lua["KVA_CENTER"] = VA_CENTER;
    lua["KVA_BOTTOM"] = VA_BOTTOM;

    // enum Corner;
    lua["KC_TOPLEFT"] = C_TOPLEFT;
    lua["KC_TOPRIGHT"] = C_TOPRIGHT;
    lua["KC_BOTTOMLEFT"] = C_BOTTOMLEFT;
    lua["KC_BOTTOMRIGHT"] = C_BOTTOMRIGHT;
    lua["KMAX_UIELEMENT_CORNERS"] = MAX_UIELEMENT_CORNERS;

    // enum Orientation;
    lua["KO_HORIZONTAL"] = O_HORIZONTAL;
    lua["KO_VERTICAL"] = O_VERTICAL;

    // enum FocusMode;
    lua["KFM_NOTFOCUSABLE"] = FM_NOTFOCUSABLE;
    lua["KFM_RESETFOCUS"] = FM_RESETFOCUS;
    lua["KFM_FOCUSABLE"] = FM_FOCUSABLE;
    lua["KFM_FOCUSABLE_DEFOCUSABLE"] = FM_FOCUSABLE_DEFOCUSABLE;

    // enum LayoutMode;
    lua["KLM_FREE"] = LM_FREE;
    lua["KLM_HORIZONTAL"] = LM_HORIZONTAL;
    lua["KLM_VERTICAL"] = LM_VERTICAL;

    // enum TraversalMode;
    lua["KTM_BREADTH_FIRST"] = TM_BREADTH_FIRST;
    lua["KTM_DEPTH_FIRST"] = TM_DEPTH_FIRST;

    lua["KDD_DISABLED"] = DD_DISABLED;
    lua["KDD_SOURCE"] = DD_SOURCE;
    lua["KDD_TARGET"] = DD_TARGET;
    lua["KDD_SOURCE_AND_TARGET"] = DD_SOURCE_AND_TARGET;

    lua["KUIElement"].setClass(UserdataMetatable<UIElement, Animatable>()
        .addStaticFunction("new", &KCreateObject<UIElement>)

        .addStaticFunction("LoadXML", UIElementLoadXML)
        .addStaticFunction("SaveXML", UIElementSaveXML)

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
            static_cast<bool(UIElement::*)(const String&, XMLFile*)>(&UIElement::SetStyle),
            static_cast<bool(UIElement::*)(const XMLElement&)>(&UIElement::SetStyle))

        .addFunction("SetStyleAuto", &UIElement::SetStyleAuto)
        .addFunction("SetDefaultStyle", &UIElement::SetDefaultStyle)
        .addFunction("SetLayout", &UIElement::SetLayout)
        .addFunction("SetLayoutMode", &UIElement::SetLayoutMode)
        .addFunction("SetLayoutSpacing", &UIElement::SetLayoutSpacing)
        .addFunction("SetLayoutBorder", &UIElement::SetLayoutBorder)
        .addFunction("SetLayoutFlexScale", &UIElement::SetLayoutFlexScale)
        .addFunction("SetIndent", &UIElement::SetIndent)
        .addFunction("SetIndentSpacing", &UIElement::SetIndentSpacing)
        
        // .addFunction("UpdateLayout", &UIElement::UpdateLayout)

        .addFunction("DisableLayoutUpdate", &UIElement::DisableLayoutUpdate)
        .addFunction("EnableLayoutUpdate", &UIElement::EnableLayoutUpdate)
        .addFunction("BringToFront", &UIElement::BringToFront)
        
        .addStaticFunction("CreateChild", &UIElementCreateChild)

        .addFunction("AddChild", &UIElement::AddChild)
        .addFunction("InsertChild", &UIElement::InsertChild)
        .addFunction("RemoveChild", &UIElement::RemoveChild)
        .addFunction("RemoveChildAtIndex", &UIElement::RemoveChildAtIndex)
        .addFunction("RemoveAllChildren", &UIElement::RemoveAllChildren)
        .addFunction("Remove", &UIElement::Remove)
        .addFunction("FindChild", &UIElement::FindChild)
        .addFunction("SetParent", &UIElement::SetParent)
        .addFunction("SetVar", &UIElement::SetVar)
        .addFunction("SetInternal", &UIElement::SetInternal)
        .addFunction("SetTraversalMode", &UIElement::SetTraversalMode)
        .addFunction("SetElementEventSender", &UIElement::SetElementEventSender)
        .addFunction("SetTags", &UIElement::SetTags)
        .addFunction("AddTag", &UIElement::AddTag)

        .addOverloadedFunctions("AddTags",
            static_cast<void(UIElement::*)(const String&, char)>(&UIElement::AddTags),
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
        .addFunction("GetColor", &UIElement::GetColor)
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
        .addFunction("GetDefaultStyle", &UIElement::GetDefaultStyle)
        .addFunction("GetLayoutMode", &UIElement::GetLayoutMode)
        .addFunction("GetLayoutSpacing", &UIElement::GetLayoutSpacing)
        .addFunction("GetLayoutBorder", &UIElement::GetLayoutBorder)
        .addFunction("GetLayoutFlexScale", &UIElement::GetLayoutFlexScale)
        .addFunction("GetNumChildren", &UIElement::GetNumChildren)

        .addOverloadedFunctions("GetChild",
            static_cast<UIElement*(UIElement::*)(unsigned) const>(&UIElement::GetChild),
            static_cast<UIElement*(UIElement::*)(const String&, bool) const>(&UIElement::GetChild),
            static_cast<UIElement*(UIElement::*)(const StringHash&, const Variant&, bool) const>(&UIElement::GetChild))

        /*
        .addOverloadedFunctions("GetChildren",
            static_cast<const Vector<SharedPtr<UIElement> >&(UIElement::*)() const>(&UIElement::GetChildren),
            static_cast<void(UIElement::*)(PODVector<UIElement*>&, bool) const>(&UIElement::GetChildren))
            */

        .addFunction("GetParent", &UIElement::GetParent)
        .addFunction("GetRoot", &UIElement::GetRoot)
        .addFunction("GetDerivedColor", &UIElement::GetDerivedColor)
        .addFunction("GetVar", &UIElement::GetVar)
        .addFunction("GetVars", &UIElement::GetVars)
        .addFunction("HasTag", &UIElement::HasTag)
        .addFunction("GetTags", &UIElement::GetTags)
        .addFunction("GetChildrenWithTag", &UIElement::GetChildrenWithTag)
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
        .addFunction("SetChildOffset", &UIElement::SetChildOffset)
        .addFunction("SetHovering", &UIElement::SetHovering)
        .addFunction("AdjustScissor", &UIElement::AdjustScissor)

        .addFunction("GetTraversalMode", &UIElement::GetTraversalMode)
        .addFunction("IsElementEventSender", &UIElement::IsElementEventSender)
        .addFunction("GetElementEventSender", &UIElement::GetElementEventSender)
        .addFunction("GetEffectiveMinSize", &UIElement::GetEffectiveMinSize)

        .addProperty("screenPosition", &UIElement::GetScreenPosition)
        .addProperty("name", &UIElement::GetName, &UIElement::SetName)
        .addProperty("position", &UIElement::GetPosition)
        .addProperty("size", &UIElement::GetSize)
        .addProperty("width", &UIElement::GetWidth, &UIElement::SetWidth)
        .addProperty("height", &UIElement::GetHeight, &UIElement::SetHeight)
        .addProperty("minSize", &UIElement::GetMinSize)
        .addProperty("minWidth", &UIElement::GetMinWidth, &UIElement::SetMinWidth)
        .addProperty("minHeight", &UIElement::GetMinHeight, &UIElement::SetMinHeight)
        .addProperty("maxSize", &UIElement::GetMaxSize)
        .addProperty("maxWidth", &UIElement::GetMaxWidth, &UIElement::SetMaxWidth)
        .addProperty("maxHeight", &UIElement::GetMaxHeight, &UIElement::SetMaxHeight)
        .addProperty("fixedSize", &UIElement::IsFixedSize)
        .addProperty("fixedWidth", &UIElement::IsFixedWidth, &UIElement::SetFixedWidth)
        .addProperty("fixedHeight", &UIElement::IsFixedHeight, &UIElement::SetFixedHeight)
        .addProperty("childOffset", &UIElement::GetChildOffset, &UIElement::SetChildOffset)
        .addProperty("horizontalAlignment", &UIElement::GetHorizontalAlignment, &UIElement::SetHorizontalAlignment)
        .addProperty("verticalAlignment", &UIElement::GetVerticalAlignment, &UIElement::SetVerticalAlignment)
        .addProperty("clipBorder", &UIElement::GetClipBorder, &UIElement::SetClipBorder)        
        .addProperty("priority", &UIElement::GetPriority, &UIElement::SetPriority)
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
        .addProperty("layoutMode", &UIElement::GetLayoutMode, &UIElement::SetLayoutMode)
        .addProperty("layoutSpacing", &UIElement::GetLayoutSpacing, &UIElement::SetLayoutSpacing)
        .addProperty("layoutBorder", &UIElement::GetLayoutBorder, &UIElement::SetLayoutBorder)
        .addProperty("layoutFlexScale", &UIElement::GetLayoutFlexScale, &UIElement::SetLayoutFlexScale)
        .addProperty("parent", &UIElement::GetParent)
        .addProperty("root", &UIElement::GetRoot)
        .addProperty("derivedColor", &UIElement::GetDerivedColor)
        .addProperty("vars", &UIElement::GetVars)
        .addProperty("tags", &UIElement::GetTags, &UIElement::SetTags)
        .addProperty("dragButtonCombo", &UIElement::GetDragButtonCombo)
        .addProperty("dragButtonCount", &UIElement::GetDragButtonCount)
        .addProperty("combinedScreenRect", &UIElement::GetCombinedScreenRect)
        .addProperty("layoutElementMaxSize", &UIElement::GetLayoutElementMaxSize)
        .addProperty("indent", &UIElement::GetIndent, &UIElement::SetIndent)
        .addProperty("indentSpacing", &UIElement::GetIndentSpacing, &UIElement::SetIndentSpacing)
        .addProperty("indentWidth", &UIElement::GetIndentWidth)
        .addProperty("traversalMode", &UIElement::GetTraversalMode, &UIElement::SetTraversalMode)
        .addProperty("elementEventSender", &UIElement::IsElementEventSender, &UIElement::SetElementEventSender)
        .addProperty("effectiveMinSize", &UIElement::GetEffectiveMinSize)
        .addProperty("deepEnabled", &UIElement::SetDeepEnabled)
        .addProperty("enabledRecursive", &UIElement::SetEnabledRecursive)
        .addProperty("focus", &UIElement::SetFocus)
        .addProperty("styleAuto", &UIElement::SetStyleAuto)
        .addProperty("defaultStyle", &UIElement::SetDefaultStyle)
    );
}

static void RegisterUIEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KE_UIMOUSECLICK"] = E_UIMOUSECLICK;
    lua["KE_UIMOUSECLICKEND"] = E_UIMOUSECLICKEND;
    lua["KE_UIMOUSEDOUBLECLICK"] = E_UIMOUSEDOUBLECLICK;
    lua["KE_CLICK"] = E_CLICK;
    lua["KE_CLICKEND"] = E_CLICKEND;
    lua["KE_DOUBLECLICK"] = E_DOUBLECLICK;
    lua["KE_DRAGDROPTEST"] = E_DRAGDROPTEST;
    lua["KE_DRAGDROPFINISH"] = E_DRAGDROPFINISH;
    lua["KE_FOCUSCHANGED"] = E_FOCUSCHANGED;
    lua["KE_NAMECHANGED"] = E_NAMECHANGED;
    lua["KE_RESIZED"] = E_RESIZED;
    lua["KE_POSITIONED"] = E_POSITIONED;
    lua["KE_VISIBLECHANGED"] = E_VISIBLECHANGED;
    lua["KE_FOCUSED"] = E_FOCUSED;
    lua["KE_DEFOCUSED"] = E_DEFOCUSED;
    lua["KE_LAYOUTUPDATED"] = E_LAYOUTUPDATED;
    lua["KE_PRESSED"] = E_PRESSED;
    lua["KE_RELEASED"] = E_RELEASED;
    lua["KE_TOGGLED"] = E_TOGGLED;
    lua["KE_SLIDERCHANGED"] = E_SLIDERCHANGED;
    lua["KE_SLIDERPAGED"] = E_SLIDERPAGED;
    lua["KE_SCROLLBARCHANGED"] = E_SCROLLBARCHANGED;
    lua["KE_VIEWCHANGED"] = E_VIEWCHANGED;
    lua["KE_MODALCHANGED"] = E_MODALCHANGED;
    lua["KE_TEXTENTRY"] = E_TEXTENTRY;
    lua["KE_TEXTCHANGED"] = E_TEXTCHANGED;
    lua["KE_TEXTFINISHED"] = E_TEXTFINISHED;
    lua["KE_MENUSELECTED"] = E_MENUSELECTED;
    lua["KE_ITEMSELECTED"] = E_ITEMSELECTED;
    lua["KE_ITEMDESELECTED"] = E_ITEMDESELECTED;
    lua["KE_SELECTIONCHANGED"] = E_SELECTIONCHANGED;
    lua["KE_ITEMCLICKED"] = E_ITEMCLICKED;
    lua["KE_ITEMDOUBLECLICKED"] = E_ITEMDOUBLECLICKED;
    lua["KE_UNHANDLEDKEY"] = E_UNHANDLEDKEY;
    lua["KE_FILESELECTED"] = E_FILESELECTED;
    lua["KE_MESSAGEACK"] = E_MESSAGEACK;
    lua["KE_ELEMENTADDED"] = E_ELEMENTADDED;
    lua["KE_ELEMENTREMOVED"] = E_ELEMENTREMOVED;
    lua["KE_HOVERBEGIN"] = E_HOVERBEGIN;
    lua["KE_HOVEREND"] = E_HOVEREND;
    lua["KE_DRAGBEGIN"] = E_DRAGBEGIN;
    lua["KE_DRAGMOVE"] = E_DRAGMOVE;
    lua["KE_DRAGEND"] = E_DRAGEND;
    lua["KE_DRAGCANCEL"] = E_DRAGCANCEL;
    lua["KE_UIDROPFILE"] = E_UIDROPFILE;
}

static void RegisterView3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KView3D"].setClass(UserdataMetatable<View3D, Window>()
        .addStaticFunction("new", &KCreateObject<View3D>)
        
        .addFunction("SetView", &View3D::SetView)
        .addFunction("SetFormat", &View3D::SetFormat)
        .addFunction("SetAutoUpdate", &View3D::SetAutoUpdate)
        
        .addFunction("GetFormat", &View3D::GetFormat)
        .addFunction("GetAutoUpdate", &View3D::GetAutoUpdate)
        .addFunction("GetScene", &View3D::GetScene)
        .addFunction("GetCameraNode", &View3D::GetCameraNode)
        .addFunction("GetRenderTexture", &View3D::GetRenderTexture)
        .addFunction("GetDepthTexture", &View3D::GetDepthTexture)
        .addFunction("GetViewport", &View3D::GetViewport)

        .addProperty("format", &View3D::GetFormat, &View3D::SetFormat)
        .addProperty("autoUpdate", &View3D::GetAutoUpdate, &View3D::SetAutoUpdate)
        .addProperty("scene", &View3D::GetScene)
        .addProperty("cameraNode", &View3D::GetCameraNode)
        .addProperty("renderTexture", &View3D::GetRenderTexture)
        .addProperty("depthTexture", &View3D::GetDepthTexture)
        .addProperty("viewport", &View3D::GetViewport)
    );
}

static void RegisterWindow(kaguya::State& lua)
{
    using namespace kaguya;

    // enum WindowDragMode;
    lua["KDRAG_NONE"] = DRAG_NONE;
    lua["KDRAG_MOVE"] = DRAG_MOVE;
    lua["KDRAG_RESIZE_TOPLEFT"] = DRAG_RESIZE_TOPLEFT;
    lua["KDRAG_RESIZE_TOP"] = DRAG_RESIZE_TOP;
    lua["KDRAG_RESIZE_TOPRIGHT"] = DRAG_RESIZE_TOPRIGHT;
    lua["KDRAG_RESIZE_RIGHT"] = DRAG_RESIZE_RIGHT;
    lua["KDRAG_RESIZE_BOTTOMRIGHT"] = DRAG_RESIZE_BOTTOMRIGHT;
    lua["KDRAG_RESIZE_BOTTOM"] = DRAG_RESIZE_BOTTOM;
    lua["KDRAG_RESIZE_BOTTOMLEFT"] = DRAG_RESIZE_BOTTOMLEFT;
    lua["KDRAG_RESIZE_LEFT"] = DRAG_RESIZE_LEFT;

    lua["KWindow"].setClass(UserdataMetatable<Window, BorderImage>()
        .addStaticFunction("new", &KCreateObject<Window>)
        
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

    RegisterUIEvents(lua);

    RegisterWindow(lua);
    RegisterView3D(lua);

    lua["kui"] = KGetSubsystem<UI>();
    lua["KGetUI"] = KGetSubsystem<UI>;
}
}
