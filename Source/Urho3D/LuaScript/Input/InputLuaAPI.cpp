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

#include "../../Input/Input.h"
#include "../../IO/File.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(InputSetMouseVisible, Input, SetMouseVisible, 1, 2); 
KAGUYA_MEMBER_FUNCTION_OVERLOADS(InputSetMouseGrabbed, Input, SetMouseGrabbed, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(InputSetMouseMode, Input, SetMouseMode, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(InputAddScreenJoystick, Input, AddScreenJoystick, 0, 2);

static bool InputSaveGestures(Input* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveGestures(*file);
}

static bool InputSaveGesture(Input* self, const char* filepath, unsigned gestureID)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveGesture(*file, gestureID);
}

static unsigned InputLoadGestures(Input* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->LoadGestures(*file);
}

static void InputMouseVisibleSetter(Input* self, bool enable)
{
    return self->SetMouseVisible(enable);
}

static bool InputMouseVisibleGetter(const Input* self)
{
    return self->IsMouseVisible();
}

void RegisterInput(kaguya::State& lua)
{
    using namespace kaguya;

    // enum MouseMode;
    lua["MM_ABSOLUTE"] = MM_ABSOLUTE;
    lua["MM_RELATIVE"] = MM_RELATIVE;
    lua["MM_WRAP"] = MM_WRAP;
    lua["MM_FREE"] = MM_FREE;
    lua["MM_INVALID"] = MM_INVALID;

    lua["TouchState"].setClass(UserdataMetatable<TouchState>()
        .addFunction("GetTouchedElement", &TouchState::GetTouchedElement)

        .addProperty("touchID", &TouchState::touchID_)
        .addProperty("position", &TouchState::position_)
        .addProperty("lastPosition", &TouchState::lastPosition_)
        .addProperty("delta", &TouchState::delta_)
        .addProperty("pressure", &TouchState::pressure_)
        .addProperty("touchedElement", &TouchState::GetTouchedElement)
    );

    lua["JoystickState"].setClass(UserdataMetatable<JoystickState>()
        .addFunction("IsController", &JoystickState::IsController)
        .addFunction("GetNumButtons", &JoystickState::GetNumButtons)
        .addFunction("GetNumAxes", &JoystickState::GetNumAxes)
        .addFunction("GetNumHats", &JoystickState::GetNumHats)
        .addFunction("GetButtonDown", &JoystickState::GetButtonDown)
        .addFunction("GetButtonPress", &JoystickState::GetButtonPress)
        .addFunction("GetAxisPosition", &JoystickState::GetAxisPosition)
        .addFunction("GetHatPosition", &JoystickState::GetHatPosition)

        .addProperty("name", &JoystickState::name_)
        .addProperty("joystickID", &JoystickState::joystickID_)
        .addProperty("controller", &JoystickState::IsController)
        .addProperty("numButtons", &JoystickState::GetNumButtons)
        .addProperty("numAxes", &JoystickState::GetNumAxes)
        .addProperty("numHats", &JoystickState::GetNumHats)
        );    

    lua["Input"].setClass(UserdataMetatable<Input, Object>()

        .addFunction("SetToggleFullscreen", &Input::SetToggleFullscreen)

        .addFunction("SetMouseVisible", InputSetMouseVisible())
        .addFunction("SetMouseGrabbed", InputSetMouseGrabbed())
        .addFunction("SetMouseMode", InputSetMouseMode())

        .addFunction("IsMouseLocked", &Input::IsMouseLocked)

        .addFunction("AddScreenJoystick", InputAddScreenJoystick())

        .addFunction("RemoveScreenJoystick", &Input::RemoveScreenJoystick)
        .addFunction("SetScreenJoystickVisible", &Input::SetScreenJoystickVisible)

        .addFunction("SetScreenKeyboardVisible", &Input::SetScreenKeyboardVisible)
        .addFunction("SetTouchEmulation", &Input::SetTouchEmulation)        
        .addFunction("RecordGesture", &Input::RecordGesture)

        .addStaticFunction("SaveGestures", &InputSaveGestures)
        .addStaticFunction("SaveGesture", &InputSaveGesture)
        .addStaticFunction("LoadGestures", &InputLoadGestures)
        
        .addFunction("RemoveGesture", &Input::RemoveGesture)
        .addFunction("RemoveAllGestures", &Input::RemoveAllGestures)

        .addFunction("GetKeyFromName", &Input::GetKeyFromName)
        .addFunction("GetKeyFromScancode", &Input::GetKeyFromScancode)
        .addFunction("GetKeyName", &Input::GetKeyName)
        .addFunction("GetScancodeFromKey", &Input::GetScancodeFromKey)
        .addFunction("GetScancodeFromName", &Input::GetScancodeFromName)
        .addFunction("GetScancodeName", &Input::GetScancodeName)
        .addFunction("GetKeyDown", &Input::GetKeyDown)
        .addFunction("GetKeyPress", &Input::GetKeyPress)
        .addFunction("GetScancodeDown", &Input::GetScancodeDown)
        .addFunction("GetScancodePress", &Input::GetScancodePress)
        .addFunction("GetMouseButtonDown", &Input::GetMouseButtonDown)
        .addFunction("GetMouseButtonPress", &Input::GetMouseButtonPress)
        .addFunction("GetQualifierDown", &Input::GetQualifierDown)
        .addFunction("GetQualifierPress", &Input::GetQualifierPress)
        .addFunction("GetQualifiers", &Input::GetQualifiers)
        .addFunction("GetMousePosition", &Input::GetMousePosition)
        .addFunction("GetMouseMove", &Input::GetMouseMove)
        .addFunction("GetMouseMoveX", &Input::GetMouseMoveX)
        .addFunction("GetMouseMoveY", &Input::GetMouseMoveY)
        .addFunction("GetMouseMoveWheel", &Input::GetMouseMoveWheel)
        
        .addFunction("GetNumTouches", &Input::GetNumTouches)
        .addFunction("GetTouch", &Input::GetTouch)

        .addFunction("GetNumJoysticks", &Input::GetNumJoysticks)
        .addFunction("GetJoystick", &Input::GetJoystick)
        .addFunction("GetJoystickByIndex", &Input::GetJoystickByIndex)
        .addFunction("GetJoystickByName", &Input::GetJoystickByName)

        .addFunction("GetToggleFullscreen", &Input::GetToggleFullscreen)
        .addFunction("GetScreenKeyboardSupport", &Input::GetScreenKeyboardSupport)
        .addFunction("IsScreenJoystickVisible", &Input::IsScreenJoystickVisible)        
        .addFunction("IsScreenKeyboardVisible", &Input::IsScreenKeyboardVisible)
        .addFunction("GetTouchEmulation", &Input::GetTouchEmulation)
        .addFunction("IsMouseVisible", &Input::IsMouseVisible)
        .addFunction("IsMouseGrabbed", &Input::IsMouseGrabbed)
        .addFunction("GetMouseMode", &Input::GetMouseMode)
        .addFunction("HasFocus", &Input::HasFocus)
        .addFunction("IsMinimized", &Input::IsMinimized)

        .addProperty("qualifiers", &Input::GetQualifiers)
        .addProperty("mousePosition", &Input::GetMousePosition)
        .addProperty("mouseMove", &Input::GetMouseMove)
        .addProperty("mouseMoveX", &Input::GetMouseMoveX)
        .addProperty("mouseMoveY", &Input::GetMouseMoveY)
        .addProperty("mouseMoveWheel", &Input::GetMouseMoveWheel)

        .addProperty("numTouches", &Input::GetNumTouches)
        .addProperty("numJoysticks", &Input::GetNumJoysticks)
        .addProperty("toggleFullscreen", &Input::GetToggleFullscreen, &Input::SetToggleFullscreen)
        .addProperty("screenKeyboardSupport", &Input::GetScreenKeyboardSupport)
        .addProperty("screenKeyboardVisible", &Input::IsScreenKeyboardVisible, &Input::SetScreenKeyboardVisible)
        .addProperty("touchEmulation", &Input::GetTouchEmulation, &Input::SetTouchEmulation)
        
        .addProperty("mouseVisible", &InputMouseVisibleGetter, &InputMouseVisibleSetter)

        .addProperty("mouseGrabbed", &Input::IsMouseGrabbed)
        .addProperty("mouseLocked", &Input::IsMouseLocked)
        .addProperty("mouseMode", &Input::GetMouseMode)
        .addFunction("focus", &Input::HasFocus)
        .addProperty("minimized", &Input::IsMinimized)
        );
}
}

