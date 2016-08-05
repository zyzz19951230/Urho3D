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
}

