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

#include <kaguya.hpp>

namespace Urho3D
{

extern void RegisterBorderImage(kaguya::State& lua);
extern void RegisterButton(kaguya::State& lua);
extern void RegisterCheckBox(kaguya::State& lua);
extern void RegisterCursor(kaguya::State& lua);
extern void RegisterDropDownList(kaguya::State& lua);
extern void RegisterFileSelector(kaguya::State& lua);
extern void RegisterFont(kaguya::State& lua);
extern void RegisterLineEdit(kaguya::State& lua);
extern void RegisterListView(kaguya::State& lua);
extern void RegisterMenu(kaguya::State& lua);
extern void RegisterMessageBox(kaguya::State& lua);
extern void RegisterScrollBar(kaguya::State& lua);
extern void RegisterScrollView(kaguya::State& lua);
extern void RegisterSlider(kaguya::State& lua);
extern void RegisterSprite(kaguya::State& lua);
extern void RegisterText(kaguya::State& lua);
extern void RegisterText3D(kaguya::State& lua);
extern void RegisterToolTip(kaguya::State& lua);
extern void RegisterUI(kaguya::State& lua);
extern void RegisterView3D(kaguya::State& lua);
extern void RegisterWindow(kaguya::State& lua);
extern void RegisterUIElement(kaguya::State& lua);

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
}
}
