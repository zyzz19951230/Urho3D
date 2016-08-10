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

#include "../../Input/InputEvents.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterInputEvents(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] int MOUSEB_LEFT
    lua["MOUSEB_LEFT"] = MOUSEB_LEFT;
    // [Constant] int MOUSEB_MIDDLE
    lua["MOUSEB_MIDDLE"] = MOUSEB_MIDDLE;
    // [Constant] int MOUSEB_RIGHT
    lua["MOUSEB_RIGHT"] = MOUSEB_RIGHT;
    // [Constant] int MOUSEB_X1
    lua["MOUSEB_X1"] = MOUSEB_X1;
    // [Constant] int MOUSEB_X2
    lua["MOUSEB_X2"] = MOUSEB_X2;

    // [Constant] int QUAL_SHIFT
    lua["QUAL_SHIFT"] = QUAL_SHIFT;
    // [Constant] int QUAL_CTRL
    lua["QUAL_CTRL"] = QUAL_CTRL;
    // [Constant] int QUAL_ALT
    lua["QUAL_ALT"] = QUAL_ALT;
    // [Constant] int QUAL_ANY
    lua["QUAL_ANY"] = QUAL_ANY;

    // [Constant] int KEY_A
    lua["KEY_A"] = KEY_A;
    // [Constant] int KEY_B
    lua["KEY_B"] = KEY_B;
    // [Constant] int KEY_C
    lua["KEY_C"] = KEY_C;
    // [Constant] int KEY_D
    lua["KEY_D"] = KEY_D;
    // [Constant] int KEY_E
    lua["KEY_E"] = KEY_E;
    // [Constant] int KEY_F
    lua["KEY_F"] = KEY_F;
    // [Constant] int KEY_G
    lua["KEY_G"] = KEY_G;
    // [Constant] int KEY_H
    lua["KEY_H"] = KEY_H;
    // [Constant] int KEY_I
    lua["KEY_I"] = KEY_I;
    // [Constant] int KEY_J
    lua["KEY_J"] = KEY_J;
    // [Constant] int KEY_K
    lua["KEY_K"] = KEY_K;
    // [Constant] int KEY_L
    lua["KEY_L"] = KEY_L;
    // [Constant] int KEY_M
    lua["KEY_M"] = KEY_M;
    // [Constant] int KEY_N
    lua["KEY_N"] = KEY_N;
    // [Constant] int KEY_O
    lua["KEY_O"] = KEY_O;
    // [Constant] int KEY_P
    lua["KEY_P"] = KEY_P;
    // [Constant] int KEY_Q
    lua["KEY_Q"] = KEY_Q;
    // [Constant] int KEY_R
    lua["KEY_R"] = KEY_R;
    // [Constant] int KEY_S
    lua["KEY_S"] = KEY_S;
    // [Constant] int KEY_T
    lua["KEY_T"] = KEY_T;
    // [Constant] int KEY_U
    lua["KEY_U"] = KEY_U;
    // [Constant] int KEY_V
    lua["KEY_V"] = KEY_V;
    // [Constant] int KEY_W
    lua["KEY_W"] = KEY_W;
    // [Constant] int KEY_X
    lua["KEY_X"] = KEY_X;
    // [Constant] int KEY_Y
    lua["KEY_Y"] = KEY_Y;
    // [Constant] int KEY_Z
    lua["KEY_Z"] = KEY_Z;
    // [Constant] int KEY_0
    lua["KEY_0"] = KEY_0;
    // [Constant] int KEY_1
    lua["KEY_1"] = KEY_1;
    // [Constant] int KEY_2
    lua["KEY_2"] = KEY_2;
    // [Constant] int KEY_3
    lua["KEY_3"] = KEY_3;
    // [Constant] int KEY_4
    lua["KEY_4"] = KEY_4;
    // [Constant] int KEY_5
    lua["KEY_5"] = KEY_5;
    // [Constant] int KEY_6
    lua["KEY_6"] = KEY_6;
    // [Constant] int KEY_7
    lua["KEY_7"] = KEY_7;
    // [Constant] int KEY_8
    lua["KEY_8"] = KEY_8;
    // [Constant] int KEY_9
    lua["KEY_9"] = KEY_9;
    // [Constant] int KEY_BACKSPACE
    lua["KEY_BACKSPACE"] = KEY_BACKSPACE;
    // [Constant] int KEY_TAB
    lua["KEY_TAB"] = KEY_TAB;
    // [Constant] int KEY_RETURN
    lua["KEY_RETURN"] = KEY_RETURN;
    // [Constant] int KEY_RETURN2
    lua["KEY_RETURN2"] = KEY_RETURN2;
    // [Constant] int KEY_KP_ENTER
    lua["KEY_KP_ENTER"] = KEY_KP_ENTER;
    // [Constant] int KEY_SHIFT
    lua["KEY_SHIFT"] = KEY_SHIFT;
    // [Constant] int KEY_CTRL
    lua["KEY_CTRL"] = KEY_CTRL;
    // [Constant] int KEY_ALT
    lua["KEY_ALT"] = KEY_ALT;
    // [Constant] int KEY_GUI
    lua["KEY_GUI"] = KEY_GUI;
    // [Constant] int KEY_PAUSE
    lua["KEY_PAUSE"] = KEY_PAUSE;
    // [Constant] int KEY_CAPSLOCK
    lua["KEY_CAPSLOCK"] = KEY_CAPSLOCK;
    // [Constant] int KEY_ESCAPE
    lua["KEY_ESCAPE"] = KEY_ESCAPE;
    // [Constant] int KEY_SPACE
    lua["KEY_SPACE"] = KEY_SPACE;
    // [Constant] int KEY_PAGEUP
    lua["KEY_PAGEUP"] = KEY_PAGEUP;
    // [Constant] int KEY_PAGEDOWN
    lua["KEY_PAGEDOWN"] = KEY_PAGEDOWN;
    // [Constant] int KEY_END
    lua["KEY_END"] = KEY_END;
    // [Constant] int KEY_HOME
    lua["KEY_HOME"] = KEY_HOME;
    // [Constant] int KEY_LEFT
    lua["KEY_LEFT"] = KEY_LEFT;
    // [Constant] int KEY_UP
    lua["KEY_UP"] = KEY_UP;
    // [Constant] int KEY_RIGHT
    lua["KEY_RIGHT"] = KEY_RIGHT;
    // [Constant] int KEY_DOWN
    lua["KEY_DOWN"] = KEY_DOWN;
    // [Constant] int KEY_SELECT
    lua["KEY_SELECT"] = KEY_SELECT;
    // [Constant] int KEY_PRINTSCREEN
    lua["KEY_PRINTSCREEN"] = KEY_PRINTSCREEN;
    // [Constant] int KEY_INSERT
    lua["KEY_INSERT"] = KEY_INSERT;
    // [Constant] int KEY_DELETE
    lua["KEY_DELETE"] = KEY_DELETE;
    // [Constant] int KEY_LGUI
    lua["KEY_LGUI"] = KEY_LGUI;
    // [Constant] int KEY_RGUI
    lua["KEY_RGUI"] = KEY_RGUI;
    // [Constant] int KEY_APPLICATION
    lua["KEY_APPLICATION"] = KEY_APPLICATION;
    // [Constant] int KEY_KP_0
    lua["KEY_KP_0"] = KEY_KP_0;
    // [Constant] int KEY_KP_1
    lua["KEY_KP_1"] = KEY_KP_1;
    // [Constant] int KEY_KP_2
    lua["KEY_KP_2"] = KEY_KP_2;
    // [Constant] int KEY_KP_3
    lua["KEY_KP_3"] = KEY_KP_3;
    // [Constant] int KEY_KP_4
    lua["KEY_KP_4"] = KEY_KP_4;
    // [Constant] int KEY_KP_5
    lua["KEY_KP_5"] = KEY_KP_5;
    // [Constant] int KEY_KP_6
    lua["KEY_KP_6"] = KEY_KP_6;
    // [Constant] int KEY_KP_7
    lua["KEY_KP_7"] = KEY_KP_7;
    // [Constant] int KEY_KP_8
    lua["KEY_KP_8"] = KEY_KP_8;
    // [Constant] int KEY_KP_9
    lua["KEY_KP_9"] = KEY_KP_9;
    // [Constant] int KEY_KP_MULTIPLY
    lua["KEY_KP_MULTIPLY"] = KEY_KP_MULTIPLY;
    // [Constant] int KEY_KP_PLUS
    lua["KEY_KP_PLUS"] = KEY_KP_PLUS;
    // [Constant] int KEY_KP_MINUS
    lua["KEY_KP_MINUS"] = KEY_KP_MINUS;
    // [Constant] int KEY_KP_PERIOD
    lua["KEY_KP_PERIOD"] = KEY_KP_PERIOD;
    // [Constant] int KEY_KP_DIVIDE
    lua["KEY_KP_DIVIDE"] = KEY_KP_DIVIDE;
    // [Constant] int KEY_F1
    lua["KEY_F1"] = KEY_F1;
    // [Constant] int KEY_F2
    lua["KEY_F2"] = KEY_F2;
    // [Constant] int KEY_F3
    lua["KEY_F3"] = KEY_F3;
    // [Constant] int KEY_F4
    lua["KEY_F4"] = KEY_F4;
    // [Constant] int KEY_F5
    lua["KEY_F5"] = KEY_F5;
    // [Constant] int KEY_F6
    lua["KEY_F6"] = KEY_F6;
    // [Constant] int KEY_F7
    lua["KEY_F7"] = KEY_F7;
    // [Constant] int KEY_F8
    lua["KEY_F8"] = KEY_F8;
    // [Constant] int KEY_F9
    lua["KEY_F9"] = KEY_F9;
    // [Constant] int KEY_F10
    lua["KEY_F10"] = KEY_F10;
    // [Constant] int KEY_F11
    lua["KEY_F11"] = KEY_F11;
    // [Constant] int KEY_F12
    lua["KEY_F12"] = KEY_F12;
    // [Constant] int KEY_F13
    lua["KEY_F13"] = KEY_F13;
    // [Constant] int KEY_F14
    lua["KEY_F14"] = KEY_F14;
    // [Constant] int KEY_F15
    lua["KEY_F15"] = KEY_F15;
    // [Constant] int KEY_F16
    lua["KEY_F16"] = KEY_F16;
    // [Constant] int KEY_F17
    lua["KEY_F17"] = KEY_F17;
    // [Constant] int KEY_F18
    lua["KEY_F18"] = KEY_F18;
    // [Constant] int KEY_F19
    lua["KEY_F19"] = KEY_F19;
    // [Constant] int KEY_F20
    lua["KEY_F20"] = KEY_F20;
    // [Constant] int KEY_F21
    lua["KEY_F21"] = KEY_F21;
    // [Constant] int KEY_F22
    lua["KEY_F22"] = KEY_F22;
    // [Constant] int KEY_F23
    lua["KEY_F23"] = KEY_F23;
    // [Constant] int KEY_F24
    lua["KEY_F24"] = KEY_F24;
    // [Constant] int KEY_NUMLOCKCLEAR
    lua["KEY_NUMLOCKCLEAR"] = KEY_NUMLOCKCLEAR;
    // [Constant] int KEY_SCROLLLOCK
    lua["KEY_SCROLLLOCK"] = KEY_SCROLLLOCK;
    // [Constant] int KEY_LSHIFT
    lua["KEY_LSHIFT"] = KEY_LSHIFT;
    // [Constant] int KEY_RSHIFT
    lua["KEY_RSHIFT"] = KEY_RSHIFT;
    // [Constant] int KEY_LCTRL
    lua["KEY_LCTRL"] = KEY_LCTRL;
    // [Constant] int KEY_RCTRL
    lua["KEY_RCTRL"] = KEY_RCTRL;
    // [Constant] int KEY_LALT
    lua["KEY_LALT"] = KEY_LALT;
    // [Constant] int KEY_RALT
    lua["KEY_RALT"] = KEY_RALT;

    // [Constant] int SCANCODE_UNKNOWN
    lua["SCANCODE_UNKNOWN"] = SCANCODE_UNKNOWN;
    // [Constant] int SCANCODE_CTRL
    lua["SCANCODE_CTRL"] = SCANCODE_CTRL;
    // [Constant] int SCANCODE_SHIFT
    lua["SCANCODE_SHIFT"] = SCANCODE_SHIFT;
    // [Constant] int SCANCODE_ALT
    lua["SCANCODE_ALT"] = SCANCODE_ALT;
    // [Constant] int SCANCODE_GUI
    lua["SCANCODE_GUI"] = SCANCODE_GUI;
    // [Constant] int SCANCODE_ALT
    lua["SCANCODE_A"] = SCANCODE_A;
    // [Constant] int SCANCODE_B
    lua["SCANCODE_B"] = SCANCODE_B;
    // [Constant] int SCANCODE_CTRL
    lua["SCANCODE_C"] = SCANCODE_C;
    // [Constant] int SCANCODE_D
    lua["SCANCODE_D"] = SCANCODE_D;
    // [Constant] int SCANCODE_E
    lua["SCANCODE_E"] = SCANCODE_E;
    // [Constant] int SCANCODE_F
    lua["SCANCODE_F"] = SCANCODE_F;
    // [Constant] int SCANCODE_GUI
    lua["SCANCODE_G"] = SCANCODE_G;
    // [Constant] int SCANCODE_H
    lua["SCANCODE_H"] = SCANCODE_H;
    // [Constant] int SCANCODE_I
    lua["SCANCODE_I"] = SCANCODE_I;
    // [Constant] int SCANCODE_J
    lua["SCANCODE_J"] = SCANCODE_J;
    // [Constant] int SCANCODE_K
    lua["SCANCODE_K"] = SCANCODE_K;
    // [Constant] int SCANCODE_CTRL
    lua["SCANCODE_L"] = SCANCODE_L;
    // [Constant] int SCANCODE_M
    lua["SCANCODE_M"] = SCANCODE_M;
    // [Constant] int SCANCODE_N
    lua["SCANCODE_N"] = SCANCODE_N;
    // [Constant] int SCANCODE_O
    lua["SCANCODE_O"] = SCANCODE_O;
    // [Constant] int SCANCODE_P
    lua["SCANCODE_P"] = SCANCODE_P;
    // [Constant] int SCANCODE_Q
    lua["SCANCODE_Q"] = SCANCODE_Q;
    // [Constant] int SCANCODE_R
    lua["SCANCODE_R"] = SCANCODE_R;
    // [Constant] int SCANCODE_SHIFT
    lua["SCANCODE_S"] = SCANCODE_S;
    // [Constant] int SCANCODE_T
    lua["SCANCODE_T"] = SCANCODE_T;
    // [Constant] int SCANCODE_UNKNOWN
    lua["SCANCODE_U"] = SCANCODE_U;
    // [Constant] int SCANCODE_V
    lua["SCANCODE_V"] = SCANCODE_V;
    // [Constant] int SCANCODE_W
    lua["SCANCODE_W"] = SCANCODE_W;
    // [Constant] int SCANCODE_X
    lua["SCANCODE_X"] = SCANCODE_X;
    // [Constant] int SCANCODE_Y
    lua["SCANCODE_Y"] = SCANCODE_Y;
    // [Constant] int SCANCODE_Z
    lua["SCANCODE_Z"] = SCANCODE_Z;
    // [Constant] int SCANCODE_1
    lua["SCANCODE_1"] = SCANCODE_1;
    // [Constant] int SCANCODE_2
    lua["SCANCODE_2"] = SCANCODE_2;
    // [Constant] int SCANCODE_3
    lua["SCANCODE_3"] = SCANCODE_3;
    // [Constant] int SCANCODE_4
    lua["SCANCODE_4"] = SCANCODE_4;
    // [Constant] int SCANCODE_5
    lua["SCANCODE_5"] = SCANCODE_5;
    // [Constant] int SCANCODE_6
    lua["SCANCODE_6"] = SCANCODE_6;
    // [Constant] int SCANCODE_7
    lua["SCANCODE_7"] = SCANCODE_7;
    // [Constant] int SCANCODE_8
    lua["SCANCODE_8"] = SCANCODE_8;
    // [Constant] int SCANCODE_9
    lua["SCANCODE_9"] = SCANCODE_9;
    // [Constant] int SCANCODE_0
    lua["SCANCODE_0"] = SCANCODE_0;
    // [Constant] int SCANCODE_RETURN
    lua["SCANCODE_RETURN"] = SCANCODE_RETURN;
    // [Constant] int SCANCODE_ESCAPE
    lua["SCANCODE_ESCAPE"] = SCANCODE_ESCAPE;
    // [Constant] int SCANCODE_BACKSPACE
    lua["SCANCODE_BACKSPACE"] = SCANCODE_BACKSPACE;
    // [Constant] int SCANCODE_TAB
    lua["SCANCODE_TAB"] = SCANCODE_TAB;
    // [Constant] int SCANCODE_SPACE
    lua["SCANCODE_SPACE"] = SCANCODE_SPACE;
    // [Constant] int SCANCODE_MINUS
    lua["SCANCODE_MINUS"] = SCANCODE_MINUS;
    // [Constant] int SCANCODE_EQUALS
    lua["SCANCODE_EQUALS"] = SCANCODE_EQUALS;
    // [Constant] int SCANCODE_LEFTBRACKET
    lua["SCANCODE_LEFTBRACKET"] = SCANCODE_LEFTBRACKET;
    // [Constant] int SCANCODE_RIGHTBRACKET
    lua["SCANCODE_RIGHTBRACKET"] = SCANCODE_RIGHTBRACKET;
    // [Constant] int SCANCODE_BACKSLASH
    lua["SCANCODE_BACKSLASH"] = SCANCODE_BACKSLASH;
    // [Constant] int SCANCODE_NONUSHASH
    lua["SCANCODE_NONUSHASH"] = SCANCODE_NONUSHASH;
    // [Constant] int SCANCODE_SEMICOLON
    lua["SCANCODE_SEMICOLON"] = SCANCODE_SEMICOLON;
    // [Constant] int SCANCODE_APOSTROPHE
    lua["SCANCODE_APOSTROPHE"] = SCANCODE_APOSTROPHE;
    // [Constant] int SCANCODE_GRAVE
    lua["SCANCODE_GRAVE"] = SCANCODE_GRAVE;
    // [Constant] int SCANCODE_COMMA
    lua["SCANCODE_COMMA"] = SCANCODE_COMMA;
    // [Constant] int SCANCODE_PERIOD
    lua["SCANCODE_PERIOD"] = SCANCODE_PERIOD;
    // [Constant] int SCANCODE_SLASH
    lua["SCANCODE_SLASH"] = SCANCODE_SLASH;
    // [Constant] int SCANCODE_CAPSLOCK
    lua["SCANCODE_CAPSLOCK"] = SCANCODE_CAPSLOCK;
    // [Constant] int SCANCODE_F1
    lua["SCANCODE_F1"] = SCANCODE_F1;
    // [Constant] int SCANCODE_F2
    lua["SCANCODE_F2"] = SCANCODE_F2;
    // [Constant] int SCANCODE_F3
    lua["SCANCODE_F3"] = SCANCODE_F3;
    // [Constant] int SCANCODE_F4
    lua["SCANCODE_F4"] = SCANCODE_F4;
    // [Constant] int SCANCODE_F5
    lua["SCANCODE_F5"] = SCANCODE_F5;
    // [Constant] int SCANCODE_F6
    lua["SCANCODE_F6"] = SCANCODE_F6;
    // [Constant] int SCANCODE_F7
    lua["SCANCODE_F7"] = SCANCODE_F7;
    // [Constant] int SCANCODE_F8
    lua["SCANCODE_F8"] = SCANCODE_F8;
    // [Constant] int SCANCODE_F9
    lua["SCANCODE_F9"] = SCANCODE_F9;
    // [Constant] int SCANCODE_F10
    lua["SCANCODE_F10"] = SCANCODE_F10;
    // [Constant] int SCANCODE_F11
    lua["SCANCODE_F11"] = SCANCODE_F11;
    // [Constant] int SCANCODE_F12
    lua["SCANCODE_F12"] = SCANCODE_F12;
    // [Constant] int SCANCODE_PRINTSCREEN
    lua["SCANCODE_PRINTSCREEN"] = SCANCODE_PRINTSCREEN;
    // [Constant] int SCANCODE_SCROLLLOCK
    lua["SCANCODE_SCROLLLOCK"] = SCANCODE_SCROLLLOCK;
    // [Constant] int SCANCODE_PAUSE
    lua["SCANCODE_PAUSE"] = SCANCODE_PAUSE;
    // [Constant] int SCANCODE_INSERT
    lua["SCANCODE_INSERT"] = SCANCODE_INSERT;
    // [Constant] int SCANCODE_HOME
    lua["SCANCODE_HOME"] = SCANCODE_HOME;
    // [Constant] int SCANCODE_PAGEUP
    lua["SCANCODE_PAGEUP"] = SCANCODE_PAGEUP;
    // [Constant] int SCANCODE_DELETE
    lua["SCANCODE_DELETE"] = SCANCODE_DELETE;
    // [Constant] int SCANCODE_END
    lua["SCANCODE_END"] = SCANCODE_END;
    // [Constant] int SCANCODE_PAGEDOWN
    lua["SCANCODE_PAGEDOWN"] = SCANCODE_PAGEDOWN;
    // [Constant] int SCANCODE_RIGHTBRACKET
    lua["SCANCODE_RIGHT"] = SCANCODE_RIGHT;
    // [Constant] int SCANCODE_LEFTBRACKET
    lua["SCANCODE_LEFT"] = SCANCODE_LEFT;
    // [Constant] int SCANCODE_DOWN
    lua["SCANCODE_DOWN"] = SCANCODE_DOWN;
    // [Constant] int SCANCODE_UP
    lua["SCANCODE_UP"] = SCANCODE_UP;
    // [Constant] int SCANCODE_NUMLOCKCLEAR
    lua["SCANCODE_NUMLOCKCLEAR"] = SCANCODE_NUMLOCKCLEAR;
    // [Constant] int SCANCODE_KP_DIVIDE
    lua["SCANCODE_KP_DIVIDE"] = SCANCODE_KP_DIVIDE;
    // [Constant] int SCANCODE_KP_MULTIPLY
    lua["SCANCODE_KP_MULTIPLY"] = SCANCODE_KP_MULTIPLY;
    // [Constant] int SCANCODE_KP_MINUS
    lua["SCANCODE_KP_MINUS"] = SCANCODE_KP_MINUS;
    // [Constant] int SCANCODE_KP_PLUS
    lua["SCANCODE_KP_PLUS"] = SCANCODE_KP_PLUS;
    // [Constant] int SCANCODE_KP_ENTER
    lua["SCANCODE_KP_ENTER"] = SCANCODE_KP_ENTER;
    // [Constant] int SCANCODE_KP_1
    lua["SCANCODE_KP_1"] = SCANCODE_KP_1;
    // [Constant] int SCANCODE_KP_2
    lua["SCANCODE_KP_2"] = SCANCODE_KP_2;
    // [Constant] int SCANCODE_KP_3
    lua["SCANCODE_KP_3"] = SCANCODE_KP_3;
    // [Constant] int SCANCODE_KP_4
    lua["SCANCODE_KP_4"] = SCANCODE_KP_4;
    // [Constant] int SCANCODE_KP_5
    lua["SCANCODE_KP_5"] = SCANCODE_KP_5;
    // [Constant] int SCANCODE_KP_6
    lua["SCANCODE_KP_6"] = SCANCODE_KP_6;
    // [Constant] int SCANCODE_KP_7
    lua["SCANCODE_KP_7"] = SCANCODE_KP_7;
    // [Constant] int SCANCODE_KP_8
    lua["SCANCODE_KP_8"] = SCANCODE_KP_8;
    // [Constant] int SCANCODE_KP_9
    lua["SCANCODE_KP_9"] = SCANCODE_KP_9;
    // [Constant] int SCANCODE_KP_0
    lua["SCANCODE_KP_0"] = SCANCODE_KP_0;
    // [Constant] int SCANCODE_KP_PERIOD
    lua["SCANCODE_KP_PERIOD"] = SCANCODE_KP_PERIOD;
    // [Constant] int SCANCODE_NONUSBACKSLASH
    lua["SCANCODE_NONUSBACKSLASH"] = SCANCODE_NONUSBACKSLASH;
    // [Constant] int SCANCODE_APPLICATION
    lua["SCANCODE_APPLICATION"] = SCANCODE_APPLICATION;
    // [Constant] int SCANCODE_POWER
    lua["SCANCODE_POWER"] = SCANCODE_POWER;
    // [Constant] int SCANCODE_KP_EQUALS
    lua["SCANCODE_KP_EQUALS"] = SCANCODE_KP_EQUALS;
    // [Constant] int SCANCODE_F13
    lua["SCANCODE_F13"] = SCANCODE_F13;
    // [Constant] int SCANCODE_F14
    lua["SCANCODE_F14"] = SCANCODE_F14;
    // [Constant] int SCANCODE_F15
    lua["SCANCODE_F15"] = SCANCODE_F15;
    // [Constant] int SCANCODE_F16
    lua["SCANCODE_F16"] = SCANCODE_F16;
    // [Constant] int SCANCODE_F17
    lua["SCANCODE_F17"] = SCANCODE_F17;
    // [Constant] int SCANCODE_F18
    lua["SCANCODE_F18"] = SCANCODE_F18;
    // [Constant] int SCANCODE_F19
    lua["SCANCODE_F19"] = SCANCODE_F19;
    // [Constant] int SCANCODE_F20
    lua["SCANCODE_F20"] = SCANCODE_F20;
    // [Constant] int SCANCODE_F21
    lua["SCANCODE_F21"] = SCANCODE_F21;
    // [Constant] int SCANCODE_F22
    lua["SCANCODE_F22"] = SCANCODE_F22;
    // [Constant] int SCANCODE_F23
    lua["SCANCODE_F23"] = SCANCODE_F23;
    // [Constant] int SCANCODE_F24
    lua["SCANCODE_F24"] = SCANCODE_F24;
    // [Constant] int SCANCODE_EXECUTE
    lua["SCANCODE_EXECUTE"] = SCANCODE_EXECUTE;
    // [Constant] int SCANCODE_HELP
    lua["SCANCODE_HELP"] = SCANCODE_HELP;
    // [Constant] int SCANCODE_MENU
    lua["SCANCODE_MENU"] = SCANCODE_MENU;
    // [Constant] int SCANCODE_SELECT
    lua["SCANCODE_SELECT"] = SCANCODE_SELECT;
    // [Constant] int SCANCODE_STOP
    lua["SCANCODE_STOP"] = SCANCODE_STOP;
    // [Constant] int SCANCODE_AGAIN
    lua["SCANCODE_AGAIN"] = SCANCODE_AGAIN;
    // [Constant] int SCANCODE_UNDO
    lua["SCANCODE_UNDO"] = SCANCODE_UNDO;
    // [Constant] int SCANCODE_CUT
    lua["SCANCODE_CUT"] = SCANCODE_CUT;
    // [Constant] int SCANCODE_COPY
    lua["SCANCODE_COPY"] = SCANCODE_COPY;
    // [Constant] int SCANCODE_PASTE
    lua["SCANCODE_PASTE"] = SCANCODE_PASTE;
    // [Constant] int SCANCODE_FIND
    lua["SCANCODE_FIND"] = SCANCODE_FIND;
    // [Constant] int SCANCODE_MUTE
    lua["SCANCODE_MUTE"] = SCANCODE_MUTE;
    // [Constant] int SCANCODE_VOLUMEUP
    lua["SCANCODE_VOLUMEUP"] = SCANCODE_VOLUMEUP;
    // [Constant] int SCANCODE_VOLUMEDOWN
    lua["SCANCODE_VOLUMEDOWN"] = SCANCODE_VOLUMEDOWN;
    // [Constant] int SCANCODE_KP_COMMA
    lua["SCANCODE_KP_COMMA"] = SCANCODE_KP_COMMA;
    // [Constant] int SCANCODE_KP_EQUALSAS400
    lua["SCANCODE_KP_EQUALSAS400"] = SCANCODE_KP_EQUALSAS400;
    // [Constant] int SCANCODE_INTERNATIONAL1
    lua["SCANCODE_INTERNATIONAL1"] = SCANCODE_INTERNATIONAL1;
    // [Constant] int SCANCODE_INTERNATIONAL2
    lua["SCANCODE_INTERNATIONAL2"] = SCANCODE_INTERNATIONAL2;
    // [Constant] int SCANCODE_INTERNATIONAL3
    lua["SCANCODE_INTERNATIONAL3"] = SCANCODE_INTERNATIONAL3;
    // [Constant] int SCANCODE_INTERNATIONAL4
    lua["SCANCODE_INTERNATIONAL4"] = SCANCODE_INTERNATIONAL4;
    // [Constant] int SCANCODE_INTERNATIONAL5
    lua["SCANCODE_INTERNATIONAL5"] = SCANCODE_INTERNATIONAL5;
    // [Constant] int SCANCODE_INTERNATIONAL6
    lua["SCANCODE_INTERNATIONAL6"] = SCANCODE_INTERNATIONAL6;
    // [Constant] int SCANCODE_INTERNATIONAL7
    lua["SCANCODE_INTERNATIONAL7"] = SCANCODE_INTERNATIONAL7;
    // [Constant] int SCANCODE_INTERNATIONAL8
    lua["SCANCODE_INTERNATIONAL8"] = SCANCODE_INTERNATIONAL8;
    // [Constant] int SCANCODE_INTERNATIONAL9
    lua["SCANCODE_INTERNATIONAL9"] = SCANCODE_INTERNATIONAL9;
    // [Constant] int SCANCODE_LANG1
    lua["SCANCODE_LANG1"] = SCANCODE_LANG1;
    // [Constant] int SCANCODE_LANG2
    lua["SCANCODE_LANG2"] = SCANCODE_LANG2;
    // [Constant] int SCANCODE_LANG3
    lua["SCANCODE_LANG3"] = SCANCODE_LANG3;
    // [Constant] int SCANCODE_LANG4
    lua["SCANCODE_LANG4"] = SCANCODE_LANG4;
    // [Constant] int SCANCODE_LANG5
    lua["SCANCODE_LANG5"] = SCANCODE_LANG5;
    // [Constant] int SCANCODE_LANG6
    lua["SCANCODE_LANG6"] = SCANCODE_LANG6;
    // [Constant] int SCANCODE_LANG7
    lua["SCANCODE_LANG7"] = SCANCODE_LANG7;
    // [Constant] int SCANCODE_LANG8
    lua["SCANCODE_LANG8"] = SCANCODE_LANG8;
    // [Constant] int SCANCODE_LANG9
    lua["SCANCODE_LANG9"] = SCANCODE_LANG9;
    // [Constant] int SCANCODE_ALTERASE
    lua["SCANCODE_ALTERASE"] = SCANCODE_ALTERASE;
    // [Constant] int SCANCODE_SYSREQ
    lua["SCANCODE_SYSREQ"] = SCANCODE_SYSREQ;
    // [Constant] int SCANCODE_CANCEL
    lua["SCANCODE_CANCEL"] = SCANCODE_CANCEL;
    // [Constant] int SCANCODE_CLEAR
    lua["SCANCODE_CLEAR"] = SCANCODE_CLEAR;
    // [Constant] int SCANCODE_PRIOR
    lua["SCANCODE_PRIOR"] = SCANCODE_PRIOR;
    // [Constant] int SCANCODE_RETURN2
    lua["SCANCODE_RETURN2"] = SCANCODE_RETURN2;
    // [Constant] int SCANCODE_SEPARATOR
    lua["SCANCODE_SEPARATOR"] = SCANCODE_SEPARATOR;
    // [Constant] int SCANCODE_OUT
    lua["SCANCODE_OUT"] = SCANCODE_OUT;
    // [Constant] int SCANCODE_OPER
    lua["SCANCODE_OPER"] = SCANCODE_OPER;
    // [Constant] int SCANCODE_CLEARAGAIN
    lua["SCANCODE_CLEARAGAIN"] = SCANCODE_CLEARAGAIN;
    // [Constant] int SCANCODE_CRSEL
    lua["SCANCODE_CRSEL"] = SCANCODE_CRSEL;
    // [Constant] int SCANCODE_EXSEL
    lua["SCANCODE_EXSEL"] = SCANCODE_EXSEL;
    // [Constant] int SCANCODE_KP_00
    lua["SCANCODE_KP_00"] = SCANCODE_KP_00;
    // [Constant] int SCANCODE_KP_000
    lua["SCANCODE_KP_000"] = SCANCODE_KP_000;
    // [Constant] int SCANCODE_THOUSANDSSEPARATOR
    lua["SCANCODE_THOUSANDSSEPARATOR"] = SCANCODE_THOUSANDSSEPARATOR;
    // [Constant] int SCANCODE_DECIMALSEPARATOR
    lua["SCANCODE_DECIMALSEPARATOR"] = SCANCODE_DECIMALSEPARATOR;
    // [Constant] int SCANCODE_CURRENCYUNIT
    lua["SCANCODE_CURRENCYUNIT"] = SCANCODE_CURRENCYUNIT;
    // [Constant] int SCANCODE_CURRENCYSUBUNIT
    lua["SCANCODE_CURRENCYSUBUNIT"] = SCANCODE_CURRENCYSUBUNIT;
    // [Constant] int SCANCODE_KP_LEFTPAREN
    lua["SCANCODE_KP_LEFTPAREN"] = SCANCODE_KP_LEFTPAREN;
    // [Constant] int SCANCODE_KP_RIGHTPAREN
    lua["SCANCODE_KP_RIGHTPAREN"] = SCANCODE_KP_RIGHTPAREN;
    // [Constant] int SCANCODE_KP_LEFTBRACE
    lua["SCANCODE_KP_LEFTBRACE"] = SCANCODE_KP_LEFTBRACE;
    // [Constant] int SCANCODE_KP_RIGHTBRACE
    lua["SCANCODE_KP_RIGHTBRACE"] = SCANCODE_KP_RIGHTBRACE;
    // [Constant] int SCANCODE_KP_TAB
    lua["SCANCODE_KP_TAB"] = SCANCODE_KP_TAB;
    // [Constant] int SCANCODE_KP_BACKSPACE
    lua["SCANCODE_KP_BACKSPACE"] = SCANCODE_KP_BACKSPACE;
    // [Constant] int SCANCODE_KP_A
    lua["SCANCODE_KP_A"] = SCANCODE_KP_A;
    // [Constant] int SCANCODE_KP_BACKSPACE
    lua["SCANCODE_KP_B"] = SCANCODE_KP_B;
    // [Constant] int SCANCODE_KP_COMMA
    lua["SCANCODE_KP_C"] = SCANCODE_KP_C;
    // [Constant] int SCANCODE_KP_DIVIDE
    lua["SCANCODE_KP_D"] = SCANCODE_KP_D;
    // [Constant] int SCANCODE_KP_ENTER
    lua["SCANCODE_KP_E"] = SCANCODE_KP_E;
    // [Constant] int SCANCODE_KP_F
    lua["SCANCODE_KP_F"] = SCANCODE_KP_F;
    // [Constant] int SCANCODE_KP_XOR
    lua["SCANCODE_KP_XOR"] = SCANCODE_KP_XOR;
    // [Constant] int SCANCODE_KP_POWER
    lua["SCANCODE_KP_POWER"] = SCANCODE_KP_POWER;
    // [Constant] int SCANCODE_KP_PERCENT
    lua["SCANCODE_KP_PERCENT"] = SCANCODE_KP_PERCENT;
    // [Constant] int SCANCODE_KP_LESS
    lua["SCANCODE_KP_LESS"] = SCANCODE_KP_LESS;
    // [Constant] int SCANCODE_KP_GREATER
    lua["SCANCODE_KP_GREATER"] = SCANCODE_KP_GREATER;
    // [Constant] int SCANCODE_KP_AMPERSAND
    lua["SCANCODE_KP_AMPERSAND"] = SCANCODE_KP_AMPERSAND;
    // [Constant] int SCANCODE_KP_DBLAMPERSAND
    lua["SCANCODE_KP_DBLAMPERSAND"] = SCANCODE_KP_DBLAMPERSAND;
    // [Constant] int SCANCODE_KP_VERTICALBAR
    lua["SCANCODE_KP_VERTICALBAR"] = SCANCODE_KP_VERTICALBAR;
    // [Constant] int SCANCODE_KP_DBLVERTICALBAR
    lua["SCANCODE_KP_DBLVERTICALBAR"] = SCANCODE_KP_DBLVERTICALBAR;
    // [Constant] int SCANCODE_KP_COLON
    lua["SCANCODE_KP_COLON"] = SCANCODE_KP_COLON;
    // [Constant] int SCANCODE_KP_HASH
    lua["SCANCODE_KP_HASH"] = SCANCODE_KP_HASH;
    // [Constant] int SCANCODE_KP_SPACE
    lua["SCANCODE_KP_SPACE"] = SCANCODE_KP_SPACE;
    // [Constant] int SCANCODE_KP_AT
    lua["SCANCODE_KP_AT"] = SCANCODE_KP_AT;
    // [Constant] int SCANCODE_KP_EXCLAM
    lua["SCANCODE_KP_EXCLAM"] = SCANCODE_KP_EXCLAM;
    // [Constant] int SCANCODE_KP_MEMSTORE
    lua["SCANCODE_KP_MEMSTORE"] = SCANCODE_KP_MEMSTORE;
    // [Constant] int SCANCODE_KP_MEMRECALL
    lua["SCANCODE_KP_MEMRECALL"] = SCANCODE_KP_MEMRECALL;
    // [Constant] int SCANCODE_KP_MEMCLEAR
    lua["SCANCODE_KP_MEMCLEAR"] = SCANCODE_KP_MEMCLEAR;
    // [Constant] int SCANCODE_KP_MEMADD
    lua["SCANCODE_KP_MEMADD"] = SCANCODE_KP_MEMADD;
    // [Constant] int SCANCODE_KP_MEMSUBTRACT
    lua["SCANCODE_KP_MEMSUBTRACT"] = SCANCODE_KP_MEMSUBTRACT;
    // [Constant] int SCANCODE_KP_MEMMULTIPLY
    lua["SCANCODE_KP_MEMMULTIPLY"] = SCANCODE_KP_MEMMULTIPLY;
    // [Constant] int SCANCODE_KP_MEMDIVIDE
    lua["SCANCODE_KP_MEMDIVIDE"] = SCANCODE_KP_MEMDIVIDE;
    // [Constant] int SCANCODE_KP_PLUSMINUS
    lua["SCANCODE_KP_PLUSMINUS"] = SCANCODE_KP_PLUSMINUS;
    // [Constant] int SCANCODE_KP_CLEAR
    lua["SCANCODE_KP_CLEAR"] = SCANCODE_KP_CLEAR;
    // [Constant] int SCANCODE_KP_CLEARENTRY
    lua["SCANCODE_KP_CLEARENTRY"] = SCANCODE_KP_CLEARENTRY;
    // [Constant] int SCANCODE_KP_BINARY
    lua["SCANCODE_KP_BINARY"] = SCANCODE_KP_BINARY;
    // [Constant] int SCANCODE_KP_OCTAL
    lua["SCANCODE_KP_OCTAL"] = SCANCODE_KP_OCTAL;
    // [Constant] int SCANCODE_KP_DECIMAL
    lua["SCANCODE_KP_DECIMAL"] = SCANCODE_KP_DECIMAL;
    // [Constant] int SCANCODE_KP_HEXADECIMAL
    lua["SCANCODE_KP_HEXADECIMAL"] = SCANCODE_KP_HEXADECIMAL;
    // [Constant] int SCANCODE_CTRL
    lua["SCANCODE_LCTRL"] = SCANCODE_LCTRL;
    // [Constant] int SCANCODE_SHIFT
    lua["SCANCODE_LSHIFT"] = SCANCODE_LSHIFT;
    // [Constant] int SCANCODE_ALT
    lua["SCANCODE_LALT"] = SCANCODE_LALT;
    // [Constant] int SCANCODE_GUI
    lua["SCANCODE_LGUI"] = SCANCODE_LGUI;
    // [Constant] int SCANCODE_RCTRL
    lua["SCANCODE_RCTRL"] = SCANCODE_RCTRL;
    // [Constant] int SCANCODE_RSHIFT
    lua["SCANCODE_RSHIFT"] = SCANCODE_RSHIFT;
    // [Constant] int SCANCODE_RALT
    lua["SCANCODE_RALT"] = SCANCODE_RALT;
    // [Constant] int SCANCODE_RGUI
    lua["SCANCODE_RGUI"] = SCANCODE_RGUI;
    // [Constant] int SCANCODE_MODE
    lua["SCANCODE_MODE"] = SCANCODE_MODE;
    // [Constant] int SCANCODE_AUDIONEXT
    lua["SCANCODE_AUDIONEXT"] = SCANCODE_AUDIONEXT;
    // [Constant] int SCANCODE_AUDIOPREV
    lua["SCANCODE_AUDIOPREV"] = SCANCODE_AUDIOPREV;
    // [Constant] int SCANCODE_AUDIOSTOP
    lua["SCANCODE_AUDIOSTOP"] = SCANCODE_AUDIOSTOP;
    // [Constant] int SCANCODE_AUDIOPLAY
    lua["SCANCODE_AUDIOPLAY"] = SCANCODE_AUDIOPLAY;
    // [Constant] int SCANCODE_AUDIOMUTE
    lua["SCANCODE_AUDIOMUTE"] = SCANCODE_AUDIOMUTE;
    // [Constant] int SCANCODE_MEDIASELECT
    lua["SCANCODE_MEDIASELECT"] = SCANCODE_MEDIASELECT;
    // [Constant] int SCANCODE_WWW
    lua["SCANCODE_WWW"] = SCANCODE_WWW;
    // [Constant] int SCANCODE_MAIL
    lua["SCANCODE_MAIL"] = SCANCODE_MAIL;
    // [Constant] int SCANCODE_CALCULATOR
    lua["SCANCODE_CALCULATOR"] = SCANCODE_CALCULATOR;
    // [Constant] int SCANCODE_COMPUTER
    lua["SCANCODE_COMPUTER"] = SCANCODE_COMPUTER;
    // [Constant] int SCANCODE_AC_SEARCH
    lua["SCANCODE_AC_SEARCH"] = SCANCODE_AC_SEARCH;
    // [Constant] int SCANCODE_AC_HOME
    lua["SCANCODE_AC_HOME"] = SCANCODE_AC_HOME;
    // [Constant] int SCANCODE_AC_BACK
    lua["SCANCODE_AC_BACK"] = SCANCODE_AC_BACK;
    // [Constant] int SCANCODE_AC_FORWARD
    lua["SCANCODE_AC_FORWARD"] = SCANCODE_AC_FORWARD;
    // [Constant] int SCANCODE_AC_STOP
    lua["SCANCODE_AC_STOP"] = SCANCODE_AC_STOP;
    // [Constant] int SCANCODE_AC_REFRESH
    lua["SCANCODE_AC_REFRESH"] = SCANCODE_AC_REFRESH;
    // [Constant] int SCANCODE_AC_BOOKMARKS
    lua["SCANCODE_AC_BOOKMARKS"] = SCANCODE_AC_BOOKMARKS;
    // [Constant] int SCANCODE_BRIGHTNESSDOWN
    lua["SCANCODE_BRIGHTNESSDOWN"] = SCANCODE_BRIGHTNESSDOWN;
    // [Constant] int SCANCODE_BRIGHTNESSUP
    lua["SCANCODE_BRIGHTNESSUP"] = SCANCODE_BRIGHTNESSUP;
    // [Constant] int SCANCODE_DISPLAYSWITCH
    lua["SCANCODE_DISPLAYSWITCH"] = SCANCODE_DISPLAYSWITCH;
    // [Constant] int SCANCODE_KBDILLUMTOGGLE
    lua["SCANCODE_KBDILLUMTOGGLE"] = SCANCODE_KBDILLUMTOGGLE;
    // [Constant] int SCANCODE_KBDILLUMDOWN
    lua["SCANCODE_KBDILLUMDOWN"] = SCANCODE_KBDILLUMDOWN;
    // [Constant] int SCANCODE_KBDILLUMUP
    lua["SCANCODE_KBDILLUMUP"] = SCANCODE_KBDILLUMUP;
    // [Constant] int SCANCODE_EJECT
    lua["SCANCODE_EJECT"] = SCANCODE_EJECT;
    // [Constant] int SCANCODE_SLEEP
    lua["SCANCODE_SLEEP"] = SCANCODE_SLEEP;
    // [Constant] int SCANCODE_APP1
    lua["SCANCODE_APP1"] = SCANCODE_APP1;
    // [Constant] int SCANCODE_APP2
    lua["SCANCODE_APP2"] = SCANCODE_APP2;

    // [Constant] int HAT_CENTER
    lua["HAT_CENTER"] = HAT_CENTER;
    // [Constant] int HAT_UP
    lua["HAT_UP"] = HAT_UP;
    // [Constant] int HAT_RIGHT
    lua["HAT_RIGHT"] = HAT_RIGHT;
    // [Constant] int HAT_DOWN
    lua["HAT_DOWN"] = HAT_DOWN;
    // [Constant] int HAT_LEFT
    lua["HAT_LEFT"] = HAT_LEFT;
    
    // [Constant] int CONTROLLER_BUTTON_A
    lua["CONTROLLER_BUTTON_A"] = CONTROLLER_BUTTON_A;
    // [Constant] int CONTROLLER_BUTTON_B
    lua["CONTROLLER_BUTTON_B"] = CONTROLLER_BUTTON_B;
    // [Constant] int CONTROLLER_BUTTON_X
    lua["CONTROLLER_BUTTON_X"] = CONTROLLER_BUTTON_X;
    // [Constant] int CONTROLLER_BUTTON_Y
    lua["CONTROLLER_BUTTON_Y"] = CONTROLLER_BUTTON_Y;
    // [Constant] int CONTROLLER_BUTTON_BACK
    lua["CONTROLLER_BUTTON_BACK"] = CONTROLLER_BUTTON_BACK;
    // [Constant] int CONTROLLER_BUTTON_GUIDE
    lua["CONTROLLER_BUTTON_GUIDE"] = CONTROLLER_BUTTON_GUIDE;
    // [Constant] int CONTROLLER_BUTTON_START
    lua["CONTROLLER_BUTTON_START"] = CONTROLLER_BUTTON_START;
    // [Constant] int CONTROLLER_BUTTON_LEFTSTICK
    lua["CONTROLLER_BUTTON_LEFTSTICK"] = CONTROLLER_BUTTON_LEFTSTICK;
    // [Constant] int CONTROLLER_BUTTON_RIGHTSTICK
    lua["CONTROLLER_BUTTON_RIGHTSTICK"] = CONTROLLER_BUTTON_RIGHTSTICK;
    // [Constant] int CONTROLLER_BUTTON_LEFTSHOULDER
    lua["CONTROLLER_BUTTON_LEFTSHOULDER"] = CONTROLLER_BUTTON_LEFTSHOULDER;
    // [Constant] int CONTROLLER_BUTTON_RIGHTSHOULDER
    lua["CONTROLLER_BUTTON_RIGHTSHOULDER"] = CONTROLLER_BUTTON_RIGHTSHOULDER;
    // [Constant] int CONTROLLER_BUTTON_DPAD_UP
    lua["CONTROLLER_BUTTON_DPAD_UP"] = CONTROLLER_BUTTON_DPAD_UP;
    // [Constant] int CONTROLLER_BUTTON_DPAD_DOWN
    lua["CONTROLLER_BUTTON_DPAD_DOWN"] = CONTROLLER_BUTTON_DPAD_DOWN;
    // [Constant] int CONTROLLER_BUTTON_DPAD_LEFT
    lua["CONTROLLER_BUTTON_DPAD_LEFT"] = CONTROLLER_BUTTON_DPAD_LEFT;
    // [Constant] int CONTROLLER_BUTTON_DPAD_RIGHT
    lua["CONTROLLER_BUTTON_DPAD_RIGHT"] = CONTROLLER_BUTTON_DPAD_RIGHT;

    // [Constant] int CONTROLLER_AXIS_LEFTX
    lua["CONTROLLER_AXIS_LEFTX"] = CONTROLLER_AXIS_LEFTX;
    // [Constant] int CONTROLLER_AXIS_LEFTY
    lua["CONTROLLER_AXIS_LEFTY"] = CONTROLLER_AXIS_LEFTY;
    // [Constant] int CONTROLLER_AXIS_RIGHTX
    lua["CONTROLLER_AXIS_RIGHTX"] = CONTROLLER_AXIS_RIGHTX;
    // [Constant] int CONTROLLER_AXIS_RIGHTY
    lua["CONTROLLER_AXIS_RIGHTY"] = CONTROLLER_AXIS_RIGHTY;
    // [Constant] int CONTROLLER_AXIS_TRIGGERLEFT
    lua["CONTROLLER_AXIS_TRIGGERLEFT"] = CONTROLLER_AXIS_TRIGGERLEFT;
    // [Constant] int CONTROLLER_AXIS_TRIGGERRIGHT
    lua["CONTROLLER_AXIS_TRIGGERRIGHT"] = CONTROLLER_AXIS_TRIGGERRIGHT;
}
}

