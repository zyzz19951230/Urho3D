#include "../Core/Context.h"
#include "../Input/Controls.h"
#include "../Input/Input.h"
#include "../Input/InputEvents.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void ControlsSet0(Controls* self, unsigned int buttons)
{
    self->Set(buttons);
}

static void ControlsSet1(Controls* self, unsigned int buttons, bool down)
{
    self->Set(buttons, down);
}

static void RegisterControls(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Controls"].setClass(UserdataMetatable<Controls>()
        .setConstructors<Controls()>()

        .addFunction("Reset", &Controls::Reset)

        ADD_OVERLOADED_FUNCTIONS_2(Controls, Set)

        .addFunction("IsDown", &Controls::IsDown)
        .addFunction("IsPressed", &Controls::IsPressed)
        .addProperty("buttons", &Controls::buttons_)
        .addProperty("yaw", &Controls::yaw_)
        .addProperty("pitch", &Controls::pitch_)
        .addProperty("extraData", &Controls::extraData_)
        );
}

static void InputSetMouseVisible0(Input* self, bool enable)
{
    self->SetMouseVisible(enable);
}

static void InputSetMouseVisible1(Input* self, bool enable, bool suppressEvent)
{
    self->SetMouseVisible(enable, suppressEvent);
}

static void InputSetMouseGrabbed0(Input* self, bool grab)
{
    self->SetMouseGrabbed(grab);
}

static void InputSetMouseGrabbed1(Input* self, bool grab, bool suppressEvent)
{
    self->SetMouseGrabbed(grab, suppressEvent);
}

static void InputSetMouseMode0(Input* self, MouseMode mode)
{
    self->SetMouseMode(mode);
}

static void InputSetMouseMode1(Input* self, MouseMode mode, bool suppressEvent)
{
    self->SetMouseMode(mode, suppressEvent);
}

static bool InputIsMouseVisible(const Input* input)
{
    return input->IsMouseVisible();
}

static int InputAddScreenJoystick0(Input* self)
{
    return self->AddScreenJoystick();
}

static int InputAddScreenJoystick1(Input* self, XMLFile* layoutFile)
{
    return self->AddScreenJoystick(layoutFile);
}

static int InputAddScreenJoystick2(Input* self, XMLFile* layoutFile, XMLFile* styleFile)
{
    return self->AddScreenJoystick(layoutFile, styleFile);
}

static void RegisterInput(kaguya::State& lua)
{
    using namespace kaguya;

    // enum MouseMode;
    lua["MM_ABSOLUTE"] = MM_ABSOLUTE;
    lua["MM_RELATIVE"] = MM_RELATIVE;
    lua["MM_WRAP"] = MM_WRAP;
    lua["MM_FREE"] = MM_FREE;
    lua["MM_INVALID"] = MM_INVALID;

    lua["MOUSE_POSITION_OFFSCREEN"] = MOUSE_POSITION_OFFSCREEN;
    lua["TouchState"].setClass(UserdataMetatable<TouchState>()

        .addFunction("GetTouchedElement", &TouchState::GetTouchedElement)

        .addProperty("touchedElement", &TouchState::GetTouchedElement)
        /*
        .addProperty("touchID", &TouchState::touchID_)
        .addProperty("position", &TouchState::position_)
        .addProperty("lastPosition", &TouchState::lastPosition_)
        .addProperty("delta", &TouchState::delta_)
        .addProperty("pressure", &TouchState::pressure_)
        */
        );

    lua["JoystickState"].setClass(UserdataMetatable<JoystickState>()
        .setConstructors<JoystickState()>()

        .addFunction("Initialize", &JoystickState::Initialize)
        .addFunction("Reset", &JoystickState::Reset)
        .addFunction("IsController", &JoystickState::IsController)
        .addFunction("GetNumButtons", &JoystickState::GetNumButtons)
        .addFunction("GetNumAxes", &JoystickState::GetNumAxes)
        .addFunction("GetNumHats", &JoystickState::GetNumHats)
        .addFunction("GetButtonDown", &JoystickState::GetButtonDown)
        .addFunction("GetButtonPress", &JoystickState::GetButtonPress)
        .addFunction("GetAxisPosition", &JoystickState::GetAxisPosition)
        .addFunction("GetHatPosition", &JoystickState::GetHatPosition)

        .addProperty("isController", &JoystickState::IsController)
        .addProperty("numButtons", &JoystickState::GetNumButtons)
        .addProperty("numAxes", &JoystickState::GetNumAxes)
        .addProperty("numHats", &JoystickState::GetNumHats)
        .addProperty("joystick", &JoystickState::joystick_)

        /*
        .addProperty("joystickID", &JoystickState::joystickID_)
        .addProperty("controller", &JoystickState::controller_)
        .addProperty("screenJoystick", &JoystickState::screenJoystick_)
        .addProperty("name", &JoystickState::name_)
        .addProperty("buttons", &JoystickState::buttons_)
        .addProperty("buttonPress", &JoystickState::buttonPress_)
        .addProperty("axes", &JoystickState::axes_)
        .addProperty("hats", &JoystickState::hats_)
        */
        );

    lua["Input"].setClass(UserdataMetatable<Input, Object>()

        .addFunction("SetToggleFullscreen", &Input::SetToggleFullscreen)

        ADD_OVERLOADED_FUNCTIONS_2(Input, SetMouseVisible)

        .addFunction("ResetMouseVisible", &Input::ResetMouseVisible)

        ADD_OVERLOADED_FUNCTIONS_2(Input, SetMouseGrabbed)

        .addFunction("ResetMouseGrabbed", &Input::ResetMouseGrabbed)

        ADD_OVERLOADED_FUNCTIONS_2(Input, SetMouseMode)

        .addFunction("ResetMouseMode", &Input::ResetMouseMode)
        
        ADD_OVERLOADED_FUNCTIONS_3(Input, AddScreenJoystick)

        .addFunction("RemoveScreenJoystick", &Input::RemoveScreenJoystick)
        .addFunction("SetScreenJoystickVisible", &Input::SetScreenJoystickVisible)
        .addFunction("SetScreenKeyboardVisible", &Input::SetScreenKeyboardVisible)
        .addFunction("SetTouchEmulation", &Input::SetTouchEmulation)
        .addFunction("RecordGesture", &Input::RecordGesture)
        .addFunction("SaveGestures", &Input::SaveGestures)
        .addFunction("SaveGesture", &Input::SaveGesture)
        .addFunction("LoadGestures", &Input::LoadGestures)
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
        .addFunction("IsScreenJoystickVisible", &Input::IsScreenJoystickVisible)
        .addFunction("GetScreenKeyboardSupport", &Input::GetScreenKeyboardSupport)
        .addFunction("IsScreenKeyboardVisible", &Input::IsScreenKeyboardVisible)
        .addFunction("GetTouchEmulation", &Input::GetTouchEmulation)
        .addFunction("IsMouseVisible", &Input::IsMouseVisible)
        .addFunction("IsMouseGrabbed", &Input::IsMouseGrabbed)
        .addFunction("IsMouseLocked", &Input::IsMouseLocked)
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

        .addProperty("mouseVisible", &InputIsMouseVisible, &InputSetMouseVisible0)

        .addProperty("mouseGrabbed", &Input::IsMouseGrabbed)
        .addProperty("mouseLocked", &Input::IsMouseLocked)
        .addProperty("mouseMode", &Input::GetMouseMode)
        .addProperty("minimized", &Input::IsMinimized)
        );
}

