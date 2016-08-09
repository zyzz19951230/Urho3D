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

#include "../../Input/Controls.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern Context* globalContext;

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ControlsSet, Controls, Set, 1, 2);

void RegisterControls(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Controls
    lua["Controls"].setClass(UserdataMetatable<Controls>()
        .setConstructors<Controls()>()

        // [Method] void Reset()
        .addFunction("Reset", &Controls::Reset)

        // [Method] void Set(unsigned buttons, bool down = true)
        .addFunction("Set", ControlsSet())

        // [Method] bool IsDown(unsigned button) const
        .addFunction("IsDown", &Controls::IsDown)
        // [Method] bool IsPressed(unsigned button, const Controls& previousControls) const
        .addFunction("IsPressed", &Controls::IsPressed)

        .addProperty("buttons", &Controls::buttons_)
        .addProperty("yaw", &Controls::yaw_)
        .addProperty("pitch", &Controls::pitch_)
        .addProperty("extraData", &Controls::extraData_)
        );
}
}

