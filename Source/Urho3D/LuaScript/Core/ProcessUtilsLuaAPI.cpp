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

    lua["ErrorDialog"] = function(&ErrorDialog);

    
    lua["ErrorExit"] = ErrorExitOverloads();
    lua["OpenConsoleWindow"] = function(&OpenConsoleWindow);
    lua["PrintLine"] = PrintLineOverloads();

    lua["GetArguments"] = function(&GetArguments);

    lua["GetConsoleInput"] = function(&GetConsoleInput);
    lua["GetPlatform"] = function(&GetPlatform);

    lua["GetNumPhysicalCPUs"] = function(&GetNumPhysicalCPUs);
    lua["GetNumLogicalCPUs"] = function(&GetNumLogicalCPUs);

    lua["SetMiniDumpDir"] = function(&SetMiniDumpDir);
    lua["GetMiniDumpDir"] = function(&GetMiniDumpDir);
}
}

