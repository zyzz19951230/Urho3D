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

    // [Enum] WindowDragMode
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

    // [Class] Window : BorderImage
    lua["Window"].setClass(UserdataMetatable<Window, BorderImage>()
        // [Constructor] Window()
        .addStaticFunction("new", &CreateObject<Window>)

        // [Method] void SetMovable(bool enable)
        .addFunction("SetMovable", &Window::SetMovable)
        // [Method] void SetResizable(bool enable)
        .addFunction("SetResizable", &Window::SetResizable)
        // [Method] void SetFixedWidthResizing(bool enable)
        .addFunction("SetFixedWidthResizing", &Window::SetFixedWidthResizing)
        // [Method] void SetFixedHeightResizing(bool enable)
        .addFunction("SetFixedHeightResizing", &Window::SetFixedHeightResizing)
        // [Method] void SetResizeBorder(const IntRect& rect)
        .addFunction("SetResizeBorder", &Window::SetResizeBorder)
        // [Method] void SetModal(bool modal)
        .addFunction("SetModal", &Window::SetModal)
        // [Method] void SetModalShadeColor(const Color& color)
        .addFunction("SetModalShadeColor", &Window::SetModalShadeColor)
        // [Method] void SetModalFrameColor(const Color& color)
        .addFunction("SetModalFrameColor", &Window::SetModalFrameColor)
        // [Method] void SetModalFrameSize(const IntVector2& size)
        .addFunction("SetModalFrameSize", &Window::SetModalFrameSize)
        // [Method] void SetModalAutoDismiss(bool enable)
        .addFunction("SetModalAutoDismiss", &Window::SetModalAutoDismiss)

        // [Method] bool IsMovable() const
        .addFunction("IsMovable", &Window::IsMovable)
        // [Method] bool IsResizable() const
        .addFunction("IsResizable", &Window::IsResizable)
        // [Method] bool GetFixedWidthResizing() const
        .addFunction("GetFixedWidthResizing", &Window::GetFixedWidthResizing)
        // [Method] bool GetFixedHeightResizing() const
        .addFunction("GetFixedHeightResizing", &Window::GetFixedHeightResizing)
        // [Method] const IntRect& GetResizeBorder() const
        .addFunction("GetResizeBorder", &Window::GetResizeBorder)
        // [Method] bool IsModal() const
        .addFunction("IsModal", &Window::IsModal)
        // [Method] const Color& GetModalShadeColor() const
        .addFunction("GetModalShadeColor", &Window::GetModalShadeColor)
        // [Method] const Color& GetModalFrameColor() const
        .addFunction("GetModalFrameColor", &Window::GetModalFrameColor)
        // [Method] const IntVector2& GetModalFrameSize() const
        .addFunction("GetModalFrameSize", &Window::GetModalFrameSize)
        // [Method] bool GetModalAutoDismiss() const
        .addFunction("GetModalAutoDismiss", &Window::GetModalAutoDismiss)

        // [Property] bool movable
        .addProperty("movable", &Window::IsMovable, &Window::SetMovable)
        // [Property] bool resizable
        .addProperty("resizable", &Window::IsResizable, &Window::SetResizable)
        // [Property] bool fixedWidthResizing
        .addProperty("fixedWidthResizing", &Window::GetFixedWidthResizing, &Window::SetFixedWidthResizing)
        // [Property] bool fixedHeightResizing
        .addProperty("fixedHeightResizing", &Window::GetFixedHeightResizing, &Window::SetFixedHeightResizing)
        // [Property] const IntRect& resizeBorder
        .addProperty("resizeBorder", &Window::GetResizeBorder, &Window::SetResizeBorder)
        // [Property] bool modal
        .addProperty("modal", &Window::IsModal, &Window::SetModal)
        // [Property] const Color& modalShadeColor
        .addProperty("modalShadeColor", &Window::GetModalShadeColor, &Window::SetModalShadeColor)
        // [Property] const Color& modalFrameColor
        .addProperty("modalFrameColor", &Window::GetModalFrameColor, &Window::SetModalFrameColor)
        // [Property] const IntVector2& modalFrameSize
        .addProperty("modalFrameSize", &Window::GetModalFrameSize, &Window::SetModalFrameSize)
        // [Property] bool modalAutoDismiss
        .addProperty("modalAutoDismiss", &Window::GetModalAutoDismiss, &Window::SetModalAutoDismiss)
        );
}
}

