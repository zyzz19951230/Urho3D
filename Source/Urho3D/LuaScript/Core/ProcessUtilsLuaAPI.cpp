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

#include "../../Core/ProcessUtils.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_FUNCTION_OVERLOADS(ErrorExitOverloads, ErrorExit, 0, 2);
KAGUYA_FUNCTION_OVERLOADS(PrintLineOverloads, PrintLine, 1, 2);

void RegisterProcessUtils(kaguya::State& lua)
{
    using namespace kaguya;

    // [Function] URHO3D_API void ErrorDialog(const String& title, const String& message)
    lua["ErrorDialog"] = function(&ErrorDialog);

    
    lua["ErrorExit"] = ErrorExitOverloads();
    // [Function] URHO3D_API void OpenConsoleWindow()
    lua["OpenConsoleWindow"] = function(&OpenConsoleWindow);
    lua["PrintLine"] = PrintLineOverloads();

    // [Function] URHO3D_API const Vector<String>& GetArguments()
    lua["GetArguments"] = function(&GetArguments);

    // [Function] URHO3D_API String GetConsoleInput()
    lua["GetConsoleInput"] = function(&GetConsoleInput);
    // [Function] URHO3D_API String GetPlatform()
    lua["GetPlatform"] = function(&GetPlatform);

    // [Function] URHO3D_API unsigned GetNumPhysicalCPUs()
    lua["GetNumPhysicalCPUs"] = function(&GetNumPhysicalCPUs);
    // [Function] URHO3D_API unsigned GetNumLogicalCPUs()
    lua["GetNumLogicalCPUs"] = function(&GetNumLogicalCPUs);

    // [Function] URHO3D_API void SetMiniDumpDir(const String& pathName)
    lua["SetMiniDumpDir"] = function(&SetMiniDumpDir);
    // [Function] URHO3D_API String GetMiniDumpDir()
    lua["GetMiniDumpDir"] = function(&GetMiniDumpDir);
}
}

