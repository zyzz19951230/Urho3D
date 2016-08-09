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

    // [Variable] URHO3D_EVENT(E_SCENEUPDATE, SceneUpdate)
    lua["E_SCENEUPDATE"] = E_SCENEUPDATE;
    // [Variable] URHO3D_EVENT(E_SCENESUBSYSTEMUPDATE, SceneSubsystemUpdate)
    lua["E_SCENESUBSYSTEMUPDATE"] = E_SCENESUBSYSTEMUPDATE;
    // [Variable] URHO3D_EVENT(E_UPDATESMOOTHING, UpdateSmoothing)
    lua["E_UPDATESMOOTHING"] = E_UPDATESMOOTHING;
    // [Variable] URHO3D_EVENT(E_SCENEDRAWABLEUPDATEFINISHED, SceneDrawableUpdateFinished)
    lua["E_SCENEDRAWABLEUPDATEFINISHED"] = E_SCENEDRAWABLEUPDATEFINISHED;
    // [Variable] URHO3D_EVENT(E_TARGETPOSITION, TargetPositionChanged)
    lua["E_TARGETPOSITION"] = E_TARGETPOSITION;
    // [Variable] URHO3D_EVENT(E_TARGETROTATION, TargetRotationChanged)
    lua["E_TARGETROTATION"] = E_TARGETROTATION;
    // [Variable] URHO3D_EVENT(E_ATTRIBUTEANIMATIONUPDATE, AttributeAnimationUpdate)
    lua["E_ATTRIBUTEANIMATIONUPDATE"] = E_ATTRIBUTEANIMATIONUPDATE;
    // [Variable] URHO3D_EVENT(E_ATTRIBUTEANIMATIONADDED, AttributeAnimationAdded)
    lua["E_ATTRIBUTEANIMATIONADDED"] = E_ATTRIBUTEANIMATIONADDED;
    // [Variable] URHO3D_EVENT(E_ATTRIBUTEANIMATIONREMOVED, AttributeAnimationRemoved)
    lua["E_ATTRIBUTEANIMATIONREMOVED"] = E_ATTRIBUTEANIMATIONREMOVED;
    // [Variable] URHO3D_EVENT(E_SCENEPOSTUPDATE, ScenePostUpdate)
    lua["E_SCENEPOSTUPDATE"] = E_SCENEPOSTUPDATE;
    // [Variable] URHO3D_EVENT(E_ASYNCLOADPROGRESS, AsyncLoadProgress)
    lua["E_ASYNCLOADPROGRESS"] = E_ASYNCLOADPROGRESS;
    // [Variable] URHO3D_EVENT(E_ASYNCLOADFINISHED, AsyncLoadFinished)
    lua["E_ASYNCLOADFINISHED"] = E_ASYNCLOADFINISHED;
    // [Variable] URHO3D_EVENT(E_NODEADDED, NodeAdded)
    lua["E_NODEADDED"] = E_NODEADDED;
    // [Variable] URHO3D_EVENT(E_NODEREMOVED, NodeRemoved)
    lua["E_NODEREMOVED"] = E_NODEREMOVED;
    // [Variable] URHO3D_EVENT(E_COMPONENTADDED, ComponentAdded)
    lua["E_COMPONENTADDED"] = E_COMPONENTADDED;
    // [Variable] URHO3D_EVENT(E_COMPONENTREMOVED, ComponentRemoved)
    lua["E_COMPONENTREMOVED"] = E_COMPONENTREMOVED;
    // [Variable] URHO3D_EVENT(E_NODENAMECHANGED, NodeNameChanged)
    lua["E_NODENAMECHANGED"] = E_NODENAMECHANGED;
    // [Variable] URHO3D_EVENT(E_NODEENABLEDCHANGED, NodeEnabledChanged)
    lua["E_NODEENABLEDCHANGED"] = E_NODEENABLEDCHANGED;
    // [Variable] URHO3D_EVENT(E_NODETAGADDED, NodeTagAdded)
    lua["E_NODETAGADDED"] = E_NODETAGADDED;
    // [Variable] URHO3D_EVENT(E_NODETAGREMOVED, NodeTagRemoved)
    lua["E_NODETAGREMOVED"] = E_NODETAGREMOVED;
    // [Variable] URHO3D_EVENT(E_COMPONENTENABLEDCHANGED, ComponentEnabledChanged)
    lua["E_COMPONENTENABLEDCHANGED"] = E_COMPONENTENABLEDCHANGED;
    // [Variable] URHO3D_EVENT(E_TEMPORARYCHANGED, TemporaryChanged)
    lua["E_TEMPORARYCHANGED"] = E_TEMPORARYCHANGED;
    // [Variable] URHO3D_EVENT(E_NODECLONED, NodeCloned)
    lua["E_NODECLONED"] = E_NODECLONED;
    // [Variable] URHO3D_EVENT(E_COMPONENTCLONED, ComponentCloned)
    lua["E_COMPONENTCLONED"] = E_COMPONENTCLONED;
    // [Variable] URHO3D_EVENT(E_INTERCEPTNETWORKUPDATE, InterceptNetworkUpdate)
    lua["E_INTERCEPTNETWORKUPDATE"] = E_INTERCEPTNETWORKUPDATE;
}
}

