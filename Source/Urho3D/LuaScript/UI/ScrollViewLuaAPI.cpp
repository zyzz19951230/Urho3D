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

#include "../../UI/BorderImage.h"
#include "../../UI/ScrollBar.h"
#include "../../UI/ScrollView.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void ScrollViewSetContentElement(ScrollView* self, UIElement* contentElement)
{
    self->SetContentElement(contentElement);
}

static SharedPtr<UIElement> ScrollViewGetContentElement(const ScrollView* self)
{
    return SharedPtr<UIElement>(self->GetContentElement());
}

void RegisterScrollView(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] ScrollView : UIElement
    lua["ScrollView"].setClass(UserdataMetatable<ScrollView, UIElement>()
        .addStaticFunction("new", &CreateObject<ScrollView>)

        // [Method] void SetContentElement(UIElement* element)
        .addFunction("SetContentElement", &ScrollView::SetContentElement)

        .addOverloadedFunctions("SetViewPosition",
            static_cast<void(ScrollView::*)(const IntVector2&)>(&ScrollView::SetViewPosition),
            static_cast<void(ScrollView::*)(int, int)>(&ScrollView::SetViewPosition))

        // [Method] void SetScrollBarsVisible(bool horizontal, bool vertical)
        .addFunction("SetScrollBarsVisible", &ScrollView::SetScrollBarsVisible)
        // [Method] void SetScrollBarsAutoVisible(bool enable)
        .addFunction("SetScrollBarsAutoVisible", &ScrollView::SetScrollBarsAutoVisible)
        // [Method] void SetScrollStep(float step)
        .addFunction("SetScrollStep", &ScrollView::SetScrollStep)
        // [Method] void SetPageStep(float step)
        .addFunction("SetPageStep", &ScrollView::SetPageStep)
        // [Method] void SetScrollDeceleration(float deceleration)
        .addFunction("SetScrollDeceleration", &ScrollView::SetScrollDeceleration)
        // [Method] void SetScrollSnapEpsilon(float snap)
        .addFunction("SetScrollSnapEpsilon", &ScrollView::SetScrollSnapEpsilon)
        // [Method] void SetAutoDisableChildren(bool disable)
        .addFunction("SetAutoDisableChildren", &ScrollView::SetAutoDisableChildren)
        // [Method] void SetAutoDisableThreshold(float amount)
        .addFunction("SetAutoDisableThreshold", &ScrollView::SetAutoDisableThreshold)

        // [Method] const IntVector2& GetViewPosition() const
        .addFunction("GetViewPosition", &ScrollView::GetViewPosition)

        .addStaticFunction("GetContentElement", &ScrollViewGetContentElement)

        // [Method] ScrollBar* GetHorizontalScrollBar() const
        .addFunction("GetHorizontalScrollBar", &ScrollView::GetHorizontalScrollBar)
        // [Method] ScrollBar* GetVerticalScrollBar() const
        .addFunction("GetVerticalScrollBar", &ScrollView::GetVerticalScrollBar)
        // [Method] BorderImage* GetScrollPanel() const
        .addFunction("GetScrollPanel", &ScrollView::GetScrollPanel)
        // [Method] bool GetScrollBarsAutoVisible() const
        .addFunction("GetScrollBarsAutoVisible", &ScrollView::GetScrollBarsAutoVisible)
        // [Method] float GetScrollStep() const
        .addFunction("GetScrollStep", &ScrollView::GetScrollStep)
        // [Method] float GetPageStep() const
        .addFunction("GetPageStep", &ScrollView::GetPageStep)
        // [Method] float GetScrollDeceleration() const
        .addFunction("GetScrollDeceleration", &ScrollView::GetScrollDeceleration)
        // [Method] float GetScrollSnapEpsilon() const
        .addFunction("GetScrollSnapEpsilon", &ScrollView::GetScrollSnapEpsilon)
        // [Method] bool GetAutoDisableChildren() const
        .addFunction("GetAutoDisableChildren", &ScrollView::GetAutoDisableChildren)
        // [Method] float GetAutoDisableThreshold() const
        .addFunction("GetAutoDisableThreshold", &ScrollView::GetAutoDisableThreshold)

        // [Property] const IntVector2& viewPosition
        .addProperty("viewPosition", &ScrollView::GetViewPosition, static_cast<void(ScrollView::*)(const IntVector2&)>(&ScrollView::SetViewPosition))

        .addProperty("contentElement", &ScrollViewGetContentElement, &ScrollViewSetContentElement)

        // [Property(ReadOnly)] ScrollBar* horizontalScrollBar
        .addProperty("horizontalScrollBar", &ScrollView::GetHorizontalScrollBar)
        // [Property(ReadOnly)] ScrollBar* verticalScrollBar
        .addProperty("verticalScrollBar", &ScrollView::GetVerticalScrollBar)
        // [Property(ReadOnly)] BorderImage* scrollPanel
        .addProperty("scrollPanel", &ScrollView::GetScrollPanel)
        // [Property] bool scrollBarsAutoVisible
        .addProperty("scrollBarsAutoVisible", &ScrollView::GetScrollBarsAutoVisible, &ScrollView::SetScrollBarsAutoVisible)
        // [Property] float scrollStep
        .addProperty("scrollStep", &ScrollView::GetScrollStep, &ScrollView::SetScrollStep)
        // [Property] float pageStep
        .addProperty("pageStep", &ScrollView::GetPageStep, &ScrollView::SetPageStep)
        // [Property] float scrollDeceleration
        .addProperty("scrollDeceleration", &ScrollView::GetScrollDeceleration, &ScrollView::SetScrollDeceleration)
        // [Property] float scrollSnapEpsilon
        .addProperty("scrollSnapEpsilon", &ScrollView::GetScrollSnapEpsilon, &ScrollView::SetScrollSnapEpsilon)
        );
}
}