static void RegisterInputEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["E_MOUSEBUTTONDOWN"] = E_MOUSEBUTTONDOWN;
    lua["E_MOUSEBUTTONUP"] = E_MOUSEBUTTONUP;
    lua["E_MOUSEMOVE"] = E_MOUSEMOVE;
    lua["E_MOUSEWHEEL"] = E_MOUSEWHEEL;
    lua["E_KEYDOWN"] = E_KEYDOWN;
    lua["E_KEYUP"] = E_KEYUP;
    lua["E_TEXTINPUT"] = E_TEXTINPUT;
    lua["E_JOYSTICKCONNECTED"] = E_JOYSTICKCONNECTED;
    lua["E_JOYSTICKDISCONNECTED"] = E_JOYSTICKDISCONNECTED;
    lua["E_JOYSTICKBUTTONDOWN"] = E_JOYSTICKBUTTONDOWN;
    lua["E_JOYSTICKBUTTONUP"] = E_JOYSTICKBUTTONUP;
    lua["E_JOYSTICKAXISMOVE"] = E_JOYSTICKAXISMOVE;
    lua["E_JOYSTICKHATMOVE"] = E_JOYSTICKHATMOVE;
    lua["E_TOUCHBEGIN"] = E_TOUCHBEGIN;
    lua["E_TOUCHEND"] = E_TOUCHEND;
    lua["E_TOUCHMOVE"] = E_TOUCHMOVE;
    lua["E_GESTURERECORDED"] = E_GESTURERECORDED;
    lua["E_GESTUREINPUT"] = E_GESTUREINPUT;
    lua["E_MULTIGESTURE"] = E_MULTIGESTURE;
    lua["E_DROPFILE"] = E_DROPFILE;
    lua["E_INPUTFOCUS"] = E_INPUTFOCUS;
    lua["E_MOUSEVISIBLECHANGED"] = E_MOUSEVISIBLECHANGED;
    lua["E_MOUSEMODECHANGED"] = E_MOUSEMODECHANGED;
    lua["E_EXITREQUESTED"] = E_EXITREQUESTED;
    lua["MOUSEB_LEFT"] = MOUSEB_LEFT;
    lua["MOUSEB_MIDDLE"] = MOUSEB_MIDDLE;
    lua["MOUSEB_RIGHT"] = MOUSEB_RIGHT;
    lua["MOUSEB_X1"] = MOUSEB_X1;
    lua["MOUSEB_X2"] = MOUSEB_X2;
    lua["QUAL_SHIFT"] = QUAL_SHIFT;
    lua["QUAL_CTRL"] = QUAL_CTRL;
    lua["QUAL_ALT"] = QUAL_ALT;
    lua["QUAL_ANY"] = QUAL_ANY;
    lua["KEY_A"] = KEY_A;
    lua["KEY_B"] = KEY_B;
    lua["KEY_C"] = KEY_C;
    lua["KEY_D"] = KEY_D;
    lua["KEY_E"] = KEY_E;
    lua["KEY_F"] = KEY_F;
    lua["KEY_G"] = KEY_G;
    lua["KEY_H"] = KEY_H;
    lua["KEY_I"] = KEY_I;
    lua["KEY_J"] = KEY_J;
    lua["KEY_K"] = KEY_K;
    lua["KEY_L"] = KEY_L;
    lua["KEY_M"] = KEY_M;
    lua["KEY_N"] = KEY_N;
    lua["KEY_O"] = KEY_O;
    lua["KEY_P"] = KEY_P;
    lua["KEY_Q"] = KEY_Q;
    lua["KEY_R"] = KEY_R;
    lua["KEY_S"] = KEY_S;
    lua["KEY_T"] = KEY_T;
    lua["KEY_U"] = KEY_U;
    lua["KEY_V"] = KEY_V;
    lua["KEY_W"] = KEY_W;
    lua["KEY_X"] = KEY_X;
    lua["KEY_Y"] = KEY_Y;
    lua["KEY_Z"] = KEY_Z;
    lua["KEY_0"] = KEY_0;
    lua["KEY_1"] = KEY_1;
    lua["KEY_2"] = KEY_2;
    lua["KEY_3"] = KEY_3;
    lua["KEY_4"] = KEY_4;
    lua["KEY_5"] = KEY_5;
    lua["KEY_6"] = KEY_6;
    lua["KEY_7"] = KEY_7;
    lua["KEY_8"] = KEY_8;
    lua["KEY_9"] = KEY_9;
    lua["KEY_BACKSPACE"] = KEY_BACKSPACE;
    lua["KEY_TAB"] = KEY_TAB;
    lua["KEY_RETURN"] = KEY_RETURN;
    lua["KEY_RETURN2"] = KEY_RETURN2;
    lua["KEY_KP_ENTER"] = KEY_KP_ENTER;
    lua["KEY_SHIFT"] = KEY_SHIFT;
    lua["KEY_CTRL"] = KEY_CTRL;
    lua["KEY_ALT"] = KEY_ALT;
    lua["KEY_GUI"] = KEY_GUI;
    lua["KEY_PAUSE"] = KEY_PAUSE;
    lua["KEY_CAPSLOCK"] = KEY_CAPSLOCK;
    lua["KEY_ESCAPE"] = KEY_ESCAPE;
    lua["KEY_SPACE"] = KEY_SPACE;
    lua["KEY_PAGEUP"] = KEY_PAGEUP;
    lua["KEY_PAGEDOWN"] = KEY_PAGEDOWN;
    lua["KEY_END"] = KEY_END;
    lua["KEY_HOME"] = KEY_HOME;
    lua["KEY_LEFT"] = KEY_LEFT;
    lua["KEY_UP"] = KEY_UP;
    lua["KEY_RIGHT"] = KEY_RIGHT;
    lua["KEY_DOWN"] = KEY_DOWN;
    lua["KEY_SELECT"] = KEY_SELECT;
    lua["KEY_PRINTSCREEN"] = KEY_PRINTSCREEN;
    lua["KEY_INSERT"] = KEY_INSERT;
    lua["KEY_DELETE"] = KEY_DELETE;
    lua["KEY_LGUI"] = KEY_LGUI;
    lua["KEY_RGUI"] = KEY_RGUI;
    lua["KEY_APPLICATION"] = KEY_APPLICATION;
    lua["KEY_KP_0"] = KEY_KP_0;
    lua["KEY_KP_1"] = KEY_KP_1;
    lua["KEY_KP_2"] = KEY_KP_2;
    lua["KEY_KP_3"] = KEY_KP_3;
    lua["KEY_KP_4"] = KEY_KP_4;
    lua["KEY_KP_5"] = KEY_KP_5;
    lua["KEY_KP_6"] = KEY_KP_6;
    lua["KEY_KP_7"] = KEY_KP_7;
    lua["KEY_KP_8"] = KEY_KP_8;
    lua["KEY_KP_9"] = KEY_KP_9;
    lua["KEY_KP_MULTIPLY"] = KEY_KP_MULTIPLY;
    lua["KEY_KP_PLUS"] = KEY_KP_PLUS;
    lua["KEY_KP_MINUS"] = KEY_KP_MINUS;
    lua["KEY_KP_PERIOD"] = KEY_KP_PERIOD;
    lua["KEY_KP_DIVIDE"] = KEY_KP_DIVIDE;
    lua["KEY_F1"] = KEY_F1;
    lua["KEY_F2"] = KEY_F2;
    lua["KEY_F3"] = KEY_F3;
    lua["KEY_F4"] = KEY_F4;
    lua["KEY_F5"] = KEY_F5;
    lua["KEY_F6"] = KEY_F6;
    lua["KEY_F7"] = KEY_F7;
    lua["KEY_F8"] = KEY_F8;
    lua["KEY_F9"] = KEY_F9;
    lua["KEY_F10"] = KEY_F10;
    lua["KEY_F11"] = KEY_F11;
    lua["KEY_F12"] = KEY_F12;
    lua["KEY_F13"] = KEY_F13;
    lua["KEY_F14"] = KEY_F14;
    lua["KEY_F15"] = KEY_F15;
    lua["KEY_F16"] = KEY_F16;
    lua["KEY_F17"] = KEY_F17;
    lua["KEY_F18"] = KEY_F18;
    lua["KEY_F19"] = KEY_F19;
    lua["KEY_F20"] = KEY_F20;
    lua["KEY_F21"] = KEY_F21;
    lua["KEY_F22"] = KEY_F22;
    lua["KEY_F23"] = KEY_F23;
    lua["KEY_F24"] = KEY_F24;
    lua["KEY_NUMLOCKCLEAR"] = KEY_NUMLOCKCLEAR;
    lua["KEY_SCROLLLOCK"] = KEY_SCROLLLOCK;
    lua["KEY_LSHIFT"] = KEY_LSHIFT;
    lua["KEY_RSHIFT"] = KEY_RSHIFT;
    lua["KEY_LCTRL"] = KEY_LCTRL;
    lua["KEY_RCTRL"] = KEY_RCTRL;
    lua["KEY_LALT"] = KEY_LALT;
    lua["KEY_RALT"] = KEY_RALT;
    lua["SCANCODE_UNKNOWN"] = SCANCODE_UNKNOWN;
    lua["SCANCODE_CTRL"] = SCANCODE_CTRL;
    lua["SCANCODE_SHIFT"] = SCANCODE_SHIFT;
    lua["SCANCODE_ALT"] = SCANCODE_ALT;
    lua["SCANCODE_GUI"] = SCANCODE_GUI;
    lua["SCANCODE_A"] = SCANCODE_A;
    lua["SCANCODE_B"] = SCANCODE_B;
    lua["SCANCODE_C"] = SCANCODE_C;
    lua["SCANCODE_D"] = SCANCODE_D;
    lua["SCANCODE_E"] = SCANCODE_E;
    lua["SCANCODE_F"] = SCANCODE_F;
    lua["SCANCODE_G"] = SCANCODE_G;
    lua["SCANCODE_H"] = SCANCODE_H;
    lua["SCANCODE_I"] = SCANCODE_I;
    lua["SCANCODE_J"] = SCANCODE_J;
    lua["SCANCODE_K"] = SCANCODE_K;
    lua["SCANCODE_L"] = SCANCODE_L;
    lua["SCANCODE_M"] = SCANCODE_M;
    lua["SCANCODE_N"] = SCANCODE_N;
    lua["SCANCODE_O"] = SCANCODE_O;
    lua["SCANCODE_P"] = SCANCODE_P;
    lua["SCANCODE_Q"] = SCANCODE_Q;
    lua["SCANCODE_R"] = SCANCODE_R;
    lua["SCANCODE_S"] = SCANCODE_S;
    lua["SCANCODE_T"] = SCANCODE_T;
    lua["SCANCODE_U"] = SCANCODE_U;
    lua["SCANCODE_V"] = SCANCODE_V;
    lua["SCANCODE_W"] = SCANCODE_W;
    lua["SCANCODE_X"] = SCANCODE_X;
    lua["SCANCODE_Y"] = SCANCODE_Y;
    lua["SCANCODE_Z"] = SCANCODE_Z;
    lua["SCANCODE_1"] = SCANCODE_1;
    lua["SCANCODE_2"] = SCANCODE_2;
    lua["SCANCODE_3"] = SCANCODE_3;
    lua["SCANCODE_4"] = SCANCODE_4;
    lua["SCANCODE_5"] = SCANCODE_5;
    lua["SCANCODE_6"] = SCANCODE_6;
    lua["SCANCODE_7"] = SCANCODE_7;
    lua["SCANCODE_8"] = SCANCODE_8;
    lua["SCANCODE_9"] = SCANCODE_9;
    lua["SCANCODE_0"] = SCANCODE_0;
    lua["SCANCODE_RETURN"] = SCANCODE_RETURN;
    lua["SCANCODE_ESCAPE"] = SCANCODE_ESCAPE;
    lua["SCANCODE_BACKSPACE"] = SCANCODE_BACKSPACE;
    lua["SCANCODE_TAB"] = SCANCODE_TAB;
    lua["SCANCODE_SPACE"] = SCANCODE_SPACE;
    lua["SCANCODE_MINUS"] = SCANCODE_MINUS;
    lua["SCANCODE_EQUALS"] = SCANCODE_EQUALS;
    lua["SCANCODE_LEFTBRACKET"] = SCANCODE_LEFTBRACKET;
    lua["SCANCODE_RIGHTBRACKET"] = SCANCODE_RIGHTBRACKET;
    lua["SCANCODE_BACKSLASH"] = SCANCODE_BACKSLASH;
    lua["SCANCODE_NONUSHASH"] = SCANCODE_NONUSHASH;
    lua["SCANCODE_SEMICOLON"] = SCANCODE_SEMICOLON;
    lua["SCANCODE_APOSTROPHE"] = SCANCODE_APOSTROPHE;
    lua["SCANCODE_GRAVE"] = SCANCODE_GRAVE;
    lua["SCANCODE_COMMA"] = SCANCODE_COMMA;
    lua["SCANCODE_PERIOD"] = SCANCODE_PERIOD;
    lua["SCANCODE_SLASH"] = SCANCODE_SLASH;
    lua["SCANCODE_CAPSLOCK"] = SCANCODE_CAPSLOCK;
    lua["SCANCODE_F1"] = SCANCODE_F1;
    lua["SCANCODE_F2"] = SCANCODE_F2;
    lua["SCANCODE_F3"] = SCANCODE_F3;
    lua["SCANCODE_F4"] = SCANCODE_F4;
    lua["SCANCODE_F5"] = SCANCODE_F5;
    lua["SCANCODE_F6"] = SCANCODE_F6;
    lua["SCANCODE_F7"] = SCANCODE_F7;
    lua["SCANCODE_F8"] = SCANCODE_F8;
    lua["SCANCODE_F9"] = SCANCODE_F9;
    lua["SCANCODE_F10"] = SCANCODE_F10;
    lua["SCANCODE_F11"] = SCANCODE_F11;
    lua["SCANCODE_F12"] = SCANCODE_F12;
    lua["SCANCODE_PRINTSCREEN"] = SCANCODE_PRINTSCREEN;
    lua["SCANCODE_SCROLLLOCK"] = SCANCODE_SCROLLLOCK;
    lua["SCANCODE_PAUSE"] = SCANCODE_PAUSE;
    lua["SCANCODE_INSERT"] = SCANCODE_INSERT;
    lua["SCANCODE_HOME"] = SCANCODE_HOME;
    lua["SCANCODE_PAGEUP"] = SCANCODE_PAGEUP;
    lua["SCANCODE_DELETE"] = SCANCODE_DELETE;
    lua["SCANCODE_END"] = SCANCODE_END;
    lua["SCANCODE_PAGEDOWN"] = SCANCODE_PAGEDOWN;
    lua["SCANCODE_RIGHT"] = SCANCODE_RIGHT;
    lua["SCANCODE_LEFT"] = SCANCODE_LEFT;
    lua["SCANCODE_DOWN"] = SCANCODE_DOWN;
    lua["SCANCODE_UP"] = SCANCODE_UP;
    lua["SCANCODE_NUMLOCKCLEAR"] = SCANCODE_NUMLOCKCLEAR;
    lua["SCANCODE_KP_DIVIDE"] = SCANCODE_KP_DIVIDE;
    lua["SCANCODE_KP_MULTIPLY"] = SCANCODE_KP_MULTIPLY;
    lua["SCANCODE_KP_MINUS"] = SCANCODE_KP_MINUS;
    lua["SCANCODE_KP_PLUS"] = SCANCODE_KP_PLUS;
    lua["SCANCODE_KP_ENTER"] = SCANCODE_KP_ENTER;
    lua["SCANCODE_KP_1"] = SCANCODE_KP_1;
    lua["SCANCODE_KP_2"] = SCANCODE_KP_2;
    lua["SCANCODE_KP_3"] = SCANCODE_KP_3;
    lua["SCANCODE_KP_4"] = SCANCODE_KP_4;
    lua["SCANCODE_KP_5"] = SCANCODE_KP_5;
    lua["SCANCODE_KP_6"] = SCANCODE_KP_6;
    lua["SCANCODE_KP_7"] = SCANCODE_KP_7;
    lua["SCANCODE_KP_8"] = SCANCODE_KP_8;
    lua["SCANCODE_KP_9"] = SCANCODE_KP_9;
    lua["SCANCODE_KP_0"] = SCANCODE_KP_0;
    lua["SCANCODE_KP_PERIOD"] = SCANCODE_KP_PERIOD;
    lua["SCANCODE_NONUSBACKSLASH"] = SCANCODE_NONUSBACKSLASH;
    lua["SCANCODE_APPLICATION"] = SCANCODE_APPLICATION;
    lua["SCANCODE_POWER"] = SCANCODE_POWER;
    lua["SCANCODE_KP_EQUALS"] = SCANCODE_KP_EQUALS;
    lua["SCANCODE_F13"] = SCANCODE_F13;
    lua["SCANCODE_F14"] = SCANCODE_F14;
    lua["SCANCODE_F15"] = SCANCODE_F15;
    lua["SCANCODE_F16"] = SCANCODE_F16;
    lua["SCANCODE_F17"] = SCANCODE_F17;
    lua["SCANCODE_F18"] = SCANCODE_F18;
    lua["SCANCODE_F19"] = SCANCODE_F19;
    lua["SCANCODE_F20"] = SCANCODE_F20;
    lua["SCANCODE_F21"] = SCANCODE_F21;
    lua["SCANCODE_F22"] = SCANCODE_F22;
    lua["SCANCODE_F23"] = SCANCODE_F23;
    lua["SCANCODE_F24"] = SCANCODE_F24;
    lua["SCANCODE_EXECUTE"] = SCANCODE_EXECUTE;
    lua["SCANCODE_HELP"] = SCANCODE_HELP;
    lua["SCANCODE_MENU"] = SCANCODE_MENU;
    lua["SCANCODE_SELECT"] = SCANCODE_SELECT;
    lua["SCANCODE_STOP"] = SCANCODE_STOP;
    lua["SCANCODE_AGAIN"] = SCANCODE_AGAIN;
    lua["SCANCODE_UNDO"] = SCANCODE_UNDO;
    lua["SCANCODE_CUT"] = SCANCODE_CUT;
    lua["SCANCODE_COPY"] = SCANCODE_COPY;
    lua["SCANCODE_PASTE"] = SCANCODE_PASTE;
    lua["SCANCODE_FIND"] = SCANCODE_FIND;
    lua["SCANCODE_MUTE"] = SCANCODE_MUTE;
    lua["SCANCODE_VOLUMEUP"] = SCANCODE_VOLUMEUP;
    lua["SCANCODE_VOLUMEDOWN"] = SCANCODE_VOLUMEDOWN;
    lua["SCANCODE_KP_COMMA"] = SCANCODE_KP_COMMA;
    lua["SCANCODE_KP_EQUALSAS400"] = SCANCODE_KP_EQUALSAS400;
    lua["SCANCODE_INTERNATIONAL1"] = SCANCODE_INTERNATIONAL1;
    lua["SCANCODE_INTERNATIONAL2"] = SCANCODE_INTERNATIONAL2;
    lua["SCANCODE_INTERNATIONAL3"] = SCANCODE_INTERNATIONAL3;
    lua["SCANCODE_INTERNATIONAL4"] = SCANCODE_INTERNATIONAL4;
    lua["SCANCODE_INTERNATIONAL5"] = SCANCODE_INTERNATIONAL5;
    lua["SCANCODE_INTERNATIONAL6"] = SCANCODE_INTERNATIONAL6;
    lua["SCANCODE_INTERNATIONAL7"] = SCANCODE_INTERNATIONAL7;
    lua["SCANCODE_INTERNATIONAL8"] = SCANCODE_INTERNATIONAL8;
    lua["SCANCODE_INTERNATIONAL9"] = SCANCODE_INTERNATIONAL9;
    lua["SCANCODE_LANG1"] = SCANCODE_LANG1;
    lua["SCANCODE_LANG2"] = SCANCODE_LANG2;
    lua["SCANCODE_LANG3"] = SCANCODE_LANG3;
    lua["SCANCODE_LANG4"] = SCANCODE_LANG4;
    lua["SCANCODE_LANG5"] = SCANCODE_LANG5;
    lua["SCANCODE_LANG6"] = SCANCODE_LANG6;
    lua["SCANCODE_LANG7"] = SCANCODE_LANG7;
    lua["SCANCODE_LANG8"] = SCANCODE_LANG8;
    lua["SCANCODE_LANG9"] = SCANCODE_LANG9;
    lua["SCANCODE_ALTERASE"] = SCANCODE_ALTERASE;
    lua["SCANCODE_SYSREQ"] = SCANCODE_SYSREQ;
    lua["SCANCODE_CANCEL"] = SCANCODE_CANCEL;
    lua["SCANCODE_CLEAR"] = SCANCODE_CLEAR;
    lua["SCANCODE_PRIOR"] = SCANCODE_PRIOR;
    lua["SCANCODE_RETURN2"] = SCANCODE_RETURN2;
    lua["SCANCODE_SEPARATOR"] = SCANCODE_SEPARATOR;
    lua["SCANCODE_OUT"] = SCANCODE_OUT;
    lua["SCANCODE_OPER"] = SCANCODE_OPER;
    lua["SCANCODE_CLEARAGAIN"] = SCANCODE_CLEARAGAIN;
    lua["SCANCODE_CRSEL"] = SCANCODE_CRSEL;
    lua["SCANCODE_EXSEL"] = SCANCODE_EXSEL;
    lua["SCANCODE_KP_00"] = SCANCODE_KP_00;
    lua["SCANCODE_KP_000"] = SCANCODE_KP_000;
    lua["SCANCODE_THOUSANDSSEPARATOR"] = SCANCODE_THOUSANDSSEPARATOR;
    lua["SCANCODE_DECIMALSEPARATOR"] = SCANCODE_DECIMALSEPARATOR;
    lua["SCANCODE_CURRENCYUNIT"] = SCANCODE_CURRENCYUNIT;
    lua["SCANCODE_CURRENCYSUBUNIT"] = SCANCODE_CURRENCYSUBUNIT;
    lua["SCANCODE_KP_LEFTPAREN"] = SCANCODE_KP_LEFTPAREN;
    lua["SCANCODE_KP_RIGHTPAREN"] = SCANCODE_KP_RIGHTPAREN;
    lua["SCANCODE_KP_LEFTBRACE"] = SCANCODE_KP_LEFTBRACE;
    lua["SCANCODE_KP_RIGHTBRACE"] = SCANCODE_KP_RIGHTBRACE;
    lua["SCANCODE_KP_TAB"] = SCANCODE_KP_TAB;
    lua["SCANCODE_KP_BACKSPACE"] = SCANCODE_KP_BACKSPACE;
    lua["SCANCODE_KP_A"] = SCANCODE_KP_A;
    lua["SCANCODE_KP_B"] = SCANCODE_KP_B;
    lua["SCANCODE_KP_C"] = SCANCODE_KP_C;
    lua["SCANCODE_KP_D"] = SCANCODE_KP_D;
    lua["SCANCODE_KP_E"] = SCANCODE_KP_E;
    lua["SCANCODE_KP_F"] = SCANCODE_KP_F;
    lua["SCANCODE_KP_XOR"] = SCANCODE_KP_XOR;
    lua["SCANCODE_KP_POWER"] = SCANCODE_KP_POWER;
    lua["SCANCODE_KP_PERCENT"] = SCANCODE_KP_PERCENT;
    lua["SCANCODE_KP_LESS"] = SCANCODE_KP_LESS;
    lua["SCANCODE_KP_GREATER"] = SCANCODE_KP_GREATER;
    lua["SCANCODE_KP_AMPERSAND"] = SCANCODE_KP_AMPERSAND;
    lua["SCANCODE_KP_DBLAMPERSAND"] = SCANCODE_KP_DBLAMPERSAND;
    lua["SCANCODE_KP_VERTICALBAR"] = SCANCODE_KP_VERTICALBAR;
    lua["SCANCODE_KP_DBLVERTICALBAR"] = SCANCODE_KP_DBLVERTICALBAR;
    lua["SCANCODE_KP_COLON"] = SCANCODE_KP_COLON;
    lua["SCANCODE_KP_HASH"] = SCANCODE_KP_HASH;
    lua["SCANCODE_KP_SPACE"] = SCANCODE_KP_SPACE;
    lua["SCANCODE_KP_AT"] = SCANCODE_KP_AT;
    lua["SCANCODE_KP_EXCLAM"] = SCANCODE_KP_EXCLAM;
    lua["SCANCODE_KP_MEMSTORE"] = SCANCODE_KP_MEMSTORE;
    lua["SCANCODE_KP_MEMRECALL"] = SCANCODE_KP_MEMRECALL;
    lua["SCANCODE_KP_MEMCLEAR"] = SCANCODE_KP_MEMCLEAR;
    lua["SCANCODE_KP_MEMADD"] = SCANCODE_KP_MEMADD;
    lua["SCANCODE_KP_MEMSUBTRACT"] = SCANCODE_KP_MEMSUBTRACT;
    lua["SCANCODE_KP_MEMMULTIPLY"] = SCANCODE_KP_MEMMULTIPLY;
    lua["SCANCODE_KP_MEMDIVIDE"] = SCANCODE_KP_MEMDIVIDE;
    lua["SCANCODE_KP_PLUSMINUS"] = SCANCODE_KP_PLUSMINUS;
    lua["SCANCODE_KP_CLEAR"] = SCANCODE_KP_CLEAR;
    lua["SCANCODE_KP_CLEARENTRY"] = SCANCODE_KP_CLEARENTRY;
    lua["SCANCODE_KP_BINARY"] = SCANCODE_KP_BINARY;
    lua["SCANCODE_KP_OCTAL"] = SCANCODE_KP_OCTAL;
    lua["SCANCODE_KP_DECIMAL"] = SCANCODE_KP_DECIMAL;
    lua["SCANCODE_KP_HEXADECIMAL"] = SCANCODE_KP_HEXADECIMAL;
    lua["SCANCODE_LCTRL"] = SCANCODE_LCTRL;
    lua["SCANCODE_LSHIFT"] = SCANCODE_LSHIFT;
    lua["SCANCODE_LALT"] = SCANCODE_LALT;
    lua["SCANCODE_LGUI"] = SCANCODE_LGUI;
    lua["SCANCODE_RCTRL"] = SCANCODE_RCTRL;
    lua["SCANCODE_RSHIFT"] = SCANCODE_RSHIFT;
    lua["SCANCODE_RALT"] = SCANCODE_RALT;
    lua["SCANCODE_RGUI"] = SCANCODE_RGUI;
    lua["SCANCODE_MODE"] = SCANCODE_MODE;
    lua["SCANCODE_AUDIONEXT"] = SCANCODE_AUDIONEXT;
    lua["SCANCODE_AUDIOPREV"] = SCANCODE_AUDIOPREV;
    lua["SCANCODE_AUDIOSTOP"] = SCANCODE_AUDIOSTOP;
    lua["SCANCODE_AUDIOPLAY"] = SCANCODE_AUDIOPLAY;
    lua["SCANCODE_AUDIOMUTE"] = SCANCODE_AUDIOMUTE;
    lua["SCANCODE_MEDIASELECT"] = SCANCODE_MEDIASELECT;
    lua["SCANCODE_WWW"] = SCANCODE_WWW;
    lua["SCANCODE_MAIL"] = SCANCODE_MAIL;
    lua["SCANCODE_CALCULATOR"] = SCANCODE_CALCULATOR;
    lua["SCANCODE_COMPUTER"] = SCANCODE_COMPUTER;
    lua["SCANCODE_AC_SEARCH"] = SCANCODE_AC_SEARCH;
    lua["SCANCODE_AC_HOME"] = SCANCODE_AC_HOME;
    lua["SCANCODE_AC_BACK"] = SCANCODE_AC_BACK;
    lua["SCANCODE_AC_FORWARD"] = SCANCODE_AC_FORWARD;
    lua["SCANCODE_AC_STOP"] = SCANCODE_AC_STOP;
    lua["SCANCODE_AC_REFRESH"] = SCANCODE_AC_REFRESH;
    lua["SCANCODE_AC_BOOKMARKS"] = SCANCODE_AC_BOOKMARKS;
    lua["SCANCODE_BRIGHTNESSDOWN"] = SCANCODE_BRIGHTNESSDOWN;
    lua["SCANCODE_BRIGHTNESSUP"] = SCANCODE_BRIGHTNESSUP;
    lua["SCANCODE_DISPLAYSWITCH"] = SCANCODE_DISPLAYSWITCH;
    lua["SCANCODE_KBDILLUMTOGGLE"] = SCANCODE_KBDILLUMTOGGLE;
    lua["SCANCODE_KBDILLUMDOWN"] = SCANCODE_KBDILLUMDOWN;
    lua["SCANCODE_KBDILLUMUP"] = SCANCODE_KBDILLUMUP;
    lua["SCANCODE_EJECT"] = SCANCODE_EJECT;
    lua["SCANCODE_SLEEP"] = SCANCODE_SLEEP;
    lua["SCANCODE_APP1"] = SCANCODE_APP1;
    lua["SCANCODE_APP2"] = SCANCODE_APP2;
    lua["HAT_CENTER"] = HAT_CENTER;
    lua["HAT_UP"] = HAT_UP;
    lua["HAT_RIGHT"] = HAT_RIGHT;
    lua["HAT_DOWN"] = HAT_DOWN;
    lua["HAT_LEFT"] = HAT_LEFT;
    lua["CONTROLLER_BUTTON_A"] = CONTROLLER_BUTTON_A;
    lua["CONTROLLER_BUTTON_B"] = CONTROLLER_BUTTON_B;
    lua["CONTROLLER_BUTTON_X"] = CONTROLLER_BUTTON_X;
    lua["CONTROLLER_BUTTON_Y"] = CONTROLLER_BUTTON_Y;
    lua["CONTROLLER_BUTTON_BACK"] = CONTROLLER_BUTTON_BACK;
    lua["CONTROLLER_BUTTON_GUIDE"] = CONTROLLER_BUTTON_GUIDE;
    lua["CONTROLLER_BUTTON_START"] = CONTROLLER_BUTTON_START;
    lua["CONTROLLER_BUTTON_LEFTSTICK"] = CONTROLLER_BUTTON_LEFTSTICK;
    lua["CONTROLLER_BUTTON_RIGHTSTICK"] = CONTROLLER_BUTTON_RIGHTSTICK;
    lua["CONTROLLER_BUTTON_LEFTSHOULDER"] = CONTROLLER_BUTTON_LEFTSHOULDER;
    lua["CONTROLLER_BUTTON_RIGHTSHOULDER"] = CONTROLLER_BUTTON_RIGHTSHOULDER;
    lua["CONTROLLER_BUTTON_DPAD_UP"] = CONTROLLER_BUTTON_DPAD_UP;
    lua["CONTROLLER_BUTTON_DPAD_DOWN"] = CONTROLLER_BUTTON_DPAD_DOWN;
    lua["CONTROLLER_BUTTON_DPAD_LEFT"] = CONTROLLER_BUTTON_DPAD_LEFT;
    lua["CONTROLLER_BUTTON_DPAD_RIGHT"] = CONTROLLER_BUTTON_DPAD_RIGHT;
    lua["CONTROLLER_AXIS_LEFTX"] = CONTROLLER_AXIS_LEFTX;
    lua["CONTROLLER_AXIS_LEFTY"] = CONTROLLER_AXIS_LEFTY;
    lua["CONTROLLER_AXIS_RIGHTX"] = CONTROLLER_AXIS_RIGHTX;
    lua["CONTROLLER_AXIS_RIGHTY"] = CONTROLLER_AXIS_RIGHTY;
    lua["CONTROLLER_AXIS_TRIGGERLEFT"] = CONTROLLER_AXIS_TRIGGERLEFT;
    lua["CONTROLLER_AXIS_TRIGGERRIGHT"] = CONTROLLER_AXIS_TRIGGERRIGHT;
}

void RegisterInputLuaAPI(kaguya::State& lua)
{
    RegisterControls(lua);
    RegisterInput(lua);
    RegisterInputEvents(lua);

    lua["input"] = KGetSubsystem<Input>();
    lua["GetInput"] = KGetSubsystem<Input>;
}
}
