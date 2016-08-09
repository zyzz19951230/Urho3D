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

#include "../../Resource/ResourceEvents.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterResourceEvents(kaguya::State& lua)
{
    using namespace kaguya;

    // [Variable] URHO3D_EVENT(E_RELOADSTARTED, ReloadStarted)
    lua["E_RELOADSTARTED"] = E_RELOADSTARTED;
    // [Variable] URHO3D_EVENT(E_RELOADFINISHED, ReloadFinished)
    lua["E_RELOADFINISHED"] = E_RELOADFINISHED;
    // [Variable] URHO3D_EVENT(E_RELOADFAILED, ReloadFailed)
    lua["E_RELOADFAILED"] = E_RELOADFAILED;
    // [Variable] URHO3D_EVENT(E_FILECHANGED, FileChanged)
    lua["E_FILECHANGED"] = E_FILECHANGED;
    // [Variable] URHO3D_EVENT(E_LOADFAILED, LoadFailed)
    lua["E_LOADFAILED"] = E_LOADFAILED;
    // [Variable] URHO3D_EVENT(E_RESOURCENOTFOUND, ResourceNotFound)
    lua["E_RESOURCENOTFOUND"] = E_RESOURCENOTFOUND;
    // [Variable] URHO3D_EVENT(E_UNKNOWNRESOURCETYPE, UnknownResourceType)
    lua["E_UNKNOWNRESOURCETYPE"] = E_UNKNOWNRESOURCETYPE;
    // [Variable] URHO3D_EVENT(E_RESOURCEBACKGROUNDLOADED, ResourceBackgroundLoaded)
    lua["E_RESOURCEBACKGROUNDLOADED"] = E_RESOURCEBACKGROUNDLOADED;
    // [Variable] URHO3D_EVENT(E_CHANGELANGUAGE, ChangeLanguage)
    lua["E_CHANGELANGUAGE"] = E_CHANGELANGUAGE;
}
}

