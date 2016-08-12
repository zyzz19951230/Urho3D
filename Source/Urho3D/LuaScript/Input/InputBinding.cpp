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
#include "../../UI/UIElement.h"

#include <kaguya.hpp>

namespace Urho3D
{

static SharedPtr<UIElement> TouchStateGetTouchedElement(TouchState* self)
{
    return SharedPtr<UIElement>(self->GetTouchedElement());
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(InputSetMouseVisible, Input, SetMouseVisible, 1, 2); 
KAGUYA_MEMBER_FUNCTION_OVERLOADS(InputSetMouseGrabbed, Input, SetMouseGrabbed, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(InputSetMouseMode, Input, SetMouseMode, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(InputAddScreenJoystick, Input, AddScreenJoystick, 0, 2);

static bool InputSaveGestures(Input* self, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveGestures(*file);
}

static bool InputSaveGesture(Input* self, const String& fileName, unsigned gestureID)
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveGesture(*file, gestureID);
}

static unsigned InputLoadGestures(Input* self, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName));
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

    // [Enum] MouseMode
    lua["MM_ABSOLUTE"] = MM_ABSOLUTE;
    lua["MM_RELATIVE"] = MM_RELATIVE;
    lua["MM_WRAP"] = MM_WRAP;
    lua["MM_FREE"] = MM_FREE;
    lua["MM_INVALID"] = MM_INVALID;

    // [Class] TouchState
    lua["TouchState"].setClass(UserdataMetatable<TouchState>()
        
        // [Method] SharedPtr<UIElement> GetTouchedElement()
        .addStaticFunction("GetTouchedElement", &TouchStateGetTouchedElement)

        // [Field] int touchID
        .addProperty("touchID", &TouchState::touchID_)
        // [Field] IntVector2 position
        .addProperty("position", &TouchState::position_)
        // [Field] IntVector2 lastPosition
        .addProperty("lastPosition", &TouchState::lastPosition_)
        // [Field] IntVector2 delta
        .addProperty("delta", &TouchState::delta_)
        // [Field] float pressure
        .addProperty("pressure", &TouchState::pressure_)
        // [Property(Readonly)] UIElement* touchedElement
        .addProperty("touchedElement", &TouchState::GetTouchedElement)
    );

    // [Class] JoystickState
    lua["JoystickState"].setClass(UserdataMetatable<JoystickState>()
        
        // [Method] bool IsController() const
        .addFunction("IsController", &JoystickState::IsController)
        // [Method] unsigned GetNumButtons() const
        .addFunction("GetNumButtons", &JoystickState::GetNumButtons)
        // [Method] unsigned GetNumAxes() const
        .addFunction("GetNumAxes", &JoystickState::GetNumAxes)
        // [Method] unsigned GetNumHats() const
        .addFunction("GetNumHats", &JoystickState::GetNumHats)
        // [Method] bool GetButtonDown(unsigned index) const
        .addFunction("GetButtonDown", &JoystickState::GetButtonDown)
        // [Method] bool GetButtonPress(unsigned index) const
        .addFunction("GetButtonPress", &JoystickState::GetButtonPress)
        // [Method] float GetAxisPosition(unsigned index) const
        .addFunction("GetAxisPosition", &JoystickState::GetAxisPosition)
        // [Method] int GetHatPosition(unsigned index) const
        .addFunction("GetHatPosition", &JoystickState::GetHatPosition)

        // [Field] String name
        .addProperty("name", &JoystickState::name_)
        // [Field] int joystickID
        .addProperty("joystickID", &JoystickState::joystickID_)
        // [Property(Readonly)] bool controller
        .addProperty("controller", &JoystickState::IsController)
        // [Property(Readonly)] unsigned numButtons
        .addProperty("numButtons", &JoystickState::GetNumButtons)
        // [Property(Readonly)] unsigned numAxes
        .addProperty("numAxes", &JoystickState::GetNumAxes)
        // [Property(Readonly)] unsigned numHats
        .addProperty("numHats", &JoystickState::GetNumHats)
        );    

    // [Class] Input : Object
    lua["Input"].setClass(UserdataMetatable<Input, Object>()

        // [Method] void SetToggleFullscreen(bool enable)
        .addFunction("SetToggleFullscreen", &Input::SetToggleFullscreen)

        // [Method] void SetMouseVisible(bool enable, bool suppressEvent = false)
        .addFunction("SetMouseVisible", InputSetMouseVisible())
        // [Method] void SetMouseGrabbed(bool grab, bool suppressEvent = false)
        .addFunction("SetMouseGrabbed", InputSetMouseGrabbed())
        // [Method] void SetMouseMode(MouseMode mode, bool suppressEvent = false)
        .addFunction("SetMouseMode", InputSetMouseMode())

        // [Method] bool IsMouseLocked() const
        .addFunction("IsMouseLocked", &Input::IsMouseLocked)

        // [Method] int AddScreenJoystick(XMLFile* layoutFile = 0, XMLFile* styleFile = 0)
        .addFunction("AddScreenJoystick", InputAddScreenJoystick())

        // [Method] bool RemoveScreenJoystick(int id)
        .addFunction("RemoveScreenJoystick", &Input::RemoveScreenJoystick)
        // [Method] void SetScreenJoystickVisible(int id, bool enable)
        .addFunction("SetScreenJoystickVisible", &Input::SetScreenJoystickVisible)

        // [Method] void SetScreenKeyboardVisible(bool enable)
        .addFunction("SetScreenKeyboardVisible", &Input::SetScreenKeyboardVisible)
        // [Method] void SetTouchEmulation(bool enable)
        .addFunction("SetTouchEmulation", &Input::SetTouchEmulation)        
        // [Method] bool RecordGesture()
        .addFunction("RecordGesture", &Input::RecordGesture)

        // [Method] void SaveGestures(const String& fileName)
        .addStaticFunction("SaveGestures", &InputSaveGestures)
        // [Method] void SaveGesture(const String& fileName, unsigned gestureID)
        .addStaticFunction("SaveGesture", &InputSaveGesture)
        // [Method] void LoadGestures(const String& fileName)
        .addStaticFunction("LoadGestures", &InputLoadGestures)
        
        // [Method] bool RemoveGesture(unsigned gestureID)
        .addFunction("RemoveGesture", &Input::RemoveGesture)
        // [Method] void RemoveAllGestures()
        .addFunction("RemoveAllGestures", &Input::RemoveAllGestures)

        // [Method] int GetKeyFromName(const String& name) const
        .addFunction("GetKeyFromName", &Input::GetKeyFromName)
        // [Method] int GetKeyFromScancode(int scancode) const
        .addFunction("GetKeyFromScancode", &Input::GetKeyFromScancode)
        // [Method] String GetKeyName(int key) const
        .addFunction("GetKeyName", &Input::GetKeyName)
        // [Method] int GetScancodeFromKey(int key) const
        .addFunction("GetScancodeFromKey", &Input::GetScancodeFromKey)
        // [Method] int GetScancodeFromName(const String& name) const
        .addFunction("GetScancodeFromName", &Input::GetScancodeFromName)
        // [Method] String GetScancodeName(int scancode) const
        .addFunction("GetScancodeName", &Input::GetScancodeName)
        // [Method] bool GetKeyDown(int key) const
        .addFunction("GetKeyDown", &Input::GetKeyDown)
        // [Method] bool GetKeyPress(int key) const
        .addFunction("GetKeyPress", &Input::GetKeyPress)
        // [Method] bool GetScancodeDown(int scancode) const
        .addFunction("GetScancodeDown", &Input::GetScancodeDown)
        // [Method] bool GetScancodePress(int scancode) const
        .addFunction("GetScancodePress", &Input::GetScancodePress)
        // [Method] bool GetMouseButtonDown(int button) const
        .addFunction("GetMouseButtonDown", &Input::GetMouseButtonDown)
        // [Method] bool GetMouseButtonPress(int button) const
        .addFunction("GetMouseButtonPress", &Input::GetMouseButtonPress)
        // [Method] bool GetQualifierDown(int qualifier) const
        .addFunction("GetQualifierDown", &Input::GetQualifierDown)
        // [Method] bool GetQualifierPress(int qualifier) const
        .addFunction("GetQualifierPress", &Input::GetQualifierPress)
        // [Method] int GetQualifiers() const
        .addFunction("GetQualifiers", &Input::GetQualifiers)
        // [Method] IntVector2 GetMousePosition() const
        .addFunction("GetMousePosition", &Input::GetMousePosition)
        // [Method] const IntVector2& GetMouseMove() const
        .addFunction("GetMouseMove", &Input::GetMouseMove)
        // [Method] int GetMouseMoveX() const
        .addFunction("GetMouseMoveX", &Input::GetMouseMoveX)
        // [Method] int GetMouseMoveY() const
        .addFunction("GetMouseMoveY", &Input::GetMouseMoveY)
        // [Method] int GetMouseMoveWheel() const
        .addFunction("GetMouseMoveWheel", &Input::GetMouseMoveWheel)
        
        // [Method] unsigned GetNumTouches() const
        .addFunction("GetNumTouches", &Input::GetNumTouches)
        // [Method] TouchState* GetTouch(unsigned index) const
        .addFunction("GetTouch", &Input::GetTouch)

        // [Method] unsigned GetNumJoysticks() const
        .addFunction("GetNumJoysticks", &Input::GetNumJoysticks)
        // [Method] JoystickState* GetJoystick(int id)
        .addFunction("GetJoystick", &Input::GetJoystick)
        // [Method] JoystickState* GetJoystickByIndex(unsigned index)
        .addFunction("GetJoystickByIndex", &Input::GetJoystickByIndex)
        // [Method] JoystickState* GetJoystickByName(const String& name)
        .addFunction("GetJoystickByName", &Input::GetJoystickByName)

        // [Method] bool GetToggleFullscreen() const
        .addFunction("GetToggleFullscreen", &Input::GetToggleFullscreen)
        // [Method] bool GetScreenKeyboardSupport() const
        .addFunction("GetScreenKeyboardSupport", &Input::GetScreenKeyboardSupport)
        // [Method] bool IsScreenJoystickVisible(int id) const
        .addFunction("IsScreenJoystickVisible", &Input::IsScreenJoystickVisible)        
        // [Method] bool IsScreenKeyboardVisible() const
        .addFunction("IsScreenKeyboardVisible", &Input::IsScreenKeyboardVisible)
        // [Method] bool GetTouchEmulation() const
        .addFunction("GetTouchEmulation", &Input::GetTouchEmulation)
        // [Method] bool IsMouseVisible() const
        .addFunction("IsMouseVisible", &Input::IsMouseVisible)
        // [Method] bool IsMouseGrabbed() const
        .addFunction("IsMouseGrabbed", &Input::IsMouseGrabbed)
        // [Method] MouseMode GetMouseMode() const
        .addFunction("GetMouseMode", &Input::GetMouseMode)
        // [Method] bool HasFocus()
        .addFunction("HasFocus", &Input::HasFocus)
        // [Method] bool IsMinimized() const
        .addFunction("IsMinimized", &Input::IsMinimized)

        // [Property(Readonly)] int qualifiers
        .addProperty("qualifiers", &Input::GetQualifiers)
        // [Property(Readonly)] IntVector2 mousePosition
        .addProperty("mousePosition", &Input::GetMousePosition)
        // [Property(Readonly)] const IntVector2& mouseMove
        .addProperty("mouseMove", &Input::GetMouseMove)
        // [Property(Readonly)] int mouseMoveX
        .addProperty("mouseMoveX", &Input::GetMouseMoveX)
        // [Property(Readonly)] int mouseMoveY
        .addProperty("mouseMoveY", &Input::GetMouseMoveY)
        // [Property(Readonly)] int mouseMoveWheel
        .addProperty("mouseMoveWheel", &Input::GetMouseMoveWheel)

        // [Property(Readonly)] unsigned numTouches
        .addProperty("numTouches", &Input::GetNumTouches)
        // [Property(Readonly)] unsigned numJoysticks
        .addProperty("numJoysticks", &Input::GetNumJoysticks)
        // [Property] bool toggleFullscreen
        .addProperty("toggleFullscreen", &Input::GetToggleFullscreen, &Input::SetToggleFullscreen)
        // [Property(Readonly)] bool screenKeyboardSupport
        .addProperty("screenKeyboardSupport", &Input::GetScreenKeyboardSupport)
        // [Property] bool screenKeyboardVisible
        .addProperty("screenKeyboardVisible", &Input::IsScreenKeyboardVisible, &Input::SetScreenKeyboardVisible)
        // [Property] bool touchEmulation
        .addProperty("touchEmulation", &Input::GetTouchEmulation, &Input::SetTouchEmulation)
        
        // [Property] bool mouseVisible
        .addProperty("mouseVisible", &InputMouseVisibleGetter, &InputMouseVisibleSetter)

        // [Property(Readonly)] bool mouseGrabbed
        .addProperty("mouseGrabbed", &Input::IsMouseGrabbed)
        // [Property(Readonly)] bool mouseLocked
        .addProperty("mouseLocked", &Input::IsMouseLocked)
        // [Property(Readonly)] MouseMode mouseMode
        .addProperty("mouseMode", &Input::GetMouseMode)
        // [Property(Readonly)] bool focus
        .addFunction("focus", &Input::HasFocus)
        // [Property(Readonly)] bool minimized
        .addProperty("minimized", &Input::IsMinimized)
        );

    // [Variable] Input* input
    lua["input"] = GetSubsystem<Input>();
    // [Function] Input* GetInput()
    lua["GetInput"] = static_cast<Input*(*)()>(&GetSubsystem<Input>);
}
}

