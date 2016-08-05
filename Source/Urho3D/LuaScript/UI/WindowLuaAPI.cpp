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

#include "../../UI/Window.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterWindow(kaguya::State& lua)
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
}

