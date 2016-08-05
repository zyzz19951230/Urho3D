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

#include "../../Scene/SceneEvents.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSceneEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["E_SCENEUPDATE"] = E_SCENEUPDATE;
    lua["E_SCENESUBSYSTEMUPDATE"] = E_SCENESUBSYSTEMUPDATE;
    lua["E_UPDATESMOOTHING"] = E_UPDATESMOOTHING;
    lua["E_SCENEDRAWABLEUPDATEFINISHED"] = E_SCENEDRAWABLEUPDATEFINISHED;
    lua["E_TARGETPOSITION"] = E_TARGETPOSITION;
    lua["E_TARGETROTATION"] = E_TARGETROTATION;
    lua["E_ATTRIBUTEANIMATIONUPDATE"] = E_ATTRIBUTEANIMATIONUPDATE;
    lua["E_ATTRIBUTEANIMATIONADDED"] = E_ATTRIBUTEANIMATIONADDED;
    lua["E_ATTRIBUTEANIMATIONREMOVED"] = E_ATTRIBUTEANIMATIONREMOVED;
    lua["E_SCENEPOSTUPDATE"] = E_SCENEPOSTUPDATE;
    lua["E_ASYNCLOADPROGRESS"] = E_ASYNCLOADPROGRESS;
    lua["E_ASYNCLOADFINISHED"] = E_ASYNCLOADFINISHED;
    lua["E_NODEADDED"] = E_NODEADDED;
    lua["E_NODEREMOVED"] = E_NODEREMOVED;
    lua["E_COMPONENTADDED"] = E_COMPONENTADDED;
    lua["E_COMPONENTREMOVED"] = E_COMPONENTREMOVED;
    lua["E_NODENAMECHANGED"] = E_NODENAMECHANGED;
    lua["E_NODEENABLEDCHANGED"] = E_NODEENABLEDCHANGED;
    lua["E_NODETAGADDED"] = E_NODETAGADDED;
    lua["E_NODETAGREMOVED"] = E_NODETAGREMOVED;
    lua["E_COMPONENTENABLEDCHANGED"] = E_COMPONENTENABLEDCHANGED;
    lua["E_TEMPORARYCHANGED"] = E_TEMPORARYCHANGED;
    lua["E_NODECLONED"] = E_NODECLONED;
    lua["E_COMPONENTCLONED"] = E_COMPONENTCLONED;
    lua["E_INTERCEPTNETWORKUPDATE"] = E_INTERCEPTNETWORKUPDATE;
}
}

