#include "../Core/Context.h"
#include "../Input/Controls.h"
#include "../Input/Input.h"
#include "../Input/InputEvents.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterControls(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KControls"].setClass(UserdataMetatable<Controls>()
        .setConstructors<Controls()>()

        .addFunction("Reset", &Controls::Reset)
        .addFunction("Set", &Controls::Set)
        .addFunction("IsDown", &Controls::IsDown)
        .addFunction("IsPressed", &Controls::IsPressed)
        .addProperty("buttons", &Controls::buttons_)
        .addProperty("yaw", &Controls::yaw_)
        .addProperty("pitch", &Controls::pitch_)
        .addProperty("extraData", &Controls::extraData_)
    );
}

static void RegisterInput(kaguya::State& lua)
{
    using namespace kaguya;

    // enum MouseMode;
    lua["KMM_ABSOLUTE"] = MM_ABSOLUTE;
    lua["KMM_RELATIVE"] = MM_RELATIVE;
    lua["KMM_WRAP"] = MM_WRAP;
    lua["KMM_FREE"] = MM_FREE;
    lua["KMM_INVALID"] = MM_INVALID;

    lua["KMOUSE_POSITION_OFFSCREEN"] = MOUSE_POSITION_OFFSCREEN;
    lua["KTouchState"].setClass(UserdataMetatable<TouchState>()

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

    lua["KJoystickState"].setClass(UserdataMetatable<JoystickState>()
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

    // GC is disable for subsystem object
    lua["KInput"].setClass(UserdataMetatable<Input, Object>()

        .addFunction("SetToggleFullscreen", &Input::SetToggleFullscreen)
        .addFunction("SetMouseVisible", &Input::SetMouseVisible)
        .addFunction("ResetMouseVisible", &Input::ResetMouseVisible)
        .addFunction("SetMouseGrabbed", &Input::SetMouseGrabbed)
        .addFunction("ResetMouseGrabbed", &Input::ResetMouseGrabbed)
        .addFunction("SetMouseMode", &Input::SetMouseMode)
        .addFunction("ResetMouseMode", &Input::ResetMouseMode)
        .addFunction("AddScreenJoystick", &Input::AddScreenJoystick)
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
        .addProperty("mouseVisible", &Input::IsMouseVisible)
        .addProperty("mouseGrabbed", &Input::IsMouseGrabbed)
        .addProperty("mouseLocked", &Input::IsMouseLocked)
        .addProperty("mouseMode", &Input::GetMouseMode)
        .addProperty("minimized", &Input::IsMinimized)
    );
}

static void RegisterInputEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KE_MOUSEBUTTONDOWN"] = E_MOUSEBUTTONDOWN;
    lua["KE_MOUSEBUTTONUP"] = E_MOUSEBUTTONUP;
    lua["KE_MOUSEMOVE"] = E_MOUSEMOVE;
    lua["KE_MOUSEWHEEL"] = E_MOUSEWHEEL;
    lua["KE_KEYDOWN"] = E_KEYDOWN;
    lua["KE_KEYUP"] = E_KEYUP;
    lua["KE_TEXTINPUT"] = E_TEXTINPUT;
    lua["KE_JOYSTICKCONNECTED"] = E_JOYSTICKCONNECTED;
    lua["KE_JOYSTICKDISCONNECTED"] = E_JOYSTICKDISCONNECTED;
    lua["KE_JOYSTICKBUTTONDOWN"] = E_JOYSTICKBUTTONDOWN;
    lua["KE_JOYSTICKBUTTONUP"] = E_JOYSTICKBUTTONUP;
    lua["KE_JOYSTICKAXISMOVE"] = E_JOYSTICKAXISMOVE;
    lua["KE_JOYSTICKHATMOVE"] = E_JOYSTICKHATMOVE;
    lua["KE_TOUCHBEGIN"] = E_TOUCHBEGIN;
    lua["KE_TOUCHEND"] = E_TOUCHEND;
    lua["KE_TOUCHMOVE"] = E_TOUCHMOVE;
    lua["KE_GESTURERECORDED"] = E_GESTURERECORDED;
    lua["KE_GESTUREINPUT"] = E_GESTUREINPUT;
    lua["KE_MULTIGESTURE"] = E_MULTIGESTURE;
    lua["KE_DROPFILE"] = E_DROPFILE;
    lua["KE_INPUTFOCUS"] = E_INPUTFOCUS;
    lua["KE_MOUSEVISIBLECHANGED"] = E_MOUSEVISIBLECHANGED;
    lua["KE_MOUSEMODECHANGED"] = E_MOUSEMODECHANGED;
    lua["KE_EXITREQUESTED"] = E_EXITREQUESTED;
    lua["KMOUSEB_LEFT"] = MOUSEB_LEFT;
    lua["KMOUSEB_MIDDLE"] = MOUSEB_MIDDLE;
    lua["KMOUSEB_RIGHT"] = MOUSEB_RIGHT;
    lua["KMOUSEB_X1"] = MOUSEB_X1;
    lua["KMOUSEB_X2"] = MOUSEB_X2;
    lua["KQUAL_SHIFT"] = QUAL_SHIFT;
    lua["KQUAL_CTRL"] = QUAL_CTRL;
    lua["KQUAL_ALT"] = QUAL_ALT;
    lua["KQUAL_ANY"] = QUAL_ANY;
    lua["KKEY_A"] = KEY_A;
    lua["KKEY_B"] = KEY_B;
    lua["KKEY_C"] = KEY_C;
    lua["KKEY_D"] = KEY_D;
    lua["KKEY_E"] = KEY_E;
    lua["KKEY_F"] = KEY_F;
    lua["KKEY_G"] = KEY_G;
    lua["KKEY_H"] = KEY_H;
    lua["KKEY_I"] = KEY_I;
    lua["KKEY_J"] = KEY_J;
    lua["KKEY_K"] = KEY_K;
    lua["KKEY_L"] = KEY_L;
    lua["KKEY_M"] = KEY_M;
    lua["KKEY_N"] = KEY_N;
    lua["KKEY_O"] = KEY_O;
    lua["KKEY_P"] = KEY_P;
    lua["KKEY_Q"] = KEY_Q;
    lua["KKEY_R"] = KEY_R;
    lua["KKEY_S"] = KEY_S;
    lua["KKEY_T"] = KEY_T;
    lua["KKEY_U"] = KEY_U;
    lua["KKEY_V"] = KEY_V;
    lua["KKEY_W"] = KEY_W;
    lua["KKEY_X"] = KEY_X;
    lua["KKEY_Y"] = KEY_Y;
    lua["KKEY_Z"] = KEY_Z;
    lua["KKEY_0"] = KEY_0;
    lua["KKEY_1"] = KEY_1;
    lua["KKEY_2"] = KEY_2;
    lua["KKEY_3"] = KEY_3;
    lua["KKEY_4"] = KEY_4;
    lua["KKEY_5"] = KEY_5;
    lua["KKEY_6"] = KEY_6;
    lua["KKEY_7"] = KEY_7;
    lua["KKEY_8"] = KEY_8;
    lua["KKEY_9"] = KEY_9;
    lua["KKEY_BACKSPACE"] = KEY_BACKSPACE;
    lua["KKEY_TAB"] = KEY_TAB;
    lua["KKEY_RETURN"] = KEY_RETURN;
    lua["KKEY_RETURN2"] = KEY_RETURN2;
    lua["KKEY_KP_ENTER"] = KEY_KP_ENTER;
    lua["KKEY_SHIFT"] = KEY_SHIFT;
    lua["KKEY_CTRL"] = KEY_CTRL;
    lua["KKEY_ALT"] = KEY_ALT;
    lua["KKEY_GUI"] = KEY_GUI;
    lua["KKEY_PAUSE"] = KEY_PAUSE;
    lua["KKEY_CAPSLOCK"] = KEY_CAPSLOCK;
    lua["KKEY_ESCAPE"] = KEY_ESCAPE;
    lua["KKEY_SPACE"] = KEY_SPACE;
    lua["KKEY_PAGEUP"] = KEY_PAGEUP;
    lua["KKEY_PAGEDOWN"] = KEY_PAGEDOWN;
    lua["KKEY_END"] = KEY_END;
    lua["KKEY_HOME"] = KEY_HOME;
    lua["KKEY_LEFT"] = KEY_LEFT;
    lua["KKEY_UP"] = KEY_UP;
    lua["KKEY_RIGHT"] = KEY_RIGHT;
    lua["KKEY_DOWN"] = KEY_DOWN;
    lua["KKEY_SELECT"] = KEY_SELECT;
    lua["KKEY_PRINTSCREEN"] = KEY_PRINTSCREEN;
    lua["KKEY_INSERT"] = KEY_INSERT;
    lua["KKEY_DELETE"] = KEY_DELETE;
    lua["KKEY_LGUI"] = KEY_LGUI;
    lua["KKEY_RGUI"] = KEY_RGUI;
    lua["KKEY_APPLICATION"] = KEY_APPLICATION;
    lua["KKEY_KP_0"] = KEY_KP_0;
    lua["KKEY_KP_1"] = KEY_KP_1;
    lua["KKEY_KP_2"] = KEY_KP_2;
    lua["KKEY_KP_3"] = KEY_KP_3;
    lua["KKEY_KP_4"] = KEY_KP_4;
    lua["KKEY_KP_5"] = KEY_KP_5;
    lua["KKEY_KP_6"] = KEY_KP_6;
    lua["KKEY_KP_7"] = KEY_KP_7;
    lua["KKEY_KP_8"] = KEY_KP_8;
    lua["KKEY_KP_9"] = KEY_KP_9;
    lua["KKEY_KP_MULTIPLY"] = KEY_KP_MULTIPLY;
    lua["KKEY_KP_PLUS"] = KEY_KP_PLUS;
    lua["KKEY_KP_MINUS"] = KEY_KP_MINUS;
    lua["KKEY_KP_PERIOD"] = KEY_KP_PERIOD;
    lua["KKEY_KP_DIVIDE"] = KEY_KP_DIVIDE;
    lua["KKEY_F1"] = KEY_F1;
    lua["KKEY_F2"] = KEY_F2;
    lua["KKEY_F3"] = KEY_F3;
    lua["KKEY_F4"] = KEY_F4;
    lua["KKEY_F5"] = KEY_F5;
    lua["KKEY_F6"] = KEY_F6;
    lua["KKEY_F7"] = KEY_F7;
    lua["KKEY_F8"] = KEY_F8;
    lua["KKEY_F9"] = KEY_F9;
    lua["KKEY_F10"] = KEY_F10;
    lua["KKEY_F11"] = KEY_F11;
    lua["KKEY_F12"] = KEY_F12;
    lua["KKEY_F13"] = KEY_F13;
    lua["KKEY_F14"] = KEY_F14;
    lua["KKEY_F15"] = KEY_F15;
    lua["KKEY_F16"] = KEY_F16;
    lua["KKEY_F17"] = KEY_F17;
    lua["KKEY_F18"] = KEY_F18;
    lua["KKEY_F19"] = KEY_F19;
    lua["KKEY_F20"] = KEY_F20;
    lua["KKEY_F21"] = KEY_F21;
    lua["KKEY_F22"] = KEY_F22;
    lua["KKEY_F23"] = KEY_F23;
    lua["KKEY_F24"] = KEY_F24;
    lua["KKEY_NUMLOCKCLEAR"] = KEY_NUMLOCKCLEAR;
    lua["KKEY_SCROLLLOCK"] = KEY_SCROLLLOCK;
    lua["KKEY_LSHIFT"] = KEY_LSHIFT;
    lua["KKEY_RSHIFT"] = KEY_RSHIFT;
    lua["KKEY_LCTRL"] = KEY_LCTRL;
    lua["KKEY_RCTRL"] = KEY_RCTRL;
    lua["KKEY_LALT"] = KEY_LALT;
    lua["KKEY_RALT"] = KEY_RALT;
    lua["KSCANCODE_UNKNOWN"] = SCANCODE_UNKNOWN;
    lua["KSCANCODE_CTRL"] = SCANCODE_CTRL;
    lua["KSCANCODE_SHIFT"] = SCANCODE_SHIFT;
    lua["KSCANCODE_ALT"] = SCANCODE_ALT;
    lua["KSCANCODE_GUI"] = SCANCODE_GUI;
    lua["KSCANCODE_A"] = SCANCODE_A;
    lua["KSCANCODE_B"] = SCANCODE_B;
    lua["KSCANCODE_C"] = SCANCODE_C;
    lua["KSCANCODE_D"] = SCANCODE_D;
    lua["KSCANCODE_E"] = SCANCODE_E;
    lua["KSCANCODE_F"] = SCANCODE_F;
    lua["KSCANCODE_G"] = SCANCODE_G;
    lua["KSCANCODE_H"] = SCANCODE_H;
    lua["KSCANCODE_I"] = SCANCODE_I;
    lua["KSCANCODE_J"] = SCANCODE_J;
    lua["KSCANCODE_K"] = SCANCODE_K;
    lua["KSCANCODE_L"] = SCANCODE_L;
    lua["KSCANCODE_M"] = SCANCODE_M;
    lua["KSCANCODE_N"] = SCANCODE_N;
    lua["KSCANCODE_O"] = SCANCODE_O;
    lua["KSCANCODE_P"] = SCANCODE_P;
    lua["KSCANCODE_Q"] = SCANCODE_Q;
    lua["KSCANCODE_R"] = SCANCODE_R;
    lua["KSCANCODE_S"] = SCANCODE_S;
    lua["KSCANCODE_T"] = SCANCODE_T;
    lua["KSCANCODE_U"] = SCANCODE_U;
    lua["KSCANCODE_V"] = SCANCODE_V;
    lua["KSCANCODE_W"] = SCANCODE_W;
    lua["KSCANCODE_X"] = SCANCODE_X;
    lua["KSCANCODE_Y"] = SCANCODE_Y;
    lua["KSCANCODE_Z"] = SCANCODE_Z;
    lua["KSCANCODE_1"] = SCANCODE_1;
    lua["KSCANCODE_2"] = SCANCODE_2;
    lua["KSCANCODE_3"] = SCANCODE_3;
    lua["KSCANCODE_4"] = SCANCODE_4;
    lua["KSCANCODE_5"] = SCANCODE_5;
    lua["KSCANCODE_6"] = SCANCODE_6;
    lua["KSCANCODE_7"] = SCANCODE_7;
    lua["KSCANCODE_8"] = SCANCODE_8;
    lua["KSCANCODE_9"] = SCANCODE_9;
    lua["KSCANCODE_0"] = SCANCODE_0;
    lua["KSCANCODE_RETURN"] = SCANCODE_RETURN;
    lua["KSCANCODE_ESCAPE"] = SCANCODE_ESCAPE;
    lua["KSCANCODE_BACKSPACE"] = SCANCODE_BACKSPACE;
    lua["KSCANCODE_TAB"] = SCANCODE_TAB;
    lua["KSCANCODE_SPACE"] = SCANCODE_SPACE;
    lua["KSCANCODE_MINUS"] = SCANCODE_MINUS;
    lua["KSCANCODE_EQUALS"] = SCANCODE_EQUALS;
    lua["KSCANCODE_LEFTBRACKET"] = SCANCODE_LEFTBRACKET;
    lua["KSCANCODE_RIGHTBRACKET"] = SCANCODE_RIGHTBRACKET;
    lua["KSCANCODE_BACKSLASH"] = SCANCODE_BACKSLASH;
    lua["KSCANCODE_NONUSHASH"] = SCANCODE_NONUSHASH;
    lua["KSCANCODE_SEMICOLON"] = SCANCODE_SEMICOLON;
    lua["KSCANCODE_APOSTROPHE"] = SCANCODE_APOSTROPHE;
    lua["KSCANCODE_GRAVE"] = SCANCODE_GRAVE;
    lua["KSCANCODE_COMMA"] = SCANCODE_COMMA;
    lua["KSCANCODE_PERIOD"] = SCANCODE_PERIOD;
    lua["KSCANCODE_SLASH"] = SCANCODE_SLASH;
    lua["KSCANCODE_CAPSLOCK"] = SCANCODE_CAPSLOCK;
    lua["KSCANCODE_F1"] = SCANCODE_F1;
    lua["KSCANCODE_F2"] = SCANCODE_F2;
    lua["KSCANCODE_F3"] = SCANCODE_F3;
    lua["KSCANCODE_F4"] = SCANCODE_F4;
    lua["KSCANCODE_F5"] = SCANCODE_F5;
    lua["KSCANCODE_F6"] = SCANCODE_F6;
    lua["KSCANCODE_F7"] = SCANCODE_F7;
    lua["KSCANCODE_F8"] = SCANCODE_F8;
    lua["KSCANCODE_F9"] = SCANCODE_F9;
    lua["KSCANCODE_F10"] = SCANCODE_F10;
    lua["KSCANCODE_F11"] = SCANCODE_F11;
    lua["KSCANCODE_F12"] = SCANCODE_F12;
    lua["KSCANCODE_PRINTSCREEN"] = SCANCODE_PRINTSCREEN;
    lua["KSCANCODE_SCROLLLOCK"] = SCANCODE_SCROLLLOCK;
    lua["KSCANCODE_PAUSE"] = SCANCODE_PAUSE;
    lua["KSCANCODE_INSERT"] = SCANCODE_INSERT;
    lua["KSCANCODE_HOME"] = SCANCODE_HOME;
    lua["KSCANCODE_PAGEUP"] = SCANCODE_PAGEUP;
    lua["KSCANCODE_DELETE"] = SCANCODE_DELETE;
    lua["KSCANCODE_END"] = SCANCODE_END;
    lua["KSCANCODE_PAGEDOWN"] = SCANCODE_PAGEDOWN;
    lua["KSCANCODE_RIGHT"] = SCANCODE_RIGHT;
    lua["KSCANCODE_LEFT"] = SCANCODE_LEFT;
    lua["KSCANCODE_DOWN"] = SCANCODE_DOWN;
    lua["KSCANCODE_UP"] = SCANCODE_UP;
    lua["KSCANCODE_NUMLOCKCLEAR"] = SCANCODE_NUMLOCKCLEAR;
    lua["KSCANCODE_KP_DIVIDE"] = SCANCODE_KP_DIVIDE;
    lua["KSCANCODE_KP_MULTIPLY"] = SCANCODE_KP_MULTIPLY;
    lua["KSCANCODE_KP_MINUS"] = SCANCODE_KP_MINUS;
    lua["KSCANCODE_KP_PLUS"] = SCANCODE_KP_PLUS;
    lua["KSCANCODE_KP_ENTER"] = SCANCODE_KP_ENTER;
    lua["KSCANCODE_KP_1"] = SCANCODE_KP_1;
    lua["KSCANCODE_KP_2"] = SCANCODE_KP_2;
    lua["KSCANCODE_KP_3"] = SCANCODE_KP_3;
    lua["KSCANCODE_KP_4"] = SCANCODE_KP_4;
    lua["KSCANCODE_KP_5"] = SCANCODE_KP_5;
    lua["KSCANCODE_KP_6"] = SCANCODE_KP_6;
    lua["KSCANCODE_KP_7"] = SCANCODE_KP_7;
    lua["KSCANCODE_KP_8"] = SCANCODE_KP_8;
    lua["KSCANCODE_KP_9"] = SCANCODE_KP_9;
    lua["KSCANCODE_KP_0"] = SCANCODE_KP_0;
    lua["KSCANCODE_KP_PERIOD"] = SCANCODE_KP_PERIOD;
    lua["KSCANCODE_NONUSBACKSLASH"] = SCANCODE_NONUSBACKSLASH;
    lua["KSCANCODE_APPLICATION"] = SCANCODE_APPLICATION;
    lua["KSCANCODE_POWER"] = SCANCODE_POWER;
    lua["KSCANCODE_KP_EQUALS"] = SCANCODE_KP_EQUALS;
    lua["KSCANCODE_F13"] = SCANCODE_F13;
    lua["KSCANCODE_F14"] = SCANCODE_F14;
    lua["KSCANCODE_F15"] = SCANCODE_F15;
    lua["KSCANCODE_F16"] = SCANCODE_F16;
    lua["KSCANCODE_F17"] = SCANCODE_F17;
    lua["KSCANCODE_F18"] = SCANCODE_F18;
    lua["KSCANCODE_F19"] = SCANCODE_F19;
    lua["KSCANCODE_F20"] = SCANCODE_F20;
    lua["KSCANCODE_F21"] = SCANCODE_F21;
    lua["KSCANCODE_F22"] = SCANCODE_F22;
    lua["KSCANCODE_F23"] = SCANCODE_F23;
    lua["KSCANCODE_F24"] = SCANCODE_F24;
    lua["KSCANCODE_EXECUTE"] = SCANCODE_EXECUTE;
    lua["KSCANCODE_HELP"] = SCANCODE_HELP;
    lua["KSCANCODE_MENU"] = SCANCODE_MENU;
    lua["KSCANCODE_SELECT"] = SCANCODE_SELECT;
    lua["KSCANCODE_STOP"] = SCANCODE_STOP;
    lua["KSCANCODE_AGAIN"] = SCANCODE_AGAIN;
    lua["KSCANCODE_UNDO"] = SCANCODE_UNDO;
    lua["KSCANCODE_CUT"] = SCANCODE_CUT;
    lua["KSCANCODE_COPY"] = SCANCODE_COPY;
    lua["KSCANCODE_PASTE"] = SCANCODE_PASTE;
    lua["KSCANCODE_FIND"] = SCANCODE_FIND;
    lua["KSCANCODE_MUTE"] = SCANCODE_MUTE;
    lua["KSCANCODE_VOLUMEUP"] = SCANCODE_VOLUMEUP;
    lua["KSCANCODE_VOLUMEDOWN"] = SCANCODE_VOLUMEDOWN;
    lua["KSCANCODE_KP_COMMA"] = SCANCODE_KP_COMMA;
    lua["KSCANCODE_KP_EQUALSAS400"] = SCANCODE_KP_EQUALSAS400;
    lua["KSCANCODE_INTERNATIONAL1"] = SCANCODE_INTERNATIONAL1;
    lua["KSCANCODE_INTERNATIONAL2"] = SCANCODE_INTERNATIONAL2;
    lua["KSCANCODE_INTERNATIONAL3"] = SCANCODE_INTERNATIONAL3;
    lua["KSCANCODE_INTERNATIONAL4"] = SCANCODE_INTERNATIONAL4;
    lua["KSCANCODE_INTERNATIONAL5"] = SCANCODE_INTERNATIONAL5;
    lua["KSCANCODE_INTERNATIONAL6"] = SCANCODE_INTERNATIONAL6;
    lua["KSCANCODE_INTERNATIONAL7"] = SCANCODE_INTERNATIONAL7;
    lua["KSCANCODE_INTERNATIONAL8"] = SCANCODE_INTERNATIONAL8;
    lua["KSCANCODE_INTERNATIONAL9"] = SCANCODE_INTERNATIONAL9;
    lua["KSCANCODE_LANG1"] = SCANCODE_LANG1;
    lua["KSCANCODE_LANG2"] = SCANCODE_LANG2;
    lua["KSCANCODE_LANG3"] = SCANCODE_LANG3;
    lua["KSCANCODE_LANG4"] = SCANCODE_LANG4;
    lua["KSCANCODE_LANG5"] = SCANCODE_LANG5;
    lua["KSCANCODE_LANG6"] = SCANCODE_LANG6;
    lua["KSCANCODE_LANG7"] = SCANCODE_LANG7;
    lua["KSCANCODE_LANG8"] = SCANCODE_LANG8;
    lua["KSCANCODE_LANG9"] = SCANCODE_LANG9;
    lua["KSCANCODE_ALTERASE"] = SCANCODE_ALTERASE;
    lua["KSCANCODE_SYSREQ"] = SCANCODE_SYSREQ;
    lua["KSCANCODE_CANCEL"] = SCANCODE_CANCEL;
    lua["KSCANCODE_CLEAR"] = SCANCODE_CLEAR;
    lua["KSCANCODE_PRIOR"] = SCANCODE_PRIOR;
    lua["KSCANCODE_RETURN2"] = SCANCODE_RETURN2;
    lua["KSCANCODE_SEPARATOR"] = SCANCODE_SEPARATOR;
    lua["KSCANCODE_OUT"] = SCANCODE_OUT;
    lua["KSCANCODE_OPER"] = SCANCODE_OPER;
    lua["KSCANCODE_CLEARAGAIN"] = SCANCODE_CLEARAGAIN;
    lua["KSCANCODE_CRSEL"] = SCANCODE_CRSEL;
    lua["KSCANCODE_EXSEL"] = SCANCODE_EXSEL;
    lua["KSCANCODE_KP_00"] = SCANCODE_KP_00;
    lua["KSCANCODE_KP_000"] = SCANCODE_KP_000;
    lua["KSCANCODE_THOUSANDSSEPARATOR"] = SCANCODE_THOUSANDSSEPARATOR;
    lua["KSCANCODE_DECIMALSEPARATOR"] = SCANCODE_DECIMALSEPARATOR;
    lua["KSCANCODE_CURRENCYUNIT"] = SCANCODE_CURRENCYUNIT;
    lua["KSCANCODE_CURRENCYSUBUNIT"] = SCANCODE_CURRENCYSUBUNIT;
    lua["KSCANCODE_KP_LEFTPAREN"] = SCANCODE_KP_LEFTPAREN;
    lua["KSCANCODE_KP_RIGHTPAREN"] = SCANCODE_KP_RIGHTPAREN;
    lua["KSCANCODE_KP_LEFTBRACE"] = SCANCODE_KP_LEFTBRACE;
    lua["KSCANCODE_KP_RIGHTBRACE"] = SCANCODE_KP_RIGHTBRACE;
    lua["KSCANCODE_KP_TAB"] = SCANCODE_KP_TAB;
    lua["KSCANCODE_KP_BACKSPACE"] = SCANCODE_KP_BACKSPACE;
    lua["KSCANCODE_KP_A"] = SCANCODE_KP_A;
    lua["KSCANCODE_KP_B"] = SCANCODE_KP_B;
    lua["KSCANCODE_KP_C"] = SCANCODE_KP_C;
    lua["KSCANCODE_KP_D"] = SCANCODE_KP_D;
    lua["KSCANCODE_KP_E"] = SCANCODE_KP_E;
    lua["KSCANCODE_KP_F"] = SCANCODE_KP_F;
    lua["KSCANCODE_KP_XOR"] = SCANCODE_KP_XOR;
    lua["KSCANCODE_KP_POWER"] = SCANCODE_KP_POWER;
    lua["KSCANCODE_KP_PERCENT"] = SCANCODE_KP_PERCENT;
    lua["KSCANCODE_KP_LESS"] = SCANCODE_KP_LESS;
    lua["KSCANCODE_KP_GREATER"] = SCANCODE_KP_GREATER;
    lua["KSCANCODE_KP_AMPERSAND"] = SCANCODE_KP_AMPERSAND;
    lua["KSCANCODE_KP_DBLAMPERSAND"] = SCANCODE_KP_DBLAMPERSAND;
    lua["KSCANCODE_KP_VERTICALBAR"] = SCANCODE_KP_VERTICALBAR;
    lua["KSCANCODE_KP_DBLVERTICALBAR"] = SCANCODE_KP_DBLVERTICALBAR;
    lua["KSCANCODE_KP_COLON"] = SCANCODE_KP_COLON;
    lua["KSCANCODE_KP_HASH"] = SCANCODE_KP_HASH;
    lua["KSCANCODE_KP_SPACE"] = SCANCODE_KP_SPACE;
    lua["KSCANCODE_KP_AT"] = SCANCODE_KP_AT;
    lua["KSCANCODE_KP_EXCLAM"] = SCANCODE_KP_EXCLAM;
    lua["KSCANCODE_KP_MEMSTORE"] = SCANCODE_KP_MEMSTORE;
    lua["KSCANCODE_KP_MEMRECALL"] = SCANCODE_KP_MEMRECALL;
    lua["KSCANCODE_KP_MEMCLEAR"] = SCANCODE_KP_MEMCLEAR;
    lua["KSCANCODE_KP_MEMADD"] = SCANCODE_KP_MEMADD;
    lua["KSCANCODE_KP_MEMSUBTRACT"] = SCANCODE_KP_MEMSUBTRACT;
    lua["KSCANCODE_KP_MEMMULTIPLY"] = SCANCODE_KP_MEMMULTIPLY;
    lua["KSCANCODE_KP_MEMDIVIDE"] = SCANCODE_KP_MEMDIVIDE;
    lua["KSCANCODE_KP_PLUSMINUS"] = SCANCODE_KP_PLUSMINUS;
    lua["KSCANCODE_KP_CLEAR"] = SCANCODE_KP_CLEAR;
    lua["KSCANCODE_KP_CLEARENTRY"] = SCANCODE_KP_CLEARENTRY;
    lua["KSCANCODE_KP_BINARY"] = SCANCODE_KP_BINARY;
    lua["KSCANCODE_KP_OCTAL"] = SCANCODE_KP_OCTAL;
    lua["KSCANCODE_KP_DECIMAL"] = SCANCODE_KP_DECIMAL;
    lua["KSCANCODE_KP_HEXADECIMAL"] = SCANCODE_KP_HEXADECIMAL;
    lua["KSCANCODE_LCTRL"] = SCANCODE_LCTRL;
    lua["KSCANCODE_LSHIFT"] = SCANCODE_LSHIFT;
    lua["KSCANCODE_LALT"] = SCANCODE_LALT;
    lua["KSCANCODE_LGUI"] = SCANCODE_LGUI;
    lua["KSCANCODE_RCTRL"] = SCANCODE_RCTRL;
    lua["KSCANCODE_RSHIFT"] = SCANCODE_RSHIFT;
    lua["KSCANCODE_RALT"] = SCANCODE_RALT;
    lua["KSCANCODE_RGUI"] = SCANCODE_RGUI;
    lua["KSCANCODE_MODE"] = SCANCODE_MODE;
    lua["KSCANCODE_AUDIONEXT"] = SCANCODE_AUDIONEXT;
    lua["KSCANCODE_AUDIOPREV"] = SCANCODE_AUDIOPREV;
    lua["KSCANCODE_AUDIOSTOP"] = SCANCODE_AUDIOSTOP;
    lua["KSCANCODE_AUDIOPLAY"] = SCANCODE_AUDIOPLAY;
    lua["KSCANCODE_AUDIOMUTE"] = SCANCODE_AUDIOMUTE;
    lua["KSCANCODE_MEDIASELECT"] = SCANCODE_MEDIASELECT;
    lua["KSCANCODE_WWW"] = SCANCODE_WWW;
    lua["KSCANCODE_MAIL"] = SCANCODE_MAIL;
    lua["KSCANCODE_CALCULATOR"] = SCANCODE_CALCULATOR;
    lua["KSCANCODE_COMPUTER"] = SCANCODE_COMPUTER;
    lua["KSCANCODE_AC_SEARCH"] = SCANCODE_AC_SEARCH;
    lua["KSCANCODE_AC_HOME"] = SCANCODE_AC_HOME;
    lua["KSCANCODE_AC_BACK"] = SCANCODE_AC_BACK;
    lua["KSCANCODE_AC_FORWARD"] = SCANCODE_AC_FORWARD;
    lua["KSCANCODE_AC_STOP"] = SCANCODE_AC_STOP;
    lua["KSCANCODE_AC_REFRESH"] = SCANCODE_AC_REFRESH;
    lua["KSCANCODE_AC_BOOKMARKS"] = SCANCODE_AC_BOOKMARKS;
    lua["KSCANCODE_BRIGHTNESSDOWN"] = SCANCODE_BRIGHTNESSDOWN;
    lua["KSCANCODE_BRIGHTNESSUP"] = SCANCODE_BRIGHTNESSUP;
    lua["KSCANCODE_DISPLAYSWITCH"] = SCANCODE_DISPLAYSWITCH;
    lua["KSCANCODE_KBDILLUMTOGGLE"] = SCANCODE_KBDILLUMTOGGLE;
    lua["KSCANCODE_KBDILLUMDOWN"] = SCANCODE_KBDILLUMDOWN;
    lua["KSCANCODE_KBDILLUMUP"] = SCANCODE_KBDILLUMUP;
    lua["KSCANCODE_EJECT"] = SCANCODE_EJECT;
    lua["KSCANCODE_SLEEP"] = SCANCODE_SLEEP;
    lua["KSCANCODE_APP1"] = SCANCODE_APP1;
    lua["KSCANCODE_APP2"] = SCANCODE_APP2;
    lua["KHAT_CENTER"] = HAT_CENTER;
    lua["KHAT_UP"] = HAT_UP;
    lua["KHAT_RIGHT"] = HAT_RIGHT;
    lua["KHAT_DOWN"] = HAT_DOWN;
    lua["KHAT_LEFT"] = HAT_LEFT;
    lua["KCONTROLLER_BUTTON_A"] = CONTROLLER_BUTTON_A;
    lua["KCONTROLLER_BUTTON_B"] = CONTROLLER_BUTTON_B;
    lua["KCONTROLLER_BUTTON_X"] = CONTROLLER_BUTTON_X;
    lua["KCONTROLLER_BUTTON_Y"] = CONTROLLER_BUTTON_Y;
    lua["KCONTROLLER_BUTTON_BACK"] = CONTROLLER_BUTTON_BACK;
    lua["KCONTROLLER_BUTTON_GUIDE"] = CONTROLLER_BUTTON_GUIDE;
    lua["KCONTROLLER_BUTTON_START"] = CONTROLLER_BUTTON_START;
    lua["KCONTROLLER_BUTTON_LEFTSTICK"] = CONTROLLER_BUTTON_LEFTSTICK;
    lua["KCONTROLLER_BUTTON_RIGHTSTICK"] = CONTROLLER_BUTTON_RIGHTSTICK;
    lua["KCONTROLLER_BUTTON_LEFTSHOULDER"] = CONTROLLER_BUTTON_LEFTSHOULDER;
    lua["KCONTROLLER_BUTTON_RIGHTSHOULDER"] = CONTROLLER_BUTTON_RIGHTSHOULDER;
    lua["KCONTROLLER_BUTTON_DPAD_UP"] = CONTROLLER_BUTTON_DPAD_UP;
    lua["KCONTROLLER_BUTTON_DPAD_DOWN"] = CONTROLLER_BUTTON_DPAD_DOWN;
    lua["KCONTROLLER_BUTTON_DPAD_LEFT"] = CONTROLLER_BUTTON_DPAD_LEFT;
    lua["KCONTROLLER_BUTTON_DPAD_RIGHT"] = CONTROLLER_BUTTON_DPAD_RIGHT;
    lua["KCONTROLLER_AXIS_LEFTX"] = CONTROLLER_AXIS_LEFTX;
    lua["KCONTROLLER_AXIS_LEFTY"] = CONTROLLER_AXIS_LEFTY;
    lua["KCONTROLLER_AXIS_RIGHTX"] = CONTROLLER_AXIS_RIGHTX;
    lua["KCONTROLLER_AXIS_RIGHTY"] = CONTROLLER_AXIS_RIGHTY;
    lua["KCONTROLLER_AXIS_TRIGGERLEFT"] = CONTROLLER_AXIS_TRIGGERLEFT;
    lua["KCONTROLLER_AXIS_TRIGGERRIGHT"] = CONTROLLER_AXIS_TRIGGERRIGHT;
}

void RegisterInputLuaAPI(kaguya::State& lua)
{
    RegisterControls(lua);
    RegisterInput(lua);
    RegisterInputEvents(lua);

    lua["kinput"] = KGetSubsystem<Input>();
    lua["KGetInput"] = KGetSubsystem<Input>;
}
}
